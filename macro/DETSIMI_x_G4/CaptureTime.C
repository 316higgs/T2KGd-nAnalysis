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
//#define POTSCALE 0.17
#define POTSCALE 1

void CaptureTime(bool beammode) {

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
  TFile* fin_numu_detsim      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig_detsim    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar_detsim   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_detsim = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_detsim    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_detsim = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  TFile* fin_numu_g4      = new TFile("../../output/fhc/fhc.numu_x_numu.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuesig_g4    = new TFile("../../output/fhc/fhc.numu_x_nue.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_numubar_g4   = new TFile("../../output/fhc/fhc.numubar_x_numubar.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_g4 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_g4    = new TFile("../../output/fhc/fhc.nue_x_nue.skg4MC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_g4 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.skg4MC.bonsaikeras_ToF.root");

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


  //////  Reco Capture Time  //////
  TH1F* h1_RecoCapTime_AccNoise_numu_detsim = (TH1F*)fin_numu_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numu_detsim     = (TH1F*)fin_numu_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numu_detsim        = (TH1F*)fin_numu_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numu_detsim       = (TH1F*)fin_numu_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuesig_detsim = (TH1F*)fin_nuesig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuesig_detsim     = (TH1F*)fin_nuesig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuesig_detsim        = (TH1F*)fin_nuesig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuesig_detsim       = (TH1F*)fin_nuesig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_numubar_detsim = (TH1F*)fin_numubar_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numubar_detsim     = (TH1F*)fin_numubar_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numubar_detsim        = (TH1F*)fin_numubar_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numubar_detsim       = (TH1F*)fin_numubar_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarsig_detsim = (TH1F*)fin_nuebarsig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarsig_detsim     = (TH1F*)fin_nuebarsig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarsig_detsim        = (TH1F*)fin_nuebarsig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarsig_detsim       = (TH1F*)fin_nuebarsig_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebkg_detsim = (TH1F*)fin_nuebkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebkg_detsim     = (TH1F*)fin_nuebkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebkg_detsim        = (TH1F*)fin_nuebkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebkg_detsim       = (TH1F*)fin_nuebkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarbkg_detsim = (TH1F*)fin_nuebarbkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarbkg_detsim     = (TH1F*)fin_nuebarbkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarbkg_detsim        = (TH1F*)fin_nuebarbkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarbkg_detsim       = (TH1F*)fin_nuebarbkg_detsim->Get("NTagAnalysis/h1_RecoNCapTime_type3");


  TH1F* h1_RecoCapTime_AccNoise_numu_g4 = (TH1F*)fin_numu_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numu_g4     = (TH1F*)fin_numu_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numu_g4        = (TH1F*)fin_numu_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numu_g4       = (TH1F*)fin_numu_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuesig_g4 = (TH1F*)fin_nuesig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuesig_g4     = (TH1F*)fin_nuesig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuesig_g4        = (TH1F*)fin_nuesig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuesig_g4       = (TH1F*)fin_nuesig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_numubar_g4 = (TH1F*)fin_numubar_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numubar_g4     = (TH1F*)fin_numubar_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numubar_g4        = (TH1F*)fin_numubar_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numubar_g4       = (TH1F*)fin_numubar_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarsig_g4 = (TH1F*)fin_nuebarsig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarsig_g4     = (TH1F*)fin_nuebarsig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarsig_g4        = (TH1F*)fin_nuebarsig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarsig_g4       = (TH1F*)fin_nuebarsig_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebkg_g4 = (TH1F*)fin_nuebkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebkg_g4     = (TH1F*)fin_nuebkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebkg_g4        = (TH1F*)fin_nuebkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebkg_g4       = (TH1F*)fin_nuebkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarbkg_g4 = (TH1F*)fin_nuebarbkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarbkg_g4     = (TH1F*)fin_nuebarbkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarbkg_g4        = (TH1F*)fin_nuebarbkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarbkg_g4       = (TH1F*)fin_nuebarbkg_g4->Get("NTagAnalysis/h1_RecoNCapTime_type3");



  /////  Merged capture time  //////
  TH1F* h1_RecoCapTime_detsim = new TH1F("h1_RecoCapTime_detsim", "", 107, 0, 535);
  h1_RecoCapTime_detsim -> SetLineColor(kViolet-7);
  h1_RecoCapTime_detsim -> SetLineWidth(2);
  h1_RecoCapTime_detsim -> SetStats(0);
  h1_RecoCapTime_detsim -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoCapTime_detsim -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_RecoCapTime_g4 = new TH1F("h1_RecoCapTime_g4", "", 107, 0, 535);
  h1_RecoCapTime_g4 -> SetLineColor(kAzure-9);
  h1_RecoCapTime_g4 -> SetLineWidth(2);
  h1_RecoCapTime_g4 -> SetStats(0);
  h1_RecoCapTime_g4 -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoCapTime_g4 -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_numu_detsim);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_nuesig_detsim);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_numubar_detsim);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_nuebarsig_detsim);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_nuebkg_detsim);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_AccNoise_nuebarbkg_detsim);

  /*h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_numu_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_nuesig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_numubar_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_nuebarsig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_nuebkg_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_dcye_nuebarbkg_g4);

  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_numu_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_nuesig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_numubar_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_nuebarsig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_nuebkg_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_H_nuebarbkg_g4);

  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_numu_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_nuesig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_numubar_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_nuebarsig_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_nuebkg_g4);
  h1_RecoCapTime_detsim -> Add(h1_RecoCapTime_Gd_nuebarbkg_g4);*/


  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_numu_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_nuesig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_numubar_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_nuebarsig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_nuebkg_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_AccNoise_nuebarbkg_g4);

  /*h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_numu_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_nuesig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_numubar_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_nuebarsig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_nuebkg_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_dcye_nuebarbkg_g4);

  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_numu_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_nuesig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_numubar_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_nuebarsig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_nuebkg_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_H_nuebarbkg_g4);

  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_numu_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_nuesig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_numubar_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_nuebarsig_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_nuebkg_g4);
  h1_RecoCapTime_g4 -> Add(h1_RecoCapTime_Gd_nuebarbkg_g4);*/
