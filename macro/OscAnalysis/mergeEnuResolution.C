#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
#define POTSCALE 1.63  //Run1-10 RHC

void mergeEnuResolution(bool beammode) {

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


  //===== No NTag ======
  TH1F* h1_All_numu     = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_Enureso_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther");  //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numu = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_EnuresoCCnonQE");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_Enureso_mode2");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_All_numubar     = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_AllEnureso");
  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_Enureso_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_Enureso_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther"); //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_EnuresoCCnonQE");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_Enureso_mode2");
  h1_CCQE_numubar -> SetStats(0);

  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_CCnonQE_numu -> SetLineColor(kCyan-8);
  h1_CCnonQE_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_CCnonQE_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_CCnonQE_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCnonQE_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCnonQE_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  //Histo
  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "Neutrino Oscillation; (E_{#nu}^{true}-E_{#nu}^{reco})/E_{#nu}^{true}; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_CCnonQE_numubar);
  hs_RecoOsc -> Add(h1_CCnonQE_numu);
  //hs_RecoOsc -> Add(h1_CCOther_numubar);
  //hs_RecoOsc -> Add(h1_CCOther_numu);
  //hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  //hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_NC_numubar);
  hs_RecoOsc -> Add(h1_CCnonQE_numu);
  hs_RecoOsc -> Add(h1_CCnonQE_numubar);
  //hs_RecoOsc -> Add(h1_CCOther_numu);
  //hs_RecoOsc -> Add(h1_CCOther_numubar);
  //hs_RecoOsc -> Add(h1_CC2p2h_numu);
  //hs_RecoOsc -> Add(h1_CC2p2h_numubar);
  hs_RecoOsc -> Add(h1_CCQE_numu);
  hs_RecoOsc -> Add(h1_CCQE_numubar);
#endif



