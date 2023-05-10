#include "Gd1RmuonSelection.h"
#include "../../../include/NeutrinoEvents.h"

void Gd1RmuonSelection::SetHistoFrame() {
  h1_1RmuonEvents = new TH1F("h1_1RmuonEvents", "", 6, 0, 6);
  h1_Proto1RmuonEvents = new TH1F("h1_Proto1RmuonEvents", "", 6, 0, 6);
  for (int i=0; i<4; i++) {
    h1_SelNuEvents[i] = new TH1F(TString::Format("h1_SelNuEvents_mode%d", i), "", 6, 0, 6);
    h1_SelTagN[i]     = new TH1F(TString::Format("h1_SelTagN_mode%d", i), "", 6, 0, 6);
  }

  for (int i=0; i<INTERACTIONTYPE_FOR_MERGE; i++) {
    h1_dwall[i]          = new TH1F(TString::Format("h1_dwall_mode%d", i), "h1_dwall; fiTQun Dwall[cm]; Number of Neutrino Events", 30, 0, 600);
    h1_Nring[i]          = new TH1F(TString::Format("h1_Nring_mode%d", i), "h1_Nring; Number of Rings; Number of Neutrino Events", 5, 1, 6);
    h1_emulikelihood[i]  = new TH1F(TString::Format("h1_emulikelihood_mode%d", i), "h1_emulikelihood; e-#{mu} Likelihood; Number of Neutrino Events", 50, -1500, 1500);
    h1_Pmu[i]            = new TH1F(TString::Format("h1_Pmu_mode%d", i), "h1_Pmu; #{mu} Momentum P_{#mu}[MeV]; Number of Neutrino Events", 60, 0, 3000);
    h1_Decaye[i]         = new TH1F(TString::Format("h1_Decaye_mode%d", i), "h1_Decaye; Number of Decay-e; Number of Neutrino Events", 6, 0, 6);
    h1_pimulikelihood[i] = new TH1F(TString::Format("h1_pimulikelihood_mode%d", i), "h1_pimulikelihood; #pi^{#pm}-#{mu} Likelihood; Number of Neutrino Events", 40, -300, 100);
  }
}

