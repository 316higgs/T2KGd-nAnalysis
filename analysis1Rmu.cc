#include <iostream>
#include <unistd.h>
#include "TChain.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TGaxis.h"
#include "TPaveStats.h"
#include "THStack.h"
#include "DefBeamMode.h"

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
#include "src/NNInputVariables/inc/NNInputVariables.h"


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

  float dtMax  = 20.;
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
  std::vector<float> *FitGoodness = 0;
  TBranch *bFitGoodness = 0;
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
  std::vector<float> *NResHits = 0;
  TBranch *bNResHits = 0;
  std::vector<float> *TRMS = 0;
  TBranch *bTRMS = 0;
  std::vector<float> *DWallMeanDir = 0;
  TBranch *bDWallMeanDir = 0;
  std::vector<float> *OpeningAngleStdev = 0;
  TBranch *bOpeningAngleStdev = 0;
  std::vector<float> *BurstRatio = 0;
  TBranch *bBurstRatio = 0;
  std::vector<float> *DarkLikelihood = 0;
  TBranch *bDarkLikelihood = 0;
  std::vector<float> *Beta1 = 0;
  TBranch *bBeta1 = 0;
  std::vector<float> *Beta2 = 0;
  TBranch *bBeta2 = 0;
  std::vector<float> *Beta3 = 0;
  TBranch *bBeta3 = 0;
  std::vector<float> *Beta4 = 0;
  TBranch *bBeta4 = 0;
  std::vector<float> *Beta5 = 0;
  TBranch *bBeta5 = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitGoodness", &FitGoodness, &bFitGoodness);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("DWall", &TagDWall, &bTagDWall);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N50", &N50, &bN50);
  tchntag->SetBranchAddress("NResHits", &NResHits, &bNResHits);
  tchntag->SetBranchAddress("TRMS", &TRMS, &bTRMS);
  tchntag->SetBranchAddress("DWallMeanDir", &DWallMeanDir, &bDWallMeanDir);
  tchntag->SetBranchAddress("OpeningAngleStdev", &OpeningAngleStdev, &bOpeningAngleStdev);
  tchntag->SetBranchAddress("BurstRatio", &BurstRatio, &bBurstRatio);
  tchntag->SetBranchAddress("DarkLikelihood", &DarkLikelihood, &bDarkLikelihood);
  tchntag->SetBranchAddress("Beta1", &Beta1, &bBeta1);
  tchntag->SetBranchAddress("Beta2", &Beta2, &bBeta2);
  tchntag->SetBranchAddress("Beta3", &Beta3, &bBeta3);
  tchntag->SetBranchAddress("Beta4", &Beta4, &bBeta4);
  tchntag->SetBranchAddress("Beta5", &Beta5, &bBeta5);
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
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Iorgvc[100];      //Index of parent particle (0: initial particles, n: n-th final particle at the primary interaction)
  Float_t tscnd[1000];
  Float_t vtxprnt[1000][3];
  Int_t   iprntidx[1000];   //Index of the parent particle (0: no parent(connected from primary particles), n: the parent of n-th secondary particle)
  Int_t   ichildidx[1000];  //Index of the first child particle (0: no childs, n: the first child of n-th secondary particle)
  Int_t   itrkscnd[1000];
  Float_t pprnt[1000][3];     //Initial momentum of the parent particle at interaction
  Float_t pprntinit[1000][3]; //Initial momentum of the parent particle at birth

  Int_t   npar2;
  UInt_t  ipv2[1000];
  UInt_t  iorg[1000];
  Float_t posv2[1000][3];
  Float_t pmomv2[1000][3];

  tchfQ -> SetBranchAddress("nmue", &nmue);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("vtxprnt", vtxprnt);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
  tchfQ -> SetBranchAddress("itrkscnd", itrkscnd);
  tchfQ -> SetBranchAddress("pprnt", pprnt);
  tchfQ -> SetBranchAddress("pprntinit", pprntinit);

  tchfQ -> SetBranchAddress("npar2", &npar2);
  tchfQ -> SetBranchAddress("ipv2", ipv2);
  tchfQ -> SetBranchAddress("iorg", iorg);
  tchfQ -> SetBranchAddress("posv2", posv2);
  tchfQ -> SetBranchAddress("pmomv2", pmomv2);

  


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

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  int NoPrmMuEnd_CCQE = 0;
  int NoPrmMuEnd_CCnonQE = 0;
  int NoPrmMuEnd_NC = 0;
  const int DCYENUM = 1;

  float GenPreFSIN  = 0.;
  float GenPostFSIN = 0.;

  float CapPostFSIN = 0.;
  float CapSIN      = 0.;
  float CapMuN      = 0.;
  float TrueN       = 0.;

  float nlikeAll = 0;
  float N1_acc  = 0;
  float N1_dcye = 0;
  float N1_H    = 0;
  float N1_Gd   = 0;
  float N2_acc  = 0;
  float N2_dcye = 0;
  float N2_H    = 0;
  float N2_Gd   = 0;
  float N3_acc  = 0;
  float N3_dcye = 0;
  float N3_H    = 0;
  float N3_Gd   = 0;
  float N4_acc  = 0;
  float N4_dcye = 0;
  float N4_H    = 0;
  float N4_Gd   = 0;

  float sel_C1 = 0;
  float sel_C2 = 0;
  float sel_C3 = 0;
  float sel_C4 = 0;
  float sel_C5 = 0;
  float sel_C6 = 0;

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
    bPID         -> GetEntry(tentry);
    bParentPID   -> GetEntry(tentry);
    bIntID       -> GetEntry(tentry);
    bType        -> GetEntry(tentry);
    bE           -> GetEntry(tentry);
    bDWall       -> GetEntry(tentry);
    btagvx       -> GetEntry(tentry);
    btagvy       -> GetEntry(tentry);
    btagvz       -> GetEntry(tentry);
    bDistFromPV  -> GetEntry(tentry);
    bLabel       -> GetEntry(tentry);
    bTagClass    -> GetEntry(tentry);
    bFitGoodness -> GetEntry(tentry);
    bFitT        -> GetEntry(tentry);
    bTagDWall    -> GetEntry(tentry);
    bNHits       -> GetEntry(tentry);
    bN50         -> GetEntry(tentry);
    bTagIndex    -> GetEntry(tentry);
    bNResHits          -> GetEntry(tentry);
    bTRMS              -> GetEntry(tentry);
    bDWallMeanDir      -> GetEntry(tentry);
    bOpeningAngleStdev -> GetEntry(tentry);
    bBurstRatio        -> GetEntry(tentry);
    bDarkLikelihood    -> GetEntry(tentry);
    bBeta1             -> GetEntry(tentry);
    bBeta2             -> GetEntry(tentry);
    bBeta3             -> GetEntry(tentry);
    bBeta4             -> GetEntry(tentry);
    bBeta5             -> GetEntry(tentry);
    bTagOut      -> GetEntry(tentry);
    bfvx         -> GetEntry(tentry);
    bfvy         -> GetEntry(tentry);
    bfvz         -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false);
    //Sequencial1RmuonSelection_Pion(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false);
    //if (numu->var<int>("fqnse")==3) 
      DecayeCutScan(prmsel, evsel, numu, decayebox, eMode, eOsc);
    if (prmsel.C1ApplyFCFV(evsel)     && 
        prmsel.C2Apply1R(evsel)       &&
        prmsel.C3Applymuonlike(evsel) &&
        prmsel.C4ApplyPmu200MeV(evsel)) 
    {

      //decayebox.GetDecayeTagPurity(numu, tscnd, pscnd, dtMax, N50Min, N50Max);
      floorcut = false;
      decayebox.DecayeMatching(numu, nmue, tscnd);

      //Reconstructed neutrino energy
      float Enu = numu->var<float>("erec");
      int   FQDcyE = numu->var<int>("fqnse") - 1;
      //if (FQDcyE==1) GetSelectedModeEvents(numu);
      //if (Enu/1000. < 1. && FQDcyE==1) GetSelectedModeEvents(numu);
    }

    int intmode   = TMath::Abs(numu->var<int>("mode"));
    float OscProb = numu->getOscWgt();

    GetSelectedModeEvents(numu);

    if (numu->var<float>("wallv")>200) GeneratedEvents++;


    //Proto 1R muon selection
    if (prmsel.ApplyProto1RmuonSelection(evsel)) GetProtoSelectedModeEvents(numu);


    if (prmsel.C1ApplyFCFV(evsel)) {

      ntagana.GetRecoNCapTime(numu, etagmode, FitT, NHits, Label, TagOut, nlikeThreshold);

      //ntagana.GetNlikeCandidates(numu, etagmode, NHits, FitT, TagOut, Label);

      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        //h1_AllRecoNCapTime -> Fill(FitT->at(jentry));

#if 0
        HistFillforLabel(numu, Label->at(jentry), N50->at(jentry), h1_N50_preNN);
        HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_preNN);
        HistFillforLabel(numu, Label->at(jentry), FitT->at(jentry), h1_FitT_preNN);
        h1_AllN50_preNN   -> Fill(N50->at(jentry));
        h1_AllNHits_preNN -> Fill(NHits->at(jentry));
        h1_AllFitT_preNN  -> Fill(FitT->at(jentry));