/*
  //===== w/ tagged neutrons ======
  TH1F* h1_All_numu_wTagN     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_All_wTagN");
  TH1F* h1_CCQE_numu_wTagN    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCQE_wTagN");
  TH1F* h1_CC2p2h_numu_wTagN  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CC2p2h_wTagN");
  TH1F* h1_CCOther_numu_wTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron"); //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numu_wTagN = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTagN");
  TH1F* h1_NC_numu_wTagN      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_NC_wTagN");
  h1_CCQE_numu_wTagN -> SetStats(0);

  TH1F* h1_All_numubar_wTagN     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_All_wTagN");
  TH1F* h1_CCQE_numubar_wTagN    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCQE_wTagN");
  TH1F* h1_CC2p2h_numubar_wTagN  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CC2p2h_wTagN"); 
  TH1F* h1_CCOther_numubar_wTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_wNeutron"); //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numubar_wTagN = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCnonQE_wTagN");
  TH1F* h1_NC_numubar_wTagN      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_NC_wTagN");
  h1_CCQE_numubar_wTagN -> SetStats(0);

  h1_CCOther_numu_wTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_wTagN -> SetFillColor(kCyan-8);
  h1_CCnonQE_numu_wTagN -> SetLineColor(kCyan-8);
  h1_CCnonQE_numu_wTagN -> SetFillColor(kCyan-8);
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

  THStack* hs_RecoOsc_wTagN = new THStack("hs_RecoOsc_wTagN", "Neutrino Oscillation w/ Tagged Neutrons; (E_{#nu}^{true}-E_{#nu}^{reco})/E_{#nu}^{true}; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc_wTagN -> Add(h1_NC_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCOther_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCOther_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numu_wTagN);
#endif
#if rhcflag
  hs_RecoOsc_wTagN -> Add(h1_NC_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_NC_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCnonQE_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCOther_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CCOther_numubar_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  //hs_RecoOsc_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numu_wTagN);
  hs_RecoOsc_wTagN -> Add(h1_CCQE_numubar_wTagN);
#endif


  //===== w/o tagged neutrons ======
  TH1F* h1_All_numu_woTagN     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_All_woTagN");
  TH1F* h1_CCQE_numu_woTagN    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCQE_woTagN");
  TH1F* h1_CC2p2h_numu_woTagN  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CC2p2h_woTagN");
  TH1F* h1_CCOther_numu_woTagN = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron"); //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numu_woTagN = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTagN");
  TH1F* h1_NC_numu_woTagN      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Enureso_NC_woTagN");
  h1_CCQE_numu_woTagN -> SetStats(0);

  TH1F* h1_All_numubar_woTagN     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_All_woTagN");
  TH1F* h1_CCQE_numubar_woTagN    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCQE_woTagN");
  TH1F* h1_CC2p2h_numubar_woTagN  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CC2p2h_woTagN");
  TH1F* h1_CCOther_numubar_woTagN = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_OscProbCCOther_woNeutron"); //should be modified (Nov.29)
  TH1F* h1_CCnonQE_numubar_woTagN = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_CCnonQE_woTagN");
  TH1F* h1_NC_numubar_woTagN      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Enureso_NC_woTagN");
  h1_CCQE_numubar_woTagN -> SetStats(0);

  h1_CCOther_numu_woTagN -> SetLineColor(kCyan-8);
  h1_CCOther_numu_woTagN -> SetFillColor(kCyan-8);
  h1_CCnonQE_numu_woTagN -> SetLineColor(kCyan-8);
  h1_CCnonQE_numu_woTagN -> SetFillColor(kCyan-8);
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

  THStack* hs_RecoOsc_woTagN = new THStack("hs_RecoOsc_woTagN", "Neutrino Oscillation w/o Tagged Neutrons; (E_{#nu}^{true}-E_{#nu}^{reco})/E_{#nu}^{true}; Number of Neutrino Events");
#if fhcflag
  hs_RecoOsc_woTagN -> Add(h1_NC_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCOther_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCOther_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numu_woTagN);
#endif
#if rhcflag
  hs_RecoOsc_woTagN -> Add(h1_NC_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_NC_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCnonQE_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCOther_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CCOther_numubar_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  //hs_RecoOsc_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numu_woTagN);
  hs_RecoOsc_woTagN -> Add(h1_CCQE_numubar_woTagN);
#endif

*/


