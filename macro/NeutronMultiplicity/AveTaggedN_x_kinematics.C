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

#define rNoise 0.0232

enum class KnmtcType
{
  Enu = 0,
  Pmu = 1,
  Pt  = 2,
  Q2  = 3,
  MuAngle = 4
};

int SetHistoBinNumber(TString KnmtcName);
void GetHistoBinContent(const int binnumber, float start, float* N_x_kinematics, TH1F* h1);

void AveTaggedN_x_kinematics(bool beammode) {

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


  //TString KnmtcName = "Enu";
  //TString KnmtcName = "MuMom";
  //TString KnmtcName = "MuPt";
  //TString KnmtcName = "Q2";
  TString KnmtcName = "MuAngle";

  const int binnumber = SetHistoBinNumber(KnmtcName);
  //double xbins[binnumber] = {0, 0.5, 1., 1.5, 2.5, 5.};
  //double xbins[binnumber] = {0, 0.5, 1.0, 2.0, 6.0};
  //double xbins[binnumber] = {0, 0.25, 0.5, 0.75, 1.5};
  //double xbins[binnumber] = {0, 0.25, 0.5, 0.75, 3.};
  double xbins[binnumber] = {-1, -0.5, 0., 0.5, 1.};
  
  double start = xbins[0];                        // start value
  double maximum = xbins[binnumber-1];            // end value
  double interval = (maximum - start)/binnumber;  // bin width
  float N1Rmu_x_kinematics[binnumber];
  float TaggedN_x_kinematics[binnumber];
  float NTagEff_x_kinematics[binnumber];


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

  TH1F* h1_TagN_CCQE_numu    = (TH1F*)fin_numu->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_numu  = (TH1F*)fin_numu->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_numu = (TH1F*)fin_numu->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_numu      = (TH1F*)fin_numu->Get(FileNCName);
  TH1F* h1_TagN_Noise_numu   = (TH1F*)fin_numu->Get(FileNoiseName);
  h1_TagN_CCQE_numu -> SetStats(0);

  TH1F* h1_TagN_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  TH1F* h1_TagN_Noise_numubar   = (TH1F*)fin_numubar->Get(FileNoiseName);
  h1_TagN_CCQE_numubar -> SetStats(0);

  h1_TagN_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_TagN_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_TagN_CCOther_numu -> SetLineColor(kCyan-8);
  h1_TagN_NC_numu      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_numu   -> SetLineColor(kYellow+2);

  h1_TagN_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_TagN_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_TagN_CCOther_numu -> SetFillColor(kCyan-8);
  h1_TagN_NC_numu      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_numu   -> SetFillColor(kYellow+2);

  h1_TagN_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_TagN_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_TagN_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_TagN_NC_numubar      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_numubar   -> SetLineColor(kYellow+2);

  h1_TagN_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_TagN_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_TagN_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_TagN_NC_numubar      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_numubar   -> SetFillColor(kYellow+2);

  h1_TagN_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_Noise_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_Noise_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_TagN_merge = new TH1F("h1_TagN_merge", "", binnumber-1, xbins);
  h1_TagN_merge -> Add(h1_TagN_CCQE_numu, 1.);
  h1_TagN_merge -> Add(h1_TagN_CCQE_numubar, 1.);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_numu, 1.);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_numubar, 1.);
  h1_TagN_merge -> Add(h1_TagN_CCOther_numu, 1.);
  h1_TagN_merge -> Add(h1_TagN_CCOther_numubar, 1.);
  h1_TagN_merge -> Add(h1_TagN_NC_numu, 1.);
  h1_TagN_merge -> Add(h1_TagN_NC_numubar, 1.);
  h1_TagN_merge -> Add(h1_TagN_Noise_numu, 1.);
  h1_TagN_merge -> Add(h1_TagN_Noise_numubar, 1.);
  h1_TagN_merge -> SetLineColor(kViolet-7);
  h1_TagN_merge -> SetLineWidth(2);
  h1_TagN_merge -> SetFillColor(kViolet-9);
  h1_TagN_merge -> SetFillStyle(3004);
  h1_TagN_merge -> SetStats(0);
  GetHistoBinContent(binnumber, start, TaggedN_x_kinematics, h1_TagN_merge);
  //for (int ibin=0; ibin<binnumber-1; ibin++) std::cout << "Bin[" << ibin << "]: " << TaggedN_x_kinematics[ibin] << std::endl;

  TH1F* h1_TagN_merge = new TH1F("h1_NTagEff_merge", "", binnumber-1, xbins);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_numu, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_numubar, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_numu, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_numubar, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_numu, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_numubar, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_NC_numu, 1.);
  h1_NTagEff_merge -> Add(h1_TagN_NC_numubar, 1.);
  //h1_NTagEff_merge -> Add(h1_TagN_Noise_numu, 1.);
  //h1_NTagEff_merge -> Add(h1_TagN_Noise_numubar, 1.);
  h1_NTagEff_merge -> SetLineColor(kViolet-7);
  h1_NTagEff_merge -> SetLineWidth(2);
  h1_NTagEff_merge -> SetFillColor(kViolet-9);
  h1_NTagEff_merge -> SetFillStyle(3004);
  h1_NTagEff_merge -> SetStats(0);

  /////////////////////////////////////////////////////////////////////////////

  Prefix = "NTagAnalysis/h1_TrueN_x_";
  FileCCQEName    = Prefix+KnmtcName+CCQEName;
  FileCC2p2hName  = Prefix+KnmtcName+CC2p2hName;
  FileCCOtherName = Prefix+KnmtcName+CCOtherName;
  FileNCName      = Prefix+KnmtcName+NCName;

  TH1F* h1_TrueN_CCQE_numu    = (TH1F*)fin_numu->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_numu  = (TH1F*)fin_numu->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_numu = (TH1F*)fin_numu->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_numu      = (TH1F*)fin_numu->Get(FileNCName);
  h1_TrueN_CCQE_numu -> SetStats(0);

  TH1F* h1_TrueN_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  h1_TrueN_CCQE_numubar -> SetStats(0);

  h1_TrueN_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_TrueN_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_TrueN_CCOther_numu -> SetLineColor(kCyan-8);
  h1_TrueN_NC_numu      -> SetLineColor(kSpring-9);

  h1_TrueN_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_TrueN_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_TrueN_CCOther_numu -> SetFillColor(kCyan-8);
  h1_TrueN_NC_numu      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_TrueN_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_TrueN_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_TrueN_NC_numubar      -> SetLineColor(kSpring-9);

  h1_TrueN_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_TrueN_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_TrueN_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_TrueN_NC_numubar      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_TrueN_merge = new TH1F("h1_TrueN_merge", "", binnumber-1, xbins);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_numu, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_numubar, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_numu, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_numubar, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_numu, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_numubar, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_NC_numu, 1.);
  h1_TrueN_merge -> Add(h1_TrueN_NC_numubar, 1.);
  h1_TrueN_merge -> SetLineColor(kViolet-7);
  h1_TrueN_merge -> SetLineWidth(2);
  h1_TrueN_merge -> SetStats(0);

  h1_NTagEff_merge -> Sumw2();
  h1_NTagEff_merge -> Divide(h1_TrueN_merge);
  GetHistoBinContent(binnumber, start, NTagEff_x_kinematics, h1_NTagEff_merge);
  //for (int ibin=0; ibin<binnumber-1; ibin++) std::cout << "Bin[" << ibin << "]: " << NTagEff_x_kinematics[ibin] << std::endl;
  
  /////////////////////////////////////////////////////////////////////////////

  Prefix      = "NTagAnalysis/h1_N1Rmu_x_";
  FileCCQEName    = Prefix+KnmtcName+CCQEName;
  FileCC2p2hName  = Prefix+KnmtcName+CC2p2hName;
  FileCCOtherName = Prefix+KnmtcName+CCOtherName;
  FileNCName      = Prefix+KnmtcName+NCName;

  TH1F* h1_N1Rmu_CCQE_numu    = (TH1F*)fin_numu->Get(FileCCQEName);
  TH1F* h1_N1Rmu_CC2p2h_numu  = (TH1F*)fin_numu->Get(FileCC2p2hName);
  TH1F* h1_N1Rmu_CCOther_numu = (TH1F*)fin_numu->Get(FileCCOtherName);
  TH1F* h1_N1Rmu_NC_numu      = (TH1F*)fin_numu->Get(FileNCName);
  h1_N1Rmu_CCQE_numu -> SetStats(0);

  TH1F* h1_N1Rmu_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_N1Rmu_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_N1Rmu_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_N1Rmu_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  h1_N1Rmu_CCQE_numubar -> SetStats(0);

  h1_N1Rmu_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_N1Rmu_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_N1Rmu_CCOther_numu -> SetLineColor(kCyan-8);
  h1_N1Rmu_NC_numu      -> SetLineColor(kSpring-9);

  h1_N1Rmu_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_N1Rmu_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_N1Rmu_CCOther_numu -> SetFillColor(kCyan-8);
  h1_N1Rmu_NC_numu      -> SetFillColor(kSpring-9);

  h1_N1Rmu_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_N1Rmu_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_N1Rmu_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_N1Rmu_NC_numubar      -> SetLineColor(kSpring-9);

  h1_N1Rmu_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_N1Rmu_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_N1Rmu_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_N1Rmu_NC_numubar      -> SetFillColor(kSpring-9);

  h1_N1Rmu_CCQE_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_N1Rmu_CCQE_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_N1Rmu_CC2p2h_numu     -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_N1Rmu_CC2p2h_numubar  -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_N1Rmu_CCOther_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_N1Rmu_CCOther_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_N1Rmu_NC_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_N1Rmu_NC_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  TH1F* h1_N1Rmu_merge = new TH1F("h1_N1Rmu_merge", "", binnumber-1, xbins);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CCQE_numu, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CCQE_numubar, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CC2p2h_numu, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CC2p2h_numubar, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CCOther_numu, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_CCOther_numubar, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_NC_numu, 1.);
  h1_N1Rmu_merge -> Add(h1_N1Rmu_NC_numubar, 1.);
  h1_N1Rmu_merge -> SetLineColor(kViolet-7);
  h1_N1Rmu_merge -> SetLineWidth(2);
  h1_N1Rmu_merge -> SetStats(0);
  GetHistoBinContent(binnumber, start, N1Rmu_x_kinematics, h1_N1Rmu_merge);
  //for (int ibin=0; ibin<binnumber-1; ibin++) std::cout << "Bin[" << ibin << "]: " << N1Rmu_x_kinematics[ibin] << std::endl;

  /////////////////////////////////////////////////////////////////////////////

  TH1F* h1_AveTaggedN_x_kinematics = new TH1F("h1_AveTaggedN_x_kinematics", "", binnumber-1, xbins);
  h1_AveTaggedN_x_kinematics -> SetLineColor(kViolet-7);
  h1_AveTaggedN_x_kinematics -> SetLineWidth(2);
  h1_AveTaggedN_x_kinematics -> SetFillColor(kViolet-9);
  h1_AveTaggedN_x_kinematics -> SetFillStyle(3004);
  h1_AveTaggedN_x_kinematics -> SetStats(0);
  float AveTaggedN_x_kinematics[binnumber];
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    AveTaggedN_x_kinematics[ibin] = (TaggedN_x_kinematics[ibin] - rNoise*N1Rmu_x_kinematics[ibin])/N1Rmu_x_kinematics[ibin];
    AveTaggedN_x_kinematics[ibin] /= NTagEff_x_kinematics[ibin];
    h1_AveTaggedN_x_kinematics->fArray[ibin+1] = AveTaggedN_x_kinematics[ibin];
  }


