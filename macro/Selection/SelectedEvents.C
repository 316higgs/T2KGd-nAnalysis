#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void SelectedEvents(bool beammode) {

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
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.root");

  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  //TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar  = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue         = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar   = (TH1F*)fin_skrate->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar    = h1_skrate_numubar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue           = h1_skrate_nue_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar     = h1_skrate_nuebar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu       = 63622;
  Double_t GenN_numu_x_nue        = 63538;
  Double_t GenN_numubar_x_numubar = 63444;
  Double_t GenN_numubar_x_nuebar  = 63463;
  Double_t GenN_nue_x_nue         = 63379;
  Double_t GenN_nuebar_x_nuebar   = 63463;
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
  std::cout << "[numub -> nueb ] ExpN_numubar_x_nuebar = " << h1_skrate_numubar_x_nuebar->Integral() << std::endl;
  std::cout << "[numub -> nueb ] GenN_numubar_x_nuebar = " << GenN_numubar_x_nuebar << std::endl;
  std::cout << "[numub -> nueb ] Normalization factor for numubar_x_nuebar: " << (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) << std::endl;
  std::cout << "[nue   -> nue  ] ExpN_nue_x_nue = " << h1_skrate_nue_x_nue->Integral() << std::endl;
  std::cout << "[nue   -> nue  ] GenN_nue_x_nue = " << GenN_nue_x_nue << std::endl;
  std::cout << "[nue   -> nue  ] Normalization factor for nue_x_nue: " << (ExpN_nue_x_nue)/(GenN_nue_x_nue) << std::endl;
  std::cout << "[nueb  -> nueb ] ExpN_nuebar_x_nuebar = " << h1_skrate_nuebar_x_nuebar->Integral() << std::endl;
  std::cout << "[nueb  -> nueb ] GenN_nuebar_x_nuebar = " << GenN_nuebar_x_nuebar << std::endl;
  std::cout << "[nueb  -> nueb ] Normalization factor for nuebar_x_nuebar: " << (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) << std::endl;

// Neutrino events
#if 1
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  h1_CCQE_nuebkg -> SetStats(0);

  //TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode0");
  //TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode1");
  //TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode2");
  //TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelNuEvents_mode3");
  //h1_CCQE_nuebarbkg -> SetStats(0);
#endif

// Tagged neutrons
#if 0
  TH1F* h1_CCQE_numu     = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_numu   = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_numu       = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar     = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_numubar   = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_numubar       = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg     = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_nuebkg   = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_nuebkg  = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_nuebkg       = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_nuebkg -> SetStats(0);

  //TH1F* h1_CCQE_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  //TH1F* h1_CC2p2h_nuebarbkg   = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  //TH1F* h1_CCOther_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  //TH1F* h1_NC_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  //h1_CCQE_nuebarbkg -> SetStats(0);
#endif

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

  h1_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_NC_nuebkg      -> SetFillColor(kSpring-9);

  /*h1_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetFillColor(kSpring-9);*/


  /////  Normalizations  //////
#if 1
  h1_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  /////  Merged #Selected Neutrinos  //////
  THStack* hs_NuEvt = new THStack("hs_NuEvt", "");
#if fhcflag
  //hs_NuEvt -> Add(h1_NC_nuebarbkg);
  hs_NuEvt -> Add(h1_NC_nuebkg);
  hs_NuEvt -> Add(h1_NC_nuebarsig);
  hs_NuEvt -> Add(h1_NC_numubar);
  hs_NuEvt -> Add(h1_NC_nuesig);
  hs_NuEvt -> Add(h1_NC_numu);

  //hs_NuEvt -> Add(h1_CCOther_nuebarbkg);
  //hs_NuEvt -> Add(h1_CC2p2h_nuebarbkg);
  //hs_NuEvt -> Add(h1_CCQE_nuebarbkg);
  hs_NuEvt -> Add(h1_CCOther_nuebkg);
  hs_NuEvt -> Add(h1_CC2p2h_nuebkg);
  hs_NuEvt -> Add(h1_CCQE_nuebkg);
  hs_NuEvt -> Add(h1_CCOther_nuebarsig);
  hs_NuEvt -> Add(h1_CC2p2h_nuebarsig);
  hs_NuEvt -> Add(h1_CCQE_nuebarsig);
  hs_NuEvt -> Add(h1_CCOther_nuesig);
  hs_NuEvt -> Add(h1_CC2p2h_nuesig);
  hs_NuEvt -> Add(h1_CCQE_nuesig);

  hs_NuEvt -> Add(h1_CCOther_numubar);
  hs_NuEvt -> Add(h1_CCOther_numu);
  hs_NuEvt -> Add(h1_CC2p2h_numubar);
  hs_NuEvt -> Add(h1_CC2p2h_numu);
  hs_NuEvt -> Add(h1_CCQE_numubar);
  hs_NuEvt -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_NuEvt -> Add(h1_NC_numu);
  hs_NuEvt -> Add(h1_NC_numubar);
  hs_NuEvt -> Add(h1_CCOther_numu);
  hs_NuEvt -> Add(h1_CCOther_numubar);
  hs_NuEvt -> Add(h1_CC2p2h_numu);
  hs_NuEvt -> Add(h1_CC2p2h_numubar);
  hs_NuEvt -> Add(h1_CCQE_numu);
  hs_NuEvt -> Add(h1_CCQE_numubar);
