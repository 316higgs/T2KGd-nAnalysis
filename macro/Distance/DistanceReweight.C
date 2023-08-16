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


void DistanceReweight() {

  //FHC
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");

  TH1F* h1_ndistance_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truendistance");
  TH1F* h1_ndistance_m30_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truendistance_m30");
  h1_ndistance_numu -> SetStats(0);


  h1_ndistance_numu     -> SetLineColor(kAzure-1);
  h1_ndistance_numu     -> SetLineWidth(3);

  h1_ndistance_m30_numu     -> SetLineColor(kAzure+1);
  h1_ndistance_m30_numu     -> SetLineWidth(3);
  //h1_ndistance_numu     -> SetFillColor(kAzure-1);

  TF1* f1_nominal = new TF1("f1_nominal", "[0] * exp(-x/[1]) + [2]", 0.1, 5);
  f1_nominal -> SetParameter(0, 1000);    // for LL option (if normalized, LL should be used)
  f1_nominal -> SetParameter(1, 50);
  f1_nominal -> SetParameter(2, 10);
  f1_nominal -> SetLineColor(kPink-8);
  f1_nominal -> SetLineWidth(3);
  f1_nominal -> SetNpx(10000);

  float Lambda = 0.92;
  float rho = 0.7;
  float Lmax = 27.;
  TF1* f1_m30 = new TF1("f1_m30", "499 * exp(-x/(0.92*0.7)) + 9.6", 0.1, 5);
  f1_m30 -> SetLineColor(kAzure+1);
  f1_m30 -> SetLineWidth(3);
  f1_m30 -> SetNpx(10000);

  TF1* f1_p30 = new TF1("f1_p30", "499 * exp(-x/(0.92*1.3)) + 9.6", 0.1, 5);
  f1_p30 -> SetLineColor(kOrange+8);
  f1_p30 -> SetLineWidth(3);
  f1_p30 -> SetNpx(10000);
  
  std::cout << "All truth captured neutrons      : " << h1_ndistance_numu->Integral() << std::endl;
  std::cout << "All truth captured neutrons(-30%): " << h1_ndistance_m30_numu->Integral() << std::endl;

  gROOT -> SetStyle("Plain");

  h1_ndistance_numu -> Fit(f1_nominal, "r");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_ndistance_numu ->GetXaxis()->SetTitle("Truth Distance btw #nu and n capture vertices [m]");
  h1_ndistance_numu ->GetYaxis()->SetTitle("Number of Truth Neutrons");
  h1_ndistance_numu -> Draw();
  h1_ndistance_m30_numu -> Draw("SAME");
  f1_nominal -> Draw("SAME");
  f1_m30 -> Draw("SAME");
  //f1_p30 -> Draw("SAME");
  //c1 -> RedrawAxis();

  TLegend* legend1 = new TLegend(0.4, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  legend1 -> AddEntry(h1_ndistance_numu, "MC truth", "F");
  legend1 -> AddEntry(f1_nominal, "A*exp(-x/#lambda)+B", "L");
  legend1 -> AddEntry(f1_p30, "+30% of the fitted #lambda", "L");
  legend1 -> AddEntry(f1_m30, "-30% of the fitted #lambda", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();

}