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
#include "include/VECTChannelChecker.h"

#include "src/DecayeBox/inc/DecayeBox.h"
#include "src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
#include "src/NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "src/DistanceViewer/inc/DistanceViewer.h"
#include "src/NTagAnalysis/inc/NTagAnalysis.h"
#include "src/TreeManager/inc/TreeManager.h"
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

  float thetamin = -1.;
  //float thetamin = 0.;
  //float thetamin = 0.2;
  //float thetamin = 0.4;
  //float thetamin = 0.6;
  //float thetamin = 0.8;
  float thetamax = 1.;

  //TTree
  TreeManager* AnaTuple = new TreeManager(3);
  AnaTuple -> SetAnaBranch();

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
  Float_t pprntinit[1000][3];

  tchfQ -> SetBranchAddress("npar2", &npar2);
  tchfQ -> SetBranchAddress("posv2", posv2);
  tchfQ -> SetBranchAddress("ipv2", ipv2);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("iorgprt", iorgprt);
  tchfQ -> SetBranchAddress("iprnttrk", iprnttrk);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
  tchfQ -> SetBranchAddress("pscnd", pscnd);
  tchfQ -> SetBranchAddress("pprntinit", pprntinit);

  ResetNeutrinoEvents();
  SetVECTHisto();

  //Histograms
  DecayeBox decayebox;
  decayebox.SetHistoFrame();

  NeutrinoOscillation neuosc;
  neuosc.SetHistoFrame();
  neuosc.SetHistoFormat();

  Gd1RmuonSelection prmsel;
  prmsel.SetHistoFrame();
  prmsel.SetHistoFormat();

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  DistanceViewer ndistance;
  DistanceMax = 3.;
  ndistance.SetHistoFrame();
  ndistance.SetHistoFormat();


  int Neutrinos_OneDcye = 0;
  int Neutrinos_MuDcye = 0;
  int Neutrinos_PiDcye = 0;
  int Neutrinos_NotCC0Pi = 0;

  int RecoDcyE_CCQE    = 0;
  int RecoDcyE_CCnonQE = 0;
  int RecoDcyE_NC      = 0;

  int NoPrmMuEnd_CCQE = 0;
  int NoPrmMuEnd_CCnonQE = 0;
  int NoPrmMuEnd_NC = 0;

  const int DCYENUM = 1;
  const float DistanceCutThreshold = 0.;

  int CC1PiPlusOther_1TruePiLikeDcyE = 0;
  int CC1PiPlusOther_1TrueMuLikeDcyE = 0;
  int CC1PiPlusOther_1TrueMuLikeDcyE_Decay    = 0;
  int CC1PiPlusOther_1TrueMuLikeDcyE_Abs      = 0;
  int CC1PiPlusOther_1TrueMuLikeDcyE_Hadronic = 0;

  int Num1Rmu             = 0;
  int Num1Rmu_dcydistance = 0;

  int NumCCQE_FCFV    = 0;
  int NumCC2p2h_FCFV  = 0;
  int NumCCOther_FCFV = 0;
  int NumNC_FCFV      = 0;
  float NumOscCCQE_FCFV    = 0.;
  float NumOscCC2p2h_FCFV  = 0.;
  float NumOscCCOther_FCFV = 0.;
  float NumOscNC_FCFV      = 0.;

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
    prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    if (evsel.pass[0]==true) {
      float OscProb = numu->getOscWgt();
      int mode = TMath::Abs(numu->var<int>("mode"));
      if (mode==1) {
        NumCCQE_FCFV++;
        NumOscCCQE_FCFV += OscProb;
      }
      if (mode>=2 && mode<=10) {
        NumCC2p2h_FCFV++;
        NumOscCC2p2h_FCFV += OscProb;
      }
      if (mode>10 && mode<=30) {
        NumCCOther_FCFV++;
        NumOscCCOther_FCFV += OscProb;
      }
      if (mode>=31) {
        NumNC_FCFV++;
        NumOscNC_FCFV += OscProb;
      }
    }

    //New 1R muon selection
    //if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
    if (evsel.pass[0]==true &&
        evsel.pass[1]==true &&
        evsel.pass[2]==true &&
        evsel.pass[3]==true) 
    {
      //GetSelectedModeEvents(numu);     

      // primary particles
      float OscProb = numu->getOscWgt();
      int mode = TMath::Abs(numu->var<int>("mode"));
      float recothetamu = neuosc.GetRecoMuDirection(numu);

      neuosc.GetPrmVtxResolution(numu);
      decayebox.GetDecayeTagPurity(numu, tscnd, pscnd, 20., 50., 400.);

      //# of reconstructed decay-e per event
      int FQDcyE = numu->var<int>("fqnse") - 1;
      int FQDcyE_Box = decayebox.GetDecayeInBox(numu, eMode, eOsc, 20., 50., 400., false);
      int NumCCPi = GetCCPiTopology(numu);

      //Count # of truth decay-e per event
      int NumDcyE = 0;
      for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
        if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
            numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) NumDcyE++;
      }
      if (NumCCPi==1) decayebox.GetTruthDecaye(numu, NumDcyE);

      //# of CC pions (for CC topology)
      //GetNeutrinoInteraction(ientry, mode);
      if (mode>10 && mode<=30) {
        if (FQDcyE_Box==DCYENUM) h1_mode -> Fill(mode);
        if (NumCCPi==0) h1_TaggedDecaye_CCPiTopo[0] -> Fill(FQDcyE_Box);
        if (NumCCPi==1) h1_TaggedDecaye_CCPiTopo[1] -> Fill(FQDcyE_Box);
        if (NumCCPi>1)  h1_TaggedDecaye_CCPiTopo[2] -> Fill(FQDcyE_Box);
      }


      bool  PrmMuEnd = false;
      bool  PiDcy    = false; //This event has a decay-e from pi+?
      bool  PrmMuDcy = false;
      bool  CC0Pi    = false;
      bool  RecoDcyE = false;

      float PrmMuEndVtx[3] = {0., 0., 0.}; //mu end vertex
      float PrmVtx[3]      = {0., 0., 0.}; //primary vertex

      int PiDcySubEvents = 0;  //pi->decay-e events per neutrino events
      int MuDcySubEvents = 0;  //mu->decay-e events per neutrino events
      int OtherSubEvents = 0;  //other events

      //Reconstructed neutrino energy
      float Enu = numu->var<float>("erec");

      int PiLikeDcyE = 0;
      bool AppliedEDistanceCut = false;