#endif

        h1_AllNTagOut -> Fill(TagOut->at(jentry));
        bool etagboxin = false;
        etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry));
        if (TagOut->at(jentry)>nlikeThreshold && !ntagana.RemnantChecker(Label->at(jentry))) {

          if (NHits->at(jentry)<N50Min) {
            if (FitT->at(jentry)<dtMax) {
              if (intmode<31) {
                if (Label->at(jentry)==0) N1_acc+=OscProb;
                if (Label->at(jentry)==1) N1_dcye+=OscProb;
                if (Label->at(jentry)==2) N1_H+=OscProb;
                if (Label->at(jentry)==3) N1_Gd+=OscProb;
              }
              else {
                if (Label->at(jentry)==0) N1_acc++;
                if (Label->at(jentry)==1) N1_dcye++;
                if (Label->at(jentry)==2) N1_H++;
                if (Label->at(jentry)==3) N1_Gd++;
              }
            }
            else {
              if (intmode<31) {
                if (Label->at(jentry)==0) N2_acc+=OscProb;
                if (Label->at(jentry)==1) N2_dcye+=OscProb;
                if (Label->at(jentry)==2) N2_H+=OscProb;
                if (Label->at(jentry)==3) N2_Gd+=OscProb;
              }
              else {
                if (Label->at(jentry)==0) N2_acc++;
                if (Label->at(jentry)==1) N2_dcye++;
                if (Label->at(jentry)==2) N2_H++;
                if (Label->at(jentry)==3) N2_Gd++;
              }
            }
          }
          else {
            if (FitT->at(jentry)<dtMax) {
              if (intmode<31) {
                if (Label->at(jentry)==0) N3_acc+=OscProb;
                if (Label->at(jentry)==1) N3_dcye+=OscProb;
                if (Label->at(jentry)==2) N3_H+=OscProb;
                if (Label->at(jentry)==3) N3_Gd+=OscProb;
              }
              else {
                if (Label->at(jentry)==0) N3_acc++;
                if (Label->at(jentry)==1) N3_dcye++;
                if (Label->at(jentry)==2) N3_H++;
                if (Label->at(jentry)==3) N3_Gd++;
              }
            }
            else {
              if (intmode<31) {
                if (Label->at(jentry)==0) N4_acc+=OscProb;
                if (Label->at(jentry)==1) N4_dcye+=OscProb;
                if (Label->at(jentry)==2) N4_H+=OscProb;
                if (Label->at(jentry)==3) N4_Gd+=OscProb;
              }
              else {
                if (Label->at(jentry)==0) N4_acc++;
                if (Label->at(jentry)==1) N4_dcye++;
                if (Label->at(jentry)==2) N4_H++;
                if (Label->at(jentry)==3) N4_Gd++;
              }
            }
          }

#if 0
          HistFillforLabel(numu, Label->at(jentry), N50->at(jentry), h1_N50_postNN);
          HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_postNN);
          HistFillforLabel(numu, Label->at(jentry), FitT->at(jentry), h1_FitT_postNN);
          h1_AllN50_postNN   -> Fill(N50->at(jentry));
          h1_AllNHits_postNN -> Fill(NHits->at(jentry));
          h1_AllFitT_postNN  -> Fill(FitT->at(jentry));
