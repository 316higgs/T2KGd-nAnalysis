#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC

#define GdNuEvents 26.2653 //nu events @C1-C4


void dtn50(bool beammode) {
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
  //Gd MC
  TFile* fin_numu_gd    = new TFile("../../output/fhc/fhc.numu_x_numu.root");
  TFile* fin_numubar_gd = new TFile("../../output/fhc/fhc.numubar_x_numubar.root");

  //Pure water MC
  TFile* fin_numu_pw    = new TFile("../../output/fhc/numu_x_numu.water.root");
  TFile* fin_numubar_pw = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu_gd    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar_gd = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
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

  TH2D* h2_dtn50_numu_gd    = (TH2D*)fin_numu_gd->Get("DecayeBox/h2_dtn50");
  TH2D* h2_dtn50_numubar_gd = (TH2D*)fin_numubar_gd->Get("DecayeBox/h2_dtn50");
  h2_dtn50_numu_gd    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h2_dtn50_numubar_gd -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH2D* h2_dtn50_gd = new TH2D("h2_dtn50_gd", "",  100, 0, 50, 40, 0, 400);
  h2_dtn50_gd -> Add(h2_dtn50_numu_gd, 1.);
  h2_dtn50_gd -> Add(h2_dtn50_numubar_gd, 1.);
  h2_dtn50_gd -> SetStats(0);
  //h2_dtn50_gd -> GetYaxis()->SetLabelSize(0.045);
  h2_dtn50_gd -> SetTitleOffset(1.3, "Y");
  //h2_dtn50_gd -> GetXaxis()->SetLabelSize(0.045);
  h2_dtn50_gd -> SetTitleOffset(1.2, "X");
  h2_dtn50_gd -> SetXTitle("Timing difference from the prompt event dt [#musec]");
  h2_dtn50_gd -> SetYTitle("#hits in 50 nsec time window N50");


  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 700);
  c1 -> SetGrid();
  h2_dtn50_gd -> Scale(1./GdNuEvents);   //Gd
  //h2_dtn50_all -> Scale(1./47086); //pure water
  h2_dtn50_gd -> Draw("colz");

  TLatex* text1 = new TLatex(0.48, 0.75, "C1-C4 applied");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.04);
  text1 -> Draw();
  TLatex* text2 = new TLatex(0.48, 0.7, "Normalized with ##nu events@C1-C4");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  text2 -> Draw();

}