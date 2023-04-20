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


void CompareDecaye(bool beammode) {

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
  //Gd MC
  //TFile* fin_numu_gd    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numubar_gd = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");
  TFile* fin_numu_gd    = new TFile("../../output/fhc/fhc.numu_x_numu.root");
  TFile* fin_numubar_gd = new TFile("../../output/fhc/fhc.numubar_x_numubar.root");

  //Pure water MC
  TFile* fin_numu_pw    = new TFile("../../output/fhc/numu_x_numu.water.root");
  TFile* fin_numubar_pw = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu_gd    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar_gd = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  TH1F* h1_numu_gd[4];
  TH1F* h1_numubar_gd[4];
  TH1F* h1_numu_boxgd[4];
  TH1F* h1_numubar_boxgd[4];

  TH1F* h1_numu_pw[4];
  TH1F* h1_numubar_pw[4];

  TH1F* h1_DcyE_gd[4];
  TH1F* h1_DcyE_boxgd[4];

  TH1F* h1_DcyE_pw[4];

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


  TH1F* h1_numu_boxgd[0] = (TH1F*)fin_numu_gd->Get("Gd1RmuonSelection/h1_Decaye_mode0");  //Legacy
  TH1F* h1_numu_boxgd[1] = (TH1F*)fin_numu_gd->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  TH1F* h1_numu_boxgd[3] = (TH1F*)fin_numu_gd->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  TH1F* h1_numu_boxgd[2] = (TH1F*)fin_numu_gd->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  TH1F* h1_numu_gd[0] = (TH1F*)fin_numu_gd->Get("DecayeBox/h1_TaggedDecaye_mode0");  // box cut
  TH1F* h1_numu_gd[1] = (TH1F*)fin_numu_gd->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_numu_gd[3] = (TH1F*)fin_numu_gd->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_numu_gd[2] = (TH1F*)fin_numu_gd->Get("DecayeBox/h1_TaggedDecaye_mode2");
  TH1F* h1_numu_pw[0] = (TH1F*)fin_numu_pw->Get("DecayeBox/h1_TaggedDecaye_mode0");  //Legacy
  TH1F* h1_numu_pw[1] = (TH1F*)fin_numu_pw->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_numu_pw[3] = (TH1F*)fin_numu_pw->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_numu_pw[2] = (TH1F*)fin_numu_pw->Get("DecayeBox/h1_TaggedDecaye_mode2");
  //TH1F* h1_numu_pw[0] = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_Decaye_mode0");  // box cut
  //TH1F* h1_numu_pw[1] = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  //TH1F* h1_numu_pw[3] = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  //TH1F* h1_numu_pw[2] = (TH1F*)fin_numu_pw->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_numu_gd[0] -> SetStats(0);
  h1_numu_boxgd[0] -> SetStats(0);

  TH1F* h1_numubar_boxgd[0] = (TH1F*)fin_numubar_gd->Get("Gd1RmuonSelection/h1_Decaye_mode0");
  TH1F* h1_numubar_boxgd[1] = (TH1F*)fin_numubar_gd->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  TH1F* h1_numubar_boxgd[3] = (TH1F*)fin_numubar_gd->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  TH1F* h1_numubar_boxgd[2] = (TH1F*)fin_numubar_gd->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  TH1F* h1_numubar_gd[0] = (TH1F*)fin_numubar_gd->Get("DecayeBox/h1_TaggedDecaye_mode0");
  TH1F* h1_numubar_gd[1] = (TH1F*)fin_numubar_gd->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_numubar_gd[3] = (TH1F*)fin_numubar_gd->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_numubar_gd[2] = (TH1F*)fin_numubar_gd->Get("DecayeBox/h1_TaggedDecaye_mode2");
  TH1F* h1_numubar_pw[0] = (TH1F*)fin_numubar_pw->Get("DecayeBox/h1_TaggedDecaye_mode0");  //Legacy
  TH1F* h1_numubar_pw[1] = (TH1F*)fin_numubar_pw->Get("DecayeBox/h1_TaggedDecaye_mode1");
  TH1F* h1_numubar_pw[3] = (TH1F*)fin_numubar_pw->Get("DecayeBox/h1_TaggedDecaye_mode3");
  TH1F* h1_numubar_pw[2] = (TH1F*)fin_numubar_pw->Get("DecayeBox/h1_TaggedDecaye_mode2");
  //TH1F* h1_numubar_pw[0] = (TH1F*)fin_numubar_pw->Get("Gd1RmuonSelection/h1_Decaye_mode0");  // box cut
  //TH1F* h1_numubar_pw[1] = (TH1F*)fin_numubar_pw->Get("Gd1RmuonSelection/h1_Decaye_mode1");
  //TH1F* h1_numubar_pw[3] = (TH1F*)fin_numubar_pw->Get("Gd1RmuonSelection/h1_Decaye_mode3");
  //TH1F* h1_numubar_pw[2] = (TH1F*)fin_numubar_pw->Get("Gd1RmuonSelection/h1_Decaye_mode2");
  h1_numubar_gd[0] -> SetStats(0);
  h1_numubar_boxgd[0] -> SetStats(0);

  //Legacy decay-e
  h1_numu_gd[0] -> SetLineColor(kAzure-1);
  h1_numu_gd[1] -> SetLineColor(kAzure-5);
  h1_numu_gd[2] -> SetLineColor(kCyan-6);
  h1_numu_gd[3] -> SetLineColor(kSpring-9);

  h1_numu_gd[0] -> SetFillColor(kAzure-1);
  h1_numu_gd[1] -> SetFillColor(kAzure-5);
  h1_numu_gd[2] -> SetFillColor(kCyan-6);
  h1_numu_gd[3] -> SetFillColor(kSpring-9);

  h1_numubar_gd[0] -> SetLineColor(kOrange+7);
  h1_numubar_gd[1] -> SetLineColor(kOrange+0);
  h1_numubar_gd[2] -> SetLineColor(kOrange+0);
  h1_numubar_gd[3] -> SetLineColor(kSpring-9);

  h1_numubar_gd[0] -> SetFillColor(kOrange+7);
  h1_numubar_gd[1] -> SetFillColor(kOrange+0);
  h1_numubar_gd[2] -> SetFillColor(kOrange+0);
  h1_numubar_gd[3] -> SetFillColor(kSpring-9);
  //Box cut decay-e
  h1_numu_boxgd[0] -> SetLineColor(kAzure-1);
  h1_numu_boxgd[1] -> SetLineColor(kAzure-5);
  h1_numu_boxgd[2] -> SetLineColor(kCyan-6);
  h1_numu_boxgd[3] -> SetLineColor(kSpring-9);

  h1_numu_boxgd[0] -> SetFillColor(kAzure-1);
  h1_numu_boxgd[1] -> SetFillColor(kAzure-5);
  h1_numu_boxgd[2] -> SetFillColor(kCyan-6);
  h1_numu_boxgd[3] -> SetFillColor(kSpring-9);

  h1_numubar_boxgd[0] -> SetLineColor(kOrange+7);
  h1_numubar_boxgd[1] -> SetLineColor(kOrange+0);
  h1_numubar_boxgd[2] -> SetLineColor(kOrange+0);
  h1_numubar_boxgd[3] -> SetLineColor(kSpring-9);

  h1_numubar_boxgd[0] -> SetFillColor(kOrange+7);
  h1_numubar_boxgd[1] -> SetFillColor(kOrange+0);
  h1_numubar_boxgd[2] -> SetFillColor(kOrange+0);
  h1_numubar_boxgd[3] -> SetFillColor(kSpring-9);

  //Legacy decay-e
  /*h1_numu_gd[0]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_gd[0] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_gd[1]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_gd[1] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_gd[2]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_gd[2] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_gd[3]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_gd[3] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //Box cut decay-e
  h1_numu_boxgd[0]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_boxgd[0] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_boxgd[1]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_boxgd[1] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_boxgd[2]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_boxgd[2] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_numu_boxgd[3]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_numubar_boxgd[3] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );*/

  for (int i=0; i<4; i++) {
    h1_numu_gd[i]       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_numubar_gd[i]    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_numu_boxgd[i]    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_numubar_boxgd[i] -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
    h1_numu_pw[i]       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
    h1_numubar_pw[i]    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  }

#if 0
  //Legacy decay-e
  THStack* hs_mergeDcyE_gd = new THStack("hs_mergeDcyE_gd", "Number of Decay-e; Number of Decay-e; Number of Events");
#if fhcflag
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[3]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[3]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[2]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[2]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[1]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[1]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[0]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[0]);
#endif
#if rhcflag
  hs_mergeDcyE_gd -> Add(h1_numu_gd[3]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[3]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[2]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[2]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[1]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[1]);
  hs_mergeDcyE_gd -> Add(h1_numu_gd[0]);
  hs_mergeDcyE_gd -> Add(h1_numubar_gd[0]);
