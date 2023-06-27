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

TH1F* h1_C1_CCQE_numu;
TH1F* h1_C1_CC2p2h_numu;
TH1F* h1_C1_CCOther_numu;
TH1F* h1_C1_NC_numu;
TH1F* h1_C1_CCQE_nuesig;
TH1F* h1_C1_CC2p2h_nuesig;
TH1F* h1_C1_CCOther_nuesig;
TH1F* h1_C1_NC_nuesig;
TH1F* h1_C1_CCQE_numubar;
TH1F* h1_C1_CC2p2h_numubar;
TH1F* h1_C1_CCOther_numubar;
TH1F* h1_C1_NC_numubar;
TH1F* h1_C1_CCQE_nuebarsig;
TH1F* h1_C1_CC2p2h_nuebarsig;
TH1F* h1_C1_CCOther_nuebarsig;
TH1F* h1_C1_NC_nuebarsig;
TH1F* h1_C1_CCQE_nuebkg;
TH1F* h1_C1_CC2p2h_nuebkg;
TH1F* h1_C1_CCOther_nuebkg;
TH1F* h1_C1_NC_nuebkg;

TH1F* h1_C2_CCQE_numu;
TH1F* h1_C2_CC2p2h_numu;
TH1F* h1_C2_CCOther_numu;
TH1F* h1_C2_NC_numu;
TH1F* h1_C2_CCQE_nuesig;
TH1F* h1_C2_CC2p2h_nuesig;
TH1F* h1_C2_CCOther_nuesig;
TH1F* h1_C2_NC_nuesig;
TH1F* h1_C2_CCQE_numubar;
TH1F* h1_C2_CC2p2h_numubar;
TH1F* h1_C2_CCOther_numubar;
TH1F* h1_C2_NC_numubar;
TH1F* h1_C2_CCQE_nuebarsig;
TH1F* h1_C2_CC2p2h_nuebarsig;
TH1F* h1_C2_CCOther_nuebarsig;
TH1F* h1_C2_NC_nuebarsig;
TH1F* h1_C2_CCQE_nuebkg;
TH1F* h1_C2_CC2p2h_nuebkg;
TH1F* h1_C2_CCOther_nuebkg;
TH1F* h1_C2_NC_nuebkg;

TH1F* h1_C3_CCQE_numu;
TH1F* h1_C3_CC2p2h_numu;
TH1F* h1_C3_CCOther_numu;
TH1F* h1_C3_NC_numu;
TH1F* h1_C3_CCQE_nuesig;
TH1F* h1_C3_CC2p2h_nuesig;
TH1F* h1_C3_CCOther_nuesig;
TH1F* h1_C3_NC_nuesig;
TH1F* h1_C3_CCQE_numubar;
TH1F* h1_C3_CC2p2h_numubar;
TH1F* h1_C3_CCOther_numubar;
TH1F* h1_C3_NC_numubar;
TH1F* h1_C3_CCQE_nuebarsig;
TH1F* h1_C3_CC2p2h_nuebarsig;
TH1F* h1_C3_CCOther_nuebarsig;
TH1F* h1_C3_NC_nuebarsig;
TH1F* h1_C3_CCQE_nuebkg;
TH1F* h1_C3_CC2p2h_nuebkg;
TH1F* h1_C3_CCOther_nuebkg;
TH1F* h1_C3_NC_nuebkg;

TH1F* h1_C4_CCQE_numu;
TH1F* h1_C4_CC2p2h_numu;
TH1F* h1_C4_CCOther_numu;
TH1F* h1_C4_NC_numu;
TH1F* h1_C4_CCQE_nuesig;
TH1F* h1_C4_CC2p2h_nuesig;
TH1F* h1_C4_CCOther_nuesig;
TH1F* h1_C4_NC_nuesig;
TH1F* h1_C4_CCQE_numubar;
TH1F* h1_C4_CC2p2h_numubar;
TH1F* h1_C4_CCOther_numubar;
TH1F* h1_C4_NC_numubar;
TH1F* h1_C4_CCQE_nuebarsig;
TH1F* h1_C4_CC2p2h_nuebarsig;
TH1F* h1_C4_CCOther_nuebarsig;
TH1F* h1_C4_NC_nuebarsig;
TH1F* h1_C4_CCQE_nuebkg;
TH1F* h1_C4_CC2p2h_nuebkg;
TH1F* h1_C4_CCOther_nuebkg;
TH1F* h1_C4_NC_nuebkg;

