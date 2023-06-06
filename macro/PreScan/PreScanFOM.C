#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void PreScanFOM() {
  TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_FOM_scn1 = (TGraphErrors*)fin1->Get("NTagAnalysis/Graph;22");
  g_FOM_scn1 -> SetMarkerColor(kAzure+5);
  g_FOM_scn1 -> SetLineColor(kAzure+5);
  g_FOM_scn1 -> SetMarkerStyle(20);
  g_FOM_scn1 -> SetMarkerSize(1.5);
  g_FOM_scn1 -> SetLineWidth(2);

  float OptThr = 0.45;
  float MaxFOM = 115.74;

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",1000,700);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 130.);
  frame -> SetXTitle("n-likethreshold");
  frame -> SetYTitle("Figure of Merit  S/#sqrt{S+B}");
  frame -> SetTitleOffset(1.1, "Y");
  frame -> GetXaxis()->SetLabelSize(0.03);
  frame -> GetYaxis()->SetLabelSize(0.03);
  g_FOM_scn1 -> Draw("PL");
  
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