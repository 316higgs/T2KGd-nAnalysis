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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.root");

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  //TFile* fin_nuesig  = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.2.1/skrate/fhc_sk_rate_tmp.root");
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
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  float ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  float ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  float ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  //Double_t GenN_numu_x_numu         = 190292;
  //Double_t GenN_numubar_x_numubar   = 190909;
  float GenN_numu_x_numu         = 63576;
  float GenN_numu_x_nue          = 63312;
  float GenN_numubar_x_numubar   = 63458;
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


  float y[2] = {0., 200.};
  float xC1[2] = {30, 30};
  TGraph* g_C1 = new TGraph(2, xC1, y);
  g_C1 -> SetLineWidth(2);
  g_C1 -> SetLineColor(kViolet-8);
  g_C1 -> SetLineStyle(7);


  //--- Dwall ------------------------
  h1_C1_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_C1_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_C1_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_C1_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_C1_CCQE_numu -> SetStats(0);

  /*
  h1_C1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_C1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_C1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_C1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_C1_CCQE_nuesig -> SetStats(0);

  h1_C1_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode0");
  h1_C1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode1");
  h1_C1_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode3");
  h1_C1_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_evis_mode2");
  h1_C1_CCQE_numubar -> SetStats(0);
  */

  h1_C1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_C1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_C1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_C1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_C1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_C1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_C1_NC_numu      -> SetLineColor(kSpring-9);
  h1_C1_NC_numu      -> SetFillColor(kSpring-9);

  h1_C1_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_C1_CC2p2h_numu  -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_C1_CCOther_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_C1_NC_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_C1_CCQE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_C1_CC2p2h_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_C1_CCOther_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_C1_NC_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_C1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_C1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_C1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_C1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_C1 = new THStack("hs_C1", "0. Evis > 30 MeV; fiTQun Evis[MeV]; ");
#if fhcflag
  //hs_C1 -> Add(h1_C1_NC_numubar);
  //hs_C1 -> Add(h1_C1_NC_nuesig);
  hs_C1 -> Add(h1_C1_NC_numu);
  //hs_C1 -> Add(h1_C1_CCOther_nuesig);
  //hs_C1 -> Add(h1_C1_CC2p2h_nuesig);
  //hs_C1 -> Add(h1_C1_CCQE_nuesig);
  //hs_C1 -> Add(h1_C1_CCOther_numubar);
  hs_C1 -> Add(h1_C1_CCOther_numu);
  //hs_C1 -> Add(h1_C1_CC2p2h_numubar);
  hs_C1 -> Add(h1_C1_CC2p2h_numu);
 // hs_C1 -> Add(h1_C1_CCQE_numubar);
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


  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.46, 0.46, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{ FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_C1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  //legend1 -> AddEntry(h1_C1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_C1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_C1_CC2p2h_numu, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_C1_CCOther_numu, "#nu_{#mu} CC-other", "F");
 // legend1 -> AddEntry(h1_C1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
 // legend1 -> AddEntry(h1_C1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_C1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);

  TCanvas* c = new TCanvas("c", "c", 1200, 800);
  c -> SetGrid();
  c -> SetLogy();
  //hs_C1 -> SetMaximum(10);
  hs_C1 -> Draw();
  hs_C1 ->GetYaxis()->SetTitleSize(0.038);
  hs_C1 ->GetYaxis()->SetTitleOffset(1.3);
  hs_C1 ->GetYaxis()->SetLabelSize(0.036);
  hs_C1 -> Draw();
  g_C1  -> Draw("SAME");
  legend1->Draw();

}