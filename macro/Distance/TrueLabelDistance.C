#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void TrueLabelDistance(bool beammode) {

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
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.root");
  
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root");

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


  TH1F* h1_MuN_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_TagNCap_MuN");
  TH1F* h1_NuN_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_TagNCap_NuN");
  h1_MuN_numu -> SetStats(0);

  TH1F* h1_MuN_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_TagNCap_MuN");
  TH1F* h1_NuN_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_TagNCap_NuN");
  h1_MuN_numubar -> SetStats(0);

  h1_MuN_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_MuN_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NuN_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NuN_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_MuN = new TH1F("h1_MuN", "Truth distance; Distance[m]; Number of Events", 50, 0, 5);
  h1_MuN -> Add(h1_MuN_numu, h1_MuN_numubar, 1., 1.);
  h1_MuN -> SetLineColor(kAzure+9);
  h1_MuN -> SetLineWidth(3);
  h1_MuN -> SetStats(0);

  TH1F* h1_NuN = new TH1F("h1_NuN", "Truth distance; Distance from #mu Stop Vertex[m]; Number of Events", 50, 0, 5);
  h1_NuN -> Add(h1_NuN_numu, h1_NuN_numubar, 1., 1.);
  h1_NuN -> SetLineColor(kRed-7);
  h1_NuN -> SetLineWidth(3);
  h1_NuN -> SetStats(0);


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //c1 -> SetLogy();

  Double_t tot_mudecay = h1_MuN->Integral();
  Double_t tot_pidecay = h1_NuN->Integral();
  //h1_MuN -> Scale(1./tot_mudecay);
  //h1_NuN -> Scale(1./tot_pidecay);

  h1_NuN -> SetMaximum(5.2);
  //h1_MuN -> Draw();
  h1_NuN -> Draw("SAME");
  h1_MuN -> Draw("SAME");
  c1 -> RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.3, 0.69, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_MuN, "Only #mu capture neutrons", "L");
  legend1 -> AddEntry(h1_NuN, "#mu capture neutrons & #nu neutrons", "L");
  //legend1 -> AddEntry(h1_distance_nu_n, "Primary - n(from #nu) capture vtx", "L");
  //legend1 -> AddEntry(h1_distance_mu_n, "Primary - n(from #mu) capture vtx", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

}