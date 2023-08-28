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
#define nThreshold 0.7
#define BINNUM 10


float CalNTagEffStatErr(float NTagEff, float NTrueN);


void systSIDistance(bool beammode) {

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
  ////  nominal  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  ////  -30%  ////
  TFile* fin_numu_m30      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIm30.root");
  TFile* fin_nuesig_m30    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIm30.root");
  TFile* fin_numubar_m30   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIm30.root");
  TFile* fin_nuebarsig_m30 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIm30.root");
  TFile* fin_nuebkg_m30    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIm30.root");
  TFile* fin_nuebarbkg_m30 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIm30.root");

  ////  +30%  ////
  TFile* fin_numu_p30      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIp30.root");
  TFile* fin_nuesig_p30    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIp30.root");
  TFile* fin_numubar_p30   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIp30.root");
  TFile* fin_nuebarsig_p30 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIp30.root");
  TFile* fin_nuebkg_p30    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIp30.root");
  TFile* fin_nuebarbkg_p30 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIp30.root");

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


#if 1
  float ThrNum = nThreshold/0.05;
  std::cout << "n-like threshold: " << nThreshold << " (#" << (int)ThrNum << ")" << std::endl;
  
  TH1F* h1_TrueD_numu     = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_numu     = (TH1F*)fin_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_numu = (TH1F*)fin_numu_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_numu = (TH1F*)fin_numu_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_numu = (TH1F*)fin_numu_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_numu = (TH1F*)fin_numu_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_numu -> SetStats(0);
  h1_TagnD_numu -> SetStats(0);

  TH1F* h1_TrueD_nuesig     = (TH1F*)fin_nuesig->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_nuesig     = (TH1F*)fin_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_nuesig = (TH1F*)fin_nuesig_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_nuesig = (TH1F*)fin_nuesig_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_nuesig = (TH1F*)fin_nuesig_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_nuesig = (TH1F*)fin_nuesig_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_nuesig -> SetStats(0);
  h1_TagnD_nuesig -> SetStats(0);

  TH1F* h1_TrueD_numubar     = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_numubar     = (TH1F*)fin_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_numubar = (TH1F*)fin_numubar_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_numubar = (TH1F*)fin_numubar_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_numubar = (TH1F*)fin_numubar_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_numubar = (TH1F*)fin_numubar_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_numubar -> SetStats(0);
  h1_TagnD_numubar -> SetStats(0);

  TH1F* h1_TrueD_nuebarsig     = (TH1F*)fin_nuebarsig->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_nuebarsig     = (TH1F*)fin_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_nuebarsig = (TH1F*)fin_nuebarsig_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_nuebarsig = (TH1F*)fin_nuebarsig_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_nuebarsig = (TH1F*)fin_nuebarsig_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_nuebarsig = (TH1F*)fin_nuebarsig_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_nuebarsig -> SetStats(0);
  h1_TagnD_nuebarsig -> SetStats(0);

  TH1F* h1_TrueD_nuebkg     = (TH1F*)fin_nuebkg->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_nuebkg     = (TH1F*)fin_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_nuebkg = (TH1F*)fin_nuebkg_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_nuebkg = (TH1F*)fin_nuebkg_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_nuebkg = (TH1F*)fin_nuebkg_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_nuebkg = (TH1F*)fin_nuebkg_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_nuebkg -> SetStats(0);
  h1_TagnD_nuebkg -> SetStats(0);

  TH1F* h1_TrueD_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_m30_nuebarbkg = (TH1F*)fin_nuebarbkg_m30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_m30_nuebarbkg = (TH1F*)fin_nuebarbkg_m30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1F* h1_TrueD_p30_nuebarbkg = (TH1F*)fin_nuebarbkg_p30->Get("DistanceViewer/h1_truedistance");
  TH1F* h1_TagnD_p30_nuebarbkg = (TH1F*)fin_nuebarbkg_p30->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  h1_TrueD_nuebarbkg -> SetStats(0);
  h1_TagnD_nuebarbkg -> SetStats(0);
#endif


  /////  stat. error calculation  /////
  float nDistance[BINNUM]  = {0.};
  float dnDistance[BINNUM] = {0.};
  float dEff_nom[BINNUM]   = {0.};
  float dEff_m30[BINNUM]   = {0.};
  float dEff_p30[BINNUM]   = {0.};
#if 1
  for (int ibin=0; ibin<BINNUM; ibin++) {
    
    nDistance[ibin] = (2*ibin+1)*0.25;

    /*float NTrueN_m30  = h1_TrueD_m30_numu->GetBinContent(ibin+1)
                      + h1_TrueD_m30_nuesig->GetBinContent(ibin+1)
                      + h1_TrueD_m30_numubar->GetBinContent(ibin+1)
                      + h1_TrueD_m30_nuebarsig->GetBinContent(ibin+1)
                      + h1_TrueD_m30_nuebkg->GetBinContent(ibin+1)
                      + h1_TrueD_m30_nuebarbkg->GetBinContent(ibin+1);

    float NTagEff_m30 = h1_TagnD_m30_numu->GetBinContent(ibin+1)
                      + h1_TagnD_m30_nuesig->GetBinContent(ibin+1)
                      + h1_TagnD_m30_numubar->GetBinContent(ibin+1)
                      + h1_TagnD_m30_nuebarsig->GetBinContent(ibin+1)
                      + h1_TagnD_m30_nuebkg->GetBinContent(ibin+1)
                      + h1_TagnD_m30_nuebarbkg->GetBinContent(ibin+1);*/

    float NTrueN_nom  = h1_TrueD_numu->GetBinContent(ibin+1)
                      + h1_TrueD_numubar->GetBinContent(ibin+1);
    float NTagEff_nom = h1_TagnD_numu->GetBinContent(ibin+1)
                      + h1_TagnD_numubar->GetBinContent(ibin+1);

    float NTrueN_m30  = h1_TrueD_m30_numu->GetBinContent(ibin+1)
                      + h1_TrueD_m30_numubar->GetBinContent(ibin+1);
    float NTagEff_m30 = h1_TagnD_m30_numu->GetBinContent(ibin+1)
                      + h1_TagnD_m30_numubar->GetBinContent(ibin+1);

    float NTrueN_p30  = h1_TrueD_p30_numu->GetBinContent(ibin+1)
                      + h1_TrueD_p30_numubar->GetBinContent(ibin+1);
    float NTagEff_p30 = h1_TagnD_p30_numu->GetBinContent(ibin+1)
                      + h1_TagnD_p30_numubar->GetBinContent(ibin+1);

    NTagEff_nom /= NTrueN_nom;
    NTagEff_m30 /= NTrueN_m30;
    NTagEff_p30 /= NTrueN_p30;

    dEff_nom[ibin] = CalNTagEffStatErr(NTagEff_nom, NTrueN_nom)*NTagEff_nom;
    dEff_m30[ibin] = CalNTagEffStatErr(NTagEff_m30, NTrueN_m30)*NTagEff_m30;
    dEff_p30[ibin] = CalNTagEffStatErr(NTagEff_p30, NTrueN_p30)*NTagEff_p30;
    //std::cout << "[ " << nDistance[ibin] << " m ] True neutrons: " << NTrueN_m30 << ", Tagging efficiency: " << NTagEff_m30 << " (" << dEff_m30[ibin] << " )" << std::endl;
  }
#endif


  /////  Normalizations  //////
#if 1
  h1_TrueD_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueD_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueD_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueD_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueD_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueD_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueD_m30_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueD_m30_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueD_m30_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueD_m30_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueD_m30_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueD_m30_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueD_p30_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueD_p30_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueD_p30_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueD_p30_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueD_p30_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueD_p30_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagnD_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagnD_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagnD_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagnD_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagnD_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagnD_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagnD_m30_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagnD_m30_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagnD_m30_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagnD_m30_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagnD_m30_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagnD_m30_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagnD_p30_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagnD_p30_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagnD_p30_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagnD_p30_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagnD_p30_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagnD_p30_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  ////  Merged histograms  ////
  ////  true neutrons  ////
  TH1F* h1_TrueD_merge = new TH1F("h1_TrueD_merge", "", 10, 0, 5);
  h1_TrueD_merge -> Add(h1_TrueD_numu);
  //h1_TrueD_merge -> Add(h1_TrueD_nuesig);
  h1_TrueD_merge -> Add(h1_TrueD_numubar);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebarsig);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebkg);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebarbkg);

  h1_TrueD_merge -> SetStats(0);
  h1_TrueD_merge -> SetLineWidth(3);
  h1_TrueD_merge -> SetLineColor(kSpring+4);
  h1_TrueD_merge -> SetFillColor(kSpring+2);
  h1_TrueD_merge -> SetFillStyle(3004);


  TH1F* h1_TrueD_m30_merge = new TH1F("h1_TrueD_m30_merge", "", 10, 0, 5);
  h1_TrueD_m30_merge -> Add(h1_TrueD_m30_numu);
  //h1_TrueD_m30_merge -> Add(h1_TrueD_m30_nuesig);
  h1_TrueD_m30_merge -> Add(h1_TrueD_m30_numubar);
  //h1_TrueD_m30_merge -> Add(h1_TrueD_m30_nuebarsig);
  //h1_TrueD_m30_merge -> Add(h1_TrueD_m30_nuebkg);
  //h1_TrueD_m30_merge -> Add(h1_TrueD_m30_nuebarbkg);

  h1_TrueD_m30_merge -> SetLineWidth(3);
  h1_TrueD_m30_merge -> SetLineColor(kAzure-5);


  TH1F* h1_TrueD_p30_merge = new TH1F("h1_TrueD_p30_merge", "", 10, 0, 5);
  h1_TrueD_p30_merge -> Add(h1_TrueD_p30_numu);
  //h1_TrueD_p30_merge -> Add(h1_TrueD_p30_nuesig);
  h1_TrueD_p30_merge -> Add(h1_TrueD_p30_numubar);
  //h1_TrueD_p30_merge -> Add(h1_TrueD_p30_nuebarsig);
  //h1_TrueD_p30_merge -> Add(h1_TrueD_p30_nuebkg);
  //h1_TrueD_p30_merge -> Add(h1_TrueD_p30_nuebarbkg);

  h1_TrueD_p30_merge -> SetLineWidth(3);
  h1_TrueD_p30_merge -> SetLineColor(kRed-3);


  ////  tagged true neutrons  ////
  TH1F* h1_TagnD_merge = new TH1F("h1_TagnD_merge", "", 10, 0, 5);
  h1_TagnD_merge -> Add(h1_TagnD_numu);
  //h1_TagnD_merge -> Add(h1_TagnD_nuesig);
  h1_TagnD_merge -> Add(h1_TagnD_numubar);
  //h1_TagnD_merge -> Add(h1_TagnD_nuebarsig);
  //h1_TagnD_merge -> Add(h1_TagnD_nuebkg);
  //h1_TagnD_merge -> Add(h1_TagnD_nuebarbkg);

  h1_TagnD_merge -> SetStats(0);
  h1_TagnD_merge -> SetLineWidth(3);
  h1_TagnD_merge -> SetLineColor(kSpring+4);
  h1_TagnD_merge -> SetFillColor(kSpring+2);
  h1_TagnD_merge -> SetFillStyle(3004);


  TH1F* h1_TagnD_m30_merge = new TH1F("h1_TagnD_m30_merge", "", 10, 0, 5);
  h1_TagnD_m30_merge -> Add(h1_TagnD_m30_numu);
  //h1_TagnD_m30_merge -> Add(h1_TagnD_m30_nuesig);
  h1_TagnD_m30_merge -> Add(h1_TagnD_m30_numubar);
  //h1_TagnD_m30_merge -> Add(h1_TagnD_m30_nuebarsig);
  //h1_TagnD_m30_merge -> Add(h1_TagnD_m30_nuebkg);
  //h1_TagnD_m30_merge -> Add(h1_TagnD_m30_nuebarbkg);
  h1_TagnD_m30_merge -> SetLineWidth(3);
  h1_TagnD_m30_merge -> SetLineColor(kAzure-5);


  TH1F* h1_TagnD_p30_merge = new TH1F("h1_TagnD_p30_merge", "", 10, 0, 5);
  h1_TagnD_p30_merge -> Add(h1_TagnD_p30_numu);
  //h1_TagnD_p30_merge -> Add(h1_TagnD_p30_nuesig);
  h1_TagnD_p30_merge -> Add(h1_TagnD_p30_numubar);
  //h1_TagnD_p30_merge -> Add(h1_TagnD_p30_nuebarsig);
  //h1_TagnD_p30_merge -> Add(h1_TagnD_p30_nuebkg);
  //h1_TagnD_p30_merge -> Add(h1_TagnD_p30_nuebarbkg);
  h1_TagnD_p30_merge -> SetLineWidth(3);
  h1_TagnD_p30_merge -> SetLineColor(kRed-3);


  ////  tagging efficiency  ////
  TH1F* h1_TagEff_merge = new TH1F("h1_TagEff_merge", "", 10, 0, 5);
  h1_TagEff_merge -> Add(h1_TagnD_numu);
  //h1_TagEff_merge -> Add(h1_TagnD_nuesig);
  h1_TagEff_merge -> Add(h1_TagnD_numubar);
  //h1_TagEff_merge -> Add(h1_TagnD_nuebarsig);
  //h1_TagEff_merge -> Add(h1_TagnD_nuebkg);
  //h1_TagEff_merge -> Add(h1_TagnD_nuebarbkg);
  h1_TagEff_merge -> Sumw2();
  h1_TagEff_merge -> Divide(h1_TrueD_merge);

  h1_TagEff_merge -> SetStats(0);
  h1_TagEff_merge -> SetLineWidth(3);
  h1_TagEff_merge -> SetLineColor(kSpring+4);
  h1_TagEff_merge -> SetFillColor(kSpring+2);
  h1_TagEff_merge -> SetFillStyle(3004);

  float Eff_nom[BINNUM] = {0.};
  for (int ibin=0; ibin<BINNUM; ibin++) {
    float NTrueN_nom  = h1_TrueD_merge->GetBinContent(ibin+1);
    float NTagEff_nom = h1_TagnD_merge->GetBinContent(ibin+1);
    NTagEff_nom /= NTrueN_nom;
    Eff_nom[ibin] = NTagEff_nom;
  }
  TGraphErrors* g_err_nom = new TGraphErrors(BINNUM, nDistance, Eff_nom, dnDistance, dEff_nom);
  g_err_nom -> SetLineWidth(3);
  g_err_nom -> SetMarkerColor(kSpring+4);
  g_err_nom -> SetLineColor(kSpring+4);


  TH1F* h1_TagEff_m30_merge = new TH1F("h1_TagEff_m30_merge", "", 10, 0, 5);
  h1_TagEff_m30_merge -> Add(h1_TagnD_m30_numu);
  //h1_TagEff_m30_merge -> Add(h1_TagnD_m30_nuesig);
  h1_TagEff_m30_merge -> Add(h1_TagnD_m30_numubar);
  //h1_TagEff_m30_merge -> Add(h1_TagnD_m30_nuebarsig);
  //h1_TagEff_m30_merge -> Add(h1_TagnD_m30_nuebkg);
  //h1_TagEff_m30_merge -> Add(h1_TagnD_m30_nuebarbkg);
  h1_TagEff_m30_merge -> Sumw2();
  h1_TagEff_m30_merge -> Divide(h1_TrueD_m30_merge);
  h1_TagEff_m30_merge -> SetLineWidth(3);
  h1_TagEff_m30_merge -> SetLineColor(kAzure-5);

  float Eff_m30[BINNUM] = {0.};
  for (int ibin=0; ibin<BINNUM; ibin++) {
    float NTrueN_m30  = h1_TrueD_m30_merge->GetBinContent(ibin+1);
    float NTagEff_m30 = h1_TagnD_m30_merge->GetBinContent(ibin+1);
    NTagEff_m30 /= NTrueN_m30;
    Eff_m30[ibin] = NTagEff_m30;
  }
  TGraphErrors* g_err_m30 = new TGraphErrors(BINNUM, nDistance, Eff_m30, dnDistance, dEff_m30);
  g_err_m30 -> SetLineWidth(3);
  g_err_m30 -> SetMarkerColor(kAzure-5);
  g_err_m30 -> SetLineColor(kAzure-5);


  TH1F* h1_TagEff_p30_merge = new TH1F("h1_TagEff_p30_merge", "", 10, 0, 5);
  h1_TagEff_p30_merge -> Add(h1_TagnD_p30_numu);
  //h1_TagEff_p30_merge -> Add(h1_TagnD_p30_nuesig);
  h1_TagEff_p30_merge -> Add(h1_TagnD_p30_numubar);
  //h1_TagEff_p30_merge -> Add(h1_TagnD_p30_nuebarsig);
  //h1_TagEff_p30_merge -> Add(h1_TagnD_p30_nuebkg);
  //h1_TagEff_p30_merge -> Add(h1_TagnD_p30_nuebarbkg);
  h1_TagEff_p30_merge -> Sumw2();
  h1_TagEff_p30_merge -> Divide(h1_TrueD_p30_merge);
  h1_TagEff_p30_merge -> SetLineWidth(3);
  h1_TagEff_p30_merge -> SetLineColor(kRed-3);

  float Eff_p30[BINNUM] = {0.};
  for (int ibin=0; ibin<BINNUM; ibin++) {
    float NTrueN_p30  = h1_TrueD_p30_merge->GetBinContent(ibin+1);
    float NTagEff_p30 = h1_TagnD_p30_merge->GetBinContent(ibin+1);
    NTagEff_p30 /= NTrueN_p30;
    Eff_p30[ibin] = NTagEff_p30;
  }
  TGraphErrors* g_err_p30 = new TGraphErrors(BINNUM, nDistance, Eff_p30, dnDistance, dEff_p30);
  g_err_p30 -> SetLineWidth(3);
  g_err_p30 -> SetMarkerColor(kRed-3);
  g_err_p30 -> SetLineColor(kRed-3);



  TLegend* legend1 = new TLegend(0.47, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_TrueD_merge, "Nominal MC", "F");
  legend1 -> AddEntry(h1_TrueD_p30_merge, "+30% Bertini's tot xsec", "L");
  legend1 -> AddEntry(h1_TrueD_m30_merge, "-30% Bertini's tot xsec", "L");
  legend1->SetFillColor(0);

