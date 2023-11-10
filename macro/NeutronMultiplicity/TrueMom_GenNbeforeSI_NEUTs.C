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


void TrueMom_GenNbeforeSI_NEUTs(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  // pure water MC
#if fhcflag
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.water.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.water.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.water.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.water.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.water.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
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
#if 1
  Double_t GenN_numu_x_numu       = 448378;
  Double_t GenN_numu_x_nue        = 100190;
  Double_t GenN_numubar_x_numubar = 429594;
  Double_t GenN_numubar_x_nuebar  = 98073;
  Double_t GenN_nue_x_nue         = 105070;
  Double_t GenN_nuebar_x_nuebar   = 98053;
#endif
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


  TString hname_GenBefSI        = "NTagAnalysis/h1_GenBefSIMom";
  TString hname_GenBefSI_nucFSI = "NTagAnalysis/h1_GenBefSIMom_nucFSI";
  TString hname_GenBefSI_piFSI  = "NTagAnalysis/h1_GenBefSIMom_piFSI";
  TString hname_GenBefSI_deexc  = "NTagAnalysis/h1_GenBefSIMom_deexc";
  TString hname_GenBefSI_others = "NTagAnalysis/h1_GenBefSIMom_others";
  TString hname_CapBefSI        = "NTagAnalysis/h1_CapBefSIMom";
  TString hname_CapAftSI        = "NTagAnalysis/h1_CapSIMom";

  TH1F* h1_GenBefSI_numu        = (TH1F*)fin_numu->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_numu = (TH1F*)fin_numu->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_numu  = (TH1F*)fin_numu->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_numu  = (TH1F*)fin_numu->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_numu = (TH1F*)fin_numu->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_numu        = (TH1F*)fin_numu->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numu        = (TH1F*)fin_numu->Get(hname_CapAftSI);
  h1_GenBefSI_numu -> SetStats(0);

  TH1F* h1_GenBefSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_nuesig = (TH1F*)fin_nuesig->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_nuesig  = (TH1F*)fin_nuesig->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_nuesig  = (TH1F*)fin_nuesig->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_nuesig = (TH1F*)fin_nuesig->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_CapAftSI);
  h1_GenBefSI_nuesig -> SetStats(0);

  TH1F* h1_GenBefSI_numubar        = (TH1F*)fin_numubar->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_numubar = (TH1F*)fin_numubar->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_numubar  = (TH1F*)fin_numubar->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_numubar  = (TH1F*)fin_numubar->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_numubar = (TH1F*)fin_numubar->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_numubar        = (TH1F*)fin_numubar->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numubar        = (TH1F*)fin_numubar->Get(hname_CapAftSI);
  h1_GenBefSI_numubar -> SetStats(0);

  TH1F* h1_GenBefSI_nuebarsig        = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_nuebarsig = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_nuebarsig  = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_nuebarsig  = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_nuebarsig = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_nuebarsig        = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarsig        = (TH1F*)fin_nuebarsig->Get(hname_CapAftSI);
  h1_GenBefSI_nuebarsig -> SetStats(0);

  TH1F* h1_GenBefSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_nuebkg = (TH1F*)fin_nuebkg->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_nuebkg  = (TH1F*)fin_nuebkg->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_nuebkg  = (TH1F*)fin_nuebkg->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_nuebkg = (TH1F*)fin_nuebkg->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_CapAftSI);
  h1_GenBefSI_nuebkg -> SetStats(0);

  TH1F* h1_GenBefSI_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI_deexc);
  TH1F* h1_GenBefSI_others_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI_others);
  TH1F* h1_CapBefSI_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get(hname_CapAftSI);
  h1_GenBefSI_nuebarbkg -> SetStats(0);


  /////  Normalizations  //////
