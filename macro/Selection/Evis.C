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

TH1F* h1_CCQE_numu;
TH1F* h1_CC2p2h_numu;
TH1F* h1_CCOther_numu;
TH1F* h1_NC_numu;
TH1F* h1_CCQE_nuesig;
TH1F* h1_CC2p2h_nuesig;
TH1F* h1_CCOther_nuesig;
TH1F* h1_NC_nuesig;
TH1F* h1_CCQE_numubar;
TH1F* h1_CC2p2h_numubar;
TH1F* h1_CCOther_numubar;
TH1F* h1_NC_numubar;


void SetHistoColor();
void ScaleHisto(int step);

void Evis(bool beammode) {

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

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
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
  Double_t GenN_numubar_x_nuebar  = 63460;
  Double_t GenN_nue_x_nue         = 63423;
  Double_t GenN_nuebar_x_nuebar   = 63652;
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


  float y[2] = {0., 400.};
  float xC1[2] = {30, 30};
  TGraph* g_C1 = new TGraph(2, xC1, y);
  g_C1 -> SetLineWidth(2);
  g_C1 -> SetLineColor(kViolet-8);
  g_C1 -> SetLineStyle(7);


  h1_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_numu -> SetStats(0);

  h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_nuesig -> SetStats(0);

  h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_numubar -> SetStats(0);

  h1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_nuebarsig -> SetStats(0);

  h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_nuebkg -> SetStats(0);

  h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_CCQE_nuebarbkg -> SetStats(0);

  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_NC_nuesig      -> SetLineColor(kSpring-9);

  h1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_NC_nuebkg      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetFillColor(kSpring-9);


  /////  Normalizations  //////
#if 1
  h1_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  THStack* hs_C1 = new THStack("hs_C1", "0. Evis > 30 MeV; fiTQun Evis[MeV]; Number of Neutrino Events");
#if fhcflag
  hs_C1 -> Add(h1_NC_nuebarbkg);
  hs_C1 -> Add(h1_NC_nuebkg);
  hs_C1 -> Add(h1_NC_nuebarsig);
  hs_C1 -> Add(h1_NC_numubar);
  hs_C1 -> Add(h1_NC_nuesig);
  hs_C1 -> Add(h1_NC_numu);

  hs_C1 -> Add(h1_CCOther_nuebarbkg);
  hs_C1 -> Add(h1_CC2p2h_nuebarbkg);
  hs_C1 -> Add(h1_CCQE_nuebarbkg);
  hs_C1 -> Add(h1_CCOther_nuebkg);
  hs_C1 -> Add(h1_CC2p2h_nuebkg);
  hs_C1 -> Add(h1_CCQE_nuebkg);
  hs_C1 -> Add(h1_CCOther_nuebarsig);
  hs_C1 -> Add(h1_CC2p2h_nuebarsig);
  hs_C1 -> Add(h1_CCQE_nuebarsig);
  hs_C1 -> Add(h1_CCOther_nuesig);
  hs_C1 -> Add(h1_CC2p2h_nuesig);
  hs_C1 -> Add(h1_CCQE_nuesig);

  hs_C1 -> Add(h1_CCOther_numubar);
  hs_C1 -> Add(h1_CCOther_numu);
  hs_C1 -> Add(h1_CC2p2h_numubar);
  hs_C1 -> Add(h1_CC2p2h_numu);
  hs_C1 -> Add(h1_CCQE_numubar);
  hs_C1 -> Add(h1_CCQE_numu);
#endif


  TFile* fin_data = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");
  TH1F* h1_data = (TH1F*)fin_data->Get("Gd1RmuonSelection/h1_Allevis");
  h1_data -> SetMarkerStyle(20);
  h1_data -> SetMarkerSize(1.2);
  h1_data -> SetMarkerColor(kBlack);
  h1_data -> SetLineColor(kBlack);
  h1_data -> SetLineWidth(1.5);


  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);

  TCanvas* c = new TCanvas("c", "c", 1000, 700);
  c -> SetGrid();
  c -> SetLogy();
  hs_C1 -> SetMaximum(50);
  hs_C1 -> Draw();
  hs_C1 ->GetYaxis()->SetTitleSize(0.045);
  hs_C1 ->GetYaxis()->SetTitleOffset(1.0);
  hs_C1 ->GetYaxis()->SetLabelSize(0.036);
  hs_C1 -> Draw();
  h1_data -> Draw("SAME E P");
  g_C1  -> Draw("SAME");
  legend1->Draw();

}

