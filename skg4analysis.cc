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
//#include "DefOscChannels.h"

#include "include/NeutrinoEvents.h"
//#include "include/NTagVariables.h"
#include "include/Const.h"
#include "include/CLTOption.h"
#include "include/ResultSummary.h"
#include "include/VECTChannelChecker.h"
#include "include/CommonTool.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"


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

  float dtMax  = 10.;
  float N50Min = 50.;
  float N50Max = 400.;
  float nlikeThreshold = 0.7;


  //=========  fiTQun output (TTree: h1)  ============
  TChain *tchfQ = new TChain("h1");
  int nfQFiles = tchfQ->Add( fiTQunFileName );
  if ( nfQFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree h1 from: " << fiTQunFileName << "\e[0m" << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: event)  ============
  TChain *tchev = new TChain("event");
  int nevFiles = tchev->Add( NtagFileName );
  if ( nevFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree event from: " << NtagFileName << "\e[0m" << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: particle)  ============
  TChain *tchpar = new TChain("particle");
  int nparFiles = tchpar->Add( NtagFileName );
  if ( nparFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree particle from: " << NtagFileName << "\e[0m" << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Delayed info (TTree: taggable)  ============
  TChain *tchtaggable = new TChain("taggable");
  int ntaggableFiles = tchtaggable->Add( NtagFileName );
  if ( ntaggableFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree taggable from: " << NtagFileName << "\e[0m" << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if ( ntagFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree ntag from: " << NtagFileName << "\e[0m" << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //Load succeed
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nfQFiles       << " files from: " << fiTQunFileName << "\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nevFiles       << " files from: " << NtagFileName   << "\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nparFiles      << " files from: " << NtagFileName   << "\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << ntaggableFiles << " files from: " << NtagFileName   << "\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: " << NtagFileName   << "\e[0m" << std::endl;


  const int nfQEntries       = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries       = tchev->GetEntries();       //total entries of TTree event
  const int nparEntries      = tchpar->GetEntries();       //total entries of TTree particle
  const int ntaggableEntries = tchtaggable->GetEntries(); //total entries of TTree taggable
  const int ntagEntries      = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Particle info     : Processing " << nparEntries      <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Delayed info      : Processing " << ntaggableEntries <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries...\e[0m" << std::endl;


  //=========  TTree event variables  ============
  //float NTrueN = 0.;   // for old NTag
  int   NTrueN = 0.;      // for Ntag v1.1.3
  float vecvx  = 0.;
  float vecvy  = 0.;
  float vecvz  = 0.;
  float pvx    = 0.;
  float pvy    = 0.;
  float pvz    = 0.;
  tchev->SetBranchAddress("NTrueN", &NTrueN);
  tchev->SetBranchAddress("vecvx", &vecvx);
  tchev->SetBranchAddress("vecvy", &vecvy);
  tchev->SetBranchAddress("vecvz", &vecvz);
  tchev->SetBranchAddress("pvx", &pvx);
  tchev->SetBranchAddress("pvy", &pvy);
  tchev->SetBranchAddress("pvz", &pvz);
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
  std::vector<float> *N50 = 0;
  TBranch *bN50 = 0;
  std::vector<float> *TagIndex = 0;
  TBranch *bTagIndex = 0;
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  std::vector<float> *fvx = 0;
  std::vector<float> *fvy = 0;
  std::vector<float> *fvz = 0;
  TBranch *bfvx = 0;
  TBranch *bfvy = 0;
  TBranch *bfvz = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("DWall", &TagDWall, &bTagDWall);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N50", &N50, &bN50);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);
  tchntag->SetBranchAddress("fvx", &fvx, &bfvx);
  tchntag->SetBranchAddress("fvy", &fvy, &bfvy);
  tchntag->SetBranchAddress("fvz", &fvz, &bfvz);

  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("pscnd", pscnd);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu? ======
  Int_t   nmue;
  Float_t Pvc[100][3];      //Momentum of primary particles
  //Int_t   Npvc;             //Number of primary particles
  Int_t   Ipvc[100];        //PID of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Ichvc[100];       //Chase at detector simulation or not(1: chase/0: not chase)
  Int_t   Iorgvc[100];      //Index of parent particle (0: initial particles, n: n-th final particle at the primary interaction)
  //Int_t   nscndprt;         //Number of secondary particles
  Int_t   iprtscnd[1000];   //PID of the secondary particle
  Float_t tscnd[1000];
  Float_t vtxscnd[1000][3]; //Generated vertex of secondary particles
  Int_t   iprntprt[1000];   //PID of the parent of this secondary particle
  Float_t vtxprnt[1000][3];
  Int_t   iprntidx[1000];   //Index of the parent particle (0: no parent(connected from primary particles), n: the parent of n-th secondary particle)
  Int_t   ichildidx[1000];  //Index of the first child particle (0: no childs, n: the first child of n-th secondary particle)
  Int_t   lmecscnd[1000];   //Interaction code of secondary particles based on GEANT
  Int_t   itrkscnd[1000];
  Float_t pprntinit[1000][3]; //Initial momentum of the parent particle at birth
  //tchfQ -> SetBranchAddress("Npvc", &Npvc);  //off if you use numu->Npvc
  tchfQ -> SetBranchAddress("nmue", &nmue);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  //tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  //tchfQ -> SetBranchAddress("Ichvc", Ichvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  //tchfQ -> SetBranchAddress("nscndprt", &nscndprt);
  //tchfQ -> SetBranchAddress("iprtscnd", iprtscnd);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  //tchfQ -> SetBranchAddress("vtxscnd", vtxscnd);
  //tchfQ -> SetBranchAddress("iprntprt", iprntprt);
  tchfQ -> SetBranchAddress("vtxprnt", vtxprnt);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
  //tchfQ -> SetBranchAddress("lmecscnd", lmecscnd);
  tchfQ -> SetBranchAddress("itrkscnd", itrkscnd);
  tchfQ -> SetBranchAddress("pprntinit", pprntinit);

  ResetNeutrinoEvents();
  InitNTagVariables();

  SetVECTHisto();

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
  DistanceMax = 3.;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();

  NTagAnalysis ntagana;
  ntagana.InitNeutrons();
  ntagana.SetHistoFrame();
  ntagana.SetHistoFormat();

  int NoPrmMuEnd_CCQE = 0;
  int NoPrmMuEnd_CCnonQE = 0;
  int NoPrmMuEnd_NC = 0;
  const int DCYENUM = 1;

  float BefFSIn = 0;
  float BefSIn = 0;
  float SIn = 0;
  float MuN = 0;
  float TrueN = 0;


  //Process
  if (MCTypeKeyword=="-MCType") {
    if (MCType=="Gd" || MCType=="gd") processmax = ntagEntries;
    else if (MCType=="Water" || MCType=="water") processmax = nfQEntries;
    else {
      std::cout << " " << std::endl;
      std::cout << "\e[38;5;A0m\e[1m[!!!CLT error!!!] MC type can not be found. --- input Gd or Water\e[0m" << std::endl;
      exit(-1); 
    }
  }
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);

  for (int ientry=0; ientry<processmax; ientry++) {

  	//Progress meter
    if(ientry>100 && ientry%100==0) std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Progress: " << 100.*ientry/processmax << "%\e[0m" << std::endl;

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
    bN50        -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);
    bfvx        -> GetEntry(tentry);
    bfvy        -> GetEntry(tentry);
    bfvz        -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false);

    GetSelectedModeEvents(numu);

    if (numu->var<float>("wallv")>200) GeneratedEvents++;

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false)) {

      int intmode   = TMath::Abs(numu->var<int>("mode"));
      float TrueEnu = numu->var<float>("pnu", 0);

      float PrmVtx[3] = {0., 0., 0.};  //Primary vertex
      PrmVtx[0] = numu->var<float>("posv", 0);
      PrmVtx[1] = numu->var<float>("posv", 1);
      PrmVtx[2] = numu->var<float>("posv", 2);


      float RecoPrmVtx_DETSIM[3] = {0., 0., 0.};  // SKDETSIM-based fiTQun vertex
      RecoPrmVtx_DETSIM[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
      RecoPrmVtx_DETSIM[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
      RecoPrmVtx_DETSIM[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);

      float PrmVtxResoX_DETSIM = RecoPrmVtx_DETSIM[0] - PrmVtx[0];
      float PrmVtxResoY_DETSIM = RecoPrmVtx_DETSIM[1] - PrmVtx[1];
      float PrmVtxResoZ_DETSIM = RecoPrmVtx_DETSIM[2] - PrmVtx[2];
      float PrmVtxReso_DETSIM  = std::sqrt( PrmVtxResoX_DETSIM*PrmVtxResoX_DETSIM +
                                            PrmVtxResoY_DETSIM*PrmVtxResoY_DETSIM +
                                            PrmVtxResoZ_DETSIM*PrmVtxResoZ_DETSIM );
      float PrmVtxDist_DETSIM  = std::sqrt( RecoPrmVtx_DETSIM[0]*RecoPrmVtx_DETSIM[0] +
                                            RecoPrmVtx_DETSIM[1]*RecoPrmVtx_DETSIM[1] +
                                            RecoPrmVtx_DETSIM[2]*RecoPrmVtx_DETSIM[2] );

      h1_PrmVtxReso_DETSIM -> Fill(PrmVtxReso_DETSIM);


      float RecoPrmVtx_G4[3] = {0., 0., 0.};  // SKG4-based fiTQun vertex
      RecoPrmVtx_G4[0] = pvx;
      RecoPrmVtx_G4[1] = pvy;
      RecoPrmVtx_G4[2] = pvz;

      float PrmVtxResoX_G4 = RecoPrmVtx_G4[0] - PrmVtx[0];
      float PrmVtxResoY_G4 = RecoPrmVtx_G4[1] - PrmVtx[1];
      float PrmVtxResoZ_G4 = RecoPrmVtx_G4[2] - PrmVtx[2];
      float PrmVtxReso_G4  = std::sqrt( PrmVtxResoX_G4*PrmVtxResoX_G4 +
                                        PrmVtxResoY_G4*PrmVtxResoY_G4 +
                                        PrmVtxResoZ_G4*PrmVtxResoZ_G4 );
      float PrmVtxDist_G4  = std::sqrt( RecoPrmVtx_G4[0]*RecoPrmVtx_G4[0] +
                                        RecoPrmVtx_G4[1]*RecoPrmVtx_G4[1] +
                                        RecoPrmVtx_G4[2]*RecoPrmVtx_G4[2] );

      if (intmode==1)                h1_PrmVtxReso[0] -> Fill(PrmVtxReso_G4/100.);
      if (intmode>=2 && intmode<=10) h1_PrmVtxReso[1] -> Fill(PrmVtxReso_G4/100.);
      if (intmode>10 && intmode<=30) h1_PrmVtxReso[2] -> Fill(PrmVtxReso_G4/100.);
      if (intmode>=31)               h1_PrmVtxReso[3] -> Fill(PrmVtxReso_G4/100.);

      h1_PrmVtxReso_G4 -> Fill(PrmVtxReso_G4);

      h2_Enu_x_PrmVtxReso -> Fill(TrueEnu, PrmVtxReso_G4);
      //h2_Enu_x_PrmVtxReso -> Fill(TrueEnu, PrmVtxReso_DETSIM);


      //////  True vs Reco  //////
      float dTrue = std::sqrt( PrmVtx[0]*PrmVtx[0] + PrmVtx[1]*PrmVtx[1] + PrmVtx[2]*PrmVtx[2] );
      //h2_True_x_Reco -> Fill( dTrue/100., PrmVtxDist_DETSIM/100. );   //  SKDETSIM
      h2_True_x_Reco -> Fill( dTrue/100., PrmVtxDist_G4/100. );       //  SKG4

      float RTrue        = PrmVtx[0]*PrmVtx[0] + PrmVtx[1]*PrmVtx[1];
      float RReco_G4     = RecoPrmVtx_G4[0]*RecoPrmVtx_G4[0] +
                           RecoPrmVtx_G4[1]*RecoPrmVtx_G4[1];
      float RReco_DETSIM = RecoPrmVtx_DETSIM[0]*RecoPrmVtx_DETSIM[0] +
                           RecoPrmVtx_DETSIM[1]*RecoPrmVtx_DETSIM[1];
      //h2_TrueR_x_RecoR -> Fill( RTrue/10000., RReco_DETSIM/10000. );   //  SKDETSIM
      h2_TrueR_x_RecoR -> Fill( RTrue/10000., RReco_G4/10000. );       //  SKG4

      //h2_TrueZ_x_RecoZ -> Fill( PrmVtx[2]/100., RecoPrmVtx_DETSIM[2]/100. );   //  SKDETSIM
      h2_TrueZ_x_RecoZ -> Fill( PrmVtx[2]/100., RecoPrmVtx_G4[2]/100. );           //  SKG4


      /////  SKG4 vs SKDETSIM  /////
      h1_PrmVtxResoX -> Fill( RecoPrmVtx_DETSIM[0] - RecoPrmVtx_G4[0] );  // DETSIM - G4 X
      h1_PrmVtxResoY -> Fill( RecoPrmVtx_DETSIM[1] - RecoPrmVtx_G4[1] );  // DETSIM - G4 Y
      h1_PrmVtxResoZ -> Fill( RecoPrmVtx_DETSIM[2] - RecoPrmVtx_G4[2] );  // DETSIM - G4 Z
      h2_PrmVtxReso  -> Fill( PrmVtxDist_G4/100., PrmVtxDist_DETSIM/100. );

    }

  }


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

    resultfile << "[Neutrino] All Parent Neutrino Events          : " << AllParentNeutrinos << std::endl;
    resultfile << "[Neutrino] Generated Neutrino Events(wallv>200): " << GeneratedEvents    << std::endl;
    resultfile << "[Neutrino] Generated 1Rmu Events (Oscillated)  : " << OscillatedAll      << std::endl;
    resultfile << " " << std::endl;
  }


  TFile* fout = new TFile(OutputRootName, "RECREATE");
  std::cout << "Output: " << OutputRootName << std::endl;
  fout -> cd();

  neuosc.cdNeutrinoOscillation(fout);
  neuosc.WritePlots();
  gDirectory -> cd("..");

}
