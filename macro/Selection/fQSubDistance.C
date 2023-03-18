#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void fQSubDistance(bool beammode) {

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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.abovePmucut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.abovePmucut.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.belowEnucut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.belowEnucut.root");
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.aboveEnucut.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.aboveEnucut.root");

  //TFile* fin_numu    = new TFile("../../output/test.numu.root");
  //TFile* fin_numubar = new TFile("../../output/test.numubar.root");
  //TFile* fin_numu    = new TFile("../../output/test.numu.Enucut.root");
  //TFile* fin_numubar = new TFile("../../output/test.numubar.Enucut.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.Enucut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.Enucut.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.root");
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


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode1");
  TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode2");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode3");
  TH1F* h1_CC0pi_numu   = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode4");
  TH1F* h1_CC1pi_numu   = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode5");
  TH1F* h1_CCXpi_numu   = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode6");
  //TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode0");
  //TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode2");
  //TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode1");
  //TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode3");
  //TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode0");
  //TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode2");
  //TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode1");
  //TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode3");
  /*std::cout << "--numu--" << std::endl;
  std::cout << "  CCQE   : " << h1_CCQE_numu->Integral() << std::endl;
  std::cout << "  CC2p2h : " << h1_CC2p2h_numu->Integral() << std::endl;
  std::cout << "  CCnonQE: " << h1_CCnonQE_numu->Integral() << std::endl;
  std::cout << "  NC     : " << h1_NC_numu->Integral() << std::endl;*/

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode1");
  TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode2");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode3");
  TH1F* h1_CC0pi_numubar   = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode4");
  TH1F* h1_CC1pi_numubar   = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode5");
  TH1F* h1_CCXpi_numubar   = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_mode6");
  //TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode0");
  //TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode2");
  //TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode1");
  //TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_MuDcy_mode3");
  //TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode0");
  //TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode2");
  //TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode1");
  //TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DistanceViewer/h1_TruePrmMuEnd_x_fQDcyE_PiDcy_mode3");
  /*std::cout << "--numubar--" << std::endl;
  std::cout << "  CCQE   : " << h1_CCQE_numubar->Integral() << std::endl;
  std::cout << "  CC2p2h : " << h1_CC2p2h_numubar->Integral() << std::endl;
  std::cout << "  CCnonQE: " << h1_CCnonQE_numubar->Integral() << std::endl;
  std::cout << "  NC     : " << h1_NC_numubar->Integral() << std::endl;*/

  TH2F* h2_TruePrmMuEnd_x_fQDcyE_x_Pmu = (TH2F*)fin_numu->Get("DistanceViewer/h2_TruePrmMuEnd_x_fQDcyE_x_Pmu");
  //TH2F* h2_TruePrmMuEnd_x_fQDcyE_x_Pmu = (TH2F*)fin_numu->Get("DistanceViewer/h2_TruePrmMuEnd_x_fQDcyE_x_Enu");

  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC0pi_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC0pi_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC1pi_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC1pi_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCXpi_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCXpi_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CCnonQE_numu -> SetLineColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kTeal+9);
  h1_CC0pi_numu   -> SetLineColor(kViolet+8);
  h1_CC1pi_numu   -> SetLineColor(kAzure-9);
  h1_CCXpi_numu   -> SetLineColor(kAzure+9);

  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CCnonQE_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetFillColor(kTeal+9);
  h1_CC0pi_numu   -> SetFillColor(kViolet+8);
  h1_CC1pi_numu   -> SetFillColor(kAzure-9);
  h1_CCXpi_numu   -> SetFillColor(kAzure+9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kTeal+9);
  h1_CC0pi_numubar   -> SetLineColor(kOrange+2);
  h1_CC1pi_numubar   -> SetLineColor(kOrange+1);
  h1_CCXpi_numubar   -> SetLineColor(kOrange-2);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kTeal+9);
  h1_CC0pi_numubar   -> SetFillColor(kOrange+2);
  h1_CC1pi_numubar   -> SetFillColor(kOrange+1);
  h1_CCXpi_numubar   -> SetFillColor(kOrange-2);

  THStack* hs_TruePrmMuEnd_x_fQDcyE = new THStack("hs_TruePrmMuEnd_x_fQDcyE", "Decay-e-related distance; Distance from #mu End Vertex[m]; Number of Events");
