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

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likethreshold");
  frame -> SetYTitle("Purity (Mis-tagged Noise Rate)");
  frame -> SetTitleOffset(1.1, "Y");
  g_NoiseRate -> Draw("PL");
  g_Purity    -> Draw("SAMEPL");

  TLegend* legend1 = new TLegend(0.5, 0.55, 0.89, 0.75);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  legend1 -> AddEntry(g_Purity, "Purity", "PL");
  legend1 -> AddEntry(g_NoiseRate, "Noise rate", "PL");
  legend1->SetFillColor(0);
  legend1->Draw() ;
}