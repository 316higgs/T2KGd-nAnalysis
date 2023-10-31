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
//#define POTSCALE 0.17
#define POTSCALE 1

void TrueNCapDistance(bool beammode) {

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
  TFile* fin_numu       = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig     = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar    = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig  = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg     = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg  = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

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


  //////  distance  //////
  TH1F* h1_TrueCapNBefSIn_numu       = (TH1F*)fin_numu ->Get("DistanceViewer/h1_truedistance_BefSIn");
  TH1F* h1_TrueCapNBefSIn_nuesig     = (TH1F*)fin_nuesig ->Get("DistanceViewer/h1_truedistance_BefSIn");
  TH1F* h1_TrueCapNBefSIn_numubar    = (TH1F*)fin_numubar ->Get("DistanceViewer/h1_truedistance_BefSIn");
  TH1F* h1_TrueCapNBefSIn_nuebarsig  = (TH1F*)fin_nuebarsig ->Get("DistanceViewer/h1_truedistance_BefSIn");
  TH1F* h1_TrueCapNBefSIn_nuebkg     = (TH1F*)fin_nuebkg ->Get("DistanceViewer/h1_truedistance_BefSIn");
  TH1F* h1_TrueCapNBefSIn_nuebarbkg  = (TH1F*)fin_nuebarbkg ->Get("DistanceViewer/h1_truedistance_BefSIn");

  TH1F* h1_TrueCapNSIn_numu       = (TH1F*)fin_numu ->Get("DistanceViewer/h1_truedistance_SIn");
  TH1F* h1_TrueCapNSIn_nuesig     = (TH1F*)fin_nuesig ->Get("DistanceViewer/h1_truedistance_SIn");
  TH1F* h1_TrueCapNSIn_numubar    = (TH1F*)fin_numubar ->Get("DistanceViewer/h1_truedistance_SIn");
  TH1F* h1_TrueCapNSIn_nuebarsig  = (TH1F*)fin_nuebarsig ->Get("DistanceViewer/h1_truedistance_SIn");
  TH1F* h1_TrueCapNSIn_nuebkg     = (TH1F*)fin_nuebkg ->Get("DistanceViewer/h1_truedistance_SIn");
  TH1F* h1_TrueCapNSIn_nuebarbkg  = (TH1F*)fin_nuebarbkg ->Get("DistanceViewer/h1_truedistance_SIn");


  /////  Merged distance  //////
  TH1F* h1_TrueCapNBefSIn  = new TH1F("h1_TrueCapNBefSIn ", "", 50, 0, 5);
  h1_TrueCapNBefSIn  -> SetLineColor(kRed-3);
  h1_TrueCapNBefSIn  -> SetFillColor(kRed-9);
  h1_TrueCapNBefSIn  -> SetFillStyle(3004);
  h1_TrueCapNBefSIn  -> SetLineWidth(3);
  h1_TrueCapNBefSIn  -> SetStats(0);
  h1_TrueCapNBefSIn  -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueCapNBefSIn  -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_TrueCapNSIn  = new TH1F("h1_TrueCapNSIn ", "", 50, 0, 5);
  h1_TrueCapNSIn  -> SetLineColor(kOrange-3);
  h1_TrueCapNSIn  -> SetFillColor(kOrange-2);
  h1_TrueCapNSIn  -> SetFillStyle(3004);
  h1_TrueCapNSIn  -> SetLineWidth(3);
  h1_TrueCapNSIn  -> SetStats(0);
  h1_TrueCapNSIn  -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueCapNSIn  -> GetYaxis()->SetTitleSize(0.045);


#if fhcflag
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_numu );
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_nuesig );
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_numubar );
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_nuebarsig );
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_nuebkg );
  h1_TrueCapNBefSIn  -> Add(h1_TrueCapNBefSIn_nuebarbkg );

  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_numu );
  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_nuesig );
  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_numubar );
  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_nuebarsig );
  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_nuebkg );
  h1_TrueCapNSIn  -> Add(h1_TrueCapNSIn_nuebarbkg );
#endif


  gROOT -> SetStyle("Plain");
  /////////// Reco Capture Time //////////
#if 1

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //h1_TrueCapNBefSIn -> SetMaximum(4000);
  h1_TrueCapNSIn -> Draw("");
  h1_TrueCapNSIn ->GetXaxis()->SetTitle("True Travel Distance [m]");
  h1_TrueCapNSIn ->GetXaxis()->SetTitleSize(0.045);
  h1_TrueCapNSIn ->GetYaxis()->SetTitle("Number of True Captured Neutrons");
  h1_TrueCapNSIn ->GetYaxis()->SetTitleSize(0.045);
  h1_TrueCapNSIn ->GetYaxis()->SetTitleOffset(1.1);
  h1_TrueCapNSIn -> Draw("SAME");
  h1_TrueCapNBefSIn -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.35, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.45]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_TrueCapNBefSIn , "Primary #nu int. + FSI (Captured)", "L");
  legend1 -> AddEntry(h1_TrueCapNSIn, "SI (Captured)", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();

#endif


}
