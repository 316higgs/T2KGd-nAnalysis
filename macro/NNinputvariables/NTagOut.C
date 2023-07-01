#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run11 FHC
#define NTHRESHOLD 0.65


void NTagOut(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << POTSCALE << " x 10^21 POT)" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC (" << POTSCALE << " x 10^21 POT)" << std::endl;

#if fhcflag

  //Pre
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.preNN.newGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.preNN.newGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC.root");

  //Post
  //TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC.root");
  //TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.postNN.newGdMC.root");
  //TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  //TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root");
  //TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.postNN.newGdMC.root");
  //TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC.root");

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


  TH1F* h1_NTagOut_AccNoise_numu = (TH1F*)fin_numu->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_numu   = (TH1F*)fin_numu->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_numu        = (TH1F*)fin_numu->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_numu       = (TH1F*)fin_numu->Get("NNInputVariables/h1_NTagOut_type3");

  TH1F* h1_NTagOut_AccNoise_nuesig = (TH1F*)fin_nuesig->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_nuesig   = (TH1F*)fin_nuesig->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_nuesig        = (TH1F*)fin_nuesig->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_nuesig       = (TH1F*)fin_nuesig->Get("NNInputVariables/h1_NTagOut_type3");

  TH1F* h1_NTagOut_AccNoise_numubar = (TH1F*)fin_numubar->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_numubar   = (TH1F*)fin_numubar->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_numubar        = (TH1F*)fin_numubar->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_numubar       = (TH1F*)fin_numubar->Get("NNInputVariables/h1_NTagOut_type3");

  TH1F* h1_NTagOut_AccNoise_nuebarsig = (TH1F*)fin_nuebarsig->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_nuebarsig   = (TH1F*)fin_nuebarsig->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_nuebarsig        = (TH1F*)fin_nuebarsig->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NNInputVariables/h1_NTagOut_type3");

  TH1F* h1_NTagOut_AccNoise_nuebkg = (TH1F*)fin_nuebkg->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_nuebkg   = (TH1F*)fin_nuebkg->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_nuebkg        = (TH1F*)fin_nuebkg->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_nuebkg       = (TH1F*)fin_nuebkg->Get("NNInputVariables/h1_NTagOut_type3");

  TH1F* h1_NTagOut_AccNoise_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NNInputVariables/h1_NTagOut_type0");
  TH1F* h1_NTagOut_Decaye_nuebarbkg   = (TH1F*)fin_nuebarbkg->Get("NNInputVariables/h1_NTagOut_type1");
  TH1F* h1_NTagOut_H_nuebarbkg        = (TH1F*)fin_nuebarbkg->Get("NNInputVariables/h1_NTagOut_type2");
  TH1F* h1_NTagOut_Gd_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("NNInputVariables/h1_NTagOut_type3");

#if 1
    // Normalization
    h1_NTagOut_Gd_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NTagOut_H_numu        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NTagOut_Decaye_numu   -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_NTagOut_AccNoise_numu -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );

    h1_NTagOut_Gd_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NTagOut_H_nuesig        -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NTagOut_Decaye_nuesig   -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
    h1_NTagOut_AccNoise_nuesig -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );

    h1_NTagOut_Gd_numubar       -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NTagOut_H_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NTagOut_Decaye_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_NTagOut_AccNoise_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

    h1_NTagOut_Gd_nuebarsig       -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NTagOut_H_nuebarsig        -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NTagOut_Decaye_nuebarsig   -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
    h1_NTagOut_AccNoise_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );

    h1_NTagOut_Gd_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NTagOut_H_nuebkg        -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NTagOut_Decaye_nuebkg   -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
    h1_NTagOut_AccNoise_nuebkg -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );

    h1_NTagOut_Gd_nuebarbkg       -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NTagOut_H_nuebarbkg        -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NTagOut_Decaye_nuebarbkg   -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
    h1_NTagOut_AccNoise_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  THStack* hs_NTagOut = new THStack("hs_NTagOut", "");
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_numu);
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_nuesig);
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_numubar);
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_nuebarsig);
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_nuebkg);
  hs_NTagOut -> Add(h1_NTagOut_AccNoise_nuebarbkg);

  hs_NTagOut -> Add(h1_NTagOut_Decaye_numu);
  hs_NTagOut -> Add(h1_NTagOut_Decaye_nuesig);
  hs_NTagOut -> Add(h1_NTagOut_Decaye_numubar);
  hs_NTagOut -> Add(h1_NTagOut_Decaye_nuebarsig);
  hs_NTagOut -> Add(h1_NTagOut_Decaye_nuebkg);
  hs_NTagOut -> Add(h1_NTagOut_Decaye_nuebarbkg);

  hs_NTagOut -> Add(h1_NTagOut_H_numu);
  hs_NTagOut -> Add(h1_NTagOut_H_nuesig);
  hs_NTagOut -> Add(h1_NTagOut_H_numubar);
  hs_NTagOut -> Add(h1_NTagOut_H_nuebarsig);
  hs_NTagOut -> Add(h1_NTagOut_H_nuebkg);
  hs_NTagOut -> Add(h1_NTagOut_H_nuebarbkg);

  hs_NTagOut -> Add(h1_NTagOut_Gd_numu);
  hs_NTagOut -> Add(h1_NTagOut_Gd_nuesig);
  hs_NTagOut -> Add(h1_NTagOut_Gd_numubar);
  hs_NTagOut -> Add(h1_NTagOut_Gd_nuebarsig);
  hs_NTagOut -> Add(h1_NTagOut_Gd_nuebkg);
  hs_NTagOut -> Add(h1_NTagOut_Gd_nuebarbkg);

  /*
  h1_NTagOut_AccNoise_numu -> SetFillColorAlpha(kGray+2, 0.5);
  h1_NTagOut_Decaye_numu   -> SetFillColorAlpha(kYellow-3, 0.3);
  h1_NTagOut_H_numu        -> SetFillColorAlpha(kAzure-4, 0.3);
  h1_NTagOut_Gd_numu       -> SetFillColorAlpha(kTeal-5, 0.3);
  */

  h1_NTagOut_AccNoise_numu -> SetStats(0);
  h1_NTagOut_AccNoise_numu ->GetYaxis()->SetTitleSize(0.038);
  h1_NTagOut_AccNoise_numu ->GetYaxis()->SetTitleOffset(1.3);
  h1_NTagOut_AccNoise_numu ->GetYaxis()->SetLabelSize(0.036);

  float y[2] = {0., 200.};
  float xC[2] = {NTHRESHOLD, NTHRESHOLD};
  TGraph* g_C = new TGraph(2, xC, y);
  g_C -> SetLineWidth(2);
  g_C -> SetLineColor(kViolet-8);
  g_C -> SetLineStyle(7);

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  c1 -> SetLogy();

