#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void TotGammaE(bool beammode) {

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

  TFile* fin_numu_ggarnet      = new TFile("../../output/fhc/fhc.numu_x_numu.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuesig_ggarnet    = new TFile("../../output/fhc/fhc.numu_x_nue.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_numubar_ggarnet   = new TFile("../../output/fhc/fhc.numubar_x_numubar.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_ggarnet = new TFile("../../output/fhc/fhc.numubar_x_nuebar.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_ggarnet    = new TFile("../../output/fhc/fhc.nue_x_nue.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_ggarnet = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.ggarnet.bonsaikeras_ToF.root");

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


  TH1F* h1_TotGammaE_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TotGammaE");

  TH1F* h1_TotGammaE_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_TotGammaE");
  TH1F* h1_TotGammaE_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_TotGammaE");

  bool mode[6] = {1, 1, 1, 1, 1, 1};

#if 0
  //  Normalization 
  if (mode[0]) h1_TotGammaE_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  if (mode[1]) h1_TotGammaE_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  if (mode[2]) h1_TotGammaE_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  if (mode[3]) h1_TotGammaE_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  if (mode[4]) h1_TotGammaE_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  if (mode[5]) h1_TotGammaE_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  int maximum = 10000;
  int BINS    = 400;

  TH1F* h1_TotGammaE = new TH1F("h1_TotGammaE", "", BINS, 0, maximum);
  if (mode[5]) h1_TotGammaE -> Add(h1_TotGammaE_nuebarbkg);
  if (mode[4]) h1_TotGammaE -> Add(h1_TotGammaE_nuebkg);
  if (mode[3]) h1_TotGammaE -> Add(h1_TotGammaE_nuebarsig);
  if (mode[2]) h1_TotGammaE -> Add(h1_TotGammaE_numubar);
  if (mode[1]) h1_TotGammaE -> Add(h1_TotGammaE_nuesig);
  if (mode[0]) h1_TotGammaE -> Add(h1_TotGammaE_numu);
  h1_TotGammaE -> SetLineColor(kViolet-7);
  h1_TotGammaE -> SetXTitle("Total #gamma-ray Energy [keV]");
  h1_TotGammaE -> SetYTitle("Number of True Neutron Captures");
  h1_TotGammaE -> SetLineWidth(2);
  h1_TotGammaE -> SetStats(0);

  TH1F* h1_TotGammaE_ggarnet = new TH1F("h1_TotGammaE_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_nuebarbkg);
  if (mode[4]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_nuebkg);
  if (mode[3]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_nuebarsig);
  if (mode[2]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_numubar);
  if (mode[1]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_nuesig);
  if (mode[0]) h1_TotGammaE_ggarnet -> Add(h1_TotGammaE_ggarnet_numu);
  h1_TotGammaE_ggarnet -> SetLineColor(kRed-6);
  h1_TotGammaE_ggarnet -> SetXTitle("Total #gamma-ray Energy [keV]");
  h1_TotGammaE_ggarnet -> SetYTitle("Number of True Neutron Captures");
  h1_TotGammaE_ggarnet -> SetLineWidth(2);
  h1_TotGammaE_ggarnet -> SetStats(0);


  TLegend* legend1 = new TLegend(0.14, 0.75, 0.6, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_TotGammaE, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(h1_TotGammaE_ggarnet, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetLogy();
  c1 -> SetGrid();
  h1_TotGammaE -> SetMaximum(800000);
  h1_TotGammaE -> Draw("SAME");
  h1_TotGammaE_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();
#endif

#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetLogy();
  c1 -> SetGrid();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->SetGridy();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  h1_TotGammaE -> Draw("SAME");
  h1_TotGammaE_ggarnet -> Draw("SAME");
  c1 -> RedrawAxis();

  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  gROOT -> SetStyle("Plain");
  TH1F *h1_TotGammaERatio = (TH1F*)h1_TotGammaE_ggarnet->Clone("h1_TotGammaERatio");
  h1_TotGammaERatio->SetLineColor(kViolet-7);
  h1_TotGammaERatio->SetMinimum(0.7);  // Define Y ..
  h1_TotGammaERatio->SetMaximum(1.25); // .. range
  h1_TotGammaERatio ->GetYaxis()->SetTitleSize(0.16);
  h1_TotGammaERatio ->GetYaxis()->SetTitleOffset(0.28);
  h1_TotGammaERatio ->GetYaxis()->SetLabelSize(0.12);
  h1_TotGammaERatio ->GetYaxis()->SetTitle("Ratio     ");
  h1_TotGammaERatio ->GetXaxis()->SetTitleSize(0.16);
  h1_TotGammaERatio ->GetXaxis()->SetTitleOffset(0.8);
  h1_TotGammaERatio ->GetXaxis()->SetLabelSize(0.13);
  h1_TotGammaERatio -> GetXaxis()->SetTitle("Total #gamma-ray Energy [keV]");

  h1_TotGammaERatio->Sumw2();
  h1_TotGammaERatio->SetStats(0);      // No statistics on lower plot
  h1_TotGammaERatio->Divide(h1_TotGammaE);
  h1_TotGammaERatio->SetMarkerStyle(21);
  h1_TotGammaERatio->Draw("histo");       // Draw the ratio plot
#endif

}