#endif

  TF1* f1_CapTime_detsim = new TF1("f1_CapTime_deetsim", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 10, 535);
  //f1_CapTime -> SetParameter(0, 10);
  //f1_CapTime -> SetParameter(1, 10);
  //f1_CapTime -> SetParameter(2, 120);
  //f1_CapTime -> SetParameter(3, 10);
  f1_CapTime_detsim -> SetParameter(0, 100);    // for LL option (if normalized, LL should be used)
  f1_CapTime_detsim -> SetParameter(1, 50);
  f1_CapTime_detsim -> SetParameter(2, 120);
  f1_CapTime_detsim -> SetParameter(3, 10);
  f1_CapTime_detsim -> SetLineColor(kViolet-7);
  f1_CapTime_detsim -> SetLineWidth(2);
  f1_CapTime_detsim -> SetNpx(10000);

  TF1* f1_CapTime_g4 = new TF1("f1_CapTime_g4", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 10, 535);
  //f1_CapTime -> SetParameter(0, 10);
  //f1_CapTime -> SetParameter(1, 10);
  //f1_CapTime -> SetParameter(2, 120);
  //f1_CapTime -> SetParameter(3, 10);
  f1_CapTime_g4 -> SetParameter(0, 100);    // for LL option (if normalized, LL should be used)
  f1_CapTime_g4 -> SetParameter(1, 50);
  f1_CapTime_g4 -> SetParameter(2, 120);
  f1_CapTime_g4 -> SetParameter(3, 10);
  f1_CapTime_g4 -> SetLineColor(kAzure-9);
  f1_CapTime_g4 -> SetLineWidth(2);
  f1_CapTime_g4 -> SetNpx(10000);


  gROOT -> SetStyle("Plain");
  gStyle->SetOptFit(1111);
  /////////// Reco Capture Time //////////
#if 1
  h1_RecoCapTime_g4 -> Fit(f1_CapTime_g4, "rLL");
  h1_RecoCapTime_detsim -> Fit(f1_CapTime_detsim, "rLL");

  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 600);
  c1 -> SetGrid();
  h1_RecoCapTime_g4 -> SetMaximum(2000);
  h1_RecoCapTime_g4 -> Draw("");
  h1_RecoCapTime_g4 ->GetXaxis()->SetTitle("Reconstructed Capture Time [#musec]");
  h1_RecoCapTime_g4 ->GetXaxis()->SetTitleSize(0.045);
  h1_RecoCapTime_g4 ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  h1_RecoCapTime_g4 ->GetYaxis()->SetTitleSize(0.045);
  h1_RecoCapTime_g4 -> Draw("SAME");
  h1_RecoCapTime_detsim -> Draw("SAME");
  //f1_CapTime -> Draw("SAME");
  c1->RedrawAxis();

  Double_t CapTime_detsim = f1_CapTime_detsim->GetParameter(2);
  Double_t CapTimeErr_detsim = f1_CapTime_detsim->GetParError(2);

  Double_t CapTime_g4 = f1_CapTime_g4->GetParameter(2);
  Double_t CapTimeErr_g4 = f1_CapTime_g4->GetParError(2);

  TLegend* legend1 = new TLegend(0.37, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.45]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_RecoCapTime_detsim, "SKDETSIM-based MC", "L");
  legend1 -> AddEntry(h1_RecoCapTime_g4, "SKG4-based MC", "L");
  //legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time(SKDETSIM) = %.1f #pm %.1f #musec}", CapTime_detsim, CapTimeErr_detsiim),"");
  //legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time(SKG4) = %.1f #pm %.1f #musec}", CapTime_g4, CapTimeErr_g4),"");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.23]{Capture time(SKDETSIM) = %.1f #musec}", CapTime_detsim),"");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.27]{Capture time(SKG4) = %.1f #musec}", CapTime_g4),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


}
