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
  TString ETAGKeyword    = argv[6];
  TString ETAG           = argv[7];
  TString BeamKeyword    = argv[8];
  TString Beam           = argv[9];
  TString OscKeyword     = argv[10];
  TString Osc            = argv[11];

  enum BeamMode::E_BEAM_MODE eMode;
  enum OscChan::E_OSC_CHAN eOsc;
  eMode = CLTOptionBeamMode(BeamKeyword, Beam);
  eOsc  = CLTOptionOscMode(OscKeyword, Osc);
  CLTOptionETAG(ETAGKeyword, ETAG);

  if (Osc=="DATA") data = true;

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
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Loaded " << ntagFiles      << " files from: " << NtagFileName   << "\e[0m" << std::endl;


  const int nfQEntries  = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries  = tchev->GetEntries();       //total entries of TTree event
  const int ntagEntries = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries...\e[0m" << std::endl;


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
  tchntag->SetBranchAddress("Label", &Label, &bLabel);
  tchntag->SetBranchAddress("TagClass", &TagClass, &bTagClass);
  tchntag->SetBranchAddress("FitGoodness", &FitGoodness, &bFitGoodness);
  tchntag->SetBranchAddress("FitT", &FitT, &bFitT);
  tchntag->SetBranchAddress("DWall", &TagDWall, &bTagDWall);
  tchntag->SetBranchAddress("NHits", &NHits, &bNHits);
  tchntag->SetBranchAddress("N50", &N50, &bN50);
  tchntag->SetBranchAddress("TagIndex", &TagIndex, &bTagIndex);
  tchntag->SetBranchAddress("TagOut", &TagOut, &bTagOut);
  tchntag->SetBranchAddress("fvx", &fvx, &bfvx);
  tchntag->SetBranchAddress("fvy", &fvy, &bfvy);
  tchntag->SetBranchAddress("fvz", &fvz, &bfvz);
  
  CC0PiNumu *numu=new CC0PiNumu(eMode, eOsc); 
  numu->resisterDefaultAllStacks();
  numu->seth1Tree(tchfQ);

  UInt_t nrun;
  Int_t nev;
  Int_t nsub;
  Int_t nurun;
  Int_t nspill;
  tchfQ -> SetBranchAddress("nrun", &nrun);
  tchfQ -> SetBranchAddress("nev", &nev);
  tchfQ -> SetBranchAddress("nsub", &nsub);
  tchfQ -> SetBranchAddress("nurun", &nurun);
  tchfQ -> SetBranchAddress("nspill", &nspill);

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

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  int selnuevents   = 0;
  int selcandidates = 0;
  int selTagN = 0;
  int N1 = 0;
  int N2 = 0;
  int N3 = 0;
  int N4 = 0;

  //Process
  if (nfQEntries==ntagEntries) processmax = ntagEntries;
  else return 1;

  for (int ientry=0; ientry<processmax; ientry++) {

    //Progress meter
    //if(ientry>1 && ientry%2==0) std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Progress: " << 100.*ientry/processmax << "%\e[0m" << std::endl;

    //All neutrino events
    AllParentNeutrinos++;

    tchfQ       -> GetEntry(ientry);
    tchev       -> GetEntry(ientry);
    tchntag     -> GetEntry(ientry);

    Long64_t tentry = tchntag->LoadTree(ientry);
    bLabel       -> GetEntry(tentry);
    bTagClass    -> GetEntry(tentry);
    bFitGoodness -> GetEntry(tentry);
    bFitT        -> GetEntry(tentry);
    bTagDWall    -> GetEntry(tentry);
    bNHits       -> GetEntry(tentry);
    bN50         -> GetEntry(tentry);
    bTagIndex    -> GetEntry(tentry);
    bTagOut      -> GetEntry(tentry);
    bfvx         -> GetEntry(tentry);
    bfvy         -> GetEntry(tentry);
    bfvz         -> GetEntry(tentry);


    numu->computeCC0PiVariables();
    numu->applyfQ1RCC0PiNumuCut();
    const EvSelVar_t evsel = numu->getEvSelVar();
    Sequencial1RmuonSelection(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false);

    int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
    GetSelectedTagN(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false, TagN);

    for (int i=0; i<10; i++) h1_FC_run -> Fill(nspill);


    float RecoPrmVtx[3] = {0., 0., 0.};
    RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
    RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
    RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);


    //  data quality check
#if 1
    if (prmsel.C1ApplyFCFV(evsel)) {

      decayebox.GetDecayeInBox(numu, eMode, eOsc, dtMax, N50Min, N50Max, true);

      neuosc.GetPrmVtx(numu);

      ntagana.GetRecoNCapTime(numu, etagmode, FitT, NHits, Label, TagOut, nlikeThreshold);
      //ntagana.RecoNCapVtxProfile(TagOut, fvx, fvy, fvz, etagmode, N50, FitT, nlikeThreshold);

      selcandidates += TagOut->size();
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        //h1_AllRecoNCapTime -> Fill(FitT->at(jentry));
        //h1_AllNTagOut -> Fill(TagOut->at(jentry));
#if 1
        //h1_AllN50_preNN   -> Fill(N50->at(jentry));
        h1_AllNHits_preNN -> Fill(NHits->at(jentry));
        h1_AllFitT_preNN  -> Fill(FitT->at(jentry));
#endif

        bool etagboxin = false;
        etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry));
        if (TagOut->at(jentry)>nlikeThreshold) {

          if (NHits->at(jentry)<N50Min) {
            if (FitT->at(jentry)<dtMax) N1++;
            else N2++;
          }
          else {
            if (FitT->at(jentry)<dtMax) N3++;
            else N4++;
          } 

#if 1
          h1_AllN50_postNN   -> Fill(N50->at(jentry));
          
          h1_AllNHits_postNN -> Fill(NHits->at(jentry));
          if (FitT->at(jentry)<dtMax) h1_AllNHits_postNN_lt20us -> Fill(NHits->at(jentry));
          else h1_AllNHits_postNN_gt20us -> Fill(NHits->at(jentry));

          h1_AllFitT_postNN  -> Fill(FitT->at(jentry));
#endif

          float RecoNCapVtx[3] = {0., 0., 0.};
          RecoNCapVtx[0] = fvx->at(jentry);
          RecoNCapVtx[1] = fvy->at(jentry);
          RecoNCapVtx[2] = fvz->at(jentry);

          bool etagboxin = false;
          etagboxin = ntagana.DecayelikeChecker(etagmode, NHits->at(jentry), FitT->at(jentry));
          if (!etagboxin) {
            h1_AllNHits_Nlike -> Fill(NHits->at(jentry));
            h1_AllFitT_Nlike  -> Fill(FitT->at(jentry));
            h1_AllRecoNCapDistance -> Fill(GetSimpleDistance(RecoPrmVtx, RecoNCapVtx)/100.);
          }
          else {
            h1_AllNHits_Elike -> Fill(NHits->at(jentry));
            h1_AllFitT_Elike  -> Fill(FitT->at(jentry));
          }

          //selcandidates++;
          h1_AllNTagOut -> Fill(TagOut->at(jentry));
        }
      }
    }
