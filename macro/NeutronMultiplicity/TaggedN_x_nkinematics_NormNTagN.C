#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.49  //Run1-9 FHC
//#define POTSCALE 1.96  //Run1-10 FHC
#define POTSCALE 0.17  //Run11 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

// Normalized with the same number of tagged neutrons as Run1-9 POT

void TaggedN_x_nkinematics_NormNTagN(bool beammode) {

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.Nmult.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.Nmult.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.Nmult.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.Nmult.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.Nmult.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.Nmult.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


  //TString KnmtcName = "nTraveld";
  //TString KnmtcName = "nTraveldL";
  //TString KnmtcName = "nTraveldT";
  TString KnmtcName = "nAngle";
  //TString KnmtcName = "MuStp_NCap";
  const int binnumber = SetHistoBinNumber(KnmtcName);
  double    xbins[binnumber] = {-1., -0.6, -0.2, 0.2, 0.6, 1.};


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

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get(FileCCOtherName);
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get(FileNCName);
  TH1F* h1_Noise_nuesig   = (TH1F*)fin_nuesig->Get(FileNoiseName);
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  TH1F* h1_Noise_numubar   = (TH1F*)fin_numubar->Get(FileNoiseName);
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get(FileCCOtherName);
  TH1F* h1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get(FileNCName);
  TH1F* h1_Noise_nuebarsig   = (TH1F*)fin_nuebarsig->Get(FileNoiseName);
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get(FileCCOtherName);
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get(FileNCName);
  TH1F* h1_Noise_nuebkg   = (TH1F*)fin_nuebkg->Get(FileNoiseName);
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(FileCCOtherName);
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get(FileNCName);
  TH1F* h1_Noise_nuebarbkg   = (TH1F*)fin_nuebarbkg->Get(FileNoiseName);
  h1_CCQE_nuebarbkg -> SetStats(0);


  TH1F* h1_merge = new TH1F("h1_merge", "", binnumber-1, xbins);
  h1_merge -> Add(h1_Noise_nuebarbkg);
  h1_merge -> Add(h1_Noise_nuebkg);
  h1_merge -> Add(h1_Noise_nuebarsig);
  h1_merge -> Add(h1_Noise_numubar);
  h1_merge -> Add(h1_Noise_nuesig);
  h1_merge -> Add(h1_Noise_numu);

  h1_merge -> Add(h1_NC_nuebarbkg);
  h1_merge -> Add(h1_NC_nuebkg);
  h1_merge -> Add(h1_NC_nuebarsig);
  h1_merge -> Add(h1_NC_numubar);
  h1_merge -> Add(h1_NC_nuesig);
  h1_merge -> Add(h1_NC_numu);

  h1_merge -> Add(h1_CCOther_nuebarbkg);
  h1_merge -> Add(h1_CC2p2h_nuebarbkg);
  h1_merge -> Add(h1_CCQE_nuebarbkg);
  h1_merge -> Add(h1_CCOther_nuebkg);
  h1_merge -> Add(h1_CC2p2h_nuebkg);
  h1_merge -> Add(h1_CCQE_nuebkg);
  h1_merge -> Add(h1_CCOther_nuebarsig);
  h1_merge -> Add(h1_CC2p2h_nuebarsig);
  h1_merge -> Add(h1_CCQE_nuebarsig);
  h1_merge -> Add(h1_CCOther_nuesig);
  h1_merge -> Add(h1_CC2p2h_nuesig);
  h1_merge -> Add(h1_CCQE_nuesig);

  h1_merge -> Add(h1_CCOther_numubar);
  h1_merge -> Add(h1_CCOther_numu);
  h1_merge -> Add(h1_CC2p2h_numubar);
  h1_merge -> Add(h1_CC2p2h_numu);
  h1_merge -> Add(h1_CCQE_numubar);
  h1_merge -> Add(h1_CCQE_numu);


  float TotalTaggedN = 0.;
  for (int i=0; i<binnumber; i++) {
    std::cout << "[### Bin" << i << " ###] Tagged neutrons: " << h1_merge->GetBinContent(i+1) << std::endl;
    TotalTaggedN += h1_merge->GetBinContent(i+1);
  }
  std::cout << "Total number of tagged neutrons: " << TotalTaggedN << std::endl;
  Double_t NTagN_pw = 60.20;
  h1_merge -> Scale( NTagN_pw / TotalTaggedN );

  h1_merge -> SetLineWidth(3);
  h1_merge -> SetLineColor(kViolet-6);
  h1_merge -> SetFillColor(kViolet-8);
  h1_merge -> SetFillStyle(3004);
  h1_merge -> SetStats(0);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_merge -> SetMinimum(0.);
  h1_merge -> SetMaximum(24.);
  h1_merge -> Draw();
  h1_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_merge ->GetYaxis()->SetTitleOffset(1.1);
  h1_merge ->GetYaxis()->SetLabelSize(0.036);
  if (KnmtcName=="nTraveld")   h1_merge->GetXaxis()->SetTitle("Reconstructed Neutron Travel Distance [cm]");
  if (KnmtcName=="nTraveldL")  h1_merge->GetXaxis()->SetTitle("Reconstructed Longitidinal Travel Distance [cm]");
  if (KnmtcName=="nTraveldT")  h1_merge->GetXaxis()->SetTitle("Reconstructed Transverse Travel Distance [cm]");
  if (KnmtcName=="nAngle")     h1_merge->GetXaxis()->SetTitle("Cosine of Angle b/w n and Beam Directions");
  if (KnmtcName=="MuStp_NCap") h1_merge->GetXaxis()->SetTitle("Distance b/w #mu Stopping and n Capture Vertices [cm]");
  h1_merge ->GetYaxis()->SetTitle("Number of Tagged Neutrons");
  h1_merge -> Draw();
  c1 -> RedrawAxis();

  TLatex* text1 = new TLatex(0.48, 0.85, "Normalized by #tagged-n of");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);
  TLatex* text2 = new TLatex(0.48, 0.80, "pure water analysis");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.045);

  text1 -> Draw();
  text2 -> Draw();


