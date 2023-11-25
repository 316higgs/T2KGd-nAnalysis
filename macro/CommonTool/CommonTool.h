
#define SAMPLES 6
#define INTERACTIONTYPE 4
#define NTAGLABEL 4

/////////  File Name  ///////////
//  input nominal MC
TString OutDir   = "../../output/fhc/";
TString BeamMode = "fhc";
TString OscMode[SAMPLES] = {"numu_x_numu", "numu_x_nue", "numubar_x_numubar", 
                            "numubar_x_nuebar", "nue_x_nue", "nuebar_x_nuebar"};
TString Prefix = "newGdMC.bonsaikeras_ToF";
TFile* fin_MC[SAMPLES];

//  flux file
TString fflux = "/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root";

//  data file
TString fdata = "../../output/fhc/run11.bonsai_keras_prompt_vertex.root";

/////////  MC generated events  //////////
Double_t GenN_numu_x_numu       = 63622;
Double_t GenN_numu_x_nue        = 63538;
Double_t GenN_numubar_x_numubar = 63444;
Double_t GenN_numubar_x_nuebar  = 63460;
Double_t GenN_nue_x_nue         = 63423;
Double_t GenN_nuebar_x_nuebar   = 63652;


////////  Histogram color  ////////
int NeutronColor = kSpring+4;
int DecayEColor  = kOrange-7;
int DataColor    = kBlack;


////////  Functions  ////////
float ApplyNorm(float genNum, int OscCh) {
  TFile* fin_skrate = new TFile(fflux);
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

  float NormFctr = 0.;
  switch (OscCh) {
    case 0:
      NormFctr = (ExpN_numu_x_numu)/(GenN_numu_x_numu);
      break;
    case 1:
      NormFctr = (ExpN_numu_x_nue)/(GenN_numu_x_nue);
      break;
    case 2:
      NormFctr = (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar);
      break;
    case 3:
      NormFctr = (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar);
      break;
    case 4:
      NormFctr = (ExpN_nue_x_nue)/(GenN_nue_x_nue);
      break;
    case 5:
      NormFctr = (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar);
      break;
  }
  return NormFctr*genNum;
}

void ApplyNorm(TH1F* h1, int OscCh) {
  TFile* fin_skrate = new TFile(fflux);
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

  float NormFctr = 0.;
  switch (OscCh) {
    case 0:
      NormFctr = (ExpN_numu_x_numu)/(GenN_numu_x_numu);
      break;
    case 1:
      NormFctr = (ExpN_numu_x_nue)/(GenN_numu_x_nue);
      break;
    case 2:
      NormFctr = (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar);
      break;
    case 3:
      NormFctr = (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar);
      break;
    case 4:
      NormFctr = (ExpN_nue_x_nue)/(GenN_nue_x_nue);
      break;
    case 5:
      NormFctr = (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar);
      break;
  }
  h1 -> Scale(NormFctr);
}

void ApplyNormforSamples(float* genNumList) {
  float Total = 0.;
  for (int isample=0; isample<SAMPLES; isample++) { 
    Total += ApplyNorm(genNumList[isample], isample);
    std::cout << "SAMPLE[ " << isample << " ] " << ApplyNorm(genNumList[isample], isample) << std::endl;
  }
  std::cout << "Total: " << Total << std::endl;
}


void SetMCHistColor_NuInt(int isample, int imode, TH1F* h1) {
  //  numu -> numu
  if (isample==0) {
    switch(imode) {
      case 0:
        h1 -> SetLineColor(kAzure-1);
        h1 -> SetFillColor(kAzure-1);
        break;
      case 1:
        h1 -> SetLineColor(kAzure-5);
        h1 -> SetFillColor(kAzure-5);
        break;
      case 2:
        h1 -> SetLineColor(kCyan-8);
        h1 -> SetFillColor(kCyan-8);
        break;
      case 3:
        h1 -> SetLineColor(kSpring-9);
        h1 -> SetFillColor(kSpring-9);
        break;
    }
  }
  //  numubar -> numubar
  else if (isample==2) {
    switch(imode) {
      case 0:
        h1 -> SetLineColor(kOrange+7);
        h1 -> SetFillColor(kOrange+7);
        break;
      case 1:
        h1 -> SetLineColor(kOrange+6);
        h1 -> SetFillColor(kOrange+6);
        break;
      case 2:
        h1 -> SetLineColor(kOrange+0);
        h1 -> SetFillColor(kOrange+0);
        break;
      case 3:
        h1 -> SetLineColor(kSpring-9);
        h1 -> SetFillColor(kSpring-9);
        break;
    }
  }
  //  nue
  else {
    if (imode==3) {
      h1 -> SetLineColor(kSpring-9);
      h1 -> SetFillColor(kSpring-9);
    }
    else {
      h1 -> SetLineColor(kViolet-1);
      h1 -> SetFillColor(kViolet-1);
    }
  }
}


void SetMCHistColor_Label(int ilabel, TH1F* h1) {
  switch(ilabel) {
    case 0:
      h1 -> SetLineColor(kGray+2);
      h1 -> SetFillColor(kGray+2);
      break;
    case 1:
      h1 -> SetLineColor(kYellow-3);
      h1 -> SetFillColor(kYellow-3);
      break;
    case 2:
      h1 -> SetLineColor(kAzure-4);
      h1 -> SetFillColor(kAzure-4);
      break;
    case 3:
      h1 -> SetLineColor(kTeal-5);
      h1 -> SetFillColor(kTeal-5);
      break;
  }
}