#endif

          bool etagboxin = false;
          etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry));
          if (!etagboxin) {
            HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_Nlike);
            HistFillforLabel(numu, Label->at(jentry), FitT->at(jentry), h1_FitT_Nlike);
            h1_AllNHits_Nlike -> Fill(NHits->at(jentry));
            h1_AllFitT_Nlike  -> Fill(FitT->at(jentry));
          }
          else {
            HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_Elike);
            HistFillforLabel(numu, Label->at(jentry), FitT->at(jentry), h1_FitT_Elike);
            h1_AllNHits_Elike -> Fill(NHits->at(jentry));
            h1_AllFitT_Elike  -> Fill(FitT->at(jentry));
          }


          if (intmode<31) nlikeAll+=OscProb;
          else nlikeAll++;
        }
      }
    }

    
    //int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, N50, FitT, Label, etagmode);
    int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
    GetSelectedTagN(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false, TagN);

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false)) {

      float Enu = numu->var<float>("erec");

      //Neutrino energy distribution
      neuosc.GetTrueEnu(numu);
      neuosc.GetRecoEnu(numu);
      neuosc.GetPrmVtxResolution(numu);
      neuosc.GetMuonPtResolution(numu);

      float PrmMuMom[3] = {0., 0., 0.}; //primary mu momentum
      bool PrmMu = decayebox.GetTruePrmMuMom(Pvc, numu, PrmMuMom);
      neuosc.GetPrmMuMomResolution(numu, PrmMuMom);

      neuosc.GetPrmVtx(numu);
      ntagana.TrueNCapVtxProfile(Type, tagvx, tagvy, tagvz);
      ntagana.GetTrueNCapTime(t, Type, E);

      //Count # of truth decay-e per event
      int NumDcyE = 0;
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
        if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
            numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) NumDcyE++;
      }
      decayebox.GetTruthDecaye(numu, NumDcyE);


      //Muon angle information
      //float truethetamu = neuosc.GetTrueMuDirection(numu, Npvc, Ipvc, Pvc, Iflvc, Ichvc);
      //float truethetamu = neuosc.GetTrueMuDirection(numu, numu->var<int>("Npvc"), Ipvc, Pvc, Iflvc, Ichvc);
      float truethetamu = neuosc.GetTrueMuDirection(numu, Pvc, Iflvc);
      float recothetamu = neuosc.GetRecoMuDirection(numu);
      neuosc.GetMuDirResolution(truethetamu, recothetamu);

      //neuosc.GetEnuResolution(numu);
      neuosc.GetEnuResolution(numu, recothetamu, thetamin, thetamax);
      neuosc.GetReso_x_TrueEnu(numu);

      //Oscillation probability check
      neuosc.OscProbCalculator(numu, true);

      //Neutrino events as a funtion of reconstructed neutrino energy (No NTag information)
      //neuosc.GetWgtNeutrino(numu, truethetamu, thetamin, thetamax);
      neuosc.GetWgtNeutrino(numu, recothetamu, thetamin, thetamax);

      neuosc.GetWgtNeutrino_wTrueN(numu, NTrueN, recothetamu, thetamin, thetamax);


      //  Generated neutrons
      float PrmVtx[3] = {0., 0., 0.};  //Primary vertex
      PrmVtx[0] = numu->var<float>("posv", 0);
      PrmVtx[1] = numu->var<float>("posv", 1);
      PrmVtx[2] = numu->var<float>("posv", 2);
      int TrueMuN = 0;
      float MuNCapVtx[3]   = {0., 0., 0.};  //neutron(from primary interaction) capture vertex

      //GetNeutrinoInteraction(ientry, intmode);
#if 0
      std::cout << "[     VECT     ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("npar"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetGEANTPIDName( numu->var<int>("ipv", iprm) )
                  << ", posv = [" << numu->var<float>("posv", 0) << ", " << numu->var<float>("posv", 1) << ", " << numu->var<float>("posv", 2)
                  << "] cm, pmomv = " << numu->var<float>("pmomv", iprm) << " MeV" 
                  << ", dirv = [" << numu->var<float>("dirv", iprm, 0) << ", " << numu->var<float>("dirv", iprm, 1) << ", " << numu->var<float>("dirv", iprm, 2) << "]" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif 
#if 0
      std::cout << "[    NEWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("numnu"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetPDGPIDName( numu->var<int>("ipnu", iprm) )
                  << ", pnu = " << numu->var<float>("pnu", iprm)*1000. << " MeV" 
                  << ", dirnu = [" << numu->var<float>("dirnu", iprm, 0) << ", " << numu->var<float>("dirnu", iprm, 1) << ", " << numu->var<float>("dirnu", iprm, 2) << "]" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif
#if 0
      std::cout << "[    VCWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetPDGPIDName( numu->var<int>("Ipvc", iprm) )
                  << ", Iorgvc = [" << Iorgvc[iprm] 
                  << "], Ichvc = [" << numu->var<int>("Ichvc", iprm)
                  << "], Pvc = [" << Pvc[iprm][0] << ", " << Pvc[iprm][1] << ", " << Pvc[iprm][2] << "] = " << numu->var<float>("Abspvc", iprm) << " MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif
#if 0
      std::cout << "[     VECT2    ]" << std::endl;
      for (int iscnd=0; iscnd<npar2; iscnd++) {
        std::cout << "[### " << ientry 
                  << " ###] Secondary[" << iscnd+1 << "] " << GetGEANTPIDName( ipv2[iscnd] )
                  << ", iorg = [" << iorg[iscnd] 
                  << "], posv2 = [" << posv2[iscnd][0] << ", " << posv2[iscnd][1] << ", " << posv2[iscnd][2]
                  << "] cm, pmomv2 = [" << pmomv2[iscnd][0] << ", " << pmomv2[iscnd][1] << ", " << pmomv2[iscnd][2] << "] MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
      std::cout << "[    CONVVECT    ]" << std::endl;
#endif
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
#if 0
        std::cout << "[### " << ientry 
                  << " ###] Secondary[" << iscnd+1 << "] " << GetPDGPIDName( numu->var<int>("iprtscnd", iscnd) )
                  << ", lmecscnd = " << numu->var<int>("lmecscnd", iscnd)
                  << ", iprntprt = " << GetPDGPIDName( numu->var<int>("iprntprt", iscnd) )
                  << ", iprntidx = [" << iprntidx[iscnd]
                  << "], ichildidx = [" << ichildidx[iscnd]
                  << "], vtxscnd = [" << numu->var<float>("vtxscnd", iscnd, 0) << ", " << numu->var<float>("vtxscnd", iscnd, 1) << ", " << numu->var<float>("vtxscnd", iscnd, 2)
                  << "] cm, pscnd = [" << pscnd[iscnd][0] << ", " << pscnd[iscnd][1] << ", " << pscnd[iscnd][2]
                  << "] MeV, vtxprnt = [" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2]
                  << "] cm, pprntinit = [" << pprntinit[iscnd][0] << ", " << pprntinit[iscnd][1] << ", " << pprntinit[iscnd][2]
                  << "] MeV, pprnt = [" << pprnt[iscnd][0] << ", " << pprnt[iscnd][1] << ", " << pprnt[iscnd][2] << "] MeV" << std::endl;
