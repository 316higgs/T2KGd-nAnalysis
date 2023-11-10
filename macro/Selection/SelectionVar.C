#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC

#define DWALL 200
#define NRING 2
#define EMU   0
#define PMU   200
#define NDCYE 2
#define PIMU  0

#define CUTSTEP 6

TH1F* h1_CCQE_numu[CUTSTEP];
TH1F* h1_CC2p2h_numu[CUTSTEP];
TH1F* h1_CCOther_numu[CUTSTEP];
TH1F* h1_NC_numu[CUTSTEP];

TH1F* h1_CCQE_nuesig[CUTSTEP];
TH1F* h1_CC2p2h_nuesig[CUTSTEP];
TH1F* h1_CCOther_nuesig[CUTSTEP];
TH1F* h1_NC_nuesig[CUTSTEP];

TH1F* h1_CCQE_numubar[CUTSTEP];
TH1F* h1_CC2p2h_numubar[CUTSTEP];
TH1F* h1_CCOther_numubar[CUTSTEP];
TH1F* h1_NC_numubar[CUTSTEP];

TH1F* h1_CCQE_nuebarsig[CUTSTEP];
TH1F* h1_CC2p2h_nuebarsig[CUTSTEP];
TH1F* h1_CCOther_nuebarsig[CUTSTEP];
TH1F* h1_NC_nuebarsig[CUTSTEP];

TH1F* h1_CCQE_nuebkg[CUTSTEP];
TH1F* h1_CC2p2h_nuebkg[CUTSTEP];
TH1F* h1_CCOther_nuebkg[CUTSTEP];
TH1F* h1_NC_nuebkg[CUTSTEP];

TH1F* h1_CCQE_nuebarbkg[CUTSTEP];
TH1F* h1_CC2p2h_nuebarbkg[CUTSTEP];
TH1F* h1_CCOther_nuebarbkg[CUTSTEP];
TH1F* h1_NC_nuebarbkg[CUTSTEP];

THStack* hs_C[CUTSTEP];

TH1F* h1_data[CUTSTEP];

Double_t ExpN_numu_x_numu;
Double_t ExpN_numu_x_nue;
Double_t ExpN_numubar_x_numubar;
Double_t ExpN_numubar_x_nuebar;
Double_t ExpN_nue_x_nue;
Double_t ExpN_nuebar_x_nuebar;

Double_t GenN_numu_x_numu;
Double_t GenN_numu_x_nue;
Double_t GenN_numubar_x_numubar;
Double_t GenN_numubar_x_nuebar;
Double_t GenN_nue_x_nue;
Double_t GenN_nuebar_x_nuebar;

TString CCQEHistoName;
TString CC2p2hHistoName;
TString CCOtherHistoName;
TString NCHistoName;
TString DataHistoName;

TString SetHistoVarName(int istep);
void SetHisto(int istep, TFile* fin, int OscMode);
void SetHistoColor(int istep, bool data);
void ScaleHisto(int istep, int OscMode);
void SetTHStack(int istep);

