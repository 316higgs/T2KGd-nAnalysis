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

void SelectedEvents(bool beammode) {

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
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;

//Neutrino events
#if 1
  TH1F* h1_CCQE_numu     = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode0");
  TH1F* h1_CC2p2h_numu   = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode1");
  TH1F* h1_CCOther_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode2");
  TH1F* h1_NC_numu       = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar     = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode0");
  TH1F* h1_CC2p2h_numubar   = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode1");
  TH1F* h1_CCOther_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode2");
  TH1F* h1_NC_numubar       = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_1RmuonEvents_mode3");
  h1_CCQE_numubar -> SetStats(0);
#endif

//Tagged neutrons
#if 0
  TH1F* h1_CCQE_numu     = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_numu   = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_numu  = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_numu       = (TH1F*)fin_numu->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar     = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode0");
  TH1F* h1_CC2p2h_numubar   = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode1");
  TH1F* h1_CCOther_numubar  = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode2");
  TH1F* h1_NC_numubar       = (TH1F*)fin_numubar->Get("Gd1RmuonSelection/h1_SelTagN_mode3");
  h1_CCQE_numubar -> SetStats(0);
#endif

  h1_CCQE_numu     -> SetLineColor(kAzure-1);
  h1_CCQE_numu     -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu   -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu   -> SetFillColor(kAzure-5);
  h1_CCOther_numu  -> SetLineColor(kCyan-8);
  h1_CCOther_numu  -> SetFillColor(kCyan-8);
  h1_NC_numu       -> SetLineColor(kSpring-9);
  h1_NC_numu       -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_NC_numubar      -> SetFillColor(kSpring-9);
  
  h1_CCQE_numu        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar     -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu          -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar       -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_NuEvt = new THStack("hs_NuEvt", "");
#if fhcflag
  hs_NuEvt -> Add(h1_NC_numubar);
  hs_NuEvt -> Add(h1_NC_numu);
  hs_NuEvt -> Add(h1_CCOther_numubar);
  hs_NuEvt -> Add(h1_CCOther_numu);
  hs_NuEvt -> Add(h1_CC2p2h_numubar);
  hs_NuEvt -> Add(h1_CC2p2h_numu);
  hs_NuEvt -> Add(h1_CCQE_numubar);
  hs_NuEvt -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_NuEvt -> Add(h1_NC_numu);
  hs_NuEvt -> Add(h1_NC_numubar);
  hs_NuEvt -> Add(h1_CCOther_numu);
  hs_NuEvt -> Add(h1_CCOther_numubar);
  hs_NuEvt -> Add(h1_CC2p2h_numu);
  hs_NuEvt -> Add(h1_CC2p2h_numubar);
  hs_NuEvt -> Add(h1_CCQE_numu);
  hs_NuEvt -> Add(h1_CCQE_numubar);
#endif

  TH1F* h1_SelEff_merge = new TH1F("h1_SelEff_merge", "", 6, 0, 6);
  h1_SelEff_merge -> Add(h1_CCQE_numu);
  h1_SelEff_merge -> Add(h1_CC2p2h_numu);
  h1_SelEff_merge -> Add(h1_CCOther_numu);
  h1_SelEff_merge -> Add(h1_NC_numu);
  h1_SelEff_merge -> Add(h1_CCQE_numubar);
  h1_SelEff_merge -> Add(h1_CC2p2h_numubar);
  h1_SelEff_merge -> Add(h1_CCOther_numubar);
  h1_SelEff_merge -> Add(h1_NC_numubar);
  float SelecEvFCFV = 0.;
  SelecEvFCFV += h1_CCQE_numu->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_numu->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_numu->GetBinContent(1);
  SelecEvFCFV += h1_NC_numu->GetBinContent(1);
  SelecEvFCFV += h1_CCQE_numubar->GetBinContent(1);
  SelecEvFCFV += h1_CC2p2h_numubar->GetBinContent(1);
  SelecEvFCFV += h1_CCOther_numubar->GetBinContent(1);
  SelecEvFCFV += h1_NC_numubar->GetBinContent(1);
  float SelecEv[6] = {0.};
  for (int i=0; i<6; i++) {
    std::cout << "Cut[" << i+1 << "] numu CCQE: " << h1_CCQE_numu->GetBinContent(i+1) 
              << ", numubar CCQE: " << h1_CCQE_numubar->GetBinContent(i+1)
              << ", numu CC 2p2h: " << h1_CC2p2h_numu->GetBinContent(i+1)
              << ", numubar CC 2p2h: " << h1_CC2p2h_numubar->GetBinContent(i+1)
              << ", numu CC other: " << h1_CCOther_numu->GetBinContent(i+1)
              << ", numubar CC other: " << h1_CCOther_numubar->GetBinContent(i+1)
              << ", NC: " << h1_NC_numu->GetBinContent(i+1)+h1_NC_numubar->GetBinContent(i+1) << std::endl;
    SelecEv[i] += h1_CCQE_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_numu->GetBinContent(i+1);
    SelecEv[i] += h1_NC_numu->GetBinContent(i+1);
    SelecEv[i] += h1_CCQE_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_CC2p2h_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_CCOther_numubar->GetBinContent(i+1);
    SelecEv[i] += h1_NC_numubar->GetBinContent(i+1);
    std::cout << "Cut[" << i+1 << "] Total: " << SelecEv[i] << std::endl;
  }
  h1_SelEff_merge -> Scale(1./SelecEvFCFV);
  for (int i=0; i<6; i++) {
    std::cout << "Cut[" << i+1 << "] Efficiency: " << h1_SelEff_merge->GetBinContent(i+1) << std::endl;
  }
  h1_SelEff_merge -> SetLineColor(kViolet-7);
  h1_SelEff_merge -> SetLineWidth(2);
  h1_SelEff_merge -> SetFillColor(kViolet-9);
  h1_SelEff_merge -> SetFillStyle(3004);
  h1_SelEff_merge -> SetStats(0);
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_SelEff_merge -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");


#if 1
  // No NTag separation
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1", 1000,700);
  c1 -> SetGrid();
  if (beammode) hs_NuEvt -> SetMaximum(130);
  //if (beammode) hs_NuEvt -> SetMaximum(16);
  //else hs_NuEvt -> SetMaximum(10);
  hs_NuEvt -> Draw();
  hs_NuEvt ->GetYaxis()->SetTitleSize(0.038);
  hs_NuEvt ->GetYaxis()->SetTitleOffset(1.3);
  hs_NuEvt ->GetYaxis()->SetLabelSize(0.036);
  hs_NuEvt ->GetYaxis()->SetTitle("Number of #nu Events");
  //hs_NuEvt ->GetYaxis()->SetTitle("Number of Tagged Neutrons");
  hs_NuEvt -> Draw();
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.47, 0.42, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 1
  TCanvas* c2 = new TCanvas("c2","c2",1000,700);
  c2 -> SetGrid();
  h1_SelEff_merge -> SetMinimum(0.);
  h1_SelEff_merge -> SetMaximum(1.1);
  h1_SelEff_merge -> Draw();
  h1_SelEff_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_SelEff_merge ->GetYaxis()->SetTitleOffset(1.3);
  h1_SelEff_merge ->GetYaxis()->SetLabelSize(0.036);
  h1_SelEff_merge ->GetYaxis()->SetTitle("Selection Efficiency");
  h1_SelEff_merge -> Draw();
  c2->RedrawAxis();
  
  TLatex* text1 = new TLatex(0.47, 0.82, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.05);
  TLatex* text2 = new TLatex(0.5, 0.77, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.5, 0.72, "-Efficiency of #nu events");
  //TLatex* text3 = new TLatex(0.5, 0.72, "-Efficiency of tagged neutrons");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
#endif
}