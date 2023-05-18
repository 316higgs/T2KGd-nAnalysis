#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Efficiency() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.root");
  //TFile* fin = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.noinpmt.root");

  //TFile* fin = new TFile("../../output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root");

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TGraphErrors* g_NNEff    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;13");
  TGraphErrors* g_NNHEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;14");
  TGraphErrors* g_NNGdEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;15");

  TGraphErrors* g_OverallEff    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;16");
  TGraphErrors* g_OverallHEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;17");
  TGraphErrors* g_OverallGdEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;18");

  gROOT -> SetStyle("Plain");

  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("n-likelihood");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame -> SetTitleOffset(1.2, "Y");
  g_OverallEff   -> Draw("PL");
  g_OverallHEff  -> Draw("SAMEPL");
  g_OverallGdEff -> Draw("SAMEPL");

  TLegend* legend = new TLegend(0.53, 0.9, 0.87, 0.94);
  legend -> SetTextSize(0.04);
  legend->AddEntry((TObject*)0,"#kern[-0.1]{noToF, -tag_e ON}","");
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  //legend->Draw() ;

  TLegend* legend1 = new TLegend(0.7, 0.85, 0.85, 0.87);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{FHC #bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC}","");
  legend1->SetLineColor(0);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetBorderSize(0);
  legend1->Draw() ;

  TLegend* legend2 = new TLegend(0.42, 0.9, 0.68, 0.95);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(g_OverallEff, "Gd+H", "PL");
  legend2->SetLineColor(0);
  legend2->SetFillColor(0);
  legend2->SetFillStyle(0);
  legend2->SetBorderSize(0);
  legend2->Draw() ;

  TLegend* legend3 = new TLegend(0.6, 0.9, 0.88, 0.95);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry(g_OverallHEff, "H", "PL");
  legend3->SetLineColor(0);
  legend3->SetFillColor(0);
  legend3->SetFillStyle(0);
  legend3->SetBorderSize(0);
  legend3->Draw() ;

  TLegend* legend4 = new TLegend(0.7, 0.9, 0.98, 0.95);
  legend4 -> SetTextSize(0.04);
  legend4 -> AddEntry(g_OverallGdEff, "Gd", "PL");
  legend4->SetLineColor(0);
  legend4->SetFillColor(0);
  legend4->SetFillStyle(0);
  legend4->SetBorderSize(0);
  legend4->Draw() ;

#if 1
  TCanvas* cNN = new TCanvas("cNN","cNN",800,800);
  cNN -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("n-likelihood");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN -> SetTitleOffset(1.2, "Y");
  g_NNEff   -> Draw("PL");
  g_NNHEff  -> Draw("SAMEPL");
  g_NNGdEff -> Draw("SAMEPL");
  //legend->Draw() ;
  legend1 -> Draw();
  legend2 -> Draw();
  legend3 -> Draw();
  legend4 -> Draw();

#endif
}

