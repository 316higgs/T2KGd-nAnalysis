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
//#define POTSCALE 1

#define NNAPPLY 1  // 0 for pre-NN, 1 for post-NN

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

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


  //////  True Capture Time  //////
  TH1F* h1_TrueCapTime_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNCapTime");
  TH1F* h1_TrueCapTime_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNCapTime");


  //////  Reco Capture Time  //////
  TString DirName   = "NTagAnalysis/";
  TString HistName  = "h1_RecoNCapTime_";
  TString TypeNoise = "type0";
  TString TypeDcyE  = "type1";
  TString TypeHn    = "type2";
  TString TypeGdn   = "type3";
  TString NNmode    = TString::Format("_NN%d", NNAPPLY);
  TH1F* h1_RecoCapTime_AccNoise_numu = (TH1F*)fin_numu->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_numu     = (TH1F*)fin_numu->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_numu        = (TH1F*)fin_numu->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_numu       = (TH1F*)fin_numu->Get(DirName+HistName+TypeGdn+NNmode);

  TH1F* h1_RecoCapTime_AccNoise_nuesig = (TH1F*)fin_nuesig->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_nuesig     = (TH1F*)fin_nuesig->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_nuesig        = (TH1F*)fin_nuesig->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_nuesig       = (TH1F*)fin_nuesig->Get(DirName+HistName+TypeGdn+NNmode);

  TH1F* h1_RecoCapTime_AccNoise_numubar = (TH1F*)fin_numubar->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_numubar     = (TH1F*)fin_numubar->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_numubar        = (TH1F*)fin_numubar->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_numubar       = (TH1F*)fin_numubar->Get(DirName+HistName+TypeGdn+NNmode);

  TH1F* h1_RecoCapTime_AccNoise_nuebarsig = (TH1F*)fin_nuebarsig->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_nuebarsig     = (TH1F*)fin_nuebarsig->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_nuebarsig        = (TH1F*)fin_nuebarsig->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_nuebarsig       = (TH1F*)fin_nuebarsig->Get(DirName+HistName+TypeGdn+NNmode);

  TH1F* h1_RecoCapTime_AccNoise_nuebkg = (TH1F*)fin_nuebkg->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_nuebkg     = (TH1F*)fin_nuebkg->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_nuebkg        = (TH1F*)fin_nuebkg->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_nuebkg       = (TH1F*)fin_nuebkg->Get(DirName+HistName+TypeGdn+NNmode);

  TH1F* h1_RecoCapTime_AccNoise_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(DirName+HistName+TypeNoise+NNmode);
  TH1F* h1_RecoCapTime_dcye_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get(DirName+HistName+TypeDcyE+NNmode);
  TH1F* h1_RecoCapTime_H_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get(DirName+HistName+TypeHn+NNmode);
  TH1F* h1_RecoCapTime_Gd_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get(DirName+HistName+TypeGdn+NNmode);

  h1_RecoCapTime_AccNoise_numu      -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuesig    -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_numubar   -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebarsig -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebkg    -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebarbkg -> SetFillColor(kGray+2);
  h1_RecoCapTime_AccNoise_numu      -> SetLineColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuesig    -> SetLineColor(kGray+2);
  h1_RecoCapTime_AccNoise_numubar   -> SetLineColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebarsig -> SetLineColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebkg    -> SetLineColor(kGray+2);
  h1_RecoCapTime_AccNoise_nuebarbkg -> SetLineColor(kGray+2);

  h1_RecoCapTime_H_numu      -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_nuesig    -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_numubar   -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_nuebarsig -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_nuebkg    -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_nuebarbkg -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_numu      -> SetLineColor(kAzure-4);
  h1_RecoCapTime_H_nuesig    -> SetLineColor(kAzure-4);
  h1_RecoCapTime_H_numubar   -> SetLineColor(kAzure-4);
  h1_RecoCapTime_H_nuebarsig -> SetLineColor(kAzure-4);
  h1_RecoCapTime_H_nuebkg    -> SetLineColor(kAzure-4);
  h1_RecoCapTime_H_nuebarbkg -> SetLineColor(kAzure-4);

  h1_RecoCapTime_Gd_numu      -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_nuesig    -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_numubar   -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebarsig -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebkg    -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebarbkg -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_numu      -> SetLineColor(kTeal-5);
  h1_RecoCapTime_Gd_nuesig    -> SetLineColor(kTeal-5);
  h1_RecoCapTime_Gd_numubar   -> SetLineColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebarsig -> SetLineColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebkg    -> SetLineColor(kTeal-5);
  h1_RecoCapTime_Gd_nuebarbkg -> SetLineColor(kTeal-5);

  h1_RecoCapTime_dcye_numu      -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_nuesig    -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_numubar   -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebarsig -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebkg    -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebarbkg -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_numu      -> SetLineColor(kYellow-3);
  h1_RecoCapTime_dcye_nuesig    -> SetLineColor(kYellow-3);
  h1_RecoCapTime_dcye_numubar   -> SetLineColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebarsig -> SetLineColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebkg    -> SetLineColor(kYellow-3);
  h1_RecoCapTime_dcye_nuebarbkg -> SetLineColor(kYellow-3);


  /////  Normalizations  //////