#endif


  /////  Merged Selection Efficiency  //////
  TH1F* h1_SelEff_merge = new TH1F("h1_SelEff_merge", "", 6, 0, 6);
  h1_SelEff_merge -> Add(h1_CCQE_numu);
  h1_SelEff_merge -> Add(h1_CC2p2h_numu);
  h1_SelEff_merge -> Add(h1_CCOther_numu);
  h1_SelEff_merge -> Add(h1_NC_numu);
  h1_SelEff_merge -> Add(h1_CCQE_nuesig);
  h1_SelEff_merge -> Add(h1_CC2p2h_nuesig);
  h1_SelEff_merge -> Add(h1_CCOther_nuesig);
  h1_SelEff_merge -> Add(h1_NC_nuesig);
  h1_SelEff_merge -> Add(h1_CCQE_numubar);
  h1_SelEff_merge -> Add(h1_CC2p2h_numubar);
  h1_SelEff_merge -> Add(h1_CCOther_numubar);
  h1_SelEff_merge -> Add(h1_NC_numubar);
  h1_SelEff_merge -> Add(h1_CCQE_nuebarsig);
  h1_SelEff_merge -> Add(h1_CC2p2h_nuebarsig);
  h1_SelEff_merge -> Add(h1_CCOther_nuebarsig);
  h1_SelEff_merge -> Add(h1_NC_nuebarsig);
  h1_SelEff_merge -> Add(h1_CCQE_nuebkg);
  h1_SelEff_merge -> Add(h1_CC2p2h_nuebkg);
  h1_SelEff_merge -> Add(h1_CCOther_nuebkg);
  h1_SelEff_merge -> Add(h1_NC_nuebkg);
  //h1_SelEff_merge -> Add(h1_CCQE_nuebarbkg);
  //h1_SelEff_merge -> Add(h1_CC2p2h_nuebarbkg);
  //h1_SelEff_merge -> Add(h1_CCOther_nuebarbkg);
  //h1_SelEff_merge -> Add(h1_NC_nuebarbkg);
  float SelecEvFCFV = 0.;
  SelecEvFCFV += h1_CCQE_numu->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_numu->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_numu->GetBinContent(1);
  SelecEvFCFV += h1_NC_numu->GetBinContent(1);
  SelecEvFCFV += h1_CCQE_nuesig->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_nuesig->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_nuesig->GetBinContent(1);
  SelecEvFCFV += h1_NC_nuesig->GetBinContent(1);
  SelecEvFCFV += h1_CCQE_numubar->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_numubar->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_numubar->GetBinContent(1);
  SelecEvFCFV += h1_NC_numubar->GetBinContent(1);
  SelecEvFCFV += h1_CCQE_nuebarsig->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_nuebarsig->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_nuebarsig->GetBinContent(1);
  SelecEvFCFV += h1_NC_nuebarsig->GetBinContent(1);
  SelecEvFCFV += h1_CCQE_nuebkg->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_nuebkg->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_nuebkg->GetBinContent(1);
  SelecEvFCFV += h1_NC_nuebkg->GetBinContent(1);
  //SelecEvFCFV += h1_CCQE_nuebarbkg->GetBinContent(1);
  //SelecEvFCFV += h1_CC2p2h_nuebarbkg->GetBinContent(1);
  //SelecEvFCFV += h1_CCOther_nuebarbkg->GetBinContent(1);
  //SelecEvFCFV += h1_NC_nuebarbkg->GetBinContent(1);
  float SelecEv[6] = {0.};
  for (int i=0; i<6; i++) {
    std::cout << "######  Cut[" << i+1 << "]  ######" << std::endl;
    std::cout << "[numu    -> numu   ]  CCQE   : " << h1_CCQE_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> numu   ]  CC2p2h : " << h1_CC2p2h_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> numu   ]  CCOther: " << h1_CCOther_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> numu   ]  NC     : " << h1_NC_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> numu   ]  Total  : " << h1_CCQE_numu->GetBinContent(i+1) +
                                                      h1_CC2p2h_numu->GetBinContent(i+1) +
                                                      h1_CCOther_numu->GetBinContent(i+1) +
                                                      h1_NC_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> nue    ]  CCQE   : " << h1_CCQE_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> nue    ]  CC2p2h : " << h1_CC2p2h_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> nue    ]  CCOther: " << h1_CCOther_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> nue    ]  NC     : " << h1_NC_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[numu    -> nue    ]  Total  : " << h1_CCQE_nuesig->GetBinContent(i+1) +
                                                      h1_CC2p2h_nuesig->GetBinContent(i+1) +
                                                      h1_CCOther_nuesig->GetBinContent(i+1) +
                                                      h1_NC_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> numubar]  CCQE   : " << h1_CCQE_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> numubar]  CC2p2h : " << h1_CC2p2h_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> numubar]  CCOther: " << h1_CCOther_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> numubar]  NC     : " << h1_NC_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> numubar]  Total  : " << h1_CCQE_numubar->GetBinContent(i+1) +
                                                      h1_CC2p2h_numubar->GetBinContent(i+1) +
                                                      h1_CCOther_numubar->GetBinContent(i+1) +
                                                      h1_NC_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> nuebar ]  CCQE   : " << h1_CCQE_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> nuebar ]  CC2p2h : " << h1_CC2p2h_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> nuebar ]  CCOther: " << h1_CCOther_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> nuebar ]  NC     : " << h1_NC_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[numubar -> nuebar ]  Total  : " << h1_CCQE_nuebarsig->GetBinContent(i+1) +
                                                      h1_CC2p2h_nuebarsig->GetBinContent(i+1) +
                                                      h1_CCOther_nuebarsig->GetBinContent(i+1) +
                                                      h1_NC_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[nue     -> nue    ]  CCQE   : " << h1_CCQE_nuebkg->GetBinContent(i+1) << std::endl;
    std::cout << "[nue     -> nue    ]  CC2p2h : " << h1_CC2p2h_nuebkg->GetBinContent(i+1) << std::endl;
    std::cout << "[nue     -> nue    ]  CCOther: " << h1_CCOther_nuebkg->GetBinContent(i+1) << std::endl;
    std::cout << "[nue     -> nue    ]  NC     : " << h1_NC_nuebkg->GetBinContent(i+1) << std::endl;
    std::cout << "[nue     -> nue    ]  Total  : " << h1_CCQE_nuebkg->GetBinContent(i+1) +
                                                      h1_CC2p2h_nuebkg->GetBinContent(i+1) +
                                                      h1_CCOther_nuebkg->GetBinContent(i+1) +
                                                      h1_NC_nuebkg->GetBinContent(i+1) << std::endl;
    //std::cout << "[nuebar  -> nuebar ]  CCQE   : " << h1_CCQE_nuebarbkg->GetBinContent(i+1) << std::endl;
    //std::cout << "[nuebar  -> nuebar ]  CC2p2h : " << h1_CC2p2h_nuebarbkg->GetBinContent(i+1) << std::endl;
    //std::cout << "[nuebar  -> nuebar ]  CCOther: " << h1_CCOther_nuebarbkg->GetBinContent(i+1) << std::endl;
    //std::cout << "[nuebar  -> nuebar ]  NC     : " << h1_NC_nuebarbkg->GetBinContent(i+1) << std::endl;
    //std::cout << "[nuebar  -> nuebar ]  Total  : " << h1_CCQE_nuebarbkg->GetBinContent(i+1) +
    //                                                  h1_CC2p2h_nuebarbkg->GetBinContent(i+1) +
    //                                                  h1_CCOther_nuebarbkg->GetBinContent(i+1) +
    //                                                  h1_NC_nuebarbkg->GetBinContent(i+1) << std::endl;
    SelecEv[i] += h1_CCQE_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_numu->GetBinContent(i+1);
    SelecEv[i] += h1_NC_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CCQE_nuesig->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_nuesig->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_nuesig->GetBinContent(i+1);
    SelecEv[i] += h1_NC_nuesig->GetBinContent(i+1);
    SelecEv[i] += h1_CCQE_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_NC_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_CCQE_nuebarsig->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_nuebarsig->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_nuebarsig->GetBinContent(i+1);
    SelecEv[i] += h1_NC_nuebarsig->GetBinContent(i+1);
    SelecEv[i] += h1_CCQE_nuebkg->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_nuebkg->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_nuebkg->GetBinContent(i+1);
    SelecEv[i] += h1_NC_nuebkg->GetBinContent(i+1);
    //SelecEv[i] += h1_CCQE_nuebarbkg->GetBinContent(i+1);
    //SelecEv[i] += h1_CC2p2h_nuebarbkg->GetBinContent(i+1);
    //SelecEv[i] += h1_CCOther_nuebarbkg->GetBinContent(i+1);
    //SelecEv[i] += h1_NC_nuebarbkg->GetBinContent(i+1);
    std::cout << "Cut[" << i+1 << "] Total: " << SelecEv[i] << std::endl;
  }
  h1_SelEff_merge -> Scale(1./SelecEvFCFV);
  for (int i=0; i<6; i++) {
    std::cout << "Cut[" << i+1 << "] Efficiency: " << h1_SelEff_merge->GetBinContent(i+1) << std::endl;
  }
  h1_SelEff_merge -> SetLineColor(kViolet-7);
  h1_SelEff_merge -> SetLineWidth(2);
  h1_SelEff_merge -> SetFillColor(kViolet-9);
  h1_SelEff_merge -> SetFillStyle(3004);
  h1_SelEff_merge -> SetStats(0);
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");


