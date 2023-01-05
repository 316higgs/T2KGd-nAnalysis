#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void PrmDistance(bool beammode) {

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
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_prm_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_prm_x_dcye.beforecut.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_prm_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_prm_x_dcye.beofrecut.root");
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


  TH1F* h1_mudecay_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_mudecay");
  TH1F* h1_pidecay_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_pidecay");
  h1_mudecay_numu -> SetStats(0);

  TH1F* h1_mudecay_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_mudecay");
  TH1F* h1_pidecay_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_pidecay");
  h1_mudecay_numubar -> SetStats(0);

  h1_mudecay_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_mudecay_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_pidecay_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_pidecay_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_mudecay = new TH1F("h1_mudecay", "Truth distance; Distance[m]; Number of Events", 50, 0, 5);
  h1_mudecay -> Add(h1_mudecay_numu, h1_mudecay_numubar, 1., 1.);
  h1_mudecay -> SetLineColor(kAzure+9);
  h1_mudecay -> SetLineWidth(3);
  h1_mudecay -> SetStats(0);

  TH1F* h1_pidecay = new TH1F("h1_pidecay", "Truth distance; Distance[m]; Number of Events", 50, 0, 5);
  h1_pidecay -> Add(h1_pidecay_numu, h1_pidecay_numubar, 1., 1.);
  h1_pidecay -> SetLineColor(kRed-7);
  h1_pidecay -> SetLineWidth(3);
  h1_pidecay -> SetStats(0);


  /*
  float TrueMuDecay = h1_mudecay->Integral();
  float TrueMuCap   = h1_mucap->Integral();
  float TruePiDecay = h1_pidecay->Integral();
  float CatMuDecay = 0.;
  float CatMuCap   = 0.;
  float CatPiDecay = 0.;

  float startd   = 0.;
  float interval = 0.01;
  const int BINS = 4;
  int binnumber = h1_mudecay->FindBin(startd);
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisd = startd + ibin*interval;
    //std::cout << "Distance = " << thisd << " m: " << binnumber << std::endl;
    //std::cout << "[" << thisd << " m, " << thisd+interval << " m] : " << h1_mudecay->GetBinContent(binnumber) << std::endl; 
    CatMuDecay += h1_mudecay->GetBinContent(binnumber);
    CatMuCap   += h1_mucap->GetBinContent(binnumber);
    CatPiDecay += h1_pidecay->GetBinContent(binnumber);
    binnumber++;
  }
  std::cout << "[###  mu- decay  ###] " << TrueMuDecay << " -> " << TrueMuDecay-CatMuDecay << " (removed " << CatMuDecay << " events)" << std::endl;
  //std::cout << "[### mu- capture ###] " << TrueMuCap << " -> " << TrueMuCap-CatMuCap << " (removed " << CatMuCap << " events)" << std::endl;
  std::cout << "[###  pi+ decay  ###] " << TruePiDecay << " -> " << TruePiDecay-CatPiDecay << " (removed " << CatPiDecay << " events)" << std::endl;
  */


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();

  Double_t tot_mudecay = h1_mudecay->Integral();
  Double_t tot_pidecay = h1_pidecay->Integral();
  //h1_mudecay -> Scale(1./tot_mudecay);
  //h1_pidecay -> Scale(1./tot_pidecay);

  h1_mudecay -> Draw("SAME");
  h1_pidecay -> Draw("SAME");
  c1 -> RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.7, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_mudecay, "Primary - #mu decay vtx", "L");
  legend1 -> AddEntry(h1_pidecay, "Primary - #pi^{+} decay vtx", "L");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}