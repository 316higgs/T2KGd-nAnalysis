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
#define POTSCALE 0.17  //Run11 FHC

void mergeEnuOscillation(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << POTSCALE << " x 10^21 POT)" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC (" << POTSCALE << " x 10^21 POT)" << std::endl;


  //FHC
#if fhcflag
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
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
  Double_t GenN_numubar_x_nuebar  = 63460;
  Double_t GenN_nue_x_nue         = 63423;
  Double_t GenN_nuebar_x_nuebar   = 63652;
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


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg     = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_nuebkg   = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_nuebkg  = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_nuebkg       = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_nuebarbkg   = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_NC_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_nuebarbkg -> SetStats(0);

  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_NC_nuesig      -> SetLineColor(kSpring-9);

  h1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
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

  h1_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetFillColor(kSpring-9);

  /////  Normalizations  //////
#if 1
  h1_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "");
#if fhcflag
  hs_RecoOsc -> Add(h1_NC_nuebarbkg);
  hs_RecoOsc -> Add(h1_NC_nuebkg);
  hs_RecoOsc -> Add(h1_NC_nuebarsig);
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_nuesig);
  hs_RecoOsc -> Add(h1_NC_numu);

  hs_RecoOsc -> Add(h1_CCOther_nuebarbkg);
  hs_RecoOsc -> Add(h1_CC2p2h_nuebarbkg);
  hs_RecoOsc -> Add(h1_CCQE_nuebarbkg);
  hs_RecoOsc -> Add(h1_CCOther_nuebkg);
  hs_RecoOsc -> Add(h1_CC2p2h_nuebkg);
  hs_RecoOsc -> Add(h1_CCQE_nuebkg);
  hs_RecoOsc -> Add(h1_CCOther_nuebarsig);
  hs_RecoOsc -> Add(h1_CC2p2h_nuebarsig);
  hs_RecoOsc -> Add(h1_CCQE_nuebarsig);
  hs_RecoOsc -> Add(h1_CCOther_nuesig);
  hs_RecoOsc -> Add(h1_CC2p2h_nuesig);
  hs_RecoOsc -> Add(h1_CCQE_nuesig);

  hs_RecoOsc -> Add(h1_CCOther_numubar);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
#endif



  //===== w/ tagged neutrons ======
  TH1F* h1_CCQE_numu_wTagN    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_numu_wTagN  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_numu_wTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_numu_wTagN      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_numu_wTagN -> SetStats(0);

  TH1F* h1_CCQE_nuesig_wTagN    = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_nuesig_wTagN  = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_nuesig_wTagN = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_nuesig_wTagN      = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_nuesig_wTagN -> SetStats(0);

  TH1F* h1_CCQE_numubar_wTagN    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_numubar_wTagN  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_numubar_wTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_numubar_wTagN      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_numubar_wTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig_wTagN    = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_nuebarsig_wTagN  = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_nuebarsig_wTagN = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_nuebarsig_wTagN      = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_nuebarsig_wTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebkg_wTagN    = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_nuebkg_wTagN  = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_nuebkg_wTagN = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_nuebkg_wTagN      = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_nuebkg_wTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg_wTagN    = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_nuebarbkg_wTagN  = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_nuebarbkg_wTagN = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_NC_nuebarbkg_wTagN      = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_nuebarbkg_wTagN -> SetStats(0);

  h1_CCOther_numu_wTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_wTagN -> SetFillColor(kCyan-8);
  h1_NC_numu_wTagN      -> SetLineColor(kSpring-9);
  h1_NC_numu_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig_wTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig_wTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig_wTagN -> SetLineColor(kViolet-1);
  h1_NC_nuesig_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuesig_wTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig_wTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig_wTagN -> SetFillColor(kViolet-1);
  h1_NC_nuesig_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar_wTagN    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar_wTagN    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar_wTagN  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar_wTagN  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_CCOther_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_NC_numubar_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar_wTagN    -> SetFillColor(kOrange+7);
  h1_CCQE_numubar_wTagN    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar_wTagN  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar_wTagN  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_CCOther_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_NC_numubar_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarsig_wTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig_wTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig_wTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarsig_wTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig_wTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig_wTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebkg_wTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg_wTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg_wTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebkg_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebkg_wTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg_wTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg_wTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebkg_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarbkg_wTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg_wTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg_wTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarbkg_wTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg_wTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg_wTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg_wTagN      -> SetFillColor(kSpring-9);

  /////  Normalizations  //////
