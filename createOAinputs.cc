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
#include "src/TreeManager/inc/TreeManager.h"


int main(int argc, char **argv) {

  TString fiTQunFileName  = argv[1];
  TString NtagFileName    = argv[2];
  TString OutputRootName  = argv[3];
  TString ResultSummary   = argv[4];
  TString NTagSummary     = argv[5];
  TString MCTypeKeyword   = argv[6];
  TString MCType          = argv[7];
  TString ETAGKeyword     = argv[8];
  TString ETAG            = argv[9];
  TString BeamKeyword     = argv[10];
  TString Beam            = argv[11];
  TString OscKeyword      = argv[12];
  TString Osc             = argv[13];
  TString SampleKeyword   = argv[14];
  TString Sample          = argv[15];
  TString OutSampleName   = argv[16];
  TString NTagInfoKeyword = argv[17];
  TString NTagInfo        = argv[18];

  enum BeamMode::E_BEAM_MODE eMode;
  enum OscChan::E_OSC_CHAN eOsc;
  eMode = CLTOptionBeamMode(BeamKeyword, Beam);
  eOsc  = CLTOptionOscMode(OscKeyword, Osc);
  CLTOptionETAG(ETAGKeyword, ETAG);

  //TTree
  TreeManager* woTagNtuple = new TreeManager(0);
  woTagNtuple -> SetBranch(0);

  TreeManager* wTagNtuple = new TreeManager(1);
  wTagNtuple -> SetBranch(1);

  TreeManager* Ntuple = new TreeManager(2);
  Ntuple -> SetBranch(2);

  if (Osc=="NUE" || Osc=="NUEBAR") {
    filetype_woTagN = 0;
    filetype_wTagN  = 0;
  }
  else if (Osc=="NUESIG" || Osc=="NUEBARSIG") {
    filetype_woTagN = 1;
    filetype_wTagN  = 1;
  }
  else {
    filetype_woTagN = -1;
    filetype_wTagN  = -1;
  }

  //If no input files, make a TTree with empty events
  if (!CLTOptionSample(SampleKeyword, Sample)) {
    std::cout << "[### analysis1Rmu ###]  No input files." << std::endl;

    if (Osc=="NUE" || Osc=="NUEBAR") {
      filetype_woTagN = 0;
      filetype_wTagN  = 0;
    }
    else if (Osc=="NUESIG" || Osc=="NUEBARSIG") {
      filetype_woTagN = 1;
      filetype_wTagN  = 1;
    }
    else {
      filetype_woTagN = -1;
      filetype_wTagN  = -1;
    }

    woTagNtuple -> FillBrankTree(0);
    woTagNtuple -> WriteTree(OutSampleName+".woTagN.root", 0);

    wTagNtuple -> FillBrankTree(1);
    wTagNtuple -> WriteTree(OutSampleName+".wTagN.root", 1);

    Ntuple -> FillBrankTree(2);
    Ntuple -> WriteTree(OutSampleName+".NoNTag.root", 2);

    std::cout << "                        Created empty mtuple." << std::endl;
    exit(1);
  }

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

  //=========  TTree h1 variables  ============
  //===== It should be called before numu ======
  Int_t   fqnmrfit;
  Float_t fqmrdir[100][7][3];
  Float_t fqmrmom[100][6][3];
  Int_t   fqmrifit[100];
  Float_t fqmrnll[100];
  Float_t fqmreloss[100][6];
  Double_t DeltaPForEmiss0;
  Float_t pi0like[2];
  Float_t pi0_e[2][2];
  Float_t pi0_dir[2][2][3];
  Float_t pi0mass[2];
  Int_t   nmue;
  Int_t   itrkscnd[1000];
  Int_t   iprnttrk[1000];
  Int_t   iorgprt[1000];
  Int_t   iflgscnd[1000];
  Float_t pprnt[1000][3];
  tchfQ -> SetBranchAddress("fqnmrfit", &fqnmrfit);
  tchfQ -> SetBranchAddress("fqmrdir", fqmrdir);
  tchfQ -> SetBranchAddress("fqmrmom", fqmrmom);
  tchfQ -> SetBranchAddress("fqmrifit", fqmrifit);
  tchfQ -> SetBranchAddress("fqmrnll", fqmrnll);
  tchfQ -> SetBranchAddress("fqmreloss", fqmreloss);
  tchfQ -> SetBranchAddress("DeltaPForEmiss0", &DeltaPForEmiss0);
  tchfQ -> SetBranchAddress("pi0like", pi0like);
  tchfQ -> SetBranchAddress("pi0_e", pi0_e);
  tchfQ -> SetBranchAddress("pi0_dir", pi0_dir);
  tchfQ -> SetBranchAddress("pi0mass", pi0mass);
  tchfQ -> SetBranchAddress("nmue", &nmue);
  tchfQ -> SetBranchAddress("itrkscnd", itrkscnd);
  tchfQ -> SetBranchAddress("iprnttrk", iprnttrk);
  tchfQ -> SetBranchAddress("iorgprt", iorgprt);
  tchfQ -> SetBranchAddress("iflgscnd", iflgscnd);
  tchfQ -> SetBranchAddress("pprnt", pprnt);
  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc);
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);
  
  //=========  TTree h1 variables  ============
  //===== It should be called after numu ======
  Int_t   Ibound;
  Float_t Pvc[100][3];     //Momentum of primary particles
  Int_t   Iflvc[100];      //Flag of final states
  Int_t   Iorgvc[100];
  Float_t tscnd[1000];
  Float_t pscnd[1000][3];   //Momentum of the secondary particle
  Int_t   nring;
  Int_t   nev;
  Float_t wall;
  Float_t evis;
  Float_t Crsx;
  Float_t Crsy;
  Float_t Crsz;
  Float_t Crsphi;
  Int_t   Nvert;
  Float_t Posvert[300][3];
  Int_t   Iflgvert[300];
  Int_t   Nvcvert;
  Float_t Dirvert[900][3];
  Float_t Abspvert[900];
  Float_t Abstpvert[900];
  Int_t   Ipvert[900];
  Int_t   Iverti[900];
  Int_t   Ivertf[900];
  Float_t Fsiprob;
  Int_t   Numbndn;
  Int_t   Numbndp;
  Int_t   Numfrep;
  Int_t   Numatom;
  tchfQ -> SetBranchAddress("Ibound", &Ibound);
  tchfQ -> SetBranchAddress("Pvc", Pvc);
  tchfQ -> SetBranchAddress("Iflvc", Iflvc);
  tchfQ -> SetBranchAddress("Iorgvc", Iorgvc);
  tchfQ -> SetBranchAddress("tscnd", tscnd);
  tchfQ -> SetBranchAddress("pscnd", pscnd);
  tchfQ -> SetBranchAddress("nring", &nring);
  tchfQ -> SetBranchAddress("nev", &nev);
  tchfQ -> SetBranchAddress("wall", &wall);
  tchfQ -> SetBranchAddress("evis", &evis);
  tchfQ -> SetBranchAddress("Crsx", &Crsx);
  tchfQ -> SetBranchAddress("Crsy", &Crsy);
  tchfQ -> SetBranchAddress("Crsz", &Crsz);
  tchfQ -> SetBranchAddress("Crsphi", &Crsphi);
  tchfQ -> SetBranchAddress("Nvert", &Nvert);
  tchfQ -> SetBranchAddress("Posvert", Posvert);
  tchfQ -> SetBranchAddress("Iflgvert", Iflgvert);
  tchfQ -> SetBranchAddress("Nvcvert", &Nvcvert);
  tchfQ -> SetBranchAddress("Dirvert", Dirvert);
  tchfQ -> SetBranchAddress("Abspvert", Abspvert);
  tchfQ -> SetBranchAddress("Abstpvert", Abstpvert);
  tchfQ -> SetBranchAddress("Ipvert", Ipvert);
  tchfQ -> SetBranchAddress("Iverti", Iverti);
  tchfQ -> SetBranchAddress("Ivertf", Ivertf);
  tchfQ -> SetBranchAddress("Fsiprob", &Fsiprob);
  tchfQ -> SetBranchAddress("Numbndn", &Numbndn);
  tchfQ -> SetBranchAddress("Numbndp", &Numbndp);
  tchfQ -> SetBranchAddress("Numfrep", &Numfrep);
  tchfQ -> SetBranchAddress("Numatom", &Numatom);


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
  bool usentag = CLTOptionNTagInfo(NTagInfoKeyword, NTagInfo);


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
    prmsel.GetemuLikelihood(numu);
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);
    //Sequencial1RmuonSelection_Pion(prmsel, evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false);

    //if (wallv>200) GeneratedEvents++;
    if (numu->var<float>("wallv")>200) GeneratedEvents++;


    //Proto 1R muon selection
    if (prmsel.ApplyProto1RmuonSelection(evsel)) GetProtoSelectedModeEvents(numu);

    //Truth neutrino energy (before #ring=1 cut)
    if (prmsel.C1ApplyFCFV(evsel)) neuosc.GetTrueEnu(numu);

    int NoTagN = 9999; // flag: 0 for w/o TagN, 1 for w/ TagN

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., true)) {
      GetSelectedModeEvents(numu);

      //Neutrino energy distribution
      //neuosc.GetTrueEnu(numu);
      neuosc.GetRecoEnu(numu);

      //Muon angle information
      //float truethetamu = neuosc.GetTrueMuDirection(numu, Npvc, Ipvc, Pvc, Iflvc, Ichvc);
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


      ntagana.GetTruthNeutrons(NTrueN, numu, Type, E, DWall);
      ntagana.GetTruthNeutronsIntType(numu, NTrueN);
      ntagana.GetResolutionwTrueN(numu, NTrueN);

      ntagana.GetTruthNeutronsinSearch(t->size(), Type, t, 3., E, DWall);
      ntagana.GetTruthDecayeinSearch(t->size(), Type, t, 3.);


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


      //=== No NTag info ===
      if (usentag==false) {
        NoTagN = 2;

        //for 1Rmu (no NTag info)
        iclass_NoNTag = 13; // 1R mu(13)

        //NEUT vector variables
        mode_NoNTag   = numu->var<int>("mode");
        Ibound_NoNTag = Ibound;
        numnu_NoNTag  = numu->var<int>("numnu");
        for (Int_t ivc=0; ivc<numnu_NoNTag; ivc++) {
          pnu_NoNTag[ivc]  = numu->var<float>("pnu", ivc);
          ipnu_NoNTag[ivc] = numu->var<int>("ipnu", ivc);
          for (int idir=0; idir<3; idir++) {
            dirnu_NoNTag[ivc][idir] = numu->var<float>("dirnu", ivc, idir);
          }
        }

        Npvc_NoNTag = numu->var<int>("Npvc");
        for (Int_t ivc=0; ivc<Npvc_NoNTag; ivc++) {
          Ipvc_NoNTag[ivc]   = numu->var<int>("Ipvc", ivc);
          Ichvc_NoNTag[ivc]  = numu->var<int>("Ichvc", ivc);
          Iflvc_NoNTag[ivc]  = Iflvc[ivc];
          Iorgvc_NoNTag[ivc] = Iorgvc[ivc];
          Abspvc_NoNTag[ivc] = numu->var<float>("Abspvc", ivc);
          for (int idir=0; idir<3; idir++) Pvc_NoNTag[ivc][idir] = Pvc[ivc][idir];
        }
        Crsx_NoNTag   = Crsx;
        Crsy_NoNTag   = Crsy;
        Crsz_NoNTag   = Crsz;
        Crsphi_NoNTag = Crsphi;
        Nvert_NoNTag  = Nvert;
        for (int i=0; i<Nvert_NoNTag; i++) {
          Iflgvert_NoNTag[i] = Iflgvert[i];
          for (int idir=0; idir<3; idir++) {
            Posvert_NoNTag[i][idir] = Posvert[i][idir];
          }
        }
        Nvcvert_NoNTag = Nvcvert;
        for (int i=0; i<Nvcvert_NoNTag; i++) {
          Abspvert_NoNTag[i]  = Abspvert[i];
          Abstpvert_NoNTag[i] = Abstpvert[i];
          Ipvert_NoNTag[i]    = Ipvert[i];
          Iverti_NoNTag[i]    = Iverti[i];
          Ivertf_NoNTag[i]    = Ivertf[i];
          for (int idir=0; idir<3; idir++) Dirvert_NoNTag[i][idir] = Dirvert[i][idir];
        }
        Fsiprob_NoNTag = Fsiprob;

        Numbndn_NoNTag = Numbndn;
        Numbndp_NoNTag = Numbndp;
        Numfrep_NoNTag = Numfrep;
        Numatom_NoNTag = Numatom;

        Nvertsk_NoNTag = 0;
        for (int iv=0; iv<Nvertsk_NoNTag; iv++) {
          Iflgvertsk_NoNTag[iv] = 0;
          for (int idir=0; idir<3; idir++) Posvertsk_NoNTag[iv][idir] = 0.;
        }

        Nvcvertsk_NoNTag = 0;
        for (int ivc=0; ivc<Nvcvertsk_NoNTag; ivc++) {
          Abspvertsk_NoNTag[ivc]  = 0.;
          Abstpvertsk_NoNTag[ivc] = 0.;
          Ipvertsk_NoNTag[ivc]    = 0;
          Ivertisk_NoNTag[ivc]    = 0;
          Ivertfsk_NoNTag[ivc]    = 0;
          for (int idir=0; idir<3; idir++) {
            Dirvertsk_NoNTag[ivc][idir] = 0.;
          }
        }
        Fsiprobsk_NoNTag = 0.;

        npar_NoNTag = numu->var<int>("npar");
        for (int iv=0; iv<npar_NoNTag; iv++) {
          ipv_NoNTag[iv]   = numu->var<int>("ipv", iv);
          pmomv_NoNTag[iv] = numu->var<float>("pmomv", iv);
          for (int idir=0; idir<3; idir++) {
            dirv_NoNTag[iv][idir] = numu->var<float>("dirv", iv, idir);
          }
        }
        for (int idir=0; idir<3; idir++) posv_NoNTag[idir] = numu->var<float>("posv", idir);
        wallv_NoNTag  = numu->var<float>("wallv");
        wgtosc_NoNTag = numu->getOscWgt();
        for (int ipi=0; ipi<2; ipi++) {
          pi0like_NoNTag[ipi] = pi0like[ipi];
          pi0mass_NoNTag[ipi] = pi0mass[ipi];
          for (int jpi=0; jpi<2; jpi++) {
            pi0_e_NoNTag[ipi][jpi] = pi0_e[ipi][jpi];
            for (int idir=0; idir<3; idir++) {
              pi0_dir_NoNTag[ipi][jpi][idir] = pi0_dir[ipi][jpi][idir];
            }
          }
        }
        nmue_NoNTag = nmue;

        nscndprt_NoNTag = numu->var<int>("nscndprt");
        for (int iscnd=0; iscnd<nscndprt_NoNTag; iscnd++) {
          itrkscnd_NoNTag[iscnd] = itrkscnd[iscnd];
          iprtscnd_NoNTag[iscnd] = numu->var<int>("iprtscnd", iscnd);
          //tscnd_NoNTag[iscnd]    = numu->var<float>("tscnd", iscnd);
          tscnd_NoNTag[iscnd]    = tscnd[iscnd];
          iprntprt_NoNTag[iscnd] = numu->var<int>("iprntprt", iscnd);
          lmecscnd_NoNTag[iscnd] = numu->var<int>("lmecscnd", iscnd);
          iprnttrk_NoNTag[iscnd] = iprnttrk[iscnd];
          iorgprt_NoNTag[iscnd]  = iorgprt[iscnd];
          iflgscnd_NoNTag[iscnd] = iflgscnd[iscnd];
          for (int idir=0; idir<3; idir++) {
            vtxscnd_NoNTag[iscnd][idir] = numu->var<float>("vtxscnd", iscnd, idir);
            pscnd_NoNTag[iscnd][idir]   = pscnd[iscnd][idir];
            pprnt_NoNTag[iscnd][idir]   = pprnt[iscnd][idir];
          }
        }

        //SK variables
        nring_NoNTag  = nring;
        nev_NoNTag    = nev;
        nhitac_NoNTag = numu->var<int>("nhitac");
        wall_NoNTag   = wall;
        evis_NoNTag   = evis;

        //fiTQun variables
        fqnse_NoNTag = numu->var<int>("fqnse");
        for (Int_t ifq=0; ifq<fqnse_NoNTag; ifq++) {
          for (int ihyp=0; ihyp<7; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fq1rdir_NoNTag[ifq][ihyp][idir] = numu->var<float>("fq1rdir", ifq, ihyp, idir);
            }
          }
        }
        fqmome_NoNTag = numu->var<float>("fq1rmom", 0, 1);
        fqmomm_NoNTag = numu->var<float>("fq1rmom", 0, 2);

        fqnmrfit_NoNTag = fqnmrfit;
        for (Int_t ifq=0; ifq<fqnmrfit_NoNTag; ifq++) {
          //ipp_wTagN[ifq] = fqmrifit[ifq];
          for (int ihyp=0; ihyp<6; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fqmrdir_NoNTag[ifq][ihyp][idir] = fqmrdir[ifq][ihyp][idir];
              fqmrmom_NoNTag[ifq][ihyp][idir] = fqmrmom[ifq][ihyp][idir];
            }
          }
        }

        //MR variables
        /*for (Int_t ifq=0; ifq<fqnmrfit; ifq++) {
          if (isnan(fqmrnll[ifq])) continue;
          int fitID = TMath::Abs(fqmrifit[ifq]); // fit ID (<0: regected by NR/(N+1)R likelihood ratio test)
          if(fitID==20000033) {
            ipp_wTagN[ifq] = ifq;
          }
        }*/
        if (nring_NoNTag==0) {
          for (int iring=0; iring<100; iring++) {
            ip_NoNTag[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_NoNTag[iring][idir] = 0.;
            }
          }          
        }
        else {
          for (int iring=0; iring<nring_NoNTag; iring++) {
            ip_NoNTag[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_NoNTag[iring][idir] = 0.;
            }
          }
        }
        
        ipp_NoNTag           = -1;
        ippp_NoNTag          = -1;
        evisible_NoNTag      = -1;
        elosssum_pipi_NoNTag = -1;

        //NIWG variables
        wgts_maqeh_NoNTag = 1.;
        DeltaPForEmiss0_NoNTag = DeltaPForEmiss0;

        //Fill before skip
        if (NoTagN==2) Ntuple -> FillTree(2);

        continue;
      }



      //=== NTag separation ===
      //Fill TTree branch
      //Get the number of tagged neutrons of this neutrino event
      float numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, 0.75, TagIndex, NHits, FitT, Label, etagmode);
      if (numtaggedneutrons == 0) {
        NoTagN        = 0;

        iclass_woTagN = 1302112;  // 1R mu(13) w/o(0) tagged-n(2112)

        //NEUT vector variables
        mode_woTagN   = numu->var<int>("mode");
        Ibound_woTagN = Ibound;
        numnu_woTagN  = numu->var<int>("numnu");
        for (Int_t ivc=0; ivc<numnu_woTagN; ivc++) {
          pnu_woTagN[ivc]  = numu->var<float>("pnu", ivc);
          ipnu_woTagN[ivc] = numu->var<int>("ipnu", ivc);
          for (int idir=0; idir<3; idir++) {
            dirnu_woTagN[ivc][idir] = numu->var<float>("dirnu", ivc, idir);
          }
        }

        Npvc_woTagN = numu->var<int>("Npvc");
        for (Int_t ivc=0; ivc<Npvc_woTagN; ivc++) {
          Ipvc_woTagN[ivc]   = numu->var<int>("Ipvc", ivc);
          Ichvc_woTagN[ivc]  = numu->var<int>("Ichvc", ivc);
          Iflvc_woTagN[ivc]  = Iflvc[ivc];
          Iorgvc_woTagN[ivc] = Iorgvc[ivc];
          Abspvc_woTagN[ivc] = numu->var<float>("Abspvc", ivc);
          for (int idir=0; idir<3; idir++) Pvc_woTagN[ivc][idir] = Pvc[ivc][idir];
        }
        Crsx_woTagN   = Crsx;
        Crsy_woTagN   = Crsy;
        Crsz_woTagN   = Crsz;
        Crsphi_woTagN = Crsphi;
        Nvert_woTagN  = Nvert;
        for (int i=0; i<Nvert_woTagN; i++) {
          Iflgvert_woTagN[i] = Iflgvert[i];
          for (int idir=0; idir<3; idir++) {
            Posvert_woTagN[i][idir] = Posvert[i][idir];
          }
        }
        Nvcvert_woTagN = Nvcvert;
        for (int i=0; i<Nvcvert_woTagN; i++) {
          Abspvert_woTagN[i]  = Abspvert[i];
          Abstpvert_woTagN[i] = Abstpvert[i];
          Ipvert_woTagN[i]    = Ipvert[i];
          Iverti_woTagN[i]    = Iverti[i];
          Ivertf_woTagN[i]    = Ivertf[i];
          for (int idir=0; idir<3; idir++) Dirvert_woTagN[i][idir] = Dirvert[i][idir];
        }
        Fsiprob_woTagN = Fsiprob;

        Numbndn_woTagN = Numbndn;
        Numbndp_woTagN = Numbndp;
        Numfrep_woTagN = Numfrep;
        Numatom_woTagN = Numatom;

        Nvertsk_woTagN = 0;
        for (int iv=0; iv<Nvertsk_woTagN; iv++) {
          Iflgvertsk_woTagN[iv] = 0;
          for (int idir=0; idir<3; idir++) Posvertsk_woTagN[iv][idir] = 0.;
        }

        Nvcvertsk_woTagN = 0;
        for (int ivc=0; ivc<Nvcvertsk_woTagN; ivc++) {
          Abspvertsk_woTagN[ivc]  = 0.;
          Abstpvertsk_woTagN[ivc] = 0.;
          Ipvertsk_woTagN[ivc]    = 0;
          Ivertisk_woTagN[ivc]    = 0;
          Ivertfsk_woTagN[ivc]    = 0;
          for (int idir=0; idir<3; idir++) {
            Dirvertsk_woTagN[ivc][idir] = 0.;
          }
        }
        Fsiprobsk_woTagN = 0.;

        npar_woTagN = numu->var<int>("npar");
        for (int iv=0; iv<npar_woTagN; iv++) {
          ipv_woTagN[iv]   = numu->var<int>("ipv", iv);
          pmomv_woTagN[iv] = numu->var<float>("pmomv", iv);
          for (int idir=0; idir<3; idir++) {
            dirv_woTagN[iv][idir] = numu->var<float>("dirv", iv, idir);
          }
        }
        for (int idir=0; idir<3; idir++) posv_woTagN[idir] = numu->var<float>("posv", idir);
        wallv_woTagN  = numu->var<float>("wallv");
        wgtosc_woTagN = numu->getOscWgt();
        for (int ipi=0; ipi<2; ipi++) {
          pi0like_woTagN[ipi] = pi0like[ipi];
          pi0mass_woTagN[ipi] = pi0mass[ipi];
          for (int jpi=0; jpi<2; jpi++) {
            pi0_e_woTagN[ipi][jpi] = pi0_e[ipi][jpi];
            for (int idir=0; idir<3; idir++) {
              pi0_dir_woTagN[ipi][jpi][idir] = pi0_dir[ipi][jpi][idir];
            }
          }
        }
        nmue_woTagN = nmue;

        nscndprt_woTagN = numu->var<int>("nscndprt");
        for (int iscnd=0; iscnd<nscndprt_woTagN; iscnd++) {
          itrkscnd_woTagN[iscnd] = itrkscnd[iscnd];
          iprtscnd_woTagN[iscnd] = numu->var<int>("iprtscnd", iscnd);
          //tscnd_woTagN[iscnd]    = numu->var<float>("tscnd", iscnd);
          tscnd_woTagN[iscnd]    = tscnd[iscnd];
          iprntprt_woTagN[iscnd] = numu->var<int>("iprntprt", iscnd);
          lmecscnd_woTagN[iscnd] = numu->var<int>("lmecscnd", iscnd);
          iprnttrk_woTagN[iscnd] = iprnttrk[iscnd];
          iorgprt_woTagN[iscnd]  = iorgprt[iscnd];
          iflgscnd_woTagN[iscnd] = iflgscnd[iscnd];

          for (int idir=0; idir<3; idir++) {
            vtxscnd_woTagN[iscnd][idir] = numu->var<float>("vtxscnd", iscnd, idir);
            pscnd_woTagN[iscnd][idir]   = pscnd[iscnd][idir];
            pprnt_woTagN[iscnd][idir]   = pprnt[iscnd][idir];
          }
        }
        

        //SK variables
        nring_woTagN  = nring;
        nev_woTagN    = nev;
        nhitac_woTagN = numu->var<int>("nhitac");
        wall_woTagN   = wall;
        evis_woTagN   = evis;

        //fiTQun variables
        fqnse_woTagN = numu->var<int>("fqnse");
        for (Int_t ifq=0; ifq<fqnse_woTagN; ifq++) {
          for (int ihyp=0; ihyp<7; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fq1rdir_woTagN[ifq][ihyp][idir] = numu->var<float>("fq1rdir", ifq, ihyp, idir);
            }
          }
        }
        fqmome_woTagN = numu->var<float>("fq1rmom", 0, 1);
        fqmomm_woTagN = numu->var<float>("fq1rmom", 0, 2);

        fqnmrfit_woTagN = fqnmrfit;
        for (Int_t ifq=0; ifq<fqnmrfit; ifq++) {
          //ipp_woTagN[ifq] = fqmrifit[ifq];
          for (int ihyp=0; ihyp<6; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fqmrdir_woTagN[ifq][ihyp][idir] = fqmrdir[ifq][ihyp][idir];
              fqmrmom_woTagN[ifq][ihyp][idir] = fqmrmom[ifq][ihyp][idir];
            }
          }
        }

        //MR variables
        /*for (Int_t ifq=0; ifq<fqnmrfit; ifq++) {
          if (isnan(fqmrnll[ifq])) continue;
          int fitID = TMath::Abs(fqmrifit[ifq]); // fit ID (<0: regected by NR/(N+1)R likelihood ratio test)
          if(fitID==20000033) {
            ipp_woTagN[ifq] = ifq;
          }
        }*/
        if (nring_woTagN==0) {
          for (int iring=0; iring<100; iring++) {
            ip_woTagN[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_woTagN[iring][idir] = 0.;
            }
          }
        }
        else {
          for (int iring=0; iring<nring_woTagN; iring++) {
            ip_woTagN[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_woTagN[iring][idir] = 0.;
            }
          }
        }
        /*for (int iring=0; iring<nring_woTagN; iring++) {
          ip_woTagN[iring] = 0;
          for (int idir=0; idir<3; idir++) {
            dir_woTagN[iring][idir] = 0.;
          }
        }*/
        ipp_woTagN           = -1;
        ippp_woTagN          = -1;
        evisible_woTagN      = -1;
        elosssum_pipi_woTagN = -1;

        //NIWG variables
        wgts_maqeh_woTagN = 1.;
        DeltaPForEmiss0_woTagN = DeltaPForEmiss0;

      }
      else {
        NoTagN       = 1;

        iclass_wTagN = 1312112; // 1R mu(13) w/ (1) tagged-n(2112)

        //NEUT vector variables
        mode_wTagN   = numu->var<int>("mode");
        Ibound_wTagN = Ibound;
        numnu_wTagN  = numu->var<int>("numnu");
        for (Int_t ivc=0; ivc<numnu_wTagN; ivc++) {
          pnu_wTagN[ivc]  = numu->var<float>("pnu", ivc);
          ipnu_wTagN[ivc] = numu->var<int>("ipnu", ivc);
          for (int idir=0; idir<3; idir++) {
            dirnu_wTagN[ivc][idir] = numu->var<float>("dirnu", ivc, idir);
          }
        }

        Npvc_wTagN = numu->var<int>("Npvc");
        for (Int_t ivc=0; ivc<Npvc_wTagN; ivc++) {
          Ipvc_wTagN[ivc]   = numu->var<int>("Ipvc", ivc);
          Ichvc_wTagN[ivc]  = numu->var<int>("Ichvc", ivc);
          Iflvc_wTagN[ivc]  = Iflvc[ivc];
          Iorgvc_wTagN[ivc] = Iorgvc[ivc];
          Abspvc_wTagN[ivc] = numu->var<float>("Abspvc", ivc);
          for (int idir=0; idir<3; idir++) Pvc_wTagN[ivc][idir] = Pvc[ivc][idir];
        }
        Crsx_wTagN   = Crsx;
        Crsy_wTagN   = Crsy;
        Crsz_wTagN   = Crsz;
        Crsphi_wTagN = Crsphi;
        Nvert_wTagN  = Nvert;
        for (int i=0; i<Nvert_wTagN; i++) {
          Iflgvert_wTagN[i] = Iflgvert[i];
          for (int idir=0; idir<3; idir++) {
            Posvert_wTagN[i][idir] = Posvert[i][idir];
          }
        }
        Nvcvert_wTagN = Nvcvert;
        for (int i=0; i<Nvcvert_wTagN; i++) {
          Abspvert_wTagN[i]  = Abspvert[i];
          Abstpvert_wTagN[i] = Abstpvert[i];
          Ipvert_wTagN[i]    = Ipvert[i];
          Iverti_wTagN[i]    = Iverti[i];
          Ivertf_wTagN[i]    = Ivertf[i];
          for (int idir=0; idir<3; idir++) Dirvert_wTagN[i][idir] = Dirvert[i][idir];
        }
        Fsiprob_wTagN = Fsiprob;

        Numbndn_wTagN = Numbndn;
        Numbndp_wTagN = Numbndp;
        Numfrep_wTagN = Numfrep;
        Numatom_wTagN = Numatom;

        Nvertsk_wTagN = 0;
        for (int iv=0; iv<Nvertsk_wTagN; iv++) {
          Iflgvertsk_wTagN[iv] = 0;
          for (int idir=0; idir<3; idir++) Posvertsk_wTagN[iv][idir] = 0.;
        }

        Nvcvertsk_wTagN = 0;
        for (int ivc=0; ivc<Nvcvertsk_wTagN; ivc++) {
          Abspvertsk_wTagN[ivc]  = 0.;
          Abstpvertsk_wTagN[ivc] = 0.;
          Ipvertsk_wTagN[ivc]    = 0;
          Ivertisk_wTagN[ivc]    = 0;
          Ivertfsk_wTagN[ivc]    = 0;
          for (int idir=0; idir<3; idir++) {
            Dirvertsk_wTagN[ivc][idir] = 0.;
          }
        }
        Fsiprobsk_wTagN = 0.;

        npar_wTagN = numu->var<int>("npar");
        for (int iv=0; iv<npar_woTagN; iv++) {
          ipv_wTagN[iv]   = numu->var<int>("ipv", iv);
          pmomv_wTagN[iv] = numu->var<float>("pmomv", iv);
          for (int idir=0; idir<3; idir++) {
            dirv_wTagN[iv][idir] = numu->var<float>("dirv", iv, idir);
          }
        }
        for (int idir=0; idir<3; idir++) posv_wTagN[idir] = numu->var<float>("posv", idir);
        wallv_wTagN  = numu->var<float>("wallv");
        wgtosc_wTagN = numu->getOscWgt();
        for (int ipi=0; ipi<2; ipi++) {
          pi0like_wTagN[ipi] = pi0like[ipi];
          pi0mass_wTagN[ipi] = pi0mass[ipi];
          for (int jpi=0; jpi<2; jpi++) {
            pi0_e_wTagN[ipi][jpi] = pi0_e[ipi][jpi];
            for (int idir=0; idir<3; idir++) {
              pi0_dir_wTagN[ipi][jpi][idir] = pi0_dir[ipi][jpi][idir];
            }
          }
        }
        nmue_wTagN = nmue;

        nscndprt_wTagN = numu->var<int>("nscndprt");
        for (int iscnd=0; iscnd<nscndprt_wTagN; iscnd++) {
          itrkscnd_wTagN[iscnd] = itrkscnd[iscnd];
          iprtscnd_wTagN[iscnd] = numu->var<int>("iprtscnd", iscnd);
          //tscnd_wTagN[iscnd]    = numu->var<float>("tscnd", iscnd);
          tscnd_wTagN[iscnd]    = tscnd[iscnd];
          iprntprt_wTagN[iscnd] = numu->var<int>("iprntprt", iscnd);
          lmecscnd_wTagN[iscnd] = numu->var<int>("lmecscnd", iscnd);
          iprnttrk_wTagN[iscnd] = iprnttrk[iscnd];
          iorgprt_wTagN[iscnd]  = iorgprt[iscnd];
          iflgscnd_wTagN[iscnd] = iflgscnd[iscnd];
          for (int idir=0; idir<3; idir++) {
            vtxscnd_wTagN[iscnd][idir] = numu->var<float>("vtxscnd", iscnd, idir);
            pscnd_wTagN[iscnd][idir]   = pscnd[iscnd][idir];
            pprnt_wTagN[iscnd][idir]   = pprnt[iscnd][idir];
          }
        }

        //SK variables
        nring_wTagN  = nring;
        nev_wTagN    = nev;
        nhitac_wTagN = numu->var<int>("nhitac");
        wall_wTagN   = wall;
        evis_wTagN   = evis;

        //fiTQun variables
        fqnse_wTagN = numu->var<int>("fqnse");
        for (Int_t ifq=0; ifq<fqnse_wTagN; ifq++) {
          for (int ihyp=0; ihyp<7; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fq1rdir_wTagN[ifq][ihyp][idir] = numu->var<float>("fq1rdir", ifq, ihyp, idir);
            }
          }
        }
        fqmome_wTagN = numu->var<float>("fq1rmom", 0, 1);
        fqmomm_wTagN = numu->var<float>("fq1rmom", 0, 2);

        fqnmrfit_wTagN = fqnmrfit;
        for (Int_t ifq=0; ifq<fqnmrfit; ifq++) {
          //ipp_wTagN[ifq] = fqmrifit[ifq];
          for (int ihyp=0; ihyp<6; ihyp++) {
            for (int idir=0; idir<3; idir++) {
              fqmrdir_wTagN[ifq][ihyp][idir] = fqmrdir[ifq][ihyp][idir];
              fqmrmom_wTagN[ifq][ihyp][idir] = fqmrmom[ifq][ihyp][idir];
            }
          }
        }

        //MR variables
        /*for (Int_t ifq=0; ifq<fqnmrfit; ifq++) {
          if (isnan(fqmrnll[ifq])) continue;
          int fitID = TMath::Abs(fqmrifit[ifq]); // fit ID (<0: regected by NR/(N+1)R likelihood ratio test)
          if(fitID==20000033) {
            ipp_wTagN[ifq] = ifq;
          }
        }*/
        if (nring_wTagN==0) {
          for (int iring=0; iring<100; iring++) {
            ip_wTagN[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_wTagN[iring][idir] = 0.;
            }
          }
        }
        else {
          for (int iring=0; iring<nring_wTagN; iring++) {
            ip_wTagN[iring] = 0;
            for (int idir=0; idir<3; idir++) {
              dir_wTagN[iring][idir] = 0.;
            }
          }
        }
        /*for (int iring=0; iring<nring_wTagN; iring++) {
          ip_wTagN[iring] = 0;
          for (int idir=0; idir<3; idir++) {
            dir_wTagN[iring][idir] = 0.;
          }
        }*/
        ipp_wTagN           = -1;
        ippp_wTagN          = -1;
        evisible_wTagN      = -1;
        elosssum_pipi_wTagN = -1;

        //NIWG variables
        wgts_maqeh_wTagN = 1.;
        DeltaPForEmiss0_wTagN = DeltaPForEmiss0;
      }

    } //New 1R muon selection

    if (NoTagN==0) woTagNtuple -> FillTree(0);
    if (NoTagN==1) wTagNtuple  -> FillTree(1);
  }



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
    resultfile << "[Neutrino] All Parent Neutrino Events: " << AllParentNeutrinos << std::endl;
    resultfile << "[Neutrino] Generated Neutrino Events(wallv>200): " << GeneratedEvents << std::endl;
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

    ntagana.SummaryTruthInfoinSearch(3., NTagSummary);
  }



  /*TFile* fout = new TFile(OutputRootName, "RECREATE");
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
  gDirectory -> cd("..");*/

  if (usentag==false) Ntuple -> WriteTree(OutSampleName+".NoNTag.root", 2);
  else {
    woTagNtuple -> WriteTree(OutSampleName+".woTagN.root", 0);
    wTagNtuple  -> WriteTree(OutSampleName+".wTagN.root", 1);
  }

}