#if 1
      //Focus on CC 
      if (mode<31) {
      //if (mode<31 && Enu/1000. >= 0.5 && Enu/1000. <= 0.7) {

        //----- True information -----
        PrmVtx[0] = numu->var<float>("posv", 0);
        PrmVtx[1] = numu->var<float>("posv", 1);
        PrmVtx[2] = numu->var<float>("posv", 2);

        float PrmMuMom[3] = {0., 0., 0.}; //primary mu momentum
        bool PrmMu = decayebox.GetTruePrmMuMom(Pvc, numu, PrmMuMom);
        neuosc.GetPrmMuMomResolution(numu, PrmMuMom);

        //Focus on #decay-e=1
        //(Events with #decay-e>1 will be cut via #decay-e cut)
        if (NumDcyE==1) {

          //Oscillation probability check
          neuosc.OscProbCalculator(numu, true);

          // Get truth mu end vertex
          PrmMuEnd = decayebox.GetTrueMuEndVtx(eOsc, iprntidx, numu, PrmMuEndVtx); //Get truth mu end vertex
          CC0Pi    = decayebox.CC0PiFilter(numu); //Is this event CC0pi?

          /*
          //CCQE & below 200 MeV
          if (mode==1 && !CC0Pi) {
            for (int iprm=0; iprm<numu->var<int>("npar"); iprm++) {
              std::cout << " Particle[" << iprm << "] = " << numu->var<int>("ipv", iprm) << ", pmomv: " << numu->var<float>("pmomv", iprm) << std::endl;
              if (std::fabs(numu->var<int>("ipv", iprm))==static_cast<int>(GEANTPID::MUMINUS)) {
                std::cout << " fill it" << std::endl;
                h1_TrueMuMom -> Fill(numu->var<float>("pmomv", iprm));
              }
            }
          }
          */


          //if (mode>10 && mode<=30 && NumCCPi==1) Neutrinos_OneDcye++;
          if (PrmMuEnd && mode>10 && mode<=30 && NumCCPi==1) Neutrinos_OneDcye++;
          bool piplus = false;
          bool fate_decay    = false;
          bool fate_abs      = false;
          bool fate_hadronic = false;
          float PiPlusMom = 0.;
          for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
            if ( numu->var<int>("Ipvc", iprm)==static_cast<int>(PDGPID::PIPLUS) ) {
              piplus = true;
              PiPlusMom = numu->var<float>("Abspvc", iprm);
              if ( Iflvc[iprm]==3 ) fate_abs      = true;
              if ( Iflvc[iprm]==0 ) fate_hadronic = true;
            }
          }

          for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {

            float PiDcyVtx[3]    = {0., 0., 0.}; //pi+ decay vertex
            float PrmMuDcyVtx[3] = {0., 0., 0.}; //primary mu decay vertex

            //Truth stopping range vs muon momentum
            if (PrmMuEnd) {
              if (PrmMu) {
                float MuMom = std::sqrt( PrmMuMom[0]*PrmMuMom[0] + PrmMuMom[1]*PrmMuMom[1] + PrmMuMom[2]*PrmMuMom[2] );
                ana_TruePrmMuAbsMom = MuMom;
                float d_PrmMuRange = ndistance.TakeDistance(PrmVtx, PrmMuEndVtx);
                h2_TruePmu_x_TrueRange -> Fill(MuMom, d_PrmMuRange/100.);
              }
            }

            PiDcy = decayebox.GetTruePiDcyVtx(eOsc, iscnd, iprntidx, numu, PiDcyVtx);
            if (PrmMuEnd && PiDcy) {
              //if (mode>10 && mode<=30 && NumCCPi==1) std::cout << "---> Pion Decay-e" << std::endl;
              float d_MuEnd_x_PiDcy = ndistance.TakeDistance(PrmMuEndVtx, PiDcyVtx);
              float d_Prm_x_PiDcy   = ndistance.TakeDistance(PrmVtx, PiDcyVtx);
              //h1_truedistance_pidecay -> Fill(d_MuEnd_x_PiDcy/100., OscProb);
              //h1_truedistance_pidecay -> Fill(d_Prm_x_PiDcy/100., OscProb);

              if (mode>10 && mode<=30 && NumCCPi==1) {
                //GetNeutrinoInteraction(ientry, mode);
                h1_truedistance_pidecay -> Fill(d_MuEnd_x_PiDcy/100., OscProb);
                
                if (piplus) {
                  CC1PiPlusOther_1TruePiLikeDcyE++;
                  h1_PiPlusMom_PiDcy -> Fill(PiPlusMom, OscProb);
                  h2_PiPlusMom_x_Enu -> Fill(Enu/1000., PiPlusMom, OscProb);
                }
                
              }

              PiDcySubEvents++;
              Neutrinos_PiDcye++;
            }

            PrmMuDcy = decayebox.GetTruePrmMuDcyVtx(eOsc, iscnd, iprntidx, numu, PrmMuDcyVtx);
            if (PrmMuEnd && PrmMuDcy) {
            //if (PrmMuEnd && PrmMuDcy && !CC0Pi) {
              //if (mode>10 && mode<=30 && NumCCPi==1) std::cout << "---> Muon Decay-e" << std::endl;
              float d_PrmMuEnd_x_PrmMuDcy = ndistance.TakeDistance(PrmMuEndVtx, PrmMuDcyVtx);
              float d_Prm_x_PrmMuDcy      = ndistance.TakeDistance(PrmVtx, PrmMuDcyVtx);
              //h1_truedistance_mudecay -> Fill(d_PrmMuEnd_x_PrmMuDcy/100., OscProb);
              //h1_truedistance_mudecay -> Fill(d_Prm_x_PrmMuDcy/100., OscProb);

              if (mode>10 && mode<=30 && NumCCPi==1) {
                //GetNeutrinoInteraction(ientry, mode);
                h1_truedistance_mudecay -> Fill(d_PrmMuEnd_x_PrmMuDcy/100., OscProb);
                //std::cout << "------- Primary particles ---------" << std::endl;
                for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
                  //std::cout << "Particle[" << iprm << "]=" << numu->var<int>("Ipvc", iprm)
                  //                                         << ", Iflvc=" << Iflvc[iprm] 
                  //                                         << ", Ichvc=" << numu->var<int>("Ichvc", iprm)
                  //                                         << ", Iorgvc=" << Iorgvc[iprm] << std::endl;
                  //if (std::fabs(numu->var<int>("Ipvc", iprm))==static_cast<int>(PDGPID::PIPLUS)) {
                  if ( numu->var<int>("Ipvc", iprm)==static_cast<int>(PDGPID::PIPLUS) ) {
                    piplus = true;
                    //std::cout << "  Muon Decay-e, PiPlus (Fate: " << Iflvc[iprm] << " )" << std::endl;
                    //float PiPlusMom = numu->var<float>("Abspvc", iprm);
                    ana_mode = Iflvc[iprm];
                    //h1_PiPlusMom -> Fill(PiPlusMom);
                    //std::cout << "  Fill PiPlus Mom: " << PiPlusMom << " MeV" << std::endl;
                  }
                }
                if (piplus) {
                  CC1PiPlusOther_1TrueMuLikeDcyE++;
                  if (fate_abs) {
                    CC1PiPlusOther_1TrueMuLikeDcyE_Abs++;
                    h1_PiPlusMom_PiAbs -> Fill(PiPlusMom, OscProb);
                    h2_PiPlusMom_x_Enu -> Fill(Enu/1000., PiPlusMom, OscProb);
                  }
                  if (fate_hadronic) {
                    CC1PiPlusOther_1TrueMuLikeDcyE_Hadronic++;
                    h1_PiPlusMom_PiHad -> Fill(PiPlusMom, OscProb);
                    h2_PiPlusMom_x_Enu -> Fill(Enu/1000., PiPlusMom, OscProb);
                  }
                }


                int piplusfate = 0;
                std::vector<int> PiDaughterList;
                //std::cout << "------- Secondary particles ---------" << std::endl;
                for (int jscnd=0; jscnd<numu->var<int>("nscndprt"); jscnd++) {
                  //std::cout << "Particle[" << jscnd << "]=" << numu->var<int>("iprtscnd", jscnd)
                  //          << ", iprntprt=" << numu->var<int>("iprntprt", jscnd)
                  //          << ", iprntidx=" << iprntidx[jscnd]  
                  //          << ", lmecscnd=" << numu->var<int>("lmecscnd", jscnd) << std::endl;
                  if (std::fabs(numu->var<int>("iprntprt", jscnd))==static_cast<int>(PDGPID::PIPLUS)) {
                    //std::cout << "  PiPlus -> " << numu->var<int>("iprtscnd", jscnd) << std::endl;
                    piplusfate++;

                    if (PiDaughterList.size()==0) {
                      PiDaughterList.push_back(numu->var<int>("iprtscnd", jscnd));
                      h1_PiPlusFate -> Fill(std::fabs(numu->var<int>("iprtscnd", jscnd)));
                    }
                    else {
                      bool NewDaughter = false;
                      int listcheck = 0;
                      for (UInt_t ipi=0; ipi<PiDaughterList.size(); ipi++) {
                        if (PiDaughterList.at(ipi)!=numu->var<int>("iprtscnd", jscnd)) listcheck++;
                      }
                      if (listcheck==PiDaughterList.size()) {
                        PiDaughterList.push_back(numu->var<int>("iprtscnd", jscnd));
                        h1_PiPlusFate -> Fill(std::fabs(numu->var<int>("iprtscnd", jscnd)));
                      }
                    }
                    
                  }
                }
                if (piplusfate==0) {
                  //std::cout << "  PiPlus -> Nothing." << std::endl;
                  h1_PiPlusFate -> Fill(0);
                }
              }

              MuDcySubEvents++;
              Neutrinos_MuDcye++;
            }
          }
          if (PiDcySubEvents==0 && MuDcySubEvents==0) {
            /*if (mode>10 && mode<=30 && NumCCPi==1 && PrmMuEnd) {
              std::cout << "---> OtherSubEvents" << std::endl;
              GetNeutrinoInteraction(ientry, mode);
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

            if (PrmMuEnd && CC0Pi) {
              Neutrinos_NotCC0Pi++;
              //std::cout << " (Not CC0PI) " << std::endl;
            }
            //else if (!PrmMuEnd) std::cout << " (Mu end vertex was not found) " << std::endl;
            //else std::cout << " (Others) " << std::endl;
            OtherSubEvents++;
          }
          /*if (mode>10 && mode<=30 && NumCCPi==1 && PrmMuEnd) {
            std::cout << "[### " << ientry << " ###]  PiDcyE: " << PiDcySubEvents 
                      << ", PrmMuDcyE: " << MuDcySubEvents 
                      << ", OtherSubEvents: " << OtherSubEvents 
                      << ", Total: " << PiDcySubEvents+MuDcySubEvents+OtherSubEvents << std::endl;
            std::cout << " " << std::endl;
          }*/
        }


        //----- Reconstrued information -----
        //Energy distributon (C1-C4 + decay-e cut)
        //if (FQDcyE_Box==DCYENUM) {
        if (FQDcyE_Box<=DCYENUM) {
          if (prmsel.C6Applynotpionlike(evsel)) {
            if (mode==1) h1_Erec[0] -> Fill(Enu/1000., OscProb);
            if (mode>=2 && mode<=10) h1_Erec[1] -> Fill(Enu/1000., OscProb);
            if (mode>10 && mode<=30) h1_Erec[2] -> Fill(Enu/1000., OscProb);
            if (mode==11 || mode==12 || mode==13) h1_Erec[4] -> Fill(Enu/1000., OscProb);
            if (mode>13 && mode<=30) h1_Erec[5] -> Fill(Enu/1000., OscProb);
          }
        }

        //Energy distributon (C1-C4)
        //if (mode==1) h1_Erec[0] -> Fill(Enu/1000., OscProb);
        //if (mode>=2 && mode<=10) h1_Erec[1] -> Fill(Enu/1000., OscProb);
        //if (mode>10 && mode<=30) h1_Erec[2] -> Fill(Enu/1000., OscProb);
      }
      if (mode>=31) {
        //Energy distribution (C1-C4)
        //h1_Erec[3] -> Fill(Enu/1000.);

        //Energy distributon (C1-C4 + decay-e cut)
        //if (FQDcyE_Box==DCYENUM) h1_Erec[3] -> Fill(Enu/1000.);
        if (FQDcyE_Box<=DCYENUM) {
          if (prmsel.C6Applynotpionlike(evsel)) {
            h1_Erec[3] -> Fill(Enu/1000.);
          }
        }
      }
      //std::cout << " " << std::endl;


      if (FQDcyE_Box==DCYENUM) {
        
        //GetNeutrinoInteraction(ientry, mode);
        PrmMuEnd = decayebox.GetTrueMuEndVtx(eOsc, iprntidx, numu, PrmMuEndVtx); //Get truth mu end vertex
        float RecoMuEndVtx[3] = {0., 0., 0.};
        float RecoMuRange = decayebox.GetRecoMuEndVtx(numu, RecoMuEndVtx);
        float d_MuEndVtxReso = ndistance.TakeDistance(PrmMuEndVtx, RecoMuEndVtx);
        float OrgnVtx[3] = {0., 0., 0.};
        float d_TrueMuEndVtx = ndistance.TakeDistance(OrgnVtx, PrmMuEndVtx);
        float d_RecoMuEndVtx = ndistance.TakeDistance(OrgnVtx, RecoMuEndVtx);
        float Pmu = numu->var<float>("fq1rmom", 0, FQ_MUHYP); //primary muon momentum
        float RecoPrmVtx[3] = {0., 0., 0.};
        RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
        RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
        RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);
        float RecoMuDir[3] = {0., 0., 0.};
        RecoMuDir[0]  = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 0);
        RecoMuDir[1]  = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 1);
        RecoMuDir[2]  = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 2);
        if (PrmMuEnd) {
          h2_RecoPmu_x_RecoRange -> Fill(Pmu, RecoMuRange/100.);
          h1_PrmMuEndVtxReso -> Fill(d_MuEndVtxReso);
          h2_PrmMuEndVtxReso -> Fill(d_TrueMuEndVtx, d_RecoMuEndVtx);
          for (int idim=0; idim<3; idim++) {
            ana_RecoMuEndVtx[idim] = RecoMuEndVtx[idim];
            ana_TrueMuEndVtx[idim] = PrmMuEndVtx[idim];
          }
        }

        if (!PrmMuEnd) {
          //std::cout << "[### " << ientry << " ###] !!! Primary muon does not stop !!!" << std::endl;
          //GetNeutrinoInteraction(ientry, mode);

          //h2_PrmVtx_XY -> Fill(PrmVtx[0]/100., PrmVtx[1]/100.);
          //h2_PrmVtx_RZ -> Fill((PrmVtx[0]*PrmVtx[0]+PrmVtx[1]*PrmVtx[1])/10000., PrmVtx[2]/100.);
          for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {

            if (std::fabs(numu->var<int>("Ipvc", iprm))==static_cast<int>(PDGPID::MUON)) {
              //std::cout << " ---> Mu Momentum: " << numu->var<float>("Abspvc", iprm) << " MeV" << std::endl;
              if (mode==1) h1_TrueMuMom[0] -> Fill(numu->var<float>("Abspvc", iprm));
              if (mode>=2 && mode<=30) h1_TrueMuMom[1] -> Fill(numu->var<float>("Abspvc", iprm));
              if (mode>=31) h1_TrueMuMom[2] -> Fill(numu->var<float>("Abspvc", iprm));
            }

            if (std::fabs(numu->var<int>("Ipvc", iprm))==static_cast<int>(PDGPID::PIPLUS) ||
                numu->var<int>("Ipvc", iprm)==static_cast<int>(PDGPID::PI0)) 
            {
              //std::cout << " ---> Pi Momentum: " << numu->var<float>("Abspvc", iprm) << " MeV" << std::endl;
              if (mode==1) h1_TruePiMom[0] -> Fill(numu->var<float>("Abspvc", iprm));
              if (mode>=2 && mode<=30) h1_TruePiMom[1] -> Fill(numu->var<float>("Abspvc", iprm));
              if (mode>=31) h1_TruePiMom[2] -> Fill(numu->var<float>("Abspvc", iprm));
            }
          }

          if (mode==1) NoPrmMuEnd_CCQE++;
          if (mode>=2 && mode<=30) NoPrmMuEnd_CCnonQE++;
          if (mode>=31) NoPrmMuEnd_NC++;
        }

        // Get the reco decay-e generation vertex
        //std::cout << "PiDcySubEvents:MuDcySubEvents = ["  << PiDcySubEvents << " : " << MuDcySubEvents << "]" << std::endl;
        //GetSelectedModeEvents(numu);

        for (int iscnd=1; iscnd<numu->var<int>("fqnse"); iscnd++) {

          float RecoDcyEVtx[3] = {0., 0., 0.}; //fiTQun decay-e generation vertex

          RecoDcyE = decayebox.GetRecoDcyEGenVtx(iscnd, numu, RecoDcyEVtx);
          if (PrmMuEnd && RecoDcyE) {
          //if (PrmMuEnd && RecoDcyE && Enu/1000. <= 1.) {
          //if (PrmMuEnd && RecoDcyE && Enu/1000. > 1.) {
          //if (PrmMuEnd && RecoDcyE && Pmu/1000. <= 0.7) {
          //if (PrmMuEnd && RecoDcyE && Pmu/1000. > 0.7) {
            float Pdcye = numu->var<float>("fq1rmom", iscnd, FQ_EHYP); // decay-e momentum

            //std::cout << "[### " << ientry << " ###] fiTQun decay-e vertex" << std::endl;
            float d_MuEnd_x_fQDcyE = ndistance.TakeDistance(PrmMuEndVtx, RecoDcyEVtx);
            //float d_MuEnd_x_fQDcyE = ndistance.TakeTransversalDistance(RecoMuDir, RecoPrmVtx, RecoDcyEVtx);

            ////// 1:1 labeling ///////
            //Mu-induced decay-e
            if (MuDcySubEvents==1) {
              //if (mode<=30) h1_TruePrmMuEnd_x_fQDcyE_MuDcy -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
              //if (mode>=31) h1_TruePrmMuEnd_x_fQDcyE_MuDcy -> Fill(d_MuEnd_x_fQDcyE/100.);
              if (mode>10 && mode<=30 && NumCCPi==1) h1_TruePrmMuEnd_x_fQDcyE_MuDcy -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            }
            //Pi-induced decay-e
            if (PiDcySubEvents==1) {
              //ana_mode = mode;
              //if (mode<=30) h1_TruePrmMuEnd_x_fQDcyE_PiDcy -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
              //if (mode>=31) h1_TruePrmMuEnd_x_fQDcyE_PiDcy -> Fill(d_MuEnd_x_fQDcyE/100.);
              if (mode>10 && mode<=30 && NumCCPi==1) h1_TruePrmMuEnd_x_fQDcyE_PiDcy -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            }

            GetSelectedModeEvents(numu);
            if (mode==1) h1_TruePrmMuEnd_x_fQDcyE[0] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (mode>=2 && mode<=10) h1_TruePrmMuEnd_x_fQDcyE[1] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (mode>10 && mode<=30) h1_TruePrmMuEnd_x_fQDcyE[2] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            if (mode>10 && mode<=30) {
              //ana_mode = mode;
              if (NumCCPi==0) h1_TruePrmMuEnd_x_fQDcyE[4] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
              if (NumCCPi==1) h1_TruePrmMuEnd_x_fQDcyE[5] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
              if (NumCCPi>1)  h1_TruePrmMuEnd_x_fQDcyE[6] -> Fill(d_MuEnd_x_fQDcyE/100., OscProb);
            }
            if (mode>=31) h1_TruePrmMuEnd_x_fQDcyE[3] -> Fill(d_MuEnd_x_fQDcyE/100.);
            h2_TruePrmMuEnd_x_fQDcyE_x_Pmu -> Fill(Pmu/1000., d_MuEnd_x_fQDcyE/100., OscProb);
            h2_TruePrmMuEnd_x_fQDcyE_x_Enu -> Fill(Enu/1000., d_MuEnd_x_fQDcyE/100., OscProb);

            //Energy distributon
            //if (mode==1) h1_Erec[0] -> Fill(Enu/1000., OscProb);
            //if (mode>=2 && mode<=10) h1_Erec[1] -> Fill(Enu/1000., OscProb);
            //if (mode>10 && mode<=30) h1_Erec[2] -> Fill(Enu/1000., OscProb);


            ///////// Cut Implementation //////////
            if (d_MuEnd_x_fQDcyE/100. > DistanceCutThreshold) PiLikeDcyE++;
            AppliedEDistanceCut = true;
          }
        }
      }