#endif
        if (ntagana.GetTrueMuNCapVtx(iscnd, numu, ichildidx, MuNCapVtx)) {
          TrueMuN++;
          float d_Prm_x_MuNCap = GetSimpleDistance(PrmVtx, MuNCapVtx);
          if (intmode<31) h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100., OscProb);
          else h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100.);
        }
      }


      int TrueBefFSI   = ntagana.GetTrueGenNBefFSI(numu);
      int TrueBefSI    = ntagana.GetTrueGenNBefSI(numu, Iorgvc);
      //int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprntinit);
      int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprntinit, Iorgvc);
      int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt, pprntinit);
      //int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprnt);
      //int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt, pprnt);

      //if (TrueBefSI!=0) std::cout << "Neutrons generated by nucleon FSI: " << TrueBefSI << std::endl;
      //std::cout << " " << std::endl;

#if 0
      std::cout << "# generated neutrons before FSI: " << TrueBefFSI << std::endl;
      std::cout << "# generated neutrons up to FSI : " << TrueBefSI << std::endl;
      std::cout << "# captured neutrons up to FSI  : " << TrueCapBefSI << std::endl;
      std::cout << "# captured neutrons from SI    : " << TrueAftSI << std::endl;
      std::cout << "# captured neutrons from mu    : " << TrueMuN << std::endl;
      std::cout << "NTrueN: " << NTrueN << std::endl;
      std::cout << " " << std::endl;
#endif

      //if (NTrueN-(TrueBefSI+TrueAftSI+TrueMuN)!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //if (TrueMuN!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //std::cout << " " << std::endl;
      if (intmode<31) {
        GenPreFSIN   += TrueBefFSI*OscProb;
        GenPostFSIN  += TrueBefSI*OscProb;

        CapPostFSIN  += TrueCapBefSI*OscProb;
        CapSIN       += TrueAftSI*OscProb;
        CapMuN       += TrueMuN*OscProb;
        TrueN        += NTrueN*OscProb;
      }
      else {
        GenPreFSIN   += TrueBefFSI;
        GenPostFSIN  += TrueBefSI;

        CapPostFSIN  += TrueCapBefSI;
        CapSIN       += TrueAftSI;
        CapMuN       += TrueMuN;
        TrueN        += NTrueN;
      }
      
      if (intmode==1) {
        //if (TrueBefFSI==1) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
        h1_GenBefFSINeutrons -> Fill(TrueBefFSI);
        h1_GenBefSINeutrons  -> Fill(TrueBefSI);
        h1_GenAftSINeutrons  -> Fill(TrueCapBefSI+TrueAftSI);
        h1_GenMuCapNeutrons  -> Fill(TrueMuN);
      } 



      if (MCType=="Water" || MCType=="water") continue;


      //decay-e distance @ C1-C6
      int FQDcyE_Box = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtMax, N50Min, N50Max, false);
      bool  PrmMuEnd = false;
      bool  RecoDcyE = false;
      float PrmMuEndVtx[3] = {0., 0., 0.}; //mu end vertex
      //if (FQDcyE_Box==DCYENUM) {
      if (FQDcyE_Box==DCYENUM && Enu/1000. >= 0.5 && Enu/1000. <= 0.7) {
        PrmMuEnd = decayebox.GetTrueMuEndVtx(eOsc, iprntidx, numu, PrmMuEndVtx); //Get truth mu end vertex
        if (!PrmMuEnd) {
          if (intmode==1) NoPrmMuEnd_CCQE++;
          if (intmode>=2 && intmode<=30) NoPrmMuEnd_CCnonQE++;
          if (intmode>=31) NoPrmMuEnd_NC++;
        }

        for (int iscnd=1; iscnd<numu->var<int>("fqnse"); iscnd++) {

          float RecoDcyEVtx[3] = {0., 0., 0.}; //fiTQun decay-e generation vertex

          RecoDcyE = decayebox.GetRecoDcyEGenVtx(iscnd, numu, RecoDcyEVtx);
          if (PrmMuEnd && RecoDcyE) {
            float d_MuEnd_x_fQDcyE = ndistance.TakeDistance(PrmMuEndVtx, RecoDcyEVtx);

            if (intmode==1) h1_TruePrmMuEnd_x_fQDcyE[0] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (intmode>=2 && intmode<=10) h1_TruePrmMuEnd_x_fQDcyE[1] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (intmode>10 && intmode<=30) h1_TruePrmMuEnd_x_fQDcyE[2] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (intmode>=31) h1_TruePrmMuEnd_x_fQDcyE[3] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
          }
        }
      }
      
      
      // cut selection
#if 0
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        if (DWallMeanDir->at(jentry)<2500) {
          if (intmode<31) sel_C1 += OscProb;
          else sel_C1++;
          HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase1);

          if (TagDWall->at(jentry)>200) {
            if (intmode<31) sel_C2 += OscProb;
            else sel_C2++;
            HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase2);

            if (Beta1->at(jentry)<0.3) {
              if (intmode<31) sel_C3 += OscProb;
              else sel_C3++;
              HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase3);
              
              if (Beta2->at(jentry)>-0.05 && Beta2->at(jentry)<0.1) {
                if (intmode<31) sel_C4 += OscProb;
                else sel_C4++;
                HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase4);

                if (DarkLikelihood->at(jentry)<0.1) {
                  if (intmode<31) sel_C5 += OscProb;
                  else sel_C5++;
                  HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase5);

                  if (BurstRatio->at(jentry)<0.2) {
                    if (intmode<31) sel_C6 += OscProb;
                    else sel_C6++;
                    HistFillforLabel(numu, Label->at(jentry), NHits->at(jentry), h1_NHits_CutBase6);
                  }
                }
              }
            }
          }
        }
      }
