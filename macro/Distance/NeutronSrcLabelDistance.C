#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void NeutronSrcLabelDistance(bool beammode) {

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
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");
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


  TH1F* h1_BefSIn_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_nu_BefSIn");
  TH1F* h1_SIn_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_nu_SIn");

  TH1F* h1_BefSIn_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_nu_BefSIn");
  TH1F* h1_SIn_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_nu_SIn");

  h1_BefSIn_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_BefSIn_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_SIn_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_SIn_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  h1_BefSIn_numu -> SetLineColor(kAzure-9);
  h1_SIn_numu    -> SetLineColor(kAzure+1);

#if 0
  h1_BefSIn_numu -> SetLineWidth(3);
  h1_SIn_numu    -> SetLineWidth(3);
  h1_BefSIn_numu -> SetYTitle("Area Normalized");
  h1_BefSIn_numu -> SetStats(0);

  Double_t BefSIn_numu = h1_BefSIn_numu->Integral();
  Double_t SIn_numu    = h1_SIn_numu->Integral();
  h1_BefSIn_numu -> Scale(1./BefSIn_numu);
  h1_SIn_numu    -> Scale(1./SIn_numu);
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c1", "c1", 900, 700);
  c2 -> SetGrid();
  //h1_SIn_numu -> SetMaximum(FrameMaximum);
  h1_BefSIn_numu -> Draw("SAME");
  h1_SIn_numu -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.4, 0.65, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend2->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");
  legend2 -> AddEntry(h1_BefSIn_numu, "#nu_{#mu} Primary or FSI neutrons", "L");
  legend2 -> AddEntry(h1_SIn_numu, "#nu_{#mu} SI neutrons", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif

  h1_BefSIn_numu -> SetFillColor(kAzure-9);
  h1_SIn_numu    -> SetFillColor(kAzure+1);

  h1_BefSIn_numubar -> SetLineColor(kOrange+6);
  h1_SIn_numubar    -> SetLineColor(kOrange+1);

  h1_BefSIn_numubar -> SetFillColor(kOrange+6);
  h1_SIn_numubar    -> SetFillColor(kOrange+1);

  //THStack* hs_TruePrmMuEnd_x_TrueNCap = new THStack("hs_TruePrmMuEnd_x_TrueNCap", "Neutron-related distance; Distance from #mu End Vertex[m]; Number of Events");
  THStack* hs_TruePrmMuEnd_x_TrueNCap = new THStack("hs_TruePrmMuEnd_x_TrueNCap", "Neutron-related distance; Distance from Primary Vertex[m]; Number of Events");
#if fhcflag
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numu);
#endif
#if rhcflag
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numubar);
#endif

  //float FrameMaximum = 4.;
  float FrameMaximum = 9.;

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  if (beammode) hs_TruePrmMuEnd_x_TrueNCap -> SetMaximum(FrameMaximum);
  else hs_TruePrmMuEnd_x_TrueNCap -> SetMaximum(50);
  hs_TruePrmMuEnd_x_TrueNCap -> Draw();
  c1 -> RedrawAxis();

  
  TLegend* legend1 = new TLegend(0.4, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_BefSIn_numu, "#nu_{#mu} Primary or FSI neutrons", "F");
  legend1 -> AddEntry(h1_BefSIn_numubar, "#bar{#nu}_{#mu} Primary or FSI neutrons", "F");
  legend1 -> AddEntry(h1_SIn_numu, "#nu_{#mu} SI neutrons", "F");
  legend1 -> AddEntry(h1_SIn_numubar, "#bar{#nu}_{#mu} SI neutrons", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}