TH1F* h1_C5_CCQE_numu;
TH1F* h1_C5_CC2p2h_numu;
TH1F* h1_C5_CCOther_numu;
TH1F* h1_C5_NC_numu;
TH1F* h1_C5_CCQE_nuesig;
TH1F* h1_C5_CC2p2h_nuesig;
TH1F* h1_C5_CCOther_nuesig;
TH1F* h1_C5_NC_nuesig;
TH1F* h1_C5_CCQE_numubar;
TH1F* h1_C5_CC2p2h_numubar;
TH1F* h1_C5_CCOther_numubar;
TH1F* h1_C5_NC_numubar;
TH1F* h1_C5_CCQE_nuebarsig;
TH1F* h1_C5_CC2p2h_nuebarsig;
TH1F* h1_C5_CCOther_nuebarsig;
TH1F* h1_C5_NC_nuebarsig;
TH1F* h1_C5_CCQE_nuebkg;
TH1F* h1_C5_CC2p2h_nuebkg;
TH1F* h1_C5_CCOther_nuebkg;
TH1F* h1_C5_NC_nuebkg;

TH1F* h1_C6_CCQE_numu;
TH1F* h1_C6_CC2p2h_numu;
TH1F* h1_C6_CCOther_numu;
TH1F* h1_C6_NC_numu;
TH1F* h1_C6_CCQE_nuesig;
TH1F* h1_C6_CC2p2h_nuesig;
TH1F* h1_C6_CCOther_nuesig;
TH1F* h1_C6_NC_nuesig;
TH1F* h1_C6_CCQE_numubar;
TH1F* h1_C6_CC2p2h_numubar;
TH1F* h1_C6_CCOther_numubar;
TH1F* h1_C6_NC_numubar;
TH1F* h1_C6_CCQE_nuebarsig;
TH1F* h1_C6_CC2p2h_nuebarsig;
TH1F* h1_C6_CCOther_nuebarsig;
TH1F* h1_C6_NC_nuebarsig;
TH1F* h1_C6_CCQE_nuebkg;
TH1F* h1_C6_CC2p2h_nuebkg;
TH1F* h1_C6_CCOther_nuebkg;
TH1F* h1_C6_NC_nuebkg;

Double_t ExpN_numu_x_numu;
Double_t ExpN_numu_x_nue;
Double_t ExpN_numubar_x_numubar;
Double_t ExpN_numubar_x_nuebar;
Double_t ExpN_nue_x_nue;

Double_t GenN_numu_x_numu;
Double_t GenN_numu_x_nue;
Double_t GenN_numubar_x_numubar;
Double_t GenN_numubar_x_nuebar;
Double_t GenN_nue_x_nue;


void SetHistoColor();
void ScaleHisto(int step);

