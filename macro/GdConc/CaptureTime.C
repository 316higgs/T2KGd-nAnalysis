#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"
#include <iomanip>

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


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

#if 0
  float Gdconc = 0.0263;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
#endif

#if 1
  float Gdconc = 0.0251;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");
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

  
  ////  True capture time  ////
  TH1F* h1_TrueCapTime_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNCapTime");

  //////  Reco Capture Time  //////
  TH1F* h1_RecoCapTime_AccNoise_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numu     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numu        = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numu       = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuesig     = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuesig        = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuesig       = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_numubar     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_numubar        = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_numubar       = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarsig        = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebkg     = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebkg        = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebkg       = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_RecoNCapTime_type3");

  TH1F* h1_RecoCapTime_AccNoise_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  TH1F* h1_RecoCapTime_dcye_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  TH1F* h1_RecoCapTime_H_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  TH1F* h1_RecoCapTime_Gd_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_RecoNCapTime_type3");



  /////  Merged capture time  //////
  TH1F* h1_TrueCapTime = new TH1F("h1_TrueCapTime", "", 107, 0, 535);
  h1_TrueCapTime -> SetLineColor(kViolet+3);
  h1_TrueCapTime -> SetLineWidth(2);
  h1_TrueCapTime -> SetStats(0);
  h1_TrueCapTime -> SetXTitle("Truth Capture Time [#musec]");
  h1_TrueCapTime -> SetYTitle("Number of Captured Neutrons");
  h1_TrueCapTime -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueCapTime -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_RecoCapTime = new TH1F("h1_RecoCapTime", "", 107, 0, 535);
  h1_RecoCapTime -> SetLineColor(kSpring-7);
  h1_RecoCapTime -> SetLineWidth(2);
  h1_RecoCapTime -> SetStats(0);
  h1_RecoCapTime -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoCapTime -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_TrueCapTime -> Add(h1_TrueCapTime_nuebarbkg);
  h1_TrueCapTime -> Add(h1_TrueCapTime_nuebkg);
  h1_TrueCapTime -> Add(h1_TrueCapTime_nuebarsig);
  h1_TrueCapTime -> Add(h1_TrueCapTime_numubar);
  h1_TrueCapTime -> Add(h1_TrueCapTime_nuesig);
  h1_TrueCapTime -> Add(h1_TrueCapTime_numu);


  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_numu);
  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuesig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_numubar);
  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebarsig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebkg);
  h1_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebarbkg);

  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_numu);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuesig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_numubar);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebarsig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebkg);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebarbkg);

  h1_RecoCapTime -> Add(h1_RecoCapTime_H_numu);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_nuesig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_numubar);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_nuebarsig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_nuebkg);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_nuebarbkg);

  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_numu);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuesig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_numubar);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebarsig);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebkg);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebarbkg);
#endif


  TString foutname = TString::Format("output/CaptureTime.Gdconc%f.root", Gdconc);
  TFile* fout = new TFile(foutname, "RECREATE");
  fout -> cd();
  h1_TrueCapTime -> Write();
  h1_RecoCapTime -> Write();

}