#if 0
  h1_CCQE_numu -> Add(h1_CC2p2h_numu, 1.);
  h1_CCQE_numubar -> Add(h1_CC2p2h_numubar, 1.);
  h1_NC_numu -> Add(h1_NC_numubar, 1.);
  h1_Noise_numu -> Add(h1_Noise_numubar, 1.);

  Double_t tot_CCQE_numu       = h1_CCQE_numu->Integral();
  Double_t tot_CCQE_numubar    = h1_CCQE_numubar->Integral();
  Double_t tot_CCOther_numu    = h1_CCOther_numu->Integral();
  Double_t tot_CCOther_numubar = h1_CCOther_numubar->Integral();
  Double_t tot_NC              = h1_NC_numu->Integral();
  Double_t tot_Noise           = h1_Noise_numu->Integral();

  Double_t NTagN_CCQE_numu       = 29.05;
  Double_t NTagN_CCQE_numubar    = 4.83;
  Double_t NTagN_CCOther_numu    = 19.45;
  Double_t NTagN_CCOther_numubar = 2.75;
  Double_t NTagN_NC              = 4.11;
  Double_t NTagN_Noise           = 3.88;

  h1_CCQE_numu       -> Scale( NTagN_CCQE_numu / tot_CCQE_numu );
  h1_CCQE_numubar    -> Scale( NTagN_CCQE_numubar / tot_CCQE_numubar );
  h1_CCOther_numu    -> Scale( NTagN_CCOther_numu / tot_CCOther_numu );
  h1_CCOther_numubar -> Scale( NTagN_CCOther_numubar / tot_CCOther_numubar );
  h1_NC_numu         -> Scale( NTagN_NC / tot_NC );
  h1_Noise_numu      -> Scale( NTagN_Noise / tot_Noise );
#endif


  /*
  THStack* hs_merge = new THStack("hs_merge", "", );
#if fhcflag
  hs_merge -> Add(h1_Noise_numu);
  hs_merge -> Add(h1_NC_numu);
  hs_merge -> Add(h1_CCOther_numubar);
  hs_merge -> Add(h1_CCOther_numu);
  hs_merge -> Add(h1_CCQE_numubar);
  hs_merge -> Add(h1_CCQE_numu);
#endif
#if rhcflag
  hs_merge -> Add(h1_Noise_numu);
  hs_merge -> Add(h1_NC_numu);
  hs_merge -> Add(h1_CCOther_numu);
  hs_merge -> Add(h1_CCOther_numubar);
  hs_merge -> Add(h1_CCQE_numu);
  hs_merge -> Add(h1_CCQE_numubar);
#endif
  */

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //hs_merge -> SetMaximum(10);
  //hs_merge -> SetMaximum(28);
  hs_merge -> SetMaximum(38);
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
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  //TLegend* legend1 = new TLegend(0.15, 0.45, 0.59, 0.89);
  //TLegend* legend1 = new TLegend(0.105, 0.45, 0.495, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.25]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h+2p2h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h+2p2h)", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  //legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1 -> AddEntry(h1_Noise_numu, "Acc. bkg. + decay-e", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw() ;
#endif

}


int SetHistoBinNumber(TString KnmtcName) {
  int binnumber = 0;
  if (KnmtcName=="nTraveld" || KnmtcName=="nTraveldT" || KnmtcName=="MuStp_NCap") binnumber = 7;
  else if (KnmtcName=="nTraveldL") binnumber = 13;
  else binnumber = 6;
  return binnumber;
}
