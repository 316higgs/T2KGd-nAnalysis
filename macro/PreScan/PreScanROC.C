#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define SCANPOINTS 5
#define CUTSTEP 21

void PreScanROC() {

  TFile* fin_scn1 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH15.root");
  TFile* fin_scn2 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH20.root");
  TFile* fin_scn3 = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  TFile* fin_scn4 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH30.root");
  TFile* fin_scn5 = new TFile("../../output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.NHITSTH35.root");


  /////////////  Overall tagging efficiency  ////////////////
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


  /////////////  Mis-tagged Noise Rate  ////////////////
  TGraphErrors* g_NoiseRate[SCANPOINTS];
  g_NoiseRate[0] = (TGraphErrors*)fin_scn1->Get("NTagAnalysis/Graph;1");
  g_NoiseRate[1] = (TGraphErrors*)fin_scn2->Get("NTagAnalysis/Graph;1");
  g_NoiseRate[2] = (TGraphErrors*)fin_scn3->Get("NTagAnalysis/Graph;1");
  g_NoiseRate[3] = (TGraphErrors*)fin_scn4->Get("NTagAnalysis/Graph;1");
  g_NoiseRate[4] = (TGraphErrors*)fin_scn5->Get("NTagAnalysis/Graph;1");

  
  Double_t Threshold[CUTSTEP]              = {0.};
  Double_t NoiseRate[SCANPOINTS][CUTSTEP]  = {0.};
  Double_t OverallEff[SCANPOINTS][CUTSTEP] = {0.};
  //Int_t iscn = 2;
  TGraph* g_NHITSTH_x_ROC[SCANPOINTS];
  for (Int_t iscn=0; iscn<SCANPOINTS; iscn++) {
    for (Int_t ithr=0; ithr<CUTSTEP; ithr++) {
  	  Threshold[ithr]        = g_NoiseRate[iscn]->GetX()[ithr];
  	  NoiseRate[iscn][ithr]  = g_NoiseRate[iscn]->GetY()[ithr];
  	  OverallEff[iscn][ithr] = g_NHITSTH_x_Eff[iscn]->GetY()[ithr];
  	  //std::cout << "[### Threshold=" << Threshold[ithr] 
  	  //          << " ###]  Noise rate = " << NoiseRate[iscn][ithr] 
  	  //          << ", Overall efficiency = " << OverallEff[iscn][ithr] << std::endl;
    }

    g_NHITSTH_x_ROC[iscn] = new TGraph(CUTSTEP, NoiseRate[iscn], OverallEff[iscn]);
    g_NHITSTH_x_ROC[iscn] -> SetLineWidth(2);
    if (iscn==0) g_NHITSTH_x_ROC[iscn] -> SetLineColor(kViolet+2);
    if (iscn==1) g_NHITSTH_x_ROC[iscn] -> SetLineColor(kAzure+7);
    if (iscn==2) g_NHITSTH_x_ROC[iscn] -> SetLineColor(kSpring-1);
    if (iscn==3) g_NHITSTH_x_ROC[iscn] -> SetLineColor(kOrange-3);
    if (iscn==4) g_NHITSTH_x_ROC[iscn] -> SetLineColor(kPink-5);
  }
 

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  //frame -> SetMaximum(0.1);
  frame -> SetXTitle("Mis-tagged Noise Rate");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame -> SetTitleOffset(1.1, "Y");
  for (int i=0; i<SCANPOINTS; i++) g_NHITSTH_x_ROC[i] -> Draw("SAMEL");

  TLegend* legendH = new TLegend(0.45, 0.55, 0.89, 0.89);
  legendH -> SetTextSize(0.035);
  legendH -> AddEntry((TObject*)0,"#kern[-0.25]{NHITSTH scan (TWIDTH=200 ns)}","");
  legendH -> AddEntry(g_NHITSTH_x_ROC[0], "NHITSTH = 15", "L");
  legendH -> AddEntry(g_NHITSTH_x_ROC[1], "NHITSTH = 20", "L");
  legendH -> AddEntry(g_NHITSTH_x_ROC[2], "NHITSTH = 25(nominal)", "L");
  legendH -> AddEntry(g_NHITSTH_x_ROC[3], "NHITSTH = 30", "L");
  legendH -> AddEntry(g_NHITSTH_x_ROC[4], "NHITSTH = 35", "L");
  legendH -> SetFillColor(0);
  legendH -> Draw();
}