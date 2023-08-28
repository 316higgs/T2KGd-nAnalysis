
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run11 FHC

TString GetNNVarName(int vartype);
TString GetNNVarAxisName(int vartype);

void mergeNNinput(bool beammode) {

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

#if 0
  // Pre NN
  bool NTagapply = false;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.preNN.newGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.preNN.newGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC.root");
#endif

#if 1
  // Post NN
  bool NTagapply = true;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.postNN.newGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.postNN.newGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC.root");
#endif

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


  TH1F* h1_NNvar_Gd_numu[12];
  TH1F* h1_NNvar_H_numu[12];
  TH1F* h1_NNvar_AccNoise_numu[12];
  TH1F* h1_NNvar_Decaye_numu[12];

  TH1F* h1_NNvar_Gd_nuesig[12];
  TH1F* h1_NNvar_H_nuesig[12];
  TH1F* h1_NNvar_AccNoise_nuesig[12];
  TH1F* h1_NNvar_Decaye_nuesig[12];

  TH1F* h1_NNvar_Gd_numubar[12];
  TH1F* h1_NNvar_H_numubar[12];
  TH1F* h1_NNvar_AccNoise_numubar[12];
  TH1F* h1_NNvar_Decaye_numubar[12];

  TH1F* h1_NNvar_Gd_nuebarsig[12];
  TH1F* h1_NNvar_H_nuebarsig[12];
  TH1F* h1_NNvar_AccNoise_nuebarsig[12];
  TH1F* h1_NNvar_Decaye_nuebarsig[12];

  TH1F* h1_NNvar_Gd_nuebkg[12];
  TH1F* h1_NNvar_H_nuebkg[12];
  TH1F* h1_NNvar_AccNoise_nuebkg[12];
  TH1F* h1_NNvar_Decaye_nuebkg[12];

  TH1F* h1_NNvar_Gd_nuebarbkg[12];
  TH1F* h1_NNvar_H_nuebarbkg[12];
  TH1F* h1_NNvar_AccNoise_nuebarbkg[12];
  TH1F* h1_NNvar_Decaye_nuebarbkg[12];

  THStack* hs_NNvar[12];

  for (int i=0; i<12; i++) {
  	h1_NNvar_Gd_numu[i]       = (TH1F*)fin_numu->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_numu[i]        = (TH1F*)fin_numu->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_numu[i] = (TH1F*)fin_numu->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numu[i]   = (TH1F*)fin_numu->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_nuesig[i]       = (TH1F*)fin_nuesig->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_nuesig[i]        = (TH1F*)fin_nuesig->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_nuesig[i] = (TH1F*)fin_nuesig->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_nuesig[i]   = (TH1F*)fin_nuesig->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_numubar[i]       = (TH1F*)fin_numubar->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_numubar[i]        = (TH1F*)fin_numubar->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_numubar[i] = (TH1F*)fin_numubar->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numubar[i]   = (TH1F*)fin_numubar->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_nuebarsig[i]       = (TH1F*)fin_nuebarsig->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_nuebarsig[i]        = (TH1F*)fin_nuebarsig->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_nuebarsig[i] = (TH1F*)fin_nuebarsig->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_nuebarsig[i]   = (TH1F*)fin_nuebarsig->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_nuebkg[i]       = (TH1F*)fin_nuebkg->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_nuebkg[i]        = (TH1F*)fin_nuebkg->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_nuebkg[i] = (TH1F*)fin_nuebkg->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_nuebkg[i]   = (TH1F*)fin_nuebkg->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_nuebarbkg[i]       = (TH1F*)fin_nuebarbkg->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_nuebarbkg[i]        = (TH1F*)fin_nuebarbkg->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_nuebarbkg[i] = (TH1F*)fin_nuebarbkg->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_nuebarbkg[i]   = (TH1F*)fin_nuebarbkg->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_numu[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_numu[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_numu[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_numu[i] -> SetFillColor(kGray+2);

    h1_NNvar_Gd_nuesig[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_nuesig[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_nuesig[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_nuesig[i] -> SetFillColor(kGray+2);

    h1_NNvar_Gd_numubar[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_numubar[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_numubar[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_numubar[i] -> SetFillColor(kGray+2);

    h1_NNvar_Gd_nuebarsig[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_nuebarsig[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_nuebarsig[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_nuebarsig[i] -> SetFillColor(kGray+2);

    h1_NNvar_Gd_nuebkg[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_nuebkg[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_nuebkg[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_nuebkg[i] -> SetFillColor(kGray+2);

    h1_NNvar_Gd_nuebarbkg[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_nuebarbkg[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_nuebarbkg[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_nuebarbkg[i] -> SetFillColor(kGray+2);

#if 1
    // Normalization
    h1_NNvar_Gd_numu[i]       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NNvar_H_numu[i]        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NNvar_Decaye_numu[i]   -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NNvar_AccNoise_numu[i] -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );

    h1_NNvar_Gd_nuesig[i]       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NNvar_H_nuesig[i]        -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NNvar_Decaye_nuesig[i]   -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NNvar_AccNoise_nuesig[i] -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );

    h1_NNvar_Gd_numubar[i]       -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NNvar_H_numubar[i]        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NNvar_Decaye_numubar[i]   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NNvar_AccNoise_numubar[i] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

    h1_NNvar_Gd_nuebarsig[i]       -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NNvar_H_nuebarsig[i]        -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NNvar_Decaye_nuebarsig[i]   -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NNvar_AccNoise_nuebarsig[i] -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );

    h1_NNvar_Gd_nuebkg[i]       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NNvar_H_nuebkg[i]        -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NNvar_Decaye_nuebkg[i]   -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NNvar_AccNoise_nuebkg[i] -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );

    h1_NNvar_Gd_nuebarbkg[i]       -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NNvar_H_nuebarbkg[i]        -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NNvar_Decaye_nuebarbkg[i]   -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NNvar_AccNoise_nuebarbkg[i] -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

    TString hsname = GetNNVarName(i);
    hs_NNvar[i] = new THStack(TString::Format("hs_NNvar_var%d", i), hsname);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_numu[i]);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_nuesig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_numubar[i]);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_nuebarsig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_nuebkg[i]);
    hs_NNvar[i] -> Add(h1_NNvar_AccNoise_nuebarbkg[i]);

    hs_NNvar[i] -> Add(h1_NNvar_Decaye_numu[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Decaye_nuesig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Decaye_numubar[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Decaye_nuebarsig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Decaye_nuebkg[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Decaye_nuebarbkg[i]);

    hs_NNvar[i] -> Add(h1_NNvar_H_numu[i]);
    hs_NNvar[i] -> Add(h1_NNvar_H_nuesig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_H_numubar[i]);
    hs_NNvar[i] -> Add(h1_NNvar_H_nuebarsig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_H_nuebkg[i]);
    hs_NNvar[i] -> Add(h1_NNvar_H_nuebarbkg[i]);

    hs_NNvar[i] -> Add(h1_NNvar_Gd_numu[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Gd_nuesig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Gd_numubar[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Gd_nuebarsig[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Gd_nuebkg[i]);
    hs_NNvar[i] -> Add(h1_NNvar_Gd_nuebarbkg[i]);
  }

  
  // for sanity check of NN input variable plots
  h1_AllNHits = (TH1F*)fin_numu->Get("NNInputVariables/h1_AllNHits");
  h1_AllNHits -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  std::cout << "numu_x_numu #tag-n = " << h1_AllNHits->Integral() << std::endl;

#if 1
  TLegend* legend = new TLegend(0.45, 0.4, 0.89, 0.89);
  legend -> SetTextSize(0.06);
  if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN (Run11)}","");
  else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (Run11)}","");
  legend -> AddEntry(h1_NNvar_Gd_numu[0], "Gd-n signal", "F");
  legend -> AddEntry(h1_NNvar_H_numu[0], "H-n signal", "F");
  legend -> AddEntry(h1_NNvar_Decaye_numu[0], "Decay-e", "F");
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "Acc. noise", "F");
  legend -> SetFillColor(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
    c1 -> cd(i+1)->SetGrid();
    //gPad->SetLogy();
    hs_NNvar[i] -> Draw();
    TString varname = GetNNVarAxisName(i);
    hs_NNvar[i] -> GetXaxis()->SetTitle(varname);
    hs_NNvar[i] -> GetYaxis()->SetTitle("Number of Events");
    ((TGaxis*)hs_NNvar[i]->GetYaxis())->SetMaxDigits(3);
    hs_NNvar[i] -> GetYaxis()->SetTitleOffset(1.3);
    hs_NNvar[i] -> GetXaxis()->SetTitleSize(0.05);
    hs_NNvar[i] -> Draw();
    //hs_NNvar_nuesig[i] -> Draw("SAME");
    //if (i==0) legend -> Draw();
    if (i==11) legend -> Draw();
  }
#endif
}


TString GetNNVarName(int vartype) {
	TString histtitle;
  	switch (vartype) {
  	  case 0:
  	    histtitle = "NHits";
  	    break;
  	  case 1:
  	    histtitle = "N200";
  	    break;
  	  case 2:
  	    histtitle = "TRMS";
  	    break;
      case 3:
  	    histtitle = "DWall";
  	    break;
  	  case 4:
  	    histtitle = "DWallMeanDir";
  	    break;
  	  case 5:
  	    histtitle = "OpeningAngleMean";
  	    break;
      case 6:
  	    histtitle = "OpeningAngleStdev";
  	    break;
  	  case 7:
  	    histtitle = "OpeningAngleSkew";
  	    break;
  	  case 8:
  	    histtitle = "MeanDirAngleMean";
  	    break;
  	  case 9:
  	    histtitle = "MeanDirAngleRMS";
  	    break;
  	  case 10:
  	    histtitle = "Beta1; Beta1";
  	    break;
  	  case 11:
  	    histtitle = "Beta5; Beta5";
  	    break;
  	}
  return histtitle;
}

TString GetNNVarAxisName(int vartype) {
  TString varname;
  switch (vartype) {
  	  case 0:
  	    varname = "NHits";
  	    break;
  	  case 1:
  	    varname = "N200";
  	    break;
  	  case 2:
  	    varname = "TRMS [nsec]";
  	    break;
      case 3:
  	    varname = "DWall [cm]";
  	    break;
  	  case 4:
  	    varname = "DWallMeanDir [cm]";
  	    break;
  	  case 5:
  	    varname = "OpeningAngleMean [deg]";
  	    break;
      case 6:
  	    varname = "OpeningAngleStdev [deg]";
  	    break;
  	  case 7:
  	    varname = "OpeningAngleSkew";
  	    break;
  	  case 8:
  	    varname = "MeanDirAngleMean [deg]";
  	    break;
  	  case 9:
  	    varname = "MeanDirAngleRMS [deg]";
  	    break;
  	  case 10:
  	    varname = "Beta1";
  	    break;
  	  case 11:
  	    varname = "Beta5";
  	    break;
  	}
  return varname;
}
