#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define CUTSTEP 21
#define nThreshold 0.7

void mergeEff(bool beammode) {
  
  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  //FHC
#if fhcflag
  
#if 0  
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");*/
#endif

#if 1
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras.root");
#endif

#if 0
  ////  -30%  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIm30.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIm30.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIm30.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIm30.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIm30.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIm30.root");
#endif

#if 0
  ////  +30%  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIp30.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIp30.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIp30.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIp30.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIp30.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIp30.root");
#endif

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar  = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue         = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar   = (TH1F*)fin_skrate->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar    = h1_skrate_numubar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue           = h1_skrate_nue_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar     = h1_skrate_nuebar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu       = 63622;
  Double_t GenN_numu_x_nue        = 63538;
  Double_t GenN_numubar_x_numubar = 63444;
  Double_t GenN_numubar_x_nuebar  = 63463;
  Double_t GenN_nue_x_nue         = 63423;
  Double_t GenN_nuebar_x_nuebar   = 63652;
  std::cout << "Misc. factor: " << (NA*FV*1.e-6) / (50.e-3) << std::endl;
  std::cout << "[numu  -> numu ] ExpN_numu_x_numu = " << h1_skrate_numu_x_numu->Integral() << std::endl;
  std::cout << "[numu  -> numu ] GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "[numu  -> numu ] Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "[numu  -> nue  ] ExpN_numu_x_nue = " << h1_skrate_numu_x_nue->Integral() << std::endl;
  std::cout << "[numu  -> nue  ] GenN_numu_x_nue = " << GenN_numu_x_nue << std::endl;
  std::cout << "[numu  -> nue  ] Normalization factor for numu_x_nue       : " << (ExpN_numu_x_nue)/(GenN_numu_x_nue) << std::endl;
  std::cout << "[numub -> numub] ExpN_numubar_x_numubar = " << h1_skrate_numubar_x_numubar->Integral() << std::endl;
  std::cout << "[numub -> numub] GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "[numub -> numub] Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;
  std::cout << "[numub -> nueb ] ExpN_numubar_x_nuebar = " << h1_skrate_numubar_x_nuebar->Integral() << std::endl;
  std::cout << "[numub -> nueb ] GenN_numubar_x_nuebar = " << GenN_numubar_x_nuebar << std::endl;
  std::cout << "[numub -> nueb ] Normalization factor for numubar_x_nuebar: " << (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) << std::endl;
  std::cout << "[nue   -> nue  ] ExpN_nue_x_nue = " << h1_skrate_nue_x_nue->Integral() << std::endl;
  std::cout << "[nue   -> nue  ] GenN_nue_x_nue = " << GenN_nue_x_nue << std::endl;
  std::cout << "[nue   -> nue  ] Normalization factor for nue_x_nue: " << (ExpN_nue_x_nue)/(GenN_nue_x_nue) << std::endl;
  std::cout << "[nueb  -> nueb ] ExpN_nuebar_x_nuebar = " << h1_skrate_nuebar_x_nuebar->Integral() << std::endl;
  std::cout << "[nueb  -> nueb ] GenN_nuebar_x_nuebar = " << GenN_nuebar_x_nuebar << std::endl;
  std::cout << "[nueb  -> nueb ] Normalization factor for nuebar_x_nuebar: " << (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) << std::endl;


  TH1F* h1_TagTrueN_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_numu       = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_numu     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueN_Gd");

  TH1F* h1_TagTrueN_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_nuesig       = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_nuesig     = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueN_Gd");

  TH1F* h1_TagTrueN_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_numubar       = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_numubar     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueN_Gd");

  TH1F* h1_TagTrueN_nuebarsig    = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_nuebarsig    = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueN_Gd");

  TH1F* h1_TagTrueN_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_nuebkg       = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_nuebkg     = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueN_Gd");

  TH1F* h1_TagTrueN_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagTrueN");
  TH1F* h1_TagTrueN_H_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagTrueN_H");
  TH1F* h1_TagTrueN_Gd_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagTrueN_Gd");
  TH1F* h1_TrueN_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueN");
  TH1F* h1_TrueN_H_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueN_H");
  TH1F* h1_TrueN_Gd_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueN_Gd");

  for (int ith=0; ith<CUTSTEP; ith++) {
    float TMVATH = 0.05*ith;
    if (ith==14) {
      std::cout << " " << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] numu    -> numu    true neutrons: " << h1_TrueN_numu -> GetBinContent(ith+1)      << ", tagged true neutrons: " << h1_TagTrueN_numu -> GetBinContent(ith+1) << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] numu    -> nue     true neutrons: " << h1_TrueN_nuesig -> GetBinContent(ith+1)    << ", tagged true neutrons: " << h1_TagTrueN_nuesig -> GetBinContent(ith+1) << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] numubar -> numubar true neutrons: " << h1_TrueN_numubar -> GetBinContent(ith+1)   << ", tagged true neutrons: " << h1_TagTrueN_numubar -> GetBinContent(ith+1) << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] numubar -> nuebar  true neutrons: " << h1_TrueN_nuebarsig -> GetBinContent(ith+1) << ", tagged true neutrons: " << h1_TagTrueN_nuebarsig -> GetBinContent(ith+1) << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] nue     -> nue     true neutrons: " << h1_TrueN_nuebkg -> GetBinContent(ith+1)    << ", tagged true neutrons: " << h1_TagTrueN_nuebkg -> GetBinContent(ith+1) << std::endl;
      std::cout << "[### n-likelihood=" << TMVATH << " ###] nuebar  -> nuebar  true neutrons: " << h1_TrueN_nuebarbkg -> GetBinContent(ith+1) << ", tagged true neutrons: " << h1_TagTrueN_nuebarbkg -> GetBinContent(ith+1) << std::endl;
      std::cout << " " << std::endl;
    }  
  }


  /////  Normalizations  //////