#endif


      //==== Present sample definition ====
      if (FQDcyE_Box<=1 && prmsel.C6Applynotpionlike(evsel))  {
        Num1Rmu++;
        //neuosc.GetWgtNeutrino(numu, recothetamu, thetamin, thetamax);
      }

      //===== Sample definition with distance cut =====
      //Distance cut is available (mainly CC)
      if (AppliedEDistanceCut) {
        if ( FQDcyE_Box==0 || (FQDcyE_Box==1 && PiLikeDcyE==0) ) {
          if (prmsel.C6Applynotpionlike(evsel)) {
            Num1Rmu_dcydistance++;
            neuosc.GetWgtNeutrino(numu, recothetamu, thetamin, thetamax);
          }
        }
      }
      //Distance cut is non-available (mainly NC)
      else {
        if ( FQDcyE_Box<=1 ) {
          if (prmsel.C6Applynotpionlike(evsel)) {
            Num1Rmu_dcydistance++;
            neuosc.GetWgtNeutrino(numu, recothetamu, thetamin, thetamax);
          }
        }
      }



#if 0
      //Focus on CC (#decay-e <= 1)
      //CC events with #decay-e>1 will be cut via #decay-e cut
      //if (mode<31 && NumDcyE<=1) {
      if (mode<31) {

        //If #decay-e=1, check whether this decay-e is originated from pi+ or not
        if (NumDcyE==1) {
        //if (NumDcyE>=0) {

          Neutrinos_OneDcye++;

          //Find decay-e from pi+
          //vtxscnd of this decay-e is pi+ decay vertex 
          for (int iscnd=0; iscnd<nscndprt; iscnd++) {
            if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
                std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))==static_cast<int>(PDGPID::PIPLUS) &&
                numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) 
            {
              PiDcy = true;
              PiDcyVtx[0] = vtxscnd[iscnd][0];
              PiDcyVtx[1] = vtxscnd[iscnd][1];
              PiDcyVtx[2] = vtxscnd[iscnd][2];
            }
          }


          //If this neutrino event has a decay-e from pi+, primary mu does not emit decay-e
          //If so, find muon capture vertex
          if (PiDcy) {
            //GetNeutrinoInteraction(ientry, mode);
            //std::cout << "------  CONVVECT secondary info  ------" << std::endl;
            for (int iscnd=0; iscnd<nscndprt; iscnd++) {
              //std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << numu->var<int>("iprtscnd", iscnd)[iscnd]
              //                     << ", iprntprt=" << numu->var<int>("iprntprt", iscnd)[iscnd]
              //                     << ", iprntidx=" << iprntidx[iscnd] 
              //                     << ", ichildidx=" << ichildidx[iscnd] 
              //                     << ", lmecscnd=" << numu->var<int>("lmecscnd", iscnd)[iscnd] 
              //                     << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " 
              //                     << vtxscnd[iscnd][1] << ", " 
              //                     << vtxscnd[iscnd][2] << "]" << std::endl;
              
              if (numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::NEUTRON) &&
                  numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::MUON) &&
                  numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) 
              {
                MuCap = true;
                MuCapVtx[0] = vtxscnd[iscnd][0];
                MuCapVtx[1] = vtxscnd[iscnd][1];
                MuCapVtx[2] = vtxscnd[iscnd][2];
              }
            }
          }
          //If this neutrino event has a decay-e from mu, this mu emits decay-e
          //If so, find muon decay vertex
          else {
            //GetNeutrinoInteraction(ientry, mode);
            //std::cout << "------  CONVVECT secondary info  ------" << std::endl;
            for (int iscnd=0; iscnd<nscndprt; iscnd++) {
              //std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << numu->var<int>("iprtscnd", iscnd)[iscnd]
              //                     << ", iprntprt=" << numu->var<int>("iprntprt", iscnd)[iscnd]
              //                     << ", iprntidx=" << iprntidx[iscnd] 
              //                     << ", ichildidx=" << ichildidx[iscnd] 
              //                     << ", lmecscnd=" << numu->var<int>("lmecscnd", iscnd)[iscnd] 
              //                     << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " 
              //                     << vtxscnd[iscnd][1] << ", " 
              //                     << vtxscnd[iscnd][2] << "]" << std::endl;

              if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) &&
                  std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) &&
                  numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) 
              {
                MuDcy = true;
                MuStpVtx[0] = vtxscnd[iscnd][0];
                MuStpVtx[1] = vtxscnd[iscnd][1];
                MuStpVtx[2] = vtxscnd[iscnd][2];

                MuDcyVtx[0] = vtxscnd[iscnd][0];
                MuDcyVtx[1] = vtxscnd[iscnd][1];
                MuDcyVtx[2] = vtxscnd[iscnd][2];
              }

              //If pi decays to other particles(not electron i.e. CC1pi), 
              if (( numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::PROTON) || 
                    numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::NEUTRON) ) &&
                  std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::PIPLUS) &&
                  ( numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY) || 
                    numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::HADRONIC) || 
                    numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::HADRONIC_ELASTIC_COH) ) ) 
              {
                OtherPiDcy = true;
              }
            }
          }

        }
        //If #decay-e=0, fill the #decay-e
        else {
          //CCQE
          if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
          //CC 2p2h
          if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
          //CC RES (Delta+)
          if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
          //CC RES (Delta++)
          if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
          //CC RES (Delta0)
          if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
          //CC other
          if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
        }
      }

      //CC events with more than two decay-e
      if (mode<31 && NumDcyE>=2) {
        //CCQE
        if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
        //CC 2p2h
        if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
        //CC RES (Delta+)
        if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
        //CC RES (Delta++)
        if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
        //CC RES (Delta0)
        if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
        //CC other
        if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
      }

      //NC events
      if (mode>=31) h1_TrueDecaye_vtx[2] -> Fill(NumDcyE);


      //std::cout << "PiDcy:MuCap:MuDcy = " << PiDcy << ":" << MuCap << ":" << MuDcy << std::endl;