#endif
  //Box cut decay-e
  THStack* hs_mergeDcyE_boxgd = new THStack("hs_mergeDcyE_boxgd", "Number of Decay-e; Number of Decay-e; Number of Events");
#if fhcflag
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[3]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[3]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[2]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[2]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[1]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[1]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[0]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[0]);
#endif
#if rhcflag
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[3]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[3]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[2]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[2]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[1]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[1]);
  hs_mergeDcyE_boxgd -> Add(h1_numu_boxgd[0]);
  hs_mergeDcyE_boxgd -> Add(h1_numubar_boxgd[0]);
#endif
#endif


  for (int i=0; i<4; i++) {
    h1_DcyE_gd[i] = new TH1F(TString::Format("h1_DcyE_gd_mode%d", i), "", 6, 0, 6);
    h1_DcyE_gd[i] -> Add(h1_numu_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_numubar_gd[i], 1.);
    h1_DcyE_gd[i] -> SetLineColor(kOrange+0);
    h1_DcyE_gd[i] -> SetLineStyle(7);
    h1_DcyE_gd[i] -> SetLineWidth(2);
    Double_t tot_DcyE_gd = h1_DcyE_gd[i]->Integral();
    h1_DcyE_gd[i] -> Scale(1./tot_DcyE_gd);
    h1_DcyE_gd[i] -> SetStats(0);

    h1_DcyE_boxgd[i] = new TH1F(TString::Format("h1_DcyE_boxgd_mode%d", i), "", 6, 0, 6);
    h1_DcyE_boxgd[i] -> Add(h1_numu_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_numubar_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> SetLineColor(kOrange+0);
    h1_DcyE_boxgd[i] -> SetLineWidth(2);
    Double_t tot_DcyE_boxgd = h1_DcyE_boxgd[i]->Integral();
    h1_DcyE_boxgd[i] -> Scale(1./tot_DcyE_boxgd);

    h1_DcyE_pw[i] = new TH1F(TString::Format("h1_DcyE_pw_mode%d", i), "", 6, 0, 6);
    h1_DcyE_pw[i] -> Add(h1_numu_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_numubar_pw[i], 1.);
    h1_DcyE_pw[i] -> SetLineColor(kAzure+1);
    h1_DcyE_pw[i] -> SetLineWidth(2);
    Double_t tot_DcyE_pw = h1_DcyE_pw[i]->Integral();
    h1_DcyE_pw[i] -> Scale(1./tot_DcyE_pw);
    h1_DcyE_pw[i] -> SetStats(0);
    h1_DcyE_pw[i] -> SetXTitle("Number of Reconstructed Decay-e");
    h1_DcyE_pw[i] -> SetYTitle("Area Normalized");

    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_DcyE_gd[i] -> GetXaxis()->SetBinLabel(6, "5");

    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(6, "5");

    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_DcyE_pw[i] -> GetXaxis()->SetBinLabel(6, "5");
  }



#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_mergeDcyE_gd -> Draw();
  hs_mergeDcyE_gd ->GetYaxis()->SetTitleSize(0.038);
  hs_mergeDcyE_gd ->GetYaxis()->SetTitleOffset(1.3);
  hs_mergeDcyE_gd ->GetYaxis()->SetLabelSize(0.036);
  hs_mergeDcyE_gd -> Draw();
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
  legend1 -> AddEntry(h1_numu_gd[0], "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_numubar_gd[0], "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_numu_gd[1], "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_numubar_gd[1], "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_numu_gd[2], "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_numubar_gd[2], "#bar{#nu}_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#nu_{#mu}+#bar{#nu}_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_numu_gd[3], "NC", "F");
  legend1->SetFillColor(0);
  //legend1->Draw();
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> Divide(2, 2);
  for (int i=0; i<4; i++) {
    c1 -> cd(i+1) -> SetGrid();

    h1_DcyE_gd[i] ->GetXaxis()->SetTitle("Number of Reconstructed Decay-e");
    h1_DcyE_gd[i] ->GetYaxis()->SetTitle("Area Normalized");
    h1_DcyE_gd[i] ->GetYaxis()->SetTitleSize(0.038);
    h1_DcyE_gd[i] ->GetYaxis()->SetTitleOffset(1.3);
    h1_DcyE_gd[i] ->GetYaxis()->SetLabelSize(0.036);
    h1_DcyE_pw[i]    -> Draw();
    h1_DcyE_gd[i]    -> Draw("SAME");
    h1_DcyE_boxgd[i] -> Draw("SAME");

    TLegend* legend1 = new TLegend(0.4, 0.55, 0.89, 0.89);
    legend1 -> SetTextSize(0.04);
    if (i==0) legend1->AddEntry((TObject*)0,"#kern[-1.2]{CCQE}","");
    if (i==1) legend1->AddEntry((TObject*)0,"#kern[-0.8]{CC 2p2h}","");
    if (i==2) legend1->AddEntry((TObject*)0,"#kern[-0.8]{CC other}","");
    if (i==3) legend1->AddEntry((TObject*)0,"#kern[-1.7]{NC}","");
    legend1->AddEntry((TObject*)0,"#kern[-0.5]{C1-C4 applied}","");
    legend1 -> AddEntry(h1_DcyE_pw[i], "Pure water", "L");
    legend1 -> AddEntry(h1_DcyE_gd[i], "Gd: decay-e by #sub-event", "L");
    legend1 -> AddEntry(h1_DcyE_boxgd[i], "Gd: decay-e by box cut", "L");
    legend1->SetFillColor(0);
    legend1->Draw() ;
  }
  
  
#endif

}
