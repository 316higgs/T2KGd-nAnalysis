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
#define nThreshold 0.7


void mergeTagEff_x_dist(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;

  TFile* fin_promptkeras_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.promptkeras.root");        /// prompt_keras
  //TFile* fin_promptkeras_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.promptkeras.root");         /// prompt_keras
  //TFile* fin_promptkeras_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.promptkeras.root");  /// prompt_keras
  //TFile* fin_promptkeras_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.promptkeras.root");   /// prompt_keras
  //TFile* fin_promptkeras_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.promptkeras.root");          /// prompt_keras
  //TFile* fin_promptkeras_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.promptkeras.root");    /// prompt_keras

  TFile* fin_bonsaikeras_ToF_numu = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");  /// ToF bonsai_keras


  TFile* fin_bonsaikeras_numu     = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras.root");      /// no-ToF bonsai_keras


  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");



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



  //////  prompt Keras w/ ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_promptkeras_numu = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_promptkeras_numu  = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_promptkeras_numu    = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");

  //////  BONSAI Keras w/ ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_bonsaikeras_ToF_numu = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_bonsaikeras_ToF_numu  = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_bonsaikeras_ToF_numu    = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");
  

  //////  BONSAI Keras w/o ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_bonsaikeras_numu = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_bonsaikeras_numu  = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_bonsaikeras_numu    = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");



  TH1D* h1_TrueD_numu      = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_truedistance");
  //TH1D* h1_TrueD_nuesig    = (TH1D*)fin_promptkeras_nuesig->Get("DistanceViewer/h1_truedistance");
  //TH1D* h1_TrueD_numubar   = (TH1D*)fin_promptkeras_numubar->Get("DistanceViewer/h1_truedistance");
  //TH1D* h1_TrueD_nuebarsig = (TH1D*)fin_promptkeras_nuebarsig->Get("DistanceViewer/h1_truedistance");
  //TH1D* h1_TrueD_nuebkg    = (TH1D*)fin_promptkeras_nuebkg->Get("DistanceViewer/h1_truedistance");
  //TH1D* h1_TrueD_nuebarbkg = (TH1D*)fin_promptkeras_nuebarbkg->Get("DistanceViewer/h1_truedistance");

  TH1D* h1_nCanD_promptkeras_numu = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_Candidatetruedistance");

  float ThrNum = nThreshold/0.05;
  std::cout << "n-like threshold: " << nThreshold << " (#" << (int)ThrNum << ")" << std::endl;
  TH1D* h1_TagnD_promptkeras_numu      = (TH1D*)fin_promptkeras_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  //TH1D* h1_TagnD_promptkeras_nuesig    = (TH1D*)fin_promptkeras_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  //TH1D* h1_TagnD_promptkeras_numubar   = (TH1D*)fin_promptkeras_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  //TH1D* h1_TagnD_promptkeras_nuebarsig = (TH1D*)fin_promptkeras_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  //TH1D* h1_TagnD_promptkeras_nuebkg    = (TH1D*)fin_promptkeras_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  //TH1D* h1_TagnD_promptkeras_nuebarbkg = (TH1D*)fin_promptkeras_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));


/////  Normalizations  //////
#if 1
  h1_TrueD_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_TrueD_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_TrueD_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_TrueD_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  //h1_TrueD_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_TrueD_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagnD_promptkeras_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_TagnD_promptkeras_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_TagnD_promptkeras_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_TagnD_promptkeras_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  //h1_TagnD_promptkeras_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_TagnD_promptkeras_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


#if 1
  TH1F* h1_TrueD_merge = new TH1F("h1_TrueD", "", 10, 0, 5);
  h1_TrueD_merge -> Add(h1_TrueD_numu);
  //h1_TrueD_merge -> Add(h1_TrueD_nuesig);
  //h1_TrueD_merge -> Add(h1_TrueD_numubar);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebarsig);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebkg);
  //h1_TrueD_merge -> Add(h1_TrueD_nuebarbkg);


  TH1F* h1_TagEff_promptkeras_merge = new TH1F("h1_TagEff_promptkeras", "", 10, 0, 5);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numu);
  //h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuesig);
  //h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numubar);
  //h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarsig);
  //h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebkg);
  //h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarbkg);
