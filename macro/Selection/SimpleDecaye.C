#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void SimpleDecaye(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << POTSCALE << "x10^21 POT" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC " << POTSCALE << "x10^21 POT" << std::endl;

  //FHC
#if fhcflag
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.beforecut.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection.beforecut.root");
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection.aftercut.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection.aftercut.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  //TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection.beforecut.root");
  //TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection.beofrecut.root");
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection.aftercut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection.aftercut.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("DecayeBox/h1_TrueDecaye_mode6");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode1");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode2");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("DecayeBox/h1_TrueDecaye_mode6");
  h1_CCQE_numubar -> SetStats(0);

  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  //h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CC2p2h_numu  -> SetLineColor(kOrange+0);
  //h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_CCOther_numu -> SetLineColor(kOrange+0);
  h1_NC_numu      -> SetLineColor(kSpring-9);

  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  //h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CC2p2h_numu  -> SetFillColor(kOrange+0);
  //h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_CCOther_numu -> SetFillColor(kOrange+0);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  //h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+0);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  //h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+0);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  std::cout << "numu    CCQE: " << h1_CCQE_numu->Integral() << std::endl;
  std::cout << "numubar CCQE: " << h1_CCQE_numubar->Integral() << std::endl;
  std::cout << "CC non-QE   : " << h1_CC2p2h_numu->Integral()+h1_CC2p2h_numubar->Integral()+h1_CCOther_numu->Integral()+h1_CCOther_numubar->Integral() << std::endl;
  std::cout << "NC          : " << h1_NC_numu->Integral()+h1_NC_numubar->Integral() << std::endl;

  float start   = 0.;
  float interval = 1.;
  const int BINS = 3;
  int binnumber = h1_CCQE_numu->FindBin(start);
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisdecaye = start + ibin*interval;
    std::cout << "# of decay-e = " <<  thisdecaye << std::endl;
    std::cout << "  numu    CCQE: " << h1_CCQE_numu->GetBinContent(binnumber) << std::endl; 
    std::cout << "  numubar CCQE: " << h1_CCQE_numubar->GetBinContent(binnumber) << std::endl; 
    std::cout << "  CC non-QE   : " << h1_CC2p2h_numu->GetBinContent(binnumber)+h1_CC2p2h_numubar->GetBinContent(binnumber)+h1_CCOther_numu->GetBinContent(binnumber)+h1_CCOther_numubar->GetBinContent(binnumber) << std::endl;
    std::cout << "  NC          : " << h1_NC_numu->GetBinContent(binnumber)+h1_NC_numubar->GetBinContent(binnumber) << std::endl;
    binnumber++;
  }


  THStack* hs_TrueDecaye = new THStack("hs_TrueDecaye", "Number of Decay-e; Number of Truth Decay-e; Number of Events");
#if fhcflag
  hs_TrueDecaye -> Add(h1_NC_numubar);
  hs_TrueDecaye -> Add(h1_NC_numu);
  hs_TrueDecaye -> Add(h1_CCOther_numubar);
  hs_TrueDecaye -> Add(h1_CCOther_numu);
  hs_TrueDecaye -> Add(h1_CC2p2h_numubar);
  hs_TrueDecaye -> Add(h1_CC2p2h_numu);
  hs_TrueDecaye -> Add(h1_CCQE_numubar);
  hs_TrueDecaye -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_TrueDecaye -> Add(h1_NC_numu);
  hs_TrueDecaye -> Add(h1_NC_numubar);
  hs_TrueDecaye -> Add(h1_CCOther_numu);
  hs_TrueDecaye -> Add(h1_CCOther_numubar);
  hs_TrueDecaye -> Add(h1_CC2p2h_numu);
  hs_TrueDecaye -> Add(h1_CC2p2h_numubar);
  hs_TrueDecaye -> Add(h1_CCQE_numu);
  hs_TrueDecaye -> Add(h1_CCQE_numubar);
#endif


#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_TrueDecaye -> Draw();
  hs_TrueDecaye ->GetYaxis()->SetTitleSize(0.038);
  hs_TrueDecaye ->GetYaxis()->SetTitleOffset(1.3);
  hs_TrueDecaye ->GetYaxis()->SetLabelSize(0.036);
  hs_TrueDecaye -> Draw();
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#nu_{#mu}+#bar{#nu}_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}