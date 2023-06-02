#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void FOM() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_FOM = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;22");
  g_FOM -> SetMarkerColor(kAzure+5);
  g_FOM -> SetLineColor(kAzure+5);
  g_FOM -> SetMarkerStyle(20);
  g_FOM -> SetMarkerSize(1.5);
  g_FOM -> SetLineWidth(2);

  float OptThr = 0.4;
  float MaxFOM = 116.309;
  
  float yC1[2] = {0., 200.};
  float xC1[2] = {OptThr, OptThr};
  TGraph* g_C1 = new TGraph(2, xC1, yC1);
  g_C1 -> SetLineWidth(2);
  g_C1 -> SetLineColor(kViolet-8);
  g_C1 -> SetLineStyle(7);

  float yC2[2] = {MaxFOM, MaxFOM};
  float xC2[2] = {0., 1.};
  TGraph* g_C2 = new TGraph(2, xC2, yC2);
  g_C2 -> SetLineWidth(2);
  g_C2 -> SetLineColor(kViolet-8);
  g_C2 -> SetLineStyle(7);

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 130.);
  frame -> SetXTitle("n-likethreshold");
  frame -> SetYTitle("Figure of Merit  S/#sqrt{S+B}");
  frame -> SetTitleOffset(1.1, "Y");
  frame -> GetXaxis()->SetLabelSize(0.03);
  frame -> GetYaxis()->SetLabelSize(0.03);
  g_FOM -> Draw("PL");
  g_C1  -> Draw("SAMEL");
  g_C2  -> Draw("SAMEL");

  /*
  TLegend* legend1 = new TLegend(0.5, 0.55, 0.89, 0.75);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  legend1 -> AddEntry(g_Purity, "Purity", "PL");
  legend1 -> AddEntry(g_NoiseRate, "Noise rate", "PL");
  legend1->SetFillColor(0);
  legend1->Draw();
  */
}