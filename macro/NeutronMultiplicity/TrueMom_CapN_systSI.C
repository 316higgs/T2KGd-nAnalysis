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


void TrueMom_CapN_systSI(bool beammode) {

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

  TFile* fin_numu_m30     = new TFile("../../output/fhc/fhc.numu_x_numu.systSIm30.bonsaikeras_ToF.root");
  TFile* fin_nuesig_m30    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIm30.bonsaikeras_ToF.root");
  TFile* fin_numubar_m30   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIm30.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_m30 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIm30.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_m30    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIm30.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_m30 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIm30.bonsaikeras_ToF.root");

  TFile* fin_numu_p30      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIp30.bonsaikeras_ToF.root");
  TFile* fin_nuesig_p30    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIp30.bonsaikeras_ToF.root");
  TFile* fin_numubar_p30   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIp30.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_p30 = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIp30.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_p30    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIp30.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_p30 = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIp30.bonsaikeras_ToF.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif



  TString hname_GenBefSI = "NTagAnalysis/h1_GenBefSIMom";
  TString hname_CapBefSI = "NTagAnalysis/h1_CapBefSIMom";
  TString hname_CapAftSI = "NTagAnalysis/h1_CapSIMom";

  TH1F* h1_GenBefSI_numu          = (TH1F*)fin_numu->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numu          = (TH1F*)fin_numu->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numu          = (TH1F*)fin_numu->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_numu_m30      = (TH1F*)fin_numu_m30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numu_m30      = (TH1F*)fin_numu_m30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numu_m30      = (TH1F*)fin_numu_m30->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_numu_p30      = (TH1F*)fin_numu_p30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numu_p30      = (TH1F*)fin_numu_p30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numu_p30      = (TH1F*)fin_numu_p30->Get(hname_CapAftSI);

  TH1F* h1_GenBefSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuesig        = (TH1F*)fin_nuesig->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuesig_m30    = (TH1F*)fin_nuesig_m30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuesig_m30    = (TH1F*)fin_nuesig_m30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuesig_m30    = (TH1F*)fin_nuesig_m30->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuesig_p30    = (TH1F*)fin_nuesig_p30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuesig_p30    = (TH1F*)fin_nuesig_p30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuesig_p30    = (TH1F*)fin_nuesig_p30->Get(hname_CapAftSI);

  TH1F* h1_GenBefSI_numubar       = (TH1F*)fin_numubar->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numubar       = (TH1F*)fin_numubar->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numubar       = (TH1F*)fin_numubar->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_numubar_m30   = (TH1F*)fin_numubar->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numubar_m30   = (TH1F*)fin_numubar->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numubar_m30   = (TH1F*)fin_numubar->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_numubar_p30   = (TH1F*)fin_numubar->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_numubar_p30   = (TH1F*)fin_numubar->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_numubar_p30   = (TH1F*)fin_numubar->Get(hname_CapAftSI);

  TH1F* h1_GenBefSI_nuebarsig     = (TH1F*)fin_nuebarsig->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarsig     = (TH1F*)fin_nuebarsig->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarsig     = (TH1F*)fin_nuebarsig->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebarsig_m30 = (TH1F*)fin_nuebarsig_m30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarsig_m30 = (TH1F*)fin_nuebarsig_m30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarsig_m30 = (TH1F*)fin_nuebarsig_m30->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebarsig_p30 = (TH1F*)fin_nuebarsig_p30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarsig_p30 = (TH1F*)fin_nuebarsig_p30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarsig_p30 = (TH1F*)fin_nuebarsig_p30->Get(hname_CapAftSI);

  TH1F* h1_GenBefSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebkg        = (TH1F*)fin_nuebkg->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebkg_m30    = (TH1F*)fin_nuebkg_m30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebkg_m30    = (TH1F*)fin_nuebkg_m30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebkg_m30    = (TH1F*)fin_nuebkg_m30->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebkg_p30    = (TH1F*)fin_nuebkg_p30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebkg_p30    = (TH1F*)fin_nuebkg_p30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebkg_p30    = (TH1F*)fin_nuebkg_p30->Get(hname_CapAftSI);

  TH1F* h1_GenBefSI_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebarbkg_m30 = (TH1F*)fin_nuebarbkg_m30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarbkg_m30 = (TH1F*)fin_nuebarbkg_m30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarbkg_m30 = (TH1F*)fin_nuebarbkg_m30->Get(hname_CapAftSI);
  TH1F* h1_GenBefSI_nuebarbkg_p30 = (TH1F*)fin_nuebarbkg_p30->Get(hname_GenBefSI);
  TH1F* h1_CapBefSI_nuebarbkg_p30 = (TH1F*)fin_nuebarbkg_p30->Get(hname_CapBefSI);
  TH1F* h1_CapAftSI_nuebarbkg_p30 = (TH1F*)fin_nuebarbkg_p30->Get(hname_CapAftSI);



  bool osc_mode_on[6] = {1, 1, 1, 1, 1, 1};  // numu, numubar, nuesig, nuebarsig, nuebkg, nuebarbkg

  /////    Generated neutrons before SI    //////  
  TH1F* h1_GenBefSI = new TH1F("h1_GenBefSI", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI -> Add(h1_GenBefSI_nuebarbkg);
  if (osc_mode_on[4]) h1_GenBefSI -> Add(h1_GenBefSI_nuebkg);
  if (osc_mode_on[3]) h1_GenBefSI -> Add(h1_GenBefSI_nuebarsig);
  if (osc_mode_on[2]) h1_GenBefSI -> Add(h1_GenBefSI_nuesig);
  if (osc_mode_on[1]) h1_GenBefSI -> Add(h1_GenBefSI_numubar);
  if (osc_mode_on[0]) h1_GenBefSI -> Add(h1_GenBefSI_numu);

  h1_GenBefSI -> SetLineColor(kAzure+1);
  h1_GenBefSI -> SetFillColor(kAzure+6);
  h1_GenBefSI -> SetFillStyle(3005);
  h1_GenBefSI -> SetStats(0);
  h1_GenBefSI -> SetLineWidth(3);

  TH1F* h1_GenBefSI_m30 = new TH1F("h1_GenBefSI_m30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_nuebarbkg_m30);
  if (osc_mode_on[4]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_nuebkg_m30);
  if (osc_mode_on[3]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_nuebarsig_m30);
  if (osc_mode_on[2]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_nuesig_m30);
  if (osc_mode_on[1]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_numubar_m30);
  if (osc_mode_on[0]) h1_GenBefSI_m30 -> Add(h1_GenBefSI_numu_m30);

  h1_GenBefSI_m30 -> SetLineColor(kAzure-9);
  h1_GenBefSI_m30 -> SetStats(0);
  h1_GenBefSI_m30 -> SetLineWidth(3);

  TH1F* h1_GenBefSI_p30 = new TH1F("h1_GenBefSI_p30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_nuebarbkg_p30);
  if (osc_mode_on[4]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_nuebkg_p30);
  if (osc_mode_on[3]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_nuebarsig_p30);
  if (osc_mode_on[2]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_nuesig_p30);
  if (osc_mode_on[1]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_numubar_p30);
  if (osc_mode_on[0]) h1_GenBefSI_p30 -> Add(h1_GenBefSI_numu_p30);

  h1_GenBefSI_p30 -> SetLineColor(kViolet-7);
  h1_GenBefSI_p30 -> SetStats(0);
  h1_GenBefSI_p30 -> SetLineWidth(3);


  /////    Capture neutrons before SI    //////  
  TH1F* h1_CapBefSI = new TH1F("h1_CapBefSI", "", 120, 0, 1200);
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

  TH1F* h1_CapBefSI_m30 = new TH1F("h1_CapBefSI_m30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_nuebarbkg_m30);
  if (osc_mode_on[4]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_nuebkg_m30);
  if (osc_mode_on[3]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_nuebarsig_m30);
  if (osc_mode_on[2]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_nuesig_m30);
  if (osc_mode_on[1]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_numubar_m30);
  if (osc_mode_on[0]) h1_CapBefSI_m30 -> Add(h1_CapBefSI_numu_m30);

  h1_CapBefSI_m30 -> SetLineColor(kRed-10);
  h1_CapBefSI_m30 -> SetStats(0);
  h1_CapBefSI_m30 -> SetLineWidth(3);

  TH1F* h1_CapBefSI_p30 = new TH1F("h1_CapBefSI_p30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_nuebarbkg_p30);
  if (osc_mode_on[4]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_nuebkg_p30);
  if (osc_mode_on[3]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_nuebarsig_p30);
  if (osc_mode_on[2]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_nuesig_p30);
  if (osc_mode_on[1]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_numubar_p30);
  if (osc_mode_on[0]) h1_CapBefSI_p30 -> Add(h1_CapBefSI_numu_p30);

  h1_CapBefSI_p30 -> SetLineColor(kPink+3);
  h1_CapBefSI_p30 -> SetStats(0);
  h1_CapBefSI_p30 -> SetLineWidth(3);


  /////    Capture neutrons after SI    //////
  TH1F* h1_CapAftSI = new TH1F("h1_CapAftSI", "", 120, 0, 1200);
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

  TH1F* h1_CapAftSI_m30 = new TH1F("h1_CapAftSI_m30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_nuebarbkg_m30);
  if (osc_mode_on[4]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_nuebkg_m30);
  if (osc_mode_on[3]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_nuebarsig_m30);
  if (osc_mode_on[2]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_nuesig_m30);
  if (osc_mode_on[1]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_numubar_m30);
  if (osc_mode_on[0]) h1_CapAftSI_m30 -> Add(h1_CapAftSI_numu_m30);

  h1_CapAftSI_m30 -> SetLineColor(kOrange-8);
  h1_CapAftSI_m30 -> SetStats(0);
  h1_CapAftSI_m30 -> SetLineWidth(3);

  TH1F* h1_CapAftSI_p30 = new TH1F("h1_CapAftSI_p30", "", 120, 0, 1200);
  if (osc_mode_on[5]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_nuebarbkg_p30);
  if (osc_mode_on[4]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_nuebkg_p30);
  if (osc_mode_on[3]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_nuebarsig_p30);
  if (osc_mode_on[2]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_nuesig_p30);
  if (osc_mode_on[1]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_numubar_p30);
  if (osc_mode_on[0]) h1_CapAftSI_p30 -> Add(h1_CapAftSI_numu_p30);

  h1_CapAftSI_p30 -> SetLineColor(kOrange+10);
  h1_CapAftSI_p30 -> SetStats(0);
  h1_CapAftSI_p30 -> SetLineWidth(3);



  gROOT -> SetStyle("Plain");

#if 0
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_GenBefSI -> SetMaximum(9000);
  //h1_GenBefSI -> SetMaximum(1000);
  h1_GenBefSI ->GetYaxis()->SetTitleSize(0.04);
  h1_GenBefSI ->GetYaxis()->SetTitleOffset(1.2);
  h1_GenBefSI ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefSI ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  h1_GenBefSI -> Draw("SAME");
  h1_CapBefSI -> Draw("SAME");
  h1_CapAftSI -> Draw("SAME");
  

  TLegend* legend2 = new TLegend(0.3, 0.65, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  //if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  legend2 -> AddEntry(h1_GenBefSI, "Primary #nu int. + FSI (Generated)", "L");
  legend2 -> AddEntry(h1_CapBefSI, "Primary #nu int. + FSI (Captured)", "L");
  legend2 -> AddEntry(h1_CapAftSI, "SI (Captured)", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_GenBefSI_m30 -> SetMaximum(1000);
  h1_GenBefSI_m30 ->GetYaxis()->SetTitleSize(0.04);
  h1_GenBefSI_m30 ->GetYaxis()->SetTitleOffset(1.2);
  h1_GenBefSI_m30 ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefSI_m30 ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI_m30 ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  h1_GenBefSI_m30 -> Draw("SAME");
  h1_GenBefSI     -> Draw("SAME");
  h1_GenBefSI_p30 -> Draw("SAME");
  
  h1_CapBefSI_m30 -> Draw("SAME");
  h1_CapBefSI     -> Draw("SAME");
  h1_CapBefSI_p30 -> Draw("SAME");


  TLegend* legend2 = new TLegend(0.45, 0.5, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(h1_GenBefSI, "Before SI (Generated)", "L");
  legend2 -> AddEntry(h1_GenBefSI_m30, "   Bertini xsec -30%", "L");
  legend2 -> AddEntry(h1_GenBefSI_p30, "   Bertini xsec +30%", "L");
  legend2 -> AddEntry(h1_CapBefSI, "Before SI (Captured)", "L");
  legend2 -> AddEntry(h1_CapBefSI_m30, "   Bertini xsec -30%", "L");
  legend2 -> AddEntry(h1_CapBefSI_p30, "   Bertini xsec +30%", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif


#if 1
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_GenBefSI_m30 -> SetMaximum(5000);
  //h1_GenBefSI_m30 -> SetMaximum(1000);
  h1_GenBefSI_m30 ->GetYaxis()->SetTitleSize(0.04);
  h1_GenBefSI_m30 ->GetYaxis()->SetTitleOffset(1.2);
  h1_GenBefSI_m30 ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefSI_m30 ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI_m30 ->GetYaxis()->SetTitle("Number of Captured Neutrons");
  h1_GenBefSI_m30 -> Draw("SAME");
  h1_GenBefSI     -> Draw("SAME");
  h1_GenBefSI_p30 -> Draw("SAME");
  
  h1_CapBefSI_m30 -> Draw("SAME");
  h1_CapBefSI     -> Draw("SAME");
  h1_CapBefSI_p30 -> Draw("SAME");

  h1_CapAftSI_m30 -> Draw("SAME");
  h1_CapAftSI     -> Draw("SAME");
  h1_CapAftSI_p30 -> Draw("SAME");


  TLegend* legend2 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(h1_GenBefSI, "Before SI (Generated)", "L");
  legend2 -> AddEntry(h1_GenBefSI_m30, "   Bertini xsec -30%", "L");
  legend2 -> AddEntry(h1_GenBefSI_p30, "   Bertini xsec +30%", "L");
  legend2 -> AddEntry(h1_CapBefSI, "Before SI (Captured)", "L");
  legend2 -> AddEntry(h1_CapBefSI_m30, "   Bertini xsec -30%", "L");
  legend2 -> AddEntry(h1_CapBefSI_p30, "   Bertini xsec +30%", "L");
  legend2 -> AddEntry(h1_CapAftSI, "After SI (Captured)", "L");
  legend2 -> AddEntry(h1_CapAftSI_m30, "   Bertini xsec -30%", "L");
  legend2 -> AddEntry(h1_CapAftSI_p30, "   Bertini xsec +30%", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif

}

