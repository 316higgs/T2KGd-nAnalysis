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
  int NTrueN = 0.;      // for Ntag v1.1.3
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
    //Sequencial1RmuonSelection_Pion(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false);
    //if (numu->var<int>("fqnse")==3) 
      DecayeCutScan(prmsel, evsel, numu, decayebox, eMode, eOsc);
    if (prmsel.C1ApplyFCFV(evsel)     && 
        prmsel.C2Apply1R(evsel)       &&
        prmsel.C3Applymuonlike(evsel) &&
        prmsel.C4ApplyPmu200MeV(evsel)) 
    {

      //decayebox.GetDecayeTagPurity(numu, tscnd, pscnd, dtMax, N50Min, N50Max);
      decayebox.DecayeMatching(numu, nmue, tscnd);

      //Reconstructed neutrino energy
      float Enu = numu->var<float>("erec");
      int   FQDcyE = numu->var<int>("fqnse") - 1;
      //if (FQDcyE==1) GetSelectedModeEvents(numu);
      //if (Enu/1000. < 1. && FQDcyE==1) GetSelectedModeEvents(numu);
    }

    GetSelectedModeEvents(numu);

    //if (wallv>200) GeneratedEvents++;
    if (numu->var<float>("wallv")>200) GeneratedEvents++;


    //Proto 1R muon selection
    if (prmsel.ApplyProto1RmuonSelection(evsel)) GetProtoSelectedModeEvents(numu);


    //if (prmsel.C1ApplyFCFV(evsel)) neuosc.GetTrueEnu(numu);
    //float TruePrmVtx[3] = {0., 0., 0.,};
    //neuosc.GetTruePrmVtx(numu, TruePrmVtx);
    //ntagana.TrueNCapVtxProfile(Type, tagvx, tagvy, tagvz);

    h1_NTrueN[0] -> Fill(NTrueN);

    //int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, N50, FitT, Label, etagmode);
    int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
    GetSelectedTagN(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false, TagN);

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false)) {

      int intmode = TMath::Abs(numu->var<int>("mode"));

      //Neutrino energy distribution
      neuosc.GetTrueEnu(numu);
      neuosc.GetRecoEnu(numu);
      neuosc.GetPrmVtxResolution(numu);
      //ntagana.NCapVtxResEstimator(numu, NTrueN, tscnd, vtxprnt, true, FitT, N50, Label, TagOut, nlikeThreshold, fvx, fvy, fvz);
      //ntagana.NCapVtxResEstimator(numu, NTrueN, tscnd, vtxprnt, true, FitT, NHits, Label, TagOut, nlikeThreshold, fvx, fvy, fvz);

      float TruePrmVtx[3] = {0., 0., 0.,};
      neuosc.GetTruePrmVtx(numu, TruePrmVtx);
      ntagana.TrueNCapVtxProfile(Type, tagvx, tagvy, tagvz);
      ntagana.GetTrueNCapTime(t, Type, E);

      //Count # of truth decay-e per event
      int NumDcyE = 0;
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
        if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
            numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) NumDcyE++;
      }
      decayebox.GetTruthDecaye(numu, NumDcyE);
      /*if (NumDcyE!=0) {
        GetNeutrinoInteraction(ientry, intmode);
        std::cout << "------- Primary particles ---------" << std::endl;
        for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
          std::cout << "Particle[" << iprm << "]=" << numu->var<int>("Ipvc", iprm)
                                                   << ", Iflvc=" << Iflvc[iprm] 
                                                   << ", Ichvc=" << numu->var<int>("Ichvc", iprm)
                                                   << ", Iorgvc=" << Iorgvc[iprm] << std::endl;
        }
        std::cout << "------- Secondary particles ---------" << std::endl;
        for (int jscnd=0; jscnd<numu->var<int>("nscndprt"); jscnd++) {
          std::cout << "Particle[" << jscnd << "]=" << numu->var<int>("iprtscnd", jscnd)
                    << ", iprntprt=" << numu->var<int>("iprntprt", jscnd)
                    << ", iprntidx=" << iprntidx[jscnd]  
                    << ", lmecscnd=" << numu->var<int>("lmecscnd", jscnd) << std::endl;
        }
      }*/

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


      if (MCType=="Water" || MCType=="water") continue;

      float OscProb = numu->getOscWgt();
      float Enu = numu->var<float>("erec");

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

      // Check tagged truth neutrons and mis-tagged decay-e and noise with respect to window and threshold.
      ntagana.GetNlikeCandidatesinWindow(numu, t, DWall, TagIndex, etagmode, NHits, FitT, TagOut, Label, TagDWall);
      //ntagana.GetNlikeCandidatesinWindow(numu, t, DWall, TagIndex, etagmode, N50, FitT, TagOut, Label, TagDWall);

      // Check tagged truth decay-e and mis-tagged neutrons and noise with respect to window and threshold.
      ntagana.GetElikeCandidatesinWindow(t, TagIndex, etagmode, NHits, FitT, TagOut, Label);
      //ntagana.GetElikeCandidatesinWindow(t, TagIndex, etagmode, N50, FitT, TagOut, Label);

      // Check neutrino events with tagged neutrons
      ntagana.GetNeutrinoEventswNTag(TagOut, TagIndex, NHits, FitT, Label, NTrueN, 
                                     etagmode, numu, neuosc, nlikeThreshold/0.05,
                                     recothetamu, thetamin, thetamax);
      //ntagana.GetNeutrinoEventswNTag(TagOut, TagIndex, N50, FitT, Label, NTrueN, 
      //                               etagmode, numu, neuosc, nlikeThreshold/0.05,
      //                               recothetamu, thetamin, thetamax);

      //Number of tagged-neutrons
      //CCQE w/ tagged-n
      //int numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, N50, FitT, Label, etagmode);
      int numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
      if (intmode==1 && numtaggedneutrons!=0) {

        CCQEwTaggedNeutrons++;

        /*
        //Get neutrons from nu interaction + FSI
        float GenPrmNeutrons = ntagana.GetGenPrmNeutrons(numu, Iorgvc, Iflvc);
        h1_GenPrmNeutrons -> Fill(GenPrmNeutrons);

        float GenAftFSINeutrons = ntagana.GetGenAftFSINeutrons(numu);
        h1_GenAftFSINeutrons -> Fill(GenAftFSINeutrons);

        float GenAftSINeutrons = ntagana.GetGenAftSINeutrons(numu, iprntidx, vtxprnt);
        h1_GenAftSINeutrons -> Fill(GenAftSINeutrons);
        */

        //float GenSINeutrons = ntagana.GetGenSINeutrons(numu, iprntidx, vtxprnt);
        //h1_GenSINeutrons -> Fill(GenSINeutrons);
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
        
        //Threshold
        //if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
        //if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

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


      float PrmVtx[3] = {0., 0., 0.};  //Primary vertex
      PrmVtx[0] = numu->var<float>("posv", 0);
      PrmVtx[1] = numu->var<float>("posv", 1);
      PrmVtx[2] = numu->var<float>("posv", 2);
      int TrueMuN = 0;
      float MuNCapVtx[3]   = {0., 0., 0.};  //neutron(from primary interaction) capture vertex
      ///////////  True distance with respect to each neutron source  /////////////
      /*GetNeutrinoInteraction(ientry, intmode);
      std::cout << "[    NEWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("numnu"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << numu->var<int>("ipnu", iprm) 
                  << " P = " << numu->var<float>("pnu", iprm)*1000. << " MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
      std::cout << "[    VCWORK    ]" << std::endl;
      for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
        std::cout << "[### " << ientry 
                  << " ###] Primary[" << iprm+1 << "] " << numu->var<int>("Ipvc", iprm) 
                  << " Iorgvc = [" << Iorgvc[iprm] 
                  << "] Ichvc = [" << numu->var<int>("Ichvc", iprm)
                  << "] P = [" << Pvc[iprm][0] << ", " << Pvc[iprm][1] << ", " << Pvc[iprm][2] << "] MeV" << std::endl;
      }
      std::cout << "----------------------" << std::endl;
      std::cout << "[    CONVVECT    ]" << std::endl;*/
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
        /*std::cout << "[### " << ientry 
                  << " ###] Secondary[" << iscnd+1 << "] " << numu->var<int>("iprtscnd", iscnd) 
                  << " lmecscnd = " << numu->var<int>("lmecscnd", iscnd)
                  << " iprntprt = [" << numu->var<int>("iprntprt", iscnd) 
                  << "] iprntidx = [" << iprntidx[iscnd]
                  << "] ichildidx = [" << ichildidx[iscnd]
                  << "] vtxscnd = [" << numu->var<float>("vtxscnd", iscnd, 0) << ", " << numu->var<float>("vtxscnd", iscnd, 1) << ", " << numu->var<float>("vtxscnd", iscnd, 2)
                  << "] cm, vtxprnt = [" << vtxprnt[iscnd][0] << ", " << vtxprnt[iscnd][1] << ", " << vtxprnt[iscnd][2]
                  << "] cm, P = [" << pscnd[iscnd][0] << ", " << pscnd[iscnd][1] << ", " << pscnd[iscnd][2] << "] MeV" << std::endl;*/
        if (ntagana.GetTrueMuNCapVtx(iscnd, numu, ichildidx, MuNCapVtx)) {
          TrueMuN++;
          float d_Prm_x_MuNCap = GetSimpleDistance(PrmVtx, MuNCapVtx);
          if (intmode<31) h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100., OscProb);
          else h1_truedistance_MuCapn -> Fill(d_Prm_x_MuNCap/100.);
        }
      }
      int TrueBefFSI = ntagana.GetTrueGenNBefFSI(numu);
      int TrueBefSI  = ntagana.GetTrueGenNBefSI(numu);
      //int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt);
      //int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt);
      int TrueCapBefSI = ntagana.GetTrueCapNBefSI(numu, iprntidx, vtxprnt, pprntinit);
      int TrueAftSI    = ntagana.GetTrueCapNAftSI(numu, iprntidx, vtxprnt, pprntinit);
      /*std::cout << "# generated neutrons before FSI: " << TrueBefFSI << std::endl;
      std::cout << "# generated neutrons up to FSI : " << TrueBefSI << std::endl;
      std::cout << "# captured neutrons up to FSI  : " << TrueCapBefSI << std::endl;
      std::cout << "# captured neutrons from SI    : " << TrueAftSI << std::endl;
      std::cout << "# captured neutrons from mu    : " << TrueMuN << std::endl;
      std::cout << "NTrueN: " << NTrueN << std::endl;*/
      //if (NTrueN-(TrueBefSI+TrueAftSI+TrueMuN)!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //if (TrueMuN!=0) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
      //std::cout << " " << std::endl;
      if (intmode<31) {
        BefFSIn += TrueBefFSI*OscProb;
        BefSIn  += TrueCapBefSI*OscProb;
        SIn     += TrueAftSI*OscProb;
        MuN     += TrueMuN*OscProb;
        TrueN   += NTrueN*OscProb;
      }
      else {
        BefFSIn += TrueBefFSI;
        BefSIn  += TrueCapBefSI;
        SIn     += TrueAftSI;
        MuN     += TrueMuN;
        TrueN   += NTrueN;
      }
      /*BefFSIn += TrueBefFSI;
      BefSIn  += TrueCapBefSI;
      SIn     += TrueAftSI;
      MuN     += TrueMuN;
      TrueN   += NTrueN;*/
      
      if (intmode==1) {
        //if (TrueBefFSI==1) std::cout << "\e[38;5;09m\e[1m BUG? \e[0m" << std::endl;
        h1_GenBefFSINeutrons -> Fill(TrueBefFSI);
        h1_GenBefSINeutrons  -> Fill(TrueBefSI);
        h1_GenAftSINeutrons  -> Fill(TrueCapBefSI+TrueAftSI);
        h1_GenMuCapNeutrons  -> Fill(TrueMuN);
      }

    } //New 1R muon selection

  }


