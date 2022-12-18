#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void CompareDecaye() {

  TFile* fin_numu1 = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.beforecut.root");
  TFile* fin_numu2 = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.aftercut.root");


  TH1F* h1_CCQE_numu1    = (TH1F*)fin_numu1->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_numu1  = (TH1F*)fin_numu1->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_numu1      = (TH1F*)fin_numu1->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_numu1 = (TH1F*)fin_numu1->Get("DecayeBox/h1_TrueDecaye_mode6");
  h1_CCQE_numu1 -> SetStats(0);
  h1_CC2p2h_numu1 -> SetStats(0);
  h1_CCOther_numu1 -> SetStats(0);
  h1_NC_numu1 -> SetStats(0);

  TH1F* h1_CCQE_numu2    = (TH1F*)fin_numu2->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_numu2  = (TH1F*)fin_numu2->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_numu2      = (TH1F*)fin_numu2->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_numu2 = (TH1F*)fin_numu2->Get("DecayeBox/h1_TrueDecaye_mode6");

  h1_CCQE_numu1    -> SetLineColor(kAzure-1);
  h1_CC2p2h_numu1  -> SetLineColor(kOrange+7);
  h1_CCOther_numu1 -> SetLineColor(kOrange+4);
  h1_NC_numu1      -> SetLineColor(kSpring-9);

  h1_CCQE_numu2    -> SetLineColor(kAzure-1);
  h1_CC2p2h_numu2  -> SetLineColor(kOrange+7);
  h1_CCOther_numu2 -> SetLineColor(kOrange+4);
  h1_NC_numu2      -> SetLineColor(kSpring-9);

  h1_CCQE_numu2    -> SetLineStyle(7);
  h1_CC2p2h_numu2  -> SetLineStyle(7);
  h1_CCOther_numu2 -> SetLineStyle(7);
  h1_NC_numu2      -> SetLineStyle(7);

  h1_CCQE_numu1    -> SetLineWidth(3);
  h1_CC2p2h_numu1  -> SetLineWidth(3);
  h1_CCOther_numu1 -> SetLineWidth(3);
  h1_NC_numu1      -> SetLineWidth(3);
  h1_CCQE_numu2    -> SetLineWidth(3);
  h1_CC2p2h_numu2  -> SetLineWidth(3);
  h1_CCOther_numu2 -> SetLineWidth(3);
  h1_NC_numu2      -> SetLineWidth(3);

  std::cout << "CCQE    (before cut): " << h1_CCQE_numu1->Integral() << std::endl;
  std::cout << "CCQE    (after cut) : " << h1_CCQE_numu2->Integral() << std::endl;
  std::cout << "CC2p2h  (before cut): " << h1_CC2p2h_numu1->Integral() << std::endl;
  std::cout << "CC2p2h  (after cut) : " << h1_CC2p2h_numu2->Integral() << std::endl;
  std::cout << "CCOther (before cut): " << h1_CCOther_numu1->Integral() << std::endl;
  std::cout << "CCOther (after cut) : " << h1_CCOther_numu2->Integral() << std::endl;
  std::cout << "NC      (before cut): " << h1_NC_numu1->Integral() << std::endl;
  std::cout << "NC      (after cut) : " << h1_NC_numu2->Integral() << std::endl;

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> Divide(2, 2);

  c1 -> cd(1) -> SetGrid();
  c1 -> cd(1) -> SetLogy();
  h1_CCQE_numu1 -> Draw();
  h1_CCQE_numu2 -> Draw("SAME");

  c1 -> cd(2) -> SetGrid();
  c1 -> cd(2) -> SetLogy();
  h1_CC2p2h_numu1 -> Draw();
  h1_CC2p2h_numu2 -> Draw("SAME");

  c1 -> cd(3) -> SetGrid();
  c1 -> cd(3) -> SetLogy();
  h1_CCOther_numu1 -> Draw();
  h1_CCOther_numu2 -> Draw("SAME");

  c1 -> cd(4) -> SetGrid();
  c1 -> cd(4) -> SetLogy();
  h1_NC_numu1 -> Draw();
  h1_NC_numu2 -> Draw("SAME");
#endif

}