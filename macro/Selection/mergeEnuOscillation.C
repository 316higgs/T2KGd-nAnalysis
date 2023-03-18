#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void mergeEnuOscillation(bool beammode) {

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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numu_Enucut    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.Enucut.root");
  //TFile* fin_numubar_Enucut = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.Enucut.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.alldcye.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.alldcye.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcye0.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcye0.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcye1.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcye1.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcye2.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcye2.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcyecut1.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcyecut1.root");
  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcyecut2.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcyecut2.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcyecut1.final.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcyecut1.final.root");
  TFile* fin_numu    = new TFile("../../output/fhc/test.numu.dcyecut2.final.root");
  TFile* fin_numubar = new TFile("../../output/fhc/test.numubar.dcyecut2.final.root");

  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.003conc.0532.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.003conc.0532.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
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


  TH1F* h1_CCQE_numu     = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode0");
  TH1F* h1_CC2p2h_numu   = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode1");
  TH1F* h1_CCOther_numu  = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode2");
  TH1F* h1_CCRES_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode4");
  TH1F* h1_CCPiProd_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode5");
  TH1F* h1_NC_numu       = (TH1F*)fin_numu->Get("DistanceViewer/h1_Erec_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar     = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode0");
  TH1F* h1_CC2p2h_numubar   = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode1");
  TH1F* h1_CCOther_numubar  = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode2");
  TH1F* h1_CCRES_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode4");
  TH1F* h1_CCPiProd_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode5");
  TH1F* h1_NC_numubar       = (TH1F*)fin_numubar->Get("DistanceViewer/h1_Erec_mode3");
  h1_CCQE_numubar -> SetStats(0);

  h1_CCQE_numu     -> SetLineColor(kAzure-1);
  h1_CCQE_numu     -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu   -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu   -> SetFillColor(kAzure-5);
  h1_CCOther_numu  -> SetLineColor(kCyan-8);
  h1_CCOther_numu  -> SetFillColor(kCyan-8);
  h1_CCRES_numu    -> SetLineColor(kCyan-8);
  h1_CCRES_numu    -> SetFillColor(kCyan-8);
  h1_CCPiProd_numu -> SetLineColor(kAzure-4);
  h1_CCPiProd_numu -> SetFillColor(kAzure-4);
  h1_NC_numu       -> SetLineColor(kSpring-9);
  h1_NC_numu       -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCRES_numubar   -> SetLineColor(kOrange+0);
  h1_CCRES_numubar   -> SetFillColor(kOrange+0);
  h1_CCPiProd_numubar-> SetLineColor(kOrange-9);
  h1_CCPiProd_numubar-> SetFillColor(kOrange-9);
  h1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_NC_numubar      -> SetFillColor(kSpring-9);
  
  h1_CCQE_numu        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar     -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCRES_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCRES_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCPiProd_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCPiProd_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu          -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar       -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "Neutrino Oscillation; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
#if fhcflag
  /*
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_CCOther_numubar);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  */

  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_CCPiProd_numubar);
  hs_RecoOsc -> Add(h1_CCPiProd_numu);
  hs_RecoOsc -> Add(h1_CCRES_numubar);
  hs_RecoOsc -> Add(h1_CCRES_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CCOther_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
#endif


#if 1
  // No NTag separation
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  if (beammode) hs_RecoOsc -> SetMaximum(19);
  //if (beammode) hs_RecoOsc -> SetMaximum(16);
  else hs_RecoOsc -> SetMaximum(10);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.4, 0.87, 0.87);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  //if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");

  /*
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  */

  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCRES_numu, "#nu_{#mu} CC-RES", "F");
  legend1 -> AddEntry(h1_CCRES_numubar, "#bar{#nu}_{#mu} CC-RES", "F");
  legend1 -> AddEntry(h1_CCPiProd_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCPiProd_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");

  legend1->SetFillColor(0);
  legend1->Draw();
#endif
  

}