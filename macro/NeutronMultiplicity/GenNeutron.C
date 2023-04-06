#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC

void GenNeutron(bool beammode) {

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
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronMultiplicity.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronMultiplicity.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
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


  TH1F* h1_GenBefSINeutrons_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAftSINeutrons_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenAftSINeutrons");
  h1_GenBefSINeutrons_numu -> SetStats(0);

  TH1F* h1_GenBefSINeutrons_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAftSINeutrons_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenAftSINeutrons");
  h1_GenBefSINeutrons_numubar -> SetStats(0);

//Neutron multiplicity distribution (merged)
#if 0
  h1_GenBefSINeutrons_numu -> SetLineColor(kViolet+2);
  h1_GenAftSINeutrons_numu -> SetLineColor(kAzure+7);
  h1_GenBefSINeutrons_numu -> SetLineWidth(2);
  h1_GenAftSINeutrons_numu -> SetLineWidth(2);

  h1_GenBefSINeutrons_numu -> SetFillColor(kViolet-9);
  h1_GenAftSINeutrons_numu  -> SetFillColor(kAzure-9);

  h1_GenBefSINeutrons_numubar -> SetLineColor(kOrange+8);
  h1_GenAftSINeutrons_numubar -> SetLineColor(kOrange-1);
  h1_GenBefSINeutrons_numubar -> SetLineWidth(2);
  h1_GenAftSINeutrons_numubar -> SetLineWidth(2);

  h1_GenBefSINeutrons_numubar -> SetFillColor(kOrange+6);
  h1_GenAftSINeutrons_numubar -> SetFillColor(kOrange-9);


  h1_GenBefSINeutrons_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenBefSINeutrons_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_GenAftSINeutrons_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_GenAftSINeutrons_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  THStack* hs_GenNeutron_merge = new THStack("hs_GenNeutron_merge", "");
#if fhcflag
  hs_GenNeutron_merge -> Add(h1_GenAftSINeutrons_numubar);
  hs_GenNeutron_merge -> Add(h1_GenAftSINeutrons_numu);
  hs_GenNeutron_merge -> Add(h1_GenBefSINeutrons_numubar);
  hs_GenNeutron_merge -> Add(h1_GenBefSINeutrons_numu);
#endif
#if rhcflag
  hs_GenNeutron_merge -> Add(h1_GenAftSINeutrons_numu);
  hs_GenNeutron_merge -> Add(h1_GenAftSINeutrons_numubar);
  hs_GenNeutron_merge -> Add(h1_GenBefSINeutrons_numu);
  hs_GenNeutron_merge -> Add(h1_GenBefSINeutrons_numubar);
#endif

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_GenNeutron_merge -> SetMaximum(150);
  hs_GenNeutron_merge -> Draw();
  hs_GenNeutron_merge ->GetYaxis()->SetTitleSize(0.038);
  hs_GenNeutron_merge ->GetYaxis()->SetTitleOffset(1.3);
  hs_GenNeutron_merge ->GetYaxis()->SetLabelSize(0.036);
  hs_GenNeutron_merge ->GetXaxis()->SetTitle("Generated Neutron Multiplicity");
  hs_GenNeutron_merge ->GetYaxis()->SetTitle("Number of #nu Events");
  hs_GenNeutron_merge -> Draw();
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{True #nu CCQE}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_GenBefSINeutrons_numu, "#nu_{#mu} Before SI", "F");
  legend1 -> AddEntry(h1_GenBefSINeutrons_numubar, "#bar{#nu}_{#mu} Before SI", "F");
  legend1 -> AddEntry(h1_GenAftSINeutrons_numu, "#nu_{#mu} After SI", "F");
  legend1 -> AddEntry(h1_GenAftSINeutrons_numubar, "#bar{#nu}_{#mu} After SI", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif


//Comparison between numu and numubar
#if 1
  h1_GenBefSINeutrons_numu    -> SetLineColor(kViolet+2);
  h1_GenBefSINeutrons_numubar -> SetLineColor(kOrange+8);
  h1_GenBefSINeutrons_numu    -> SetLineWidth(2);
  h1_GenBefSINeutrons_numubar -> SetLineWidth(2);

  Double_t tot_GenBefSINeutrons_numu = h1_GenBefSINeutrons_numu->Integral();
  h1_GenBefSINeutrons_numu -> Scale(1./tot_GenBefSINeutrons_numu);
  Double_t tot_GenBefSINeutrons_numubar = h1_GenBefSINeutrons_numubar->Integral();
  h1_GenBefSINeutrons_numubar -> Scale(1./tot_GenBefSINeutrons_numubar);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //h1_GenBefSINeutrons_numu -> SetMaximum(150);
  h1_GenBefSINeutrons_numu ->GetYaxis()->SetTitleSize(0.038);
  h1_GenBefSINeutrons_numu ->GetYaxis()->SetTitleOffset(1.3);
  h1_GenBefSINeutrons_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefSINeutrons_numu ->GetXaxis()->SetTitle("Generated Neutron Multiplicity");
  h1_GenBefSINeutrons_numu ->GetYaxis()->SetTitle("Area Normalized");
  h1_GenBefSINeutrons_numu -> Draw();
  h1_GenBefSINeutrons_numubar -> Draw("SAME");
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{True #nu CCQE}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_GenBefSINeutrons_numu, "#nu_{#mu} Before SI", "F");
  legend1 -> AddEntry(h1_GenBefSINeutrons_numubar, "#bar{#nu}_{#mu} Before SI", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}