#if 1
  h1_CCQE_numu_wTagN         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig_wTagN       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar_wTagN      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig_wTagN    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg_wTagN       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCQE_nuebarbkg_wTagN    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu_wTagN       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig_wTagN     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar_wTagN    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig_wTagN  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg_wTagN     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CC2p2h_nuebarbkg_wTagN  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu_wTagN      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig_wTagN    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar_wTagN   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig_wTagN -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg_wTagN    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCOther_nuebarbkg_wTagN -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu_wTagN           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig_wTagN         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar_wTagN        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig_wTagN      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg_wTagN         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_NC_nuebarbkg_wTagN      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  THStack* hs_RecoOsc_wTagN = new THStack("hs_RecoOsc_wTagN", "");
#if fhcflag
  hs_RecoOsc_wTagN -> Add(h1_NC_nuebarbkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_nuebkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_nuebarsig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_nuesig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numu_wTagN);

  hs_RecoOsc_wTagN -> Add(h1_CCOther_nuebarbkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_nuebarbkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_nuebarbkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_nuebkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_nuebkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_nuebkg_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_nuebarsig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_nuebarsig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_nuebarsig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_nuesig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_nuesig_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_nuesig_wTagN);

  hs_RecoOsc_wTagN -> Add(h1_CCOther_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numu_wTagN);
#endif



  //===== w/o tagged neutrons ======
  TH1F* h1_CCQE_numu_woTagN    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_numu_woTagN  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_numu_woTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_numu_woTagN      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_numu_woTagN -> SetStats(0);

  TH1F* h1_CCQE_nuesig_woTagN    = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_nuesig_woTagN  = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_nuesig_woTagN = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_nuesig_woTagN      = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_nuesig_woTagN -> SetStats(0);

  TH1F* h1_CCQE_numubar_woTagN    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_numubar_woTagN  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_numubar_woTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_numubar_woTagN      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_numubar_woTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig_woTagN    = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_nuebarsig_woTagN  = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_nuebarsig_woTagN = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_nuebarsig_woTagN      = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_nuebarsig_woTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebkg_woTagN    = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_nuebkg_woTagN  = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_nuebkg_woTagN = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_nuebkg_woTagN      = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_nuebkg_woTagN -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg_woTagN    = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_nuebarbkg_woTagN  = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_nuebarbkg_woTagN = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_NC_nuebarbkg_woTagN      = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_nuebarbkg_woTagN -> SetStats(0);

  h1_CCOther_numu_woTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_woTagN -> SetFillColor(kCyan-8);
  h1_NC_numu_woTagN      -> SetLineColor(kSpring-9);
  h1_NC_numu_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig_woTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig_woTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig_woTagN -> SetLineColor(kViolet-1);
  h1_NC_nuesig_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuesig_woTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig_woTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig_woTagN -> SetFillColor(kViolet-1);
  h1_NC_nuesig_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar_woTagN    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar_woTagN    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar_woTagN  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar_woTagN  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_CCOther_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_NC_numubar_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar_woTagN    -> SetFillColor(kOrange+7);
  h1_CCQE_numubar_woTagN    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar_woTagN  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar_woTagN  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_CCOther_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_NC_numubar_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarsig_woTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig_woTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig_woTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarsig_woTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig_woTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig_woTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebkg_woTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg_woTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg_woTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebkg_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebkg_woTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg_woTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg_woTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebkg_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarbkg_woTagN    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg_woTagN  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg_woTagN -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_nuebarbkg_woTagN    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg_woTagN  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg_woTagN -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg_woTagN      -> SetFillColor(kSpring-9);

  /////  Normalizations  //////
