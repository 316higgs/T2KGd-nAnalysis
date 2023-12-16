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
#include "include/NTagVariables.h"
#include "include/CLTOption.h"
#include "include/ResultSummary.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"
#include "src/NNInputVariables/inc/NNInputVariables.h"

#define NLIKETHRESHOLD 0.7


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
  //float NTrueN = 0.;
  int NTrueN = 0.;
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
  std::vector<int> *ParentIndex = 0; //avalable at NTag1.1.2
  TBranch *bParentIndex = 0;         //avalable at NTag1.1.2
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
  tchpar->SetBranchAddress("ParentIndex", &ParentIndex, &bParentIndex); //avalable at NTag1.1.2
  tchpar->SetBranchAddress("IntID", &IntID, &bIntID);
  //tchpar->SetBranchAddress("t", &par_t);
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
  std::vector<float> *N50 = 0;
  TBranch *bN50 = 0;
  std::vector<float> *N200 = 0;
  TBranch *bN200 = 0;
  std::vector<float> *NResHits = 0;
  TBranch *bNResHits = 0;
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
  std::vector<float> *BurstRatio = 0;
  TBranch *bBurstRatio = 0;
  std::vector<float> *FitGoodness = 0;
  TBranch *bFitGoodness = 0;
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
  std::vector<float> *TagOut = 0;
  TBranch *bTagOut = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N50", &N50, &bN50);
  tchntag->SetBranchAddress("N200", &N200, &bN200);
  tchntag->SetBranchAddress("NResHits", &NResHits, &bNResHits);
  tchntag->SetBranchAddress("TRMS", &TRMS, &bTRMS);
  tchntag->SetBranchAddress("DWall", &DWall, &bDWall);
  tchntag->SetBranchAddress("DWallMeanDir", &DWallMeanDir, &bDWallMeanDir);
  tchntag->SetBranchAddress("OpeningAngleMean", &OpeningAngleMean, &bOpeningAngleMean);
  tchntag->SetBranchAddress("OpeningAngleSkew", &OpeningAngleSkew, &bOpeningAngleSkew);
  tchntag->SetBranchAddress("OpeningAngleStdev", &OpeningAngleStdev, &bOpeningAngleStdev);
  tchntag->SetBranchAddress("MeanDirAngleMean", &MeanDirAngleMean, &bMeanDirAngleMean);
  tchntag->SetBranchAddress("MeanDirAngleRMS", &MeanDirAngleRMS, &bMeanDirAngleRMS);
  tchntag->SetBranchAddress("BurstRatio", &BurstRatio, &bBurstRatio);
  tchntag->SetBranchAddress("FitGoodness", &FitGoodness, &bFitGoodness);
  tchntag->SetBranchAddress("DarkLikelihood", &DarkLikelihood, &bDarkLikelihood);
  tchntag->SetBranchAddress("Beta1", &Beta1, &bBeta1);
  tchntag->SetBranchAddress("Beta2", &Beta2, &bBeta2);
  tchntag->SetBranchAddress("Beta3", &Beta3, &bBeta3);
  tchntag->SetBranchAddress("Beta4", &Beta4, &bBeta4);
  tchntag->SetBranchAddress("Beta5", &Beta5, &bBeta5);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu ======
  Int_t   Npvc;             //Number of primary particles
  Int_t   Ipvc[100];        //PID of primary particles
  Float_t Pvc[100][3];      //Momentum of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Ichvc[100];       //Chase at detector simulation or not (1: chase/0: not chase)
  Int_t   Iorgvc[100];      //Index of parent particle (0: initial particles, n: n-th final particle at the primary interaction)
  Int_t   nscndprt;         //Number of secondary particles
  Int_t   iprtscnd[1000];   //PID of the secondary particle
  Float_t tscnd[1000];      //Generated time of secondary particles
  Int_t   iprntprt[1000];   //PID of the parent of this secondary particle
  Int_t   iorgprt[1000];
  Int_t   iprnttrk[1000];
  Int_t   iprntidx[1000];   //Index of the parent particle (0: no parent(connected from primary particles), n: the parent of n-th secondary particle)
  Int_t   ichildidx[1000];  //Index of the first child particle (0: no childs, n: the first child of n-th secondary particle)
  Int_t   lmecscnd[1000];   //Interaction code of secondary particles based on GEANT
  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  //tchfQ -> SetBranchAddress("Npvc", &Npvc);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  //tchfQ -> SetBranchAddress("Ipvc", Ipvc);
  //tchfQ -> SetBranchAddress("Ichvc", Ichvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  //tchfQ -> SetBranchAddress("nscndprt", &nscndprt);
  //tchfQ -> SetBranchAddress("iprtscnd", iprtscnd);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  //tchfQ -> SetBranchAddress("iprntprt", iprntprt);
  //tchfQ -> SetBranchAddress("iorgprt", iorgprt);
  tchfQ -> SetBranchAddress("iprnttrk", iprnttrk);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
  //tchfQ -> SetBranchAddress("lmecscnd", lmecscnd);
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


  //Total event number of muon
  int NumberMu = 0;
  int NumberMuCap = 0;
  int NumberMu_wNeutrons = 0;

  //Number of neutrons from mu-
  int NumberMuN = 0;
  int NumberNCap_MuN = 0;

  //Number of neutrons from neutrino
  int NumberNuN = 0;
  int NumberNCap_NuN = 0;

  //int expNumberNuN = 0;

  int NumberNCap = 0;


  //Process
  CLTOptionSummary(ETAGKeyword, ETAG, MCTypeKeyword, MCType);

  for (int ientry=0; ientry<ntagEntries; ientry++) {

  	//Progress meter
    //if(ientry>100 && ientry%100==0) std::cout << "[### getNNvariables ###]  Progress: " << 100.*ientry/ntagEntries << "%" << std::endl;
    if(ientry>100 && ientry%100==0) std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Progress: " << 100.*ientry/ntagEntries << "%\e[0m" << std::endl;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchpar      -> GetEntry(ientry);
    tchtaggable -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bPID        -> GetEntry(tentry);
    bParentPID  -> GetEntry(tentry);
    bParentIndex -> GetEntry(tentry);  //avalable from NTag1.1.2
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
    bN50               -> GetEntry(tentry);
    bN200              -> GetEntry(tentry);
    bNResHits          -> GetEntry(tentry);
    bTRMS              -> GetEntry(tentry);
    bDWall             -> GetEntry(tentry);
    bDWallMeanDir      -> GetEntry(tentry);
    bOpeningAngleMean  -> GetEntry(tentry);
    bOpeningAngleSkew  -> GetEntry(tentry);
    bOpeningAngleStdev -> GetEntry(tentry);
    bMeanDirAngleMean  -> GetEntry(tentry);
    bMeanDirAngleRMS   -> GetEntry(tentry);
    bBurstRatio        -> GetEntry(tentry);
    bDarkLikelihood    -> GetEntry(tentry);
    bFitGoodness       -> GetEntry(tentry);
    bBeta1             -> GetEntry(tentry);
    bBeta2             -> GetEntry(tentry);
    bBeta3             -> GetEntry(tentry);
    bBeta4             -> GetEntry(tentry);
    bBeta5             -> GetEntry(tentry);
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();


    //Number of selected neutrino events
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    if (prmsel.C1ApplyFCFV(evsel)) {
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        h1_AllNTagOut -> Fill(TagOut->at(jentry));
      }
    }

    //New 1R muon selection
    //if (prmsel.C1ApplyFCFV(evsel)) {
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
      GetSelectedModeEvents(numu);

      int mode = TMath::Abs(numu->var<int>("mode"));
      float OscProb = numu->getOscWgt();

      int reco = 0;
      float reco_mucaptime = 0.;
      for (UInt_t jentry=0; jentry<Label->size(); ++jentry) {

        bool etagboxin = false;
        if (NHits->at(jentry)>50 && FitT->at(jentry)<20) etagboxin = true;
        //etagboxin = ntagana->DecayelikeChecker(etagmode, N50->at(ican), FitT->at(ican));

        float NNVar = 0.;
        for (int ivar=0; ivar<NNVARIABLES; ivar++) {
          switch (ivar) {
#if 0
            case 0:
              NNVar = NHits->at(jentry);
              break;
            case 1:
              NNVar = N200->at(jentry);
              break;
            case 2:
              NNVar = TRMS->at(jentry);
              break;
            case 3:
              NNVar = DWall->at(jentry);
              break;
            case 4:
              NNVar = DWallMeanDir->at(jentry);
              break;
            case 5:
              NNVar = OpeningAngleMean->at(jentry);
              break;
            case 6:
              NNVar = OpeningAngleStdev->at(jentry);
              break;
            case 7:
              NNVar = OpeningAngleSkew->at(jentry);
              break;
            case 8:
              NNVar = MeanDirAngleMean->at(jentry);
              break;
            case 9:
              NNVar = MeanDirAngleRMS->at(jentry);
              break;
            case 10:
              NNVar = Beta1->at(jentry);
              break;
            case 11:
              NNVar = Beta5->at(jentry);
              break;
#endif
            case 0:
              NNVar = NHits->at(jentry);
              break;
            case 1:
              NNVar = NResHits->at(jentry);
              break;
            case 2:
              NNVar = TRMS->at(jentry);
              break;
            case 3:
              NNVar = DWall->at(jentry);
              break;
            case 4:
              NNVar = DWallMeanDir->at(jentry);
              break;
            case 5:
              NNVar = OpeningAngleStdev->at(jentry);
              break;
            case 6:
              NNVar = Beta1->at(jentry);
              break;
            case 7:
              NNVar = Beta2->at(jentry);
              break;
            case 8:
              NNVar = Beta3->at(jentry);
              break;
            case 9:
              NNVar = Beta4->at(jentry);
              break;
            case 10:
              NNVar = Beta5->at(jentry);
              break;
            case 11:
              NNVar = BurstRatio->at(jentry);
              break;
            case 12:
              NNVar = FitGoodness->at(jentry);
              break;
            case 13:
              NNVar = DarkLikelihood->at(jentry);
              break;
            default:
              NNVar = 0.;
              break;  
          }

          //Pre-NN
#if 1
          if (mode <31) {
            if (Label->at(jentry)==0) h1_NNvar_AccNoise[ivar] -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==1) h1_NNvar_Decaye[ivar]   -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==2) h1_NNvar_H[ivar]        -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==3) h1_NNvar_Gd[ivar]       -> Fill(NNVar, OscProb);
          }
          else {
            if (Label->at(jentry)==0) h1_NNvar_AccNoise[ivar] -> Fill(NNVar);
            if (Label->at(jentry)==1) h1_NNvar_Decaye[ivar]   -> Fill(NNVar);
            if (Label->at(jentry)==2) h1_NNvar_H[ivar]        -> Fill(NNVar);
            if (Label->at(jentry)==3) h1_NNvar_Gd[ivar]       -> Fill(NNVar);
          }
          h1_NNvar[ivar] -> Fill(NNVar);