#if 1
  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  if (beammode) h1_TrueD_merge -> SetMaximum(25);
  h1_TrueD_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_TrueD_merge ->GetXaxis()->SetTitleSize(0.038);
  h1_TrueD_merge ->GetYaxis()->SetTitleOffset(1.3);
  h1_TrueD_merge ->GetYaxis()->SetLabelSize(0.036);
  h1_TrueD_merge ->GetXaxis()->SetTitle("Truth Distance between #nu and n Capture Vertices [m]");
  h1_TrueD_merge ->GetYaxis()->SetTitle("Number of Truth Neutrons");
  h1_TrueD_merge -> Draw();
  h1_TrueD_m30_merge -> Draw("SAME");
  h1_TrueD_p30_merge -> Draw("SAME");
  legend1->Draw();
#endif

#if 1
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  if (beammode) h1_TagnD_merge -> SetMaximum(10);
  h1_TagnD_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_TagnD_merge ->GetXaxis()->SetTitleSize(0.038);
  h1_TagnD_merge ->GetYaxis()->SetTitleOffset(1.3);
  h1_TagnD_merge ->GetYaxis()->SetLabelSize(0.036);
  h1_TagnD_merge ->GetXaxis()->SetTitle("Truth Distance between #nu and n Capture Vertices [m]");
  h1_TagnD_merge ->GetYaxis()->SetTitle("Number of Tagged Truth Neutrons");
  h1_TagnD_merge -> Draw();
  h1_TagnD_m30_merge -> Draw("SAME");
  h1_TagnD_p30_merge -> Draw("SAME");
  legend1 -> Draw();