void SelVal(bool beammode) {

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar  = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue         = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar   = (TH1F*)fin_skrate->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar    = h1_skrate_numubar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue           = h1_skrate_nue_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar     = h1_skrate_nuebar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu       = 63622;
  Double_t GenN_numu_x_nue        = 63538;
  Double_t GenN_numubar_x_numubar = 63444;
  Double_t GenN_numubar_x_nuebar  = 63463;
  Double_t GenN_nue_x_nue         = 63379;
  Double_t GenN_nuebar_x_nuebar   = 63463;
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
  TGraph* g_C1 = new TGraph(2, xC1, y);
  g_C1 -> SetLineWidth(2);
  g_C1 -> SetLineColor(kViolet-8);
  g_C1 -> SetLineStyle(7);
  TGraph* g_C2 = new TGraph(2, xC2, y);
  g_C2 -> SetLineWidth(2);
  g_C2 -> SetLineColor(kViolet-8);
  g_C2 -> SetLineStyle(7);
  TGraph* g_C3 = new TGraph(2, xC3, y);
  g_C3 -> SetLineWidth(2);
  g_C3 -> SetLineColor(kViolet-8);
  g_C3 -> SetLineStyle(7);
  TGraph* g_C4 = new TGraph(2, xC4, y);
  g_C4 -> SetLineWidth(2);
  g_C4 -> SetLineColor(kViolet-8);
  g_C4 -> SetLineStyle(7);
  TGraph* g_C5 = new TGraph(2, xC5, y);
  g_C5 -> SetLineWidth(2);
  g_C5 -> SetLineColor(kViolet-8);
  g_C5 -> SetLineStyle(7);
  TGraph* g_C6 = new TGraph(2, xC6, y);
  g_C6 -> SetLineWidth(2);
  g_C6 -> SetLineColor(kViolet-8);
  g_C6 -> SetLineStyle(7);


  //--- Dwall ------------------------
  h1_C1_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_dwall_mode0");
  h1_C1_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_dwall_mode1");
  h1_C1_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_dwall_mode3");
  h1_C1_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_dwall_mode2");
  h1_C1_CCQE_numu -> SetStats(0);

  h1_C1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_dwall_mode0");
  h1_C1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_dwall_mode1");
  h1_C1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_dwall_mode3");
  h1_C1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_dwall_mode2");
  h1_C1_CCQE_nuesig -> SetStats(0);

  h1_C1_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_dwall_mode0");
  h1_C1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_dwall_mode1");
  h1_C1_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_dwall_mode3");
  h1_C1_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_dwall_mode2");
  h1_C1_CCQE_numubar -> SetStats(0);

  h1_C1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_dwall_mode0");
  h1_C1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_dwall_mode1");
  h1_C1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_dwall_mode3");
  h1_C1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_dwall_mode2");
  h1_C1_CCQE_nuebarsig -> SetStats(0);

  h1_C1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_dwall_mode0");
  h1_C1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_dwall_mode1");
  h1_C1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_dwall_mode3");
  h1_C1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_dwall_mode2");
  h1_C1_CCQE_nuebkg -> SetStats(0);

  THStack* hs_C1 = new THStack("hs_C1", "1. Dwall #geq 2 m; fiTQun Dwall[cm]; ");
  ScaleHisto(1);
#if fhcflag
  //hs_C1 -> Add(h1_C1_NC_nuebkg);
  //hs_C1 -> Add(h1_C1_NC_nuebarsig);
  hs_C1 -> Add(h1_C1_NC_numubar);
  hs_C1 -> Add(h1_C1_NC_nuesig);
  hs_C1 -> Add(h1_C1_NC_numu);
  //hs_C1 -> Add(h1_C1_CCOther_nuebkg);
  //hs_C1 -> Add(h1_C1_CC2p2h_nuebkg);
  //hs_C1 -> Add(h1_C1_CCQE_nuebkg);
  //hs_C1 -> Add(h1_C1_CCOther_nuebarsig);
  //hs_C1 -> Add(h1_C1_CC2p2h_nuebarsig);
  //hs_C1 -> Add(h1_C1_CCQE_nuebarsig);
  hs_C1 -> Add(h1_C1_CCOther_nuesig);
  hs_C1 -> Add(h1_C1_CC2p2h_nuesig);
  hs_C1 -> Add(h1_C1_CCQE_nuesig);
  hs_C1 -> Add(h1_C1_CCOther_numubar);
  hs_C1 -> Add(h1_C1_CCOther_numu);
  hs_C1 -> Add(h1_C1_CC2p2h_numubar);
  hs_C1 -> Add(h1_C1_CC2p2h_numu);
  hs_C1 -> Add(h1_C1_CCQE_numubar);
  hs_C1 -> Add(h1_C1_CCQE_numu);
#endif
#if rhcflag
  hs_C1 -> Add(h1_C1_NC_numu);
  hs_C1 -> Add(h1_C1_NC_numubar);
  hs_C1 -> Add(h1_C1_CCOther_numu);
  hs_C1 -> Add(h1_C1_CCOther_numubar);
  hs_C1 -> Add(h1_C1_CC2p2h_numu);
  hs_C1 -> Add(h1_C1_CC2p2h_numubar);
  hs_C1 -> Add(h1_C1_CCQE_numu);
  hs_C1 -> Add(h1_C1_CCQE_numubar);
#endif

  //--- Nring ------------------------
  h1_C2_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Nring_mode0");
  h1_C2_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Nring_mode1");
  h1_C2_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Nring_mode3");
  h1_C2_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Nring_mode2");
  h1_C2_CCQE_numu -> SetStats(0);

  h1_C2_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Nring_mode0");
  h1_C2_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Nring_mode1");
  h1_C2_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Nring_mode3");
  h1_C2_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Nring_mode2");
  h1_C2_CCQE_nuesig -> SetStats(0);

  h1_C2_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Nring_mode0");
  h1_C2_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Nring_mode1");
  h1_C2_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Nring_mode3");
  h1_C2_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Nring_mode2");
  h1_C2_CCQE_numubar -> SetStats(0);

  h1_C2_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Nring_mode0");
  h1_C2_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Nring_mode1");
  h1_C2_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Nring_mode3");
  h1_C2_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Nring_mode2");
  h1_C2_CCQE_nuebarsig -> SetStats(0);

  h1_C2_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Nring_mode0");
  h1_C2_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Nring_mode1");
  h1_C2_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Nring_mode3");
  h1_C2_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Nring_mode2");
  h1_C2_CCQE_nuebkg -> SetStats(0);

  THStack* hs_C2 = new THStack("hs_C2", "2. Single ring; Number of Rings; ");
  ScaleHisto(2);
#if fhcflag
  hs_C2 -> Add(h1_C2_NC_nuebkg);
  hs_C2 -> Add(h1_C2_NC_nuebarsig);
  hs_C2 -> Add(h1_C2_NC_numubar);
  hs_C2 -> Add(h1_C2_NC_nuesig);
  hs_C2 -> Add(h1_C2_NC_numu);
  hs_C2 -> Add(h1_C2_CCOther_nuebkg);
  hs_C2 -> Add(h1_C2_CC2p2h_nuebkg);
  hs_C2 -> Add(h1_C2_CCQE_nuebkg);
  hs_C2 -> Add(h1_C2_CCOther_nuebarsig);
  hs_C2 -> Add(h1_C2_CC2p2h_nuebarsig);
  hs_C2 -> Add(h1_C2_CCQE_nuebarsig);
  hs_C2 -> Add(h1_C2_CCOther_nuesig);
  hs_C2 -> Add(h1_C2_CC2p2h_nuesig);
  hs_C2 -> Add(h1_C2_CCQE_nuesig);
  hs_C2 -> Add(h1_C2_CCOther_numubar);
  hs_C2 -> Add(h1_C2_CCOther_numu);
  hs_C2 -> Add(h1_C2_CC2p2h_numubar);
  hs_C2 -> Add(h1_C2_CC2p2h_numu);
  hs_C2 -> Add(h1_C2_CCQE_numubar);
  hs_C2 -> Add(h1_C2_CCQE_numu);
#endif
#if rhcflag
  hs_C2 -> Add(h1_C2_NC_numu);
  hs_C2 -> Add(h1_C2_NC_numubar);
  hs_C2 -> Add(h1_C2_CCOther_numu);
  hs_C2 -> Add(h1_C2_CCOther_numubar);
  hs_C2 -> Add(h1_C2_CC2p2h_numu);
  hs_C2 -> Add(h1_C2_CC2p2h_numubar);
  hs_C2 -> Add(h1_C2_CCQE_numu);
  hs_C2 -> Add(h1_C2_CCQE_numubar);
#endif


  //--- mu/e PID ------------------------
  h1_C3_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_emulikelihood_mode0");
  h1_C3_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_emulikelihood_mode1");
  h1_C3_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_emulikelihood_mode3");
  h1_C3_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_emulikelihood_mode2");
  h1_C3_CCQE_numu -> SetStats(0);

  h1_C3_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_emulikelihood_mode0");
  h1_C3_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_emulikelihood_mode1");
  h1_C3_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_emulikelihood_mode3");
  h1_C3_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_emulikelihood_mode2");
  h1_C3_CCQE_nuesig -> SetStats(0);

  h1_C3_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_emulikelihood_mode0");
  h1_C3_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_emulikelihood_mode1");
  h1_C3_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_emulikelihood_mode3");
  h1_C3_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_emulikelihood_mode2");
  h1_C3_CCQE_numubar -> SetStats(0);

  h1_C3_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_emulikelihood_mode0");
  h1_C3_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_emulikelihood_mode1");
  h1_C3_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_emulikelihood_mode3");
  h1_C3_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_emulikelihood_mode2");
  h1_C3_CCQE_nuebarsig -> SetStats(0);

  h1_C3_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_emulikelihood_mode0");
  h1_C3_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_emulikelihood_mode1");
  h1_C3_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_emulikelihood_mode3");
  h1_C3_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_emulikelihood_mode2");
  h1_C3_CCQE_nuebkg -> SetStats(0);
  
  THStack* hs_C3 = new THStack("hs_C3", "3. #mu-like; e-#mu PID; ");
  ScaleHisto(3);
#if fhcflag
  hs_C3 -> Add(h1_C3_NC_nuebkg);
  hs_C3 -> Add(h1_C3_NC_nuebarsig);
  hs_C3 -> Add(h1_C3_NC_numubar);
  hs_C3 -> Add(h1_C3_NC_nuesig);
  hs_C3 -> Add(h1_C3_NC_numu);
  hs_C3 -> Add(h1_C3_CCOther_nuebkg);
  hs_C3 -> Add(h1_C3_CC2p2h_nuebkg);
  hs_C3 -> Add(h1_C3_CCQE_nuebkg);
  hs_C3 -> Add(h1_C3_CCOther_nuebarsig);
  hs_C3 -> Add(h1_C3_CC2p2h_nuebarsig);
  hs_C3 -> Add(h1_C3_CCQE_nuebarsig);
  hs_C3 -> Add(h1_C3_CCOther_nuesig);
  hs_C3 -> Add(h1_C3_CC2p2h_nuesig);
  hs_C3 -> Add(h1_C3_CCQE_nuesig);
  hs_C3 -> Add(h1_C3_CCOther_numubar);
  hs_C3 -> Add(h1_C3_CCOther_numu);
  hs_C3 -> Add(h1_C3_CC2p2h_numubar);
  hs_C3 -> Add(h1_C3_CC2p2h_numu);
  hs_C3 -> Add(h1_C3_CCQE_numubar);
  hs_C3 -> Add(h1_C3_CCQE_numu);
#endif
#if rhcflag
  hs_C3 -> Add(h1_C3_NC_numu);
  hs_C3 -> Add(h1_C3_NC_numubar);
  hs_C3 -> Add(h1_C3_CCOther_numu);
  hs_C3 -> Add(h1_C3_CCOther_numubar);
  hs_C3 -> Add(h1_C3_CC2p2h_numu);
  hs_C3 -> Add(h1_C3_CC2p2h_numubar);
  hs_C3 -> Add(h1_C3_CCQE_numu);
  hs_C3 -> Add(h1_C3_CCQE_numubar);
#endif

  //--- mu momentum ------------------------
  h1_C4_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Pmu_mode0");
  h1_C4_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Pmu_mode1");
  h1_C4_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Pmu_mode3");
  h1_C4_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Pmu_mode2");
  h1_C4_CCQE_numu -> SetStats(0);

  h1_C4_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Pmu_mode0");
  h1_C4_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Pmu_mode1");
  h1_C4_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Pmu_mode3");
  h1_C4_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Pmu_mode2");
  h1_C4_CCQE_nuesig -> SetStats(0);

  h1_C4_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Pmu_mode0");
  h1_C4_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Pmu_mode1");
  h1_C4_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Pmu_mode3");
  h1_C4_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Pmu_mode2");
  h1_C4_CCQE_numubar -> SetStats(0);

  h1_C4_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Pmu_mode0");
  h1_C4_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Pmu_mode1");
  h1_C4_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Pmu_mode3");
  h1_C4_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Pmu_mode2");
  h1_C4_CCQE_nuebarsig -> SetStats(0);

  h1_C4_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Pmu_mode0");
  h1_C4_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Pmu_mode1");
  h1_C4_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Pmu_mode3");
  h1_C4_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Pmu_mode2");
  h1_C4_CCQE_nuebkg -> SetStats(0);
  
  THStack* hs_C4 = new THStack("hs_C4", "4. P_{#mu} #geq 200 MeV; #mu momentum[MeV/c]; ");
  ScaleHisto(4);
#if fhcflag
  hs_C4 -> Add(h1_C4_NC_nuebkg);
  hs_C4 -> Add(h1_C4_NC_nuebarsig);
  hs_C4 -> Add(h1_C4_NC_numubar);
  hs_C4 -> Add(h1_C4_NC_nuesig);
  hs_C4 -> Add(h1_C4_NC_numu);
  hs_C4 -> Add(h1_C4_CCOther_nuebkg);
  hs_C4 -> Add(h1_C4_CC2p2h_nuebkg);
  hs_C4 -> Add(h1_C4_CCQE_nuebkg);
  hs_C4 -> Add(h1_C4_CCOther_nuebarsig);
  hs_C4 -> Add(h1_C4_CC2p2h_nuebarsig);
  hs_C4 -> Add(h1_C4_CCQE_nuebarsig);
  hs_C4 -> Add(h1_C4_CCOther_nuesig);
  hs_C4 -> Add(h1_C4_CC2p2h_nuesig);
  hs_C4 -> Add(h1_C4_CCQE_nuesig);
  hs_C4 -> Add(h1_C4_CCOther_numubar);
  hs_C4 -> Add(h1_C4_CCOther_numu);
  hs_C4 -> Add(h1_C4_CC2p2h_numubar);
  hs_C4 -> Add(h1_C4_CC2p2h_numu);
  hs_C4 -> Add(h1_C4_CCQE_numubar);
  hs_C4 -> Add(h1_C4_CCQE_numu);
#endif
#if rhcflag
  hs_C4 -> Add(h1_C4_NC_numu);
  hs_C4 -> Add(h1_C4_NC_numubar);
  hs_C4 -> Add(h1_C4_CCOther_numu);
  hs_C4 -> Add(h1_C4_CCOther_numubar);
  hs_C4 -> Add(h1_C4_CC2p2h_numu);
  hs_C4 -> Add(h1_C4_CC2p2h_numubar);
  hs_C4 -> Add(h1_C4_CCQE_numu);
  hs_C4 -> Add(h1_C4_CCQE_numubar);
#endif

  //--- Decay-e ------------------------
  h1_C5_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  h1_C5_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  h1_C5_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  h1_C5_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_C5_CCQE_numu -> SetStats(0);

  h1_C5_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  h1_C5_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  h1_C5_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  h1_C5_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_C5_CCQE_nuesig -> SetStats(0);

  h1_C5_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  h1_C5_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  h1_C5_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  h1_C5_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_C5_CCQE_numubar -> SetStats(0);

  h1_C5_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  h1_C5_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  h1_C5_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  h1_C5_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_C5_CCQE_nuebarsig -> SetStats(0);

  h1_C5_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  h1_C5_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  h1_C5_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  h1_C5_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_C5_CCQE_nuebkg -> SetStats(0);
  
  THStack* hs_C5 = new THStack("hs_C5", "5. Decay-e #leq 1; Number of Decay-e; ");
  ScaleHisto(5);
#if fhcflag
  hs_C5 -> Add(h1_C5_NC_nuebkg);
  hs_C5 -> Add(h1_C5_NC_nuebarsig);
  hs_C5 -> Add(h1_C5_NC_numubar);
  hs_C5 -> Add(h1_C5_NC_nuesig);
  hs_C5 -> Add(h1_C5_NC_numu);
  hs_C5 -> Add(h1_C5_CCOther_nuebkg);
  hs_C5 -> Add(h1_C5_CC2p2h_nuebkg);
  hs_C5 -> Add(h1_C5_CCQE_nuebkg);
  hs_C5 -> Add(h1_C5_CCOther_nuebarsig);
  hs_C5 -> Add(h1_C5_CC2p2h_nuebarsig);
  hs_C5 -> Add(h1_C5_CCQE_nuebarsig);
  hs_C5 -> Add(h1_C5_CCOther_nuesig);
  hs_C5 -> Add(h1_C5_CC2p2h_nuesig);
  hs_C5 -> Add(h1_C5_CCQE_nuesig);
  hs_C5 -> Add(h1_C5_CCOther_numubar);
  hs_C5 -> Add(h1_C5_CCOther_numu);
  hs_C5 -> Add(h1_C5_CC2p2h_numubar);
  hs_C5 -> Add(h1_C5_CC2p2h_numu);
  hs_C5 -> Add(h1_C5_CCQE_numubar);
  hs_C5 -> Add(h1_C5_CCQE_numu);
#endif
#if rhcflag
  hs_C5 -> Add(h1_C5_NC_numu);
  hs_C5 -> Add(h1_C5_NC_numubar);
  hs_C5 -> Add(h1_C5_CCOther_numu);
  hs_C5 -> Add(h1_C5_CCOther_numubar);
  hs_C5 -> Add(h1_C5_CC2p2h_numu);
  hs_C5 -> Add(h1_C5_CC2p2h_numubar);
  hs_C5 -> Add(h1_C5_CCQE_numu);
  hs_C5 -> Add(h1_C5_CCQE_numubar);
#endif

  //--- pi/mu likelihood ------------------------
  h1_C6_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_pimulikelihood_mode0");
  h1_C6_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_pimulikelihood_mode1");
  h1_C6_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_pimulikelihood_mode3");
  h1_C6_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_pimulikelihood_mode2");
  h1_C6_CCQE_numu -> SetStats(0);

  h1_C6_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode0");
  h1_C6_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode1");
  h1_C6_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode3");
  h1_C6_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode2");
  h1_C6_CCQE_nuesig -> SetStats(0);

  h1_C6_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_pimulikelihood_mode0");
  h1_C6_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_pimulikelihood_mode1");
  h1_C6_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_pimulikelihood_mode3");
  h1_C6_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_pimulikelihood_mode2");
  h1_C6_CCQE_numubar -> SetStats(0);

  h1_C6_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode0");
  h1_C6_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode1");
  h1_C6_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode3");
  h1_C6_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_pimulikelihood_mode2");
  h1_C6_CCQE_nuebarsig -> SetStats(0);

  h1_C6_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_pimulikelihood_mode0");
  h1_C6_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_pimulikelihood_mode1");
  h1_C6_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_pimulikelihood_mode3");
  h1_C6_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_pimulikelihood_mode2");
  h1_C6_CCQE_nuebkg -> SetStats(0);
  
  THStack* hs_C6 = new THStack("hs_C6", "6. Not#pi^{#pm}like; #pi^{#pm}-#mu PID; ");
  ScaleHisto(6);
#if fhcflag
  hs_C6 -> Add(h1_C6_NC_nuebkg);
  hs_C6 -> Add(h1_C6_NC_nuebarsig);
  hs_C6 -> Add(h1_C6_NC_numubar);
  hs_C6 -> Add(h1_C6_NC_nuesig);
  hs_C6 -> Add(h1_C6_NC_numu);
  hs_C6 -> Add(h1_C6_CCOther_nuebkg);
  hs_C6 -> Add(h1_C6_CC2p2h_nuebkg);
  hs_C6 -> Add(h1_C6_CCQE_nuebkg);
  hs_C6 -> Add(h1_C6_CCOther_nuebarsig);
  hs_C6 -> Add(h1_C6_CC2p2h_nuebarsig);
  hs_C6 -> Add(h1_C6_CCQE_nuebarsig);
  hs_C6 -> Add(h1_C6_CCOther_nuesig);
  hs_C6 -> Add(h1_C6_CC2p2h_nuesig);
  hs_C6 -> Add(h1_C6_CCQE_nuesig);
  hs_C6 -> Add(h1_C6_CCOther_numubar);
  hs_C6 -> Add(h1_C6_CCOther_numu);
  hs_C6 -> Add(h1_C6_CC2p2h_numubar);
  hs_C6 -> Add(h1_C6_CC2p2h_numu);
  hs_C6 -> Add(h1_C6_CCQE_numubar);
  hs_C6 -> Add(h1_C6_CCQE_numu);
#endif
#if rhcflag
  hs_C6 -> Add(h1_C6_NC_numu);
  hs_C6 -> Add(h1_C6_NC_numubar);
  hs_C6 -> Add(h1_C6_CCOther_numu);
  hs_C6 -> Add(h1_C6_CCOther_numubar);
  hs_C6 -> Add(h1_C6_CC2p2h_numu);
  hs_C6 -> Add(h1_C6_CC2p2h_numubar);
  hs_C6 -> Add(h1_C6_CCQE_numu);
  hs_C6 -> Add(h1_C6_CCQE_numubar);
#endif


  SetHistColor();


  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.46, 0.46, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{ FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_C2_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_C2_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_C2_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_C2_CC2p2h_numu, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_C2_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_C2_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_C2_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_C2_NC_numu, "NC", "F");
  legend1->SetFillColor(0);

  TCanvas* c = new TCanvas("c", "c", 1200, 800);
  c -> Divide(3,2);
  c -> cd(1) -> SetGrid();
  hs_C1 -> SetMaximum(10);
  hs_C1 -> Draw();
  hs_C1 ->GetYaxis()->SetTitleSize(0.038);
  hs_C1 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C1 ->GetYaxis()->SetLabelSize(0.036);
  hs_C1 -> Draw();
  g_C1  -> Draw("SAME");
  legend1->Draw();

  c -> cd(2) -> SetGrid();
  hs_C2 -> Draw();
  hs_C2 ->GetYaxis()->SetTitleSize(0.038);
  hs_C2 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C2 ->GetYaxis()->SetLabelSize(0.036);
  hs_C2 -> Draw();
  g_C2  -> Draw("SAME");

  c -> cd(3) -> SetGrid();
  hs_C3 -> Draw();
  hs_C3 ->GetYaxis()->SetTitleSize(0.038);
  hs_C3 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C3 ->GetYaxis()->SetLabelSize(0.036);
  hs_C3 -> Draw();
  g_C3  -> Draw("SAME");

  c -> cd(4) -> SetGrid();
  hs_C4 -> Draw();
  hs_C4 ->GetYaxis()->SetTitleSize(0.038);
  hs_C4 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C4 ->GetYaxis()->SetLabelSize(0.036);
  hs_C4 -> Draw();
  g_C4  -> Draw("SAME");

  c -> cd(5) -> SetGrid();
  hs_C5 -> Draw();
  hs_C5 ->GetYaxis()->SetTitleSize(0.038);
  hs_C5 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C5 ->GetYaxis()->SetLabelSize(0.036);
  hs_C5 -> Draw();
  g_C5  -> Draw("SAME");

  c -> cd(6) -> SetGrid();
  hs_C6 -> Draw();
  hs_C6 ->GetYaxis()->SetTitleSize(0.038);
  hs_C6 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C6 ->GetYaxis()->SetLabelSize(0.036);
  hs_C6 -> Draw();
  g_C6  -> Draw("SAME");
}