#if 1
  h1_TrueCapTime_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueCapTime_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueCapTime_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueCapTime_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueCapTime_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueCapTime_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_RecoCapTime_AccNoise_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_RecoCapTime_AccNoise_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_RecoCapTime_AccNoise_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_RecoCapTime_AccNoise_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_RecoCapTime_AccNoise_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_RecoCapTime_AccNoise_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_RecoCapTime_H_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_RecoCapTime_H_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_RecoCapTime_H_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_RecoCapTime_H_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_RecoCapTime_H_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_RecoCapTime_H_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_RecoCapTime_Gd_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_RecoCapTime_Gd_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_RecoCapTime_Gd_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_RecoCapTime_Gd_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_RecoCapTime_Gd_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_RecoCapTime_Gd_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_RecoCapTime_dcye_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_RecoCapTime_dcye_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_RecoCapTime_dcye_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_RecoCapTime_dcye_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_RecoCapTime_dcye_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_RecoCapTime_dcye_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  /////  Merged capture time  //////
  TH1F* h1_TrueCapTime = new TH1F("h1_TrueCapTime", "", 107, 0, 535);
  h1_TrueCapTime -> SetFillColor(kViolet-8);
  h1_TrueCapTime -> SetLineColor(kViolet+3);
  h1_TrueCapTime -> SetLineWidth(2);
  h1_TrueCapTime -> SetStats(0);
  h1_TrueCapTime -> SetXTitle("Truth Capture Time [#musec]");
  h1_TrueCapTime -> SetYTitle("Number of Captured Neutrons");
  h1_TrueCapTime -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueCapTime -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_RecoCapTime = new TH1F("h1_RecoCapTime", "", 50, 0, 535);
  //TH1F* h1_RecoCapTime = new TH1F("h1_RecoCapTime", "Reco Captrued Time; Reconstructed Capture Time [#mu sec]; Number of Events", 40, 0, 20);
  //h1_TrueCapTime -> SetFillColor(kViolet-8);
  h1_RecoCapTime -> SetLineColor(kSpring-7);
  h1_RecoCapTime -> SetLineWidth(2);
  h1_RecoCapTime -> SetStats(0);
  h1_RecoCapTime -> GetXaxis()->SetTitleSize(0.045);
  h1_RecoCapTime -> GetYaxis()->SetTitleSize(0.045);

  THStack* hs_RecoCapTime = new THStack("hs_RecoCapTime", "");

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

  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_numu);
  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuesig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_numubar);
  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebarsig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebkg);
  hs_RecoCapTime -> Add(h1_RecoCapTime_AccNoise_nuebarbkg);

  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_numu);
  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuesig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_numubar);
  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebarsig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebkg);
  hs_RecoCapTime -> Add(h1_RecoCapTime_dcye_nuebarbkg);

  hs_RecoCapTime -> Add(h1_RecoCapTime_H_numu);
  hs_RecoCapTime -> Add(h1_RecoCapTime_H_nuesig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_H_numubar);
  hs_RecoCapTime -> Add(h1_RecoCapTime_H_nuebarsig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_H_nuebkg);
  hs_RecoCapTime -> Add(h1_RecoCapTime_H_nuebarbkg);

  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_numu);
  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuesig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_numubar);
  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebarsig);
  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebkg);
  hs_RecoCapTime -> Add(h1_RecoCapTime_Gd_nuebarbkg);