#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_AveTaggedN_x_kinematics -> SetMinimum(0);
  h1_AveTaggedN_x_kinematics -> SetMaximum(5.0);
  h1_AveTaggedN_x_kinematics ->GetYaxis()->SetTitleSize(0.045);
  h1_AveTaggedN_x_kinematics ->GetYaxis()->SetTitleOffset(1.);
  h1_AveTaggedN_x_kinematics ->GetYaxis()->SetLabelSize(0.036);
  h1_AveTaggedN_x_kinematics ->GetXaxis()->SetTitleSize(0.045);
  if (KnmtcName=="Enu")     h1_AveTaggedN_x_kinematics->GetXaxis()->SetTitle("Reconstructed Neutrino Energy [GeV]");
  if (KnmtcName=="MuMom")   h1_AveTaggedN_x_kinematics->GetXaxis()->SetTitle("Reconstructed #mu Momentum [GeV]");
  if (KnmtcName=="MuPt")    h1_AveTaggedN_x_kinematics->GetXaxis()->SetTitle("Reconstructed #mu Transverse Momentum [GeV]");
  if (KnmtcName=="Q2")      h1_AveTaggedN_x_kinematics->GetXaxis()->SetTitle("Reconstructed Q^{2}(CCQE Assumption) [GeV^{2}]");
  if (KnmtcName=="MuAngle") h1_AveTaggedN_x_kinematics->GetXaxis()->SetTitle("Cosine of Angle b/w #mu and Beam Directions");
  h1_AveTaggedN_x_kinematics->GetYaxis()->SetTitle("Mean Neutron Multiplicity");
  h1_AveTaggedN_x_kinematics -> Draw("histo");
  c1->RedrawAxis();
  
  TLatex* text1 = new TLatex(0.12, 0.82, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.05);
  TLatex* text2 = new TLatex(0.14, 0.77, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.03);
  TLatex* text3 = new TLatex(0.14, 0.72, "-Subtracted acc. bkg. + decay-e");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.03);
  TLatex* text4 = new TLatex(0.14, 0.67, "-Corrected tagging efficiency");
  text4 -> SetNDC(1);
  text4 -> SetTextSize(0.03);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
  text4 -> Draw();
#endif

}


int SetHistoBinNumber(TString KnmtcName) {
  int binnumber = 0;
  if (KnmtcName=="Enu") binnumber = 6;
  else binnumber = 5;
  return binnumber;
}

void GetHistoBinContent(const int binnumber, float start, float* N_x_kinematics, TH1F* h1) {
  int thisbin = h1->FindBin(start);
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    N_x_kinematics[ibin] = h1->GetBinContent(thisbin);
    //std::cout << "Bin[" << ibin << "]=" << thisbin << ": " << N_x_kinematics[ibin] << std::endl;
    thisbin++;
  }
}



