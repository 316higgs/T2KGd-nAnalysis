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
#define POTSCALE 0.17


void mergeDcyePerform(bool beammode) {

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
  Double_t GenN_numubar_x_nuebar  = 63463;
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


  //////  All true decay-e  //////
  Double_t Q1_numu      = 6088.48;
  Double_t Q1_nuesig    = 183.448;
  Double_t Q1_numubar   = 11771.3;
  Double_t Q1_nuebarsig = 241;
  Double_t Q1_nuebkg    = 249.886;
  Double_t Q1_nuebarbkg = 323;

  //////  fiTQun sub-events in the box (reco. decay-e)  //////
  Double_t Q2_numu      = 59.6321;
  Double_t Q2_nuesig    = 3;
  Double_t Q2_numubar   = 83.7877;
  Double_t Q2_nuebarsig = 6;
  Double_t Q2_nuebkg    = 7;
  Double_t Q2_nuebarbkg = 4;

  //////  True-mateched sub-events in the box  //////
  Double_t Q3_numu      = 162.892;
  Double_t Q3_nuesig    = 0;
  Double_t Q3_numubar   = 57.5076;
  Double_t Q3_nuebarsig = 0;
  Double_t Q3_nuebkg    = 1;
  Double_t Q3_nuebarbkg = 0;

  
  Double_t mergeQ1 = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*Q1_numu
                            + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*Q1_nuesig
                            + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*Q1_numubar
                            + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*Q1_nuebarsig
                            + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*Q1_nuebkg
                            + (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar)*Q1_nuebarbkg;

  Double_t mergeQ2 = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*Q2_numu
                          + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*Q2_nuesig
                          + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*Q2_numubar
                          + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*Q2_nuebarsig
                          + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*Q2_nuebkg
                          + (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar)*Q2_nuebarbkg;

  Double_t mergeQ3 = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*Q3_numu
                              + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*Q3_nuesig
                              + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*Q3_numubar
                              + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*Q3_nuebarsig
                              + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*Q3_nuebkg
                              + (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar)*Q3_nuebarbkg;

  std::cout << "Q1: " << mergeQ1 << std::endl;
  std::cout << "Q2: " << mergeQ2 << std::endl;
  std::cout << "Q3: " << mergeQ3 << std::endl;
  std::cout << "Purity    : " << (mergeQ1/(mergeQ1+mergeQ2))*100. << " %" << std::endl;
  std::cout << "Efficiency: " << (mergeQ1/(mergeQ1+mergeQ3))*100. << " %" << std::endl;

}