#endif


  TF1* f1_CapTime = new TF1("f", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 10, 535);
  //f1_CapTime -> SetParameter(0, 10);
  //f1_CapTime -> SetParameter(1, 10);
  //f1_CapTime -> SetParameter(2, 120);
  //f1_CapTime -> SetParameter(3, 10);
  f1_CapTime -> SetParameter(0, 100);    // for LL option (if normalized, LL should be used)
  f1_CapTime -> SetParameter(1, 50);
  f1_CapTime -> SetParameter(2, 120);
  f1_CapTime -> SetParameter(3, 10);
  f1_CapTime -> SetLineColor(kPink-8);
  f1_CapTime -> SetLineWidth(3);
  f1_CapTime -> SetNpx(10000);


  // Data
  TString HistData = "h1_AllRecoNCapTime";
  TFile* fin_data     = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");
  TH1F* h1_RecoCapTime_data = (TH1F*)fin_data->Get(DirName+HistData+NNmode);
  h1_RecoCapTime_data -> SetMarkerStyle(20);
  h1_RecoCapTime_data -> SetMarkerSize(1.2);
  h1_RecoCapTime_data -> SetMarkerColor(kBlack);
  h1_RecoCapTime_data -> SetLineColor(kBlack);
  h1_RecoCapTime_data -> SetLineWidth(1.5);

  gStyle->SetOptFit(1111);
  gROOT -> SetStyle("Plain");
  /////////// True Capture Time //////////
#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 600);
  c1 -> SetGrid();
  h1_TrueCapTime -> Fit(f1_CapTime, "rLL");
  //h1_TrueCapTime -> Fit(f1_CapTime, "r");
  h1_TrueCapTime -> Draw("");
  f1_CapTime -> Draw("SAME");
  c1->RedrawAxis();

  Double_t CapTime = f1_CapTime->GetParameter(2);
  Double_t CapTimeErr = f1_CapTime->GetParError(2);

  TLegend* legend1 = new TLegend(0.45, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (T2K Run11)}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_TrueCapTime, "0.01% Gd MC", "F");
  legend1 -> AddEntry(f1_CapTime, "A*(1-e^{-B*t})*exp(-x/C)+D", "L");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time = %.1f #pm %.1f #musec}", CapTime, CapTimeErr),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


  /////////// Reco Capture Time //////////
