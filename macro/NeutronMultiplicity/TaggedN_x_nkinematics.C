#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
#define POTSCALE 0.17  //Run11 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void TaggedN_x_nkinematics(bool beammode) {

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


  //TString KnmtcName = "nTraveld";
  //TString KnmtcName = "nTraveldL";
  //TString KnmtcName = "nTraveldT";
  TString KnmtcName = "nAngle";
  //TString KnmtcName = "MuStp_NCap";

  TString Prefix      = "NTagAnalysis/h1_TaggedN_x_";
  TString CCQEName    = "_mode0";
  TString CC2p2hName  = "_mode1";
  TString CCOtherName = "_mode2";
  TString NCName      = "_mode3";
  TString NoiseName   = "_mode4";
  TString FileCCQEName    = Prefix+KnmtcName+CCQEName;
  TString FileCC2p2hName  = Prefix+KnmtcName+CC2p2hName;
  TString FileCCOtherName = Prefix+KnmtcName+CCOtherName;
  TString FileNCName      = Prefix+KnmtcName+NCName;
  TString FileNoiseName   = Prefix+KnmtcName+NoiseName;

  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get(FileCCQEName);
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get(FileCC2p2hName);
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get(FileCCOtherName);
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get(FileNCName);
  TH1F* h1_Noise_numu   = (TH1F*)fin_numu->Get(FileNoiseName);
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  TH1F* h1_Noise_numubar   = (TH1F*)fin_numubar->Get(FileNoiseName);
  h1_CCQE_numubar -> SetStats(0);

  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_Noise_numu   -> SetLineColor(kYellow+2);

  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetFillColor(kSpring-9);
  h1_Noise_numu   -> SetFillColor(kYellow+2);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_Noise_numubar   -> SetLineColor(kYellow+2);

  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);
  h1_Noise_numubar   -> SetFillColor(kYellow+2);

  h1_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_Noise_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_Noise_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );


  THStack* hs_merge = new THStack("hs_merge", "");
#if fhcflag
  hs_merge -> Add(h1_Noise_numubar);
  hs_merge -> Add(h1_Noise_numu);
  hs_merge -> Add(h1_NC_numubar);
  hs_merge -> Add(h1_NC_numu);
  hs_merge -> Add(h1_CCOther_numubar);
  hs_merge -> Add(h1_CCOther_numu);
  hs_merge -> Add(h1_CC2p2h_numubar);
  hs_merge -> Add(h1_CC2p2h_numu);
  hs_merge -> Add(h1_CCQE_numubar);
  hs_merge -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_merge -> Add(h1_Noise_numubar);
  hs_merge -> Add(h1_Noise_numu);
  hs_merge -> Add(h1_NC_numu);
  hs_merge -> Add(h1_NC_numubar);
  hs_merge -> Add(h1_CCOther_numu);
  hs_merge -> Add(h1_CCOther_numubar);
  hs_merge -> Add(h1_CC2p2h_numu);
  hs_merge -> Add(h1_CC2p2h_numubar);
  hs_merge -> Add(h1_CCQE_numu);
  hs_merge -> Add(h1_CCQE_numubar);
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_merge -> SetMaximum(10);
  hs_merge -> Draw();
  hs_merge ->GetYaxis()->SetTitleSize(0.038);
  hs_merge ->GetYaxis()->SetTitleOffset(1.1);
  hs_merge ->GetYaxis()->SetLabelSize(0.036);
  if (KnmtcName=="nTraveld")   hs_merge->GetXaxis()->SetTitle("Reconstructed Neutron Travel Distance [cm]");
  if (KnmtcName=="nTraveldL")  hs_merge->GetXaxis()->SetTitle("Reconstructed Longitidinal Travel Distance [cm]");
  if (KnmtcName=="nTraveldT")  hs_merge->GetXaxis()->SetTitle("Reconstructed Transverse Travel Distance [cm]");
  if (KnmtcName=="nAngle")     hs_merge->GetXaxis()->SetTitle("Cosine of Angle b/w n and Beam Directions");
  if (KnmtcName=="MuStp_NCap") hs_merge->GetXaxis()->SetTitle("Distance b/w #mu Stopping and n Capture Vertices [cm]");
  hs_merge ->GetYaxis()->SetTitle("Number of Tagged Neutrons");
  hs_merge -> Draw();
  c1 -> RedrawAxis();
  
  //TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  TLegend* legend1 = new TLegend(0.15, 0.45, 0.59, 0.89);
  //TLegend* legend1 = new TLegend(0.105, 0.45, 0.495, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  //legend1 -> AddEntry(h1_CCOther_numubar, "#nu_{#mu}+#bar{#nu}_{#mu} CC non-QE", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  //legend1 -> AddEntry(h1_Noise_numu, "Acc. bkg. + decay-e", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;
#endif

}