#endif

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false)) {

      float Enu = numu->var<float>("erec");
      //std::cout << "data = " << data << std::endl;
      selnuevents++;

      //  Neutrino energy distribution
      neuosc.GetRecoEnu(numu);

      //ntagana.GetRecoNCapTime(numu, etagmode, FitT, NHits, Label, TagOut, nlikeThreshold);

      int numtaggedneutrons = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
      selTagN += numtaggedneutrons;

      if (numtaggedneutrons==0) {
        std::cout << "\e[38;5;94m\e[1m MR Run[ " << nurun << " ] Spill[ " << nspill << " ] SK Run[ " << nrun << " ] Ev[ " << nev << " ] Sub[ " << nsub << " ]\e[0m" << std::endl;
        for (int i=0; i<10; i++) h1_1Rmu_run -> Fill(nspill);  // make a band
      }
      else {
        std::cout << "\e[38;5;30m\e[1m MR Run[ " << nurun << " ] Spill[ " << nspill << " ] SK Run[ " << nrun << " ] Ev[ " << nev << " ] Sub[ " << nsub << " ] #tagged-n: " << numtaggedneutrons << "\e[0m" << std::endl;
        for (int i=0; i<10; i++) h1_1Rmu_run -> Fill(nspill);  // make a band
        for (int i=0; i<numtaggedneutrons; i++) h1_TagN_run -> Fill(nspill);
      }


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

      ntagana.RecoNCapVtxProfile(TagOut, fvx, fvy, fvz, etagmode, N50, FitT, nlikeThreshold);


      //  Neutron multiplicity
#if 1
      float Pmu         = numu->var<float>("fq1rmom", PrmEvent, FQ_MUHYP);
      float Pt          = neuosc.GetMuonPt(numu);
      float Qsquare     = neuosc.GetQsquare(numu);
      float recothetamu = neuosc.GetRecoMuDirection(numu);
      ntagana.N1Rmu_x_kinematics(numu, Enu/1000., xEnubins, N1Rmu_x_Enu, h1_N1Rmu_x_Enu, 0);
      ntagana.N1Rmu_x_kinematics(numu, Pmu/1000., xMuMombins, N1Rmu_x_MuMom, h1_N1Rmu_x_MuMom, 1);
      ntagana.N1Rmu_x_kinematics(numu, Pt/1000., xMuPtbins, N1Rmu_x_MuPt, h1_N1Rmu_x_MuPt, 1);
      ntagana.N1Rmu_x_kinematics(numu, Qsquare/1000000., xQ2bins, N1Rmu_x_Q2, h1_N1Rmu_x_Q2, 1);
      ntagana.N1Rmu_x_kinematics(numu, recothetamu, xMuAnglebins, N1Rmu_x_MuAngle, h1_N1Rmu_x_MuAngle, 1);

      h1_AllTagNmultiplicity -> Fill(numtaggedneutrons);
      ntagana.TaggedN_x_kinematics_data(numu, numtaggedneutrons, Enu/1000., xEnubins, TaggedN_x_Enu, h1_TaggedN_x_Enu, 0);
      ntagana.TaggedN_x_kinematics_data(numu, numtaggedneutrons, Pmu/1000., xMuMombins, TaggedN_x_MuMom, h1_TaggedN_x_MuMom, 1);
      ntagana.TaggedN_x_kinematics_data(numu, numtaggedneutrons, Pt/1000., xMuPtbins, TaggedN_x_MuPt, h1_TaggedN_x_MuPt, 1);
      ntagana.TaggedN_x_kinematics_data(numu, numtaggedneutrons, Qsquare/1000000., xQ2bins, TaggedN_x_Q2, h1_TaggedN_x_Q2, 1);
      ntagana.TaggedN_x_kinematics_data(numu, numtaggedneutrons, recothetamu, xMuAnglebins, TaggedN_x_MuAngle, h1_TaggedN_x_MuAngle, 1);
#endif
#if 1
      //float RecoPrmVtx[3] = {0., 0., 0.};
      //RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0);
      //RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1);
      //RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2);

      float NuBeamDir[3] = {0., 0., 0.};
      NuBeamDir[0] = beamDir[0];
      NuBeamDir[1] = beamDir[1];
      NuBeamDir[2] = beamDir[2];

      float RecoMuStpVtx[3] = {0., 0., 0.};
      float RecoMuRange     = decayebox.GetRecoMuEndVtx(numu, RecoMuStpVtx);

      for (UInt_t ican=0; ican<TagOut->size(); ican++) {
        if (etagmode){
          if (TagOut->at(ican)>nlikeThreshold && 
              ntagana.DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican))==false) {
            float NCapVtx[3]   = {fvx->at(ican), fvy->at(ican), fvz->at(ican)};  //Neutron capture vertex
            float nTraveld     = ndistance.TakeDistance(RecoPrmVtx, NCapVtx);    //Neutron flight distance
            float d_MuStp_NCap = ndistance.TakeDistance(RecoMuStpVtx, NCapVtx);  //Distance b/w muon stopping and neutron capture vertices
            float nTraveldv[3] = {0., 0., 0.};  //Neutron flight distance vector
            nTraveldv[0]       = NCapVtx[0] - RecoPrmVtx[0];
            nTraveldv[1]       = NCapVtx[1] - RecoPrmVtx[1];
            nTraveldv[2]       = NCapVtx[2] - RecoPrmVtx[2];
            float nTraveldL    = GetInnerProduct(nTraveldv, NuBeamDir);  //Longitudinal neutron flight distance
            float nTraveldT    = nTraveld*std::sin( std::acos( nTraveldL/nTraveld ) );
            float ncostheta    = nTraveldL/nTraveld;
            ntagana.TaggedN_x_Neutronkinematics_data(numu, nTraveld, xnTraveldbins, TaggedN_x_nTraveld, h1_TaggedN_x_nTraveld, 0);
            ntagana.TaggedN_x_Neutronkinematics_data(numu, d_MuStp_NCap, xMuStp_NCapbins, TaggedN_x_MuStp_NCap, h1_TaggedN_x_MuStp_NCap, 0);
            ntagana.TaggedN_x_Neutronkinematics_data(numu, nTraveldL, xnTraveldLbins, TaggedN_x_nTraveldL, h1_TaggedN_x_nTraveldL, 1);
            ntagana.TaggedN_x_Neutronkinematics_data(numu, nTraveldT, xnTraveldTbins, TaggedN_x_nTraveldT, h1_TaggedN_x_nTraveldT, 0);
            ntagana.TaggedN_x_Neutronkinematics_data(numu, ncostheta, xnAnglebins, TaggedN_x_nAngle, h1_TaggedN_x_nAngle, 2);
          }
        }
      }
