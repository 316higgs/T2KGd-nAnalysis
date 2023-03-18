#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void CCPiDecaye(bool beammode) {

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


  TH1F* h1_CC0pi_numu    = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_CCpi0");
  TH1F* h1_CC1pi_numu  = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_CCpi1");
  TH1F* h1_CCXpi_numu      = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_CCpi2");
  h1_CC0pi_numu -> SetStats(0);

  TH1F* h1_CC0pi_numubar    = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_CCpi0");
  TH1F* h1_CC1pi_numubar  = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_CCpi1");
  TH1F* h1_CCXpi_numubar      = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_CCpi2");
  h1_CC0pi_numubar -> SetStats(0);

  h1_CC0pi_numu  -> SetLineColor(kViolet+8);
  h1_CC1pi_numu  -> SetLineColor(kAzure-9);
  h1_CCXpi_numu  -> SetLineColor(kAzure+9);

  h1_CC0pi_numu  -> SetFillColor(kViolet+8);
  h1_CC1pi_numu  -> SetFillColor(kAzure-9);
  h1_CCXpi_numu  -> SetFillColor(kAzure+9);

  h1_CC0pi_numubar  -> SetLineColor(kOrange+2);
  h1_CC1pi_numubar  -> SetLineColor(kOrange+1);
  h1_CCXpi_numubar  -> SetLineColor(kOrange-2);

  h1_CC0pi_numubar  -> SetFillColor(kOrange+2);
  h1_CC1pi_numubar  -> SetFillColor(kOrange+1);
  h1_CCXpi_numubar  -> SetFillColor(kOrange-2);

  h1_CC0pi_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC0pi_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC1pi_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC1pi_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCXpi_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCXpi_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );


  THStack* hs_TrueDecaye = new THStack("hs_TrueDecaye", "Number of Decay-e; Number of Decay-e; Number of Events");
#if fhcflag
  hs_TrueDecaye -> Add(h1_CCXpi_numubar);
  hs_TrueDecaye -> Add(h1_CCXpi_numu);
  hs_TrueDecaye -> Add(h1_CC1pi_numubar);
  hs_TrueDecaye -> Add(h1_CC1pi_numu);
  hs_TrueDecaye -> Add(h1_CC0pi_numubar);
  hs_TrueDecaye -> Add(h1_CC0pi_numu);
#endif
#if rhcflag
  hs_TrueDecaye -> Add(h1_CCXpi_numu);
  hs_TrueDecaye -> Add(h1_CCXpi_numubar);
  hs_TrueDecaye -> Add(h1_CC1pi_numu);
  hs_TrueDecaye -> Add(h1_CC1pi_numubar);
  hs_TrueDecaye -> Add(h1_CC0pi_numu);
  hs_TrueDecaye -> Add(h1_CC0pi_numubar);
#endif


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_TrueDecaye -> SetMaximum(300);
  hs_TrueDecaye -> Draw();
  hs_TrueDecaye ->GetYaxis()->SetTitleSize(0.038);
  hs_TrueDecaye ->GetYaxis()->SetTitleOffset(1.3);
  hs_TrueDecaye ->GetYaxis()->SetLabelSize(0.036);
  hs_TrueDecaye -> Draw();
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
  legend1 -> AddEntry(h1_CC0pi_numu, "#nu_{#mu} CC-other(0 #pi)", "F");
  legend1 -> AddEntry(h1_CC0pi_numubar, "#bar{#nu}_{#mu} CC-other(0 #pi)", "F");
  legend1 -> AddEntry(h1_CC1pi_numu, "#nu_{#mu} CC-other(1 #pi)", "F");
  legend1 -> AddEntry(h1_CC1pi_numubar, "#bar{#nu}_{#mu} CC-other(1 #pi)", "F");
  legend1 -> AddEntry(h1_CCXpi_numu, "#nu_{#mu} CC-other(other)", "F");
  legend1 -> AddEntry(h1_CCXpi_numubar, "#bar{#nu}_{#mu} CC-other(other)", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}