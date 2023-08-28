#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void TrueVtxProfile() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");

  TH2F* h2_TruePrmVtx_XY = (TH2F*)fin->Get("NeutrinoOscillation/h2_TruePrmVtxXY");
  TH2F* h2_TruePrmVtx_RZ = (TH2F*)fin->Get("NeutrinoOscillation/h2_TruePrmVtxRZ");
  h2_TruePrmVtx_XY -> SetStats(0);
  h2_TruePrmVtx_RZ -> SetStats(0);
  h2_TruePrmVtx_XY -> SetXTitle("Primary vertex X [m]");
  h2_TruePrmVtx_XY -> SetYTitle("Primary vertex Y [m]");
  h2_TruePrmVtx_RZ -> SetXTitle("Primary vertex R^{2} [m^{2}]");
  h2_TruePrmVtx_RZ -> SetYTitle("Primary vertex Z [m]");

  TH1D* h1_TruePrmVtxX = h2_TruePrmVtx_XY->ProjectionX("h1_TruePrmVtxX");
  TH1D* h1_TruePrmVtxY = h2_TruePrmVtx_XY->ProjectionY("h1_TruePrmVtxY");

  TF1* f1_uprFCFV_XY  = new TF1("f1_uprFCFV_XY", "sqrt(14.9*14.9-x*x)", -15.1, 15.1);
  TF1* f1_btmFCFV_XY = new TF1("f1_btmFCFV_XY", "-sqrt(14.9*14.9-x*x)", -15.1, 15.1);
  f1_uprFCFV_XY -> SetLineStyle(7);
  f1_uprFCFV_XY -> SetLineWidth(3);
  f1_uprFCFV_XY -> SetLineColor(kOrange-2);
  f1_btmFCFV_XY -> SetLineStyle(7);
  f1_btmFCFV_XY -> SetLineWidth(3);
  f1_btmFCFV_XY -> SetLineColor(kOrange-2);

  TF1* f1_uprFCFV_RZ = new TF1("f1_uprFCFV_RZ", "16.1", 0., 14.9*14.9);
  TF1* f1_btmFCFV_RZ = new TF1("f1_btmFCFV_RZ", "-16.1", 0., 14.9*14.9);
  f1_uprFCFV_RZ -> SetLineStyle(7);
  f1_uprFCFV_RZ -> SetLineWidth(3);
  f1_uprFCFV_RZ -> SetLineColor(kOrange-2);
  f1_btmFCFV_RZ -> SetLineStyle(7);
  f1_btmFCFV_RZ -> SetLineWidth(3);
  f1_btmFCFV_RZ -> SetLineColor(kOrange-2);
  float x[2] = {14.9*14.9, 14.9*14.9};
  float y[2] = {-16.1, 16.1};
  TGraph* g1_brlFCFV_RZ = new TGraph(2, x, y);
  g1_brlFCFV_RZ -> SetLineStyle(7);
  g1_brlFCFV_RZ -> SetLineWidth(3);
  g1_brlFCFV_RZ -> SetLineColor(kOrange-2);

  /////////////////////////////////////////////////////////

  TH2F* h2_TrueNCapVtx_XY = (TH2F*)fin->Get("NTagAnalysis/h2_TrueNCapVtxXY");
  TH2F* h2_TrueNCapVtx_RZ = (TH2F*)fin->Get("NTagAnalysis/h2_TrueNCapVtxRZ");
  h2_TruePrmVtx_XY -> SetStats(0);
  h2_TrueNCapVtx_RZ -> SetStats(0);
  h2_TrueNCapVtx_XY -> SetXTitle("Neutron capture vertex X [m]");
  h2_TrueNCapVtx_XY -> SetYTitle("Neutron capture vertex Y [m]");
  h2_TrueNCapVtx_RZ -> SetXTitle("Neutron capture vertex R^{2} [m^{2}]");
  h2_TrueNCapVtx_RZ -> SetYTitle("Neutron capture vertex Z [m]");
  h2_TrueNCapVtx_XY -> SetStats(0);
  h2_TrueNCapVtx_RZ -> SetStats(0);

  /////////////////////////////////////////////////////////

  // neutrino direction: [0.669764, -0.742179, 0.024223]
  // Y = X tan theta_nu
  Double_t Xstart    = -18.;
  Double_t Ystart    = 18.;
  Double_t Xlength   = 6.;
  Double_t Ylength   = Xlength * (-0.742179/0.669764);
  Double_t arrowHead = 0.02;
  TArrow* ar = new TArrow(Xstart, Ystart, Xstart+Xlength, Ystart+Ylength, arrowHead, "|>");
  ar -> SetLineWidth(3);
  ar -> SetLineColor(kGray+2);
  ar -> SetFillColor(kGray+2);

  TLatex* text1 = new TLatex(0.2, 0.81, "#nu beam direction");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);


  gROOT -> SetStyle("Plain");
  //gStyle -> SetPalette(53);  //kDarkBodyRadiator
  gStyle -> SetPalette(51);  //kDeepSea
#if 1
  TCanvas* c1 = new TCanvas("c1","PrmVtx XY", 700, 700);
  c1 -> SetGrid();
  h2_TruePrmVtx_XY -> Draw("COLZ");
  f1_uprFCFV_XY -> Draw("SAME");
  f1_btmFCFV_XY -> Draw("SAME");
  ar    -> Draw();
  text1 -> Draw();

  TCanvas* c2 = new TCanvas("c2","PrmVtx RZ", 700, 700);
  c2 -> SetGrid();
  h2_TruePrmVtx_RZ -> Draw("COLZ");
  f1_uprFCFV_RZ -> Draw("SAME");
  f1_btmFCFV_RZ -> Draw("SAME");
  //f1_brlFCFV_RZ -> Draw("SAME");
  g1_brlFCFV_RZ -> Draw("SAME");
#endif

#if 0
  TCanvas* c1 = new TCanvas("c1","PrmVtx X", 700, 700);
  c1 -> SetGrid();
  h1_TruePrmVtxX -> Draw();
#endif

#if 1
  TCanvas* c3 = new TCanvas("c3","NCapVtx XY", 700, 700);
  c3 -> SetGrid();
  h2_TrueNCapVtx_XY -> Draw("COLZ");
  f1_uprFCFV_XY -> Draw("SAME");
  f1_btmFCFV_XY -> Draw("SAME");
  ar    -> Draw();
  text1 -> Draw();

  TCanvas* c4 = new TCanvas("c4","NCapVtx RZ", 700, 700);
  c4 -> SetGrid();
  h2_TrueNCapVtx_RZ -> Draw("COLZ");
  f1_uprFCFV_RZ -> Draw("SAME");
  f1_btmFCFV_RZ -> Draw("SAME");
  //f1_brlFCFV_RZ -> Draw("SAME");
  g1_brlFCFV_RZ -> Draw("SAME");
#endif
}
