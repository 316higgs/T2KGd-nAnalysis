#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"


void Simpledtn50() {

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TH2D* h2_dtn50 = (TH2D*)fin->Get("DecayeBox/h2_dtn50");
  h2_dtn50 -> SetStats(0);
  //h2_dtn50 -> GetYaxis()->SetLabelSize(0.045);
  h2_dtn50 -> SetTitleOffset(1.3, "Y");
  //h2_dtn50 -> GetXaxis()->SetLabelSize(0.045);
  h2_dtn50 -> SetTitleOffset(1.2, "X");
  h2_dtn50 -> SetXTitle("Timing difference from the prompt event dt [#musec]");
  h2_dtn50 -> SetYTitle("#hits in 50 nsec time window N50");

  //TF1* f1_upr = new TF1("f1_upr", "400.", 0., 10.);
  TF1* f1_btm = new TF1("f1_btm", "4*x+30.0", 1.5, 20.);
  //f1_upr -> SetLineStyle(7);
  //f1_upr -> SetLineWidth(3);
  //f1_upr -> SetLineColor(kOrange+7);
  f1_btm -> SetLineStyle(7);
  f1_btm -> SetLineWidth(3);
  f1_btm -> SetLineColor(kOrange+7);
  float x1[2] = {1.5, 1.5};
  float y1[2] = {0., 36.0};
  TGraph* g1_side1 = new TGraph(2, x1, y1);
  g1_side1 -> SetLineStyle(7);
  g1_side1 -> SetLineWidth(3);
  g1_side1 -> SetLineColor(kOrange+7);
  float x2[2] = {20., 20.};
  float y2[2] = {110., 400.};
  TGraph* g1_side2 = new TGraph(2, x2, y2);
  g1_side2 -> SetLineStyle(7);
  g1_side2 -> SetLineWidth(3);
  g1_side2 -> SetLineColor(kOrange+7);
  g1_side2 -> SetLineStyle(7);
  g1_side2 -> SetLineWidth(3);
  g1_side2 -> SetLineColor(kOrange+7);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 700);
  c1 -> SetGrid();
  h2_dtn50 -> Draw("COLZ");
  f1_btm -> Draw("SAME");
  //f1_upr -> Draw("SAME");
  g1_side1 -> Draw("SAME");
  g1_side2 -> Draw("SAME");

  TLatex* text1 = new TLatex(0.44, 0.85, "C1-C4 applied");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);
  text1 -> Draw();
  TLatex* text2 = new TLatex(0.44, 0.8, "Normalized with ##nu events@C1-C4");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.045);
  text2 -> Draw();
  TLatex* text3 = new TLatex(0.44, 0.7, "Decay-e definition:");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.045);
  text3 -> Draw();
  TLatex* text4 = new TLatex(0.44, 0.65, "- All for dt < 1.5 #musec");
  text4 -> SetNDC(1);
  text4 -> SetTextSize(0.045);
  text4 -> Draw();
  TLatex* text5 = new TLatex(0.44, 0.6, "- dt < 0.25#upointN50-7.5");
  text5 -> SetNDC(1);
  text5 -> SetTextSize(0.045);
  text5 -> Draw();
  TLatex* text5 = new TLatex(0.44, 0.55, "  for 1.5 #musec < dt < 20 #musec");
  text5 -> SetNDC(1);
  text5 -> SetTextSize(0.045);
  text5 -> Draw();
}