#endif

    } //New 1R muon selection
    else {
      std::cout << "\e[38;5;00m\e[1m MR Run[ " << nurun << " ] Spill[ " << nspill << " ] SK Run[ " << nrun << " ] Ev[ " << nev << " ] Sub[ " << nsub << " ] \e[0m" << std::endl;
    }

  }

  std::cout << "#nu events : " << selnuevents << std::endl;
  std::cout << "#candidates: " << selcandidates << std::endl;
  std::cout << "#tagged-n  : " << selTagN << std::endl;


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
      h1_1RmuonEvents      -> SetBinContent(i+1, SelectedParentNeutrinos[i]);
      h1_Proto1RmuonEvents -> SetBinContent(i+1, ProtoSelectedParentNeutrinos[i]);
      h1_AllSelTagN        -> SetBinContent(i+1, SelectedAllTagN[i]);

      resultfile << "[Neutrino] C" << i+1 << ": " << ProtoSelectedParentNeutrinos[i] << " -> " << SelectedParentNeutrinos[i] << std::endl;
      resultfile << "[Neutron ] C" << i+1 << ": " << SelectedAllTagN[i] << std::endl;
    }

    resultfile << "N1: " << N1 << std::endl;
    resultfile << "N2: " << N2 << std::endl;
    resultfile << "N3: " << N3 << std::endl;
    resultfile << "N4: " << N4 << std::endl;

    float totalev = 0.;
    totalev = 0.;
    resultfile << "===== #1Rmu as a function of Pt =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#1Rmu @ Pt [" << xMuPtbins[ibin] << ", " << xMuPtbins[ibin+1] << "): " << N1Rmu_x_MuPt[ibin] << std::endl;
      else resultfile << "#1Rmu @ Pt > " << xMuPtbins[ibin] << ": " << N1Rmu_x_MuPt[ibin] << std::endl;
      totalev += N1Rmu_x_MuPt[ibin];
    }
    resultfile << "Total: " << totalev << std::endl;

    totalev = 0.;
    resultfile << "===== #tagged neutrons as a function of Pt =====" << std::endl;
    for (int ibin=0; ibin<binnumber_mu; ibin++) {
      if (ibin<binnumber_mu-1) resultfile << "#tagged-n @ Pt [" << xMuPtbins[ibin] << ", " << xMuPtbins[ibin+1] << "): " << TaggedN_x_MuPt[ibin] << std::endl;
      else resultfile << "#tagged-n @ Pt > " << xMuPtbins[ibin] << ": " << TaggedN_x_MuPt[ibin] << std::endl;
      totalev += TaggedN_x_MuPt[ibin];
    }
    resultfile << "Total: " << totalev << std::endl;

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

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

  ntagana.cdNTagAnalysis(fout);
  ntagana.WritePlots(false);
  gDirectory -> cd("..");

}
