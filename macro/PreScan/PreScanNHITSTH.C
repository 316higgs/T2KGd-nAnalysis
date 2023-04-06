#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5

void PreScanNHITSTH() {
  TFile* fin120 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH10.root");
  TFile* fin160 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH15.root");
  TFile* fin200 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH35.root");
  TFile* fin280 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH45.root");

  float NHITSTH[SCANPOINTS];
  float eNHITSTH[SCANPOINTS];

  float PreEff[SCANPOINTS];
  float PreHEff[SCANPOINTS];
  float PreGdEff[SCANPOINTS];
  float ePreEff[SCANPOINTS];
  float ePreHEff[SCANPOINTS];
  float ePreGdEff[SCANPOINTS];
  for (int i=0; i<SCANPOINTS; i++) {
    eNHITSTH[i]   = 0.;
    ePreEff[i]   = 0.;
    ePreHEff[i]  = 0.;
    ePreGdEff[i] = 0.;

    switch (i) {
      case 0:
        NHITSTH[i]   = 10;
        PreEff[i]   = 68.2667;
        PreHEff[i]  = 41.541;
        PreGdEff[i] = 94.3518;
        break;
      case 1:
        NHITSTH[i]   = 15;
        PreEff[i]   = 59.1718;
        PreHEff[i]  = 32.5068;
        PreGdEff[i] = 90.6488;
        break;
      case 2:
        NHITSTH[i]   = 25;
        PreEff[i]   = 56.375;
        PreHEff[i]  = 23.0365;
        PreGdEff[i] = 88.9142;
        break;
      case 3:
        NHITSTH[i]   = 35;
        PreEff[i]   = 39.0501;
        PreHEff[i]  = 2.29831;
        PreGdEff[i] = 74.9207;
        break;
      case 4:
        NHITSTH[i]   = 45;
        PreEff[i]   = 20.8295;
        PreHEff[i]  = 0.0912206;
        PreGdEff[i] = 41.0706;
        break;
    }

    PreEff[i] /= 100.;
    PreHEff[i] /= 100.;
    PreGdEff[i] /= 100.;
  }
  TGraphErrors* g_NHITSTH_x_PreEff   = new TGraphErrors(SCANPOINTS, NHITSTH, PreEff, eNHITSTH, ePreEff);
  TGraphErrors* g_NHITSTH_x_PreHEff  = new TGraphErrors(SCANPOINTS, NHITSTH, PreHEff, eNHITSTH, ePreHEff);
  TGraphErrors* g_NHITSTH_x_PreGdEff = new TGraphErrors(SCANPOINTS, NHITSTH, PreGdEff, eNHITSTH, ePreGdEff);

  g_NHITSTH_x_PreEff   -> SetMarkerColor(kPink-5);
  g_NHITSTH_x_PreEff   -> SetLineColor(kPink-5);
  g_NHITSTH_x_PreEff   -> SetLineWidth(2);
  g_NHITSTH_x_PreEff   -> SetMarkerStyle(20);
  g_NHITSTH_x_PreEff   -> SetMarkerSize(1.5);

  g_NHITSTH_x_PreHEff  -> SetMarkerColor(kAzure-4);
  g_NHITSTH_x_PreHEff  -> SetLineColor(kAzure-4);
  g_NHITSTH_x_PreHEff  -> SetLineWidth(2);
  g_NHITSTH_x_PreHEff  -> SetMarkerStyle(20);
  g_NHITSTH_x_PreHEff  -> SetMarkerSize(1.5);

  g_NHITSTH_x_PreGdEff -> SetMarkerColor(kTeal-5);
  g_NHITSTH_x_PreGdEff -> SetLineColor(kTeal-5);
  g_NHITSTH_x_PreGdEff -> SetLineWidth(2);
  g_NHITSTH_x_PreGdEff -> SetMarkerStyle(20);
  g_NHITSTH_x_PreGdEff -> SetMarkerSize(1.5);

  ////////////////////////////////////////////////////////////////////////////////

  TGraphErrors* g_NHITSTH_x_NNEff[SCANPOINTS];
  g_NHITSTH_x_NNEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;13");

  TGraphErrors* g_NHITSTH_x_NNHEff[SCANPOINTS];
  g_NHITSTH_x_NNHEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;14");

  TGraphErrors* g_NHITSTH_x_NNGdEff[SCANPOINTS];
  g_NHITSTH_x_NNGdEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;15");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_NHITSTH_x_NNEff[iscan]   -> SetLineWidth(2);
    g_NHITSTH_x_NNHEff[iscan]  -> SetLineWidth(2);
    g_NHITSTH_x_NNGdEff[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_NHITSTH_x_NNEff[iscan]   -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_NNEff[iscan]   -> SetLineColor(kViolet+2);
        g_NHITSTH_x_NNHEff[iscan]  -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_NNHEff[iscan]  -> SetLineColor(kViolet+2);
        g_NHITSTH_x_NNGdEff[iscan] -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_NNGdEff[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_NHITSTH_x_NNEff[iscan]   -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_NNEff[iscan]   -> SetLineColor(kAzure+7);
        g_NHITSTH_x_NNHEff[iscan]  -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_NNHEff[iscan]  -> SetLineColor(kAzure+7);
        g_NHITSTH_x_NNGdEff[iscan] -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_NNGdEff[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_NHITSTH_x_NNEff[iscan]   -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_NNEff[iscan]   -> SetLineColor(kSpring-1);
        g_NHITSTH_x_NNHEff[iscan]  -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_NNHEff[iscan]  -> SetLineColor(kSpring-1);
        g_NHITSTH_x_NNGdEff[iscan] -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_NNGdEff[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_NHITSTH_x_NNEff[iscan]   -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_NNEff[iscan]   -> SetLineColor(kOrange-3);
        g_NHITSTH_x_NNHEff[iscan]  -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_NNHEff[iscan]  -> SetLineColor(kOrange-3);
        g_NHITSTH_x_NNGdEff[iscan] -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_NNGdEff[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_NHITSTH_x_NNEff[iscan]   -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_NNEff[iscan]   -> SetLineColor(kPink-5);
        g_NHITSTH_x_NNHEff[iscan]  -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_NNHEff[iscan]  -> SetLineColor(kPink-5);
        g_NHITSTH_x_NNGdEff[iscan] -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_NNGdEff[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  TGraphErrors* g_NHITSTH_x_Eff[SCANPOINTS];
  g_NHITSTH_x_Eff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;16");

  TGraphErrors* g_NHITSTH_x_HEff[SCANPOINTS];
  g_NHITSTH_x_HEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;17");

  TGraphErrors* g_NHITSTH_x_GdEff[SCANPOINTS];
  g_NHITSTH_x_GdEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;18");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_NHITSTH_x_Eff[iscan]   -> SetLineWidth(2);
    g_NHITSTH_x_HEff[iscan]  -> SetLineWidth(2);
    g_NHITSTH_x_GdEff[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_NHITSTH_x_Eff[iscan]   -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_Eff[iscan]   -> SetLineColor(kViolet+2);
        g_NHITSTH_x_HEff[iscan]  -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_HEff[iscan]  -> SetLineColor(kViolet+2);
        g_NHITSTH_x_GdEff[iscan] -> SetMarkerColor(kViolet+2);
        g_NHITSTH_x_GdEff[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_NHITSTH_x_Eff[iscan]   -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_Eff[iscan]   -> SetLineColor(kAzure+7);
        g_NHITSTH_x_HEff[iscan]  -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_HEff[iscan]  -> SetLineColor(kAzure+7);
        g_NHITSTH_x_GdEff[iscan] -> SetMarkerColor(kAzure+7);
        g_NHITSTH_x_GdEff[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_NHITSTH_x_Eff[iscan]   -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_Eff[iscan]   -> SetLineColor(kSpring-1);
        g_NHITSTH_x_HEff[iscan]  -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_HEff[iscan]  -> SetLineColor(kSpring-1);
        g_NHITSTH_x_GdEff[iscan] -> SetMarkerColor(kSpring-1);
        g_NHITSTH_x_GdEff[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_NHITSTH_x_Eff[iscan]   -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_Eff[iscan]   -> SetLineColor(kOrange-3);
        g_NHITSTH_x_HEff[iscan]  -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_HEff[iscan]  -> SetLineColor(kOrange-3);
        g_NHITSTH_x_GdEff[iscan] -> SetMarkerColor(kOrange-3);
        g_NHITSTH_x_GdEff[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_NHITSTH_x_Eff[iscan]   -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_Eff[iscan]   -> SetLineColor(kPink-5);
        g_NHITSTH_x_HEff[iscan]  -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_HEff[iscan]  -> SetLineColor(kPink-5);
        g_NHITSTH_x_GdEff[iscan] -> SetMarkerColor(kPink-5);
        g_NHITSTH_x_GdEff[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }


  TCanvas* cPre = new TCanvas("cPre", "cPre", 900, 700);
  cPre -> cd();
  cPre -> SetGrid();
  TH1F* framePre = gPad->DrawFrame(5., 0., 50., 1.);
  framePre -> SetXTitle("n-likelihood");
  framePre -> SetYTitle("Pre-selection Efficiency");
  framePre -> SetTitleOffset(1.1, "Y");
  g_NHITSTH_x_PreEff   -> Draw("PL");
  g_NHITSTH_x_PreHEff  -> Draw("PL");
  g_NHITSTH_x_PreGdEff -> Draw("PL");

  TLegend* legend1 = new TLegend(0.56, 0.75, 0.89, 0.93);
  legend1 -> SetTextSize(0.03);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan(TWIDTH=200 ns)}","");
  legend1 -> AddEntry(g_NHITSTH_x_PreEff, "Gd(n,#gamma)+H(n,#gamma)", "PL");
  legend1 -> AddEntry(g_NHITSTH_x_PreHEff, "H(n,#gamma)", "PL");
  legend1 -> AddEntry(g_NHITSTH_x_PreGdEff, "Gd(n,#gamma)", "PL");
  legend1->SetFillColor(0);
  legend1->Draw();

  TCanvas* cNN = new TCanvas("cNN", "cNN", 900, 700);
  cNN -> cd();
  cNN -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("n-likelihood");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNEff[iscan] -> Draw("PL");

  TLegend* legendNN = new TLegend(0.12, 0.12, 0.6, 0.5);
  legendNN -> SetTextSize(0.04);
  legendNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan(TWIDTH=200 ns)}","");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 10", "PL");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 15", "PL");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25", "PL");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 35", "PL");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 45", "PL");
  legendNN -> SetFillColor(0);
  legendNN -> Draw();

  TCanvas* cHNN = new TCanvas("cHNN", "cHNN", 900, 700);
  cHNN -> cd();
  cHNN -> SetGrid();
  TH1F* frameHNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameHNN -> SetXTitle("n-likelihood");
  frameHNN -> SetYTitle("NN H(n, #gamma) Classification Efficiency");
  frameHNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNHEff[iscan] -> Draw("PL");
  TLegend* legendHNN = new TLegend(0.4, 0.5, 0.89, 0.89);
  legendHNN -> SetTextSize(0.04);
  legendHNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan(TWIDTH=200 ns)}","");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 10", "PL");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 15", "PL");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25", "PL");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 35", "PL");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 45", "PL");
  legendHNN -> SetFillColor(0);
  legendHNN -> Draw();

  TCanvas* cGdNN = new TCanvas("cGdNN", "cGdNN", 900, 700);
  cGdNN -> cd();
  cGdNN -> SetGrid();
  TH1F* frameGdNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameGdNN -> SetXTitle("n-likelihood");
  frameGdNN -> SetYTitle("NN Gd(n, #gamma) Classification Efficiency");
  frameGdNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNGdEff[iscan] -> Draw("PL");
  TLegend* legendGdNN = new TLegend(0.2, 0.2, 0.68, 0.58);
  legendGdNN -> SetTextSize(0.04);
  legendGdNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan(TWIDTH=200 ns)}","");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 10", "PL");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 15", "PL");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25", "PL");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 35", "PL");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 45", "PL");
  legendGdNN -> SetFillColor(0);
  legendGdNN -> Draw();


  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> cd();
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_Eff[iscan] -> Draw("PL");
  TLegend* legend = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend -> SetTextSize(0.04);
  legend -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan(TWIDTH=200 ns)}","");
  legend -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 10", "PL");
  legend -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 15", "PL");
  legend -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25", "PL");
  legend -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 35", "PL");
  legend -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 45", "PL");
  legend -> SetFillColor(0);
  legend -> Draw();

  TCanvas* cH = new TCanvas("cH", "cH", 900, 700);
  cH -> cd();
  cH -> SetGrid();
  TH1F* frameH = gPad->DrawFrame(0., 0., 1., 1.);
  frameH -> SetXTitle("n-likelihood");
  frameH -> SetYTitle("Overall H(n, #gamma) Tagging Efficiency");
  frameH -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_HEff[iscan] -> Draw("PL");
  legendHNN -> Draw();

  TCanvas* cGd = new TCanvas("cGd", "cGd", 900, 700);
  cGd -> cd();
  cGd -> SetGrid();
  TH1F* frameGd = gPad->DrawFrame(0., 0., 1., 1.);
  frameGd -> SetXTitle("Threshold of Hit Cluster NHITSTH[nsec]");
  frameGd -> SetYTitle("Overall Gd(n, #gamma) Tagging Efficiency");
  frameGd -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_GdEff[iscan] -> Draw("PL");
  legendGdNN -> Draw();
  
}
