#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void NeutronDistance_prm_x_n(bool beammode) {

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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_prm_x_n.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_prm_x_n.root");
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.NeutronVertex_prm_x_n.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.NeutronVertex_prm_x_n.root");
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

  TH1F* h1_truedistance_mu_n_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_prm_mu_n");
  TH1F* h1_truedistance_nu_n_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_prm_nu_n");
  h1_truedistance_nu_n_numu -> SetStats(0);
  h1_truedistance_nu_n_numu -> SetYTitle("Number of Events");

  TH1F* h1_truedistance_mu_n_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_prm_mu_n");
  TH1F* h1_truedistance_nu_n_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_prm_nu_n");
  h1_truedistance_nu_n_numubar -> SetStats(0);
  h1_truedistance_nu_n_numubar -> SetYTitle("Number of Events");

  h1_truedistance_nu_n_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_truedistance_nu_n_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_truedistance_mu_n_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_truedistance_mu_n_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_distance_nu_n = new TH1F("h1_distance_nu_n", "Truth distance; Distance[m]; Number of Events", 50, 0, 5.);
  h1_distance_nu_n -> Add(h1_truedistance_nu_n_numu, h1_truedistance_nu_n_numubar, 1., 1.);
  h1_distance_nu_n -> SetLineColor(kRed-7);
  h1_distance_nu_n -> SetLineWidth(3);
  h1_distance_nu_n -> SetStats(0);

  TH1F* h1_distance_mu_n = new TH1F("h1_distance_mu_n", "Truth distance; Distance[m]; Number of Events", 50, 0, 5.);
  h1_distance_mu_n -> Add(h1_truedistance_mu_n_numu, h1_truedistance_mu_n_numubar, 1., 1.);
  h1_distance_mu_n -> SetLineColor(kAzure+9);
  h1_distance_mu_n -> SetLineWidth(3);
  h1_distance_mu_n -> SetStats(0);

  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  h1_distance_nu_n -> Draw("SAME");
  h1_distance_mu_n -> Draw("SAME");
  
  TLegend* legend1 = new TLegend(0.35, 0.69, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  //legend1 -> AddEntry(h1_distance_nu_n, "#mu decay - n(from #nu) cap vtx", "L");
  //legend1 -> AddEntry(h1_distance_mu_n, "#mu capture - n(from #mu) cap vtx", "L");
  legend1 -> AddEntry(h1_distance_nu_n, "Primary - n(from #nu) capture vtx", "L");
  legend1 -> AddEntry(h1_distance_mu_n, "Primary - n(from #mu) capture vtx", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
}