#if 1
  h1_TagTrueN_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagTrueN_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagTrueN_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagTrueN_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagTrueN_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagTrueN_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueN_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueN_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueN_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueN_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  
  TH1F* h1_TagEff_merge    = new TH1F("h1_TagEff_merge", "", 20, 0, 1);
  TH1F* h1_TagEff_H_merge  = new TH1F("h1_TagEff_H_merge", "", 20, 0, 1);
  TH1F* h1_TagEff_Gd_merge = new TH1F("h1_TagEff_Gd_merge", "", 20, 0, 1);

  TH1F* h1_TrueN_merge    = new TH1F("h1_TrueN_merge", "", 20, 0, 1);
  TH1F* h1_TrueN_H_merge  = new TH1F("h1_TrueN_H_merge", "", 20, 0, 1);
  TH1F* h1_TrueN_Gd_merge = new TH1F("h1_TrueN_Gd_merge", "", 20, 0, 1);

  h1_TagEff_merge    -> SetLineColor(kPink-5);
  h1_TagEff_merge    -> SetFillColor(kPink-2);
  h1_TagEff_merge    -> SetFillStyle(3004);
  h1_TagEff_merge    -> SetLineWidth(2);
  h1_TagEff_merge    -> SetStats(0);

  h1_TagEff_H_merge    -> SetLineColor(kAzure-4);
  h1_TagEff_H_merge    -> SetLineWidth(2);
  h1_TagEff_H_merge    -> SetStats(0);

  h1_TagEff_Gd_merge    -> SetLineColor(kTeal-5);
  h1_TagEff_Gd_merge    -> SetLineWidth(2);
  h1_TagEff_Gd_merge    -> SetStats(0);


  /////  Tagged truth neutrons  /////
  h1_TagEff_merge    -> Add(h1_TagTrueN_numu);
  h1_TagEff_merge    -> Add(h1_TagTrueN_nuesig);
  h1_TagEff_merge    -> Add(h1_TagTrueN_numubar);
  h1_TagEff_merge    -> Add(h1_TagTrueN_nuebarsig);
  h1_TagEff_merge    -> Add(h1_TagTrueN_nuebkg);
  h1_TagEff_merge    -> Add(h1_TagTrueN_nuebarbkg);

  h1_TagEff_H_merge  -> Add(h1_TagTrueN_H_numu);

  h1_TagEff_Gd_merge -> Add(h1_TagTrueN_Gd_numu);

  /////  Truth neutrons  /////
  h1_TrueN_merge    -> Add(h1_TrueN_numu);
  h1_TrueN_merge    -> Add(h1_TrueN_nuesig);
  h1_TrueN_merge    -> Add(h1_TrueN_numubar);
  h1_TrueN_merge    -> Add(h1_TrueN_nuebarsig);
  h1_TrueN_merge    -> Add(h1_TrueN_nuebkg);
  h1_TrueN_merge    -> Add(h1_TrueN_nuebarbkg);

  h1_TrueN_H_merge  -> Add(h1_TrueN_H_numu);

  h1_TrueN_Gd_merge -> Add(h1_TrueN_Gd_numu);


  h1_TagEff_merge -> Sumw2();
  h1_TagEff_merge -> Divide(h1_TrueN_merge);
  h1_TagEff_H_merge -> Sumw2();
  h1_TagEff_H_merge -> Divide(h1_TrueN_H_merge);
  h1_TagEff_Gd_merge -> Sumw2();
  h1_TagEff_Gd_merge -> Divide(h1_TrueN_Gd_merge);

  for (int ith=0; ith<CUTSTEP; ith++) {
    float TMVATH = 0.05*ith;
    std::cout << "[### n-likelihood=" << TMVATH << " ###] Overall Eff.: " << h1_TagEff_merge -> GetBinContent(ith+1)*100. << " %" << std::endl;
  }