#if 0
      //CC non-QE w/ one decay-e from pi
      //Check the behavior of mu
      if ((mode>10 && mode<=30) && PiDcy && !MuCap) {
        GetNeutrinoInteraction(ientry, mode);
        std::cout << "------  NEUT primary info  ------" << std::endl;
        for (int iprm=0; iprm<Npvc; iprm++) {
          std::cout << "[### " << ientry << " ###] Particle[" << iprm << "]=" << Ipvc[iprm]
                                         << ", Iflvc=" << Iflvc[iprm] 
                                         << ", Ichvc=" << Ichvc[iprm]
                                         << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
        }

        std::cout << "------  CONVVECT secondary info  ------" << std::endl;
        for (int iscnd=0; iscnd<nscndprt; iscnd++) {
          std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << numu->var<int>("iprtscnd", iscnd)[iscnd]
                               << ", iprntprt=" << numu->var<int>("iprntprt", iscnd)[iscnd]
                               << ", iprntidx=" << iprntidx[iscnd] 
                               << ", ichildidx=" << ichildidx[iscnd] 
                               << ", lmecscnd=" << numu->var<int>("lmecscnd", iscnd)[iscnd] << std::endl;
        }
        std::cout << " " << std::endl;      
      }
#endif

#if 0
      //CC non-QE w/ one decay-e from mu
      //Check the behavior of pions
      if ((mode>10 && mode<=30) && MuDcy) {
        GetNeutrinoInteraction(ientry, mode);
        std::cout << "------  NEUT primary info  ------" << std::endl;
        for (int iprm=0; iprm<Npvc; iprm++) {
          std::cout << "[### " << ientry << " ###] Particle[" << iprm << "]=" << Ipvc[iprm]
                                         << ", Iflvc=" << Iflvc[iprm] 
                                         << ", Ichvc=" << Ichvc[iprm]
                                         << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
          //Check pi fate if MC does not chase it
          if ((std::fabs(Ipvc[iprm])==static_cast<int>(PDGPID::PIPLUS) || 
              Ipvc[iprm]==static_cast<int>(PDGPID::PI0)) &&
              Ichvc[iprm]==0) 
          {
            h1_Iflvc -> Fill(Iflvc[iprm]);
          }
          //Check pi daughters in primary list
          if ((std::fabs(Ipvc[ Iorgvc[iprm]-1 ])==static_cast<int>(PDGPID::PIPLUS) || 
              Ipvc[ Iorgvc[iprm]-1 ]==static_cast<int>(PDGPID::PI0))) 
          {
            h1_Ipvc -> Fill(Ipvc[iprm]);
          }
        }

        std::cout << "------  CONVVECT secondary info  ------" << std::endl;
        for (int iscnd=0; iscnd<nscndprt; iscnd++) {
          std::cout << "[### " << ientry << " ###] Particle[" << iscnd << "]=" << numu->var<int>("iprtscnd", iscnd)[iscnd]
                               << ", iprntprt=" << numu->var<int>("iprntprt", iscnd)[iscnd]
                               << ", iprntidx=" << iprntidx[iscnd] 
                               << ", ichildidx=" << ichildidx[iscnd] 
                               << ", lmecscnd=" << numu->var<int>("lmecscnd", iscnd)[iscnd] 
                               << ", vtxscnd=[" << vtxscnd[iscnd][0] << ", " 
                               << vtxscnd[iscnd][1] << ", " 
                               << vtxscnd[iscnd][2] << "]" << std::endl;
          //Check pi daughters in secondary list
          if (std::fabs(numu->var<int>("iprntprt", iscnd)[iscnd])==static_cast<int>(PDGPID::PIPLUS) || 
              numu->var<int>("iprntprt", iscnd)[iscnd]==static_cast<int>(PDGPID::PI0)) 
          {
            h1_iprtscnd -> Fill(numu->var<int>("iprtscnd", iscnd)[iscnd]);
          }
        }
        std::cout << " " << std::endl;
      }
