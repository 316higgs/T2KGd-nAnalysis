
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run11 FHC

#define NNFEATURES 14

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.preNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.preNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.preNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC_bonsai_keras_prompt_vertex.root");

  TFile* fin_data = new TFile("../../output/fhc/preNN.run11.bonsai_keras_prompt_vertex.root");
#endif

#if 1
  // Post NN
  bool NTagapply = true;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.postNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.postNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.postNN.newGdMC_bonsai_keras_prompt_vertex.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC_bonsai_keras_prompt_vertex.root");

  TFile* fin_data = new TFile("../../output/fhc/postNN.run11.bonsai_keras_prompt_vertex.root");
#endif

#if 0
  // Pre NN
  bool NTagapply = false;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");

  TFile* fin_data = new TFile("../../output/fhc/preNN.run11.FCFVvalid.bonsai_keras_prompt_vertex.root");
#endif

#if 0
  // Post NN
  bool NTagapply = true;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC_bonsai_keras_prompt_vertex.FCFVvalid.root");

  TFile* fin_data = new TFile("../../output/fhc/postNN.run11.FCFVvalid.bonsai_keras_prompt_vertex.root");
#endif

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


  TH1F* h1_NNvar_Gd_numu[NNFEATURES];
  TH1F* h1_NNvar_H_numu[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_numu[NNFEATURES];
  TH1F* h1_NNvar_Decaye_numu[NNFEATURES];

  TH1F* h1_NNvar_Gd_nuesig[NNFEATURES];
  TH1F* h1_NNvar_H_nuesig[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_nuesig[NNFEATURES];
  TH1F* h1_NNvar_Decaye_nuesig[NNFEATURES];

  TH1F* h1_NNvar_Gd_numubar[NNFEATURES];
  TH1F* h1_NNvar_H_numubar[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_numubar[NNFEATURES];
  TH1F* h1_NNvar_Decaye_numubar[NNFEATURES];

  TH1F* h1_NNvar_Gd_nuebarsig[NNFEATURES];
  TH1F* h1_NNvar_H_nuebarsig[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_nuebarsig[NNFEATURES];
  TH1F* h1_NNvar_Decaye_nuebarsig[NNFEATURES];

  TH1F* h1_NNvar_Gd_nuebkg[NNFEATURES];
  TH1F* h1_NNvar_H_nuebkg[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_nuebkg[NNFEATURES];
  TH1F* h1_NNvar_Decaye_nuebkg[NNFEATURES];

  TH1F* h1_NNvar_Gd_nuebarbkg[NNFEATURES];
  TH1F* h1_NNvar_H_nuebarbkg[NNFEATURES];
  TH1F* h1_NNvar_AccNoise_nuebarbkg[NNFEATURES];
  TH1F* h1_NNvar_Decaye_nuebarbkg[NNFEATURES];

  THStack* hs_NNvar[NNFEATURES];

  for (int i=0; i<NNFEATURES; i++) {
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
  //h1_AllNHits = (TH1F*)fin_numu->Get("NNInputVariables/h1_AllNHits");
  //h1_AllNHits -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //std::cout << "numu_x_numu #tag-n = " << h1_AllNHits->Integral() << std::endl;


  TH1F* h1_NNvar_data[NNFEATURES];
  for (int i=0; i<NNFEATURES; i++) {
    h1_NNvar_data[i] = (TH1F*)fin_data->Get(TString::Format("NNInputVariables/h1_NNvar_type%d", i));
    h1_NNvar_data[i] -> SetMarkerStyle(20);
    h1_NNvar_data[i] -> SetMarkerSize(1);
    h1_NNvar_data[i] -> SetMarkerColor(kBlack);
    h1_NNvar_data[i] -> SetLineColor(kBlack);
    h1_NNvar_data[i] -> SetLineWidth(1.5);
  }


#if 1
  gROOT -> SetStyle("Plain");
  TLegend* legend = new TLegend(0.2, 0.1, 0.89, 0.89);
  legend -> SetTextSize(0.08);
  if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN (Run11)}","");
  else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (Run11)}","");
  //if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN (FCFV applied)}","");
  //else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (FCFV applied)}","");
  legend -> AddEntry(h1_NNvar_Gd_numu[0], "Gd-n signal", "F");
  legend -> AddEntry(h1_NNvar_H_numu[0], "H-n signal", "F");
  legend -> AddEntry(h1_NNvar_Decaye_numu[0], "Decay-e", "F");
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "Acc. noise", "F");
  legend -> SetFillColor(0);

  gROOT -> SetStyle("Plain");
  //TCanvas* c1 = new TCanvas("c1", "c1", 1400, 1000);
  TCanvas* c1 = new TCanvas("c1", "c1", 800, 1400);
  c1 -> Divide(3,5);
  //for (int i=0; i<1; i++) {
  for (int i=0; i<NNFEATURES; i++) {
    c1 -> cd(i+1)->SetGrid();
    gPad->SetLogy();

    if (!NTagapply) {
      if (i==0 || i==1 || i==2 || i==4 || i==5 || i==7) hs_NNvar[i] -> SetMaximum(70);
      if (i==6) hs_NNvar[i] -> SetMaximum(50);
      if (i==8) hs_NNvar[i] -> SetMaximum(100);
      if (i==9 || i==10 || i==12) hs_NNvar[i] -> SetMaximum(120);
    }

    hs_NNvar[i] -> Draw();
    TString varname = GetNNVarAxisName(i);
    hs_NNvar[i] -> GetXaxis()->SetTitle(varname);
    hs_NNvar[i] -> GetYaxis()->SetTitle("Number of Events");
    ((TGaxis*)hs_NNvar[i]->GetYaxis())->SetMaxDigits(3);
    hs_NNvar[i] -> GetYaxis()->SetTitleOffset(1.3);
    hs_NNvar[i] -> GetXaxis()->SetTitleSize(0.05);
    hs_NNvar[i] -> Draw();
    
    h1_NNvar_data[i] -> Draw("SAME E P");

    //hs_NNvar_nuesig[i] -> Draw("SAME");
    //if (i==0) legend -> Draw();
  }
  c1 -> cd(15) -> SetGrid();
  legend -> Draw();
#endif


  //  only NHits
#if 0
  TLegend* legend = new TLegend(0.5, 0.5, 0.89, 0.89);
  legend -> SetTextSize(0.045);
  if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN (Run11)}","");
  else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (Run11)}","");
  //if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN (FCFV applied)}","");
  //else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (FCFV applied)}","");
  legend -> AddEntry(h1_NNvar_Gd_numu[0], "Gd-n signal", "F");
  legend -> AddEntry(h1_NNvar_H_numu[0], "H-n signal", "F");
  legend -> AddEntry(h1_NNvar_Decaye_numu[0], "Decay-e", "F");
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "Acc. noise", "F");
  legend -> SetFillColor(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  int VarNum = 8;
  //hs_NNvar[VarNum] -> SetMaximum(20);
  hs_NNvar[VarNum] -> Draw();
  TString varname = GetNNVarAxisName(VarNum);
  hs_NNvar[VarNum] -> GetXaxis()->SetTitle(varname);
  hs_NNvar[VarNum] -> GetYaxis()->SetTitle("Number of Events");
  ((TGaxis*)hs_NNvar[VarNum]->GetYaxis())->SetMaxDigits(3);
  hs_NNvar[VarNum] -> GetYaxis()->SetTitleOffset(1.3);
  hs_NNvar[VarNum] -> GetXaxis()->SetTitleSize(0.05);

  h1_NNvar_data[VarNum] -> SetMarkerSize(1.5);
  hs_NNvar[VarNum] -> Draw();

  h1_NNvar_data[VarNum] -> Draw("SAME E P");
  legend -> Draw();
#endif


}