#if 1
  hs_NTagOut -> Draw();
  hs_NTagOut ->GetYaxis()->SetTitleSize(0.038);
  hs_NTagOut ->GetYaxis()->SetTitleOffset(1.3);
  hs_NTagOut ->GetYaxis()->SetLabelSize(0.036);
  hs_NTagOut -> GetXaxis()->SetTitle("n-likelihood");
  hs_NTagOut -> GetYaxis()->SetTitle("Number of Candidates in Pre-selection");
  hs_NTagOut -> Draw();
  g_C        -> Draw("SAME");
  c1 -> RedrawAxis();
#endif

#if 0
  h1_NTagOut_AccNoise_numu -> Draw();
  h1_NTagOut_Gd_numu -> Draw("SAME");
  h1_NTagOut_H_numu -> Draw("SAME");
  h1_NTagOut_Decaye_numu -> Draw("SAME");
#endif

  TLegend* legend1 = new TLegend(0.55, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.03);
  //legend1->AddEntry((TObject*)0,"#kern[-0.3]{ FHC 1R#mu sample (#nu_{#mu}#rightarrow#nu_{#mu}) }","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{ FHC #bar{#nu}_{#mu} #rightarrow #bar{#nu}_{#mu} MC }","");
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_NTagOut_Gd_numu, "Gd-n signal", "F");
  legend1 -> AddEntry(h1_NTagOut_H_numu, "H-n signal", "F");
  legend1 -> AddEntry(h1_NTagOut_Decaye_numu, "Decay-e", "F");
  legend1 -> AddEntry(h1_NTagOut_AccNoise_numu, "Acc. noise", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;

}