#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void PiMom(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << POTSCALE << "x10^21 POT" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC " << POTSCALE << "x10^21 POT" << std::endl;

  //FHC
#if fhcflag
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.aftercut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection.aftercut.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection.aftercut.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection.aftercut.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  TH1F* h1_PiDcy_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_PiPlusMom_PiDcy");
  TH1F* h1_PiAbs_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_PiPlusMom_PiAbs");
  TH1F* h1_PiHad_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_PiPlusMom_PiHad");
  h1_PiDcy_numu -> SetStats(0);

  TH1F* h1_PiDcy_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_PiPlusMom_PiDcy");
  TH1F* h1_PiAbs_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_PiPlusMom_PiAbs");
  TH1F* h1_PiHad_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_PiPlusMom_PiHad");
  h1_PiDcy_numubar -> SetStats(0);

  h1_PiDcy_numu    -> SetLineColor(kOrange-3);
  h1_PiAbs_numu  -> SetLineColor(kAzure+1);
  h1_PiHad_numu -> SetLineColor(kSpring+5);

  h1_PiDcy_numu    -> SetFillColor(kOrange-3);
  h1_PiAbs_numu  -> SetFillColor(kAzure+1);
  h1_PiHad_numu -> SetFillColor(kSpring+5);

  h1_PiDcy_numubar    -> SetLineColor(kOrange-3);
  h1_PiAbs_numubar  -> SetLineColor(kAzure+1);
  h1_PiHad_numubar -> SetLineColor(kSpring+5);

  h1_PiDcy_numubar    -> SetFillColor(kOrange-3);
  h1_PiAbs_numubar  -> SetFillColor(kAzure+1);
  h1_PiHad_numubar -> SetFillColor(kSpring+5);

  h1_PiDcy_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PiDcy_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_PiAbs_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PiAbs_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_PiHad_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PiHad_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );


  THStack* hs_PiPlusMom = new THStack("hs_PiPlusMom", "Pion Momentum; #pi^{+} Momentum [MeV]; Number of Events");
#if fhcflag
  hs_PiPlusMom -> Add(h1_PiDcy_numubar);
  hs_PiPlusMom -> Add(h1_PiDcy_numu);
  hs_PiPlusMom -> Add(h1_PiHad_numubar);
  hs_PiPlusMom -> Add(h1_PiHad_numu);
  hs_PiPlusMom -> Add(h1_PiAbs_numubar);
  hs_PiPlusMom -> Add(h1_PiAbs_numu);
#endif
#if rhcflag
  hs_PiPlusMom -> Add(h1_PiDcy_numu);
  hs_PiPlusMom -> Add(h1_PiDcy_numubar);
  hs_PiPlusMom -> Add(h1_PiHad_numu);
  hs_PiPlusMom -> Add(h1_PiHad_numubar);
  hs_PiPlusMom -> Add(h1_PiAbs_numu);
  hs_PiPlusMom -> Add(h1_PiAbs_numubar);
#endif

  float FrameMaximum = 6.;
  float ChereThreshold = 159.6;
  float y[2] = {0., FrameMaximum+10.};
  float x[2] = {ChereThreshold, ChereThreshold};
  TGraph* g_ChereThreshold = new TGraph(2, x, y);
  g_ChereThreshold -> SetLineWidth(2);
  g_ChereThreshold -> SetLineColor(kViolet-8);
  g_ChereThreshold -> SetLineStyle(7);

  TH2F* h2_PiPlusMom_x_Enu = (TH2F*)fin_numu->Get("DecayeBox/h2_PiPlusMom_x_Enu");

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_PiPlusMom -> Draw();
  hs_PiPlusMom ->GetYaxis()->SetTitleSize(0.038);
  hs_PiPlusMom ->GetYaxis()->SetTitleOffset(1.3);
  hs_PiPlusMom ->GetYaxis()->SetLabelSize(0.036);
  hs_PiPlusMom -> Draw();
  g_ChereThreshold -> Draw("SAME");
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
  legend1 -> AddEntry(h1_PiDcy_numu, "#pi^{+} decay", "F");
  //legend1 -> AddEntry(h1_PiDcy_numubar, "#bar{#nu}_{#mu} #pi^{+} decay", "F");
  legend1 -> AddEntry(h1_PiAbs_numu, "#pi^{+} absorption", "F");
  //legend1 -> AddEntry(h1_PiAbs_numubar, "#bar{#nu}_{#mu} #pi^{+} absorption", "F");
  legend1 -> AddEntry(h1_PiHad_numu, "#pi^{+} hadronic", "F");
  //legend1 -> AddEntry(h1_PiHad_numubar, "#bar{#nu}_{#mu} #pi^{+} hadronic", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h2_PiPlusMom_x_Enu -> Draw("COLZ");
#endif

}