#if 1
  //No NTag separation
  //Show RMS
  std::cout << "--- No NTag ---" << std::endl;
  TH1F* h1_All = new TH1F("h1_All", "h1_All", 50, -0.8, 0.8);
  h1_All -> Add(h1_All_numu, h1_All_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS     = " << h1_All->GetRMS() << std::endl;

  TH1F* h1_CCQE = new TH1F("h1_CCQE", "h1_CCQE", 60, -1, 1);
  h1_CCQE -> Add(h1_CCQE_numu, h1_CCQE_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS    = " << h1_CCQE->GetRMS() << std::endl;

  TH1F* h1_CCnonQE = new TH1F("h1_CCnonQE", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE -> Add(h1_CCnonQE_numu, h1_CCnonQE_numubar, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE->GetRMS() << std::endl;
  std::cout << " " << std::endl;


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  if (beammode) hs_RecoOsc -> SetMaximum(150);
  else hs_RecoOsc -> SetMaximum(50);
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.4);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.55, 0.5, 0.88, 0.88);
  legend1 -> SetTextSize(0.038);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.3]{RHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif


#if 0
  //Show RMS
  std::cout << "--- w/ tagged-n ---" << std::endl;
  TH1F* h1_All_wTagN = new TH1F("h1_All_wTagN", "h1_All", 60, -1, 1);
  h1_All_wTagN -> Add(h1_All_numu_wTagN, h1_All_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS     = " << h1_All_wTagN->GetRMS() << std::endl;

  TH1F* h1_CCQE_wTagN = new TH1F("h1_CCQE_wTagN", "h1_CCQE", 60, -1, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_numu_wTagN, h1_CCQE_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS    = " << h1_CCQE_wTagN->GetRMS() << std::endl;

  TH1F* h1_CCnonQE_wTagN = new TH1F("h1_CCnonQE_wTagN", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE_wTagN -> Add(h1_CCnonQE_numu_wTagN, h1_CCnonQE_numubar_wTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE_wTagN->GetRMS() << std::endl;
  std::cout << " " << std::endl;

  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  if (beammode) hs_RecoOsc_wTagN -> SetMaximum(150);
  else hs_RecoOsc_wTagN -> SetMaximum(50);
  hs_RecoOsc_wTagN -> Draw();
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_wTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_wTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_wTagN -> Draw();
  c2->RedrawAxis();


  TLegend* legend2 = new TLegend(0.55, 0.5, 0.88, 0.87);
  legend2 -> SetTextSize(0.04);
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample}","");
  else legend2->AddEntry((TObject*)0,"#kern[-0.3]{RHC 1R #mu sample}","");
  legend2->AddEntry((TObject*)0,"#kern[-0.25]{w/ tagged neutrons}","");
  legend2 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend2 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  legend2 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  //legend2 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend2 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  //legend2 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  //legend2 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend2 -> AddEntry(h1_NC_numu, "NC", "F");
  legend2->SetFillColor(0);
  legend2->Draw() ;
#endif


#if 0
  //Show RMS
  std::cout << "--- w/o tagged-n ---" << std::endl;
  TH1F* h1_All_woTagN = new TH1F("h1_All_woTagN", "h1_All", 60, -1, 1);
  h1_All_woTagN -> Add(h1_All_numu_woTagN, h1_All_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "All RMS     = " << h1_All_woTagN->GetRMS() << std::endl;

  TH1F* h1_CCQE_woTagN = new TH1F("h1_CCQE_woTagN", "h1_CCQE", 60, -1, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_numu_woTagN, h1_CCQE_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCQE RMS    = " << h1_CCQE_woTagN->GetRMS() << std::endl;

  TH1F* h1_CCnonQE_woTagN = new TH1F("h1_CCnonQE_woTagN", "h1_CCnonQE", 60, -1, 1);
  h1_CCnonQE_woTagN -> Add(h1_CCnonQE_numu_woTagN, h1_CCnonQE_numubar_woTagN, (ExpN_numu_x_numu)/(GenN_numu_x_numu), (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar));
  std::cout << "CCnonQE RMS = " << h1_CCnonQE_woTagN->GetRMS() << std::endl;


  TCanvas* c3 = new TCanvas("c3","c3",900,700);
  c3 -> SetGrid();
  if (beammode) hs_RecoOsc_woTagN -> SetMaximum(150);
  else hs_RecoOsc_woTagN -> SetMaximum(50);
  hs_RecoOsc_woTagN -> Draw();
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc_woTagN ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc_woTagN ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc_woTagN -> Draw();
  c3->RedrawAxis();

  TLegend* legend3 = new TLegend(0.55, 0.5, 0.88, 0.87);
  legend3 -> SetTextSize(0.04);
  if (beammode) legend3->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample}","");
  else legend3->AddEntry((TObject*)0,"#kern[-0.3]{RHC 1R #mu sample}","");
  legend3->AddEntry((TObject*)0,"#kern[-0.25]{w/o tagged neutrons}","");
  legend3 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend3 -> AddEntry(h1_CCnonQE_numu, "#nu_{#mu} CC non-QE", "F");
  legend3 -> AddEntry(h1_CCnonQE_numubar, "#bar{#nu}_{#mu} CC non-QE", "F");
  //legend3 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend3 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  //legend3 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  //legend3 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend3 -> AddEntry(h1_NC_numu, "NC", "F");
  legend3->SetFillColor(0);
  legend3->Draw() ;
#endif

}