#endif

          //Post-NN
#if 0
          if (mode<31) {
            if (Label->at(jentry)==0 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_AccNoise[ivar] -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==1 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_Decaye[ivar]   -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==2 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_H[ivar]        -> Fill(NNVar, OscProb);
            if (Label->at(jentry)==3 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_Gd[ivar]       -> Fill(NNVar, OscProb);
          }
          else {
            if (Label->at(jentry)==0 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_AccNoise[ivar] -> Fill(NNVar);
            if (Label->at(jentry)==1 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_Decaye[ivar]   -> Fill(NNVar);
            if (Label->at(jentry)==2 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_H[ivar]        -> Fill(NNVar);
            if (Label->at(jentry)==3 && TagOut->at(jentry)>NLIKETHRESHOLD && etagboxin==false) h1_NNvar_Gd[ivar]       -> Fill(NNVar);
          }
          h1_NNvar[ivar] -> Fill(NNVar);
#endif
        }
        //h1_AllNHits -> Fill(NHits->at(jentry), OscProb);

        //NN output
        if (mode < 31) {
          if (Label->at(jentry)==0) h1_NTagOut[0] -> Fill(TagOut->at(jentry), OscProb);
          if (Label->at(jentry)==1) h1_NTagOut[1] -> Fill(TagOut->at(jentry), OscProb);
          if (Label->at(jentry)==2) h1_NTagOut[2] -> Fill(TagOut->at(jentry), OscProb);
          if (Label->at(jentry)==3) h1_NTagOut[3] -> Fill(TagOut->at(jentry), OscProb);
        }
        else {
          if (Label->at(jentry)==0) h1_NTagOut[0] -> Fill(TagOut->at(jentry));
          if (Label->at(jentry)==1) h1_NTagOut[1] -> Fill(TagOut->at(jentry));
          if (Label->at(jentry)==2) h1_NTagOut[2] -> Fill(TagOut->at(jentry));
          if (Label->at(jentry)==3) h1_NTagOut[3] -> Fill(TagOut->at(jentry));
        }


        //Excess of NHits for numu MC
        if (Label->at(jentry)==0 && (NHits->at(jentry) > 30 && NHits->at(jentry) < 80)) {
          h1_FitT_NHitsExcess -> Fill(FitT->at(jentry));
          reco++;
          reco_mucaptime = FitT->at(jentry);
          //NHitsExcess = true;
        }

        h1_Beta1 -> Fill(Beta1->at(jentry));
        h1_Beta2 -> Fill(Beta2->at(jentry));
        h1_Beta3 -> Fill(Beta3->at(jentry));
        h1_Beta4 -> Fill(Beta4->at(jentry));
        h1_Beta5 -> Fill(Beta5->at(jentry));
      }



      //NHits excess check
      int truth = 0;
      float truth_mucaptime = 0.;
      //Truth particles loop
      //std::cout << "Npvc(" << Npvc << ") + nscndprt(" << nscndprt << "): " << Npvc+nscndprt << std::endl;
      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {
        //std::cout << "[" << jentry+1 << "] PID: " << PID->at(jentry) << " --- ParentPID: " << ParentPID->at(jentry) << std::endl;

        //Truth gamma from muon
        if (PID->at(jentry)==22 && ParentPID->at(jentry)==13) {
          //std::cout << "[" << jentry+1 << "] PID: " << PID->at(jentry) << " --- ParentPID: " 
          //                                          << ParentPID->at(jentry) << " IntID:" 
          //                                          << IntID->at(jentry) << std::endl;
          h1_IntID -> Fill(IntID->at(jentry));

          //mu- capture
          if (IntID->at(jentry)==5) {
            truth++;
            truth_mucaptime = par_t->at(jentry);
            //std::cout << par_t[jentry] << std::endl;
          }
        }
      }

      //matching with the excess event and the truth
      if (reco==1 && reco==truth) h1_timediff -> Fill(truth_mucaptime - reco_mucaptime);
      //if (reco==1 && reco==truth) h1_timediff -> Fill(truth_mucaptime);



#if 0
      //NEUT level check
      // primary particles
      std::cout << "------  NEUT primary info  ------" << std::endl;
      for (int iprm=0; iprm<Npvc; iprm++) {
        std::cout << "[### " << ientry << " ###] Particle[" << iprm << "]=" << Ipvc[iprm]
                                       << ", Iflvc=" << Iflvc[iprm] 
                                       << ", Ichvc=" << Ichvc[iprm]
                                       << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
      }

      // secondary particles
      std::cout << "------  NEUT secondary info  ------" << std::endl;
      for (int iscnd=0; iscnd<nscndprt; iscnd++) {
        std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << iprtscnd[iscnd]
                                       << ", iprntprt=" << iprntprt[iscnd]
                                       << ", iprntidx=" << iprntidx[iscnd] 
                                       << ", ichildidx=" << ichildidx[iscnd] << std::endl;
      }
#endif


#if 0
      //Get gamma from mu- capture and make lists of neutrons from mu- capture and neutrino interactions
      std::cout << "------  NTag info  ------" << std::endl;
      int mu_thisev = 0;  // Number of muons
      int n_thisev  = 0;  // Number of neutrons from mu- captures
      bool MuCapture = false;            // This muon is captured or not?
      bool MuCapture_wNeutrons = false;  // This muon capture emits neutrons or not?
      //bool MuBremsstrahlung = false;     // This muon occurs bremsstrahlung

      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {

        float d_x = std::fabs(par_x->at(jentry) - vecvx);
        float d_y = std::fabs(par_y->at(jentry) - vecvy);
        float d_z = std::fabs(par_z->at(jentry) - vecvz);
        float d   = std::sqrt(d_x*d_x + d_y*d_y + d_z*d_z);

        //Fill creation vertex of all gamma-primary vertex
        /*if (PID->at(jentry)==22) {
          h1_truedistance_particle -> Fill(d/100.);
        }*/

        std::cout << "[### " << ientry << " ###] Particle[" << jentry << "]=" << PID->at(jentry) 
                                       << ", ParentPID=" << ParentPID->at(jentry) 
                                       << ", ParentIndex=" << ParentIndex->at(jentry)
                                       << ", IntID=" << IntID->at(jentry)
                                       << std::endl;

        //Total number of mu-
        if (PID->at(jentry)==13) {

          NumberMu++;   //Total number of muons
          mu_thisev++;  //Number of muons in this neutrino event

          //Bremsstrahlung from mu- (@ secondary lists)
          if (mu_thisev==2 && IntID->at(jentry)==9) {
            //MuBremsstrahlung = true;
            NumberMu -= 1; //prevent double counting
          }
        }

        //Find particles from muon captures
        if (ParentPID->at(jentry)==13 && IntID->at(jentry)==5) {
          MuCapture = true;
        }

        //Number of neutrons from muon
        if (PID->at(jentry)==2112 && ParentPID->at(jentry)==13 && IntID->at(jentry)==5) {
          MuCapture_wNeutrons = true; //switch on flag at once
          n_thisev++;
          NumberMuN++;
        }
        

        //Number of neutrons from neutrino interaction
        if (PID->at(jentry)==2112 && ParentPID->at(jentry)==0) NumberNuN++;
        //if (!(IntID->at(jentry)==5 && ParentPID->at(jentry)==13) && PID->at(jentry)==2112 && ParentPID->at(jentry)==0) NumberNuN++;

        //Number of all neutron captures
        if (PID->at(jentry)==22 && ParentPID->at(jentry)==2112) NumberNCap++;


        //Products from mu- capture (either n or gamma)
        /*if (IntID->at(jentry)==5 && ParentPID->at(jentry)==13) {
          //h1_truedistance_mu -> Fill(d/100.);
          if (PID->at(jentry)==22) h1_truedistance_mu_gamma -> Fill(d/100.);

          if (PID->at(jentry)==2112) {
            //std::cout << "----------------> MuNeutron[" << jentry << "] ParentPID: " << ParentPID->at(jentry) << std::endl;
            MuNeutronList.push_back(jentry);
          }
        }
        //Neutrons from neutrino interaction
        else {
          if (PID->at(jentry)==2112 && ParentPID->at(jentry)==0) {
            //std::cout << "----------------> NuNeutron[" << jentry << "] ParentPID: " << ParentPID->at(jentry) << std::endl;
            NuNeutronList.push_back(jentry);
          }
        }*/
        
        //gamma from neutron capture
        if (PID->at(jentry)==22) {
          if (ParentPID->at(jentry)==2112 && ParentIndex->at(jentry)!=-1) {
            //std::cout << "   !!!! Gamma from neutron !!!!  ParentIndex=" << ParentIndex->at(jentry) << std::endl;
            //std::cout << "                                 ParentPID=" << ParentPID->at(ParentIndex->at(jentry)) << std::endl;
            if (ParentPID->at(ParentIndex->at(jentry))==13) {
              //std::cout << "                                 **** This is n from mu- ****" << std::endl;
              NumberNCap_MuN++;
            }
            else {
              //std::cout << "                                 **** This is n from nu interaction ****" << std::endl;
              NumberNCap_NuN++;
            }
            
          }
        }

      }
      h1_MuNeutronMultiplicity -> Fill(n_thisev);


      //Count number of muons with neutrons
      for (UInt_t jentry=0; jentry<PID->size(); ++jentry) {

        //Muon captures
        if (PID->at(jentry)==13 && MuCapture==true) {
          NumberMuCap++;
        }

        //Muon captures with neutrons
        if (PID->at(jentry)==13 && MuCapture_wNeutrons==true) {
          NumberMu_wNeutrons++;
        }
      }
      
      
      std::cout << " " << std::endl;
#endif

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
    resultfile << "Selected NC events: " << SelectedNCevents << std::endl;
  }



  std::cout << "Total number of muons                    : " << NumberMu       << std::endl;
  std::cout << "Number of muon captures                  : " << NumberMuCap    
            << " (fraction of muon captures: " << ((float)NumberMuCap/NumberMu)*100. << " %)" << std::endl;
  std::cout << "Number of muon captures with neutrons    : " << NumberMu_wNeutrons 
            << " (fraction of muons with neutrons: " << ((float)NumberMu_wNeutrons/NumberMu)*100. << " %)" << std::endl;
  std::cout << "Total number of neutrons from mu- capture: " << NumberMuN      
            << " (Mean number of neutrons from mu-: " << ((float)NumberMuN/NumberMu_wNeutrons)*100. << ")" << std::endl;
  //std::cout << "Number of Gd-n (mu- capture)             : " << h1_truedistance_mu_n->Integral() << std::endl;
  std::cout << "Total number of neutrons from neutrino   : " << NumberNuN      << std::endl;
  std::cout << "Total number of all neutron captures     : " << NumberNCap     << std::endl;
  std::cout << "Number of captured neutrons (from mu-)   : " << NumberNCap_MuN << std::endl;
  std::cout << "Number of captured neutrons (from nu)    : " << NumberNCap_NuN << std::endl;
  //std::cout << "Expected number of neutrons from neutrino: " << expNumberNuN << std::endl;
  //std::cout << "Number of Gd-n (neutrino)                : " << h1_truedistance_nu_n->Integral() << std::endl;


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
  ndistance.WritePlots(false);
  gDirectory -> cd("..");

}