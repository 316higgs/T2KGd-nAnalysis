#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void ROC() {
  //TFile* fin   = new TFile("../../output/test.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_ROC = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;21");
  g_ROC -> SetMarkerColor(kAzure+5);
  g_ROC -> SetLineColor(kAzure+5);
  g_ROC -> SetMarkerStyle(20);
  g_ROC -> SetMarkerSize(1.0);
  g_ROC -> SetLineWidth(2);

  // slope = TPR@0.05 / FPR@0.05
  //TF1* f1 = new TF1("worstROC", "1344.15*x", 0., 0.0004);
  TF1* f1 = new TF1("worstROC", "13.4397*x", 0., 0.05);
  f1 -> SetLineColor(kOrange+1);
  f1 -> SetLineStyle(7);

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  //TH1F* frame = gPad->DrawFrame(0., 0., 0.0004, 0.5);
  TH1F* frame = gPad->DrawFrame(0., 0., 0.05, 0.65);
  frame -> SetXTitle("False Positive Rate");
  frame -> SetYTitle("True Positive Rate");
  ((TGaxis*)frame->GetXaxis())->SetMaxDigits(3);
  frame -> GetYaxis()->SetLabelSize(0.035);
  frame -> GetXaxis()->SetLabelSize(0.035);
  frame -> SetTitleOffset(1.3, "Y");
  f1 -> Draw("SAME");
  g_ROC -> Draw("SAMEPL");
  

  TLegend* legend1 = new TLegend(0.35, 0.15, 0.89, 0.3);
  legend1 -> SetTextSize(0.03);
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC #nu_{#mu}#rightarrow#nu_{#mu} (n-likelihood is [0.05, 1])}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC #nu_{#mu}#rightarrow#nu_{#mu} (n-likelihood is [0, 1])}","");
  legend1 -> AddEntry(g_ROC, "ROC curve", "PL");
  legend1 -> AddEntry(f1, "Lowest validity ROC(AUC=0.5)", "PL");
  legend1->SetFillColor(0);
  legend1->Draw() ;
}