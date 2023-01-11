#include <iostream>
#include <unistd.h>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "THStack.h"
//#include "CC0PiNumu.h"  //src: /disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu
#include "DefBeamMode.h"
#include "DefOscChannels.h"

#include "include/NeutrinoEvents.h"
#include "include/NTagVariables.h"
#include "include/CLTOption.h"
#include "include/ResultSummary.h"
#include "include/VECTChannelChecker.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"


constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;


int main(int argc, char **argv) {

  TString fiTQunFileName = argv[1];
  TString NtagFileName   = argv[2];
  TString OutputRootName = argv[3];
  TString ResultSummary  = argv[4];
  TString NTagSummary    = argv[5];
  TString MCTypeKeyword  = argv[6];
  TString MCType         = argv[7];
  TString ETAGKeyword    = argv[8];
  TString ETAG           = argv[9];
  TString BeamKeyword    = argv[10];
  TString Beam           = argv[11];
  TString OscKeyword     = argv[12];
  TString Osc            = argv[13];

  enum BeamMode::E_BEAM_MODE eMode;
  enum OscChan::E_OSC_CHAN eOsc;
  eMode = CLTOptionBeamMode(BeamKeyword, Beam);
  eOsc  = CLTOptionOscMode(OscKeyword, Osc);
  CLTOptionETAG(ETAGKeyword, ETAG);

  float thetamin = -1.;
  //float thetamin = 0.;
  //float thetamin = 0.2;
  //float thetamin = 0.4;
  //float thetamin = 0.6;
  //float thetamin = 0.8;
  float thetamax = 1.;


  //=========  fiTQun output (TTree: h1)  ============
  TChain *tchfQ = new TChain("h1");
  int nfQFiles = tchfQ->Add( fiTQunFileName );
  if ( nfQFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree h1 from: " << fiTQunFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: event)  ============
  TChain *tchev = new TChain("event");
  int nevFiles = tchev->Add( NtagFileName );
  if ( nevFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree event from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: particle)  ============
  TChain *tchpar = new TChain("particle");
  int nparFiles = tchpar->Add( NtagFileName );
  if ( nparFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree particle from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  Delayed info (TTree: taggable)  ============
  TChain *tchtaggable = new TChain("taggable");
  int ntaggableFiles = tchtaggable->Add( NtagFileName );
  if ( ntaggableFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree taggable from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if ( ntagFiles==0 ) {
    std::cout << "[### analysis1Rmu ###]  Cannot load TTree ntag from: " << NtagFileName << std::endl;
    std::cout << "[### analysis1Rmu ###]  -> EXIT " << std::endl;
    exit(-1);
  }
  //Load succeed
  std::cout << "[### analysis1Rmu ###]  Loaded " << nfQFiles       << " files from: " << fiTQunFileName << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << nevFiles       << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << nparFiles      << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntaggableFiles << " files from: " << NtagFileName   << std::endl;
  std::cout << "[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: " << NtagFileName   << std::endl;


  const int nfQEntries       = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries       = tchev->GetEntries();       //total entries of TTree event
  const int nparEntries      = tchpar->GetEntries();       //total entries of TTree particle
  const int ntaggableEntries = tchtaggable->GetEntries(); //total entries of TTree taggable
  const int ntagEntries      = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Particle info     : Processing " << nparEntries      <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  Delayed info      : Processing " << ntaggableEntries <<" entries..." << std::endl;
  std::cout << "[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries..." << std::endl;


  //=========  TTree event variables  ============
  float NTrueN = 0.;
  float vecvx  = 0.;
  float vecvy  = 0.;
  float vecvz  = 0.;
  tchev->SetBranchAddress("NTrueN", &NTrueN);
  tchev->SetBranchAddress("vecvx", &vecvx);
  tchev->SetBranchAddress("vecvy", &vecvy);
  tchev->SetBranchAddress("vecvz", &vecvz);
  //=========  TTree taggable variables  ============
  std::vector<int> *Type = 0;
  TBranch *bType = 0;
  std::vector<float> *E = 0;
  TBranch *bE = 0;
  std::vector<float> *t = 0;
  TBranch *bt = 0;
  std::vector<float> *DWall = 0;
  TBranch *bDWall = 0;
  std::vector<float> *tagvx = 0;
  TBranch *btagvx = 0;
  std::vector<float> *tagvy = 0;
  TBranch *btagvy = 0;
  std::vector<float> *tagvz = 0;
  TBranch *btagvz = 0;
  std::vector<float> *DistFromPV = 0;
  TBranch *bDistFromPV = 0;
  tchtaggable->SetBranchAddress("Type", &Type, &bType);
  tchtaggable->SetBranchAddress("E", &E, &bE);
  tchtaggable->SetBranchAddress("t", &t, &bt);
  tchtaggable->SetBranchAddress("DWall", &DWall, &bDWall);
  tchtaggable->SetBranchAddress("tagvx", &tagvx, &btagvx);
  tchtaggable->SetBranchAddress("tagvy", &tagvy, &btagvy);
  tchtaggable->SetBranchAddress("tagvz", &tagvz, &btagvz);
  tchtaggable->SetBranchAddress("DistFromPV", &DistFromPV, &bDistFromPV);
  //=========  TTree partilce variables  ============
  std::vector<int> *PID = 0;
  TBranch *bPID = 0;
  std::vector<int> *ParentPID = 0;
  TBranch *bParentPID = 0;
  std::vector<int> *IntID = 0;
  TBranch *bIntID = 0;
  tchpar->SetBranchAddress("PID", &PID, &bPID);
  tchpar->SetBranchAddress("ParentPID", &ParentPID, &bParentPID);
  tchpar->SetBranchAddress("IntID", &IntID, &bIntID);
  //=========  TTree ntag variables  ============
  int NCandidates = 0;
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *TagClass = 0;
  TBranch *bTagClass = 0;
  std::vector<float> *FitT = 0;
  TBranch *bFitT = 0;
  std::vector<float> *TagDWall = 0;
  TBranch *bTagDWall = 0;
  std::vector<float> *NHits = 0;
  TBranch *bNHits = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("DWall", &TagDWall, &bTagDWall);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("pscnd", pscnd);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu? ======
  Float_t posv[3];          //Primary vertex
  Int_t   npar;
  Int_t   npar2;            //Number of secondary vertex
  Float_t posv2[100][3];    //Secondary vertex
  Int_t   ipv[100];         //GEANT code of primary particle
  UInt_t  ipv2[100];        //GEANT code of secondary particle
  Float_t wallv2[100];      //dwall of the secondary particle
  Int_t   Npvc;             //Number of primary particles
  Int_t   Ipvc[100];        //PID of primary particles
  Float_t Pvc[100][3];      //Momentum of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Ichvc[100];       //Chase at detector simulation or not (1: chase/0: not chase)
  Int_t   Iorgvc[100];      //Index of parent particle (0: initial particles, n: n-th final particle at the primary interaction)
  Int_t   nscndprt;         //Number of secondary particles
  Int_t   iprtscnd[1000];   //PID of the secondary particle
  Float_t tscnd[1000];      //Generated time of secondary particles
  Float_t vtxscnd[1000][3]; //Generated vertex of secondary particles
  Int_t   iprntprt[1000];   //PID of the parent of this secondary particle
  Int_t   iorgprt[1000];
  Float_t vtxprnt[1000][3];
  Int_t   iprnttrk[1000];
  Int_t   iprntidx[1000];   //Index of the parent particle (0: no parent(connected from primary particles), n: the parent of n-th secondary particle)
  Int_t   ichildidx[1000];  //Index of the first child particle (0: no childs, n: the first child of n-th secondary particle)
  Int_t   lmecscnd[1000];   //Interaction code of secondary particles based on GEANT
  tchfQ -> SetBranchAddress("posv", posv);
  tchfQ -> SetBranchAddress("npar", &npar);
  tchfQ -> SetBranchAddress("npar2", &npar2);
  tchfQ -> SetBranchAddress("posv2", posv2);
  tchfQ -> SetBranchAddress("wallv2", wallv2);
  tchfQ -> SetBranchAddress("ipv2", ipv2);
  tchfQ -> SetBranchAddress("Npvc", &Npvc);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  tchfQ -> SetBranchAddress("Ichvc", Ichvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  tchfQ -> SetBranchAddress("nscndprt", &nscndprt);
  tchfQ -> SetBranchAddress("iprtscnd", iprtscnd);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("vtxscnd", vtxscnd);
  tchfQ -> SetBranchAddress("iprntprt", iprntprt);
  tchfQ -> SetBranchAddress("iorgprt", iorgprt);
  tchfQ -> SetBranchAddress("vtxprnt", vtxprnt);
  tchfQ -> SetBranchAddress("iprnttrk", iprnttrk);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
  tchfQ -> SetBranchAddress("lmecscnd", lmecscnd);

  ResetNeutrinoEvents();
  InitNTagVariables();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();
  decayebox.SetHistoFormat();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NeutrinoOscillation neuosc;
  neuosc.SetHistoFrame();
  neuosc.SetHistoFormat();

  DistanceViewer ndistance;
  DistanceMax = 5.;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();

  NTagAnalysis ntagana;
  ntagana.InitNeutrons();
  ntagana.SetHistoFrame();
  ntagana.SetHistoFormat();


  //Process
  if (MCTypeKeyword=="-MCType") {
    if (MCType=="Gd" || MCType=="gd") processmax = ntagEntries;
    else if (MCType=="Water" || MCType=="water") processmax = nfQEntries;
    else {
      std::cout << " " << std::endl;
      std::cout << "[!!!CLT error!!!] MC type can not be found. --- input Gd or Water" << std::endl;
      exit(-1); 
    }
  }
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);


  int PrmMuons  = 0;
  int ScndMuons = 0;
  int BremMuons = 0;
  int PrmMuons_wNeutron = 0;
  int PrmMuons_wCapNeutron = 0;

  int Neutron_PrmMuon = 0;
  int CapNeutron_PrmMuon = 0;

  int Neutron_Nu = 0;

  for (int ientry=0; ientry<processmax; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "[### analysis1Rmu ###]  Progress: " << 100.*ientry/processmax << "%" << std::endl;

    //All neutrino events
    AllParentNeutrinos++;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bPID        -> GetEntry(tentry);
    bParentPID  -> GetEntry(tentry);
    bIntID      -> GetEntry(tentry);
    bType       -> GetEntry(tentry);
    bE          -> GetEntry(tentry);
    bDWall      -> GetEntry(tentry);
    btagvx      -> GetEntry(tentry);
    btagvy      -> GetEntry(tentry);
    btagvz      -> GetEntry(tentry);
    bDistFromPV -> GetEntry(tentry);
    bLabel      -> GetEntry(tentry);
    bTagClass   -> GetEntry(tentry);
    bFitT       -> GetEntry(tentry);
    bTagDWall   -> GetEntry(tentry);
    bNHits      -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    h1_NTrueN[0] -> Fill(NTrueN);

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false)) {
      //GetSelectedModeEvents(numu);
    

      // Primary particles
      float OscProb = numu->getOscWgt();
      int mode = TMath::Abs(numu->var<int>("mode"));
      //int prmneutrons = 0;
      //int prmmuons = 0;
      //GetNeutrinoInteraction(ientry, mode);
      //std::cout << "------  VCWORK primary info  ------" << std::endl;
      //for (int iprm=0; iprm<Npvc; iprm++) {
      //  std::cout << "[### " << ientry << " ###] Particle[" << iprm << "]=" << Ipvc[iprm]
      //                                   << ", Iflvc=" << Iflvc[iprm] 
      //                                   << ", Ichvc=" << Ichvc[iprm]
      //                                   << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
      
        //Find neutrons at neutrino interaction+FSI (exclude initial neutron)
      //  if (Ipvc[iprm]==static_cast<int>(PDGPID::NEUTRON) && 
      //      Iorgvc[iprm]!=0) prmneutrons++;

        //Find muons in prmiary interaction
      //  if (std::fabs(Ipvc[iprm])==static_cast<int>(PDGPID::MUON)) prmmuons++;
      //}
      //PrmMuons += prmmuons;


      float PrmVtx[3] = {0., 0., 0.};  //Primary vertex
      PrmVtx[0] = posv[0];
      PrmVtx[1] = posv[1];
      PrmVtx[2] = posv[2];


      float MuCapVtx[3] = {0., 0., 0.};  //mu capture vertex

      bool  MuDcy = false;               //Primary mu decays?
      float MuDcyVtx[3] = {0., 0., 0.};  //mu decay vertex

      float MuNCapVtx[3] = {0., 0., 0.}; //neutron(from mu capture) capture vertex

      //bool  NuNCap = false;              //Neutron capture from primary interaction?
      float NuNCapVtx[3] = {0., 0., 0.}; //neutron(from primary interaction) capture vertex

      //Focus on CC
      if (mode<31) {

        //Find primary mu (use for neutron from primary interaction)
        for (int iscnd=0; iscnd<nscndprt; iscnd++) {
          //std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << iprtscnd[iscnd]
          //                               << ", iprntprt=" << iprntprt[iscnd]
          //                               << ", iprntidx=" << iprntidx[iscnd] 
          //                               << ", ichildidx=" << ichildidx[iscnd] 
          //                               << ", lmecscnd=" << lmecscnd[iscnd] 
          //                               << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " << vtxscnd[iscnd][1] << ", " << vtxscnd[iscnd][2] << "]" 
          //                               << ", vtxprnt=[" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2] << "]" << std::endl;

          if (( std::fabs(iprtscnd[iscnd])==static_cast<int>(PDGPID::ELECTRON) || 
                iprtscnd[iscnd]==static_cast<int>(PDGPID::NEUTRON) ) &&
              std::fabs(iprntprt[iscnd])==static_cast<int>(PDGPID::MUON) &&
              iprntidx[iscnd]==0) 
          {
            MuDcy = true;
            MuDcyVtx[0] = vtxscnd[iscnd][0];
            MuDcyVtx[1] = vtxscnd[iscnd][1];
            MuDcyVtx[2] = vtxscnd[iscnd][2];
            //std::cout << "[### " << ientry << " ###] MuDcyVtx=[" << MuDcyVtx[0] << ", " << MuDcyVtx[1] << ", " << MuDcyVtx[2] << "]" << std::endl;
          }
        }

        //Find captured neutrons
        std::vector<float> VtxPrntList;
        std::vector<float> VtxScndList;
        for (int iscnd=0; iscnd<nscndprt; iscnd++) {
          //std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << iprtscnd[iscnd]
          //                               << ", iprntprt=" << iprntprt[iscnd]
          //                               << ", iprntidx=" << iprntidx[iscnd] 
          //                               << ", ichildidx=" << ichildidx[iscnd] 
          //                               << ", lmecscnd=" << lmecscnd[iscnd] 
          //                               << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " << vtxscnd[iscnd][1] << ", " << vtxscnd[iscnd][2] << "]" 
          //                               << ", vtxprnt=[" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2] << "]" << std::endl;

          //Captured neutron
          //if (iprtscnd[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
          //    iprtscnd[ ichildidx[iscnd]-1 ]==static_cast<int>(PDGPID::GAMMA))
          if (iprtscnd[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
              lmecscnd[ ichildidx[iscnd]-1 ]==static_cast<int>(GEANTINT::NEUTRONCAPTURE))
          {
            //This neutron comes from mu capture
            if (iprntprt[iscnd]==static_cast<int>(PDGPID::MUON) &&
                lmecscnd[iscnd]==static_cast<int>(GEANTINT::DECAY)) 
            {
              MuCapVtx[0] = vtxscnd[iscnd][0];
              MuCapVtx[1] = vtxscnd[iscnd][1];
              MuCapVtx[2] = vtxscnd[iscnd][2];

              MuNCapVtx[0] = vtxscnd[ ichildidx[iscnd]-1 ][0];
              MuNCapVtx[1] = vtxscnd[ ichildidx[iscnd]-1 ][1];
              MuNCapVtx[2] = vtxscnd[ ichildidx[iscnd]-1 ][2];
              //std::cout << "[### " << ientry << " ###] MuNCapVtx=[" << MuNCapVtx[0] << ", " << MuNCapVtx[1] << ", " << MuNCapVtx[2] << "]" << std::endl;

              float d_MuCap_x_MuNCap_x = MuCapVtx[0] - MuNCapVtx[0];
              float d_MuCap_x_MuNCap_y = MuCapVtx[1] - MuNCapVtx[1];
              float d_MuCap_x_MuNCap_z = MuCapVtx[2] - MuNCapVtx[2];
              float d_MuCap_x_MuNCap   = std::sqrt( d_MuCap_x_MuNCap_x*d_MuCap_x_MuNCap_x +
                                                    d_MuCap_x_MuNCap_y*d_MuCap_x_MuNCap_y +
                                                    d_MuCap_x_MuNCap_z*d_MuCap_x_MuNCap_z );
              //h1_truedistance_mu_n -> Fill(d_MuCap_x_MuNCap/100.);
              h1_truedistance_mu_n -> Fill(d_MuCap_x_MuNCap/100., OscProb);
            }
          }


          //Gamma from captrued neutrons of nu interaction
          if (iprtscnd[iscnd]==static_cast<int>(PDGPID::GAMMA) &&
              iprntprt[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
              iprntidx[iscnd]==0 &&
              lmecscnd[iscnd]==static_cast<int>(GEANTINT::NEUTRONCAPTURE))
          {
            float d_vtxprnt = std::sqrt( vtxprnt[iscnd][0]*vtxprnt[iscnd][0] +
                                         vtxprnt[iscnd][1]*vtxprnt[iscnd][1] +
                                         vtxprnt[iscnd][2]*vtxprnt[iscnd][2] );
            float d_vtxscnd = std::sqrt( vtxscnd[iscnd][0]*vtxscnd[iscnd][0] +
                                         vtxscnd[iscnd][1]*vtxscnd[iscnd][1] +
                                         vtxscnd[iscnd][2]*vtxscnd[iscnd][2] );

            //First neutron
            if (VtxScndList.size()==0) {
              VtxScndList.push_back(d_vtxscnd);
              VtxPrntList.push_back(d_vtxprnt);
              NuNCapVtx[0] = vtxscnd[iscnd][0];
              NuNCapVtx[1] = vtxscnd[iscnd][1];
              NuNCapVtx[2] = vtxscnd[iscnd][2];
            }
            else {
              bool NewNeutron = false;
              for (UInt_t in=0; in<VtxPrntList.size(); in++) {
                if (VtxPrntList.at(in)!=d_vtxprnt) NewNeutron = true;
                else {
                  for (UInt_t jn=0; jn<VtxScndList.size(); jn++) {
                    if (VtxScndList.at(jn)!=d_vtxscnd) NewNeutron = true;
                    else NewNeutron = false;
                  }
                }
              }
              //If this is a new neutron
              if (NewNeutron) {
                VtxScndList.push_back(d_vtxscnd);
                VtxPrntList.push_back(d_vtxprnt);
                NuNCapVtx[0] = vtxscnd[iscnd][0];
                NuNCapVtx[1] = vtxscnd[iscnd][1];
                NuNCapVtx[2] = vtxscnd[iscnd][2];
              }
            }

            /*
            if (NeutronList.size()==0) {
              NeutronList.push_back(d_vtxprnt);
              NuNCapVtx[0] = vtxscnd[iscnd][0];
              NuNCapVtx[1] = vtxscnd[iscnd][1];
              NuNCapVtx[2] = vtxscnd[iscnd][2];
              //std::cout << "[### " << ientry << " ###] NuNCapVtx=[" << NuNCapVtx[0] << ", " << NuNCapVtx[1] << ", " << NuNCapVtx[2] << "]" << std::endl;
            }
            else {
              bool NewNeutron = false;
              for (UInt_t in=0; in<NeutronList.size(); in++) {
                if (NeutronList.at(in)!=d_vtxprnt) NewNeutron = true;
                else NewNeutron = false;
              }
              //If this is a new neutron
              if (NewNeutron) {
                NeutronList.push_back(d_vtxprnt);
                NuNCapVtx[0] = vtxscnd[iscnd][0];
                NuNCapVtx[1] = vtxscnd[iscnd][1];
                NuNCapVtx[2] = vtxscnd[iscnd][2];
                //std::cout << "[### " << ientry << " ###] NuNCapVtx=[" << NuNCapVtx[0] << ", " << NuNCapVtx[1] << ", " << NuNCapVtx[2] << "]" << std::endl;
              }
            }
            */
          }
          //std::cout << "[### " << ientry << " ###] MuDcy: " << MuDcy << std::endl;

          //If primary mu decays to other particles
          if (MuDcy) {
            float d_MuDcy_x_NuNCap_x = MuDcyVtx[0] - NuNCapVtx[0];
            float d_MuDcy_x_NuNCap_y = MuDcyVtx[1] - NuNCapVtx[1];
            float d_MuDcy_x_NuNCap_z = MuDcyVtx[2] - NuNCapVtx[2];
            float d_MuDcy_x_NuNCap   = std::sqrt( d_MuDcy_x_NuNCap_x*d_MuDcy_x_NuNCap_x +
                                                  d_MuDcy_x_NuNCap_y*d_MuDcy_x_NuNCap_y +
                                                  d_MuDcy_x_NuNCap_z*d_MuDcy_x_NuNCap_z );
            //h1_truedistance_nu_n -> Fill(d_MuDcy_x_NuNCap/100.);
            h1_truedistance_nu_n -> Fill(d_MuDcy_x_NuNCap/100., OscProb);
          }

        }
        VtxScndList.clear();
        VtxPrntList.clear();
      }


#if 0
      // Secondary partciles
      //std::cout << "------  CONVVECT secondary info  ------" << std::endl;
      int scndmuons = 0;
      int muonbrems = 0; //Number of bremsstralhung (muonbrems-1)
      for (int iscnd=0; iscnd<nscndprt; iscnd++) {

        //std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << iprtscnd[iscnd]
        //                               << ", iprntprt=" << iprntprt[iscnd]
        //                               << ", iprntidx=" << iprntidx[iscnd] 
        //                               << ", ichildidx=" << ichildidx[iscnd] 
        //                               << ", lmecscnd=" << lmecscnd[iscnd] 
        //                               << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " << vtxscnd[iscnd][1] << ", " << vtxscnd[iscnd][2] << "]" 
        //                               << ", vtxprnt=[" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2] << "]" << std::endl;

        //Find muons in secondary interactions
        if (std::fabs(iprtscnd[iscnd])==static_cast<int>(PDGPID::MUON)) scndmuons++;
        //Check muon bremsstralhung
        if (std::fabs(iprtscnd[iscnd])==static_cast<int>(PDGPID::MUON) && 
            lmecscnd[iscnd]==static_cast<int>(GEANTINT::BREMSS)) muonbrems++;
      }


      //Check fraction of muon captures
      bool prm_wneutron = false;    //flag for primary muon with neutrons
      bool prm_wcapneutron = false; //flag for primary muon with captured neutrons
      float d_nu_x_mucap = 0.; //distance between mu- stopping vertex and primary vertex
      if (prmmuons!=0) {

        for (int iscnd=0; iscnd<nscndprt; iscnd++) {

          //Find neutrons from muon
          if (iprtscnd[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
              iprntprt[iscnd]==static_cast<int>(PDGPID::MUON) &&
              lmecscnd[iscnd]==static_cast<int>(GEANTINT::DECAY))
          {
            //What is this muon? Primary or secondary
            //If the parent is primary muon(iprntidx=0), count it
            //std::cout << "iprntidx of neutron: " << iprntidx[iscnd] << std::endl;
            if (iprntidx[iscnd]==0) {
              prm_wneutron = true;
              Neutron_PrmMuon++;


              // n's children is gamma of n-capture?
              // if so, fill n's vertex
              //std::cout << "ichildidx of neutron: " << iprtscnd[ ichildidx[iscnd]-1 ] << std::endl;
              if (iprtscnd[ ichildidx[iscnd]-1 ]==static_cast<int>(PDGPID::GAMMA)) {
                prm_wcapneutron = true;
                CapNeutron_PrmMuon++;
              }


              //get n's generated vertex (= mu- stopping vertex)
              float d_x = vtxscnd[iscnd][0] - posv[0];
              float d_y = vtxscnd[iscnd][1] - posv[1];
              float d_z = vtxscnd[iscnd][2] - posv[2];
              d_nu_x_mucap = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z);
            }
          }
        }
      }


      //Find neutrons from nu interaction
      std::vector<float> dlist;  //store different distance neutrons
      for (int iscnd=0; iscnd<nscndprt; iscnd++) {

        float d_nu_x_ncap = 0.;

        //Find gamma from neutron capture
        if (iprtscnd[iscnd]==static_cast<int>(PDGPID::GAMMA) &&
            iprntprt[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
            lmecscnd[iscnd]==static_cast<int>(GEANTINT::NEUTRONCAPTURE)) {

          //What is the parent?
          //If iprntidx=0, it comes from nu interaction
          if (iprntidx[iscnd]==0) {

            //Fill gamma's vertex per one neutron
            //distinguish by distance?
            float d_x = vtxscnd[iscnd][0] - posv[0];
            float d_y = vtxscnd[iscnd][1] - posv[1];
            float d_z = vtxscnd[iscnd][2] - posv[2];
            d_nu_x_ncap = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z);
            
            //If this is first gamma,
            if (dlist.size()==0) {
              dlist.push_back(d_nu_x_ncap);
            }
            else {

              //Search different distance gamma
              int diff_count = 0;
              for (UInt_t ilist=0; ilist<dlist.size(); ilist++) {
                if (d_nu_x_ncap != dlist.at(ilist)) diff_count++;
              }
              if (diff_count!=0) dlist.push_back(d_nu_x_ncap);
            }

          }
        }
      }



      //if (scndmuons!=0) std::cout << "[### " << ientry << " ###] Secondary muons: " << scndmuons << std::endl;
      //if (muonbrems!=0) std::cout << "[### " << ientry << " ###] Muon Bremss: " << muonbrems << std::endl;
      ScndMuons += scndmuons;
      BremMuons += muonbrems; //correction of double muon counting

      //If it is CC and has the captured primiary mu-
      if (prm_wneutron) {
        PrmMuons_wNeutron++;
        //h1_truedistance_mu_n -> Fill(d_nu_x_mucap/100.);
      }

      //If it is CC and has the captured primary mu- with captured neutrons
      if (prm_wneutron && prm_wcapneutron) {
        PrmMuons_wCapNeutron++;
        h1_truedistance_mu_n -> Fill(d_nu_x_mucap/100.);
      }


      for (UInt_t in=0; in<dlist.size(); in++) {
        Neutron_Nu++;
        h1_truedistance_nu_n -> Fill(dlist.at(in)/100.);
      }

      //std::cout << " " << std::endl;
#endif

    } //New 1R muon selection
  }


  std::cout << "Primary muons: " << PrmMuons << std::endl;
  std::cout << "Nominal Secondary muons: " << ScndMuons << std::endl;
  std::cout << "Muon Bremss: " << BremMuons << std::endl;
  std::cout << "All muons: " << PrmMuons+ScndMuons-BremMuons << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << "Primary muons with neutrons: " << PrmMuons_wNeutron << std::endl;
  std::cout << "Primary muons with captured neutrons: " << PrmMuons_wCapNeutron << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << "Neutrons from primary mu- capture: " << Neutron_PrmMuon << std::endl;
  std::cout << "Captured neutrons from primary mu- capture: " << CapNeutron_PrmMuon << std::endl;
  std::cout << "-----------------" << std::endl;
  std::cout << "Neutrons from nu interaction: " << Neutron_Nu << std::endl;


  std::fstream resultfile;
  resultfile.open(ResultSummary, std::ios_base::out);
  if (!resultfile.is_open()) {
    std::cout << "Results can not be written in " << ResultSummary << std::endl;
  }
  else {
    resultfile << "[fiTQun OUTPUT] " << fiTQunFileName << std::endl;
    resultfile << "[NTag   OUTPUT] " << NtagFileName   << std::endl;
    resultfile << " " << std::endl;

    for (int i=0; i<SELECTIONCUTS; i++) {
      resultfile << "[Neutrino] C" << i << ": " << ProtoSelectedParentNeutrinos[i] << " -> " << SelectedParentNeutrinos[i] << std::endl;
      h1_1RmuonEvents->fArray[i+1]      = (float)SelectedParentNeutrinos[i]/SelectedParentNeutrinos[0];
      h1_Proto1RmuonEvents->fArray[i+1] = (float)ProtoSelectedParentNeutrinos[i]/ProtoSelectedParentNeutrinos[0];
    }
  }


  TFile* fout = new TFile(OutputRootName, "RECREATE");
  std::cout << "Output: " << OutputRootName << std::endl;
  fout -> cd();
  
  decayebox.cdDecayeBox(fout);
  decayebox.WritePlots();
  gDirectory -> cd("..");

  prmsel.cdGd1RmuonSelection(fout);
  prmsel.WritePlots();
  gDirectory -> cd("..");

  neuosc.cdNeutrinoOscillation(fout);
  neuosc.WritePlots();
  gDirectory -> cd("..");

  ndistance.cdDistanceViewer(fout);
  ndistance.WritePlots();
  gDirectory -> cd("..");

  //noise rate and efficiency for window optimization
  ntagana.SetNoiseRateGraph();
  ntagana.GetEfficiencyforWinOpt();
  ntagana.SetEfficiencyGraph(0);

  ntagana.cdNTagAnalysis(fout);
  ntagana.WritePlots();
  gDirectory -> cd("..");

}