#endif

      //CASE1: Pi+ decays to a decay-e, and mu is captured
      if (PiDcy && MuCap) {
        Neutrinos_PiDcy_x_MuCap++;
        float d_MuCap_x_PiDcy_x = MuCapVtx[0] - PiDcyVtx[0];
        float d_MuCap_x_PiDcy_y = MuCapVtx[1] - PiDcyVtx[1];
        float d_MuCap_x_PiDcy_z = MuCapVtx[2] - PiDcyVtx[2];
        float d_MuCap_x_PiDcy   = std::sqrt( d_MuCap_x_PiDcy_x*d_MuCap_x_PiDcy_x +
                                             d_MuCap_x_PiDcy_y*d_MuCap_x_PiDcy_y +
                                             d_MuCap_x_PiDcy_z*d_MuCap_x_PiDcy_z );
        //h1_truedistance_pidecay -> Fill(d_MuCap_x_PiDcy/100.);
        h1_truedistance_pidecay -> Fill(d_MuCap_x_PiDcy/100., OscProb);

        //Vertex cut
        //if (d_MuCap_x_PiDcy/100. < 999.) {
        if (d_MuCap_x_PiDcy/100. < 0.1) {
          //This is decay-e from pi+(bkg) passed the vtx cut, so fill the #decay-e
          //CCQE
          if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
          //CC 2p2h
          if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
          //CC RES (Delta+)
          if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
          //CC RES (Delta++)
          if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
          //CC RES (Delta0)
          if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
          //CC other
          if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
        }
      }
      if (PiDcy && !MuCap) {
        //This is decay-e from pi+(bkg) passed the vtx cut, so fill the #decay-e
        //CCQE
        if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
        //CC 2p2h
        if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
        //CC RES (Delta+)
        if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
        //CC RES (Delta++)
        if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
        //CC RES (Delta0)
        if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
        //CC other
        if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
      }
      if (OtherPiDcy) {
        //This is pi+(bkg), so fill the #decay-e
        //CCQE
        if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
        //CC 2p2h
        if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
        //CC RES (Delta+)
        if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
        //CC RES (Delta++)
        if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
        //CC RES (Delta0)
        if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
        //CC other
        if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
      }

      //CASE2: mu decays to a electron
      //if (MuDcy) {
      if (MuDcy && !OtherPiDcy) {
        //Neutrinos_MuDcy++;
        float d_MuStp_x_MuDcy_x = MuStpVtx[0] - MuDcyVtx[0];
        float d_MuStp_x_MuDcy_y = MuStpVtx[1] - MuDcyVtx[1];
        float d_MuStp_x_MuDcy_z = MuStpVtx[2] - MuDcyVtx[2];
        float d_MuStp_x_MuDcy   = std::sqrt( d_MuStp_x_MuDcy_x*d_MuStp_x_MuDcy_x +
                                             d_MuStp_x_MuDcy_y*d_MuStp_x_MuDcy_y +
                                             d_MuStp_x_MuDcy_z*d_MuStp_x_MuDcy_z );
        //h1_truedistance_mudecay -> Fill(d_MuStp_x_MuDcy/100.);
        h1_truedistance_mudecay -> Fill(d_MuStp_x_MuDcy/100., OscProb);

        //This is decay-e from mu(signal), so fill the #decay-e
        //CCQE
        if (mode==1) h1_TrueDecaye_vtx[0] -> Fill(NumDcyE);
        //CC 2p2h
        if (mode>=2 && mode<=10) h1_TrueDecaye_vtx[1] -> Fill(NumDcyE);
        //CC RES (Delta+)
        if (mode==13) h1_TrueDecaye_vtx[3] -> Fill(NumDcyE);
        //CC RES (Delta++)
        if (mode==11) h1_TrueDecaye_vtx[4] -> Fill(NumDcyE);
        //CC RES (Delta0)
        if (mode==12) h1_TrueDecaye_vtx[5] -> Fill(NumDcyE);
        //CC other
        if (mode>10 && mode<=30) h1_TrueDecaye_vtx[6] -> Fill(NumDcyE);
      }
