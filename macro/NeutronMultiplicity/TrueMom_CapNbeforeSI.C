#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void TrueMom_CapNbeforeSI(bool beammode) {

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


  TString hname_CapBefSI        = "NTagAnalysis/h1_CapBefSIMom";
  TString hname_CapBefSI_nucFSI = "NTagAnalysis/h1_CapBefSIMom_nucFSI";
  TString hname_CapBefSI_piFSI  = "NTagAnalysis/h1_CapBefSIMom_piFSI";
  TString hname_CapBefSI_deexc  = "NTagAnalysis/h1_CapBefSIMom_deexc";
  TString hname_CapBefSI_others = "NTagAnalysis/h1_CapBefSIMom_others";

  TH1F* h1_CapBefSI_numu        = (TH1F*)fin_numu->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_numu = (TH1F*)fin_numu->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_numu  = (TH1F*)fin_numu->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_numu  = (TH1F*)fin_numu->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_numu = (TH1F*)fin_numu->Get(hname_CapBefSI_others);
  h1_CapBefSI_numu -> SetStats(0);

  TH1F* h1_CapBefSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_nuesig = (TH1F*)fin_nuesig->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_nuesig  = (TH1F*)fin_nuesig->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_nuesig  = (TH1F*)fin_nuesig->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_nuesig = (TH1F*)fin_nuesig->Get(hname_CapBefSI_others);
  h1_CapBefSI_nuesig -> SetStats(0);

  TH1F* h1_CapBefSI_numubar        = (TH1F*)fin_numubar->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_numubar = (TH1F*)fin_numubar->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_numubar  = (TH1F*)fin_numubar->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_numubar  = (TH1F*)fin_numubar->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_numubar = (TH1F*)fin_numubar->Get(hname_CapBefSI_others);
  h1_CapBefSI_numubar -> SetStats(0);

  TH1F* h1_CapBefSI_nuebarsig        = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_nuebarsig = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_nuebarsig  = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_nuebarsig  = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_nuebarsig = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI_others);
  h1_CapBefSI_nuebarsig -> SetStats(0);

  TH1F* h1_CapBefSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_nuebkg = (TH1F*)fin_nuebkg->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_nuebkg  = (TH1F*)fin_nuebkg->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_nuebkg  = (TH1F*)fin_nuebkg->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_nuebkg = (TH1F*)fin_nuebkg->Get(hname_CapBefSI_others);
  h1_CapBefSI_nuebkg -> SetStats(0);

  TH1F* h1_CapBefSI_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI);
  TH1F* h1_CapBefSI_nucFSI_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI_nucFSI);
  TH1F* h1_CapBefSI_piFSI_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI_piFSI);
  TH1F* h1_CapBefSI_deexc_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI_deexc);
  TH1F* h1_CapBefSI_others_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI_others);
  h1_CapBefSI_nuebarbkg -> SetStats(0);


  /////  Normalizations  //////