#if fhcflag
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numu);

  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numu);

  /*
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCXpi_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCXpi_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC1pi_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC1pi_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC0pi_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC0pi_numu);
  */

  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numubar);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numu);
  hs_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numubar);
#endif

  TH1F* h1_TruePrmMuEnd_x_fQDcyE = new TH1F("h1_TruePrmMuEnd_x_fQDcyE", "Decay-e-related distance; Distance from #mu end vertex[m]; Number of Events", 100, 0, 3);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numu, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCQE_numubar, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numu, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CC2p2h_numubar, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numu, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_CCnonQE_numubar, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numu, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> Add(h1_NC_numubar, 1.);
  h1_TruePrmMuEnd_x_fQDcyE -> SetLineColor(kViolet-7);
  h1_TruePrmMuEnd_x_fQDcyE -> SetLineWidth(2);
  h1_TruePrmMuEnd_x_fQDcyE -> SetStats(0);

  Double_t AllEvents = h1_TruePrmMuEnd_x_fQDcyE -> Integral();
  //std::cout << "All events: " << AllEvents << std::endl;
  float start    = 0.;   // start value
  float maximum  = 3.; // histo end [cm]
  //const int BINS = 100;  // Number of bins
  const int BINS = 100;  // Number of bins
  float interval = (maximum - start)/BINS;   // bin witdh [cm]
  int   binnumber = h1_TruePrmMuEnd_x_fQDcyE->FindBin(start); // get bin number
  float OneSigmaEvents = 0.;
  float tmpvalue = 999.;
  float OneSigmaReso = 999.;
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisvalue = start+ibin*interval; // value of this bin
    OneSigmaEvents += h1_TruePrmMuEnd_x_fQDcyE->GetBinContent(binnumber);
    if (std::fabs(OneSigmaEvents/AllEvents - 0.683) < tmpvalue) {
      tmpvalue     = std::fabs(OneSigmaEvents/AllEvents - 0.683);
      OneSigmaReso = thisvalue;
    }
    //std::cout << "[### " << ibin << " ###] " << thisvalue << " cm, Area: " << (OneSigmaEvents/AllEvents)*100. << " %"<< std::endl;
    binnumber++;
  }
  std::cout << "OneSigmaReso: " << OneSigmaReso << " cm" << std::endl;

  float FrameMaximum = 16.;
  //float FrameMaximum = 3.;
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
  if (beammode) hs_TruePrmMuEnd_x_fQDcyE -> SetMaximum(FrameMaximum);
  else hs_TruePrmMuEnd_x_fQDcyE -> SetMaximum(50);
  //hs_TruePrmMuEnd_x_fQDcyE -> Draw();
  //hs_TruePrmMuEnd_x_fQDcyE ->GetYaxis()->SetTitleSize(0.038);
  //hs_TruePrmMuEnd_x_fQDcyE ->GetYaxis()->SetTitleOffset(1.3);
  //hs_TruePrmMuEnd_x_fQDcyE ->GetYaxis()->SetLabelSize(0.036);
  hs_TruePrmMuEnd_x_fQDcyE -> Draw();
  //h1_TruePrmMuEnd_x_fQDcyE -> Draw("SAME");
  //g_onesigma -> Draw("SAME");
  c1 -> RedrawAxis();

  
  TLegend* legend1 = new TLegend(0.45, 0.35, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");

  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC-other", "F");


  /*
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(0#pi)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(0#pi)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC0pi_numu, "#nu_{#mu} CC non-QE (0#pi)", "F");
  legend1 -> AddEntry(h1_CC0pi_numubar, "#bar{#nu}_{#mu} CC non-QE (0#pi)", "F");
  legend1 -> AddEntry(h1_CC1pi_numu, "#nu_{#mu} CC non-QE (1#pi)", "F");
  legend1 -> AddEntry(h1_CC1pi_numubar, "#bar{#nu}_{#mu} CC non-QE (1#pi)", "F");
  legend1 -> AddEntry(h1_CCXpi_numu, "#nu_{#mu} CC non-QE (other)", "F");
  legend1 -> AddEntry(h1_CCXpi_numubar, "#bar{#nu}_{#mu} CC non-QE (other)", "F");
  */

  //legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h2_TruePrmMuEnd_x_fQDcyE_x_Pmu -> Draw("COLZ");
#endif

}