#endif


  h1_TagEff_promptkeras_merge -> SetLineColor(kAzure+7);
  h1_TagEff_promptkeras_merge -> SetLineWidth(3);
  h1_TagEff_promptkeras_merge -> SetStats(0);
  h1_TagEff_promptkeras_merge -> SetTitleOffset(0.9, "Y");
  h1_TagEff_promptkeras_merge ->GetXaxis()->SetTitleSize(0.045);
  h1_TagEff_promptkeras_merge ->GetYaxis()->SetTitleSize(0.045);
  h1_TagEff_promptkeras_merge -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_TagEff_promptkeras_merge -> SetYTitle("Overall Tagging Efficiency");


  h1_PreEff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_PreEff_promptkeras_numu -> SetLineWidth(3);
  h1_PreEff_promptkeras_numu -> SetStats(0);
  h1_PreEff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_PreEff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_PreEff_promptkeras_numu -> SetYTitle("Pre-selection Efficiency");

  h1_PreEff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_PreEff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_PreEff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_PreEff_bonsaikeras_numu -> SetLineWidth(3);

  h1_NNEff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_NNEff_promptkeras_numu -> SetLineWidth(3);
  h1_NNEff_promptkeras_numu -> SetStats(0);
  h1_NNEff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_NNEff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_NNEff_promptkeras_numu -> SetYTitle("NN Classification Efficiency");

  h1_NNEff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_NNEff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_NNEff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_NNEff_bonsaikeras_numu -> SetLineWidth(3);

  h1_Eff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_Eff_promptkeras_numu -> SetLineWidth(3);
  h1_Eff_promptkeras_numu -> SetStats(0);
  h1_Eff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_Eff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_Eff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_Eff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_Eff_promptkeras_numu -> SetYTitle("Overall Tagging Efficiency");

  h1_Eff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_Eff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_Eff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_Eff_bonsaikeras_numu -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.13, 0.16, 0.55, 0.35);
  legend1 -> SetTextSize(0.035);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (#nu_{#mu}#rightarrow#nu_{#mu})}","");
  legend1 -> AddEntry(h1_Eff_promptkeras_numu, "prompt Keras", "L");
  legend1 -> AddEntry(h1_Eff_bonsaikeras_ToF_numu, "BONSAI Keras", "L");
  legend1 -> AddEntry(h1_Eff_bonsaikeras_numu, "BONSAI Keras (no ToF)", "L");
  legend1 -> SetFillColor(0);

  TLegend* legend2 = new TLegend(0.13, 0.13, 0.6, 0.35);
  legend2 -> SetTextSize(0.035);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample (#nu_{#mu}#rightarrow#nu_{#mu})}","");
  //legend2 -> AddEntry((TObject*)0,"#kern[-0]{NN: Keras trained by SKG4 single n MC}","");
  legend2 -> AddEntry(h1_Eff_promptkeras_numu, "prompt Keras", "L");
  legend2 -> AddEntry(h1_Eff_bonsaikeras_ToF_numu, "BONSAI Keras", "L");
  legend2 -> AddEntry(h1_Eff_bonsaikeras_numu, "BONSAI Keras (no ToF)", "L");
  legend2 -> AddEntry((TObject*)0,"#kern[-0]{ (n-like threshold: 0.7)}","");
  legend2 -> SetFillColor(0);
  

#if 1
  /// Pre-selection ////////////////////////////////
  TCanvas* cpreeff = new TCanvas("cpreeff","cpreeff", 900, 700);
  cpreeff -> SetGrid();
  cpreeff -> cd();
  h1_PreEff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0.2, 1.0);
  h1_PreEff_promptkeras_numu     -> Draw();
  h1_PreEff_bonsaikeras_ToF_numu -> Draw("SAME");
  h1_PreEff_bonsaikeras_numu     -> Draw("SAME");
  legend1 -> Draw();
#endif


#if 1
  /// NN classification ////////////////////////////////
  TCanvas* cnneff = new TCanvas("cnneff","cnneff", 900, 700);
  cnneff -> SetGrid();
  cnneff -> cd();
  h1_NNEff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0., 1.0);
  h1_NNEff_promptkeras_numu     -> Draw();
  h1_NNEff_bonsaikeras_ToF_numu -> Draw("SAME");
  h1_NNEff_bonsaikeras_numu     -> Draw("SAME");
  legend2 -> Draw();
#endif 

  /// Overall ////////////////////////////////
  TCanvas* cEff = new TCanvas("cEff","Overall Eff", 900, 700);
  cEff -> SetGrid();
  cEff -> cd();
  h1_Eff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0., 0.7);
  h1_Eff_promptkeras_numu     -> Draw();
  h1_Eff_bonsaikeras_ToF_numu -> Draw("SAME");
  h1_Eff_bonsaikeras_numu     -> Draw("SAME");
  legend2 -> Draw();
  /*h1_TagEff_promptkeras_merge -> GetYaxis() -> SetRangeUser(0., 0.7);
  h1_TagEff_promptkeras_merge -> Sumw2();
  h1_TagEff_promptkeras_merge -> Divide(h1_TrueD_merge);
  h1_TagEff_promptkeras_merge -> Draw("histo");*/

}