void SetHistColor() {
  h1_C1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C1_NC_numu      -> SetLineColor(kSpring-9);
  h1_C1_NC_numu      -> SetFillColor(kSpring-9);

  h1_C1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C1_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C1_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C1_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C1_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C1_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C1_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C1_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C1_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C1_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C1_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C1_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C1_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C1_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C1_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C1_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C1_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C1_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C1_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_C2_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C2_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C2_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C2_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C2_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C2_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C2_NC_numu      -> SetLineColor(kSpring-9);
  h1_C2_NC_numu      -> SetFillColor(kSpring-9);

  h1_C2_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C2_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C2_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C2_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C2_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C2_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C2_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C2_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C2_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C2_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C2_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C2_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C2_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C2_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C2_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C2_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C2_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C2_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C2_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C2_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C2_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C2_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C2_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C2_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C2_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C2_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C2_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C2_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C2_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C2_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C2_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C2_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_C3_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C3_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C3_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C3_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C3_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C3_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C3_NC_numu      -> SetLineColor(kSpring-9);
  h1_C3_NC_numu      -> SetFillColor(kSpring-9);

  h1_C3_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C3_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C3_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C3_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C3_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C3_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C3_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C3_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C3_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C3_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C3_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C3_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C3_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C3_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C3_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C3_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C3_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C3_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C3_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C3_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C3_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C3_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C3_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C3_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C3_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C3_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C3_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C3_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C3_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C3_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C3_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C3_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_C4_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C4_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C4_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C4_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C4_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C4_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C4_NC_numu      -> SetLineColor(kSpring-9);
  h1_C4_NC_numu      -> SetFillColor(kSpring-9);

  h1_C4_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C4_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C4_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C4_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C4_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C4_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C4_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C4_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C4_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C4_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C4_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C4_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C4_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C4_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C4_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C4_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C4_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C4_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C4_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C4_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C4_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C4_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C4_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C4_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C4_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C4_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C4_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C4_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C4_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C4_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C4_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C4_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_C5_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C5_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C5_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C5_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C5_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C5_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C5_NC_numu      -> SetLineColor(kSpring-9);
  h1_C5_NC_numu      -> SetFillColor(kSpring-9);

  h1_C5_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C5_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C5_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C5_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C5_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C5_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C5_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C5_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C5_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C5_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C5_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C5_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C5_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C5_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C5_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C5_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C5_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C5_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C5_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C5_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C5_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C5_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C5_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C5_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C5_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C5_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C5_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C5_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C5_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C5_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C5_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C5_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_C6_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C6_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C6_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C6_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C6_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C6_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C6_NC_numu      -> SetLineColor(kSpring-9);
  h1_C6_NC_numu      -> SetFillColor(kSpring-9);

  h1_C6_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_C6_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_C6_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_C6_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_C6_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_C6_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_C6_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_C6_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_C6_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_C6_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_C6_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_C6_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_C6_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_C6_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_C6_NC_numubar      -> SetLineColor(kSpring-9);
  h1_C6_NC_numubar      -> SetFillColor(kSpring-9);

  h1_C6_CCQE_nuebarsig    -> SetLineColor(kOrange+7);
  h1_C6_CCQE_nuebarsig    -> SetFillColor(kOrange+7);
  h1_C6_CC2p2h_nuebarsig  -> SetLineColor(kOrange+6);
  h1_C6_CC2p2h_nuebarsig  -> SetFillColor(kOrange+6);
  h1_C6_CCOther_nuebarsig -> SetLineColor(kOrange+0);
  h1_C6_CCOther_nuebarsig -> SetFillColor(kOrange+0);
  h1_C6_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_C6_NC_nuebarsig      -> SetFillColor(kSpring-9);
  
  h1_C6_CCQE_nuebkg    -> SetLineColor(kOrange+7);
  h1_C6_CCQE_nuebkg    -> SetFillColor(kOrange+7);
  h1_C6_CC2p2h_nuebkg  -> SetLineColor(kOrange+6);
  h1_C6_CC2p2h_nuebkg  -> SetFillColor(kOrange+6);
  h1_C6_CCOther_nuebkg -> SetLineColor(kOrange+0);
  h1_C6_CCOther_nuebkg -> SetFillColor(kOrange+0);
  h1_C6_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_C6_NC_nuebkg      -> SetFillColor(kSpring-9);
}

