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

float scaledTagEff = 0.75;


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


  int TruthNeutrons = 0;
  int TaggedTruthNeutrons = 0;

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
    

      int TrueNeutrons = 0;
      std::vector<float> neutronlists;
      std::vector<int> parentlists;
      int mode = TMath::Abs(numu->var<int>("mode"));

      for (int iscnd=0; iscnd<nscndprt; iscnd++) {

        float capturedistance = std::sqrt( vtxscnd[iscnd][0]*vtxscnd[iscnd][0] + 
                                           vtxscnd[iscnd][1]*vtxscnd[iscnd][1] + 
                                           vtxscnd[iscnd][2]*vtxscnd[iscnd][2] );

        //Find truth captured neutrons
        if (iprtscnd[iscnd]==static_cast<int>(PDGPID::GAMMA) &&
            iprntprt[iscnd]==static_cast<int>(PDGPID::NEUTRON) &&
            lmecscnd[iscnd]==static_cast<int>(GEANTINT::NEUTRONCAPTURE)) 
        {
          
          //If neutron list is still empty, fill the first captured neutron
          if (neutronlists.size()==0) {
            neutronlists.push_back(capturedistance);
            parentlists.push_back(iprntidx[iscnd]);
          }
          else {
            int notsamedistance = 0;
            int notsameparent = 0;
            for (UInt_t in=0; in<neutronlists.size(); in++) {
              if (capturedistance!=neutronlists.at(in)) notsamedistance++;
            }
            for (UInt_t ip=0; ip<parentlists.size(); ip++) {
              if (iprntidx[iscnd]!=parentlists.at(ip)) notsameparent++;
            }
            //If there is no same distance neutrons, add it
            if ((UInt_t)notsamedistance==neutronlists.size() || 
                (UInt_t)notsameparent==parentlists.size()) {
              neutronlists.push_back(capturedistance);
              parentlists.push_back(iprntidx[iscnd]);
            }
          }
        }
      }
      TrueNeutrons   = neutronlists.size();  // # of true neutrons per neutrino events
      TruthNeutrons += neutronlists.size();  // # of all true neutrons
      //for (UInt_t ip=0; ip<parentlists.size(); ip++) {
      //  std::cout << parentlists.at(ip) << std::endl;
      //}
      //std::cout << "NTrueN=" << NTrueN << ", TrueNeutrons=" << TrueNeutrons << std::endl;
      //if (NTrueN!=TrueNeutrons) std::cout << "[### " << ientry << " ###] not macthed" << std::endl;



      //Get the number of "pseudo" tagged neutrons
      std::random_device rd;
      std::default_random_engine eng(rd());
      std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX); //assume uniform distribution
      int taggedneutrons = 0;  // # of tagged neutrons per neutrino event
      for (UInt_t in=0; in<neutronlists.size(); in++) {
        float TagProb = distr(eng);  // Tagging probability
        //if (TagProb < 0.75) {
        if (TagProb < scaledTagEff) {
          taggedneutrons++;
          TaggedTruthNeutrons++;
        }
      }


      //Based on the number of tagged neutrons, split neutrino interactions
      float OscProb = numu->getOscWgt();
      float RecoEnu = numu->var<float>("erec");

      //Energy pectrum
      if (mode==1) h1_OscProb[0] -> Fill(RecoEnu/1000., OscProb);
      if (mode>=2 && mode<=10) h1_OscProb[1] -> Fill(RecoEnu/1000., OscProb);
      if (mode>10 && mode<=30) h1_OscProbCCOther -> Fill(RecoEnu/1000., OscProb);
      if (mode>=31) h1_OscProb[2] -> Fill(RecoEnu/1000.);

      //Separation fraction
      if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
        if (mode==1) OscillatedCCQE += OscProb;
        if (mode>=2 && mode<=10) OscillatedCCnonQE += OscProb;
        if (mode==13) OscillatedCCRESp += OscProb;
        if (mode==11) OscillatedCCRESpp += OscProb;
        if (mode==12) OscillatedCCRES0 += OscProb;
        if (mode>14 && mode<=30) OscillatedCCOther += OscProb;
        if (mode>=31) OscillatedNC++;
      }

      if (taggedneutrons==0) {
        //Energy pectrum
        if (mode==1) h1_OscProb_woNeutron[0] -> Fill(RecoEnu/1000., OscProb);                 //CCQE(1p1h)
        if (mode>=2 && mode<=10) h1_OscProb_woNeutron[1] -> Fill(RecoEnu/1000., OscProb);     //CC 2p2h
        if (mode>10 && mode<=30) h1_OscProbCCOther_woNeutron -> Fill(RecoEnu/1000., OscProb); //CC RES+CC Other
        if (mode>=31) h1_OscProb_woNeutron[2] -> Fill(RecoEnu/1000.);                         //NC

        //Separation fraction
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          if (mode==1) OscillatedCCQE_woTagN += OscProb;
          if (mode>=2 && mode<=10) OscillatedCCnonQE_woTagN += OscProb;
          if (mode==13) OscillatedCCRESp_woTagN += OscProb;
          if (mode==11) OscillatedCCRESpp_woTagN += OscProb;
          if (mode==12) OscillatedCCRES0_woTagN += OscProb;
          if (mode>14 && mode<=30) OscillatedCCOther_woTagN += OscProb;
          if (mode>=31) OscillatedNC_woTagN++;
        }
      }
      else {
        //Energy fraction
        if (mode==1) h1_OscProb_wNeutron[0] -> Fill(RecoEnu/1000., OscProb);                 //CCQE(1p1h)
        if (mode>=2 && mode<=10) h1_OscProb_wNeutron[1] -> Fill(RecoEnu/1000., OscProb);     //CC 2p2h
        if (mode>10 && mode<=30) h1_OscProbCCOther_wNeutron -> Fill(RecoEnu/1000., OscProb); //CC RES+CC Other
        if (mode>=31) h1_OscProb_wNeutron[2] -> Fill(RecoEnu/1000.);                         //NC

        //Separation fraction
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          if (mode==1) OscillatedCCQE_wTagN += OscProb;
          if (mode>=2 && mode<=10) OscillatedCCnonQE_wTagN += OscProb;
          if (mode==13) OscillatedCCRESp_wTagN += OscProb;
          if (mode==11) OscillatedCCRESpp_wTagN += OscProb;
          if (mode==12) OscillatedCCRES0_wTagN += OscProb;
          if (mode>14 && mode<=30) OscillatedCCOther_wTagN += OscProb;
          if (mode>=31) OscillatedNC_wTagN++;
        }
      }


      neutronlists.clear();
      parentlists.clear();

      //std::cout << " " << std::endl;
      
    } //New 1R muon selection
  }


  std::cout << "# of truth neutrons: " << TruthNeutrons << std::endl;
  std::cout << "# of tagged truth neutrons: " << TaggedTruthNeutrons << std::endl;



  std::fstream resultfile;
  resultfile.open(ResultSummary, std::ios_base::out);
  if (!resultfile.is_open()) {
    std::cout << "Results can not be written in " << ResultSummary << std::endl;
  }
  else {
    resultfile << "[fiTQun OUTPUT] " << fiTQunFileName << std::endl;
    resultfile << "[NTag   OUTPUT] " << NtagFileName   << std::endl;
    resultfile << " " << std::endl;

    resultfile << "[Generated] CCQE   : " << SelectedCCQEevents    << std::endl;
    resultfile << "[Generated] CC2p2h : " << SelectedCC2p2hevents  << std::endl;
    resultfile << "[Generated] CCOther: " << SelectedCCnonQEevents << std::endl;
    resultfile << "[Generated] NC     : " << SelectedNCevents      << std::endl;
    resultfile << " " << std::endl;

    for (int i=0; i<SELECTIONCUTS; i++) {
      resultfile << "[Neutrino] C" << i+1 << ": " << ProtoSelectedParentNeutrinos[i] << " -> " << SelectedParentNeutrinos[i] << std::endl;
      //h1_1RmuonEvents      -> SetBinContent(i+1, (float)SelectedParentNeutrinos[i]/SelectedParentNeutrinos[0]);
      //h1_Proto1RmuonEvents -> SetBinContent(i+1, (float)ProtoSelectedParentNeutrinos[i]/ProtoSelectedParentNeutrinos[0]);
      h1_1RmuonEvents      -> SetBinContent(i+1, SelectedParentNeutrinos[i]);
      h1_Proto1RmuonEvents -> SetBinContent(i+1, ProtoSelectedParentNeutrinos[i]);

      h1_SelNuEvents[0]->fArray[i+1]    = SelectedCCQENeutrinos[i];
      h1_SelNuEvents[1]->fArray[i+1]    = SelectedCC2p2hNeutrinos[i];
      h1_SelNuEvents[2]->fArray[i+1]    = SelectedCCnonQENeutrinos[i];
      h1_SelNuEvents[3]->fArray[i+1]    = SelectedNCNeutrinos[i];
      h1_SelTagN[0]->fArray[i+1]        = SelectedCCQETagN[i];
      h1_SelTagN[1]->fArray[i+1]        = SelectedCC2p2hTagN[i];
      h1_SelTagN[2]->fArray[i+1]        = SelectedCCnonQETagN[i];
      h1_SelTagN[3]->fArray[i+1]        = SelectedNCTagN[i];

      resultfile << "  ======  # of selected neutrinos  ======" << std::endl;
      resultfile << "  CCQE    (osc.): " << SelectedCCQENeutrinos[i]    << std::endl;
      resultfile << "  CC-2p2h (osc.): " << SelectedCC2p2hNeutrinos[i]  << std::endl;
      resultfile << "  CC-Other(osc.): " << SelectedCCnonQENeutrinos[i] << std::endl;
      resultfile << "  NC      (osc.): " << SelectedNCNeutrinos[i]      << std::endl;
      resultfile << "  ------------------------------------------"      << std::endl;
      resultfile << "  Total   (osc.): " << SelectedCCQENeutrinos[i]+SelectedCC2p2hNeutrinos[i]+SelectedCCnonQENeutrinos[i]+SelectedNCNeutrinos[i] << std::endl;
      resultfile << " " << std::endl;
      resultfile << "  CCQE    (No osc.): " << SelectedNoOscCCQENeutrinos[i]    << std::endl;
      resultfile << "  CC-2p2h (No osc.): " << SelectedNoOscCC2p2hNeutrinos[i]  << std::endl;
      resultfile << "  CC-Other(No osc.): " << SelectedNoOscCCnonQENeutrinos[i] << std::endl;
      resultfile << "  NC      (No osc.): " << SelectedNoOscNCNeutrinos[i]      << std::endl;
      resultfile << "  ------------------------------------------"      << std::endl;
      resultfile << "  Total   (No osc.): " << SelectedNoOscCCQENeutrinos[i]+SelectedNoOscCC2p2hNeutrinos[i]+SelectedNoOscCCnonQENeutrinos[i]+SelectedNoOscNCNeutrinos[i] << std::endl;
      resultfile << " " << std::endl;
      resultfile << "  ======  # of selected tagged-n  ======" << std::endl;
      resultfile << "  CCQE    (osc.): " << SelectedCCQETagN[i]    << std::endl;
      resultfile << "  CC-2p2h (osc.): " << SelectedCC2p2hTagN[i]  << std::endl;
      resultfile << "  CC-Other(osc.): " << SelectedCCnonQETagN[i] << std::endl;
      resultfile << "  NC      (osc.): " << SelectedNCTagN[i]      << std::endl;
      resultfile << "  ------------------------------------------"      << std::endl;
      resultfile << "  Total   (osc.): " << SelectedCCQETagN[i]+SelectedCC2p2hTagN[i]+SelectedCCnonQETagN[i]+SelectedNCTagN[i] << std::endl;
      resultfile << " " << std::endl;
      resultfile << "  CCQE    (No osc.): " << SelectedNoOscCCQETagN[i]    << std::endl;
      resultfile << "  CC-2p2h (No osc.): " << SelectedNoOscCC2p2hTagN[i]  << std::endl;
      resultfile << "  CC-Other(No osc.): " << SelectedNoOscCCnonQETagN[i] << std::endl;
      resultfile << "  NC      (No osc.): " << SelectedNoOscNCTagN[i]      << std::endl;
      resultfile << "  ------------------------------------------"      << std::endl;
      resultfile << "  Total   (No osc.): " << SelectedNoOscCCQETagN[i]+SelectedNoOscCC2p2hTagN[i]+SelectedNoOscCCnonQETagN[i]+SelectedNoOscNCTagN[i] << std::endl;
    }
 
    resultfile << "--- Box cut performance ---" << std::endl;
    resultfile << " 0 < dt[usec] < " << dtMax << ", " << N50Min << " < N50 < " << N50Max << std::endl;
    resultfile << " All truth decay-e                : " << AllTrueDcye   << std::endl;
    resultfile << " All fiTQun decay-e               : " << AllfQdcye     << std::endl;
    resultfile << " fiTQun decya-e in the box        : " << BoxfQdcye     << std::endl;
    resultfile << " Matched fiTQun decya-e (legacy)  : " << MatchedfQdcye << std::endl;
    resultfile << " Matched fiTQun decya-e in the box: " << MatchedBoxfQdcye << std::endl;
    resultfile << " Q1 : " << SelectedMatchTrueDcye << std::endl;
    resultfile << " Q2 : " << SelectedfQdcye << std::endl;
    resultfile << " Q3 : " << RejectedMatchedTrueDcye << std::endl;
    resultfile << " efficiency Q1/(Q1+Q3): " << SelectedMatchTrueDcye /( SelectedMatchTrueDcye + RejectedMatchedTrueDcye )*100.  << " %" << std::endl;
    resultfile << " purity     Q1/(Q1+Q2): " << SelectedMatchTrueDcye /( SelectedMatchTrueDcye + SelectedfQdcye)*100. << " %" << std::endl;

    /*resultfile << "[Decay-e Cut Scan] " << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 20 us: " << SelectedParentNeutrinos_dtScan[0]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[0] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 15 us: " << SelectedParentNeutrinos_dtScan[1]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[1] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 10 us: " << SelectedParentNeutrinos_dtScan[2]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[2] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt =  5 us: " << SelectedParentNeutrinos_dtScan[3]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[3] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt =  3 us: " << SelectedParentNeutrinos_dtScan[4]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[4] << std::endl;*/

    resultfile << "[Neutrino] All Parent Neutrino Events          : " << AllParentNeutrinos << std::endl;
    resultfile << "[Neutrino] Generated Neutrino Events(wallv>200): " << GeneratedEvents    << std::endl;
    resultfile << "[Neutrino] Generated 1Rmu Events (Oscillated)  : " << OscillatedAll      << std::endl;
    resultfile << " " << std::endl;


    resultfile << "[Neutron] # generated neutrons before FSI: " << GenPreFSIN << std::endl;
    resultfile << "[Neutron] # generated neutrons before SI : " << GenPostFSIN << std::endl;
    resultfile << "[Neutron]   (primary interaction): " << GenN_prm << std::endl;
    resultfile << "[Neutron]   (nucleon FSI)        : " << GenN_nucFSI << std::endl;
    resultfile << "[Neutron]   (pion FSI)           : " << GenN_piFSI << std::endl;
    resultfile << "[Neutron]   (de-excitation)      : " << GenN_deex << std::endl;

    resultfile << "[Neutron] # captured neutrons before FSI  : " << CapPostFSIN << std::endl;
    resultfile << "[Neutron]   (primary interaction): " << CapN_prm << std::endl;
    resultfile << "[Neutron]   (nucleon FSI)        : " << CapN_nucFSI << std::endl;
    resultfile << "[Neutron]   (pion FSI)           : " << CapN_piFSI << std::endl;
    resultfile << "[Neutron]   (de-excitation)      : " << CapN_deex << std::endl;

    resultfile << "[Neutron] # captured neutrons from SI    : " << CapSIN << std::endl;
    resultfile << "[Neutron] # captured neutrons from mu    : " << CapMuN << std::endl;
    resultfile << "[Neutron] -------------------------------------------" << std::endl;
    resultfile << "[Neutron] Total                          : " << CapPostFSIN+CapSIN+CapMuN << std::endl;
    resultfile << "[Neutron] # all true neutrons            : " << TrueN << std::endl;
    resultfile << " " << std::endl;

    float TotalEventsNoNeutronAnalysis = OscillatedCCQE 
                                       + OscillatedCCnonQE 
                                       + OscillatedCCRESp
                                       + OscillatedCCRESpp
                                       + OscillatedCCRES0
                                       + OscillatedCCOther
                                       + OscillatedNC;
    float TotalEventswTrueN = OscillatedCCQE_wTrueN
                            + OscillatedCCnonQE_wTrueN
                            + OscillatedCCRESp_wTrueN
                            + OscillatedCCRESpp_wTrueN
                            + OscillatedCCRES0_wTrueN
                            + OscillatedCCOther_wTrueN
                            + OscillatedNC_wTrueN;
    float TotalEventswoTrueN = OscillatedCCQE_woTrueN
                            + OscillatedCCnonQE_woTrueN
                            + OscillatedCCRESp_woTrueN
                            + OscillatedCCRESpp_woTrueN
                            + OscillatedCCRES0_woTrueN
                            + OscillatedCCOther_woTrueN
                            + OscillatedNC_woTrueN;
    float TotalEventswTagN = OscillatedCCQE_wTagN
                           + OscillatedCCnonQE_wTagN
                           + OscillatedCCRESp_wTagN
                           + OscillatedCCRESpp_wTagN
                           + OscillatedCCRES0_wTagN
                           + OscillatedCCOther_wTagN
                           + OscillatedNC_wTagN;
    float TotalEventswoTagN = OscillatedCCQE_woTagN
                            + OscillatedCCnonQE_woTagN
                            + OscillatedCCRESp_woTagN
                            + OscillatedCCRESpp_woTagN
                            + OscillatedCCRES0_woTagN
                            + OscillatedCCOther_woTagN
                            + OscillatedNC_woTagN;
    resultfile << "[Neutrino] Oscillated CCQE Events     : " << OscillatedCCQE << "(" << (OscillatedCCQE/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCQE_wTrueN << " (" << (OscillatedCCQE_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCQE_woTrueN << " (" << (OscillatedCCQE_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCQE_wTagN << "(" << (OscillatedCCQE_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCQE_woTagN << "(" << (OscillatedCCQE_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CC(2p2h) Events : " << OscillatedCCnonQE << "(" << (OscillatedCCnonQE/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCnonQE_wTrueN << " (" << (OscillatedCCnonQE_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCnonQE_woTrueN << " (" << (OscillatedCCnonQE_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCnonQE_wTagN << "(" << (OscillatedCCnonQE_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCnonQE_woTagN << "(" << (OscillatedCCnonQE_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    /*
    resultfile << "[Neutrino] Oscillated CCRES0 Events   : " << OscillatedCCRES0 << "(" << (OscillatedCCRES0/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCRES0_wTrueN << " (" << (OscillatedCCRES0_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCRES0_woTrueN << " (" << (OscillatedCCRES0_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCRES0_wTagN << "(" << (OscillatedCCRES0_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCRES0_woTagN << "(" << (OscillatedCCRES0_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CCRES+ Events   : " << OscillatedCCRESp << "(" << (OscillatedCCRESp/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCRESp_wTrueN << " (" << (OscillatedCCRESp_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCRESp_woTrueN << " (" << (OscillatedCCRESp_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCRESp_wTagN << "(" << (OscillatedCCRESp_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCRESp_woTagN << "(" << (OscillatedCCRESp_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CCRES++ Events  : " << OscillatedCCRESpp << "(" << (OscillatedCCRESpp/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCRESpp_wTrueN << " (" << (OscillatedCCRESpp_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCRESpp_woTrueN << " (" << (OscillatedCCRESpp_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCRESpp_wTagN << "(" << (OscillatedCCRESpp_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCRESpp_woTagN << "(" << (OscillatedCCRESpp_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;
    */

    resultfile << "[Neutrino] Oscillated All CCRES Events: " << OscillatedCCRES0 + OscillatedCCRESp + OscillatedCCRESpp << "(" << ((OscillatedCCRES0 + OscillatedCCRESp + OscillatedCCRESpp)/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCRES0_wTrueN + OscillatedCCRESp_wTrueN + OscillatedCCRESpp_wTrueN << " (" << ((OscillatedCCRES0_wTrueN + OscillatedCCRESp_wTrueN + OscillatedCCRESpp_wTrueN)/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCRES0_woTrueN + OscillatedCCRESp_woTrueN + OscillatedCCRESpp_woTrueN << " (" << ((OscillatedCCRES0_woTrueN + OscillatedCCRESp_woTrueN + OscillatedCCRESpp_woTrueN)/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCRES0_wTagN  + OscillatedCCRESp_wTagN  + OscillatedCCRESpp_wTagN << "(" << ((OscillatedCCRES0_wTagN  + OscillatedCCRESp_wTagN  + OscillatedCCRESpp_wTagN)/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCRES0_woTagN  + OscillatedCCRESp_woTagN  + OscillatedCCRESpp_woTagN << "(" << ((OscillatedCCRES0_woTagN  + OscillatedCCRESp_woTagN  + OscillatedCCRESpp_woTagN)/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CC Other Events : " << OscillatedCCOther << "(" << (OscillatedCCOther/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedCCOther_wTrueN << " (" << (OscillatedCCOther_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedCCOther_woTrueN << " (" << (OscillatedCCOther_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCOther_wTagN << "(" << (OscillatedCCOther_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCOther_woTagN << "(" << (OscillatedCCOther_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated NC Events       : " << OscillatedNC << "(" << (OscillatedNC/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ truth neutrons : " << OscillatedNC_wTrueN << " (" << (OscillatedNC_wTrueN/TotalEventswTrueN)*100 
               << " %), w/o truth neutrons :" << OscillatedNC_woTrueN << " (" << (OscillatedNC_woTrueN/TotalEventswoTrueN)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedNC_wTagN << "(" << (OscillatedNC_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedNC_woTagN << "(" << (OscillatedNC_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;


    resultfile << "[Neutrino] Oscillated Neutrino Events within [0.25 GeV, 1.5 GeV]" << std::endl;
    resultfile << "           Legacy Analysis    : " << OscLegacy   << "(Osc)/" << NoOscLegacy   << "(No Osc) = " << OscLegacy/NoOscLegacy     << std::endl;
    resultfile << "           Only CCQE(1p1h)    : " << OscOnlyCCQE << "(Osc)/" << NoOscOnlyCCQE << "(No Osc) = " << OscOnlyCCQE/NoOscOnlyCCQE << std::endl;
    resultfile << "           w/o truth neutrons : " << OscwoTrueN  << "(Osc)/" << NoOscwoTrueN  << "(No Osc) = " << OscwoTrueN/NoOscwoTrueN   << std::endl;
    resultfile << "           w/o tagged neutrons: " << OscwoTagN   << "(Osc)/" << NoOscwoTagN   << "(No Osc) = " << OscwoTagN/NoOscwoTagN     << std::endl;
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