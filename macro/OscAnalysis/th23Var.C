
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC


void th23Var(bool beammode, TString outname) {
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

/////////  0.01%  //////////
#if 0
  //  0.511
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF_0511.root");
#endif

#if 0
  //  0.550
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF_0530.root");
#endif

#if 0
  //  0.561
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
#endif

#if 0
  //  0.570
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF_0570.root");
#endif


/////////  (pseudo-)0.03%  //////////
#if 0
  //  0.511
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.003GdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.003GdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.003GdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.003GdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.003GdMC.bonsaikeras_ToF_0511.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.003GdMC.bonsaikeras_ToF_0511.root");
#endif

#if 0
  //  0.550
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.003GdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.003GdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.003GdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.003GdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.003GdMC.bonsaikeras_ToF_0530.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.003GdMC.bonsaikeras_ToF_0530.root");
#endif

#if 1
  //  0.561
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.003GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.003GdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.003GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.003GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.003GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.003GdMC.bonsaikeras_ToF.root");
#endif

#if 0
  //  0.570
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.003GdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.003GdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.003GdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.003GdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.003GdMC.bonsaikeras_ToF_0570.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.003GdMC.bonsaikeras_ToF_0570.root");
#endif

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

  //Whole spectra shape
  TH1F* h1_NoNTag = new TH1F("h1_NoNTag", "", 60, 0, 3);
  h1_NoNTag -> SetLineWidth(2);
  h1_NoNTag -> SetLineColor(kRed-4);
  h1_NoNTag -> Add(h1_NC_nuebarbkg);
  h1_NoNTag -> Add(h1_NC_nuebkg);
  h1_NoNTag -> Add(h1_NC_nuebarsig);
  h1_NoNTag -> Add(h1_NC_numubar);
  h1_NoNTag -> Add(h1_NC_nuesig);
  h1_NoNTag -> Add(h1_NC_numu);

  h1_NoNTag -> Add(h1_CCOther_nuebarbkg);
  h1_NoNTag -> Add(h1_CC2p2h_nuebarbkg);
  h1_NoNTag -> Add(h1_CCQE_nuebarbkg);
  h1_NoNTag -> Add(h1_CCOther_nuebkg);
  h1_NoNTag -> Add(h1_CC2p2h_nuebkg);
  h1_NoNTag -> Add(h1_CCQE_nuebkg);
  h1_NoNTag -> Add(h1_CCOther_nuebarsig);
  h1_NoNTag -> Add(h1_CC2p2h_nuebarsig);
  h1_NoNTag -> Add(h1_CCQE_nuebarsig);
  h1_NoNTag -> Add(h1_CCOther_nuesig);
  h1_NoNTag -> Add(h1_CC2p2h_nuesig);
  h1_NoNTag -> Add(h1_CCQE_nuesig);

  h1_NoNTag -> Add(h1_CCOther_numubar);
  h1_NoNTag -> Add(h1_CCOther_numu);
  h1_NoNTag -> Add(h1_CC2p2h_numubar);
  h1_NoNTag -> Add(h1_CC2p2h_numu);
  h1_NoNTag -> Add(h1_CCQE_numubar);
  h1_NoNTag -> Add(h1_CCQE_numu);
  if (beammode) h1_NoNTag -> SetMaximum(2.4);
  else h1_NoNTag -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_NoNTag = new TH1F("h1_CCQE_NoNTag", "", 60, 0, 3);
  h1_CCQE_NoNTag -> SetLineWidth(2);
  h1_CCQE_NoNTag -> SetLineColor(kRed-4);
  h1_CCQE_NoNTag -> Add(h1_CCQE_numu, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_nuesig, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_numubar, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_nuebarsig, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_nuebkg, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_nuebarbkg, 1);



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

  //Whole spectra shape
  TH1F* h1_wTagN = new TH1F("h1_wTagN", "", 60, 0, 3);
  h1_wTagN -> SetLineWidth(2);
  h1_wTagN -> SetLineColor(kRed-4);
  h1_wTagN -> Add(h1_NC_nuebarbkg_wTagN);
  h1_wTagN -> Add(h1_NC_nuebkg_wTagN);
  h1_wTagN -> Add(h1_NC_nuebarsig_wTagN);
  h1_wTagN -> Add(h1_NC_numubar_wTagN);
  h1_wTagN -> Add(h1_NC_nuesig_wTagN);
  h1_wTagN -> Add(h1_NC_numu_wTagN);

  h1_wTagN -> Add(h1_CCOther_nuebarbkg_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_nuebarbkg_wTagN);
  h1_wTagN -> Add(h1_CCQE_nuebarbkg_wTagN);
  h1_wTagN -> Add(h1_CCOther_nuebkg_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_nuebkg_wTagN);
  h1_wTagN -> Add(h1_CCQE_nuebkg_wTagN);
  h1_wTagN -> Add(h1_CCOther_nuebarsig_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_nuebarsig_wTagN);
  h1_wTagN -> Add(h1_CCQE_nuebarsig_wTagN);
  h1_wTagN -> Add(h1_CCOther_nuesig_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_nuesig_wTagN);
  h1_wTagN -> Add(h1_CCQE_nuesig_wTagN);

  h1_wTagN -> Add(h1_CCOther_numubar_wTagN);
  h1_wTagN -> Add(h1_CCOther_numu_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_numubar_wTagN);
  h1_wTagN -> Add(h1_CC2p2h_numu_wTagN);
  h1_wTagN -> Add(h1_CCQE_numubar_wTagN);
  h1_wTagN -> Add(h1_CCQE_numu_wTagN);
  if (beammode) h1_wTagN -> SetMaximum(2.4);
  else h1_wTagN -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_wTagN = new TH1F("h1_CCQE_wTagN", "", 60, 0, 3);
  h1_CCQE_wTagN -> SetLineWidth(2);
  h1_CCQE_wTagN -> SetLineColor(kRed-4);
  h1_CCQE_wTagN -> Add(h1_CCQE_numu_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_nuesig_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_numubar_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_nuebarsig_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_nuebkg_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_nuebarbkg_wTagN, 1);



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

  //Whole spectra shape
  TH1F* h1_woTagN = new TH1F("h1_woTagN", "", 60, 0, 3);
  h1_woTagN -> SetLineWidth(2);
  h1_woTagN -> SetLineColor(kRed-4);
  h1_woTagN -> Add(h1_NC_nuebarbkg_woTagN);
  h1_woTagN -> Add(h1_NC_nuebkg_woTagN);
  h1_woTagN -> Add(h1_NC_nuebarsig_woTagN);
  h1_woTagN -> Add(h1_NC_numubar_woTagN);
  h1_woTagN -> Add(h1_NC_nuesig_woTagN);
  h1_woTagN -> Add(h1_NC_numu_woTagN);

  h1_woTagN -> Add(h1_CCOther_nuebarbkg_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_nuebarbkg_woTagN);
  h1_woTagN -> Add(h1_CCQE_nuebarbkg_woTagN);
  h1_woTagN -> Add(h1_CCOther_nuebkg_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_nuebkg_woTagN);
  h1_woTagN -> Add(h1_CCQE_nuebkg_woTagN);
  h1_woTagN -> Add(h1_CCOther_nuebarsig_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_nuebarsig_woTagN);
  h1_woTagN -> Add(h1_CCQE_nuebarsig_woTagN);
  h1_woTagN -> Add(h1_CCOther_nuesig_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_nuesig_woTagN);
  h1_woTagN -> Add(h1_CCQE_nuesig_woTagN);

  h1_woTagN -> Add(h1_CCOther_numubar_woTagN);
  h1_woTagN -> Add(h1_CCOther_numu_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_numubar_woTagN);
  h1_woTagN -> Add(h1_CC2p2h_numu_woTagN);
  h1_woTagN -> Add(h1_CCQE_numubar_woTagN);
  h1_woTagN -> Add(h1_CCQE_numu_woTagN);
  if (beammode) h1_woTagN -> SetMaximum(2.4);
  else h1_woTagN -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_woTagN = new TH1F("h1_CCQE_woTagN", "", 60, 0, 3);
  h1_CCQE_woTagN -> SetLineWidth(2);
  h1_CCQE_woTagN -> SetLineColor(kRed-4);
  h1_CCQE_woTagN -> Add(h1_CCQE_numu_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_nuesig_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_numubar_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_nuebarsig_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_nuebkg_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_nuebarbkg_woTagN, 1);


#if 0
  TCanvas* c1 = new TCanvas("c1", "No NTag", 900, 700);
  c1 -> SetGrid();
  h1_NoNTag -> Draw();
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2", "w/ TagN", 900, 700);
  c2 -> SetGrid();
  h1_wTagN -> Draw();
#endif

#if 0
  TCanvas* c3 = new TCanvas("c3", "w/o TagN", 900, 700);
  c3 -> SetGrid();
  h1_woTagN -> Draw();
#endif

  TFile* fout = new TFile(outname+".root", "RECREATE");
  fout -> cd();
  h1_NoNTag -> Write();
  h1_wTagN  -> Write();
  h1_woTagN -> Write();

  h1_CCQE_NoNTag -> Write();
  h1_CCQE_wTagN  -> Write();
  h1_CCQE_woTagN -> Write();  

}


