#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void TagEff_x_dist() {
  //TFile* fin_o = new TFile("../../../NTagEff/output/thresholdscan.original.root");   /// ToF
  TFile* fin_n = new TFile("../../../NTagEff/output/thresholdscan.train.root");
  //TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");
  //TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  //TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.root");

  TFile* fin_o = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.wToF.root");   /// ToF
  TFile* fin   = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");    /// no-ToF

  //TH1D* h1_eff_x_dist_o    = (TH1D*)fin_o->Get("h1_tagging_eff_scan7");
  //TH1D* h1_preeff_x_dist_o = (TH1D*)fin_o->Get("h1_pre_eff_scan7");
  //TH1D* h1_NNeff_x_dist_o  = (TH1D*)fin_o->Get("h1_NN_eff_scan7");
  //TH1D* h1_truedistance_o  = (TH1D*)fin_o->Get("h1_truedistance");

  TH1D* h1_eff_x_dist_o    = (TH1D*)fin_o->Get("DistanceViewer/h1_OverallEff_dist_thr11");
  h1_eff_x_dist_o -> SetXTitle("Truth Neutron Travel DIstance[m]");
  h1_eff_x_dist_o -> SetYTitle("Overall Tagging Efficiency");
  TH1D* h1_preeff_x_dist_o = (TH1D*)fin_o->Get("DistanceViewer/h1_PreEff_dist");
  h1_preeff_x_dist_o -> SetXTitle("Truth Neutron Travel DIstance[m]");
  h1_preeff_x_dist_o -> SetYTitle("Pre-selection Efficiency");
  h1_preeff_x_dist_o -> SetTitleOffset(1.3, "Y");
  TH1D* h1_NNeff_x_dist_o  = (TH1D*)fin_o->Get("DistanceViewer/h1_NNEff_dist_thr11");
  h1_NNeff_x_dist_o -> SetXTitle("Truth Neutron Travel DIstance[m]");
  h1_NNeff_x_dist_o -> SetYTitle("NN Classification Efficiency");
  TH1D* h1_truedistance_o  = (TH1D*)fin_o->Get("DistanceViewer/h1_truedistance");

  TH1D* h1_eff_x_dist_n    = (TH1D*)fin_n->Get("h1_tagging_eff_scan8");
  TH1D* h1_preeff_x_dist_n = (TH1D*)fin_n->Get("h1_pre_eff_scan8");
  TH1D* h1_NNeff_x_dist_n  = (TH1D*)fin_n->Get("h1_NN_eff_scan8");
  TH1D* h1_truedistance_n  = (TH1D*)fin_n->Get("h1_truedistance");

  TH1D* h1_eff_x_dist    = (TH1D*)fin->Get("DistanceViewer/h1_OverallEff_dist_thr11");
  TH1D* h1_preeff_x_dist = (TH1D*)fin->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNeff_x_dist  = (TH1D*)fin->Get("DistanceViewer/h1_NNEff_dist_thr11");
  TH1D* h1_truedistance  = (TH1D*)fin->Get("DistanceViewer/h1_truedistance");

  h1_eff_x_dist_o    -> SetLineColor(kAzure+7);
  h1_preeff_x_dist_o -> SetLineColor(kAzure+7);
  h1_NNeff_x_dist_o  -> SetLineColor(kAzure+7);
  h1_truedistance_o  -> SetLineColor(kAzure+7);
  h1_truedistance_o  -> SetFillColor(0);
  h1_eff_x_dist_o    -> SetLineWidth(3);
  h1_preeff_x_dist_o -> SetLineWidth(3);
  h1_NNeff_x_dist_o  -> SetLineWidth(3);
  h1_eff_x_dist_o    -> SetStats(0);
  h1_preeff_x_dist_o -> SetStats(0);
  h1_NNeff_x_dist_o  -> SetStats(0);

  h1_eff_x_dist_n    -> SetLineColor(kSpring-5);
  h1_preeff_x_dist_n -> SetLineColor(kSpring-5);
  h1_NNeff_x_dist_n  -> SetLineColor(kSpring-5);
  h1_truedistance_n  -> SetLineColor(kSpring-5);
  h1_truedistance_n  -> SetFillColor(0);
  h1_truedistance_n  -> SetLineWidth(2);
  h1_eff_x_dist      -> SetLineColor(kOrange+7);
  h1_preeff_x_dist   -> SetLineColor(kOrange+7);
  h1_NNeff_x_dist    -> SetLineColor(kOrange+7);
  h1_eff_x_dist      -> SetLineWidth(3);
  h1_preeff_x_dist   -> SetLineWidth(3);
  h1_NNeff_x_dist    -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");
  /// Pre-selection ////////////////////////////////
  TCanvas* cpreeff = new TCanvas("cpreeff","cpreeff",800,800);
  cpreeff -> SetGrid();
  cpreeff -> cd();
  h1_preeff_x_dist_o -> GetYaxis() -> SetRangeUser(0.1, 0.9);
  h1_preeff_x_dist_o -> Draw();
  //h1_preeff_x_dist_n -> Draw("SAME");
  h1_preeff_x_dist   -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.13, 0.14, 0.55, 0.35);
  legend1 -> SetTextSize(0.035);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (#nu_{#mu}#rightarrow#nu_{#mu})}","");
  legend1 -> AddEntry(h1_eff_x_dist_o, "ToF-subtracted", "L");
  legend1 -> AddEntry(h1_eff_x_dist, "No ToF-subtraction", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();

  /// NN classification ////////////////////////////////
  TCanvas* cnneff = new TCanvas("cnneff","cnneff",800,800);
  cnneff -> SetGrid();
  cnneff -> cd();
  h1_NNeff_x_dist_o -> GetYaxis() -> SetRangeUser(0., 0.8);
  h1_NNeff_x_dist_o -> Draw();
  //h1_NNeff_x_dist_n -> Draw("SAME");
  h1_NNeff_x_dist   -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.13, 0.14, 0.55, 0.35);
  legend2 -> SetTextSize(0.035);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (#nu_{#mu}#rightarrow#nu_{#mu})}","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.28]{n-likelihood: 0.55}","");
  legend2 -> AddEntry(h1_eff_x_dist_o, "ToF-subtracted", "L");
  legend2 -> AddEntry(h1_eff_x_dist, "No ToF-subtraction", "L");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();

  /// Overall ////////////////////////////////
  TCanvas* ceff = new TCanvas("ceff","ceff",800,800);
  ceff -> SetGrid();
  ceff -> cd();
  h1_eff_x_dist_o -> GetYaxis() -> SetRangeUser(0., 0.6);
  h1_eff_x_dist_o -> Draw();
  //h1_eff_x_dist_n -> Draw("SAME");
  h1_eff_x_dist   -> Draw("SAME");
  legend2 -> Draw();

  


  /*TCanvas* cdist = new TCanvas("cdist", "cdist", 800, 800);
  cdist -> cd();
  //h1_truedistance_o -> Draw();
  //h1_truedistance_n -> Draw("SAME");
  h1_truedistance   -> Draw("SAME");
  cdist -> SaveAs("../figure/truedistance.pdf");*/

}