#if 1
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
      h1_1RmuonEvents->fArray[i+1]      = (float)SelectedParentNeutrinos[i]/SelectedParentNeutrinos[0];
      h1_Proto1RmuonEvents->fArray[i+1] = (float)ProtoSelectedParentNeutrinos[i]/ProtoSelectedParentNeutrinos[0];
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

    resultfile << "[Neutron] # generated neutrons before FSI: " << BefFSIn << std::endl;
    resultfile << "[Neutron] # captured neutrons up to FSI  : " << BefSIn << std::endl;
    resultfile << "[Neutron] # captured neutrons from SI    : " << SIn << std::endl;
    resultfile << "[Neutron] # captured neutrons from mu    : " << MuN << std::endl;
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


    // Calculation of ROC
    float TagTPR[CUTSTEP];
    float TagFPR[CUTSTEP];
    for (int i=0; i<CUTSTEP; i++) {
      TagTPR[i] = 0;
      TagFPR[i] = 0;
    }

    resultfile << "All Truth neutrons: " << AllTruthNeutrons << std::endl;
    resultfile << "Candidates        : " << TagCandidates << std::endl;
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
#endif


#if 1
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
  ntagana.SetEfficiencyGraph(0);  //0 for [3 us, 535 us]

  ntagana.cdNTagAnalysis(fout);
  ntagana.WritePlots();
  gDirectory -> cd("..");

  WriteVECTHisto();
#endif

}