#endif
      

      ntagana.GetTruthNeutrons(NTrueN, numu, Type, E, DWall);
      ntagana.GetTruthNeutronsIntType(numu, NTrueN);
      ntagana.GetResolutionwTrueN(numu, NTrueN);

      //Truth distance distribution
      for (UInt_t jentry=0; jentry<DistFromPV->size(); ++jentry) {
        if (Type->at(jentry)==2) ndistance.GetTruthDistance(numu, tagvx->at(jentry), tagvy->at(jentry), tagvz->at(jentry), vecvx, vecvy, vecvz);
      }

      ntagana.GetTruthNeutronsinSearch(t->size(), Type, t, 3., E, DWall);
      ntagana.GetTruthDecayeinSearch(t->size(), Type, t, 3.);


      // Check truth breakdown(H-n/Gd-n/Decay-e/Acc.Noise) of candidates in the time window
      ntagana.TruthBreakdowninWindow(numu, TagClass, t, DWall, TagIndex, Label, FitT, TagDWall);

      ntagana.GetNlikeCandidates(numu, etagmode, NHits, FitT, TagOut, Label);

      // Check neutrino events with tagged neutrons
      ntagana.GetNeutrinoEventswNTag(TagOut, TagIndex, NHits, FitT, Label, NTrueN, 
                                     etagmode, numu, neuosc, nlikeThreshold/0.05,
                                     recothetamu, thetamin, thetamax);

#if 0
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        if (TagOut->at(jentry)>nlikeThreshold && !ntagana.RemnantChecker(Label->at(jentry))) {
          bool etagboxin = false;
          etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry));
          if (!etagboxin) {
            h1_AllNHits_Nlike -> Fill(NHits->at(jentry));
            h1_AllFitT_Nlike  -> Fill(FitT->at(jentry));
          }
          else {
            h1_AllNHits_Elike -> Fill(NHits->at(jentry));
            h1_AllFitT_Elike  -> Fill(FitT->at(jentry));
          }
        }
      }
#endif
      

      //Number of tagged-neutrons
      //CCQE w/ tagged-n
      int numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
      int numtaggednoise = ntagana.GetTaggedNoise(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);

      float Pmu = numu->var<float>("fq1rmom", PrmEvent, FQ_MUHYP);
      float Pt  = neuosc.GetMuonPt(numu);
      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, Pt/1000., xMuPtbins, TaggedN_x_MuPt, h1_TaggedN_x_MuPt, 1);
      ntagana.TrueN_x_kinematics(numu, NTrueN, Pt/1000., xMuPtbins, TrueN_x_MuPt, h1_TrueN_x_MuPt, 1);

      ntagana.NCapVtxResEstimator(numu, NTrueN, tscnd, vtxprnt, true, FitT, NHits, Label, TagOut, nlikeThreshold, fvx, fvy, fvz);
      //ntagana.GetRecoNCapTime(numu, etagmode, FitT, NHits, Label, TagOut, nlikeThreshold);
      if (intmode==1 && numtaggedneutrons!=0) CCQEwTaggedNeutrons++;

      if (intmode==1)                 h1_TagNmultiplicity[0]->Fill(numtaggedneutrons, OscProb);
      if (intmode>=2 && intmode<=10)  h1_TagNmultiplicity[1]->Fill(numtaggedneutrons, OscProb);
      if (intmode>10 && intmode<=30)  h1_TagNmultiplicity[2]->Fill(numtaggedneutrons, OscProb);
      if (intmode>=31)                h1_TagNmultiplicity[3]->Fill(numtaggedneutrons);


      //std::cout << "TagOut size: " << TagOut->size() << ", FitGoodness size: " << FitGoodness->size() << std::endl;
      for (UInt_t jentry=0; jentry<FitGoodness->size(); jentry++) {
        if (intmode<31) {
          if (Label->at(jentry)==0) h1_Goodness[0] -> Fill(FitGoodness->at(jentry), OscProb);  
          if (Label->at(jentry)==1) h1_Goodness[1] -> Fill(FitGoodness->at(jentry), OscProb);
          if (Label->at(jentry)==2) h1_Goodness[2] -> Fill(FitGoodness->at(jentry), OscProb);
          if (Label->at(jentry)==3) h1_Goodness[3] -> Fill(FitGoodness->at(jentry), OscProb);
        }
        else {
          if (Label->at(jentry)==0) h1_Goodness[0] -> Fill(FitGoodness->at(jentry));  
          if (Label->at(jentry)==1) h1_Goodness[1] -> Fill(FitGoodness->at(jentry));
          if (Label->at(jentry)==2) h1_Goodness[2] -> Fill(FitGoodness->at(jentry));
          if (Label->at(jentry)==3) h1_Goodness[3] -> Fill(FitGoodness->at(jentry));
        }
        
      }


      //Pre-selection
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        //Truth Gd-n or H-n captures
        if (Label->at(jentry)==2 || Label->at(jentry)==3) {
          //Fill corresponded truth distance
          for (UInt_t kentry=0; kentry<DistFromPV->size(); ++kentry) {
            if (Type->at(kentry)==2 && DWall->at(kentry)>0.) {
              ndistance.GetPreEffDistance(numu, TagIndex->at(jentry), kentry,
                                          tagvx->at(kentry), tagvy->at(kentry), tagvz->at(kentry),
                                          vecvx, vecvy, vecvz);
            }
          }
        }
      }


      //Threshold scan
      for (int ith=0; ith<CUTSTEP; ith++) {

        //Candidates loop
        for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {

          ntagana.GetTagBreakdown(numu, ith, jentry, TMVATH[ith], NHits, FitT, Label, TagOut, etagmode);
          //ntagana.GetTagBreakdown(numu, ith, jentry, TMVATH[ith], N50, FitT, Label, TagOut, etagmode);
          //TagCandidates++;
          TagCandidates += OscProb;


          //Truth Gd-n or H-n captures
          if (Label->at(jentry)==2 || Label->at(jentry)==3) {

            if (etagmode) {
              //Focus on neutron-like candidates(e-tagging ON)
              if (TagOut->at(jentry)>TMVATH[ith] && ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry))==false) {
              //if (TagOut->at(jentry)>TMVATH[ith] && ntagana.DecayelikeChecker(etagmode, N50->at(jentry), FitT->at(jentry))==false) {
                //Fill corresponded truth distance
                for (UInt_t kentry=0; kentry<DistFromPV->size(); ++kentry) {
                  if (Type->at(kentry)==2 && DWall->at(kentry)>0.) {
                    ndistance.GetOverallEffDistance(numu, ith, TagIndex->at(jentry), kentry,
                                                  tagvx->at(kentry), tagvy->at(kentry), tagvz->at(kentry),
                                                  vecvx, vecvy, vecvz);
                  }
                }
              }
            }
            else {
              //Focus on neutron-like candidates(e-tagging OFF)
              if (TagOut->at(jentry)>TMVATH[ith]) {
                //Fill corresponded truth distance
                for (UInt_t kentry=0; kentry<DistFromPV->size(); ++kentry) {
                  if (Type->at(kentry)==2 && DWall->at(kentry)>0.) {
                    ndistance.GetOverallEffDistance(numu, ith, TagIndex->at(jentry), kentry,
                                                  tagvx->at(kentry), tagvy->at(kentry), tagvz->at(kentry),
                                                  vecvx, vecvy, vecvz);
                  }
                }
              }
            }
          }
        } //candidates loop

      } //threshold scan

