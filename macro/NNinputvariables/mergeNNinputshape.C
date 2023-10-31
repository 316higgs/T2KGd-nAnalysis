
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run11 FHC

TString GetNNVarName(int vartype);
TString GetNNVarAxisName(int vartype);

void mergeNNinputshape(bool beammode) {

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

#if 1
  // Pre
  bool NTagapply = false;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.preNN.newGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.preNN.newGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC.root");
#endif

#if 0
  // Post
  bool NTagapply = true;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.postNN.newGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.postNN.newGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC.root");
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


  TH1F* h1_NNvar_Gd_numu[14];
  TH1F* h1_NNvar_H_numu[14];
  TH1F* h1_NNvar_AccNoise_numu[14];
  TH1F* h1_NNvar_Decaye_numu[14];

  TH1F* h1_NNvar_Gd_nuesig[14];
  TH1F* h1_NNvar_H_nuesig[14];
  TH1F* h1_NNvar_AccNoise_nuesig[14];
  TH1F* h1_NNvar_Decaye_nuesig[14];

  TH1F* h1_NNvar_Gd_numubar[14];
  TH1F* h1_NNvar_H_numubar[14];
  TH1F* h1_NNvar_AccNoise_numubar[14];
  TH1F* h1_NNvar_Decaye_numubar[14];

  TH1F* h1_NNvar_Gd_nuebarsig[14];
  TH1F* h1_NNvar_H_nuebarsig[14];
  TH1F* h1_NNvar_AccNoise_nuebarsig[14];
  TH1F* h1_NNvar_Decaye_nuebarsig[14];

  TH1F* h1_NNvar_Gd_nuebkg[14];
  TH1F* h1_NNvar_H_nuebkg[14];
  TH1F* h1_NNvar_AccNoise_nuebkg[14];
  TH1F* h1_NNvar_Decaye_nuebkg[14];

  TH1F* h1_NNvar_Gd_nuebarbkg[14];
  TH1F* h1_NNvar_H_nuebarbkg[14];
  TH1F* h1_NNvar_AccNoise_nuebarbkg[14];
  TH1F* h1_NNvar_Decaye_nuebarbkg[14];

  TH1F* h1_NNvar_Gd[14];
  TH1F* h1_NNvar_H[14];
  TH1F* h1_NNvar_Decaye[14];
  TH1F* h1_NNvar_AccNoise[14];
  /*float binnum[14] = {50, 40, 50,   50,   50,  40, 40,   40,  40,  40,   40,   40};
  float xmin[14]   = {0,   0,  0, -150,    0,  20, 10, -150,  20,   0, -0.2, -0.2};
  float xmax[14]   = {50, 80,  5, 1600, 5000,  80, 30,  150,  90,  60,  0.8,  0.4};*/
  float binnum[14] = {50, 70, 50,   50,   50,  40,   40,   40,    40,    40,   40, 20, 50, 20};
  float xmin[14]   = {0,   0,  0, -150,    0,  10, -0.2, -0.2,  -0.2,  -0.2, -0.2,  0,  0,  0};
  float xmax[14]   = {50, 70, 10, 1600, 5000,  30,  0.8,  0.8,   0.4,   0.4,  0.4,  1,  1,  1};

  for (int i=0; i<14; i++) {
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

#if 0
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
#endif

    TString hsname = GetNNVarName(i);
    std::cout << "[### Var" << i << " ###] " << hsname << std::endl;
    h1_NNvar_Gd[i]       = new TH1F(TString::Format("h1_NNvar_Gd_var%d", i), hsname, binnum[i], xmin[i], xmax[i]);
    h1_NNvar_H[i]        = new TH1F(TString::Format("h1_NNvar_H_var%d", i), hsname, binnum[i], xmin[i], xmax[i]);
    h1_NNvar_Decaye[i]   = new TH1F(TString::Format("h1_NNvarDecayed_var%d",   i), hsname, binnum[i], xmin[i], xmax[i]);
    h1_NNvar_AccNoise[i] = new TH1F(TString::Format("h1_NNvar_Gd_AccNoiser%d", i), hsname, binnum[i], xmin[i], xmax[i]);

    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_numu[i]);
    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_nuesig[i]);
    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_numubar[i]);
    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_nuebarsig[i]);
    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_nuebkg[i]);
    h1_NNvar_Gd[i] -> Add(h1_NNvar_Gd_nuebarbkg[i]);
    h1_NNvar_Gd[i] -> SetLineColor(kTeal-5);
    h1_NNvar_Gd[i] -> SetLineWidth(2);
    h1_NNvar_Gd[i] -> SetStats(0);

    h1_NNvar_H[i] -> Add(h1_NNvar_H_numu[i]);
    h1_NNvar_H[i] -> Add(h1_NNvar_H_nuesig[i]);
    h1_NNvar_H[i] -> Add(h1_NNvar_H_numubar[i]);
    h1_NNvar_H[i] -> Add(h1_NNvar_Gd_nuebarsig[i]);
    h1_NNvar_H[i] -> Add(h1_NNvar_Gd_nuebkg[i]);
    h1_NNvar_H[i] -> Add(h1_NNvar_Gd_nuebarbkg[i]);
    h1_NNvar_H[i] -> SetLineColor(kAzure-4);
    h1_NNvar_H[i] -> SetLineWidth(2);
    h1_NNvar_H[i] -> SetStats(0);

    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Decaye_numu[i]);
    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Decaye_nuesig[i]);
    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Decaye_numubar[i]);
    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Gd_nuebarsig[i]);
    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Gd_nuebkg[i]);
    h1_NNvar_Decaye[i] -> Add(h1_NNvar_Gd_nuebarbkg[i]);
    h1_NNvar_Decaye[i] -> SetLineColor(kYellow-3);
    h1_NNvar_Decaye[i] -> SetLineWidth(2);
    h1_NNvar_Decaye[i] -> SetStats(0);

    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_AccNoise_numu[i]);
    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_AccNoise_nuesig[i]);
    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_AccNoise_numubar[i]);
    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_Gd_nuebarsig[i]);
    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_Gd_nuebkg[i]);
    h1_NNvar_AccNoise[i] -> Add(h1_NNvar_Gd_nuebarbkg[i]);
    h1_NNvar_AccNoise[i] -> SetLineColor(kGray+2);
    h1_NNvar_AccNoise[i] -> SetLineWidth(2);
    h1_NNvar_AccNoise[i] -> SetStats(0);

    Double_t tot_Gd       = h1_NNvar_Gd[i]->Integral();
    Double_t tot_H        = h1_NNvar_H[i]->Integral();
    Double_t tot_Decaye   = h1_NNvar_Decaye[i]->Integral();
    Double_t tot_AccNoise = h1_NNvar_AccNoise[i]->Integral();

    h1_NNvar_Gd[i]       -> Scale(1./tot_Gd);
    h1_NNvar_H[i]        -> Scale(1./tot_H);
    h1_NNvar_Decaye[i]   -> Scale(1./tot_Decaye);
    h1_NNvar_AccNoise[i] -> Scale(1./tot_AccNoise);
  }

  
  // for sanity check of NN input variable plots
  h1_AllNHits = (TH1F*)fin_numu->Get("NNInputVariables/h1_AllNHits");
  h1_AllNHits -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  std::cout << "numu_x_numu #tag-n = " << h1_AllNHits->Integral() << std::endl;

  TLegend* legend = new TLegend(0.2, 0.1, 0.89, 0.89);
  legend -> SetTextSize(0.08);
  if (!NTagapply) legend -> AddEntry((TObject*)0,"#kern[-0.35]{Pre-NN (Run11)}","");
  else legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN (Run11)}","");
  legend -> AddEntry(h1_NNvar_Gd[0], "Gd-n signal", "L");
  legend -> AddEntry(h1_NNvar_H[0], "H-n signal", "L");
  legend -> AddEntry(h1_NNvar_Decaye[0], "Decay-e", "L");
  legend -> AddEntry(h1_NNvar_AccNoise[0], "Acc. noise", "L");
  legend -> SetFillColor(0);

  gROOT -> SetStyle("Plain");
  //TCanvas* c1 = new TCanvas("c1", "c1", 1400, 1000);
  TCanvas* c1 = new TCanvas("c1", "c1", 800, 1400);
  //c1 -> Divide(4,3);
  c1 -> Divide(3,5);
  for (int i=0; i<14; i++) {
    c1 -> cd(i+1) -> SetGrid();
    //gPad->SetLogy();
    TString varname = GetNNVarAxisName(i);
    h1_NNvar_Gd[i]       -> GetXaxis()->SetTitle(varname);
    h1_NNvar_Gd[i]       -> GetYaxis()->SetTitle("Area Normalized");
    h1_NNvar_H[i]        -> GetXaxis()->SetTitle(varname);
    h1_NNvar_H[i]        -> GetYaxis()->SetTitle("Area Normalized");
    h1_NNvar_Decaye[i]   -> GetXaxis()->SetTitle(varname);
    h1_NNvar_Decaye[i]   -> GetYaxis()->SetTitle("Area Normalized");
    h1_NNvar_AccNoise[i] -> GetXaxis()->SetTitle(varname);
    h1_NNvar_AccNoise[i] -> GetYaxis()->SetTitle("Area Normalized");
    h1_NNvar_AccNoise[i] -> SetTitleOffset(1.2, "Y");
    h1_NNvar_Gd[i]       -> SetTitleOffset(1.2, "Y");
    h1_NNvar_H[i]        -> SetTitleOffset(1.2, "Y");
    h1_NNvar_Decaye[i]   -> SetTitleOffset(1.2, "Y");

    h1_NNvar_AccNoise[i] -> GetXaxis()->SetTitleSize(0.05);
    h1_NNvar_Gd[i]       -> GetXaxis()->SetTitleSize(0.05);
    h1_NNvar_H[i]        -> GetXaxis()->SetTitleSize(0.05);
    h1_NNvar_Decaye[i]   -> GetXaxis()->SetTitleSize(0.05);

    ((TGaxis*)h1_NNvar_AccNoise[i] ->GetYaxis())->SetMaxDigits(3);
    ((TGaxis*)h1_NNvar_Gd[i]       ->GetYaxis())->SetMaxDigits(3);
    ((TGaxis*)h1_NNvar_H[i]        ->GetYaxis())->SetMaxDigits(3);
    ((TGaxis*)h1_NNvar_Decaye[i]   ->GetYaxis())->SetMaxDigits(3);

#if !NTagapply
    if (i==0 || i==1 || i==3 || i==4) {
      h1_NNvar_AccNoise[i] -> Draw();
      h1_NNvar_H[i]        -> Draw("SAME");
      h1_NNvar_Gd[i]       -> Draw("SAME");
      h1_NNvar_Decaye[i]   -> Draw("SAME");
    }
    else if ((i>=5 && i<=7) || i==9 || i==10 || i==11 || i==12 ) {
      h1_NNvar_Gd[i]       -> Draw();
      h1_NNvar_AccNoise[i] -> Draw("SAME");
      h1_NNvar_H[i]        -> Draw("SAME");
      h1_NNvar_Decaye[i]   -> Draw("SAME");
    }
    else if (i==2 || i==8 || i==13) {
      h1_NNvar_Decaye[i]   -> Draw();
      h1_NNvar_Gd[i]       -> Draw("SAME");
      h1_NNvar_H[i]        -> Draw("SAME");
      h1_NNvar_AccNoise[i] -> Draw("SAME");
    }
#endif
#if NTagapply
    /*if (i==0 || i==1 || i==3 || i==4) {
      h1_NNvar_H[i]        -> Draw("SAME");
      h1_NNvar_AccNoise[i] -> Draw("SAME");
      h1_NNvar_Gd[i]       -> Draw("SAME");
      h1_NNvar_Decaye[i]   -> Draw("SAME");
    }
    else {
      h1_NNvar_Decaye[i]   -> Draw();
      h1_NNvar_Gd[i]       -> Draw("SAME");
      h1_NNvar_H[i]        -> Draw("SAME");
      h1_NNvar_AccNoise[i] -> Draw("SAME");
    }*/

    h1_NNvar_Decaye[i]   -> Draw();
    h1_NNvar_H[i]        -> Draw("SAME");
    h1_NNvar_AccNoise[i] -> Draw("SAME");
    h1_NNvar_Gd[i]       -> Draw("SAME");
#endif
    //if (i==11) legend -> Draw();
  }
  c1 -> cd(15) -> SetGrid();
  legend -> Draw();

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
