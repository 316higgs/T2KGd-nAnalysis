#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Purity() {
  //TFile* fin   = new TFile("../../output/test.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_Purity    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;19");
  TGraphErrors* g_NoiseRate = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;1");
  g_Purity    -> SetLineWidth(2);
  g_NoiseRate -> SetLineWidth(2);
  //g_NoiseRate -> RemovePoint(20);

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c", 900, 700);
  c -> SetGrid();
  //c -> SetLogy();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likethreshold");
  frame -> SetYTitle("Mis-tagged Noise Rate & Purity");
  frame -> SetTitleOffset(1.2, "Y");
  frame -> GetYaxis()->SetLabelSize(0.035);
  frame -> GetYaxis()->SetLabelColor(kViolet-7);
  frame -> GetXaxis()->SetLabelSize(0.035);
  frame -> GetXaxis()->SetTitleSize(0.035);
  frame -> GetYaxis()->SetTitleSize(0.035);
  //frame -> GetYaxis()->SetTitleColor(kViolet-7);
  g_NoiseRate -> Draw("L");
  g_Purity    -> Draw("SAMEL");

  float xMinPos = 1; // x-minimum where you want to set
  float xMaxPos = 1; // x-maximum where you want to set
  float yMinPos = 0; // y-minimum where you want to set
  float yMaxPos = 1; // y-maximum where you want to set
  float SetPos  = 1;
  TGaxis* axis = new TGaxis(xMinPos,yMinPos,xMaxPos,yMaxPos, 0, SetPos, 510, "+L");
  //axis -> SetTitle("Purity");
  //axis -> SetTitleSize(0.035);
  //axis -> SetTitleColor(kPink-5);
  axis -> SetLabelColor(kPink-5);
  axis -> SetLabelSize(0.035);
  axis -> Draw();

  TLegend* legend1 = new TLegend(0.45, 0.55, 0.84, 0.75);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  legend1 -> AddEntry(g_Purity, "Purity", "PL");
  legend1 -> AddEntry(g_NoiseRate, "Noise rate", "PL");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;
}