#if 0
  h1_CapBefSI_numu         -> Scale( (ExpN_numu_x_numu)/(CapN_numu_x_numu) );
  h1_CapBefSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(CapN_numu_x_nue) );
  h1_CapBefSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(CapN_numubar_x_numubar) );
  h1_CapBefSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(CapN_numubar_x_nuebar) );
  h1_CapBefSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(CapN_nue_x_nue) );
  h1_CapBefSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(CapN_nuebar_x_nuebar) );

  h1_CapBefSI_nucFSI_numu         -> Scale( (ExpN_numu_x_numu)/(CapN_numu_x_numu) );
  h1_CapBefSI_nucFSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(CapN_numu_x_nue) );
  h1_CapBefSI_nucFSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(CapN_numubar_x_numubar) );
  h1_CapBefSI_nucFSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(CapN_numubar_x_nuebar) );
  h1_CapBefSI_nucFSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(CapN_nue_x_nue) );
  h1_CapBefSI_nucFSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(CapN_nuebar_x_nuebar) );

  h1_CapBefSI_piFSI_numu         -> Scale( (ExpN_numu_x_numu)/(CapN_numu_x_numu) );
  h1_CapBefSI_piFSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(CapN_numu_x_nue) );
  h1_CapBefSI_piFSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(CapN_numubar_x_numubar) );
  h1_CapBefSI_piFSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(CapN_numubar_x_nuebar) );
  h1_CapBefSI_piFSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(CapN_nue_x_nue) );
  h1_CapBefSI_piFSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(CapN_nuebar_x_nuebar) );

  h1_CapBefSI_deexc_numu         -> Scale( (ExpN_numu_x_numu)/(CapN_numu_x_numu) );
  h1_CapBefSI_deexc_nuesig       -> Scale( (ExpN_numu_x_nue)/(CapN_numu_x_nue) );
  h1_CapBefSI_deexc_numubar      -> Scale( (ExpN_numubar_x_numubar)/(CapN_numubar_x_numubar) );
  h1_CapBefSI_deexc_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(CapN_numubar_x_nuebar) );
  h1_CapBefSI_deexc_nuebkg       -> Scale( (ExpN_nue_x_nue)/(CapN_nue_x_nue) );
  h1_CapBefSI_deexc_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(CapN_nuebar_x_nuebar) );

  h1_CapBefSI_others_numu         -> Scale( (ExpN_numu_x_numu)/(CapN_numu_x_numu) );
  h1_CapBefSI_others_nuesig       -> Scale( (ExpN_numu_x_nue)/(CapN_numu_x_nue) );
  h1_CapBefSI_others_numubar      -> Scale( (ExpN_numubar_x_numubar)/(CapN_numubar_x_numubar) );
  h1_CapBefSI_others_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(CapN_numubar_x_nuebar) );
  h1_CapBefSI_others_nuebkg       -> Scale( (ExpN_nue_x_nue)/(CapN_nue_x_nue) );
  h1_CapBefSI_others_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(CapN_nuebar_x_nuebar) );
