#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"
#include <iomanip>

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void CompareSelEff(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  //FHC
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");

  //Pure water MC
  TFile* fin_numu_pw      = new TFile("../../output/fhc/fhc.numu_x_numu.water.root");
  TFile* fin_nuesig_pw    = new TFile("../../output/fhc/fhc.numu_x_nue.water.root");
  TFile* fin_numubar_pw   = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");
  TFile* fin_nuebarsig_pw = new TFile("../../output/fhc/fhc.numubar_x_nuebar.water.root");
  TFile* fin_nuebkg_pw    = new TFile("../../output/fhc/fhc.nue_x_nue.water.root");
  TFile* fin_nuebarbkg_pw = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.water.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");

  
  TH1F* h1_SelEff_numu_gd = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  h1_SelEff_numu_gd -> SetLineColor(kOrange+0);
  h1_SelEff_numu_gd -> SetLineWidth(3);

  TH1F* h1_ProtoSelEff_numu_gd = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_Proto1RmuonEvents");
  h1_ProtoSelEff_numu_gd -> SetLineColor(kOrange+0);
  h1_ProtoSelEff_numu_gd -> SetLineStyle(7);
  h1_ProtoSelEff_numu_gd -> SetLineWidth(3);

  TH1F* h1_SelEff_numu_pw = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_1RmuonEvents");
  h1_SelEff_numu_pw -> SetLineColor(kAzure+1);
  h1_SelEff_numu_pw -> SetLineStyle(7);
  h1_SelEff_numu_pw -> SetLineWidth(3);
  h1_SelEff_numu_pw -> SetStats(0);
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_SelEff_numu_pw -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");


#if 1
  //Selection efficiency

  TCanvas* c2 = new TCanvas("c2","c2",1000,700);
  c2 -> SetGrid();
  h1_SelEff_numu_pw -> SetMinimum(0.);
  h1_SelEff_numu_pw -> SetMaximum(1.1);
  h1_SelEff_numu_pw ->GetYaxis()->SetTitleSize(0.038);
  h1_SelEff_numu_pw ->GetYaxis()->SetTitleOffset(0.9);
  h1_SelEff_numu_pw ->GetYaxis()->SetLabelSize(0.04);
  h1_SelEff_numu_pw ->GetYaxis()->SetTitle("Remaining rate from FCFV cut");
  h1_SelEff_numu_pw ->GetYaxis()->SetTitleSize(0.045);
  h1_SelEff_numu_pw ->GetXaxis()->SetLabelSize(0.045);
  h1_SelEff_numu_pw -> Draw();
  h1_ProtoSelEff_numu_gd -> Draw("SAME");
  h1_SelEff_numu_gd -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1->AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R#mu sample}","");
  legend1 -> AddEntry(h1_SelEff_numu_pw, "Pure water", "L");
  legend1 -> AddEntry(h1_ProtoSelEff_numu_gd, "Gd: #sub-event", "L");
  legend1 -> AddEntry(h1_SelEff_numu_gd, "Gd: floor cut", "L");
  legend1->SetFillColor(0);
  legend1->Draw() ;
  
  
  /*TLatex* text1 = new TLatex(0.47, 0.82, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.05);
  TLatex* text2 = new TLatex(0.5, 0.77, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.5, 0.72, "-#nu events");
  //TLatex* text3 = new TLatex(0.5, 0.72, "-#tagged neutrons");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();*/
#endif
}