/*
      float PrmVtx[3] = {0., 0., 0.};  //Primary vertex
      PrmVtx[0] = numu->var<float>("posv", 0);
      PrmVtx[1] = numu->var<float>("posv", 1);
      PrmVtx[2] = numu->var<float>("posv", 2);
      int TrueMuN = 0;
      float MuNCapVtx[3]   = {0., 0., 0.};  //neutron(from primary interaction) capture vertex

      //GetNeutrinoInteraction(ientry, intmode);
#if 0
      std::cout << "[     VECT     ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("npar"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetGEANTPIDName( numu->var<int>("ipv", iprm) )
                  << ", posv = [" << numu->var<float>("posv", 0) << ", " << numu->var<float>("posv", 1) << ", " << numu->var<float>("posv", 2)
                  << "] cm, pmomv = " << numu->var<float>("pmomv", iprm) << " MeV" 
                  << ", dirv = [" << numu->var<float>("dirv", iprm, 0) << ", " << numu->var<float>("dirv", iprm, 1) << ", " << numu->var<float>("dirv", iprm, 2) << "]" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif 
#if 0
      std::cout << "[    NEWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("numnu"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetPDGPIDName( numu->var<int>("ipnu", iprm) )
                  << ", pnu = " << numu->var<float>("pnu", iprm)*1000. << " MeV" 
                  << ", dirnu = [" << numu->var<float>("dirnu", iprm, 0) << ", " << numu->var<float>("dirnu", iprm, 1) << ", " << numu->var<float>("dirnu", iprm, 2) << "]" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif
#if 0
      std::cout << "[    VCWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << GetPDGPIDName( numu->var<int>("Ipvc", iprm) )
                  << ", Iorgvc = [" << Iorgvc[iprm] 
                  << "], Ichvc = [" << numu->var<int>("Ichvc", iprm)
                  << "], Pvc = [" << Pvc[iprm][0] << ", " << Pvc[iprm][1] << ", " << Pvc[iprm][2] << "] = " << numu->var<float>("Abspvc", iprm) << " MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
#endif
#if 0
      std::cout << "[     VECT2    ]" << std::endl;
      for (int iscnd=0; iscnd<npar2; iscnd++) {
        std::cout << "[### " << ientry 
                  << " ###] Secondary[" << iscnd+1 << "] " << GetGEANTPIDName( ipv2[iscnd] )
                  << ", iorg = [" << iorg[iscnd] 
                  << "], posv2 = [" << posv2[iscnd][0] << ", " << posv2[iscnd][1] << ", " << posv2[iscnd][2]
                  << "] cm, pmomv2 = [" << pmomv2[iscnd][0] << ", " << pmomv2[iscnd][1] << ", " << pmomv2[iscnd][2] << "] MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
      std::cout << "[    CONVVECT    ]" << std::endl;
#endif
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
#if 0
        std::cout << "[### " << ientry 
                  << " ###] Secondary[" << iscnd+1 << "] " << GetPDGPIDName( numu->var<int>("iprtscnd", iscnd) )
                  << ", lmecscnd = " << numu->var<int>("lmecscnd", iscnd)
                  << ", iprntprt = " << GetPDGPIDName( numu->var<int>("iprntprt", iscnd) )
                  << ", iprntidx = [" << iprntidx[iscnd]
                  << "], ichildidx = [" << ichildidx[iscnd]
                  << "], vtxscnd = [" << numu->var<float>("vtxscnd", iscnd, 0) << ", " << numu->var<float>("vtxscnd", iscnd, 1) << ", " << numu->var<float>("vtxscnd", iscnd, 2)
                  << "] cm, pscnd = [" << pscnd[iscnd][0] << ", " << pscnd[iscnd][1] << ", " << pscnd[iscnd][2]
                  << "] MeV, vtxprnt = [" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2]
                  << "] cm, pprntinit = [" << pprntinit[iscnd][0] << ", " << pprntinit[iscnd][1] << ", " << pprntinit[iscnd][2]
                  << "] MeV, pprnt = [" << pprnt[iscnd][0] << ", " << pprnt[iscnd][1] << ", " << pprnt[iscnd][2] << "] MeV" << std::endl;
#endif
        if (ntagana.GetTrueMuNCapVtx(iscnd, numu, ichildidx, MuNCapVtx)) {
          TrueMuN++;
          float d_Prm_x_MuNCap = GetSimpleDistance(PrmVtx, MuNCapVtx);
          if (intmode<31) h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100., OscProb);
          else h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100.);
        }
      }



      int TrueBefFSI   = ntagana.GetTrueGenNBefFSI(numu);
      int TrueBefSI    = ntagana.GetTrueGenNBefSI(numu, Iorgvc);
      //int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprntinit);
      int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprntinit, Iorgvc);
      int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt, pprntinit);
      //int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprnt);
      //int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt, pprnt);

      //if (TrueBefSI!=0) std::cout << "Neutrons generated by nucleon FSI: " << TrueBefSI << std::endl;
      //std::cout << " " << std::endl;

#if 0
      std::cout << "# generated neutrons before FSI: " << TrueBefFSI << std::endl;
      std::cout << "# generated neutrons up to FSI : " << TrueBefSI << std::endl;
      std::cout << "# captured neutrons up to FSI  : " << TrueCapBefSI << std::endl;
      std::cout << "# captured neutrons from SI    : " << TrueAftSI << std::endl;
      std::cout << "# captured neutrons from mu    : " << TrueMuN << std::endl;
      std::cout << "NTrueN: " << NTrueN << std::endl;
      std::cout << " " << std::endl;
#endif

      //if (NTrueN-(TrueBefSI+TrueAftSI+TrueMuN)!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //if (TrueMuN!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //std::cout << " " << std::endl;
      if (intmode<31) {
        GenPreFSIN   += TrueBefFSI*OscProb;
        GenPostFSIN  += TrueBefSI*OscProb;

        CapPostFSIN  += TrueCapBefSI*OscProb;
        CapSIN       += TrueAftSI*OscProb;
        CapMuN       += TrueMuN*OscProb;
        TrueN        += NTrueN*OscProb;
      }
      else {
        GenPreFSIN   += TrueBefFSI;
        GenPostFSIN  += TrueBefSI;

        CapPostFSIN  += TrueCapBefSI;
        CapSIN       += TrueAftSI;
        CapMuN       += TrueMuN;
        TrueN        += NTrueN;
      }
      
      if (intmode==1) {
        //if (TrueBefFSI==1) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
        h1_GenBefFSINeutrons -> Fill(TrueBefFSI);
        h1_GenBefSINeutrons  -> Fill(TrueBefSI);
        h1_GenAftSINeutrons  -> Fill(TrueCapBefSI+TrueAftSI);
        h1_GenMuCapNeutrons  -> Fill(TrueMuN);
      } 
*/



      /////  Reco distance  /////
      float RecoPrmVtx[3] = {0., 0., 0.};  // SKDETSIM-based fiTQun vertex
      RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
      RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
      RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);

      for (UInt_t ican=0; ican<TagOut->size(); ican++) {

        //h1_AllRecoNCapTime -> Fill(FitT->at(ican));

        bool etagboxin = false;
        if (etagmode){

          etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican));
          if (TagOut->at(ican)>nlikeThreshold && etagboxin==false) {

            float RecoNCapVtx[3] = {0., 0., 0.};
            RecoNCapVtx[0] = fvx->at(ican);
            RecoNCapVtx[1] = fvy->at(ican);
            RecoNCapVtx[2] = fvz->at(ican);

            h1_RecoNCapDistance -> Fill( GetSimpleDistance(RecoPrmVtx, RecoNCapVtx)/100. );
          }
        }
      }

    } //New 1R muon selection

  }

  //std::cout << "No mu stop CCQE   : " << NoPrmMuEnd_CCQE << std::endl;
  //std::cout << "No mu stop CCnonQE: " << NoPrmMuEnd_CCnonQE << std::endl;
  //std::cout << "No mu stop NC     : " << NoPrmMuEnd_NC << std::endl;

  
  //std::cout << "No nlike: " << test1 << std::endl;
  //std::cout << "More than one nlike: " << test2 << std::endl;
  /*std::cout << "CCQE w/ tagged neutrons: " << CCQEwTaggedNeutrons << std::endl;
  std::cout << "All Primary Neutrons: " << AllPrimaryNeutrons << std::endl;
  std::cout << "All SI Neutrons: " << AllSINeutrons << std::endl;
  std::cout << "All Other Neutrons: " << AllOtherNeutrons << std::endl;
  std::cout << "CCQE w/ tagged neutrons(nonzero truth primary neutrons): " << CCQEwTaggedNeutrons_prm << std::endl;
  std::cout << "CCQE w/ tagged neutrons(nonzero truth secondary neutrons): " << CCQEwTaggedNeutrons_scnd << std::endl;
  */

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

    resultfile << "N1 (acc) : " << N1_acc << std::endl;
    resultfile << "N1 (dcye): " << N1_dcye << std::endl;
    resultfile << "N1 (H)   : " << N1_H << std::endl;
    resultfile << "N1 (Gd)  : " << N1_Gd << std::endl;
    resultfile << " " << std::endl;
    resultfile << "N2 (acc) : " << N2_acc << std::endl;
    resultfile << "N2 (dcye): " << N2_dcye << std::endl;
    resultfile << "N2 (H)   : " << N2_H << std::endl;
    resultfile << "N2 (Gd)  : " << N2_Gd << std::endl;
    resultfile << " " << std::endl;
    resultfile << "N3 (acc) : " << N3_acc << std::endl;
    resultfile << "N3 (dcye): " << N3_dcye << std::endl;
    resultfile << "N3 (H)   : " << N3_H << std::endl;
    resultfile << "N3 (Gd)  : " << N3_Gd << std::endl;
    resultfile << " " << std::endl;
    resultfile << "N4 (acc) : " << N4_acc << std::endl;
    resultfile << "N4 (dcye): " << N4_dcye << std::endl;
    resultfile << "N4 (H)   : " << N4_H << std::endl;
    resultfile << "N4 (Gd)  : " << N4_Gd << std::endl;
    resultfile << " " << std::endl;

    resultfile << "NTag Cut Base[ DarkLikelihood ]: " << sel_C1 << std::endl;
    resultfile << "NTag Cut Base[ BurstRatio     ]: " << sel_C2 << std::endl;
    resultfile << "NTag Cut Base[ DWallMeanDir   ]: " << sel_C3 << std::endl;
    resultfile << "NTag Cut Base[ DWall          ]: " << sel_C4 << std::endl;
    resultfile << "NTag Cut Base[ Beta1          ]: " << sel_C5 << std::endl;
    resultfile << "NTag Cut Base[ Beta2          ]: " << sel_C6 << std::endl;
    resultfile << " " << std::endl;

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

    resultfile << "All Truth neutrons: " << AllTruthNeutrons << std::endl;
    resultfile << "Candidates        : " << TagCandidates << std::endl;
    std::cout  << "All neutron-like  : " << nlikeAll << std::endl;

    // Calculation of ROC
