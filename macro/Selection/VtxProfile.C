#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NNAPPLY 1  // 0 for pre-NN, 1 for post-NN

void VtxProfile() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");

  //  primary vertex
  TH2F* h2_PrmVtx_XY = (TH2F*)fin->Get("NeutrinoOscillation/h2_PrmVtxXY");
  TH2F* h2_PrmVtx_RZ = (TH2F*)fin->Get("NeutrinoOscillation/h2_PrmVtxRZ");
  h2_PrmVtx_XY -> SetStats(0);
  h2_PrmVtx_RZ -> SetStats(0);
  h2_PrmVtx_XY -> SetXTitle("Primary vertex X [m]");
  h2_PrmVtx_XY -> SetYTitle("Primary vertex Y [m]");
  h2_PrmVtx_RZ -> SetXTitle("Primary vertex R^{2} [m^{2}]");
  h2_PrmVtx_RZ -> SetYTitle("Primary vertex Z [m]");

  TH1D* h1_PrmVtxX = h2_PrmVtx_XY->ProjectionX("h1_PrmVtxX");
  TH1D* h1_PrmVtxY = h2_PrmVtx_XY->ProjectionY("h1_PrmVtxY");

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

  //  capture vertex
#if 1
  TString DirName   = "NTagAnalysis/";
  TString HistName  = "h2_NCapVtx";
  TString projXY    = "XY";
  TString projRZ    = "RZ";
  TString NNmode    = TString::Format("_NN%d", NNAPPLY);
  TH2F* h2_NCapVtx_XY = (TH2F*)fin->Get(DirName+HistName+projXY+NNmode);
  TH2F* h2_NCapVtx_RZ = (TH2F*)fin->Get(DirName+HistName+projRZ+NNmode);
  h2_PrmVtx_XY -> SetStats(0);
  h2_NCapVtx_RZ -> SetStats(0);
  h2_NCapVtx_XY -> SetXTitle("Neutron capture vertex X [m]");
  h2_NCapVtx_XY -> SetYTitle("Neutron capture vertex Y [m]");
  h2_NCapVtx_RZ -> SetXTitle("Neutron capture vertex R^{2} [m^{2}]");
  h2_NCapVtx_RZ -> SetYTitle("Neutron capture vertex Z [m]");
  h2_NCapVtx_XY -> SetStats(0);
  h2_NCapVtx_RZ -> SetStats(0);
#endif

  /////////////////////////////////////////////////////////

  // neutrino direction: [0.669764, -0.742179, 0.024223]
  // Y = X tan theta_nu
  Double_t XstartXY  = -18.;
  Double_t YstartXY  = 18.;
  Double_t XlengthXY = 6.;
  Double_t YlengthXY = XlengthXY * (-0.742179/0.669764);
  Double_t arrowHead = 0.02;
  TArrow* arXY = new TArrow(XstartXY, YstartXY, XstartXY+XlengthXY, YstartXY+YlengthXY, arrowHead, "|>");
  arXY -> SetLineWidth(3);
  arXY -> SetLineColor(kGray+2);
  arXY -> SetFillColor(kGray+2);

  TLatex* text1 = new TLatex(0.2, 0.81, "#nu beam direction");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);

  Double_t XstartRZ  = 360;
  Double_t YstartRZ  = 0.;
  Double_t XlengthRZ = 60.;
  Double_t YlengthRZ = XlengthRZ * (0.024223/std::sqrt(0.669764*0.669764 + 0.742179*0.742179) );
  TArrow* arRZ = new TArrow(XstartRZ, YstartRZ, XstartRZ-XlengthRZ, YstartRZ+YlengthRZ, arrowHead, "|>");
  arRZ -> SetLineWidth(3);
  arRZ -> SetLineColor(kGray+2);
  arRZ -> SetFillColor(kGray+2);

  TLatex* text2 = new TLatex(0.68, 0.45, "#nu beam");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.045);

  TLatex* text3 = new TLatex(0.67, 0.41, "direction");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.045);

  TLatex* text4 = new TLatex(0.65, 0.91, "FCFV applied");
  text4 -> SetNDC(1);
  text4 -> SetTextSize(0.045);

  TString NNapplymode = "pre-NN";
  if (NNAPPLY==1) NNapplymode = "post-NN";
  TLatex* text5 = new TLatex(0.65, 0.95, NNapplymode);
  text5 -> SetNDC(1);
  text5 -> SetTextSize(0.045);




  //gStyle -> SetPalette(53);  //kDarkBodyRadiator
  gStyle -> SetPalette(51);  //kDeepSea
  gROOT -> SetStyle("Plain");
#if 0
  TCanvas* c1 = new TCanvas("c1","PrmVtx XY", 700, 700);
  c1 -> SetGrid();
  h2_PrmVtx_XY -> Draw("COLZ");
  f1_uprFCFV_XY -> Draw("SAME");
  f1_btmFCFV_XY -> Draw("SAME");
  arXY    -> Draw();
  text1 -> Draw();
  text4 -> Draw();

  TCanvas* c2 = new TCanvas("c2","PrmVtx RZ", 700, 700);
  c2 -> SetGrid();
  h2_PrmVtx_RZ -> Draw("COLZ");
  f1_uprFCFV_RZ -> Draw("SAME");
  f1_btmFCFV_RZ -> Draw("SAME");
  //f1_brlFCFV_RZ -> Draw("SAME");
  g1_brlFCFV_RZ -> Draw("SAME");
  text4 -> Draw();
  //arRZ -> Draw();
  //text2 -> Draw();
  //text3 -> Draw();
#endif

#if 0
  TCanvas* c1 = new TCanvas("c1","PrmVtx X", 700, 700);
  c1 -> SetGrid();
  h1_PrmVtxX -> Draw();
#endif

#if 1
  TCanvas* c3 = new TCanvas("c3","NCapVtx XY", 700, 700);
  c3 -> SetGrid();
  h2_NCapVtx_XY -> Draw("COLZ");
  f1_uprFCFV_XY -> Draw("SAME");
  f1_btmFCFV_XY -> Draw("SAME");
  arXY    -> Draw();
  text1 -> Draw();
  text4 -> Draw();
  text5 -> Draw();

  TCanvas* c4 = new TCanvas("c4","NCapVtx RZ", 700, 700);
  c4 -> SetGrid();
  h2_NCapVtx_RZ -> Draw("COLZ");
  f1_uprFCFV_RZ -> Draw("SAME");
  f1_btmFCFV_RZ -> Draw("SAME");
  //f1_brlFCFV_RZ -> Draw("SAME");
  g1_brlFCFV_RZ -> Draw("SAME");
  text4 -> Draw();
  text5 -> Draw();
#endif
}