#if 1
  h1_CCQE_numu_woTagN         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig_woTagN       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar_woTagN      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig_woTagN    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg_woTagN       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCQE_nuebarbkg_woTagN    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu_woTagN       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig_woTagN     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar_woTagN    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig_woTagN  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg_woTagN     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CC2p2h_nuebarbkg_woTagN  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu_woTagN      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig_woTagN    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar_woTagN   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig_woTagN -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg_woTagN    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCOther_nuebarbkg_woTagN -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu_woTagN           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig_woTagN         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar_woTagN        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig_woTagN      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg_woTagN         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_NC_nuebarbkg_woTagN      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  THStack* hs_RecoOsc_woTagN = new THStack("hs_RecoOsc_woTagN", "");
#if fhcflag
  hs_RecoOsc_woTagN -> Add(h1_NC_nuebarbkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_nuebkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_nuebarsig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_nuesig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numu_woTagN);

  hs_RecoOsc_woTagN -> Add(h1_CCOther_nuebarbkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_nuebarbkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_nuebarbkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_nuebkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_nuebkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_nuebkg_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_nuebarsig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_nuebarsig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_nuebarsig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_nuesig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_nuesig_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_nuesig_woTagN);

  hs_RecoOsc_woTagN -> Add(h1_CCOther_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numu_woTagN);
#endif



  gROOT -> SetStyle("Plain");
#if 1
  // No NTag separation
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  //if (beammode) hs_RecoOsc -> SetMaximum(16);
  //else hs_RecoOsc -> SetMaximum(10);
  if (beammode) hs_RecoOsc -> SetMaximum(2.1);
  else hs_RecoOsc -> SetMaximum(10);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.2);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc ->GetXaxis()->SetTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  hs_RecoOsc ->GetYaxis()->SetTitle("Number of Neutrino Events");
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  //if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
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
  // NTag separation
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  if (beammode) hs_RecoOsc_wTagN -> SetMaximum(2.1);
  else hs_RecoOsc_wTagN -> SetMaximum(10);
  hs_RecoOsc_wTagN -> Draw();
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleOffset(1.1);
  hs_RecoOsc_wTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_wTagN ->GetXaxis()->SetTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitle("Number of Neutrino Events");
  hs_RecoOsc_wTagN -> Draw();
  c2->RedrawAxis();

  TLegend* legend2 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend2->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  //if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  //else legend2->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend2->AddEntry((TObject*)0,"#kern[-0.35]{w/ tagged neutrons}","");
  legend2 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend2 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend2 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend2 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend2 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend2 -> AddEntry(h1_NC_numu, "NC", "F");
  legend2->SetFillColor(0);
  legend2->Draw();


  TCanvas* c3 = new TCanvas("c3","c3",900,700);
  c3 -> SetGrid();
  if (beammode) hs_RecoOsc_woTagN -> SetMaximum(2.1);
  else hs_RecoOsc_woTagN -> SetMaximum(10);
  hs_RecoOsc_woTagN -> Draw();
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleOffset(1.1);
  hs_RecoOsc_woTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_woTagN ->GetXaxis()->SetTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitle("Number of Neutrino Events");
  hs_RecoOsc_woTagN -> Draw();
  c3->RedrawAxis();

  TLegend* legend3 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend3 -> SetTextSize(0.04);
  if (beammode) legend3->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend3->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  //if (beammode) legend3->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  //else legend3->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend3->AddEntry((TObject*)0,"#kern[-0.35]{w/o tagged neutrons}","");
  legend3 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend3 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend3 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend3 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend3 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend3 -> AddEntry(h1_NC_numu, "NC", "F");
  legend3->SetFillColor(0);
  legend3->Draw() ;
#endif

}