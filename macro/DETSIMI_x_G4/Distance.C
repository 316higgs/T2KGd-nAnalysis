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

void Distance(bool beammode) {

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
  TFile* fin_numu_detsim      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig_detsim    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar_detsim   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_detsim = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_detsim    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_detsim = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  TFile* fin_numu_g4      = new TFile("../../output/fhc/fhc.numu_x_numu.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuesig_g4    = new TFile("../../output/fhc/fhc.numu_x_nue.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_numubar_g4   = new TFile("../../output/fhc/fhc.numubar_x_numubar.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_g4 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_g4    = new TFile("../../output/fhc/fhc.nue_x_nue.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_g4 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.skg4MC.bonsaikeras_ToF.root");

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


  //////  Reco Capture Time  //////
  TH1F* h1_RecoDistance_numu_detsim      = (TH1F*)fin_numu_detsim->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuesig_detsim    = (TH1F*)fin_nuesig_detsim->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_numubar_detsim   = (TH1F*)fin_numubar_detsim->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebarsig_detsim = (TH1F*)fin_nuebarsig_detsim->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebkg_detsim    = (TH1F*)fin_nuebkg_detsim->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebarbkg_detsim = (TH1F*)fin_nuebarbkg_detsim->Get("DistanceViewer/h1_RecoNCapDistance");


  TH1F* h1_RecoDistance_numu_g4      = (TH1F*)fin_numu_g4->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuesig_g4    = (TH1F*)fin_nuesig_g4->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_numubar_g4   = (TH1F*)fin_numubar_g4->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebarsig_g4 = (TH1F*)fin_nuebarsig_g4->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebkg_g4    = (TH1F*)fin_nuebkg_g4->Get("DistanceViewer/h1_RecoNCapDistance");
  TH1F* h1_RecoDistance_nuebarbkg_g4 = (TH1F*)fin_nuebarbkg_g4->Get("DistanceViewer/h1_RecoNCapDistance");



  /////  Merged capture time  //////
  TH1F* h1_RecoDistance_detsim = new TH1F("h1_RecoDistance_detsim", "", 50, 0, 5);
  h1_RecoDistance_detsim -> SetLineColor(kViolet-7);
  h1_RecoDistance_detsim -> SetLineWidth(3);
  h1_RecoDistance_detsim -> SetStats(0);
  h1_RecoDistance_detsim -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoDistance_detsim -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_RecoDistance_g4 = new TH1F("h1_RecoDistance_g4", "", 50, 0, 5);
  h1_RecoDistance_g4 -> SetLineColor(kAzure-9);
  h1_RecoDistance_g4 -> SetLineWidth(3);
  h1_RecoDistance_g4 -> SetStats(0);
  h1_RecoDistance_g4 -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoDistance_g4 -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_numu_detsim);
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_nuesig_detsim);
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_numubar_detsim);
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_nuebarsig_detsim);
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_nuebkg_detsim);
  h1_RecoDistance_detsim -> Add(h1_RecoDistance_nuebarbkg_detsim);

  h1_RecoDistance_g4 -> Add(h1_RecoDistance_numu_g4);
  h1_RecoDistance_g4 -> Add(h1_RecoDistance_nuesig_g4);
  h1_RecoDistance_g4 -> Add(h1_RecoDistance_numubar_g4);
  h1_RecoDistance_g4 -> Add(h1_RecoDistance_nuebarsig_g4);
  h1_RecoDistance_g4 -> Add(h1_RecoDistance_nuebkg_g4);
  h1_RecoDistance_g4 -> Add(h1_RecoDistance_nuebarbkg_g4);
#endif


  gROOT -> SetStyle("Plain");
  /////////// Reco Capture Time //////////
#if 1

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_RecoDistance_g4 -> SetMaximum(4000);
  h1_RecoDistance_g4 -> Draw("");
  h1_RecoDistance_g4 ->GetXaxis()->SetTitle("Reconstructed Travel Distance [m]");
  h1_RecoDistance_g4 ->GetXaxis()->SetTitleSize(0.045);
  h1_RecoDistance_g4 ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  h1_RecoDistance_g4 ->GetYaxis()->SetTitleSize(0.045);
  h1_RecoDistance_g4 ->GetYaxis()->SetTitleOffset(1.1);
  h1_RecoDistance_g4 -> Draw("SAME");
  h1_RecoDistance_detsim -> Draw("SAME");
  //f1_CapTime -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.37, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_RecoDistance_detsim, "SKDETSIM-based MC", "L");
  legend1 -> AddEntry(h1_RecoDistance_g4, "SKG4-based MC", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


}
