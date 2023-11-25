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

#define SELECTIONCUTS 6


void CompareSelEff(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  // Gd MC
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  // Pure water MC
  TFile* fin_numu_pw      = new TFile("../../output/fhc/fhc.numu_x_numu.water.root");
  TFile* fin_nuesig_pw    = new TFile("../../output/fhc/fhc.numu_x_nue.water.root");
  TFile* fin_numubar_pw   = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");
  TFile* fin_nuebarsig_pw = new TFile("../../output/fhc/fhc.numubar_x_nuebar.water.root");
  TFile* fin_nuebkg_pw    = new TFile("../../output/fhc/fhc.nue_x_nue.water.root");
  TFile* fin_nuebarbkg_pw = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.water.root");

  TFile* fin_skrate_pw = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate_gd = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");


  // Normalization factors
  TH1F* h1_skrate_numu_x_numu_gd       = (TH1F*)fin_skrate_gd->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue_gd        = (TH1F*)fin_skrate_gd->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar_gd = (TH1F*)fin_skrate_gd->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar_gd  = (TH1F*)fin_skrate_gd->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue_gd         = (TH1F*)fin_skrate_gd->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar_gd   = (TH1F*)fin_skrate_gd->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu_gd         = h1_skrate_numu_x_numu_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue_gd          = h1_skrate_numu_x_nue_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar_gd   = h1_skrate_numubar_x_numubar_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar_gd    = h1_skrate_numubar_x_nuebar_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue_gd           = h1_skrate_nue_x_nue_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar_gd     = h1_skrate_nuebar_x_nuebar_gd->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu_gd         = 63622;
  Double_t GenN_numu_x_nue_gd          = 63538;
  Double_t GenN_numubar_x_numubar_gd   = 63444;
  Double_t GenN_numubar_x_nuebar_gd    = 63460;
  Double_t GenN_nue_x_nue_gd           = 63423;
  Double_t GenN_nuebar_x_nuebar_gd     = 63652;

  TH1F* h1_skrate_numu_x_numu_pw       = (TH1F*)fin_skrate_pw->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue_pw        = (TH1F*)fin_skrate_pw->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar_pw = (TH1F*)fin_skrate_pw->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar_pw  = (TH1F*)fin_skrate_pw->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue_pw         = (TH1F*)fin_skrate_pw->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar_pw   = (TH1F*)fin_skrate_pw->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu_pw         = h1_skrate_numu_x_numu_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue_pw          = h1_skrate_numu_x_nue_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar_pw   = h1_skrate_numubar_x_numubar_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar_pw    = h1_skrate_numubar_x_nuebar_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue_pw           = h1_skrate_nue_x_nue_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar_pw     = h1_skrate_nuebar_x_nuebar_pw->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu_pw         = 448378;
  Double_t GenN_numu_x_nue_pw          = 100190;
  Double_t GenN_numubar_x_numubar_pw   = 429594;
  Double_t GenN_numubar_x_nuebar_pw    = 98073;
  Double_t GenN_nue_x_nue_pw           = 105070;
  Double_t GenN_nuebar_x_nuebar_pw     = 98053;



  ////  No oscillation  ////
  TH1F* h1_SelEff_numu_gd      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuesig_gd    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_numubar_gd   = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebarsig_gd = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebkg_gd    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebarbkg_gd = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_1RmuonEvents");

  TH1F* h1_ProtoSelEff_numu_gd      = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  TH1F* h1_ProtoSelEff_nuesig_gd    = (TH1F*)fin_nuesig->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  TH1F* h1_ProtoSelEff_numubar_gd   = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  TH1F* h1_ProtoSelEff_nuebarsig_gd = (TH1F*)fin_nuebarsig->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  TH1F* h1_ProtoSelEff_nuebkg_gd    = (TH1F*)fin_nuebkg->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  TH1F* h1_ProtoSelEff_nuebarbkg_gd = (TH1F*)fin_nuebarbkg->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");

  TH1F* h1_SelEff_numu_pw      = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuesig_pw    = (TH1F*)fin_nuesig_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_numubar_pw   = (TH1F*)fin_numubar_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebarsig_pw = (TH1F*)fin_nuebarsig_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebkg_pw    = (TH1F*)fin_nuebkg_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  TH1F* h1_SelEff_nuebarbkg_pw = (TH1F*)fin_nuebarbkg_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");


  //  Generated number (for error calculation)
  TH1F* h1_GenSelEff_pw = new TH1F("h1_GenSelEff_pw", "", 6, 0, 6);
  h1_GenSelEff_pw -> Add(h1_SelEff_numu_pw);
  h1_GenSelEff_pw -> Add(h1_SelEff_nuesig_pw);
  h1_GenSelEff_pw -> Add(h1_SelEff_numubar_pw);
  h1_GenSelEff_pw -> Add(h1_SelEff_nuebarsig_pw);
  h1_GenSelEff_pw -> Add(h1_SelEff_nuebkg_pw);
  h1_GenSelEff_pw -> Add(h1_SelEff_nuebarbkg_pw);

  TH1F* h1_ProtoGenSelEff_gd = new TH1F("h1_ProtoGenSelEff_gd", "", 6, 0, 6);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_numu_gd);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_nuesig_gd);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_numubar_gd);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_nuebarsig_gd);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_nuebkg_gd);
  h1_ProtoGenSelEff_gd -> Add(h1_ProtoSelEff_nuebarbkg_gd);

  TH1F* h1_GenSelEff_gd = new TH1F("h1_GenSelEff_gd", "", 6, 0, 6);
  h1_GenSelEff_gd -> Add(h1_SelEff_numu_gd);
  h1_GenSelEff_gd -> Add(h1_SelEff_nuesig_gd);
  h1_GenSelEff_gd -> Add(h1_SelEff_numubar_gd);
  h1_GenSelEff_gd -> Add(h1_SelEff_nuebarsig_gd);
  h1_GenSelEff_gd -> Add(h1_SelEff_nuebkg_gd);
  h1_GenSelEff_gd -> Add(h1_SelEff_nuebarbkg_gd);

  TH1F* h1_GenFCFV_pw = new TH1F("h1_FCFV_pw", "", 6, 0, 6);
  TH1F* h1_GenFCFV_gd = new TH1F("h1_FCFV_gd", "", 6, 0, 6);
  for (int ibin=0; ibin<SELECTIONCUTS; ibin++) {
    h1_GenFCFV_pw      -> SetBinContent(ibin+1, h1_GenSelEff_pw->GetBinContent(1));
    h1_GenFCFV_gd      -> SetBinContent(ibin+1, h1_GenSelEff_gd->GetBinContent(1));
  }


  /////  Normalizations  //////
  h1_SelEff_numu_gd      -> Scale( (ExpN_numu_x_numu_gd)/(GenN_numu_x_numu_gd) );
  h1_SelEff_nuesig_gd    -> Scale( (ExpN_numu_x_nue_gd)/(GenN_numu_x_nue_gd) );
  h1_SelEff_numubar_gd   -> Scale( (ExpN_numubar_x_numubar_gd)/(GenN_numubar_x_numubar_gd) );
  h1_SelEff_nuebarsig_gd -> Scale( (ExpN_numubar_x_nuebar_gd)/(GenN_numubar_x_nuebar_gd) );
  h1_SelEff_nuebkg_gd    -> Scale( (ExpN_nue_x_nue_gd)/(GenN_nue_x_nue_gd) );
  h1_SelEff_nuebarbkg_gd -> Scale( (ExpN_nuebar_x_nuebar_gd)/(GenN_nuebar_x_nuebar_gd) );

  h1_ProtoSelEff_numu_gd      -> Scale( (ExpN_numu_x_numu_gd)/(GenN_numu_x_numu_gd) );
  h1_ProtoSelEff_nuesig_gd    -> Scale( (ExpN_numu_x_nue_gd)/(GenN_numu_x_nue_gd) );
  h1_ProtoSelEff_numubar_gd   -> Scale( (ExpN_numubar_x_numubar_gd)/(GenN_numubar_x_numubar_gd) );
  h1_ProtoSelEff_nuebarsig_gd -> Scale( (ExpN_numubar_x_nuebar_gd)/(GenN_numubar_x_nuebar_gd) );
  h1_ProtoSelEff_nuebkg_gd    -> Scale( (ExpN_nue_x_nue_gd)/(GenN_nue_x_nue_gd) );
  h1_ProtoSelEff_nuebarbkg_gd -> Scale( (ExpN_nuebar_x_nuebar_gd)/(GenN_nuebar_x_nuebar_gd) );

  h1_SelEff_numu_pw      -> Scale( (ExpN_numu_x_numu_pw)/(GenN_numu_x_numu_pw) );
  h1_SelEff_nuesig_pw    -> Scale( (ExpN_numu_x_nue_pw)/(GenN_numu_x_nue_pw) );
  h1_SelEff_numubar_pw   -> Scale( (ExpN_numubar_x_numubar_pw)/(GenN_numubar_x_numubar_pw) );
  h1_SelEff_nuebarsig_pw -> Scale( (ExpN_numubar_x_nuebar_pw)/(GenN_numubar_x_nuebar_pw) );
  h1_SelEff_nuebkg_pw    -> Scale( (ExpN_nue_x_nue_pw)/(GenN_nue_x_nue_pw) );
  h1_SelEff_nuebarbkg_pw -> Scale( (ExpN_nuebar_x_nuebar_pw)/(GenN_nuebar_x_nuebar_pw) );


  TH1F* h1_SelEff_pw = new TH1F("h1_SelEff_pw", "", 6, 0, 6);
  h1_SelEff_pw -> Add(h1_SelEff_numu_pw);
  h1_SelEff_pw -> Add(h1_SelEff_nuesig_pw);
  h1_SelEff_pw -> Add(h1_SelEff_numubar_pw);
  h1_SelEff_pw -> Add(h1_SelEff_nuebarsig_pw);
  h1_SelEff_pw -> Add(h1_SelEff_nuebkg_pw);
  h1_SelEff_pw -> Add(h1_SelEff_nuebarbkg_pw);

  TH1F* h1_ProtoSelEff_gd = new TH1F("h1_ProtoSelEff_gd", "", 6, 0, 6);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_numu_gd);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_nuesig_gd);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_numubar_gd);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_nuebarsig_gd);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_nuebkg_gd);
  h1_ProtoSelEff_gd -> Add(h1_ProtoSelEff_nuebarbkg_gd);

  TH1F* h1_SelEff_gd = new TH1F("h1_SelEff_gd", "", 6, 0, 6);
  h1_SelEff_gd -> Add(h1_SelEff_numu_gd);
  h1_SelEff_gd -> Add(h1_SelEff_nuesig_gd);
  h1_SelEff_gd -> Add(h1_SelEff_numubar_gd);
  h1_SelEff_gd -> Add(h1_SelEff_nuebarsig_gd);
  h1_SelEff_gd -> Add(h1_SelEff_nuebkg_gd);
  h1_SelEff_gd -> Add(h1_SelEff_nuebarbkg_gd);

  float fcfv_gd = h1_SelEff_numu_gd->GetBinContent(1) +
                  h1_SelEff_nuesig_gd->GetBinContent(1) +
                  h1_SelEff_numubar_gd->GetBinContent(1) +
                  h1_SelEff_nuebarsig_gd->GetBinContent(1) +
                  h1_SelEff_nuebkg_gd->GetBinContent(1) +
                  h1_SelEff_nuebarbkg_gd->GetBinContent(1);

  float fcfv_pw = h1_SelEff_numu_pw->GetBinContent(1) +
                  h1_SelEff_nuesig_pw->GetBinContent(1) +
                  h1_SelEff_numubar_pw->GetBinContent(1) +
                  h1_SelEff_nuebarsig_pw->GetBinContent(1) +
                  h1_SelEff_nuebkg_pw->GetBinContent(1) +
                  h1_SelEff_nuebarbkg_pw->GetBinContent(1);

  h1_SelEff_gd      -> Scale(1./fcfv_gd);
  h1_ProtoSelEff_gd -> Scale(1./fcfv_gd);
  h1_SelEff_pw      -> Scale(1./fcfv_pw);


  for (int istep=0; istep<SELECTIONCUTS; istep++) {
    std::cout << "[" << istep+1 << "] Gd MC(floor cut) : " << h1_SelEff_gd->GetBinContent(istep+1) << std::endl;
    std::cout << "[" << istep+1 << "] Gd MC            : " << h1_ProtoSelEff_gd->GetBinContent(istep+1) << std::endl;
    std::cout << "[" << istep+1 << "] Pure water MC    : " << h1_SelEff_pw->GetBinContent(istep+1) << std::endl;
    std::cout << " " << std::endl;
  }


  h1_SelEff_gd -> SetLineColor(kOrange+0);
  h1_SelEff_gd -> SetLineWidth(3);

  h1_ProtoSelEff_gd -> SetLineColor(kOrange+0);
  h1_ProtoSelEff_gd -> SetLineStyle(7);
  h1_ProtoSelEff_gd -> SetLineWidth(3);

  h1_SelEff_pw -> SetLineColor(kAzure+1);
  //h1_SelEff_pw -> SetLineStyle(7);
  h1_SelEff_pw -> SetLineWidth(3);
  h1_SelEff_pw -> SetStats(0);
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_SelEff_pw -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");


  //  error histograms
  h1_GenSelEff_gd -> Sumw2();
  h1_GenSelEff_gd -> Divide(h1_GenFCFV_gd);

  h1_ProtoGenSelEff_gd -> Sumw2();
  h1_ProtoGenSelEff_gd -> Divide(h1_GenFCFV_gd);

  h1_GenSelEff_pw -> Sumw2();
  h1_GenSelEff_pw -> Divide(h1_GenFCFV_pw);

  Double_t step[SELECTIONCUTS]            = {0.5, 1.5, 2.5, 3.5, 4.5, 5.5};
  Double_t dstep[SELECTIONCUTS]           = {0.};
  Double_t SelEff_gd[SELECTIONCUTS]       = {0.};
  Double_t dSelEff_gd[SELECTIONCUTS]      = {0.};
  Double_t ProtoSelEff_gd[SELECTIONCUTS]  = {0.};
  Double_t dProtoSelEff_gd[SELECTIONCUTS] = {0.};
  Double_t SelEff_pw[SELECTIONCUTS]       = {0.};
  Double_t dSelEff_pw[SELECTIONCUTS]      = {0.};

  for (int ibin=0; ibin<SELECTIONCUTS; ibin++) {
    SelEff_gd[ibin]      = h1_SelEff_gd->GetBinContent(ibin+1);
    ProtoSelEff_gd[ibin] = h1_ProtoSelEff_gd->GetBinContent(ibin+1);
    SelEff_pw[ibin]      = h1_SelEff_pw->GetBinContent(ibin+1);
    if (ibin==0) {
      dSelEff_gd[ibin]      = 0.;  // definition
      dProtoSelEff_gd[ibin] = 0.;  // definition
      dSelEff_pw[ibin]      = 0.;  // definition
    }
    else {
      dSelEff_gd[ibin]      = h1_GenSelEff_gd->GetBinError(ibin+1);
      dProtoSelEff_gd[ibin] = h1_ProtoGenSelEff_gd->GetBinError(ibin+1);
      dSelEff_pw[ibin]      = h1_GenSelEff_pw->GetBinError(ibin+1);
    }
  }

  TGraphErrors* g_SelEff_gd = new TGraphErrors(SELECTIONCUTS, step, SelEff_gd, dstep, dSelEff_gd);
  g_SelEff_gd -> SetLineColor(kOrange+0);
  g_SelEff_gd -> SetLineWidth(2);

  TGraphErrors* g_ProtoSelEff_gd = new TGraphErrors(SELECTIONCUTS, step, ProtoSelEff_gd, dstep, dProtoSelEff_gd);
  g_ProtoSelEff_gd -> SetLineColor(kOrange+0);
  g_ProtoSelEff_gd -> SetLineWidth(2);

  TGraphErrors* g_SelEff_pw = new TGraphErrors(SELECTIONCUTS, step, SelEff_pw, dstep, dSelEff_pw);
  g_SelEff_pw -> SetLineColor(kAzure+1);
  g_SelEff_pw -> SetLineWidth(2);


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2","c2", 1000, 700);
  c2 -> SetGrid();
  h1_SelEff_pw -> Draw();
  h1_SelEff_pw -> SetMinimum(0.);
  h1_SelEff_pw -> SetMaximum(1.1);
  h1_SelEff_pw ->GetYaxis()->SetTitleSize(0.038);
  h1_SelEff_pw ->GetYaxis()->SetTitleOffset(0.9);
  h1_SelEff_pw ->GetYaxis()->SetLabelSize(0.04);
  h1_SelEff_pw ->GetYaxis()->SetTitle("Remaining rate from FCFV cut");
  h1_SelEff_pw ->GetYaxis()->SetTitleSize(0.045);
  h1_SelEff_pw ->GetXaxis()->SetLabelSize(0.045);
  
  h1_SelEff_pw -> Draw("");
  g_SelEff_pw  -> Draw("SAME E P");
  
  h1_ProtoSelEff_gd -> Draw("SAME");
  g_ProtoSelEff_gd  -> Draw("SAME E P");

  h1_SelEff_gd -> Draw("SAME");
  g_SelEff_gd  -> Draw("SAME E P");

  TLegend* legend1 = new TLegend(0.35, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.45]{FHC 1R#mu sample}","");
  legend1 -> AddEntry(h1_SelEff_pw, "Pure water MC: Decay-e #leq 1", "L");
  legend1 -> AddEntry(h1_ProtoSelEff_gd, "Gd MC: Decay-e #leq 1", "L");
  legend1 -> AddEntry(h1_SelEff_gd, "Gd MC: floor cut + Decay-e #leq 1", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif
}

