#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5

void PreScanTWIDTH() {
  TFile* fin120 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH120.NHITSTH25.root");
  TFile* fin160 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.NHITSTH25.root");
  TFile* fin200 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");
  TFile* fin240 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH240.NHITSTH25.root");
  TFile* fin280 = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH280.NHITSTH25.root");

  float TWIDTH[SCANPOINTS];
  float eTWIDTH[SCANPOINTS];

  float PreEff[SCANPOINTS];
  float PreHEff[SCANPOINTS];
  float PreGdEff[SCANPOINTS];
  float ePreEff[SCANPOINTS];
  float ePreHEff[SCANPOINTS];
  float ePreGdEff[SCANPOINTS];
  for (int i=0; i<SCANPOINTS; i++) {
    eTWIDTH[i]   = 0.;
    ePreEff[i]   = 0.;
    ePreHEff[i]  = 0.;
    ePreGdEff[i] = 0.;

    switch (i) {
      case 0:
        TWIDTH[i]   = 120;
        PreEff[i]   = 44.4987;
        PreHEff[i]  = 4.06933;
        PreGdEff[i] = 83.9587;
        break;
      case 1:
        TWIDTH[i]   = 160;
        PreEff[i]   = 52.0506;
        PreHEff[i]  = 13.1803;
        PreGdEff[i] = 89.9891;
        break;
      case 2:
        TWIDTH[i]   = 200;
        PreEff[i]   = 56.7773;
        PreHEff[i]  = 23.0365;
        PreGdEff[i] = 88.9142;
        break;
      case 3:
        TWIDTH[i]   = 240;
        PreEff[i]   = 57.7773;
        PreHEff[i]  = 28.9036;
        PreGdEff[i] = 85.9587;
        break;
      case 4:
        TWIDTH[i]   = 280;
        PreEff[i]   = 61.3434;
        PreHEff[i]  = 33.1286;
        PreGdEff[i] = 88.8816;
        break;
    }

    PreEff[i] /= 100.;
    PreHEff[i] /= 100.;
    PreGdEff[i] /= 100.;
  }
  TGraphErrors* g_TWIDTH_x_PreEff   = new TGraphErrors(SCANPOINTS, TWIDTH, PreEff, eTWIDTH, ePreEff);
  TGraphErrors* g_TWIDTH_x_PreHEff  = new TGraphErrors(SCANPOINTS, TWIDTH, PreHEff, eTWIDTH, ePreHEff);
  TGraphErrors* g_TWIDTH_x_PreGdEff = new TGraphErrors(SCANPOINTS, TWIDTH, PreGdEff, eTWIDTH, ePreGdEff);

  g_TWIDTH_x_PreEff   -> SetMarkerColor(kPink-5);
  g_TWIDTH_x_PreEff   -> SetLineColor(kPink-5);
  g_TWIDTH_x_PreEff   -> SetLineWidth(2);
  g_TWIDTH_x_PreEff   -> SetMarkerStyle(20);
  g_TWIDTH_x_PreEff   -> SetMarkerSize(1.5);

  g_TWIDTH_x_PreHEff  -> SetMarkerColor(kAzure-4);
  g_TWIDTH_x_PreHEff  -> SetLineColor(kAzure-4);
  g_TWIDTH_x_PreHEff  -> SetLineWidth(2);
  g_TWIDTH_x_PreHEff  -> SetMarkerStyle(20);
  g_TWIDTH_x_PreHEff  -> SetMarkerSize(1.5);

  g_TWIDTH_x_PreGdEff -> SetMarkerColor(kTeal-5);
  g_TWIDTH_x_PreGdEff -> SetLineColor(kTeal-5);
  g_TWIDTH_x_PreGdEff -> SetLineWidth(2);
  g_TWIDTH_x_PreGdEff -> SetMarkerStyle(20);
  g_TWIDTH_x_PreGdEff -> SetMarkerSize(1.5);

  ////////////////////////////////////////////////////////////////////////////////

  TGraphErrors* g_TWIDTH_x_NNEff[SCANPOINTS];
  g_TWIDTH_x_NNEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;13");
  g_TWIDTH_x_NNEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;13");
  g_TWIDTH_x_NNEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;13");
  g_TWIDTH_x_NNEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;13");
  g_TWIDTH_x_NNEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;13");

  TGraphErrors* g_TWIDTH_x_NNHEff[SCANPOINTS];
  g_TWIDTH_x_NNHEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;14");
  g_TWIDTH_x_NNHEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;14");
  g_TWIDTH_x_NNHEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;14");
  g_TWIDTH_x_NNHEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;14");
  g_TWIDTH_x_NNHEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;14");

  TGraphErrors* g_TWIDTH_x_NNGdEff[SCANPOINTS];
  g_TWIDTH_x_NNGdEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;15");
  g_TWIDTH_x_NNGdEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;15");
  g_TWIDTH_x_NNGdEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;15");
  g_TWIDTH_x_NNGdEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;15");
  g_TWIDTH_x_NNGdEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;15");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_TWIDTH_x_NNEff[iscan]   -> SetLineWidth(2);
    g_TWIDTH_x_NNHEff[iscan]  -> SetLineWidth(2);
    g_TWIDTH_x_NNGdEff[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_TWIDTH_x_NNEff[iscan]   -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_NNEff[iscan]   -> SetLineColor(kViolet+2);
        g_TWIDTH_x_NNHEff[iscan]  -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_NNHEff[iscan]  -> SetLineColor(kViolet+2);
        g_TWIDTH_x_NNGdEff[iscan] -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_NNGdEff[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_TWIDTH_x_NNEff[iscan]   -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_NNEff[iscan]   -> SetLineColor(kAzure+7);
        g_TWIDTH_x_NNHEff[iscan]  -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_NNHEff[iscan]  -> SetLineColor(kAzure+7);
        g_TWIDTH_x_NNGdEff[iscan] -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_NNGdEff[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_TWIDTH_x_NNEff[iscan]   -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_NNEff[iscan]   -> SetLineColor(kSpring-1);
        g_TWIDTH_x_NNHEff[iscan]  -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_NNHEff[iscan]  -> SetLineColor(kSpring-1);
        g_TWIDTH_x_NNGdEff[iscan] -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_NNGdEff[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_TWIDTH_x_NNEff[iscan]   -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_NNEff[iscan]   -> SetLineColor(kOrange-3);
        g_TWIDTH_x_NNHEff[iscan]  -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_NNHEff[iscan]  -> SetLineColor(kOrange-3);
        g_TWIDTH_x_NNGdEff[iscan] -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_NNGdEff[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_TWIDTH_x_NNEff[iscan]   -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_NNEff[iscan]   -> SetLineColor(kPink-5);
        g_TWIDTH_x_NNHEff[iscan]  -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_NNHEff[iscan]  -> SetLineColor(kPink-5);
        g_TWIDTH_x_NNGdEff[iscan] -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_NNGdEff[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }

  ////////////////////////////////////////////////////////////////////////////////

  TGraphErrors* g_TWIDTH_x_Eff[SCANPOINTS];
  g_TWIDTH_x_Eff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;16");
  g_TWIDTH_x_Eff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;16");
  g_TWIDTH_x_Eff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;16");
  g_TWIDTH_x_Eff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;16");
  g_TWIDTH_x_Eff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;16");

  TGraphErrors* g_TWIDTH_x_HEff[SCANPOINTS];
  g_TWIDTH_x_HEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;17");
  g_TWIDTH_x_HEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;17");
  g_TWIDTH_x_HEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;17");
  g_TWIDTH_x_HEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;17");
  g_TWIDTH_x_HEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;17");

  TGraphErrors* g_TWIDTH_x_GdEff[SCANPOINTS];
  g_TWIDTH_x_GdEff[0] = (TGraphErrors*)fin120->Get("NTagAnalysis/Graph;18");
  g_TWIDTH_x_GdEff[1] = (TGraphErrors*)fin160->Get("NTagAnalysis/Graph;18");
  g_TWIDTH_x_GdEff[2] = (TGraphErrors*)fin200->Get("NTagAnalysis/Graph;18");
  g_TWIDTH_x_GdEff[3] = (TGraphErrors*)fin240->Get("NTagAnalysis/Graph;18");
  g_TWIDTH_x_GdEff[4] = (TGraphErrors*)fin280->Get("NTagAnalysis/Graph;18");

  for (int iscan=0; iscan<SCANPOINTS; iscan++) {
    g_TWIDTH_x_Eff[iscan]   -> SetLineWidth(2);
    g_TWIDTH_x_HEff[iscan]  -> SetLineWidth(2);
    g_TWIDTH_x_GdEff[iscan] -> SetLineWidth(2);
    switch (iscan) {
      case 0:
        g_TWIDTH_x_Eff[iscan]   -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_Eff[iscan]   -> SetLineColor(kViolet+2);
        g_TWIDTH_x_HEff[iscan]  -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_HEff[iscan]  -> SetLineColor(kViolet+2);
        g_TWIDTH_x_GdEff[iscan] -> SetMarkerColor(kViolet+2);
        g_TWIDTH_x_GdEff[iscan] -> SetLineColor(kViolet+2);
        break;
      case 1:
        g_TWIDTH_x_Eff[iscan]   -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_Eff[iscan]   -> SetLineColor(kAzure+7);
        g_TWIDTH_x_HEff[iscan]  -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_HEff[iscan]  -> SetLineColor(kAzure+7);
        g_TWIDTH_x_GdEff[iscan] -> SetMarkerColor(kAzure+7);
        g_TWIDTH_x_GdEff[iscan] -> SetLineColor(kAzure+7);
        break;
      case 2:
        g_TWIDTH_x_Eff[iscan]   -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_Eff[iscan]   -> SetLineColor(kSpring-1);
        g_TWIDTH_x_HEff[iscan]  -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_HEff[iscan]  -> SetLineColor(kSpring-1);
        g_TWIDTH_x_GdEff[iscan] -> SetMarkerColor(kSpring-1);
        g_TWIDTH_x_GdEff[iscan] -> SetLineColor(kSpring-1);
        break;
      case 3:
        g_TWIDTH_x_Eff[iscan]   -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_Eff[iscan]   -> SetLineColor(kOrange-3);
        g_TWIDTH_x_HEff[iscan]  -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_HEff[iscan]  -> SetLineColor(kOrange-3);
        g_TWIDTH_x_GdEff[iscan] -> SetMarkerColor(kOrange-3);
        g_TWIDTH_x_GdEff[iscan] -> SetLineColor(kOrange-3);
        break;
      case 4:
        g_TWIDTH_x_Eff[iscan]   -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_Eff[iscan]   -> SetLineColor(kPink-5);
        g_TWIDTH_x_HEff[iscan]  -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_HEff[iscan]  -> SetLineColor(kPink-5);
        g_TWIDTH_x_GdEff[iscan] -> SetMarkerColor(kPink-5);
        g_TWIDTH_x_GdEff[iscan] -> SetLineColor(kPink-5);
        break;
    }
  }


  TCanvas* cPre = new TCanvas("cPre", "cPre", 900, 700);
  cPre -> cd();
  cPre -> SetGrid();
  TH1F* framePre = gPad->DrawFrame(110., 0., 290., 1.);
  framePre -> SetXTitle("Time Width of Hit Cluster Search TWIDTH[nsec]");
  framePre -> SetYTitle("Pre-selection Efficiency");
  framePre -> SetTitleOffset(1.1, "Y");
  g_TWIDTH_x_PreEff   -> Draw("PL");
  g_TWIDTH_x_PreHEff  -> Draw("PL");
  g_TWIDTH_x_PreGdEff -> Draw("PL");

  TLegend* legend1 = new TLegend(0.6, 0.12, 0.89, 0.3);
  legend1 -> SetTextSize(0.03);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{TWIDTH scan(NHITSTH=25)}","");
  legend1 -> AddEntry(g_TWIDTH_x_PreEff, "Gd(n,#gamma)+H(n,#gamma)", "PL");
  legend1 -> AddEntry(g_TWIDTH_x_PreHEff, "H(n,#gamma)", "PL");
  legend1 -> AddEntry(g_TWIDTH_x_PreGdEff, "Gd(n,#gamma)", "PL");
  legend1->SetFillColor(0);
  legend1->Draw();

  TCanvas* cNN = new TCanvas("cNN", "cNN", 900, 700);
  cNN -> cd();
  cNN -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("n-likelihood");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_NNEff[iscan] -> Draw("PL");

  TLegend* legendNN = new TLegend(0.12, 0.12, 0.6, 0.5);
  legendNN -> SetTextSize(0.04);
  legendNN -> AddEntry((TObject*)0,"#kern[-0.25]{TWIDTH scan(NHITSTH=25)}","");
  legendNN -> AddEntry(g_TWIDTH_x_NNEff[0], "TWIDTH = 120 nsec", "PL");
  legendNN -> AddEntry(g_TWIDTH_x_NNEff[1], "TWIDTH = 160 nsec", "PL");
  legendNN -> AddEntry(g_TWIDTH_x_NNEff[2], "TWIDTH = 200 nsec", "PL");
  legendNN -> AddEntry(g_TWIDTH_x_NNEff[3], "TWIDTH = 240 nsec", "PL");
  legendNN -> AddEntry(g_TWIDTH_x_NNEff[4], "TWIDTH = 280 nsec", "PL");
  legendNN -> SetFillColor(0);
  legendNN -> Draw();

  TCanvas* cHNN = new TCanvas("cHNN", "cHNN", 900, 700);
  cHNN -> cd();
  cHNN -> SetGrid();
  TH1F* frameHNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameHNN -> SetXTitle("n-likelihood");
  frameHNN -> SetYTitle("NN H(n, #gamma) Classification Efficiency");
  frameHNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_NNHEff[iscan] -> Draw("PL");
  TLegend* legendHNN = new TLegend(0.4, 0.5, 0.89, 0.89);
  legendHNN -> SetTextSize(0.04);
  legendHNN -> AddEntry((TObject*)0,"#kern[-0.25]{TWIDTH scan(NHITSTH=25)}","");
  legendHNN -> AddEntry(g_TWIDTH_x_NNEff[0], "TWIDTH = 120 nsec", "PL");
  legendHNN -> AddEntry(g_TWIDTH_x_NNEff[1], "TWIDTH = 160 nsec", "PL");
  legendHNN -> AddEntry(g_TWIDTH_x_NNEff[2], "TWIDTH = 200 nsec", "PL");
  legendHNN -> AddEntry(g_TWIDTH_x_NNEff[3], "TWIDTH = 240 nsec", "PL");
  legendHNN -> AddEntry(g_TWIDTH_x_NNEff[4], "TWIDTH = 280 nsec", "PL");
  legendHNN -> SetFillColor(0);
  legendHNN -> Draw();

  TCanvas* cGdNN = new TCanvas("cGdNN", "cGdNN", 900, 700);
  cGdNN -> cd();
  cGdNN -> SetGrid();
  TH1F* frameGdNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameGdNN -> SetXTitle("n-likelihood");
  frameGdNN -> SetYTitle("NN Gd(n, #gamma) Classification Efficiency");
  frameGdNN -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_NNGdEff[iscan] -> Draw("PL");
  TLegend* legendGdNN = new TLegend(0.2, 0.2, 0.68, 0.58);
  legendGdNN -> SetTextSize(0.04);
  legendGdNN -> AddEntry((TObject*)0,"#kern[-0.25]{TWIDTH scan(NHITSTH=25)}","");
  legendGdNN -> AddEntry(g_TWIDTH_x_NNEff[0], "TWIDTH = 120 nsec", "PL");
  legendGdNN -> AddEntry(g_TWIDTH_x_NNEff[1], "TWIDTH = 160 nsec", "PL");
  legendGdNN -> AddEntry(g_TWIDTH_x_NNEff[2], "TWIDTH = 200 nsec", "PL");
  legendGdNN -> AddEntry(g_TWIDTH_x_NNEff[3], "TWIDTH = 240 nsec", "PL");
  legendGdNN -> AddEntry(g_TWIDTH_x_NNEff[4], "TWIDTH = 280 nsec", "PL");
  legendGdNN -> SetFillColor(0);
  legendGdNN -> Draw();


  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> cd();
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_Eff[iscan] -> Draw("PL");
  TLegend* legend = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend -> SetTextSize(0.04);
  legend -> AddEntry((TObject*)0,"#kern[-0.25]{TWIDTH scan(NHITSTH=25)}","");
  legend -> AddEntry(g_TWIDTH_x_NNEff[0], "TWIDTH = 120 nsec", "PL");
  legend -> AddEntry(g_TWIDTH_x_NNEff[1], "TWIDTH = 160 nsec", "PL");
  legend -> AddEntry(g_TWIDTH_x_NNEff[2], "TWIDTH = 200 nsec", "PL");
  legend -> AddEntry(g_TWIDTH_x_NNEff[3], "TWIDTH = 240 nsec", "PL");
  legend -> AddEntry(g_TWIDTH_x_NNEff[4], "TWIDTH = 280 nsec", "PL");
  legend -> SetFillColor(0);
  legend -> Draw();

  TCanvas* cH = new TCanvas("cH", "cH", 900, 700);
  cH -> cd();
  cH -> SetGrid();
  TH1F* frameH = gPad->DrawFrame(0., 0., 1., 1.);
  frameH -> SetXTitle("n-likelihood");
  frameH -> SetYTitle("Overall H(n, #gamma) Tagging Efficiency");
  frameH -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_HEff[iscan] -> Draw("PL");
  legendHNN -> Draw();

  TCanvas* cGd = new TCanvas("cGd", "cGd", 900, 700);
  cGd -> cd();
  cGd -> SetGrid();
  TH1F* frameGd = gPad->DrawFrame(0., 0., 1., 1.);
  frameGd -> SetXTitle("Time Width of Hit Cluster Search TWIDTH[nsec]");
  frameGd -> SetYTitle("Overall Gd(n, #gamma) Tagging Efficiency");
  frameGd -> SetTitleOffset(1.1, "Y");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_TWIDTH_x_GdEff[iscan] -> Draw("PL");
  legendGdNN -> Draw();
  
}
