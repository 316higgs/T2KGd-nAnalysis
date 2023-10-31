#include "TStyle.h"
#include "TColor.h"

#define VARNUM 14

void CorrelationMatrix(TString foutname) {
  /*TFile* fin[196];
  TH2F* h2_matrix[196];
  for (int i=0; i<196; i++) {
    fin[i]       = new TFile(TString::Format("./tmp/output%d.root", i+1));
    h2_matrix[i] = (TH2F*)fin[i]->Get("textCol");
  }*/

  TFile* fin[VARNUM*VARNUM];
  TH2F* h2_matrix[VARNUM*VARNUM];
  for (int i=0; i<VARNUM*VARNUM; i++) {
    fin[i]       = new TFile(TString::Format("./tmp/output%d.root", i+1));
    h2_matrix[i] = (TH2F*)fin[i]->Get("textCol");
  }

  gROOT -> SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetFrameFillColor(0);
  gStyle->SetCanvasColor(0);
  gStyle->SetPadBorderSize(0);
  gStyle->SetPaintTextFormat(".2f");

  /*const Int_t NRGBs = 5;
  const Int_t NCont = 255;
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);*/

  TCanvas* c = new TCanvas("c", "c", 1600, 1000);

  TList* l = new TList;
  for (int i=0; i<VARNUM*VARNUM; i++) {
    l -> Add(h2_matrix[i]);
  }


  TH2D* h2 = new TH2D("h2","", VARNUM, 0, VARNUM, VARNUM, 0, VARNUM);
  /*h2 -> GetXaxis() -> SetNdivisions(VARNUM);
  h2 -> GetXaxis() -> SetBinLabel(1, "NHits");
  h2 -> GetXaxis() -> SetBinLabel(2, "N200");
  h2 -> GetXaxis() -> SetBinLabel(3, "TRMS");
  h2 -> GetXaxis() -> SetBinLabel(4, "Dwall");
  h2 -> GetXaxis() -> SetBinLabel(5, "DwallMeanDir");
  h2 -> GetXaxis() -> SetBinLabel(6, "Dwall_n");
  h2 -> GetXaxis() -> SetBinLabel(7, "prompt_nfit");
  h2 -> GetXaxis() -> SetBinLabel(8, "AngleMean");
  h2 -> GetXaxis() -> SetBinLabel(9, "AngleStdev");
  h2 -> GetXaxis() -> SetBinLabel(10, "AngleSkew");
  h2 -> GetXaxis() -> SetBinLabel(11, "ThetaMeanDir");
  h2 -> GetXaxis() -> SetBinLabel(12, "Beta1");
  h2 -> GetXaxis() -> SetBinLabel(13, "Beta2");
  h2 -> GetXaxis() -> SetBinLabel(14, "Beta3");
  h2 -> GetXaxis() -> SetBinLabel(15, "Beta4");
  h2 -> GetXaxis() -> SetBinLabel(VARNUM, "Beta5");*/
  h2 -> GetXaxis() -> SetNdivisions(VARNUM);
  h2 -> GetXaxis() -> SetBinLabel(1, "NHits");
  h2 -> GetXaxis() -> SetBinLabel(2, "NResHits");
  h2 -> GetXaxis() -> SetBinLabel(3, "TRMS");
  h2 -> GetXaxis() -> SetBinLabel(4, "Dwall");
  h2 -> GetXaxis() -> SetBinLabel(5, "DwallMeanDir");
  h2 -> GetXaxis() -> SetBinLabel(6, "OpeningAngleStdev");
  h2 -> GetXaxis() -> SetBinLabel(7, "Beta1");
  h2 -> GetXaxis() -> SetBinLabel(8, "Beta2");
  h2 -> GetXaxis() -> SetBinLabel(9, "Beta3");
  h2 -> GetXaxis() -> SetBinLabel(10, "Beta4");
  h2 -> GetXaxis() -> SetBinLabel(11, "Beta5");
  h2 -> GetXaxis() -> SetBinLabel(12, "BurstRatio");
  h2 -> GetXaxis() -> SetBinLabel(13, "FitGoodness");
  h2 -> GetXaxis() -> SetBinLabel(14, "DarkLikelihood");
  h2 -> SetLabelSize(0.03, "X");


  h2 -> GetYaxis() -> SetNdivisions(VARNUM);
  h2 -> GetXaxis() -> SetNdivisions(VARNUM);
  h2 -> GetYaxis() -> SetBinLabel(1, "NHits");
  h2 -> GetYaxis() -> SetBinLabel(2, "NResHits");
  h2 -> GetYaxis() -> SetBinLabel(3, "TRMS");
  h2 -> GetYaxis() -> SetBinLabel(4, "Dwall");
  h2 -> GetYaxis() -> SetBinLabel(5, "DwallMeanDir");
  h2 -> GetYaxis() -> SetBinLabel(6, "OpeningAngleStdev");
  h2 -> GetYaxis() -> SetBinLabel(7, "Beta1");
  h2 -> GetYaxis() -> SetBinLabel(8, "Beta2");
  h2 -> GetYaxis() -> SetBinLabel(9, "Beta3");
  h2 -> GetYaxis() -> SetBinLabel(10, "Beta4");
  h2 -> GetYaxis() -> SetBinLabel(11, "Beta5");
  h2 -> GetYaxis() -> SetBinLabel(12, "BurstRatio");
  h2 -> GetYaxis() -> SetBinLabel(13, "FitGoodness");
  h2 -> GetYaxis() -> SetBinLabel(14, "DarkLikelihood");
  h2 -> SetLabelSize(0.03, "Y");

  h2 -> Merge(l);
  h2 -> SetStats(0);
  
  h2 -> Draw("textcol");
  
  TFile* fout = new TFile(foutname, "RECREATE");
  fout -> cd();
  h2 -> Write();
}