TString GetNNVarName(int vartype) {
  TString histtitle;
    switch (vartype) {
#if 0
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
#endif
      case 0:
        histtitle = "NHits";
        break;
      case 1:
        histtitle = "NResHits";
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
        histtitle = "OpeningAngleStdev";
        break;
      case 6:
        histtitle = "Beta1";
        break;
      case 7:
        histtitle = "Beta2";
        break;
      case 8:
        histtitle = "Beta3";
        break;
      case 9:
        histtitle = "Beta4";
        break;
      case 10:
        histtitle = "Beta5";
        break;
      case 11:
        histtitle = "BurstRatio";
        break;
      case 12:
        histtitle = "FitGoodness";
        break;
      case 13:
        histtitle = "DarkLikelihood";
        break;
    }
  return histtitle;
}

TString GetNNVarAxisName(int vartype) {
  TString varname;
  switch (vartype) {
#if 0
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
#endif
    case 0:
        varname = "NHits";
        break;
      case 1:
        varname = "NResHits";
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
        varname = "OpeningAngleStdev [deg]";
        break;
      case 6:
        varname = "Beta1";
        break;
      case 7:
        varname = "Beta2";
        break;
      case 8:
        varname = "Beta3";
        break;
      case 9:
        varname = "Beta4";
        break;
      case 10:
        varname = "Beta5";
        break;
      case 11:
        varname = "BurstRatio";
        break;
      case 12:
        varname = "FitGoodness";
        break;
      case 13:
        varname = "DarkLikelihood";
        break;
    }
  return varname;
}