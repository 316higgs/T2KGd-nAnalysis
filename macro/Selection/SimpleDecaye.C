#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

void SimpleDecaye(bool beammode) {

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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.aftercut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection.aftercut.root");

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  TFile* fin_nuesig  = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.2.1/skrate/fhc_sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection.aftercut.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection.aftercut.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  //Double_t GenN_numu_x_numu         = 190292;
  //Double_t GenN_numubar_x_numubar   = 190909;
  Double_t GenN_numu_x_numu         = 63576;
  Double_t GenN_numu_x_nue          = 63312;
  Double_t GenN_numubar_x_numubar   = 63458;
  std::cout << "Misc. factor: " << (NA*FV*1.e-6) / (50.e-3) << std::endl;
  std::cout << "[numu  -> numu ] ExpN_numu_x_numu = " << h1_skrate_numu_x_numu->Integral() << std::endl;
  std::cout << "[numu  -> numu ] GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "[numu  -> numu ] Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "[numu  -> nue  ] ExpN_numu_x_nue = " << h1_skrate_numu_x_nue->Integral() << std::endl;
  std::cout << "[numu  -> nue  ] GenN_numu_x_nue = " << GenN_numu_x_nue << std::endl;
  std::cout << "[numu  -> nue  ] Normalization factor for numu_x_nue       : " << (ExpN_numu_x_nue)/(GenN_numu_x_nue) << std::endl;
  std::cout << "[numub -> numub] ExpN_numubar_x_numubar = " << h1_skrate_numubar_x_numubar->Integral() << std::endl;
  std::cout << "[numub -> numub] GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "[numub -> numub] Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


#if 0
  //////////  True decay-e  /////////
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode6");
#endif
#if 0
  //////////  Reconstructed decay-e (fiTQun sub-events)  /////////
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_TaggedDecaye_mode2");
#endif
#if 1
  //////////  Reconstructed decay-e (floor cut)  /////////
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Decaye_mode3");
#endif
  h1_CCQE_numu -> SetStats(0);

#if 0
  //////////  True decay-e  /////////
  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TrueDecaye_mode6");
#endif
#if 0
  //////////  Reconstructed decay-e (fiTQun sub-events)  /////////
  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TaggedDecaye_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("DecayeBox/h1_TaggedDecaye_mode2");
#endif
#if 1
  //////////  Reconstructed decay-e (floor cut)  /////////
  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Decaye_mode3");
#endif
  h1_CCQE_nuesig -> SetStats(0);

#if 0
  //////////  True decay-e  /////////
  //TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode0");
  //TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode1");
  //TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode2");
  //TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode6");
#endif
#if 0
  //////////  Reconstructed decay-e (fiTQun sub-events)  /////////
  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_TaggedDecaye_mode2");
#endif
#if 1
  //////////  Reconstructed decay-e (floor cut)  /////////
  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Decaye_mode3");
#endif
  h1_CCQE_numubar -> SetStats(0);


  h1_CCQE_numu     -> SetLineColor(kAzure-1);
  h1_CCQE_numu     -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu   -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu   -> SetFillColor(kAzure-5);
  h1_CCOther_numu  -> SetLineColor(kCyan-8);
  h1_CCOther_numu  -> SetFillColor(kCyan-8);
  h1_NC_numu       -> SetLineColor(kSpring-9);
  h1_NC_numu       -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_NC_nuesig      -> SetLineColor(kSpring-9);

  h1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  /////  Normalizations  //////
#if 1
  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig   -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig  -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
#endif


  THStack* hs_Dcye = new THStack("hs_Dcye", "");
#if fhcflag
  hs_Dcye -> Add(h1_NC_numubar);
  hs_Dcye -> Add(h1_NC_nuesig);
  hs_Dcye -> Add(h1_NC_numu);
  hs_Dcye -> Add(h1_CCOther_nuesig);
  hs_Dcye -> Add(h1_CC2p2h_nuesig);
  hs_Dcye -> Add(h1_CCQE_nuesig);
  hs_Dcye -> Add(h1_CCOther_numubar);
  hs_Dcye -> Add(h1_CCOther_numu);
  hs_Dcye -> Add(h1_CC2p2h_numubar);
  hs_Dcye -> Add(h1_CC2p2h_numu);
  hs_Dcye -> Add(h1_CCQE_numubar);
  hs_Dcye -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_Dcye -> Add(h1_NC_numu);
  hs_Dcye -> Add(h1_NC_numubar);
  hs_Dcye -> Add(h1_CCOther_numu);
  hs_Dcye -> Add(h1_CCOther_numubar);
  hs_Dcye -> Add(h1_CC2p2h_numu);
  hs_Dcye -> Add(h1_CC2p2h_numubar);
  hs_Dcye -> Add(h1_CCQE_numu);
  hs_Dcye -> Add(h1_CCQE_numubar);
#endif

  #define NDCYE 2
  float y[2] = {0., 200.};
  float xC[2] = {NDCYE, NDCYE};
  TGraph* g_C = new TGraph(2, xC, y);
  g_C -> SetLineWidth(2);
  g_C -> SetLineColor(kViolet-8);
  g_C -> SetLineStyle(7);


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //hs_Dcye -> SetMaximum(18);
  hs_Dcye -> Draw();
  hs_Dcye ->GetYaxis()->SetTitleSize(0.038);
  hs_Dcye ->GetYaxis()->SetTitleOffset(1.3);
  hs_Dcye ->GetYaxis()->SetLabelSize(0.036);
  //hs_Dcye ->GetXaxis()->Title("Number of the Truth Decay-e");
  hs_Dcye ->GetXaxis()->SetTitle("Number of the Reconstructed Decay-e");
  hs_Dcye ->GetYaxis()->SetTitle("Number of #nu Events");
  hs_Dcye -> Draw();
  g_C     -> Draw("SAME");
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.4, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.35]{#fiTQun sub-events}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#nu_{#mu}+#bar{#nu}_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}