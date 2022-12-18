#include <iostream>
#include <unistd.h>
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

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"
#include "src/NNInputVariables/inc/NNInputVariables.h"

#define NLIKETHRESHOLD 0.75


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
  tchtaggable->SetBranchAddress("Type", &Type, &bType);
  tchtaggable->SetBranchAddress("E", &E, &bE);
  tchtaggable->SetBranchAddress("t", &t, &bt);
  //=========  TTree partilce variables  ============
  std::vector<int> *PID = 0;
  TBranch *bPID = 0;
  std::vector<int> *ParentPID = 0;
  TBranch *bParentPID = 0;
  //std::vector<int> *ParentIndex = 0; //avalable at NTag1.1.2
  //TBranch *bParentIndex = 0;         //avalable at NTag1.1.2
  std::vector<int> *IntID = 0;
  TBranch *bIntID = 0;
  std::vector<float> *par_t = 0;
  TBranch *bpar_t = 0;
  std::vector<float> *par_x = 0;
  TBranch *bpar_x = 0;
  std::vector<float> *par_y = 0;
  TBranch *bpar_y = 0;
  std::vector<float> *par_z = 0;
  TBranch *bpar_z = 0;
  tchpar->SetBranchAddress("PID", &PID, &bPID);
  tchpar->SetBranchAddress("ParentPID", &ParentPID, &bParentPID);
  //tchpar->SetBranchAddress("ParentIndex", &ParentIndex, &bParentIndex); //avalable at NTag1.1.2
  tchpar->SetBranchAddress("IntID", &IntID, &bIntID);
  //tchpar->SetBranchAddress("t", par_t);
  tchpar->SetBranchAddress("t", &par_t, &bpar_t);
  tchpar->SetBranchAddress("x", &par_x, &bpar_x);
  tchpar->SetBranchAddress("y", &par_y, &bpar_y);
  tchpar->SetBranchAddress("z", &par_z, &bpar_z);
  //=========  TTree ntag variables  ============
  std::vector<float> *Label = 0;
  TBranch *bLabel = 0;
  std::vector<float> *TagClass = 0;
  TBranch *bTagClass = 0;
  std::vector<float> *FitT = 0;
  TBranch *bFitT = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *NHits = 0;
  TBranch *bNHits = 0;
  std::vector<float> *N200 = 0;
  TBranch *bN200 = 0;
  std::vector<float> *TRMS = 0;
  TBranch *bTRMS = 0;
  std::vector<float> *DWall = 0;
  TBranch *bDWall = 0;
  std::vector<float> *DWallMeanDir = 0;
  TBranch *bDWallMeanDir = 0;
  std::vector<float> *OpeningAngleMean = 0;
  TBranch *bOpeningAngleMean = 0;
  std::vector<float> *OpeningAngleSkew = 0;
  TBranch *bOpeningAngleSkew = 0;
  std::vector<float> *OpeningAngleStdev = 0;
  TBranch *bOpeningAngleStdev = 0;
  std::vector<float> *MeanDirAngleMean = 0;
  TBranch *bMeanDirAngleMean = 0;
  std::vector<float> *MeanDirAngleRMS = 0;
  TBranch *bMeanDirAngleRMS = 0;
  std::vector<float> *Beta1 = 0;
  TBranch *bBeta1 = 0;
  std::vector<float> *Beta5 = 0;
  TBranch *bBeta5 = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N200", &N200, &bN200);
  tchntag->SetBranchAddress("TRMS", &TRMS, &bTRMS);
  tchntag->SetBranchAddress("DWall", &DWall, &bDWall);
  tchntag->SetBranchAddress("DWallMeanDir", &DWallMeanDir, &bDWallMeanDir);
  tchntag->SetBranchAddress("OpeningAngleMean", &OpeningAngleMean, &bOpeningAngleMean);
  tchntag->SetBranchAddress("OpeningAngleSkew", &OpeningAngleSkew, &bOpeningAngleSkew);
  tchntag->SetBranchAddress("OpeningAngleStdev", &OpeningAngleStdev, &bOpeningAngleStdev);
  tchntag->SetBranchAddress("MeanDirAngleMean", &MeanDirAngleMean, &bMeanDirAngleMean);
  tchntag->SetBranchAddress("MeanDirAngleRMS", &MeanDirAngleRMS, &bMeanDirAngleRMS);
  tchntag->SetBranchAddress("Beta1", &Beta1, &bBeta1);
  tchntag->SetBranchAddress("Beta5", &Beta5, &bBeta5);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu ======
  Float_t posv[3];          //Primary vertex
  Int_t   npar;
  Int_t   npar2;            //Number of secondary vertex
  Float_t posv2[100][3];    //Secondary vertex
  Int_t   ipv[100];         //GEANT code of primary particle
  UInt_t   ipv2[100];       //GEANT code of secondary particle
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
  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("posv", posv);
  tchfQ -> SetBranchAddress("npar", &npar);
  tchfQ -> SetBranchAddress("npar2", &npar2);
  tchfQ -> SetBranchAddress("posv2", posv2);
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
  tchfQ -> SetBranchAddress("pscnd", pscnd);

  ResetNeutrinoEvents();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  DistanceViewer ndistance;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();



  //Process
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);

  for (int ientry=0; ientry<ntagEntries; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "[### analysis1Rmu ###]  Progress: " << 100.*ientry/ntagEntries << "%" << std::endl;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchpar      -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bPID        -> GetEntry(tentry);
    bParentPID  -> GetEntry(tentry);
    //bParentIndex -> GetEntry(tentry);  //avalable at NTag1.1.2
    bIntID      -> GetEntry(tentry);
    bpar_t      -> GetEntry(tentry);
    bpar_x      -> GetEntry(tentry);
    bpar_y      -> GetEntry(tentry);
    bpar_z      -> GetEntry(tentry);
    bType       -> GetEntry(tentry);
    bE          -> GetEntry(tentry);
    bLabel      -> GetEntry(tentry);
    bTagClass   -> GetEntry(tentry);
    bFitT       -> GetEntry(tentry);
    bNHits             -> GetEntry(tentry);
    bN200              -> GetEntry(tentry);
    bTRMS              -> GetEntry(tentry);
    bDWall             -> GetEntry(tentry);
    bDWallMeanDir      -> GetEntry(tentry);
    bOpeningAngleMean  -> GetEntry(tentry);
    bOpeningAngleSkew  -> GetEntry(tentry);
    bOpeningAngleStdev -> GetEntry(tentry);
    bMeanDirAngleMean  -> GetEntry(tentry);
    bMeanDirAngleRMS   -> GetEntry(tentry);
    bBeta1             -> GetEntry(tentry);
    bBeta5             -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();


    //Number of selected neutrino events
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    //New 1R muon selection
    //if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
    if (evsel.pass[0]==true &&
        evsel.pass[1]==true &&
        evsel.pass[2]==true &&
        evsel.pass[3]==true) 
    {
      GetSelectedModeEvents(numu);

      int mode = TMath::Abs(numu->var<int>("mode"));
      //std::cout << "[### " << ientry << " ###] Neutrino interaction: " << mode << std::endl;

      // primary particles
      //std::cout << "------  VECT primary info  ------" << std::endl;
      //std::cout << "[### " << ientry << " ###] # of particles=" << npar << std::endl;
      //std::cout << "[### " << ientry << " ###] vecvx=[" << vecvx << ", " << vecvy << ", " << vecvz << "]" << std::endl;
      //std::cout << "[### " << ientry << " ###] posv=[" << posv[0] << ", " << posv[1] << ", " << posv[2] << "]" << std::endl;      

      // primary particles
      //std::cout << "------  NEUT primary info  ------" << std::endl;
      //std::cout << "[### " << ientry << " ###] # of particles=" << Npvc << std::endl;
      //for (int iprm=0; iprm<Npvc; iprm++) {
        //std::cout << "[### " << ientry << " ###] Particle[" << iprm << "]=" << Ipvc[iprm]
        //                                 << ", Iflvc=" << Iflvc[iprm] 
        //                                 << ", Ichvc=" << Ichvc[iprm]
        //                                 << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
      //}

      // secondary particles
      /*std::cout << "------  VECT secondary info  ------" << std::endl;
      std::cout << "[### " << ientry << " ###] # of particles=" << npar2 << std::endl;
      int decaye_VECT2 = 0;
      for (int iscnd=0; iscnd<npar2; iscnd++) {
        std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << ipv2[iscnd] << "(GEANT), posv2=[" << posv2[iscnd][0] << ", " << posv2[iscnd][1] << ", " << posv2[iscnd][2] << "]" << std::endl;
        if (ipv2[iscnd]==static_cast<int>(GEANTPID::ELECTRON)) decaye_VECT2++;
      }*/

      // secondary particles
      int e_thisev = 0;          // # of decay-e in this event
      int e_aftercut_thisev = 0; // # of decay-e(after cut) in this event
      //int decaye_CONVVECT = 0;
      //int mucap_thisev = 0;      // # of mu- captures in this event
      std::cout << "------  CONVVECT secondary info  ------" << std::endl;
      std::cout << "[### " << ientry << " ###] # of particles=" << nscndprt << std::endl;
      for (int iscnd=0; iscnd<nscndprt; iscnd++) {
        std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << iprtscnd[iscnd]
                                         << ", iprntprt=" << iprntprt[iscnd]
                                         << ", iprntidx=" << iprntidx[iscnd] 
                                         << ", ichildidx=" << ichildidx[iscnd] 
                                         << ", lmecscnd=" << lmecscnd[iscnd] 
                                         << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " << vtxscnd[iscnd][1] << ", " << vtxscnd[iscnd][2] << "]" << std::endl;

        if (std::fabs(iprtscnd[iscnd])==static_cast<int>(PDGPID::ELECTRON) && 
            lmecscnd[iscnd]==static_cast<int>(GEANTINT::DECAY) &&
            std::fabs(iprntprt[iscnd])==static_cast<int>(PDGPID::MUON)) {
          //decaye_CONVVECT++;
          float d_x = vtxscnd[iscnd][0] - posv[0];
          float d_y = vtxscnd[iscnd][1] - posv[1];
          float d_z = vtxscnd[iscnd][2] - posv[2];
          float d   = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
          h1_truedistance_decaye -> Fill(d/100.);
        }

        
        //Find decay-e
        if (std::fabs(iprtscnd[iscnd])==11 && lmecscnd[iscnd]==5) {
          e_thisev++;

          //Take the distance between decay-e generated vertex and primary vertex
          //float d_x = vtxscnd[iscnd][0] - vecvx;
          //float d_y = vtxscnd[iscnd][1] - vecvy;
          //float d_z = vtxscnd[iscnd][2] - vecvz;
          //float d   = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );

          //if (d/100. >= 0.04) e_aftercut_thisev++;
        }
        
        //Find neutrons from mu- captures
        //if (iprtscnd[iscnd]==2112 && iprntprt[iscnd]==13 && lmecscnd[iscnd]==5) mucap_thisev++;
      }
      //if (decaye_VECT2!=decaye_CONVVECT) std::cout << "[### " << ientry << "###] decaye_VECT2=" << decaye_VECT2 << ", decaye_CONVVECT=" << decaye_CONVVECT << std::endl;
      std::cout << " " << std::endl;

      // Fill the # of decay-e in this event
      //std::cout << "Number of decay-e: " << e_thisev << std::endl;
#if 0
      //CCQE(1p1h)
      if (mode==1) h1_TrueDecaye[0] -> Fill(e_thisev);
      //CC 2p2h
      if (mode>=2 && mode<=10) h1_TrueDecaye[1] -> Fill(e_thisev);
      //NC
      if (mode>=31) h1_TrueDecaye[2] -> Fill(e_thisev);
      //CC RES (Delta+)
      if (mode>=13) h1_TrueDecaye[3] -> Fill(e_thisev);
      //CC RES (Delta++)
      if (mode>=11) h1_TrueDecaye[4] -> Fill(e_thisev);
      //CC RES (Delta0)
      if (mode>=12) h1_TrueDecaye[5] -> Fill(e_thisev);
      //CC other
      if (mode>=14 && mode<=30) h1_TrueDecaye[6] -> Fill(e_thisev);
#endif
#if 0
      //CCQE(1p1h)
      if (mode==1) h1_TrueDecaye[0] -> Fill(e_aftercut_thisev);
      //CC 2p2h
      if (mode>=2 && mode<=10) h1_TrueDecaye[1] -> Fill(e_aftercut_thisev);
      //NC
      if (mode>=31) h1_TrueDecaye[2] -> Fill(e_aftercut_thisev);
      //CC RES (Delta+)
      if (mode>=13) h1_TrueDecaye[3] -> Fill(e_aftercut_thisev);
      //CC RES (Delta++)
      if (mode>=11) h1_TrueDecaye[4] -> Fill(e_aftercut_thisev);
      //CC RES (Delta0)
      if (mode>=12) h1_TrueDecaye[5] -> Fill(e_aftercut_thisev);
      //CC other
      if (mode>=14 && mode<=30) h1_TrueDecaye[6] -> Fill(e_aftercut_thisev);
#endif


      //Check contributions of the event that the # of deca-e is one
      // secondary vertex of neutrons from mu- capture (mu- stopping point)
      //Float_t scndvtx_mucap[3];
      //bool fillonce_mucap = false; // fill at once

      // secondary vertex of mu+ (pi+ decay vertex)
      float scndvtx_pidecay[3];
      bool fillonce_pidecay = false;

      // secondary vertex of decay-e (mu decay vertex)
      float scndvtx_mudecay[3];
      bool fillonce_mudecay = false;

      for (int i=0; i<3; i++) {
        //scndvtx_mucap[i]   = 0.;
        scndvtx_pidecay[i] = 0.;
        scndvtx_mudecay[i] = 0.;
      }

      //if (e_thisev==1) {

        //secondary particles
        /*for (int iscnd=0; iscnd<nscndprt; iscnd++) {

          //If we found mu- captures...
          if (mucap_thisev!=0) {
            if (iprtscnd[iscnd]==2112 && iprntprt[iscnd]==13 && lmecscnd[iscnd]==5) {
              std::cout << "[### " << ientry << " ###] !!!!! Neutrons from mu- capture !!!!!!!" << std::endl;

              //Get the generated vertex of neutron (= mu- stopping point)
              if (!fillonce_mucap) {
                for (int idir=0; idir<3; idir++) scndvtx_mucap[idir] = vtxscnd[iscnd][idir];
                float d_x = scndvtx_mucap[0] - vecvx;
                float d_y = scndvtx_mucap[1] - vecvy;
                float d_z = scndvtx_mucap[2] - vecvz;
                float d = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
                h1_truedistance_mucap -> Fill(d/100.);
                fillonce_mucap = true;
              }
            }
          }

          //Find decay-e
          if (std::fabs(iprtscnd[iscnd])==11 && lmecscnd[iscnd]==5) {

            //Decay-e from mu+
            if (iprntprt[iscnd]==-13) {
              std::cout << "[### " << ientry << " ###] !!!!! Decay-e from mu+ !!!!!!!" << std::endl;
              std::cout << "                           Parent of mu+ is " << iprntprt[ iprntidx[iscnd]-1 ] << std::endl;

              //mu+ from pi+ decay
              if (iprntprt[ iprntidx[iscnd]-1 ]==211) {
                //for (int idir=0; idir<3; idir++) scndvtx_pidecay[idir] = vtxscnd[ iprntidx[iscnd]-1 ][idir];
                for (int idir=0; idir<3; idir++) scndvtx_pidecay[idir] = vtxscnd[iscnd][idir];
                float d_x = scndvtx_pidecay[0] - vecvx;
                float d_y = scndvtx_pidecay[1] - vecvy;
                float d_z = scndvtx_pidecay[2] - vecvz;
                float d = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
                h1_truedistance_pidecay -> Fill(d/100.);
                fillonce_pidecay = true;
              }
              else {
                for (int idir=0; idir<3; idir++) scndvtx_mudecay[idir] = vtxscnd[iscnd][idir];
                float d_x = scndvtx_mudecay[0] - vecvx;
                float d_y = scndvtx_mudecay[1] - vecvy;
                float d_z = scndvtx_mudecay[2] - vecvz;
                float d = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
                h1_truedistance_mudecay -> Fill(d/100.);
                fillonce_mudecay = true;
              }
            }
            //Decay-e from mu-
            if (iprntprt[iscnd]==13) {
              std::cout << "[### " << ientry << " ###] !!!!! Decay-e from mu- !!!!!!!" << std::endl;
              for (int idir=0; idir<3; idir++) scndvtx_mudecay[idir] = vtxscnd[iscnd][idir];
              float d_x = scndvtx_mudecay[0] - vecvx;
              float d_y = scndvtx_mudecay[1] - vecvy;
              float d_z = scndvtx_mudecay[2] - vecvz;
              float d = std::sqrt( d_x*d_x + d_y*d_y + d_z*d_z );
              h1_truedistance_mudecay -> Fill(d/100.);
              fillonce_mudecay = true;
            }

          }
        }*/
      //}


    } //1R mu selection

  } //Event loop


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

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

  ndistance.cdDistanceViewer(fout);
  ndistance.WritePlots();
  gDirectory -> cd("..");

}