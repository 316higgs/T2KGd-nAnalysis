#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void SimpleEnu() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");

  TH1F* h1_CCQE_numu    = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProbCCOther");
  //TH1F* h1_CCnonQE_numu = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProbCCnonQE");
  TH1F* h1_NC_numu      = (TH1F*)fin->Get("NeutrinoOscillation/h1_OscProb_mode2");
  h1_CCQE_numu -> SetStats(0);
  
  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  THStack* hs_RecoOsc = new THStack("hs_RecoOsc", "");
  hs_RecoOsc -> Add(h1_NC_numu);
  hs_RecoOsc -> Add(h1_CCOther_numu);
  hs_RecoOsc -> Add(h1_CC2p2h_numu);
  hs_RecoOsc -> Add(h1_CCQE_numu);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  hs_RecoOsc -> Draw();
  hs_RecoOsc ->GetYaxis()->SetTitleSize(0.038);
  hs_RecoOsc ->GetYaxis()->SetTitleOffset(1.3);
  hs_RecoOsc ->GetYaxis()->SetLabelSize(0.036);
  hs_RecoOsc ->GetXaxis()->SetTitle("Reconstructed #nu Energy [GeV]");
  hs_RecoOsc ->GetYaxis()->SetTitle("Number of #nu Events");
  hs_RecoOsc -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.87, 0.87);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.9]{#nu_{#mu}#rightarrow#nu_{#mu}}","");
  //if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.03% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.03% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
}