#if 0
    float TagTPR[CUTSTEP];
    float TagFPR[CUTSTEP];
    for (int i=0; i<CUTSTEP; i++) {
      TagTPR[i] = 0;
      TagFPR[i] = 0;
    }
    for (int ith=0; ith<CUTSTEP; ith++) {
      TagFN[ith] = AllTruthNeutrons - TagTP[ith];
      TagTN[ith] = TagCandidates - (TagFP[ith]+TagTP[ith]+TagFN[ith]);
      TagTPR[ith] = (float)TagTP[ith]/(TagTP[ith] + TagFN[ith]);
      TagFPR[ith] = (float)TagFP[ith]/(TagTN[ith] + TagFP[ith]);
    }

    g_ROC = new TGraph(CUTSTEP, TagFPR, TagTPR);

    // Calculation of FOM
    float TagFOM[CUTSTEP];
    float TagFOM_p30[CUTSTEP];
    float TagFOM_p40[CUTSTEP];
    float TagFOM_m30[CUTSTEP];
    float TagFOM_m40[CUTSTEP];
    for (int i=0; i<CUTSTEP; i++) {
      TagFOM[i] = 0.;
      TagFOM_p30[CUTSTEP] = 0;
      TagFOM_p40[CUTSTEP] = 0;
      TagFOM_m30[CUTSTEP] = 0;
      TagFOM_m40[CUTSTEP] = 0;
    }

    float MaxFOM = 0;
    float MaxFOM_p30 = 0;
    float MaxFOM_m30 = 0;
    float MaxFOM_p40 = 0;
    float MaxFOM_m40 = 0;
    float OptThreshold_FOM = 0;
    float OptThreshold_FOM_p30 = 0;
    float OptThreshold_FOM_m30 = 0;
    float OptThreshold_FOM_p40 = 0;
    float OptThreshold_FOM_m40 = 0;
    for (int ith=0; ith<CUTSTEP; ith++) {
      TagFOM[ith] = TagTP[ith]/std::sqrt( TagTP[ith] + TagFP[ith] );
      float TagTP_p30 = TagTP[ith] + 0.3*TagTP[ith];
      float TagTP_m30 = TagTP[ith] - 0.3*TagTP[ith];
      float TagTP_p40 = TagTP[ith] + 0.4*TagTP[ith];
      float TagTP_m40 = TagTP[ith] - 0.4*TagTP[ith];
      TagFOM_p40[ith] = TagTP_p40/std::sqrt( TagTP_p40 + TagFP[ith] );
      TagFOM_p30[ith] = TagTP_p30/std::sqrt( TagTP_p30 + TagFP[ith] );
      TagFOM_m30[ith] = TagTP_m30/std::sqrt( TagTP_m30 + TagFP[ith] );
      TagFOM_m40[ith] = TagTP_m40/std::sqrt( TagTP_m40 + TagFP[ith] );

      resultfile << "[### i=" << ith << ", Thr=" << TMVATH[ith] << " ###] FOM = " << TagFOM[ith] << std::endl;
      resultfile << "   +40%: " << TagTP_p40 << ", FOM = " << TagFOM_p40[ith] << std::endl;
      resultfile << "   +30%: " << TagTP_p30 << ", FOM = " << TagFOM_p30[ith] << std::endl;
      resultfile << "   -30%: " << TagTP_m30 << ", FOM = " << TagFOM_m30[ith] << std::endl;
      resultfile << "   -40%: " << TagTP_m40 << ", FOM = " << TagFOM_m40[ith] << std::endl;

      // finding of the max. FOM
      if (TagFOM[ith] > MaxFOM) {
        MaxFOM = TagFOM[ith];
        OptThreshold_FOM = TMVATH[ith];
      }
      if (TagFOM_p40[ith] > MaxFOM_p40) {
        MaxFOM_p40 = TagFOM_p40[ith];
        OptThreshold_FOM_p40 = TMVATH[ith];
      }
      if (TagFOM_p30[ith] > MaxFOM_p30) {
        MaxFOM_p30 = TagFOM_p30[ith];
        OptThreshold_FOM_p30 = TMVATH[ith];
      }
      if (TagFOM_m30[ith] > MaxFOM_m30) {
        MaxFOM_m30 = TagFOM_m30[ith];
        OptThreshold_FOM_m30 = TMVATH[ith];
      }
      if (TagFOM_m40[ith] > MaxFOM_m40) {
        MaxFOM_m40 = TagFOM_m40[ith];
        OptThreshold_FOM_m40 = TMVATH[ith];
      }

    }
    resultfile << "Optimized n-like threshold(FOM): " << OptThreshold_FOM << std::endl;
    resultfile << "                           +40%: " << OptThreshold_FOM_p40 << std::endl;
    resultfile << "                           +30%: " << OptThreshold_FOM_p30 << std::endl;
    resultfile << "                           -30%: " << OptThreshold_FOM_m30 << std::endl;
    resultfile << "                           -40%: " << OptThreshold_FOM_m40 << std::endl;
    g_FOM = new TGraph(CUTSTEP, TMVATH, TagFOM);
    g_FOM -> RemovePoint(20); // remove infinity @ n-likelihood=1

    g_FOM_p30 = new TGraph(CUTSTEP, TMVATH, TagFOM_p30);
    g_FOM_m30 = new TGraph(CUTSTEP, TMVATH, TagFOM_m30);
    g_FOM_p40 = new TGraph(CUTSTEP, TMVATH, TagFOM_p40);
    g_FOM_m40 = new TGraph(CUTSTEP, TMVATH, TagFOM_m40);
    g_FOM_p30 -> RemovePoint(20); // remove infinity @ n-likelihood=1
    g_FOM_m30 -> RemovePoint(20); // remove infinity @ n-likelihood=1
    g_FOM_p40 -> RemovePoint(20); // remove infinity @ n-likelihood=1
    g_FOM_m40 -> RemovePoint(20); // remove infinity @ n-likelihood=1
