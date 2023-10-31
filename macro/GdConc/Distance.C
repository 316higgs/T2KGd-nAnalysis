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


void Distance(bool beammode) {

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

#if 1
  float Gdconc = 0.0263;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
#endif

#if 0
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

  
  ////  True distance  ////
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("DistanceViewer/h1_truedistance_CCQE");
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("DistanceViewer/h1_truedistance_CC2p2h");
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("DistanceViewer/h1_truedistance_CCOther");
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("DistanceViewer/h1_truedistance_NC");
  h1_CCQE_nuebarbkg -> SetStats(0);


  /////  Merged distance  //////
  TH1F* h1_TrueDistance = new TH1F("h1_TrueDistance", "", 10, 0, 5);
  h1_TrueDistance -> SetLineColor(kViolet+3);
  h1_TrueDistance -> SetLineWidth(2);
  h1_TrueDistance -> SetStats(0);
  h1_TrueDistance -> SetXTitle("Truth Capture Time [#musec]");
  h1_TrueDistance -> SetYTitle("Number of Captured Neutrons");
  h1_TrueDistance -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueDistance -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_TrueDistance -> Add(h1_NC_nuebarbkg);
  h1_TrueDistance -> Add(h1_NC_nuebkg);
  h1_TrueDistance -> Add(h1_NC_nuebarsig);
  h1_TrueDistance -> Add(h1_NC_numubar);
  h1_TrueDistance -> Add(h1_NC_nuesig);
  h1_TrueDistance -> Add(h1_NC_numu);

  h1_TrueDistance -> Add(h1_CCOther_nuebarbkg);
  h1_TrueDistance -> Add(h1_CC2p2h_nuebarbkg);
  h1_TrueDistance -> Add(h1_CCQE_nuebarbkg);
  h1_TrueDistance -> Add(h1_CCOther_nuebkg);
  h1_TrueDistance -> Add(h1_CC2p2h_nuebkg);
  h1_TrueDistance -> Add(h1_CCQE_nuebkg);
  h1_TrueDistance -> Add(h1_CCOther_nuebarsig);
  h1_TrueDistance -> Add(h1_CC2p2h_nuebarsig);
  h1_TrueDistance -> Add(h1_CCQE_nuebarsig);
  h1_TrueDistance -> Add(h1_CCOther_nuesig);
  h1_TrueDistance -> Add(h1_CC2p2h_nuesig);
  h1_TrueDistance -> Add(h1_CCQE_nuesig);

  h1_TrueDistance -> Add(h1_CCOther_numubar);
  h1_TrueDistance -> Add(h1_CCOther_numu);
  h1_TrueDistance -> Add(h1_CC2p2h_numubar);
  h1_TrueDistance -> Add(h1_CC2p2h_numu);
  h1_TrueDistance -> Add(h1_CCQE_numubar);
  h1_TrueDistance -> Add(h1_CCQE_numu);
#endif


  TString foutname = TString::Format("output/Distance.Gdconc%f.root", Gdconc);
  TFile* fout = new TFile(foutname, "RECREATE");
  fout -> cd();
  h1_TrueDistance -> Write();

}