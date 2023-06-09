#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5

void PreScanNoiseRate() {
#if 0
  TFile* fin120 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH120.NHITSTH25.root");
  TFile* fin160 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.NHITSTH25.root");
  TFile* fin200 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH240.NHITSTH25.root");
  TFile* fin280 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH280.NHITSTH25.root");
#endif

#if 1
  TFile* fin_scn1 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH15.root");
  TFile* fin_scn2 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH20.root");
  TFile* fin_scn3 = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  TFile* fin_scn4 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH30.root");
  TFile* fin_scn5 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH35.root");
#endif
  
  TGraphErrors* g_NoiseRate[SCANPOINTS];
  g_NoiseRate[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;20");
  g_NoiseRate[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;20");
  g_NoiseRate[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;20");
  g_NoiseRate[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;20");
  g_NoiseRate[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;20");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_NoiseRate[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_NoiseRate[iscan] -> SetMarkerColor(kViolet+2);
        g_NoiseRate[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_NoiseRate[iscan] -> SetMarkerColor(kAzure+7);
        g_NoiseRate[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_NoiseRate[iscan] -> SetMarkerColor(kSpring-1);
        g_NoiseRate[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_NoiseRate[iscan] -> SetMarkerColor(kOrange-3);
        g_NoiseRate[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_NoiseRate[iscan] -> SetMarkerColor(kPink-5);
        g_NoiseRate[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  //frame -> SetMaximum(0.1);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Mis-tagged Noise Rate");
  frame -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NoiseRate[iscan]->Draw("SAMEL");

  TLegend* legend1 = new TLegend(0.3, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
#if 0
  legend1->AddEntry((TObject*)0,"#kern[-0.25]{Pre-selection TWIDTH scan(NHITSTH=25)}","");
  legend1 -> AddEntry(g_NoiseRate[0], "TWIDTH = 120 nsec", "PL");
  legend1 -> AddEntry(g_NoiseRate[1], "TWIDTH = 160 nsec", "PL");
  legend1 -> AddEntry(g_NoiseRate[2], "TWIDTH = 200 nsec", "PL");
  legend1 -> AddEntry(g_NoiseRate[3], "TWIDTH = 240 nsec", "PL");
  legend1 -> AddEntry(g_NoiseRate[4], "TWIDTH = 280 nsec", "PL");
#endif
#if 1
  legend1->AddEntry((TObject*)0,"#kern[-0.25]{Pre-selection NHITSTH scan(TWIDTH=200 ns)}","");
  legend1 -> AddEntry(g_NoiseRate[0], "NHITSTH = 15", "PL");
  legend1 -> AddEntry(g_NoiseRate[1], "NHITSTH = 20", "PL");
  legend1 -> AddEntry(g_NoiseRate[2], "NHITSTH = 25 (nominal)", "PL");
  legend1 -> AddEntry(g_NoiseRate[3], "NHITSTH = 30", "PL");
  legend1 -> AddEntry(g_NoiseRate[4], "NHITSTH = 35", "PL");
#endif
  legend1->SetFillColor(0);
  legend1->Draw();
}