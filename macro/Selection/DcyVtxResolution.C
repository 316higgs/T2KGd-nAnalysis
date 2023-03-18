#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void DcyVtxResolution(bool beammode) {

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
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");
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


  TH1F* h1_DcyVtxReso_numu    = (TH1F*)fin_numu->Get("DecayeBox/h1_DcyVtxReso");
  TH1F* h1_DcyVtxReso_numubar    = (TH1F*)fin_numubar->Get("DecayeBox/h1_DcyVtxReso");

  h1_DcyVtxReso_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_DcyVtxReso_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_DcyVtxReso = new TH1F("h1_DcyVtxReso", "Decay Vertex Resolution; d_{Reco. vs True}[cm]; Number of Events", 2000, 0, 200);
  h1_DcyVtxReso -> Add(h1_DcyVtxReso_numu, 1.);
  h1_DcyVtxReso -> Add(h1_DcyVtxReso_numubar, 1.);
  h1_DcyVtxReso -> SetLineColor(kViolet-7);
  h1_DcyVtxReso -> SetLineWidth(2);
  h1_DcyVtxReso -> SetStats(0);

  Double_t AllEvents = h1_DcyVtxReso -> Integral();
  //std::cout << "All events: " << AllEvents << std::endl;
  float start    = 0.;   // start value
  float maximum  = 200.; // histo end [cm]
  //const int BINS = 100;  // Number of bins
  const int BINS = 2000;  // Number of bins
  float interval = (maximum - start)/BINS;   // bin witdh [cm]
  int   binnumber = h1_DcyVtxReso->FindBin(start); // get bin number
  float OneSigmaEvents = 0.;
  float tmpvalue = 999.;
  float OneSigmaReso = 999.;
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisvalue = start+ibin*interval; // value of this bin
    OneSigmaEvents += h1_DcyVtxReso->GetBinContent(binnumber);
    if (std::fabs(OneSigmaEvents/AllEvents - 0.683) < tmpvalue) {
      tmpvalue     = std::fabs(OneSigmaEvents/AllEvents - 0.683);
      OneSigmaReso = thisvalue;
    }
    //std::cout << "[### " << ibin << " ###] " << thisvalue << " cm, Area: " << (OneSigmaEvents/AllEvents)*100. << " %"<< std::endl;
    binnumber++;
  }
  std::cout << "OneSigmaReso: " << OneSigmaReso << " cm" << std::endl;

  float FrameMaximum = 8.;
  float y[2] = {0., FrameMaximum+10.};
  float x[2] = {OneSigmaReso, OneSigmaReso};
  TGraph* g_onesigma = new TGraph(2, x, y);
  g_onesigma -> SetLineWidth(2);
  g_onesigma -> SetLineColor(kViolet-8);
  g_onesigma -> SetLineStyle(7);

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_DcyVtxReso -> Draw("SAME");
  g_onesigma -> Draw("SAME");
  c1 -> RedrawAxis();

#endif

}