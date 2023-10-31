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
#define nThreshold 0.7


void mergeEff_x_Distance() {


  TFile* fin_00251Gd_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.00251GdMC.bonsaikeras_ToF.root"); 
  TFile* fin_00251Gd_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_00251Gd_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_00251Gd_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_00251Gd_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_00251Gd_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");

  TFile* fin_00263Gd_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root"); 
  TFile* fin_00263Gd_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_00263Gd_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_00263Gd_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_00263Gd_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_00263Gd_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");


  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");


  /////  Truth neutrons  /////
  TH1D* h1_TrueD_00263Gd_numu      = (TH1D*)fin_00263Gd_numu->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00263Gd_nuesig    = (TH1D*)fin_00263Gd_nuesig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00263Gd_numubar   = (TH1D*)fin_00263Gd_numubar->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00263Gd_nuebarsig = (TH1D*)fin_00263Gd_nuebarsig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00263Gd_nuebkg    = (TH1D*)fin_00263Gd_nuebkg->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00263Gd_nuebarbkg = (TH1D*)fin_00263Gd_nuebarbkg->Get("DistanceViewer/h1_truedistance");

  TH1D* h1_TrueD_00251Gd_numu      = (TH1D*)fin_00251Gd_numu->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00251Gd_nuesig    = (TH1D*)fin_00251Gd_nuesig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00251Gd_numubar   = (TH1D*)fin_00251Gd_numubar->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00251Gd_nuebarsig = (TH1D*)fin_00251Gd_nuebarsig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00251Gd_nuebkg    = (TH1D*)fin_00251Gd_nuebkg->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_00251Gd_nuebarbkg = (TH1D*)fin_00251Gd_nuebarbkg->Get("DistanceViewer/h1_truedistance");


  /////  Tagged truth neutrons  /////
  float ThrNum = nThreshold/0.05;
  std::cout << "n-like threshold: " << nThreshold << " (#" << (int)ThrNum << ")" << std::endl;
  TH1D* h1_TagnD_00263Gd_numu      = (TH1D*)fin_00263Gd_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00263Gd_nuesig    = (TH1D*)fin_00263Gd_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00263Gd_numubar   = (TH1D*)fin_00263Gd_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00263Gd_nuebarsig = (TH1D*)fin_00263Gd_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00263Gd_nuebkg    = (TH1D*)fin_00263Gd_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00263Gd_nuebarbkg = (TH1D*)fin_00263Gd_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));

  TH1D* h1_TagnD_00251Gd_numu      = (TH1D*)fin_00251Gd_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00251Gd_nuesig    = (TH1D*)fin_00251Gd_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00251Gd_numubar   = (TH1D*)fin_00251Gd_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00251Gd_nuebarsig = (TH1D*)fin_00251Gd_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00251Gd_nuebkg    = (TH1D*)fin_00251Gd_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_00251Gd_nuebarbkg = (TH1D*)fin_00251Gd_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));


  ////  True neutrons (denominator)  ////
  TH1F* h1_TrueD_00263Gd_merge = new TH1F("h1_TrueD_00263Gd_merge", "", 10, 0, 5);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_numu);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_nuesig);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_numubar);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_nuebarsig);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_nuebkg);
  h1_TrueD_00263Gd_merge -> Add(h1_TrueD_00263Gd_nuebarbkg);

  TH1F* h1_TrueD_00251Gd_merge = new TH1F("h1_TrueD_00251Gd_merge", "", 10, 0, 5);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_numu);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_nuesig);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_numubar);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_nuebarsig);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_nuebkg);
  h1_TrueD_00251Gd_merge -> Add(h1_TrueD_00251Gd_nuebarbkg);


  ////  Overall efficiency (numerator)  ////
  TH1F* h1_TagEff_00263Gd_merge = new TH1F("h1_TagEff_00263Gd_merge", "", 10, 0, 5);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_numu);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_nuesig);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_numubar);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_nuebarsig);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_nuebkg);
  h1_TagEff_00263Gd_merge -> Add(h1_TagnD_00263Gd_nuebarbkg);

  TH1F* h1_TagEff_00251Gd_merge = new TH1F("h1_TagEff_00251Gd_merge", "", 10, 0, 5);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_numu);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_nuesig);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_numubar);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_nuebarsig);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_nuebkg);
  h1_TagEff_00251Gd_merge -> Add(h1_TagnD_00251Gd_nuebarbkg);

  h1_TagEff_00263Gd_merge -> SetLineColor(kAzure+5);
  h1_TagEff_00263Gd_merge -> SetLineWidth(3);
  h1_TagEff_00263Gd_merge -> Sumw2();
  h1_TagEff_00263Gd_merge -> Divide(h1_TrueD_00263Gd_merge);

  h1_TagEff_00251Gd_merge -> SetLineColor(kOrange+8);
  h1_TagEff_00251Gd_merge -> SetLineWidth(3);
  h1_TagEff_00251Gd_merge -> Sumw2();
  h1_TagEff_00251Gd_merge -> Divide(h1_TrueD_00251Gd_merge);


  gROOT -> SetStyle("Plain");

  TCanvas* cEff = new TCanvas("cEff","Overall Eff", 900, 700);
  cEff -> SetGrid();
  cEff -> cd();

  h1_TagEff_00251Gd_merge -> GetYaxis() -> SetRangeUser(0., 0.7);
  h1_TagEff_00251Gd_merge -> SetStats(0);
  h1_TagEff_00251Gd_merge -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_TagEff_00251Gd_merge -> SetYTitle("Overall Tagging Efficiency");
  h1_TagEff_00251Gd_merge -> Draw("SAME");
  h1_TagEff_00263Gd_merge -> Draw("SAME");

  TLegend* legend3 = new TLegend(0.13, 0.13, 0.6, 0.35);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  legend3 -> AddEntry(h1_TagEff_00263Gd_merge, "0.0263% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend3 -> AddEntry(h1_TagEff_00251Gd_merge, "0.0251% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend3 -> AddEntry((TObject*)0,"#kern[-0]{ (n-like threshold: 0.7)}","");
  legend3 -> SetFillColor(0);
  legend3 -> Draw();

}