void SelectionVar(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  //FHC
#if fhcflag
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar  = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue         = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar   = (TH1F*)fin_skrate->Get("skrate_nue_bar_x_nue_bar");
  ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  ExpN_numubar_x_nuebar    = h1_skrate_numubar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  ExpN_nue_x_nue           = h1_skrate_nue_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  ExpN_nuebar_x_nuebar     = h1_skrate_nuebar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  GenN_numu_x_numu       = 63622;
  GenN_numu_x_nue        = 63538;
  GenN_numubar_x_numubar = 63444;
  GenN_numubar_x_nuebar  = 63460;
  GenN_nue_x_nue         = 63423;
  GenN_nuebar_x_nuebar   = 63652;
  std::cout << "Misc. factor: " << (NA*FV*1.e-6) / (50.e-3) << std::endl;
  std::cout << "[numu  -> numu ] ExpN_numu_x_numu = " << h1_skrate_numu_x_numu->Integral() << std::endl;
  std::cout << "[numu  -> numu ] GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "[numu  -> numu ] Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "[numu  -> nue  ] ExpN_numu_x_nue = " << h1_skrate_numu_x_nue->Integral() << std::endl;
  std::cout << "[numu  -> nue  ] GenN_numu_x_nue = " << GenN_numu_x_nue << std::endl;
  std::cout << "[numu  -> nue  ] Normalization factor for numu_x_nue       : " << (ExpN_numu_x_nue)/(GenN_numu_x_nue) << std::endl;
  std::cout << "[numub -> numub] ExpN_numubar_x_numubar = " << h1_skrate_numubar_x_numubar->Integral() << std::endl;
  std::cout << "[numub -> numub] GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "[numub -> numub] Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;
  std::cout << "[numub -> nueb ] ExpN_numubar_x_nuebar = " << h1_skrate_numubar_x_nuebar->Integral() << std::endl;
  std::cout << "[numub -> nueb ] GenN_numubar_x_nuebar = " << GenN_numubar_x_nuebar << std::endl;
  std::cout << "[numub -> nueb ] Normalization factor for numubar_x_nuebar: " << (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) << std::endl;
  std::cout << "[nue   -> nue  ] ExpN_nue_x_nue = " << h1_skrate_nue_x_nue->Integral() << std::endl;
  std::cout << "[nue   -> nue  ] GenN_nue_x_nue = " << GenN_nue_x_nue << std::endl;
  std::cout << "[nue   -> nue  ] Normalization factor for nue_x_nue: " << (ExpN_nue_x_nue)/(GenN_nue_x_nue) << std::endl;
  std::cout << "[nueb  -> nueb ] ExpN_nuebar_x_nuebar = " << h1_skrate_nuebar_x_nuebar->Integral() << std::endl;
  std::cout << "[nueb  -> nueb ] GenN_nuebar_x_nuebar = " << GenN_nuebar_x_nuebar << std::endl;
  std::cout << "[nueb  -> nueb ] Normalization factor for nuebar_x_nuebar: " << (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) << std::endl;

  
  float y[2] = {0., 200.};
  float xC1[2] = {DWALL, DWALL};
  float xC2[2] = {NRING, NRING};
  float xC3[2] = {EMU, EMU};
  float xC4[2] = {PMU, PMU};
  float xC5[2] = {NDCYE, NDCYE};
  float xC6[2] = {PIMU, PIMU};
  TGraph* g_Cut[CUTSTEP];
  for (int i=0; i<CUTSTEP; i++) {
  	if (i==0) g_Cut[i] = new TGraph(2, xC1, y);
  	if (i==1) g_Cut[i] = new TGraph(2, xC2, y);
  	if (i==2) g_Cut[i] = new TGraph(2, xC3, y);
  	if (i==3) g_Cut[i] = new TGraph(2, xC4, y);
  	if (i==4) g_Cut[i] = new TGraph(2, xC5, y);
  	if (i==5) g_Cut[i] = new TGraph(2, xC6, y);
  	g_Cut[i] -> SetLineWidth(2);
    g_Cut[i] -> SetLineColor(kOrange+7);
    g_Cut[i] -> SetLineStyle(7);
  }


  TString VarPath = "Gd1RmuonSelection/h1_";
  TString suffix_CCQE    = "_mode0";
  TString suffix_CC2p2h  = "_mode1";
  TString suffix_CCOther = "_mode3";
  TString suffix_NC      = "_mode2";
  bool isData            = false;
  for (int istep=0; istep<CUTSTEP; istep++) {
  	TString VarName = SetHistoVarName(istep);
  	CCQEHistoName    = VarPath+VarName+suffix_CCQE;
    CC2p2hHistoName  = VarPath+VarName+suffix_CC2p2h;
    CCOtherHistoName = VarPath+VarName+suffix_CCOther;
    NCHistoName      = VarPath+VarName+suffix_NC;

    // Get original histograms
    SetHisto(istep, fin_numu, 0);      // numu -> numu
    SetHisto(istep, fin_nuesig, 1);    // numu -> nue
    SetHisto(istep, fin_numubar, 2);   // numubar -> numubar
    SetHisto(istep, fin_nuebarsig, 3); // numubar -> nuebar
    SetHisto(istep, fin_nuebkg, 4);    // nue -> nue
    SetHisto(istep, fin_nuebarbkg, 5); // nuebar -> nuebar

    // Color
    SetHistoColor(istep, isData);

    // Scale
    ScaleHisto(istep, 0);  // numu    -> numu
    ScaleHisto(istep, 1);  // numu    -> nue
    ScaleHisto(istep, 2);  // numubar -> numubar
    ScaleHisto(istep, 3);  // numubar -> nuebar
    ScaleHisto(istep, 4);  // nue     -> nue
    ScaleHisto(istep, 5);  // nuebar  -> nuebar

    // Stack
    SetTHStack(istep);
  }


  // Data
  isData = true;
  TFile* fin_data = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");
  for (int istep=0; istep<CUTSTEP; istep++) {
    TString VarName = SetHistoVarName(istep);
    DataHistoName = VarPath+"All"+VarName;
    //std::cout << DataHistoName << std::endl;

    SetHisto(istep, fin_data, 6); // data

    // Color
    SetHistoColor(istep, isData);
  }

  //#ring
  /*h1_data[1]->SetBinContent(3, 0.);
  h1_data[1]->SetBinContent(4, 0.);
  h1_data[1]->SetBinContent(5, 0.);
  h1_data[1]->SetBinError(3, 0.);
  h1_data[1]->SetBinError(4, 0.);
  h1_data[1]->SetBinError(5, 0.);*/
  

#if 1
  // Draw
  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.46, 0.46, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{ FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_CCQE_numu[0], "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar[0], "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu[0], "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar[0], "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu[0], "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar[0], "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCQE_nuesig[0], "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu[0], "NC", "F");
  legend1->SetFillColor(0);

  TCanvas* c = new TCanvas("c", "c", 1200, 800);
  c -> Divide(3,2);

  for (int istep=0; istep<CUTSTEP; istep++) {
  	c -> cd(istep+1) -> SetGrid();
    if (istep==0) hs_C[istep] -> SetMaximum(30);
    if (istep==1) hs_C[istep] -> SetMaximum(50);
    if (istep==4) hs_C[istep] -> SetMaximum(30);
    hs_C[istep] -> Draw();
    hs_C[istep] ->GetYaxis()->SetTitleSize(0.038);
    hs_C[istep] ->GetYaxis()->SetTitleOffset(1.3);
    hs_C[istep] ->GetYaxis()->SetLabelSize(0.036);
    hs_C[istep] -> Draw();
    h1_data[istep] -> Draw("SAME P E");
    g_Cut[istep]  -> Draw("SAME");
    if (istep==0) legend1->Draw();
  }
#endif

#if 0
  // Draw
  gROOT -> SetStyle("Plain");

  TCanvas* c = new TCanvas("c", "c", 1200, 800);
  c -> SetGrid();
  hs_C[4] -> SetMaximum(30);
  hs_C[4] -> Draw();
  //hs_C[4] ->GetYaxis()->SetTitleSize(0.038);
  //hs_C[4] ->GetYaxis()->SetTitleOffset(1.3);
  //hs_C[4] ->GetYaxis()->SetLabelSize(0.036);
  //hs_C[4] -> Draw();
  h1_data[4] -> Draw("SAME P E");
  //g_Cut[4]  -> Draw("SAME");
#endif
 
}




TString SetHistoVarName(int istep) {
  TString VarName = "dwall";
  switch (istep+1) {
    case 1:
      VarName = "dwall";
      break;
    case 2:
      VarName = "Nring";
      break;
    case 3:
      VarName = "emulikelihood";
      break;
    case 4:
      VarName = "Pmu";
      break;
    case 5:
      VarName = "Decaye";
      break;
    case 6:
      VarName = "pimulikelihood";
      break;
    default:
      VarName = "dwall";
      break;
  }
  return VarName;
}

void SetHisto(int istep, TFile* fin, int OscMode) {
  switch (OscMode) {
    case 0:
      h1_CCQE_numu[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_numu[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_numu[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_numu[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    case 1:
      h1_CCQE_nuesig[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_nuesig[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_nuesig[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_nuesig[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    case 2:
      h1_CCQE_numubar[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_numubar[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_numubar[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_numubar[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    case 3:
      h1_CCQE_nuebarsig[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_nuebarsig[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_nuebarsig[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_nuebarsig[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    case 4:
      h1_CCQE_nuebkg[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_nuebkg[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_nuebkg[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_nuebkg[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    case 5:
      h1_CCQE_nuebarbkg[istep]    = (TH1F*)fin->Get(CCQEHistoName);
      h1_CC2p2h_nuebarbkg[istep]  = (TH1F*)fin->Get(CC2p2hHistoName);
      h1_CCOther_nuebarbkg[istep] = (TH1F*)fin->Get(CCOtherHistoName);
      h1_NC_nuebarbkg[istep]      = (TH1F*)fin->Get(NCHistoName);
      break;
    default:
      h1_data[istep] = (TH1F*)fin->Get(DataHistoName);
      break;
  }
}

void ScaleHisto(int istep, int OscMode) {
  switch (OscMode) {
    case 0:
      h1_CCQE_numu[istep]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_CC2p2h_numu[istep]  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_CCOther_numu[istep] -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_NC_numu[istep]      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      break;
    case 1:
      h1_CCQE_nuesig[istep]    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_CC2p2h_nuesig[istep]  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_CCOther_nuesig[istep] -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_NC_nuesig[istep]      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      break;
    case 2:
      h1_CCQE_numubar[istep]    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_CC2p2h_numubar[istep]  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_CCOther_numubar[istep] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_NC_numubar[istep]      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      break;
    case 3:
      h1_CCQE_nuebarsig[istep]    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_CC2p2h_nuebarsig[istep]  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_CCOther_nuebarsig[istep] -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_NC_nuebarsig[istep]      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      break;
    case 4:
      h1_CCQE_nuebkg[istep]    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_CC2p2h_nuebkg[istep]  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_CCOther_nuebkg[istep] -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_NC_nuebkg[istep]      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 5:
      h1_CCQE_nuebarbkg[istep]    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
      h1_CC2p2h_nuebarbkg[istep]  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
      h1_CCOther_nuebarbkg[istep] -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
      h1_NC_nuebarbkg[istep]      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
      break;
    default:
      break;
  }
}

void SetTHStack(int istep) {
  switch (istep+1) {
    case 1:
      hs_C[istep] = new THStack("hs_C1", "1. Dwall #geq 2 m; fiTQun Dwall[cm]; ");
      break;
    case 2:
      hs_C[istep] = new THStack("hs_C2", "2. Single ring; Number of Rings; ");
      break;
    case 3:
      hs_C[istep] = new THStack("hs_C3", "3. #mu-like; e-#mu PID; ");
      break;
    case 4:
      hs_C[istep] = new THStack("hs_C4", "4. P_{#mu} #geq 200 MeV; #mu momentum[MeV/c]; ");
      break;
    case 5:
      hs_C[istep] = new THStack("hs_C5", "5. Decay-e #leq 1; Number of Decay-e; ");
      break;
    case 6:
      hs_C[istep] = new THStack("hs_C6", "6. Not#pi^{#pm}like; #pi^{#pm}-#mu PID; ");
      break;
  }

  //////  NC  //////
  hs_C[istep] -> Add(h1_NC_nuebarbkg[istep]);
  hs_C[istep] -> Add(h1_NC_nuebkg[istep]);
  hs_C[istep] -> Add(h1_NC_nuebarsig[istep]);
  hs_C[istep] -> Add(h1_NC_numubar[istep]);
  hs_C[istep] -> Add(h1_NC_nuesig[istep]);
  hs_C[istep] -> Add(h1_NC_numu[istep]);

  //////  CC nue/nuebar  //////
  hs_C[istep] -> Add(h1_CCOther_nuebarbkg[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_nuebarbkg[istep]);
  hs_C[istep] -> Add(h1_CCQE_nuebarbkg[istep]);
  hs_C[istep] -> Add(h1_CCOther_nuebkg[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_nuebkg[istep]);
  hs_C[istep] -> Add(h1_CCQE_nuebkg[istep]);
  hs_C[istep] -> Add(h1_CCOther_nuebarsig[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_nuebarsig[istep]);
  hs_C[istep] -> Add(h1_CCQE_nuebarsig[istep]);
  hs_C[istep] -> Add(h1_CCOther_nuesig[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_nuesig[istep]);
  hs_C[istep] -> Add(h1_CCQE_nuesig[istep]);

  //////  CC numu/numubar  //////
  hs_C[istep] -> Add(h1_CCOther_numubar[istep]);
  hs_C[istep] -> Add(h1_CCOther_numu[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_numubar[istep]);
  hs_C[istep] -> Add(h1_CC2p2h_numu[istep]);
  hs_C[istep] -> Add(h1_CCQE_numubar[istep]);
  hs_C[istep] -> Add(h1_CCQE_numu[istep]);
}

void SetHistoColor(int istep, bool data) {

  if (!data) {
    h1_CCQE_numu[istep]    -> SetLineColor(kAzure-1);
    h1_CCQE_numu[istep]    -> SetFillColor(kAzure-1);
    h1_CC2p2h_numu[istep]  -> SetLineColor(kAzure-5);
    h1_CC2p2h_numu[istep]  -> SetFillColor(kAzure-5);
    h1_CCOther_numu[istep] -> SetLineColor(kCyan-8);
    h1_CCOther_numu[istep] -> SetFillColor(kCyan-8);
    h1_NC_numu[istep]      -> SetLineColor(kSpring-9);
    h1_NC_numu[istep]      -> SetFillColor(kSpring-9);

    h1_CCQE_nuesig[istep]    -> SetLineColor(kViolet-1);
    h1_CCQE_nuesig[istep]    -> SetFillColor(kViolet-1);
    h1_CC2p2h_nuesig[istep]  -> SetLineColor(kViolet-1);
    h1_CC2p2h_nuesig[istep]  -> SetFillColor(kViolet-1);
    h1_CCOther_nuesig[istep] -> SetLineColor(kViolet-1);
    h1_CCOther_nuesig[istep] -> SetFillColor(kViolet-1);
    h1_NC_nuesig[istep]      -> SetLineColor(kSpring-9);
    h1_NC_nuesig[istep]      -> SetFillColor(kSpring-9);

    h1_CCQE_numubar[istep]    -> SetLineColor(kOrange+7);
    h1_CCQE_numubar[istep]    -> SetFillColor(kOrange+7);
    h1_CC2p2h_numubar[istep]  -> SetLineColor(kOrange+6);
    h1_CC2p2h_numubar[istep]  -> SetFillColor(kOrange+6);
    h1_CCOther_numubar[istep] -> SetLineColor(kOrange+0);
    h1_CCOther_numubar[istep] -> SetFillColor(kOrange+0);
    h1_NC_numubar[istep]      -> SetLineColor(kSpring-9);
    h1_NC_numubar[istep]      -> SetFillColor(kSpring-9);

    h1_CCQE_nuebarsig[istep]    -> SetLineColor(kViolet-1);
    h1_CCQE_nuebarsig[istep]    -> SetFillColor(kViolet-1);
    h1_CC2p2h_nuebarsig[istep]  -> SetLineColor(kViolet-1);
    h1_CC2p2h_nuebarsig[istep]  -> SetFillColor(kViolet-1);
    h1_CCOther_nuebarsig[istep] -> SetLineColor(kViolet-1);
    h1_CCOther_nuebarsig[istep] -> SetFillColor(kViolet-1);
    h1_NC_nuebarsig[istep]      -> SetLineColor(kSpring-9);
    h1_NC_nuebarsig[istep]      -> SetFillColor(kSpring-9);
  
    h1_CCQE_nuebkg[istep]    -> SetLineColor(kViolet-1);
    h1_CCQE_nuebkg[istep]    -> SetFillColor(kViolet-1);
    h1_CC2p2h_nuebkg[istep]  -> SetLineColor(kViolet-1);
    h1_CC2p2h_nuebkg[istep]  -> SetFillColor(kViolet-1);
    h1_CCOther_nuebkg[istep] -> SetLineColor(kViolet-1);
    h1_CCOther_nuebkg[istep] -> SetFillColor(kViolet-1);
    h1_NC_nuebkg[istep]      -> SetLineColor(kSpring-9);
    h1_NC_nuebkg[istep]      -> SetFillColor(kSpring-9);

    h1_CCQE_nuebarbkg[istep]    -> SetLineColor(kOrange+7);
    h1_CCQE_nuebarbkg[istep]    -> SetFillColor(kOrange+7);
    h1_CC2p2h_nuebarbkg[istep]  -> SetLineColor(kOrange+6);
    h1_CC2p2h_nuebarbkg[istep]  -> SetFillColor(kOrange+6);
    h1_CCOther_nuebarbkg[istep] -> SetLineColor(kOrange+0);
    h1_CCOther_nuebarbkg[istep] -> SetFillColor(kOrange+0);
    h1_NC_nuebarbkg[istep]      -> SetLineColor(kSpring-9);
    h1_NC_nuebarbkg[istep]      -> SetFillColor(kSpring-9);
  }
  else {
    h1_data[istep] -> SetMarkerStyle(20);
    h1_data[istep] -> SetMarkerSize(1.2);
    h1_data[istep] -> SetMarkerColor(kBlack);
    h1_data[istep] -> SetLineColor(kBlack);
    h1_data[istep] -> SetLineWidth(1.5);
  }
}