#endif


  bool osc_mode_on[6] = {1, 1, 1, 1, 1, 1};  // numu, numubar, nuesig, nuebarsig, nuebkg, nuebarbkg

  // 1D hist for each neutron source
  TH1F* h1_CapBefSI = new TH1F("h1_CapBefSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI -> Add(h1_CapBefSI_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI -> Add(h1_CapBefSI_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI -> Add(h1_CapBefSI_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI -> Add(h1_CapBefSI_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI -> Add(h1_CapBefSI_numubar);
  if (osc_mode_on[0]) h1_CapBefSI -> Add(h1_CapBefSI_numu);

  h1_CapBefSI -> SetLineColor(kGray+2);
  h1_CapBefSI -> SetStats(0);
  h1_CapBefSI -> SetLineWidth(3);

  TH1F* h1_CapBefSI_FSI = new TH1F("h1_CapBefSI_FSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_nuebarbkg);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_nuebarbkg);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_nuebarbkg);
  }
  if (osc_mode_on[4]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_nuebkg);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_nuebkg);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_nuebkg);
  }
  if (osc_mode_on[3]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_nuebarsig);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_nuebarsig);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_nuebarsig);
  }
  if (osc_mode_on[2]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_nuesig);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_nuesig);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_nuesig);
  }
  if (osc_mode_on[1]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_numubar);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_numubar);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_numubar);
  }
  if (osc_mode_on[0]) {
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_nucFSI_numu);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_piFSI_numu);
    h1_CapBefSI_FSI -> Add(h1_CapBefSI_deexc_numu);
  }

  h1_CapBefSI_FSI -> SetLineColor(kGray+2);
  h1_CapBefSI_FSI -> SetStats(0);
  h1_CapBefSI_FSI -> SetLineWidth(3);


  TH1F* h1_CapBefSI_nucFSI = new TH1F("h1_CapBefSI_nucFSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_numubar);
  if (osc_mode_on[0]) h1_CapBefSI_nucFSI -> Add(h1_CapBefSI_nucFSI_numu);

  h1_CapBefSI_nucFSI -> SetLineColor(kAzure+5);
  h1_CapBefSI_nucFSI -> SetStats(0);
  h1_CapBefSI_nucFSI -> SetLineWidth(3);

  TH1F* h1_CapBefSI_piFSI = new TH1F("h1_CapBefSI_piFSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_numubar);
  if (osc_mode_on[0]) h1_CapBefSI_piFSI -> Add(h1_CapBefSI_piFSI_numu);

  h1_CapBefSI_piFSI -> SetLineColor(kRed-6);
  h1_CapBefSI_piFSI -> SetStats(0);
  h1_CapBefSI_piFSI -> SetLineWidth(3);

  TH1F* h1_CapBefSI_deexc = new TH1F("h1_CapBefSI_deexc", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_numubar);
  if (osc_mode_on[0]) h1_CapBefSI_deexc -> Add(h1_CapBefSI_deexc_numu);

  h1_CapBefSI_deexc -> SetLineColor(kSpring+5);
  h1_CapBefSI_deexc -> SetStats(0);
  h1_CapBefSI_deexc -> SetLineWidth(3);

  TH1F* h1_CapBefSI_others = new TH1F("h1_CapBefSI_others", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_numubar);
  if (osc_mode_on[0]) h1_CapBefSI_others -> Add(h1_CapBefSI_others_numu);

  h1_CapBefSI_others -> SetLineColor(kYellow-3);
  h1_CapBefSI_others -> SetStats(0);
  h1_CapBefSI_others -> SetLineWidth(3);



  gROOT -> SetStyle("Plain");
#if 0
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_CapBefSI -> SetMaximum(1150);
  h1_CapBefSI ->GetYaxis()->SetTitleSize(0.045);
  h1_CapBefSI ->GetYaxis()->SetTitleOffset(1.1);
  h1_CapBefSI ->GetYaxis()->SetLabelSize(0.04);
  h1_CapBefSI ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_CapBefSI ->GetYaxis()->SetTitle("Number of Caperated Neutrons");
  h1_CapBefSI        -> Draw("SAME");
  h1_CapBefSI_nucFSI -> Draw("SAME");
  h1_CapBefSI_deexc  -> Draw("SAME");
  h1_CapBefSI_piFSI  -> Draw("SAME");
  h1_CapBefSI_others -> Draw("SAME");
  
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_CapBefSI, "All neutrons (before SI)", "L");
  legend1 -> AddEntry(h1_CapBefSI_others, "Primary #nu interaction", "L");
  legend1 -> AddEntry(h1_CapBefSI_nucFSI, "Nucleon FSI", "L");
  legend1 -> AddEntry(h1_CapBefSI_piFSI, "#pi FSI", "L");
  legend1 -> AddEntry(h1_CapBefSI_deexc, "de-excitation", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 1
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_CapBefSI_FSI -> SetMaximum(780);
  h1_CapBefSI_FSI ->GetYaxis()->SetTitleSize(0.045);
  h1_CapBefSI_FSI ->GetYaxis()->SetTitleOffset(1.1);
  h1_CapBefSI_FSI ->GetYaxis()->SetLabelSize(0.04);
  h1_CapBefSI_FSI ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_CapBefSI_FSI ->GetYaxis()->SetTitle("Number of Caperated Neutrons");
  h1_CapBefSI_FSI        -> Draw("SAME");
  h1_CapBefSI_nucFSI -> Draw("SAME");
  h1_CapBefSI_deexc  -> Draw("SAME");
  h1_CapBefSI_piFSI  -> Draw("SAME");
  
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_CapBefSI, "All neutrons (before SI)", "L");
  legend1 -> AddEntry(h1_CapBefSI_nucFSI, "Nucleon FSI", "L");
  legend1 -> AddEntry(h1_CapBefSI_piFSI, "#pi FSI", "L");
  legend1 -> AddEntry(h1_CapBefSI_deexc, "de-excitation", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

}