#endif

#if 1
  TCanvas* c3 = new TCanvas("c3","c3",900,700);
  c3 -> SetGrid();
  h1_TagEff_merge -> SetMaximum(1.);
  h1_TagEff_merge -> SetMinimum(0.);
  h1_TagEff_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_TagEff_merge ->GetXaxis()->SetTitleSize(0.038);
  h1_TagEff_merge ->GetYaxis()->SetTitleOffset(1.3);
  h1_TagEff_merge ->GetYaxis()->SetLabelSize(0.036);
  h1_TagEff_merge ->GetXaxis()->SetTitle("Truth Distance between #nu and n Capture Vertices [m]");
  h1_TagEff_merge ->GetYaxis()->SetTitle("Overall Tagging Efficiency");
  h1_TagEff_merge -> Draw("histo");
  g_err_nom -> Draw("SAMEP");
  h1_TagEff_m30_merge -> Draw("histoSAME");
  g_err_m30 -> Draw("SAMEP");
  h1_TagEff_p30_merge -> Draw("histoSAME");
  g_err_p30 -> Draw("SAMEP");

  float xMinPos = 5;       // x-minimum where you want to set
  float xMaxPos = xMinPos; // x-maximum where you want to set
  float yMinPos = 0;       // y-minimum where you want to set
  float yMaxPos = 1;       // y-maximum where you want to set
  float SetPos  = 1;
  TGaxis* axis = new TGaxis(xMinPos,yMinPos,xMaxPos,yMaxPos, 0, SetPos, 510, "+L");
  //axis -> SetTitle("Purity");
  //axis -> SetTitleSize(0.035);
  //axis -> SetTitleColor(kPink-5);
  axis -> SetLabelColor(kWhite);
  //axis -> SetLabelSize(0.035);
  axis -> Draw();

  legend1 -> Draw();
#endif

}



float CalNTagEffStatErr(float NTagEff, float NTrueN) {
  float dNTagEff = std::sqrt( ( NTagEff*(1-NTagEff) ) / NTrueN );
  return dNTagEff/NTagEff;
}


