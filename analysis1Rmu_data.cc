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


  const int nfQEntries       = tchfQ->GetEntries();       //total entries of TTree h1
  const int nevEntries       = tchev->GetEntries();       //total entries of TTree event
  const int ntagEntries      = tchntag->GetEntries();     //total entries of TTree ntag
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  fiTQun output     : Processing " << nfQEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Event info        : Processing " << nevEntries       <<" entries...\e[0m" << std::endl;
  std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  NTag output       : Processing " << ntagEntries      <<" entries...\e[0m" << std::endl;


  //=========  TTree event variables  ============
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

  NNInputVariables nninputs;
  nninputs.SetNNinputHisto();

  int allcandidates = 0;


  //Process
  if (nfQEntries==ntagEntries) processmax = ntagEntries;
  else return 1;

  for (int ientry=0; ientry<processmax; ientry++) {

  	//Progress meter
    if(ientry>1 && ientry%2==0) std::cout << "\e[38;5;70m\e[1m[### analysis1Rmu ###]  Progress: " << 100.*ientry/processmax << "%\e[0m" << std::endl;

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

    //allcandidates += TagOut->size();
    for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
      //h1_AllNTagOut -> Fill(TagOut->at(jentry));
    }

    //New 1R muon selection
    if (prmsel.Apply1RmuonSelection(evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, true)) {

      //float OscProb = numu->getOscWgt();
      float Enu     = numu->var<float>("erec");
      std::cout << "data = " << data << std::endl;

      //Neutrino energy distribution
      neuosc.GetRecoEnu(numu);

      /*int TagN = ntagana.GetTaggedNeutrons(TagOut, nlikeThreshold, NHits, FitT, Label, etagmode);
      GetSelectedTagN(prmsel, evsel, numu, decayebox, eMode, eOsc, dtMax, N50Min, N50Max, false, TagN);
      std::cout << "#tagged-n: " << TagN << std::endl;*/

      //std::cout << "TagOut: " << TagOut->size() << std::endl;
      allcandidates += TagOut->size();
      for (UInt_t jentry=0; jentry<TagOut->size(); ++jentry) {
        h1_AllNTagOut -> Fill(TagOut->at(jentry));
      }

    } //New 1R muon selection

  }

  std::cout << "#all candidates: " << allcandidates << std::endl;


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
      resultfile << "[Neutrino] C" << i+1 << ": " << ProtoSelectedParentNeutrinos[i] << " -> " << SelectedParentNeutrinos[i] << std::endl;
      h1_1RmuonEvents      -> SetBinContent(i+1, SelectedParentNeutrinos[i]);
      h1_Proto1RmuonEvents -> SetBinContent(i+1, ProtoSelectedParentNeutrinos[i]);
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

  nninputs.cdNNInputVariables(fout);
  nninputs.WritePlots();

  ntagana.cdNTagAnalysis(fout);
  ntagana.WritePlots(false);
  gDirectory -> cd("..");

}
