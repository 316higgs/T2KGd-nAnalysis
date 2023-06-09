#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define VARNUM 5

void Var_FOM() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_FOM[VARNUM];
  g_FOM[0] = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;25");  // +40%
  g_FOM[1] = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;23");  // +30%
  g_FOM[2] = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;22");  // nominal
  g_FOM[3] = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;24");  // -30%
  g_FOM[4] = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;26");  // -40%

  for (int i=0; i<VARNUM; i++) {
    if (i==0) g_FOM[i] -> SetLineColor(kViolet+2);
    if (i==1) g_FOM[i] -> SetLineColor(kAzure+7);
    if (i==2) g_FOM[i] -> SetLineColor(kSpring-1);
    if (i==3) g_FOM[i] -> SetLineColor(kOrange-3);
    if (i==4) g_FOM[i] -> SetLineColor(kPink-5);
    g_FOM[i] -> SetMarkerStyle(20);
    g_FOM[i] -> SetMarkerSize(1.5);
    g_FOM[i] -> SetLineWidth(2);
  }

  // Optimal threshold
  Double_t OptX_p40 = 0.35;
  Double_t OptX_p30 = 0.35;
  Double_t OptX_nom = 0.45;
  Double_t OptX_m30 = 0.5;
  Double_t OptX_m40 = 0.5;

  // Maximized FOM
  Double_t OptY_p40 = 138.226;
  Double_t OptY_p30 = 132.915;
  Double_t OptY_nom = 115.74;
  Double_t OptY_m30 = 95.823;
  Double_t OptY_m40 = 88.2368;

  TGraph* g_Opt[VARNUM];
  g_Opt[0] = new TGraph(1, &OptX_p40, &OptY_p40);
  g_Opt[1] = new TGraph(1, &OptX_p30, &OptY_p30);
  g_Opt[2] = new TGraph(1, &OptX_nom, &OptY_nom);
  g_Opt[3] = new TGraph(1, &OptX_m30, &OptY_m30);
  g_Opt[4] = new TGraph(1, &OptX_m40, &OptY_m40);
  g_Opt[0] -> SetMarkerColor(kViolet+2);
  g_Opt[1] -> SetMarkerColor(kAzure+7);
  g_Opt[2] -> SetMarkerColor(kSpring-1);
  g_Opt[3] -> SetMarkerColor(kOrange-3);
  g_Opt[4] -> SetMarkerColor(kPink-5);
  for (int i=0; i<VARNUM; i++) {
    g_Opt[i] -> SetMarkerStyle(33);
    g_Opt[i] -> SetMarkerSize(1.5);
  }

  // Noise rate variation
  float OptNoiseRate[VARNUM];
  OptNoiseRate[0] = 4.66482;  // %
  OptNoiseRate[1] = 4.66482;  // %
  OptNoiseRate[2] = 3.18619;  // %
  OptNoiseRate[3] = 2.69331;  // %
  OptNoiseRate[4] = 2.69331;  // %
  TH1F* h1_VarNoiseRate = new TH1F("h1_VarNoiseRate", "", VARNUM, 0, VARNUM);
  for (int ibin=0; ibin<VARNUM; ibin++) {
    h1_VarNoiseRate -> SetBinContent(ibin+1, OptNoiseRate[ibin]/OptNoiseRate[2]);
  }
  h1_VarNoiseRate -> SetLineColor(kViolet-6);
  h1_VarNoiseRate -> SetLineWidth(2);
  h1_VarNoiseRate -> SetStats(0);
  h1_VarNoiseRate -> SetYTitle("r_{noise}/r_{noise}(nominal)");
  h1_VarNoiseRate -> GetXaxis()->SetBinLabel(1, "+40%");
  h1_VarNoiseRate -> GetXaxis()->SetBinLabel(2, "+30%");
  h1_VarNoiseRate -> GetXaxis()->SetBinLabel(3, "Nominal MC");
  h1_VarNoiseRate -> GetXaxis()->SetBinLabel(4, "-30%");
  h1_VarNoiseRate -> GetXaxis()->SetBinLabel(5, "-40%");
  h1_VarNoiseRate -> GetXaxis()->SetLabelSize(0.055);


  TF1* f1_base = new TF1("f1_base", "1", 0, VARNUM);
  f1_base -> SetLineColor(kViolet-6);
  f1_base -> SetLineWidth(2);
  f1_base -> SetLineStyle(7);


  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",1000,700);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 150.);
  frame -> SetXTitle("n-likethreshold");
  frame -> SetYTitle("Figure of Merit  S/#sqrt{S+B}");
  frame -> SetTitleOffset(1.1, "Y");
  frame -> GetXaxis()->SetLabelSize(0.03);
  frame -> GetYaxis()->SetLabelSize(0.03);
  for (int i=0; i<VARNUM; i++) {
    g_FOM[i] -> Draw("L");
    g_Opt[i] -> Draw("P");
  }

  TLegend* legend = new TLegend(0.55, 0.13, 0.89, 0.45);
  legend -> SetTextSize(0.035);
  //legend -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legend -> AddEntry(g_FOM[0], "+40%", "L");
  legend -> AddEntry(g_FOM[1], "+30%", "L");
  legend -> AddEntry(g_FOM[2], "nominal MC", "L");
  legend -> AddEntry(g_FOM[3], "-30%", "L");
  legend -> AddEntry(g_FOM[4], "-40%", "L");
  legend -> SetFillColor(0);
  legend -> Draw();


  // Variation of noise rate at each optimial threshold for different TagTP
  TCanvas* c1 = new TCanvas("c1","c1",1000,700);
  c1 -> SetGrid();
  h1_VarNoiseRate -> Draw("");
  f1_base -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.6, 0.8, 0.89, 0.89);
  legend1 -> SetTextSize(0.035);
  legend1 -> AddEntry((TObject*)0, TString::Format("#kern[-0.25]{r_{noise}(nominal)=%.2f%}", OptNoiseRate[2]),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();

}