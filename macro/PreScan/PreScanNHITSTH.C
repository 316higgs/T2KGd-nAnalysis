#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5

void PreScanNHITSTH() {
  TFile* fin_scn1 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH15.root");
  TFile* fin_scn2 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH20.root");
  TFile* fin_scn3 = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  TFile* fin_scn4 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH30.root");
  TFile* fin_scn5 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH35.root");

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
        NHITSTH[i]   = 15;
        PreEff[i]   = 74.7672;
        PreHEff[i]  = 53.9946;
        PreGdEff[i] = 95.1158;
        break;
      case 1:
        NHITSTH[i]   = 20;
        PreEff[i]   = 71.8403;
        PreHEff[i]  = 49.8059;
        PreGdEff[i] = 93.4249;
        break;
      case 2:
        NHITSTH[i]   = 25;
        PreEff[i]   = 63.9352;
        PreHEff[i]  = 35.8948;
        PreGdEff[i] = 91.4037;
        break;
      case 3:
        NHITSTH[i]   = 30;
        PreEff[i]   = 51.5914;
        PreHEff[i]  = 15.1829;
        PreGdEff[i] = 87.2582;
        break;
      case 4:
        NHITSTH[i]   = 35;
        PreEff[i]   = 41.1455;
        PreHEff[i]  = 4.02583;
        PreGdEff[i] = 77.5087;
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
  g_NHITSTH_x_NNEff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;13");
  g_NHITSTH_x_NNEff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;13");

  TGraphErrors* g_NHITSTH_x_NNHEff[SCANPOINTS];
  g_NHITSTH_x_NNHEff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;14");
  g_NHITSTH_x_NNHEff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;14");

  TGraphErrors* g_NHITSTH_x_NNGdEff[SCANPOINTS];
  g_NHITSTH_x_NNGdEff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;15");
  g_NHITSTH_x_NNGdEff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;15");

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
  g_NHITSTH_x_Eff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;16");
  g_NHITSTH_x_Eff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;16");

  TGraphErrors* g_NHITSTH_x_HEff[SCANPOINTS];
  g_NHITSTH_x_HEff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;17");
  g_NHITSTH_x_HEff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;17");

  TGraphErrors* g_NHITSTH_x_GdEff[SCANPOINTS];
  g_NHITSTH_x_GdEff[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;18");
  g_NHITSTH_x_GdEff[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;18");

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


#if 1
  ///////////  Pre-selection Efficiency  ////////////
  TCanvas* cPre = new TCanvas("cPre", "cPre", 900, 700);
  cPre -> cd();
  cPre -> SetGrid();
  TH1F* framePre = gPad->DrawFrame(10., 0., 45., 1.);
  framePre -> SetXTitle("NHITSTH");
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
  //legend1->Draw();

  TLegend* legend2 = new TLegend(0.42, 0.9, 0.68, 0.95);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(g_NHITSTH_x_PreEff, "Gd+H", "PL");
  legend2->SetLineColor(0);
  legend2->SetFillColor(0);
  legend2->SetFillStyle(0);
  legend2->SetBorderSize(0);
  legend2->Draw() ;

  TLegend* legend3 = new TLegend(0.6, 0.9, 0.88, 0.95);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry(g_NHITSTH_x_PreHEff, "H", "PL");
  legend3->SetLineColor(0);
  legend3->SetFillColor(0);
  legend3->SetFillStyle(0);
  legend3->SetBorderSize(0);
  legend3->Draw() ;

  TLegend* legend4 = new TLegend(0.7, 0.9, 0.98, 0.95);
  legend4 -> SetTextSize(0.04);
  legend4 -> AddEntry(g_NHITSTH_x_PreGdEff, "Gd", "PL");
  legend4->SetLineColor(0);
  legend4->SetFillColor(0);
  legend4->SetFillStyle(0);
  legend4->SetBorderSize(0);
  legend4->Draw() ;
#endif


#if 1
  ///////////  NN Classification Efficiency (Gd+H)  ////////////
  TCanvas* cNN = new TCanvas("cNN", "cNN", 900, 1000);
  cNN -> Divide(1, 3);
  cNN -> cd(1) -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("n-likelihood");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN ->GetXaxis()->SetLabelSize(0.053);
  frameNN ->GetYaxis()->SetLabelSize(0.053);
  frameNN ->GetXaxis()->SetTitleSize(0.053);
  frameNN ->GetYaxis()->SetTitleSize(0.053);
  frameNN -> SetTitleOffset(0.7, "Y");
  frameNN -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNEff[iscan] -> Draw("L");

  TLegend* legendNN = new TLegend(0.15, 0.15, 0.49, 0.59);
  legendNN -> SetTextSize(0.055);
  legendNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legendNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legendNN -> SetFillColor(0);
  legendNN -> Draw();

  ///////////  NN Classification Efficiency (H)  ////////////
  cNN -> cd(2) -> SetGrid();
  TH1F* frameHNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameHNN -> SetXTitle("n-likelihood");
  frameHNN -> SetYTitle("NN H(n, #gamma) Classification Efficiency");
  frameHNN ->GetXaxis()->SetLabelSize(0.053);
  frameHNN ->GetYaxis()->SetLabelSize(0.053);
  frameHNN ->GetXaxis()->SetTitleSize(0.053);
  frameHNN ->GetYaxis()->SetTitleSize(0.053);
  frameHNN -> SetTitleOffset(0.7, "Y");
  frameHNN -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNHEff[iscan] -> Draw("L");

  TLegend* legendHNN = new TLegend(0.55, 0.45, 0.89, 0.89);
  legendHNN -> SetTextSize(0.055);
  legendHNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legendHNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legendHNN -> SetFillColor(0);
  legendHNN -> Draw();
  
  ///////////  NN Classification Efficiency (Gd)  ////////////
  cNN -> cd(3) -> SetGrid();
  TH1F* frameGdNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameGdNN -> SetXTitle("n-likelihood");
  frameGdNN -> SetYTitle("NN Gd(n, #gamma) Classification Efficiency");
  frameGdNN ->GetXaxis()->SetLabelSize(0.053);
  frameGdNN ->GetYaxis()->SetLabelSize(0.053);
  frameGdNN ->GetXaxis()->SetTitleSize(0.053);
  frameGdNN ->GetYaxis()->SetTitleSize(0.053);
  frameGdNN -> SetTitleOffset(0.7, "Y");
  frameGdNN -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_NNGdEff[iscan] -> Draw("L");

  TLegend* legendGdNN = new TLegend(0.15, 0.15, 0.49, 0.59);
  legendGdNN -> SetTextSize(0.055);
  legendGdNN -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legendGdNN -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legendGdNN -> SetFillColor(0);
  legendGdNN -> Draw();
#endif


#if 1
  ///////////  Overall Tagging Efficiency (Gd+H)  ////////////
  TCanvas* c = new TCanvas("c", "cOverall", 900, 1000);
  c -> Divide(1, 3);
  c -> cd(1) -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame ->GetXaxis()->SetLabelSize(0.053);
  frame ->GetYaxis()->SetLabelSize(0.053);
  frame ->GetXaxis()->SetTitleSize(0.053);
  frame ->GetYaxis()->SetTitleSize(0.053);
  frame -> SetTitleOffset(0.7, "Y");
  frame -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_Eff[iscan] -> Draw("L");

  TLegend* legend = new TLegend(0.55, 0.45, 0.89, 0.89);
  legend -> SetTextSize(0.055);
  legend -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legend -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legend -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legend -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legend -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legend -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legend -> SetFillColor(0);
  legend -> Draw();

  ///////////  Overall Tagging Efficiency (H)  ////////////
  c -> cd(2) -> SetGrid();
  TH1F* frameH = gPad->DrawFrame(0., 0., 1., 1.);
  frameH -> SetXTitle("n-likelihood");
  frameH -> SetYTitle("Overall H(n, #gamma) Tagging Efficiency");
  frameH ->GetXaxis()->SetLabelSize(0.053);
  frameH ->GetYaxis()->SetLabelSize(0.053);
  frameH ->GetXaxis()->SetTitleSize(0.053);
  frameH ->GetYaxis()->SetTitleSize(0.053);
  frameH -> SetTitleOffset(0.7, "Y");
  frameH -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_HEff[iscan] -> Draw("L");

  TLegend* legendH = new TLegend(0.55, 0.45, 0.89, 0.89);
  legendH -> SetTextSize(0.055);
  legendH -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendH -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legendH -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legendH -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legendH -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legendH -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legendH -> SetFillColor(0);
  legendH -> Draw();
  
  ///////////  Overall Tagging Efficiency (Gd)  ////////////
  c -> cd(3) -> SetGrid();
  TH1F* frameGd = gPad->DrawFrame(0., 0., 1., 1.);
  frameGd -> SetXTitle("n-likelihood");
  frameGd -> SetYTitle("Overall Gd(n, #gamma) Tagging Efficiency");
  frameGd ->GetXaxis()->SetLabelSize(0.053);
  frameGd ->GetYaxis()->SetLabelSize(0.053);
  frameGd ->GetXaxis()->SetTitleSize(0.053);
  frameGd ->GetYaxis()->SetTitleSize(0.053);
  frameGd -> SetTitleOffset(0.7, "Y");
  frameGd -> SetTitleOffset(0.8, "X");
  for (int iscan=0; iscan<SCANPOINTS; iscan++) g_NHITSTH_x_GdEff[iscan] -> Draw("L");

  TLegend* legendGd = new TLegend(0.15, 0.15, 0.49, 0.59);
  legendGd -> SetTextSize(0.055);
  legendGd -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendGd -> AddEntry(g_NHITSTH_x_NNEff[0], "NHITSTH = 15", "L");
  legendGd -> AddEntry(g_NHITSTH_x_NNEff[1], "NHITSTH = 20", "L");
  legendGd -> AddEntry(g_NHITSTH_x_NNEff[2], "NHITSTH = 25(nominal)", "L");
  legendGd -> AddEntry(g_NHITSTH_x_NNEff[3], "NHITSTH = 30", "L");
  legendGd -> AddEntry(g_NHITSTH_x_NNEff[4], "NHITSTH = 35", "L");
  legendGd -> SetFillColor(0);
  legendGd -> Draw();
#endif
  
}
