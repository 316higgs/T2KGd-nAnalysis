
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
#define POTSCALE 1.63  //Run1-10 RHC

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
  //==== 0.532 ====
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  //==== 0.511 ====
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.maximalmix.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.maximalmix.root");
  //==== 0.5 ====
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.0.5.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.0.5.root");
  //==== 0.55 ====
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.0.55.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.0.55.root");
 
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  //==== 0.532 ====
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  //==== 0.511 ====
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.maximalmix.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.maximalmix.root");
  //==== 0.5 ====
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.0.5.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.0.5.root");
  //==== 0.55 ====
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.0.55.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.0.55.root");

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


  //===== No NTag ======
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

  //Whole spectra shape
  TH1F* h1_NoNTag = new TH1F("h1_NoNTag", "No NTag", 60, 0, 3);
  h1_NoNTag -> SetLineWidth(2);
  h1_NoNTag -> SetLineColor(kRed-4);
  h1_NoNTag -> Add(h1_CCQE_numu, 1);
  h1_NoNTag -> Add(h1_CCQE_numubar, 1);
  h1_NoNTag -> Add(h1_CC2p2h_numu, 1);
  h1_NoNTag -> Add(h1_CC2p2h_numubar, 1);
  h1_NoNTag -> Add(h1_CCOther_numu, 1);
  h1_NoNTag -> Add(h1_CCOther_numubar, 1);
  h1_NoNTag -> Add(h1_NC_numu, 1);
  h1_NoNTag -> Add(h1_NC_numubar, 1);
  if (beammode) h1_NoNTag -> SetMaximum(20);
  else h1_NoNTag -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_NoNTag = new TH1F("h1_CCQE_NoNTag", "No NTag", 60, 0, 3);
  h1_CCQE_NoNTag -> SetLineWidth(2);
  h1_CCQE_NoNTag -> SetLineColor(kRed-4);
  h1_CCQE_NoNTag -> Add(h1_CCQE_numu, 1);
  h1_CCQE_NoNTag -> Add(h1_CCQE_numubar, 1);



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

  //Whole spectra shape
  TH1F* h1_wTagN = new TH1F("h1_wTagN", "w/ TagN", 60, 0, 3);
  h1_wTagN -> SetLineWidth(2);
  h1_wTagN -> SetLineColor(kRed-4);
  h1_wTagN -> Add(h1_CCQE_numu_wTagN, 1);
  h1_wTagN -> Add(h1_CCQE_numubar_wTagN, 1);
  h1_wTagN -> Add(h1_CC2p2h_numu_wTagN, 1);
  h1_wTagN -> Add(h1_CC2p2h_numubar_wTagN, 1);
  h1_wTagN -> Add(h1_CCOther_numu_wTagN, 1);
  h1_wTagN -> Add(h1_CCOther_numubar_wTagN, 1);
  h1_wTagN -> Add(h1_NC_numu_wTagN, 1);
  h1_wTagN -> Add(h1_NC_numubar_wTagN, 1);
  if (beammode) h1_wTagN -> SetMaximum(20);
  else h1_wTagN -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_wTagN = new TH1F("h1_CCQE_wTagN", "w/ TagN", 60, 0, 3);
  h1_CCQE_wTagN -> SetLineWidth(2);
  h1_CCQE_wTagN -> SetLineColor(kRed-4);
  h1_CCQE_wTagN -> Add(h1_CCQE_numu_wTagN, 1);
  h1_CCQE_wTagN -> Add(h1_CCQE_numubar_wTagN, 1);



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

  //Whole spectra shape
  TH1F* h1_woTagN = new TH1F("h1_woTagN", "w/o TagN", 60, 0, 3);
  h1_woTagN -> SetLineWidth(2);
  h1_woTagN -> SetLineColor(kRed-4);
  h1_woTagN -> Add(h1_CCQE_numu_woTagN, 1);
  h1_woTagN -> Add(h1_CCQE_numubar_woTagN, 1);
  h1_woTagN -> Add(h1_CC2p2h_numu_woTagN, 1);
  h1_woTagN -> Add(h1_CC2p2h_numubar_woTagN, 1);
  h1_woTagN -> Add(h1_CCOther_numu_woTagN, 1);
  h1_woTagN -> Add(h1_CCOther_numubar_woTagN, 1);
  h1_woTagN -> Add(h1_NC_numu_woTagN, 1);
  h1_woTagN -> Add(h1_NC_numubar_woTagN, 1);
  if (beammode) h1_woTagN -> SetMaximum(20);
  else h1_woTagN -> SetMaximum(11);

  //Only CCQE
  TH1F* h1_CCQE_woTagN = new TH1F("h1_CCQE_woTagN", "w/o TagN", 60, 0, 3);
  h1_CCQE_woTagN -> SetLineWidth(2);
  h1_CCQE_woTagN -> SetLineColor(kRed-4);
  h1_CCQE_woTagN -> Add(h1_CCQE_numu_woTagN, 1);
  h1_CCQE_woTagN -> Add(h1_CCQE_numubar_woTagN, 1);


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