#endif

    ntagana.SummaryTruthInfoinSearch(3., NTagSummary);
    for (int ithr=0; ithr<CUTSTEP; ithr++) {
      h1_TagTrueN    -> SetBinContent(ithr+1, TaggedTruthNeutronsinWin[0][ithr]);
      h1_TagTrueN_H  -> SetBinContent(ithr+1, TaggedTruthHNeutronsinWin[0][ithr]);
      h1_TagTrueN_Gd -> SetBinContent(ithr+1, TaggedTruthGdNeutronsinWin[0][ithr]);

      h1_CanTrueN    -> SetBinContent(ithr+1, TruthNeutroninCandidatesinWin[0]);
      h1_CanTrueN_H  -> SetBinContent(ithr+1, TruthHNeutroninCandidatesinWin[0]);
      h1_CanTrueN_Gd -> SetBinContent(ithr+1, TruthGdNeutroninCandidatesinWin[0]);

      h1_TrueN    -> SetBinContent(ithr+1, AllTruthNeutrons);
      h1_TrueN_H  -> SetBinContent(ithr+1, TruthHNeutrons);
      h1_TrueN_Gd -> SetBinContent(ithr+1, TruthGdNeutrons);

      h1_MisTagDcye     -> SetBinContent(ithr+1, MisTaggedDecayeinNlike[0][ithr]);
      h1_MisTagAccNoise -> SetBinContent(ithr+1, MisTaggedAccNoiseinNlike[0][ithr]);
      h1_NuEvtC6        -> SetBinContent(ithr+1, SelectedCCQENeutrinos[5]+SelectedCC2p2hNeutrinos[5]+SelectedCCnonQENeutrinos[5]+SelectedNCNeutrinos[5]);
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
  ndistance.WritePlots(true);
  gDirectory -> cd("..");

  //noise rate and efficiency for window optimization
  ntagana.SetNoiseRateGraph();
  //ntagana.GetEfficiencyforWinOpt();
  ntagana.SetEfficiencyGraph(0);  //0 for [3 us, 535 us]

  ntagana.cdNTagAnalysis(fout);
  ntagana.WritePlots(true);
  gDirectory -> cd("..");

  WriteVECTHisto();

}
