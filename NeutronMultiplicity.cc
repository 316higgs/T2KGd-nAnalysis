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


  //=========  fiTQun output (TTree: h1)  ============
  TChain *tchfQ = new TChain("h1");
  int nfQFiles = tchfQ->Add( fiTQunFileName );
  if ( nfQFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree h1 from: \e[0m" << fiTQunFileName << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: event)  ============
  TChain *tchev = new TChain("event");
  int nevFiles = tchev->Add( NtagFileName );
  if ( nevFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree event from: \e[0m" << NtagFileName << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Event info (TTree: particle)  ============
  TChain *tchpar = new TChain("particle");
  int nparFiles = tchpar->Add( NtagFileName );
  if ( nparFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree particle from: \e[0m" << NtagFileName << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  Delayed info (TTree: taggable)  ============
  TChain *tchtaggable = new TChain("taggable");
  int ntaggableFiles = tchtaggable->Add( NtagFileName );
  if ( ntaggableFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree taggable from: \e[0m" << NtagFileName << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //=========  NTag output (TTree: ntag)  ============
  TChain *tchntag = new TChain("ntag");
  int ntagFiles = tchntag->Add( NtagFileName );
  if ( ntagFiles==0 ) {
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Cannot load TTree ntag from: \e[0m" << NtagFileName << std::endl;
    std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  -> EXIT \e[0m" << std::endl;
    exit(-1);
  }
  //Load succeed
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nfQFiles       << " files from: \e[0m" << fiTQunFileName << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nevFiles       << " files from: \e[0m" << NtagFileName   << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << nparFiles      << " files from: \e[0m" << NtagFileName   << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << ntaggableFiles << " files from: \e[0m" << NtagFileName   << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: \e[0m" << NtagFileName   << std::endl;


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
  std::vector<float> *dvx = 0;
  TBranch *bdvx = 0;
  std::vector<float> *dvy = 0;
  TBranch *bdvy = 0;
  std::vector<float> *dvz = 0;
  TBranch *bdvz = 0;
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("DWall", &TagDWall, &bTagDWall);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);
  tchntag->SetBranchAddress("dvx", &dvx, &bdvx);
  tchntag->SetBranchAddress("dvy", &dvy, &bdvy);
  tchntag->SetBranchAddress("dvz", &dvz, &bdvz);

  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  tchfQ -> SetBranchAddress("pscnd", pscnd);

  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu? ======
  Float_t Pvc[100][3];      //Momentum of primary particles
  Int_t   Iflvc[100];       //Flag of final states
  Int_t   Iorgvc[100];      //Index of parent particle (0: initial particles, n: n-th final particle at the primary interaction)
  Float_t tscnd[1000];
  Float_t vtxscnd[1000][3]; //Generated vertex of secondary particles
  Float_t vtxprnt[1000][3];
  Int_t   iprntidx[1000];   //Index of the parent particle (0: no parent(connected from primary particles), n: the parent of n-th secondary particle)
  Int_t   ichildidx[1000];  //Index of the first child particle (0: no childs, n: the first child of n-th secondary particle)
  Int_t   itrkscnd[1000];
  Float_t pprntinit[1000][3]; //Initial momentum of the parent particle at birth
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("vtxprnt", vtxprnt);
  tchfQ -> SetBranchAddress("iprntidx", iprntidx);
  tchfQ -> SetBranchAddress("ichildidx", ichildidx);
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

  int TotlTaggedN = 0;

  float WinMin = 3.;

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
    bTagIndex   -> GetEntry(tentry);
    bTagOut     -> GetEntry(tentry);
    bdvx        -> GetEntry(tentry);
    bdvy        -> GetEntry(tentry);
    bdvz        -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    if (numu->var<float>("wallv")>200) GeneratedEvents++;

    //Proto 1R muon selection
    if (prmsel.ApplyProto1RmuonSelection(evsel)) GetProtoSelectedModeEvents(numu);

    //if (prmsel.C1ApplyFCFV(evsel)) neuosc.GetTrueEnu(numu);

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false)) {
      GetSelectedModeEvents(numu);

      //Neutrino energy distribution
      neuosc.GetTrueEnu(numu);
      neuosc.GetRecoEnu(numu);
      neuosc.GetPrmVtxResolution(numu);

      //Muon angle information
      float truethetamu = neuosc.GetTrueMuDirection(numu, Pvc, Iflvc);
      float recothetamu = neuosc.GetRecoMuDirection(numu);
      neuosc.GetMuDirResolution(truethetamu, recothetamu);

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
      int intmode = TMath::Abs(numu->var<int>("mode"));
      float Enu = numu->var<float>("erec");
      
      ntagana.GetTruthNeutrons(NTrueN, numu, Type, E, DWall);
      ntagana.GetTruthNeutronsIntType(numu, NTrueN);
      ntagana.GetResolutionwTrueN(numu, NTrueN);

      //Truth neutrons
      h1_NTrueN[0] -> Fill(NTrueN);
      int TrueBefSI = ntagana.GetTrueNBefSI(numu, iprntidx, vtxprnt);
      int TrueAftSI = ntagana.GetTrueNAftSI(numu, iprntidx, vtxprnt);
      if (intmode==1) {
        h1_GenBefSINeutrons -> Fill(TrueBefSI);
        h1_GenAftSINeutrons -> Fill(TrueAftSI);
      }

      //Truth distance distribution
      for (UInt_t jentry=0; jentry<DistFromPV->size(); ++jentry) {
        if (Type->at(jentry)==2 && DWall->at(jentry)>0.) {
          ndistance.GetTruthDistance(numu, tagvx->at(jentry), tagvy->at(jentry), tagvz->at(jentry),
                                     vecvx, vecvy, vecvz);
        }
      }

      ntagana.GetTruthNeutronsinSearch(t->size(), Type, t, WinMin, E, DWall);
      ntagana.GetTruthDecayeinSearch(t->size(), Type, t, WinMin);


      //Check truth breakdown(H-n/Gd-n/Decay-e/Acc.Noise) of candidates in the time window
      ntagana.TruthBreakdowninWindow(TagClass, t, DWall, TagIndex, Label, FitT, TagDWall);

      //Check tagged truth neutrons and mis-tagged decay-e and noise with respect to window and threshold.
      ntagana.GetNlikeCandidatesinWindow(t, DWall, TagIndex, etagmode, NHits, FitT, TagOut, Label, TagDWall);

      //Check tagged truth decay-e and mis-tagged neutrons and noise with respect to window and threshold.
      ntagana.GetElikeCandidatesinWindow(t, TagIndex, etagmode, NHits, FitT, TagOut, Label);

      //Check neutrino events with tagged neutrons
      ntagana.GetNeutrinoEventswNTag(TagOut, TagIndex, NHits, FitT, Label, NTrueN, 
                                     etagmode, numu, neuosc, 15,
                                     recothetamu, thetamin, thetamax);

      //Number of tagged-neutrons
      int numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, 0.75, TagIndex, NHits, FitT, Label, etagmode);
      TotlTaggedN += numtaggedneutrons;
      int numtaggednoise = ntagana.GetTaggedNoise(TagOut, 0.75, TagIndex, NHits, FitT, Label, etagmode);

      //Pre-selection
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        //Truth Gd-n or H-n captures
        if (Label->at(jentry)==2 || Label->at(jentry)==3) {
          //Fill corresponded truth distance
          for (UInt_t kentry=0; kentry<DistFromPV->size(); ++kentry) {
            if (Type->at(kentry)==2 && DWall->at(kentry)>0.) {
              ndistance.GetPreEffDistance(TagIndex->at(jentry), kentry,
                                          tagvx->at(kentry), tagvy->at(kentry), tagvz->at(kentry),
                                          vecvx, vecvy, vecvz);
            }
          }
        }
      }

      //Threshold scan
      for (int ith=0; ith<CUTSTEP; ith++) {
        
        //Threshold
        if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
        if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

        //Candidates loop
        for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
          //Truth Gd-n or H-n captures
          if (Label->at(jentry)==2 || Label->at(jentry)==3) {

            if (etagmode) {
              //Focus on neutron-like candidates(e-tagging ON)
              if (TagOut->at(jentry)>TMVATH[ith] && ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry))==false) {
                //Fill corresponded truth distance
                for (UInt_t kentry=0; kentry<DistFromPV->size(); ++kentry) {
                  if (Type->at(kentry)==2 && DWall->at(kentry)>0.) {
                    ndistance.GetOverallEffDistance(ith, TagIndex->at(jentry), kentry,
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
                    ndistance.GetOverallEffDistance(ith, TagIndex->at(jentry), kentry,
                                                  tagvx->at(kentry), tagvy->at(kentry), tagvz->at(kentry),
                                                  vecvx, vecvy, vecvz);
                  }
                }
              }
            }
          }
        } //candidates loop

      } //threshold scan

      if (intmode==1)                 h1_TagNmultiplicity[0]->Fill(numtaggedneutrons);
      if (intmode>=2 && intmode<=10)  h1_TagNmultiplicity[1]->Fill(numtaggedneutrons);
      if (intmode>10 && intmode<=30)  h1_TagNmultiplicity[2]->Fill(numtaggedneutrons);
      if (intmode>=31)                h1_TagNmultiplicity[3]->Fill(numtaggedneutrons);

      float Pmu = numu->var<float>("fq1rmom", PrmEvent, FQ_MUHYP);
      float Pt  = neuosc.GetMuonPt(numu);
      float Qsquare = neuosc.GetQsquare(numu);
      ntagana.N1Rmu_x_kinematics(numu, Enu/1000., xEnubins, N1Rmu_x_Enu, h1_N1Rmu_x_Enu, 0);
      ntagana.N1Rmu_x_kinematics(numu, Pmu/1000., xMuMombins, N1Rmu_x_MuMom, h1_N1Rmu_x_MuMom, 1);
      ntagana.N1Rmu_x_kinematics(numu, Pt/1000., xMuPtbins, N1Rmu_x_MuPt, h1_N1Rmu_x_MuPt, 1);
      ntagana.N1Rmu_x_kinematics(numu, Qsquare/1000000., xQ2bins, N1Rmu_x_Q2, h1_N1Rmu_x_Q2, 1);
      ntagana.N1Rmu_x_kinematics(numu, recothetamu, xMuAnglebins, N1Rmu_x_MuAngle, h1_N1Rmu_x_MuAngle, 1);

      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, Enu/1000., xEnubins, TaggedN_x_Enu, h1_TaggedN_x_Enu, 0);
      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, Pmu/1000., xMuMombins, TaggedN_x_MuMom, h1_TaggedN_x_MuMom, 1);
      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, Pt/1000., xMuPtbins, TaggedN_x_MuPt, h1_TaggedN_x_MuPt, 1);
      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, Qsquare/1000000., xQ2bins, TaggedN_x_Q2, h1_TaggedN_x_Q2, 1);
      ntagana.TaggedN_x_kinematics(numu, numtaggedneutrons, numtaggednoise, recothetamu, xMuAnglebins, TaggedN_x_MuAngle, h1_TaggedN_x_MuAngle, 1);

      ntagana.TrueN_x_kinematics(numu, Type, t, WinMin, Enu/1000., xEnubins, TrueN_x_Enu, h1_TrueN_x_Enu, 0);
      ntagana.TrueN_x_kinematics(numu, Type, t, WinMin, Pmu/1000., xMuMombins, TrueN_x_MuMom, h1_TrueN_x_MuMom, 1);
      ntagana.TrueN_x_kinematics(numu, Type, t, WinMin, Pt/1000., xMuPtbins, TrueN_x_MuPt, h1_TrueN_x_MuPt, 1);
      ntagana.TrueN_x_kinematics(numu, Type, t, WinMin, Qsquare/1000000., xQ2bins, TrueN_x_Q2, h1_TrueN_x_Q2, 1);
      ntagana.TrueN_x_kinematics(numu, Type, t, WinMin, recothetamu, xMuAnglebins, TrueN_x_MuAngle, h1_TrueN_x_MuAngle, 1);

      float RecoPrmVtx[3] = {0., 0., 0.};
      RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
      RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
      RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);
      float NuBeamDir[3] = {0., 0., 0.};
      NuBeamDir[0] = beamDir[0];
      NuBeamDir[1] = beamDir[1];
      NuBeamDir[2] = beamDir[2];
      float RecoMuStpVtx[3] = {0., 0., 0.};
      float RecoMuRange = decayebox.GetRecoMuEndVtx(numu, RecoMuStpVtx);

      for (UInt_t ican=0; ican<TagOut->size(); ican++) {
        if (etagmode){
          if (TagOut->at(ican)>0.75 && ntagana.DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican))==false) {
            float NCapVtx[3]   = {dvx->at(ican), dvy->at(ican), dvz->at(ican)};  //Neutron capture vertex
            float nTraveld     = ndistance.TakeDistance(RecoPrmVtx, NCapVtx);  //Neutron flight distance
            float d_MuStp_NCap = ndistance.TakeDistance(RecoMuStpVtx, NCapVtx);  //Distance b/w muon stopping and neutron capture vertices
            float nTraveldv[3]  = {0., 0., 0.};  //Neutron flight distance vector
            nTraveldv[0] = NCapVtx[0] - RecoPrmVtx[0];
            nTraveldv[1] = NCapVtx[1] - RecoPrmVtx[1];
            nTraveldv[2] = NCapVtx[2] - RecoPrmVtx[2];
            float nTraveldL = GetInnerProduct(nTraveldv, NuBeamDir);  //Longitudinal neutron flight distance
            float nTraveldT = nTraveld*std::sin( std::acos( nTraveldL/nTraveld ) );
            float ncostheta = nTraveldL/nTraveld;
            ntagana.TaggedN_x_Neutronkinematics(numu, Label, ican, nTraveld, xnTraveldbins, TaggedN_x_nTraveld, h1_TaggedN_x_nTraveld, 0);
            ntagana.TaggedN_x_Neutronkinematics(numu, Label, ican, d_MuStp_NCap, xMuStp_NCapbins, TaggedN_x_MuStp_NCap, h1_TaggedN_x_MuStp_NCap, 0);
            ntagana.TaggedN_x_Neutronkinematics(numu, Label, ican, nTraveldL, xnTraveldLbins, TaggedN_x_nTraveldL, h1_TaggedN_x_nTraveldL, 1);
            ntagana.TaggedN_x_Neutronkinematics(numu, Label, ican, nTraveldT, xnTraveldTbins, TaggedN_x_nTraveldT, h1_TaggedN_x_nTraveldT, 0);
            ntagana.TaggedN_x_Neutronkinematics(numu, Label, ican, ncostheta, xnAnglebins, TaggedN_x_nAngle, h1_TaggedN_x_nAngle, 2);
          }
        }
      }

    } //New 1R muon selection

  }

  std::cout << "No mu stop CCQE   : " << NoPrmMuEnd_CCQE << std::endl;
  std::cout << "No mu stop CCnonQE: " << NoPrmMuEnd_CCnonQE << std::endl;
  std::cout << "No mu stop NC     : " << NoPrmMuEnd_NC << std::endl;

  
  std::cout << "No nlike: " << test1 << std::endl;
  std::cout << "More than one nlike: " << test2 << std::endl;

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
    resultfile << "[Decay-e Cut Scan] " << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 20 us: " << SelectedParentNeutrinos_dtScan[0]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[0] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 15 us: " << SelectedParentNeutrinos_dtScan[1]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[1] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt = 10 us: " << SelectedParentNeutrinos_dtScan[2]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[2] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt =  5 us: " << SelectedParentNeutrinos_dtScan[3]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[3] << std::endl;
    resultfile << "[Decay-e Cut Scan] dt =  3 us: " << SelectedParentNeutrinos_dtScan[4]      << std::endl;
    resultfile << "                             : " << FinalSelectedParentNeutrinos_dtScan[4] << std::endl;

    resultfile << "[Neutrino] All Parent Neutrino Events          : " << AllParentNeutrinos << std::endl;
    resultfile << "[Neutrino] Generated Neutrino Events(wallv>200): " << GeneratedEvents    << std::endl;
    resultfile << "[Neutrino] Generated 1Rmu Events (Oscillated)  : " << OscillatedAll      << std::endl;
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
    resultfile << "           w/ tagged neutrons: " << OscillatedCCQE_wTagN << "(" << (OscillatedCCQE_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCQE_woTagN << "(" << (OscillatedCCQE_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CC(2p2h) Events : " << OscillatedCCnonQE << "(" << (OscillatedCCnonQE/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCnonQE_wTagN << "(" << (OscillatedCCnonQE_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCnonQE_woTagN << "(" << (OscillatedCCnonQE_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated All CCRES Events: " << OscillatedCCRES0 + OscillatedCCRESp + OscillatedCCRESpp << "(" << ((OscillatedCCRES0 + OscillatedCCRESp + OscillatedCCRESpp)/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCRES0_wTagN  + OscillatedCCRESp_wTagN  + OscillatedCCRESpp_wTagN << "(" << ((OscillatedCCRES0_wTagN  + OscillatedCCRESp_wTagN  + OscillatedCCRESpp_wTagN)/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCRES0_woTagN  + OscillatedCCRESp_woTagN  + OscillatedCCRESpp_woTagN << "(" << ((OscillatedCCRES0_woTagN  + OscillatedCCRESp_woTagN  + OscillatedCCRESpp_woTagN)/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated CC Other Events : " << OscillatedCCOther << "(" << (OscillatedCCOther/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedCCOther_wTagN << "(" << (OscillatedCCOther_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedCCOther_woTagN << "(" << (OscillatedCCOther_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated NC Events       : " << OscillatedNC << "(" << (OscillatedNC/TotalEventsNoNeutronAnalysis)*100 << " %)" << std::endl;
    resultfile << "           w/ tagged neutrons: " << OscillatedNC_wTagN << "(" << (OscillatedNC_wTagN/TotalEventswTagN)*100
               << " %), w/o tagged neutrons:" << OscillatedNC_woTagN << "(" << (OscillatedNC_woTagN/TotalEventswoTagN)*100 << " %)" << std::endl;

    resultfile << "[Neutrino] Oscillated Neutrino Events within [0.25 GeV, 1.5 GeV]" << std::endl;
    resultfile << "           Legacy Analysis    : " << OscLegacy   << "(Osc)/" << NoOscLegacy   << "(No Osc) = " << OscLegacy/NoOscLegacy     << std::endl;
    resultfile << "           Only CCQE(1p1h)    : " << OscOnlyCCQE << "(Osc)/" << NoOscOnlyCCQE << "(No Osc) = " << OscOnlyCCQE/NoOscOnlyCCQE << std::endl;
    resultfile << "           w/o truth neutrons : " << OscwoTrueN  << "(Osc)/" << NoOscwoTrueN  << "(No Osc) = " << OscwoTrueN/NoOscwoTrueN   << std::endl;
    resultfile << "           w/o tagged neutrons: " << OscwoTagN   << "(Osc)/" << NoOscwoTagN   << "(No Osc) = " << OscwoTagN/NoOscwoTagN     << std::endl;

    resultfile << " " << std::endl;
    resultfile << "===== #1Rmu as a function of Enu =====" << std::endl;
    for (int ibin=0; ibin<binnumber_nu; ibin++) {
      if (ibin<binnumber_nu-1) resultfile << "#1Rmu @ Enu [" << xEnubins[ibin] << ", " << xEnubins[ibin+1] << "): " << N1Rmu_x_Enu[ibin] << std::endl;
      else resultfile << "#1Rmu @ Enu > " << xEnubins[ibin] << ": " << N1Rmu_x_Enu[ibin] << std::endl;
    }
    resultfile << "===== #1Rmu as a function of Pmu =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#1Rmu @ Pmu [" << xMuMombins[ibin] << ", " << xMuMombins[ibin+1] << "): " << N1Rmu_x_MuMom[ibin] << std::endl;
      else resultfile << "#1Rmu @ Pmu > " << xMuMombins[ibin] << ": " << N1Rmu_x_MuMom[ibin] << std::endl;
    }
    resultfile << "===== #1Rmu as a function of Pt =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#1Rmu @ Pt [" << xMuMombins[ibin] << ", " << xMuMombins[ibin+1] << "): " << N1Rmu_x_MuPt[ibin] << std::endl;
      else resultfile << "#1Rmu @ Pt > " << xMuMombins[ibin] << ": " << N1Rmu_x_MuPt[ibin] << std::endl;
    }
    resultfile << "===== #1Rmu as a function of Q2 =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#1Rmu @ Q2 [" << xQ2bins[ibin] << ", " << xQ2bins[ibin+1] << "): " << N1Rmu_x_Q2[ibin] << std::endl;
      else resultfile << "#1Rmu @ Q2 > " << xQ2bins[ibin] << ": " << N1Rmu_x_Q2[ibin] << std::endl;
    }
    resultfile << "===== #1Rmu as a function of costheta =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#1Rmu @ costheta [" << xMuAnglebins[ibin] << ", " << xMuAnglebins[ibin+1] << "): " << N1Rmu_x_MuAngle[ibin] << std::endl;
    }
    resultfile << " " << std::endl;
    resultfile << "Total #tagged neutrons: " << TotlTaggedN << std::endl;
    resultfile << "===== #tagged-n as a function of Enu =====" << std::endl;
    for (int ibin=0; ibin<binnumber_nu; ibin++) {
      if (ibin<binnumber_nu-1) resultfile << "#tagged-n @ Enu [" << xEnubins[ibin] << ", " << xEnubins[ibin+1] << "): " << TaggedN_x_Enu[ibin] << std::endl;
      else resultfile << "#tagged-n @ Enu > " << xEnubins[ibin] << ": " << TaggedN_x_Enu[ibin] << std::endl;
    }
    resultfile << "===== #tagged neutrons as a function of Pmu =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#tagged-n @ Pmu [" << xMuMombins[ibin] << ", " << xMuMombins[ibin+1] << "): " << TaggedN_x_MuMom[ibin] << std::endl;
      else resultfile << "#tagged-n @ Pmu > " << xMuMombins[ibin] << ": " << TaggedN_x_MuMom[ibin] << std::endl;
    }
    resultfile << "===== #tagged neutrons as a function of Pt =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#tagged-n @ Pt [" << xMuMombins[ibin] << ", " << xMuMombins[ibin+1] << "): " << TaggedN_x_MuPt[ibin] << std::endl;
      else resultfile << "#tagged-n @ Pt > " << xMuMombins[ibin] << ": " << TaggedN_x_MuPt[ibin] << std::endl;
    }
    resultfile << "===== #tagged neutrons as a function of Q2 =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#tagged-n @ Q2 [" << xQ2bins[ibin] << ", " << xQ2bins[ibin+1] << "): " << TaggedN_x_Q2[ibin] << std::endl;
      else resultfile << "#tagged-n @ Q2 > " << xQ2bins[ibin] << ": " << TaggedN_x_Q2[ibin] << std::endl;
    }
    resultfile << "===== #1Rmu as a function of costheta =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#tagged-n @ costheta [" << xMuAnglebins[ibin] << ", " << xMuAnglebins[ibin+1] << "): " << TaggedN_x_MuAngle[ibin] << std::endl;
    }
    resultfile << " " << std::endl;
    resultfile << "===== #truth neutrons as a function of Enu =====" << std::endl;
    for (int ibin=0; ibin<binnumber_nu; ibin++) {
      if (ibin<binnumber_nu-1) resultfile << "#truth n @ Enu [" << xEnubins[ibin] << ", " << xEnubins[ibin+1] << "): " << TrueN_x_Enu[ibin] << std::endl;
      else resultfile << "#truth n @ Enu > " << xEnubins[ibin] << ": " << TrueN_x_Enu[ibin] << std::endl;
    }
    resultfile << " " << std::endl;
    resultfile << "===== #tagged neutrons as a function of dn =====" << std::endl;
    for (int ibin=0; ibin<binnumber_n; ibin++) {
      if (ibin<binnumber_n-1) resultfile << "#truth n @ dn [" << xnTraveldbins[ibin] << ", " << xnTraveldbins[ibin+1] << "): " << TaggedN_x_nTraveld[ibin] << std::endl;
      else resultfile << "#truth n @ dn > " << xnTraveldbins[ibin] << ": " << TaggedN_x_nTraveld[ibin] << std::endl;
    }

    ntagana.SummaryTruthInfoinSearch(WinMin, NTagSummary);
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

  WriteVECTHisto();

}