#if 1
  // Number of Events

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1", 1000,700);
  c1 -> SetGrid();
  //hs_NuEvt -> SetMaximum(20000);
  if (beammode) hs_NuEvt -> SetMaximum(110);
  //if (beammode) hs_NuEvt -> SetMaximum(180);
  //else hs_NuEvt -> SetMaximum(10);
  hs_NuEvt -> Draw();
  hs_NuEvt ->GetYaxis()->SetTitleSize(0.038);
  hs_NuEvt ->GetYaxis()->SetTitleOffset(1.3);
  hs_NuEvt ->GetYaxis()->SetLabelSize(0.036);
  hs_NuEvt ->GetYaxis()->SetTitle("Number of #nu Events");
  //hs_NuEvt ->GetYaxis()->SetTitle("Number of Tagged Neutrons");
  hs_NuEvt -> Draw();
  TGaxis* axis = new TGaxis(6, 0, 6, 115, 0, 115, 23, "+L");
  axis -> SetLabelColor(kWhite);
  //axis -> Draw();
  c1 -> RedrawAxis();


  TLegend* legend1 = new TLegend(0.47, 0.42, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC (0.01% Gd)}","");
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 1
  //Selection efficiency

  TCanvas* c2 = new TCanvas("c2","c2",1000,700);
  c2 -> SetGrid();
  h1_SelEff_merge -> SetMinimum(0.);
  h1_SelEff_merge -> SetMaximum(1.1);
  h1_SelEff_merge -> Draw();
  h1_SelEff_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_SelEff_merge ->GetYaxis()->SetTitleOffset(0.9);
  h1_SelEff_merge ->GetYaxis()->SetLabelSize(0.04);
  h1_SelEff_merge ->GetYaxis()->SetTitle("Selection Efficiency");
  h1_SelEff_merge ->GetYaxis()->SetTitleSize(0.045);
  h1_SelEff_merge ->GetXaxis()->SetTitleSize(0.06);
  h1_SelEff_merge -> Draw();
  c2->RedrawAxis();
  
  TLatex* text1 = new TLatex(0.47, 0.82, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.05);
  TLatex* text2 = new TLatex(0.5, 0.77, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.5, 0.72, "-Efficiency of #nu events");
  //TLatex* text3 = new TLatex(0.5, 0.72, "-Efficiency of tagged neutrons");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
#endif
}