#if 1
  //h1_RecoCapTime -> Fit(f1_CapTime, "rLL");

  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 600);
  c1 -> SetGrid();
  if (NNAPPLY==0) hs_RecoCapTime -> SetMaximum(150);
  else hs_RecoCapTime -> SetMaximum(25);
  hs_RecoCapTime -> Draw("");
  hs_RecoCapTime ->GetXaxis()->SetTitle("Reconstructed Capture Time [#musec]");
  hs_RecoCapTime ->GetXaxis()->SetTitleSize(0.045);
  hs_RecoCapTime ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  hs_RecoCapTime ->GetYaxis()->SetTitleSize(0.045);
  h1_RecoCapTime -> Draw("SAME");
  //f1_CapTime -> Draw("SAME");

  h1_RecoCapTime_data -> Draw("SAME E P");
  c1->RedrawAxis();

  Double_t CapTime = f1_CapTime->GetParameter(2);
  Double_t CapTimeErr = f1_CapTime->GetParError(2);


  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (T2K Run11)}","");
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FCFV applied (pre-NN)}","");
  if (NNAPPLY==0) legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FCFV applied (pre-NN)}","");
  else legend1 -> AddEntry((TObject*)0,"#kern[-0.34]{FCFV applied (post-NN)}","");
  legend1 -> AddEntry(h1_RecoCapTime_AccNoise_numu, "Acc. noise", "F");
  legend1 -> AddEntry(h1_RecoCapTime_dcye_numu, "Decay-e", "F");
  legend1 -> AddEntry(h1_RecoCapTime_H_numu, "H-n signal", "F");
  legend1 -> AddEntry(h1_RecoCapTime_Gd_numu, "Gd-n signal", "F");
  //legend1 -> AddEntry(f1_CapTime, "A*(1-e^{-B*t})*exp(-x/C)+D", "L");
  //legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time = %.1f #pm %.1f #musec}", CapTime, CapTimeErr),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


  TF1* f1_DcyTime = new TF1("f", "[0] * exp(-x/[1]) + [2]", 0, 20);
  f1_DcyTime -> SetParameter(0, 500);
  f1_DcyTime -> SetParameter(1, 10);
  f1_DcyTime -> SetParameter(2, 10);
  f1_DcyTime -> SetLineColor(kViolet+2);


  /////////// Only noise study //////////
#if 0
  TH1F* h1_NHits_AccNoise_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type0");
  h1_NHits_AccNoise_numu -> SetFillColor(kGray+2);
  h1_NHits_AccNoise_numu -> SetLineColor(kGray+2);
  TH1F* h1_NHits_dcye_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type1");
  h1_NHits_dcye_numu -> SetFillColor(kYellow-3);
  h1_NHits_dcye_numu -> SetLineColor(kYellow-3);
  TH1F* h1_NHits_H_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type2");
  h1_NHits_H_numu -> SetFillColor(kAzure-4);
  h1_NHits_H_numu -> SetLineColor(kAzure-4);
  TH1F* h1_NHits_Gd_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type3");
  h1_NHits_Gd_numu -> SetFillColor(kTeal-5);
  h1_NHits_Gd_numu -> SetLineColor(kTeal-5);

  THStack* hs_NHits_numu = new THStack("hs_NHits_numu", "NHits; NHits; Number of Events");
  hs_NHits_numu -> Add(h1_NHits_AccNoise_numu);
  hs_NHits_numu -> Add(h1_NHits_dcye_numu);
  hs_NHits_numu -> Add(h1_NHits_H_numu);
  hs_NHits_numu -> Add(h1_NHits_Gd_numu);


  //TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  //c1 -> SetGrid();
  //hs_RecoCapTime_numu -> Draw();
  //h1_TrueCapTime_numu -> Draw("SAME");
  //f1_DcyTime -> Draw("SAME");
  //c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.87, 0.87);
  legend1 -> SetTextSize(0.035);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Truth #nu CCQE}","");
  legend1 -> AddEntry(h1_RecoCapTime_AccNoise_numu, "Acc. noise", "F");
  legend1 -> AddEntry(h1_RecoCapTime_dcye_numu, "Decay-e", "F");
  legend1 -> AddEntry(h1_RecoCapTime_H_numu, "H-n signal", "F");
  legend1 -> AddEntry(h1_RecoCapTime_Gd_numu, "Gd-n signal", "F");
  legend1 -> SetFillColor(0);
  //legend1 -> Draw();

  TCanvas* c2 = new TCanvas("c2", "c2", 700, 500);
  c2 -> SetGrid();
  hs_NHits_numu -> Draw();
  c2->RedrawAxis();
  legend1 -> Draw();
#endif

}