#if 0
  h1_GenBefSI_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_GenBefSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenBefSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_GenBefSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_GenBefSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_GenBefSI_nucFSI_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSI_nucFSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_GenBefSI_nucFSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenBefSI_nucFSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_GenBefSI_nucFSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_GenBefSI_nucFSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_GenBefSI_piFSI_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSI_piFSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_GenBefSI_piFSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenBefSI_piFSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_GenBefSI_piFSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_GenBefSI_piFSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_GenBefSI_deexc_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSI_deexc_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_GenBefSI_deexc_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenBefSI_deexc_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_GenBefSI_deexc_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_GenBefSI_deexc_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_GenBefSI_others_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSI_others_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_GenBefSI_others_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenBefSI_others_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_GenBefSI_others_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_GenBefSI_others_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  bool osc_mode_on[6] = {1, 1, 1, 1, 1, 1};  // numu, numubar, nuesig, nuebarsig, nuebkg, nuebarbkg

  // 1D hist for each neutron source
  //  generated neutrons
  TH1F* h1_GenBefSI = new TH1F("h1_GenBefSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI -> Add(h1_GenBefSI_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI -> Add(h1_GenBefSI_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI -> Add(h1_GenBefSI_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI -> Add(h1_GenBefSI_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI -> Add(h1_GenBefSI_numubar);
  if (osc_mode_on[0]) h1_GenBefSI -> Add(h1_GenBefSI_numu);

  h1_GenBefSI -> SetLineColor(kGray+2);
  h1_GenBefSI -> SetStats(0);
  h1_GenBefSI -> SetLineWidth(3);

  TH1F* h1_GenBefSI_FSI = new TH1F("h1_GenBefSI_FSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_nuebarbkg);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_nuebarbkg);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_nuebarbkg);
  }
  if (osc_mode_on[4]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_nuebkg);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_nuebkg);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_nuebkg);
  }
  if (osc_mode_on[3]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_nuebarsig);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_nuebarsig);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_nuebarsig);
  }
  if (osc_mode_on[2]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_nuesig);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_nuesig);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_nuesig);
  }
  if (osc_mode_on[1]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_numubar);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_numubar);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_numubar);
  }
  if (osc_mode_on[0]) {
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_nucFSI_numu);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_piFSI_numu);
    h1_GenBefSI_FSI -> Add(h1_GenBefSI_deexc_numu);
  }

  h1_GenBefSI_FSI -> SetLineColor(kGray+2);
  h1_GenBefSI_FSI -> SetStats(0);
  h1_GenBefSI_FSI -> SetLineWidth(3);


  TH1F* h1_GenBefSI_nucFSI = new TH1F("h1_GenBefSI_nucFSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_numubar);
  if (osc_mode_on[0]) h1_GenBefSI_nucFSI -> Add(h1_GenBefSI_nucFSI_numu);

  h1_GenBefSI_nucFSI -> SetLineColor(kAzure+5);
  h1_GenBefSI_nucFSI -> SetStats(0);
  h1_GenBefSI_nucFSI -> SetLineWidth(3);

  TH1F* h1_GenBefSI_piFSI = new TH1F("h1_GenBefSI_piFSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_numubar);
  if (osc_mode_on[0]) h1_GenBefSI_piFSI -> Add(h1_GenBefSI_piFSI_numu);

  h1_GenBefSI_piFSI -> SetLineColor(kRed-6);
  h1_GenBefSI_piFSI -> SetStats(0);
  h1_GenBefSI_piFSI -> SetLineWidth(3);

  TH1F* h1_GenBefSI_deexc = new TH1F("h1_GenBefSI_deexc", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_numubar);
  if (osc_mode_on[0]) h1_GenBefSI_deexc -> Add(h1_GenBefSI_deexc_numu);

  h1_GenBefSI_deexc -> SetLineColor(kSpring+5);
  h1_GenBefSI_deexc -> SetStats(0);
  h1_GenBefSI_deexc -> SetLineWidth(3);

  TH1F* h1_GenBefSI_others = new TH1F("h1_GenBefSI_others", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_numubar);
  if (osc_mode_on[0]) h1_GenBefSI_others -> Add(h1_GenBefSI_others_numu);

  h1_GenBefSI_others -> SetLineColor(kYellow-3);
  h1_GenBefSI_others -> SetStats(0);
  h1_GenBefSI_others -> SetLineWidth(3);


  //  captured neutrons
  TH1F* h1_CapBefSI = new TH1F("h1_CapBefSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI -> Add(h1_CapBefSI_nuebarbkg);
  if (osc_mode_on[4]) h1_CapBefSI -> Add(h1_CapBefSI_nuebkg);
  if (osc_mode_on[3]) h1_CapBefSI -> Add(h1_CapBefSI_nuebarsig);
  if (osc_mode_on[2]) h1_CapBefSI -> Add(h1_CapBefSI_nuesig);
  if (osc_mode_on[1]) h1_CapBefSI -> Add(h1_CapBefSI_numubar);
  if (osc_mode_on[0]) h1_CapBefSI -> Add(h1_CapBefSI_numu);

  h1_CapBefSI -> SetLineColor(kRed-3);
  h1_CapBefSI -> SetFillColor(kRed-9);
  h1_CapBefSI -> SetFillStyle(3004);
  h1_CapBefSI -> SetStats(0);
  h1_CapBefSI -> SetLineWidth(3);


  TH1F* h1_CapAftSI = new TH1F("h1_CapAftSI", "", 60, 0, 1200);
  if (osc_mode_on[5]) h1_CapAftSI -> Add(h1_CapAftSI_nuebarbkg);
  if (osc_mode_on[4]) h1_CapAftSI -> Add(h1_CapAftSI_nuebkg);
  if (osc_mode_on[3]) h1_CapAftSI -> Add(h1_CapAftSI_nuebarsig);
  if (osc_mode_on[2]) h1_CapAftSI -> Add(h1_CapAftSI_nuesig);
  if (osc_mode_on[1]) h1_CapAftSI -> Add(h1_CapAftSI_numubar);
  if (osc_mode_on[0]) h1_CapAftSI -> Add(h1_CapAftSI_numu);

  h1_CapAftSI -> SetLineColor(kOrange-3);
  h1_CapAftSI -> SetFillColor(kOrange-2);
  h1_CapAftSI -> SetFillStyle(3004);
  h1_CapAftSI -> SetStats(0);
  h1_CapAftSI -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");
#if 0
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_GenBefSI ->GetYaxis()->SetTitleSize(0.045);
  h1_GenBefSI ->GetYaxis()->SetTitleOffset(1.1);
  h1_GenBefSI ->GetYaxis()->SetLabelSize(0.04);
  h1_GenBefSI ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI ->GetYaxis()->SetTitle("Number of Generated Neutrons");
  h1_GenBefSI -> Draw("SAME");
  h1_GenBefSI_nucFSI -> Draw("SAME");
  h1_GenBefSI_deexc  -> Draw("SAME");
  h1_GenBefSI_piFSI  -> Draw("SAME");
  h1_GenBefSI_others -> Draw("SAME");
  
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_GenBefSI, "All neutrons (before SI)", "L");
  legend1 -> AddEntry(h1_GenBefSI_others, "Primary #nu interaction", "L");
  legend1 -> AddEntry(h1_GenBefSI_nucFSI, "Nucleon FSI", "L");
  legend1 -> AddEntry(h1_GenBefSI_piFSI, "#pi FSI", "L");
  legend1 -> AddEntry(h1_GenBefSI_deexc, "de-excitation", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 1
  // except with primary interaction
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_GenBefSI_FSI ->GetXaxis()->SetTitleSize(0.045);
  h1_GenBefSI_FSI ->GetYaxis()->SetTitleSize(0.045);
  h1_GenBefSI_FSI ->GetYaxis()->SetTitleOffset(1.1);
  h1_GenBefSI_FSI ->GetYaxis()->SetLabelSize(0.04);
  h1_GenBefSI_FSI ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI_FSI ->GetYaxis()->SetTitle("Number of Generated Neutrons");
  h1_GenBefSI_FSI    -> Draw("SAME");
  h1_GenBefSI_nucFSI -> Draw("SAME");
  h1_GenBefSI_deexc  -> Draw("SAME");
  h1_GenBefSI_piFSI  -> Draw("SAME");
  
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_GenBefSI, "All neutrons (before SI)", "L");
  legend1 -> AddEntry(h1_GenBefSI_nucFSI, "Nucleon FSI", "L");
  legend1 -> AddEntry(h1_GenBefSI_piFSI, "#pi FSI", "L");
  legend1 -> AddEntry(h1_GenBefSI_deexc, "de-excitation", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

}

