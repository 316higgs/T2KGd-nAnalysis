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
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.003conc.0532.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.003conc.0532.root");
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


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCnonQE");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther");
  TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCnonQE");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_numubar -> SetStats(0);

  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar   -> SetLineColor(kOrange+7);
  h1_CCQE_numubar   -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar   -> SetFillColor(kOrange+7);
  h1_CCQE_numubar   -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "Neutrino Oscillation; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_numu);
  //hs_RecoOsc -> Add(h1_CCnonQE_numubar);  //non-QE = 2p2h + other
  //hs_RecoOsc -> Add(h1_CCnonQE_numu);
  hs_RecoOsc -> Add(h1_CCOther_numubar);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_NC_numubar);
  //hs_RecoOsc -> Add(h1_CCnonQE_numu);
  //hs_RecoOsc -> Add(h1_CCnonQE_numubar);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CCOther_numubar);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
#endif


  //===== w/ tagged neutrons ======
  TH1F* h1_CCQE_numu_wTagN    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_numu_wTagN  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_numu_wTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_CCnonQE_numu_wTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCnonQE_wNeutron");
  TH1F* h1_NC_numu_wTagN      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_numu_wTagN -> SetStats(0);

  TH1F* h1_CCQE_numubar_wTagN    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode0");
  TH1F* h1_CC2p2h_numubar_wTagN  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode1");
  TH1F* h1_CCOther_numubar_wTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron");
  TH1F* h1_CCnonQE_numubar_wTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCnonQE_wNeutron");
  TH1F* h1_NC_numubar_wTagN      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_wNeutron_mode2");
  h1_CCQE_numubar_wTagN -> SetStats(0);

  h1_CCOther_numu_wTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_wTagN -> SetFillColor(kCyan-8);
  h1_NC_numu_wTagN      -> SetLineColor(kSpring-9);
  h1_NC_numu_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar_wTagN    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar_wTagN    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar_wTagN  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar_wTagN  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_CCOther_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar_wTagN -> SetLineColor(kOrange+0);
  h1_NC_numubar_wTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar_wTagN    -> SetFillColor(kOrange+7);
  h1_CCQE_numubar_wTagN    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar_wTagN  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar_wTagN  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_CCOther_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar_wTagN -> SetFillColor(kOrange+0);
  h1_NC_numubar_wTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numu_wTagN       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar_wTagN    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu_wTagN     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar_wTagN  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu_wTagN    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar_wTagN -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu_wTagN    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar_wTagN -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu_wTagN         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar_wTagN      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_RecoOsc_wTagN = new THStack("hs_RecoOsc_wTagN", "Neutrino Oscillation w/ Tagged Neutrons; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc_wTagN -> Add(h1_NC_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numu_wTagN);
#endif
#if rhcflag
  hs_RecoOsc_wTagN -> Add(h1_NC_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCOther_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numubar_wTagN);
#endif


  //===== w/o tagged neutrons ======
  TH1F* h1_CCQE_numu_woTagN    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_numu_woTagN  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_numu_woTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_CCnonQE_numu_woTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCnonQE_woNeutron");
  TH1F* h1_NC_numu_woTagN      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_numu_woTagN -> SetStats(0);

  TH1F* h1_CCQE_numubar_woTagN    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode0");
  TH1F* h1_CC2p2h_numubar_woTagN  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode1");
  TH1F* h1_CCOther_numubar_woTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron");
  TH1F* h1_CCnonQE_numubar_woTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCnonQE_woNeutron");
  TH1F* h1_NC_numubar_woTagN      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProb_woNeutron_mode2");
  h1_CCQE_numubar_woTagN -> SetStats(0);

  h1_CCOther_numu_woTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_woTagN -> SetFillColor(kCyan-8);
  h1_NC_numu_woTagN      -> SetLineColor(kSpring-9);
  h1_NC_numu_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar_woTagN    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar_woTagN    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar_woTagN  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar_woTagN  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_CCOther_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar_woTagN -> SetLineColor(kOrange+0);
  h1_NC_numubar_woTagN      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar_woTagN    -> SetFillColor(kOrange+7);
  h1_CCQE_numubar_woTagN    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar_woTagN  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar_woTagN  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_CCOther_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar_woTagN -> SetFillColor(kOrange+0);
  h1_NC_numubar_woTagN      -> SetFillColor(kSpring-9);

  h1_CCQE_numu_woTagN       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar_woTagN    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu_woTagN     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar_woTagN  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu_woTagN    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar_woTagN -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu_woTagN    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar_woTagN -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu_woTagN         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar_woTagN      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_RecoOsc_woTagN = new THStack("hs_RecoOsc_woTagN", "Neutrino Oscillation w/o Tagged Neutrons; Reconstructed Neutrino Energy E_{#nu}[GeV]; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc_woTagN -> Add(h1_NC_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numu_woTagN);
#endif
#if rhcflag
  hs_RecoOsc_woTagN -> Add(h1_NC_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCOther_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numubar_woTagN);
#endif



#if 1
  // No NTag separation
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  if (beammode) hs_RecoOsc -> SetMaximum(16);
  else hs_RecoOsc -> SetMaximum(10);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.87, 0.87);
  legend1 -> SetTextSize(0.04);
  //if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  //legend1 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  //legend1 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 1
  // NTag separation
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  if (beammode) hs_RecoOsc_wTagN -> SetMaximum(16);
  else hs_RecoOsc_wTagN -> SetMaximum(10);
  hs_RecoOsc_wTagN -> Draw();
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_wTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_wTagN -> Draw();
  c2->RedrawAxis();

  TLegend* legend2 = new TLegend(0.45, 0.45, 0.87, 0.87);
  legend2 -> SetTextSize(0.04);
  //if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend2->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  else legend2->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend2->AddEntry((TObject*)0,"#kern[-0.3]{w/ tagged neutrons}","");
  legend2 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  //legend2 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  //legend2 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  legend2 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend2 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend2 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend2 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend2 -> AddEntry(h1_NC_numu, "NC", "F");
  legend2->SetFillColor(0);
  legend2->Draw();


  TCanvas* c3 = new TCanvas("c3","c3",900,700);
  c3 -> SetGrid();
  if (beammode) hs_RecoOsc_woTagN -> SetMaximum(16);
  else hs_RecoOsc_woTagN -> SetMaximum(10);
  hs_RecoOsc_woTagN -> Draw();
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_woTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_woTagN -> Draw();
  c3->RedrawAxis();

  TLegend* legend3 = new TLegend(0.45, 0.45, 0.87, 0.87);
  legend3 -> SetTextSize(0.04);
  //if (beammode) legend3->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend3->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  if (beammode) legend3->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  else legend3->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend3->AddEntry((TObject*)0,"#kern[-0.3]{w/o tagged neutrons}","");
  legend3 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  //legend3 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  //legend3 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  legend3 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend3 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend3 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend3 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend3 -> AddEntry(h1_NC_numu, "NC", "F");
  legend3->SetFillColor(0);
  legend3->Draw() ;
#endif

}