#endif

    } //1R mu selection
    AnaTuple -> FillAnaTree();
  } //Event loop


  std::cout << "Stopped primary muon: " << Neutrinos_OneDcye << std::endl;
  std::cout << "No mu stop CCQE   : " << NoPrmMuEnd_CCQE << std::endl;
  std::cout << "No mu stop CCnonQE: " << NoPrmMuEnd_CCnonQE << std::endl;
  std::cout << "No mu stop NC     : " << NoPrmMuEnd_NC << std::endl;
  std::cout << "Found Decay-e vertex(CCQE)   : " << DcyE_CCQE    << std::endl;
  std::cout << "Found Decay-e vertex(CC2p2h) : " << DcyE_CC2p2h  << std::endl;
  std::cout << "Found Decay-e vertex(CCnonQE): " << DcyE_CCnonQE << std::endl;
  std::cout << "Found Decay-e vertex(NC).    : " << DcyE_NC      << std::endl;

  std::cout << "--- Box cut performance ---" << std::endl;
  std::cout << " All truth decay-e                : " << AllTrueDcye   << std::endl;
  std::cout << " All fiTQun decay-e               : " << AllfQdcye     << std::endl;
  std::cout << " fiTQun decya-e in the box        : " << BoxfQdcye     << std::endl;
  std::cout << " Matched fiTQun decya-e in the box: " << MatchedfQdcye << std::endl;

  std::cout << "Generated CCQE events   : " << SelectedCCQEevents    << std::endl;
  std::cout << "Generated CCnonQE events: " << SelectedCCnonQEevents << std::endl;
  std::cout << "Generated NC events     : " << SelectedNCevents      << std::endl;

  std::cout << "  CC-Other, 1pi+, #true decay-e = 1(mu): " << CC1PiPlusOther_1TrueMuLikeDcyE << std::endl;
  std::cout << "    Absorption: " << CC1PiPlusOther_1TrueMuLikeDcyE_Abs << std::endl;
  std::cout << "    Hadronic  : " << CC1PiPlusOther_1TrueMuLikeDcyE_Hadronic << std::endl;
  std::cout << "  CC-Other, 1pi+, #true decay-e = 1(pi): " << CC1PiPlusOther_1TruePiLikeDcyE << std::endl;

  std::cout << "1Rmu events          : " << Num1Rmu << std::endl;
  std::cout << "Redefined 1Rmu events: " << Num1Rmu_dcydistance << std::endl;
  std::cout << "CCQE events after FCFV   : " << NumCCQE_FCFV << " (osc: " << NumOscCCQE_FCFV << ")" << std::endl;
  std::cout << "CC2p2h events after FCFV : " << NumCC2p2h_FCFV << " (osc: " << NumOscCC2p2h_FCFV << ")" << std::endl;
  std::cout << "CCOther events after FCFV: " << NumCCOther_FCFV << " (osc: " << NumOscCCOther_FCFV << ")" << std::endl;
  std::cout << "NC events after FCFV     : " << NumNC_FCFV << " (osc: " << NumOscNC_FCFV << ")" << std::endl;



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
    resultfile << "Generated CCQE events   : " << SelectedCCQEevents    << std::endl;
    resultfile << "Generated CC2p2h events : " << SelectedCC2p2hevents  << std::endl;
    resultfile << "Generated CCnonQE events: " << SelectedCCnonQEevents << std::endl;
    resultfile << "Generated NC events     : " << SelectedNCevents      << std::endl;
    resultfile << " " << std::endl;

    resultfile << "1Rmu events          : " << Num1Rmu << std::endl;
    resultfile << "Redefined 1Rmu events: " << Num1Rmu_dcydistance << std::endl;
    resultfile << "CCQE events after FCFV   : " << NumCCQE_FCFV << " (osc: " << NumOscCCQE_FCFV << ")" << std::endl;
    resultfile << "CC2p2h events after FCFV : " << NumCC2p2h_FCFV << " (osc: " << NumOscCC2p2h_FCFV << ")" << std::endl;
    resultfile << "CCOther events after FCFV: " << NumCCOther_FCFV << " (osc: " << NumOscCCOther_FCFV << ")" << std::endl;
    resultfile << "NC events after FCFV     : " << NumNC_FCFV << " (osc: " << NumOscNC_FCFV << ")" << std::endl;
    resultfile << " " << std::endl;

    float TotalEventsNoNeutronAnalysis = OscillatedCCQE 
                                       + OscillatedCCnonQE 
                                       + OscillatedCCRESp
                                       + OscillatedCCRESpp
                                       + OscillatedCCRES0
                                       + OscillatedCCOther
                                       + OscillatedNC;
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
    resultfile << "[Neutrino] Oscillated CCQE Events     : " << OscillatedCCQE  << std::endl;
    resultfile << "           w/ tagged neutrons         : " << OscillatedCCQE_wTagN << ", w/o tagged neutrons:" << OscillatedCCQE_woTagN << std::endl;
    resultfile << " " << std::endl;
    resultfile << "[Neutrino] Oscillated CC(2p2h) Events : " << OscillatedCCnonQE << std::endl;
    resultfile << "           w/ tagged neutrons         : " << OscillatedCCnonQE_wTagN << ", w/o tagged neutrons:" << OscillatedCCnonQE_woTagN << std::endl;
    resultfile << " " << std::endl;
    resultfile << "[Neutrino] Oscillated All CCRES Events: " << OscillatedCCRES0 + OscillatedCCRESp + OscillatedCCRESpp << std::endl;
    resultfile << "           w/ tagged neutrons         : " << OscillatedCCRES0_wTagN  + OscillatedCCRESp_wTagN  + OscillatedCCRESpp_wTagN 
               << ", w/o tagged neutrons:" << OscillatedCCRES0_woTagN  + OscillatedCCRESp_woTagN  + OscillatedCCRESpp_woTagN << std::endl;
    resultfile << " " << std::endl;
    resultfile << "[Neutrino] Oscillated CC Other Events : " << OscillatedCCOther << std::endl;
    resultfile << "           w/ tagged neutrons         : " << OscillatedCCOther_wTagN << ", w/o tagged neutrons:" << OscillatedCCOther_woTagN << std::endl;
    resultfile << " " << std::endl;
    resultfile << "[Neutrino] NC Events                  : " << OscillatedNC << std::endl;
    resultfile << "           w/ tagged neutrons         : " << OscillatedNC_wTagN << ", w/o tagged neutrons:" << OscillatedNC_woTagN << std::endl;
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

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

  ndistance.cdDistanceViewer(fout);
  ndistance.WritePlots();
  gDirectory -> cd("..");

  WriteVECTHisto();

  AnaTuple -> WriteAnaTree();

}