#if 0
  TCanvas* c = new TCanvas("c", "c", 700, 700);
  c -> SetGrid();
  h1_TagEff_merge -> Draw();
  h1_TagEff_merge -> SetMinimum(0.);
  h1_TagEff_merge -> SetMaximum(1.);
  h1_TagEff_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_TagEff_merge ->GetYaxis()->SetTitleOffset(1.2);
  //h1_TagEff_merge ->GetYaxis()->SetLabelSize(0.04);
  h1_TagEff_merge ->GetYaxis()->SetTitle("Overall Tagging Efficiency");
  h1_TagEff_merge ->GetYaxis()->SetTitleSize(0.04);
  h1_TagEff_merge ->GetXaxis()->SetTitleSize(0.04);
  h1_TagEff_merge ->GetXaxis()->SetTitle("n-likelihood");
  //h1_TagEff_merge -> Draw("E1");
  h1_TagEff_merge -> Draw("histo");
  //h1_TagEff_H_merge -> Draw("SAME");
  //h1_TagEff_Gd_merge -> Draw("SAME");

  float xMinPos = 1; // x-minimum where you want to set
  float xMaxPos = 1; // x-maximum where you want to set
  float yMinPos = 0; // y-minimum where you want to set
  float yMaxPos = 1; // y-maximum where you want to set
  float SetPos  = 1;
  TGaxis* axis = new TGaxis(xMinPos,yMinPos,xMaxPos,yMaxPos, 0, SetPos, 510, "+L");
  //axis -> SetTitle("Purity");
  //axis -> SetTitleSize(0.035);
  //axis -> SetTitleColor(kPink-5);
  axis -> SetLabelColor(kWhite);
  //axis -> SetLabelSize(0.035);
  axis -> Draw();

  TLatex* text1 = new TLatex(0.35, 0.77, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);
  TLatex* text2 = new TLatex(0.38, 0.72, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.38, 0.67, "-Gd(n,#gamma)+p(n,#gamma)");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
#endif

}
