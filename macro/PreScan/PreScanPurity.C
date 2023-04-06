#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5

void PreScanPurity() {
#if 0
  TFile* fin120 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH120.NHITSTH25.root");
  TFile* fin160 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.NHITSTH25.root");
  TFile* fin200 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH240.NHITSTH25.root");
  TFile* fin280 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH280.NHITSTH25.root");
#endif

#if 1
  TFile* fin120 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH10.root");
  TFile* fin160 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH15.root");
  TFile* fin200 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH35.root");
  TFile* fin280 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH45.root");
#endif
  
  TGraphErrors* g_Purity[SCANPOINTS];
  g_Purity[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;19");
  g_Purity[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;19");
  g_Purity[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;19");
  g_Purity[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;19");
  g_Purity[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;19");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_Purity[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_Purity[iscan] -> SetMarkerColor(kViolet+2);
        g_Purity[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_Purity[iscan] -> SetMarkerColor(kAzure+7);
        g_Purity[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_Purity[iscan] -> SetMarkerColor(kSpring-1);
        g_Purity[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_Purity[iscan] -> SetMarkerColor(kOrange-3);
        g_Purity[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_Purity[iscan] -> SetMarkerColor(kPink-5);
        g_Purity[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetMinimum(0.7);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Tagging Purity");
  frame -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_Purity[iscan]->Draw("SAMEPL");

  TLegend* legend1 = new TLegend(0.3, 0.2, 0.89, 0.65);
  legend1 -> SetTextSize(0.04);
#if 0
  legend1->AddEntry((TObject*)0,"#kern[-0.25]{Pre-selection TWIDTH scan(NHITSTH=25)}","");
  legend1 -> AddEntry(g_Purity[0], "TWIDTH = 120 nsec", "PL");
  legend1 -> AddEntry(g_Purity[1], "TWIDTH = 160 nsec", "PL");
  legend1 -> AddEntry(g_Purity[2], "TWIDTH = 200 nsec", "PL");
  legend1 -> AddEntry(g_Purity[3], "TWIDTH = 240 nsec", "PL");
  legend1 -> AddEntry(g_Purity[4], "TWIDTH = 280 nsec", "PL");
#endif
#if 1
  legend1->AddEntry((TObject*)0,"#kern[-0.25]{Pre-selection NHITSTH scan(TWIDTH=200 ns)}","");
  legend1 -> AddEntry(g_Purity[0], "NHITSTH = 10", "PL");
  legend1 -> AddEntry(g_Purity[1], "NHITSTH = 15", "PL");
  legend1 -> AddEntry(g_Purity[2], "NHITSTH = 25", "PL");
  legend1 -> AddEntry(g_Purity[3], "NHITSTH = 35", "PL");
  legend1 -> AddEntry(g_Purity[4], "NHITSTH = 45", "PL");
#endif
  legend1->SetFillColor(0);
  legend1->Draw();
}