void Gd1RmuonSelection::SetHistoFormat() {
  h1_1RmuonEvents -> SetLineWidth(2);
  h1_1RmuonEvents -> SetLineColor(kOrange+0);
  h1_1RmuonEvents -> SetTitleOffset(1.4, "Y");
  h1_1RmuonEvents -> SetTitleSize(0.035, "Y");
  h1_1RmuonEvents -> SetLabelSize(0.033, "Y");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_1RmuonEvents -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
  h1_1RmuonEvents -> SetStats(0);

  h1_Proto1RmuonEvents -> SetLineWidth(2);
  h1_Proto1RmuonEvents -> SetLineColor(kOrange+0);
  h1_Proto1RmuonEvents -> SetLineStyle(2);
  h1_Proto1RmuonEvents -> SetTitleOffset(1.4, "Y");
  h1_Proto1RmuonEvents -> SetTitleSize(0.035, "Y");
  h1_Proto1RmuonEvents -> SetLabelSize(0.033, "Y");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_Proto1RmuonEvents -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
  h1_Proto1RmuonEvents -> SetStats(0);

  for (int i=0; i<4; i++) {
    h1_SelNuEvents[i] -> SetLineWidth(2);
    h1_SelNuEvents[i] -> SetTitleOffset(1.4, "Y");
    h1_SelNuEvents[i] -> SetTitleSize(0.035, "Y");
    h1_SelNuEvents[i] -> SetLabelSize(0.033, "Y");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
    h1_SelNuEvents[i] -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
    h1_SelNuEvents[i] -> SetStats(0);

    h1_SelTagN[i] -> SetLineWidth(2);
    h1_SelTagN[i] -> SetTitleOffset(1.4, "Y");
    h1_SelTagN[i] -> SetTitleSize(0.035, "Y");
    h1_SelTagN[i] -> SetLabelSize(0.033, "Y");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
    h1_SelTagN[i] -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
    h1_SelTagN[i] -> SetStats(0);
  }

  for (int i=0; i<INTERACTIONTYPE_FOR_MERGE; i++) {
    h1_Nring[i] -> GetXaxis()->SetBinLabel(1, "1");
    h1_Nring[i] -> GetXaxis()->SetBinLabel(2, "2");
    h1_Nring[i] -> GetXaxis()->SetBinLabel(3, "3");
    h1_Nring[i] -> GetXaxis()->SetBinLabel(4, "4");
    h1_Nring[i] -> GetXaxis()->SetBinLabel(5, "5");

    h1_Decaye[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_Decaye[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_Decaye[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_Decaye[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_Decaye[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_Decaye[i] -> GetXaxis()->SetBinLabel(6, "5");
  }
}

float Gd1RmuonSelection::GetDWall(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  float dwall = numu->var<float>("fqdwall");
  if (mode==1)              h1_dwall[0] -> Fill(dwall); //CCQE
  if (mode>=2 && mode<=10)  h1_dwall[1] -> Fill(dwall); //CC 2p2h
  if (mode>=31)             h1_dwall[2] -> Fill(dwall); //NC
  if (mode>10 && mode<=30)  h1_dwall[3] -> Fill(dwall); //CC other

  return dwall;
}

int Gd1RmuonSelection::GetNring(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  int Nring = numu->var<int>("fqmrnring",0);
  if (mode==1)              h1_Nring[0] -> Fill(Nring); //CCQE
  if (mode>=2 && mode<=10)  h1_Nring[1] -> Fill(Nring); //CC 2p2h
  if (mode>=31)             h1_Nring[2] -> Fill(Nring); //NC
  if (mode>10 && mode<=30)  h1_Nring[3] -> Fill(Nring); //CC other

  return Nring;
}

float Gd1RmuonSelection::GetemuLikelihood(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  float likelihood = numu->var<float>("pidemu");
  if (mode==1)              h1_emulikelihood[0] -> Fill(likelihood);
  if (mode>=2 && mode<=10)  h1_emulikelihood[1] -> Fill(likelihood);
  if (mode>=31)             h1_emulikelihood[2] -> Fill(likelihood);
  if (mode>10 && mode<=30)  h1_emulikelihood[3] -> Fill(likelihood);

  return likelihood;
}

float Gd1RmuonSelection::GetPmu(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  float Pmu = numu->var<float>("fqmomm");
  if (mode==1)              h1_Pmu[0] -> Fill(Pmu);
  if (mode>=2 && mode<=10)  h1_Pmu[1] -> Fill(Pmu);
  if (mode>=31)             h1_Pmu[2] -> Fill(Pmu);
  if (mode>10 && mode<=30)  h1_Pmu[3] -> Fill(Pmu);

  return Pmu;
}

float Gd1RmuonSelection::GetpimuLikelihood(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));

  float likelihood = numu->var<float>("pidcpimu");
  if (mode==1)              h1_pimulikelihood[0] -> Fill(likelihood);
  if (mode>=2 && mode<=10)  h1_pimulikelihood[1] -> Fill(likelihood);
  if (mode>=31)             h1_pimulikelihood[2] -> Fill(likelihood);
  if (mode>10 && mode<=30)  h1_pimulikelihood[3] -> Fill(likelihood);

  return likelihood;
}


bool Gd1RmuonSelection::C1ApplyFCFV(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[0]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C2Apply1R(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[1]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C2Apply1RCheck(EvSelVar_t evsel, CC0PiNumu* numu, TreeManager* tree) {
  bool pass = false;
  if (evsel.pass[1]==true) pass = true;

  /*int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("pnu", 0);

  if (evsel.pass[1]==false && mode==1) {
    OneRingRejectCCQE = Enu;
    tree -> FillTree();
    //std::cout << "[Gd1RmuonSelection::C2Apply1RCheck()] 1R rejected CCQE: " << Enu << " GeV" << std::endl;
  }*/

  return pass;
}

bool Gd1RmuonSelection::C3Applymuonlike(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[2]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C4ApplyPmu200MeV(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[3]==true) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C4ApplyPe1MeV(CC0PiNumu* numu) {
  bool pass = false;
  float Pe = numu->var<float>("fq1rmom", 0, 1); //Primary electron
  if (Pe > 1.) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C5Applydecaye(EvSelVar_t evsel,
	                                  CC0PiNumu* numu,
	                                  DecayeBox decayebox, 
	                                  BeamMode::E_BEAM_MODE eMode, 
	                                  OscChan::E_OSC_CHAN eOsc,
	                                  float dtCut,
	                                  float N50CutMin,
	                                  float N50CutMax,
                                    bool dtvsn50fill) 
{
  bool pass = false;
  int NumDecaye = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill);
  //std::cout << "[### C5Applydecaye ###] #decay-e = " << NumDecaye << std::endl;
  if (NumDecaye<=1) pass = true;
  //if (NumDecaye==0) pass = true;
  return pass;
}

bool Gd1RmuonSelection::C5ApplyProtodecaye(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[4]==true) pass = true;
  return pass;	
}

bool Gd1RmuonSelection::C6Applynotpionlike(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[5]==true) pass = true;
  return pass;
}


bool Gd1RmuonSelection::Apply1RmuonSelection(EvSelVar_t evsel,
                                             CC0PiNumu* numu, 
	                                           DecayeBox decayebox, 
	                                           BeamMode::E_BEAM_MODE eMode, 
	                                           OscChan::E_OSC_CHAN eOsc,
	                                           float dtCut,
	                                           float N50CutMin,
	                                           float N50CutMax,
                                             bool dtvsn50fill) 
{
  bool pass = false;
  if (evsel.pass[0]==true &&
  	  evsel.pass[1]==true &&
  	  evsel.pass[2]==true &&
  	  evsel.pass[3]==true) 
  {
  	int NumDecaye = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill);
    //decayebox.GetDecayeTagPurity(numu, dtCut, N50CutMin, N50CutMax);

    int mode = TMath::Abs(numu->var<int>("mode"));
    if (mode==1)              h1_Decaye[0] -> Fill(NumDecaye);
    if (mode>=2 && mode<=10)  h1_Decaye[1] -> Fill(NumDecaye);
    if (mode>=31)             h1_Decaye[2] -> Fill(NumDecaye);
    if (mode>10 && mode<=30)  h1_Decaye[3] -> Fill(NumDecaye);

  	if (NumDecaye<=1 && evsel.pass[5]==true) pass = true;
  }
  return pass;
}

bool Gd1RmuonSelection::ApplyProto1RmuonSelection(EvSelVar_t evsel) {
  bool pass = false;
  if (evsel.pass[0]==true &&
  	  evsel.pass[1]==true &&
  	  evsel.pass[2]==true &&
  	  evsel.pass[3]==true &&
  	  evsel.pass[4]==true &&
  	  evsel.pass[5]==true) 
  {
  	pass = true;
  }
  return pass;
}

bool Gd1RmuonSelection::Apply1ReSelection(EvSelVar_t evsel,
                                             CC0PiNumu* numu, 
                                             DecayeBox decayebox, 
                                             BeamMode::E_BEAM_MODE eMode, 
                                             OscChan::E_OSC_CHAN eOsc,
                                             float dtCut,
                                             float N50CutMin,
                                             float N50CutMax,
                                             bool dtvsn50fill) 
{
  bool pass = false;
  if (evsel.pass[0]==true &&
      evsel.pass[1]==true &&
      evsel.pass[2]==false) 
  {
    float Pe = numu->var<float>("fq1rmom", 0, 1); //Primary electron
    int NumDecaye = decayebox.GetDecayeInBox(numu, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill);
    if (Pe > 1. && NumDecaye==0 && evsel.pass[5]==true) pass = true;
  }
  return pass;
}

void Gd1RmuonSelection::cdGd1RmuonSelection(TFile* fout) {
  fout -> mkdir("Gd1RmuonSelection");
  fout -> cd("Gd1RmuonSelection");
}

void Gd1RmuonSelection::WritePlots() {
  h1_1RmuonEvents      -> Write();
  h1_Proto1RmuonEvents -> Write();
  for (int i=0; i<4; i++) {
    h1_SelNuEvents[i] -> Write();
    h1_SelTagN[i]     -> Write();
  }

  for (int i=0; i<INTERACTIONTYPE_FOR_MERGE; i++) {
    h1_dwall[i]          -> Write();
    h1_Nring[i]          -> Write();
    h1_emulikelihood[i]  -> Write();
    h1_Pmu[i]            -> Write();
    h1_Decaye[i]         -> Write();
    h1_pimulikelihood[i] -> Write();
  }
}

