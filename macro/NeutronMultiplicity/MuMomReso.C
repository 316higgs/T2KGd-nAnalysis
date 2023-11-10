#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

void MuMomReso(bool beammode) {

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

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
  Double_t GenN_numubar_x_nuebar  = 63460;
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


  //////  True muon Pt resolution  //////
  TH1F* h1_PtMomReso_numu      = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_MuonPtReso");
  TH1F* h1_PtMomReso_nuesig    = (TH1F*)fin_nuesig->Get("NeutrinoOscillation/h1_MuonPtReso");
  TH1F* h1_PtMomReso_numubar   = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_MuonPtReso");
  TH1F* h1_PtMomReso_nuebarsig = (TH1F*)fin_nuebarsig->Get("NeutrinoOscillation/h1_MuonPtReso");
  TH1F* h1_PtMomReso_nuebkg    = (TH1F*)fin_nuebkg->Get("NeutrinoOscillation/h1_MuonPtReso");
  TH1F* h1_PtMomReso_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NeutrinoOscillation/h1_MuonPtReso");

  TH2F* h2_PtMomReso_x_E_numu      = (TH2F*)fin_numu->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");
  TH2F* h2_PtMomReso_x_E_nuesig    = (TH2F*)fin_nuesig->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");
  TH2F* h2_PtMomReso_x_E_numubar   = (TH2F*)fin_numubar->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");
  TH2F* h2_PtMomReso_x_E_nuebarsig = (TH2F*)fin_nuebarsig->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");
  TH2F* h2_PtMomReso_x_E_nuebkg    = (TH2F*)fin_nuebkg->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");
  TH2F* h2_PtMomReso_x_E_nuebarbkg = (TH2F*)fin_nuebarbkg->Get("NeutrinoOscillation/h2_MuonPtReso_x_E");


  /////  Normalizations  //////
#if 1
  h1_PtMomReso_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PtMomReso_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_PtMomReso_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_PtMomReso_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_PtMomReso_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_PtMomReso_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h2_PtMomReso_x_E_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h2_PtMomReso_x_E_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h2_PtMomReso_x_E_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h2_PtMomReso_x_E_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h2_PtMomReso_x_E_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h2_PtMomReso_x_E_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  /////  Merged capture time  //////
  TH1F* h1_PtMomReso = new TH1F("h1_PtMomReso", "", 800, -50, 50);
  h1_PtMomReso -> SetFillColor(kViolet-8);
  h1_PtMomReso -> SetLineColor(kViolet+3);
  h1_PtMomReso -> SetLineWidth(2);
  h1_PtMomReso -> SetStats(0);
  //h1_PtMomReso -> SetXTitle("P_{T} resolution (P_{T}^{reco} - P_{T}^{true})/P_{T}^{true}");
  h1_PtMomReso -> SetXTitle("P_{T} resolution P_{T}^{reco} - P_{T}^{true}");
  h1_PtMomReso -> SetYTitle("Number of Neutrino Events");
  h1_PtMomReso -> GetXaxis()->SetTitleSize(0.045);
  h1_PtMomReso -> GetYaxis()->SetTitleSize(0.045);

  TH2F* h2_PtMomReso_x_E = new TH2F("h2_PtMomReso_x_E", "", 60, 0, 3000, 80, -50, 50);
  h2_PtMomReso_x_E -> SetFillColor(kViolet-8);
  h2_PtMomReso_x_E -> SetLineColor(kViolet+3);
  h2_PtMomReso_x_E -> SetLineWidth(2);
  h2_PtMomReso_x_E -> SetStats(0);
  h2_PtMomReso_x_E -> SetXTitle("Reconstructed #nu energy [MeV]");
  h2_PtMomReso_x_E -> SetYTitle("P_{T} resolution P_{T}^{reco} - P_{T}^{true}");
  h2_PtMomReso_x_E -> GetXaxis()->SetTitleSize(0.045);
  h2_PtMomReso_x_E -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_PtMomReso -> Add(h1_PtMomReso_nuebarbkg);
  h1_PtMomReso -> Add(h1_PtMomReso_nuebkg);
  h1_PtMomReso -> Add(h1_PtMomReso_nuebarsig);
  h1_PtMomReso -> Add(h1_PtMomReso_numubar);
  h1_PtMomReso -> Add(h1_PtMomReso_nuesig);
  h1_PtMomReso -> Add(h1_PtMomReso_numu);

  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_nuebarbkg);
  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_nuebkg);
  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_nuebarsig);
  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_numubar);
  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_nuesig);
  h2_PtMomReso_x_E -> Add(h2_PtMomReso_x_E_numu);
#endif


  TF1* f1 = new TF1("f", "[0] * exp( -(x - [1])*(x - [1]) / (2*[2]*[2]) )", -20, 20);
  f1 -> SetParameter(0, 10); 
  f1 -> SetParameter(1, 3);
  f1 -> SetParameter(2, 1);
  f1 -> SetLineColor(kPink-8);
  f1 -> SetLineWidth(3);
  f1 -> SetNpx(10000);


  
  gStyle->SetOptFit(1111);
  gROOT -> SetStyle("Plain");
  /////////// Muon Pt resolution //////////
#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_PtMomReso -> SetMaximum(0.8);
  h1_PtMomReso -> Fit(f1, "rLL");
  h1_PtMomReso -> Draw("");
  f1 -> Draw("SAME");
  c1->RedrawAxis();

  Double_t Sigma = f1->GetParameter(2);
  Double_t SigmaErr = f1->GetParError(2);

  TLegend* legend1 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (T2K Run11)}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_PtMomReso, "0.01% Gd MC", "F");
  //legend1 -> AddEntry(f1, "A*(1-e^{-B*t})*exp(-x/C)+D", "L");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{#sigma = %.3f MeV}", Sigma),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h2_PtMomReso_x_E -> Draw("COLZ");
  c1->RedrawAxis();
#endif


}