void ScaleHisto(int step) {
  switch (step) {
    case 1:
      h1_C1_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C1_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C1_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C1_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C1_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C1_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C1_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C1_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C1_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C1_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C1_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C1_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C1_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C1_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C1_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C1_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 2:
      h1_C2_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C2_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C2_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C2_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C2_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C2_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C2_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C2_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C2_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C2_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C2_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C2_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C2_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C2_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C2_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C2_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C2_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C2_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C2_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C2_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 3:
      h1_C3_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C3_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C3_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C3_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C3_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C3_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C3_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C3_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C3_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C3_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C3_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C3_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C3_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C3_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C3_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C3_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C3_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C3_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C3_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C3_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 4:
      h1_C4_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C4_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C4_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C4_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C4_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C4_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C4_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C4_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C4_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C4_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C4_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C4_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C4_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C4_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C4_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C4_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C4_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C4_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C4_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C4_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 5:
      h1_C5_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C5_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C5_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C5_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C5_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C5_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C5_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C5_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C5_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C5_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C5_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C5_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C5_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C5_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C5_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C5_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C5_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C5_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C5_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C5_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    case 6:
      h1_C6_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C6_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C6_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C6_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
      h1_C6_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C6_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C6_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C6_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
      h1_C6_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C6_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C6_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C6_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
      h1_C6_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C6_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C6_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C6_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
      h1_C6_CCQE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C6_CC2p2h_nuebkg  -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C6_CCOther_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      h1_C6_NC_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
      break;
    default:
      break;
  }
}


