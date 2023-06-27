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
  Double_t GenN_nue_x_nue         = 63379;
  Double_t GenN_nuebar_x_nuebar   = 63463;
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
  Double_t AllTruedcye_numu      = 6507.34;
  Double_t AllTruedcye_nuesig    = 0.447566;
  Double_t AllTruedcye_numubar   = 13762.2;
  Double_t AllTruedcye_nuebarsig = 243;
  Double_t AllTruedcye_nuebkg    = 259.886;

  //////  fiTQun sub-events in the box (reco. decay-e)  //////
  Double_t BoxfQdcye_numu      = 6146.16;
  Double_t BoxfQdcye_nuesig    = 0.447566;
  Double_t BoxfQdcye_numubar   = 11855.1;
  Double_t BoxfQdcye_nuebarsig = 245;
  Double_t BoxfQdcye_nuebkg    = 256.886;

  //////  True-mateched sub-events in the box  //////
  Double_t MatchedfQdcye_numu      = 5848.38;
  Double_t MatchedfQdcye_nuesig    = 0.447566;
  Double_t MatchedfQdcye_numubar   = 11791;
  Double_t MatchedfQdcye_nuebarsig = 238;
  Double_t MatchedfQdcye_nuebkg    = 249.886;

  
  Double_t mergeAllTruedcye = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*AllTruedcye_numu
                            + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*AllTruedcye_nuesig
                            + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*AllTruedcye_numubar
                            + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*AllTruedcye_nuebarsig
                            + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*AllTruedcye_nuebkg;

  Double_t mergeBoxfQdcye = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*BoxfQdcye_numu
                          + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*BoxfQdcye_nuesig
                          + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*BoxfQdcye_numubar
                          + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*BoxfQdcye_nuebarsig
                          + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*BoxfQdcye_nuebkg;

  Double_t mergeMatchedfQdcye = (ExpN_numu_x_numu)/(GenN_numu_x_numu)*MatchedfQdcye_numu
                              + (ExpN_numu_x_nue)/(GenN_numu_x_nue)*MatchedfQdcye_nuesig
                              + (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar)*MatchedfQdcye_numubar
                              + (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar)*MatchedfQdcye_nuebarsig
                              + (ExpN_nue_x_nue)/(GenN_nue_x_nue)*MatchedfQdcye_nuebkg;

  std::cout << "All True Decay-e                 : " << mergeAllTruedcye << std::endl;
  std::cout << "fiTQun Decay-e in the Box        : " << mergeBoxfQdcye << std::endl;
  std::cout << "Matched fiTQun Decay-e in the Box: " << mergeMatchedfQdcye << std::endl;
  std::cout << "Purity    : " << (mergeMatchedfQdcye/mergeBoxfQdcye)*100. << " %" << std::endl;
  std::cout << "Efficiency: " << (mergeMatchedfQdcye/mergeAllTruedcye)*100. << " %" << std::endl;

}


