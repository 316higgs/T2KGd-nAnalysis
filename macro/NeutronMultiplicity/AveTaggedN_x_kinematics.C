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

#define rNoise 0.0135

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
float CalStatErr(float N1Rmu, float NTagN, float NTagEff);


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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.Nmult.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.Nmult.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.Nmult.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.Nmult.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.Nmult.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.Nmult.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.beforecut.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.beofrecut.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
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


  //TString KnmtcName = "Enu";
  //TString KnmtcName = "MuMom";
  TString KnmtcName = "MuPt";
  //TString KnmtcName = "Q2";
  //TString KnmtcName = "MuAngle";
  const int binnumber = SetHistoBinNumber(KnmtcName);

  //double xbins[binnumber] = {0, 0.5, 1., 1.5, 2.5, 5.};
  //double xbins[binnumber] = {0, 0.5, 1.0, 2.0, 6.0};
  double xbins[binnumber] = {0, 0.25, 0.5, 0.75, 1.5};
  //double xbins[binnumber] = {0, 0.25, 0.5, 0.75, 3.};
  //double xbins[binnumber] = {-1, -0.5, 0., 0.5, 1.};
  
  double start = xbins[0];                        // start value
  double maximum = xbins[binnumber-1];            // end value
  double interval = (maximum - start)/binnumber;  // bin width
  float N1Rmu_x_kinematics[binnumber];
  float TaggedN_x_kinematics[binnumber];
  float NTagEff_x_kinematics[binnumber];
  double Gen_N1Rmu_x_kinematics[binnumber];
  double Gen_TaggedN_x_kinematics[binnumber];
  double Gen_TrueN_x_kinematics[binnumber];
  double Gen_NTagEff_x_kinematics[binnumber];


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

  TH1F* h1_TagN_CCQE_nuesig    = (TH1F*)fin_nuesig->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_nuesig = (TH1F*)fin_nuesig->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_nuesig      = (TH1F*)fin_nuesig->Get(FileNCName);
  TH1F* h1_TagN_Noise_nuesig   = (TH1F*)fin_nuesig->Get(FileNoiseName);
  h1_TagN_CCQE_nuesig -> SetStats(0);

  TH1F* h1_TagN_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  TH1F* h1_TagN_Noise_numubar   = (TH1F*)fin_numubar->Get(FileNoiseName);
  h1_TagN_CCQE_numubar -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get(FileNCName);
  TH1F* h1_TagN_Noise_nuebarsig   = (TH1F*)fin_nuebarsig->Get(FileNoiseName);
  h1_TagN_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_nuebkg      = (TH1F*)fin_nuebkg->Get(FileNCName);
  TH1F* h1_TagN_Noise_nuebkg   = (TH1F*)fin_nuebkg->Get(FileNoiseName);
  h1_TagN_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get(FileCCQEName);
  TH1F* h1_TagN_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(FileCC2p2hName);
  TH1F* h1_TagN_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(FileCCOtherName);
  TH1F* h1_TagN_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get(FileNCName);
  TH1F* h1_TagN_Noise_nuebarbkg   = (TH1F*)fin_nuebarbkg->Get(FileNoiseName);
  h1_TagN_CCQE_nuebarbkg -> SetStats(0);

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

  h1_TagN_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_TagN_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_TagN_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_TagN_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_nuesig   -> SetLineColor(kYellow+2);
  h1_TagN_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_TagN_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_TagN_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_TagN_NC_nuesig      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_nuesig   -> SetFillColor(kYellow+2);

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

  h1_TagN_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_TagN_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_TagN_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_TagN_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_nuebarsig   -> SetLineColor(kYellow+2);
  h1_TagN_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_TagN_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_TagN_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_TagN_NC_nuebarsig      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_nuebarsig   -> SetFillColor(kYellow+2);

  h1_TagN_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_TagN_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_TagN_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_TagN_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_nuebkg   -> SetLineColor(kYellow+2);
  h1_TagN_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_TagN_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_TagN_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_TagN_NC_nuebkg      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_nuebkg   -> SetFillColor(kYellow+2);

  h1_TagN_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_TagN_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_TagN_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_TagN_NC_nuebarbkg      -> SetLineColor(kSpring-9);
  h1_TagN_Noise_nuebarbkg   -> SetLineColor(kYellow+2);
  h1_TagN_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_TagN_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_TagN_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_TagN_NC_nuebarbkg      -> SetFillColor(kSpring-9);
  h1_TagN_Noise_nuebarbkg   -> SetFillColor(kYellow+2);

  for (int ibin=0; ibin<binnumber; ibin++) {
    Gen_TaggedN_x_kinematics[ibin] = h1_TagN_CCQE_numu->GetBinContent(ibin+1) + h1_TagN_CC2p2h_numu->GetBinContent(ibin+1) + h1_TagN_CCOther_numu->GetBinContent(ibin+1) + h1_TagN_NC_numu->GetBinContent(ibin+1) + h1_TagN_Noise_numu->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuesig->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuesig->GetBinContent(ibin+1) + h1_TagN_CCOther_nuesig->GetBinContent(ibin+1) + h1_TagN_NC_nuesig->GetBinContent(ibin+1) + h1_TagN_Noise_nuesig->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_numubar->GetBinContent(ibin+1) + h1_TagN_CC2p2h_numubar->GetBinContent(ibin+1) + h1_TagN_CCOther_numubar->GetBinContent(ibin+1) + h1_TagN_NC_numubar->GetBinContent(ibin+1) + h1_TagN_Noise_numubar->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebarsig->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebarsig->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebarsig->GetBinContent(ibin+1) + h1_TagN_NC_nuebarsig->GetBinContent(ibin+1) + h1_TagN_Noise_nuebarsig->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebkg->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebkg->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebkg->GetBinContent(ibin+1) + h1_TagN_NC_nuebkg->GetBinContent(ibin+1) + h1_TagN_Noise_nuebkg->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_NC_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_Noise_nuebarbkg->GetBinContent(ibin+1);
    Gen_NTagEff_x_kinematics[ibin] = h1_TagN_CCQE_numu->GetBinContent(ibin+1) + h1_TagN_CC2p2h_numu->GetBinContent(ibin+1) + h1_TagN_CCOther_numu->GetBinContent(ibin+1) + h1_TagN_NC_numu->GetBinContent(ibin+1) 
                                   + h1_TagN_CCQE_nuesig->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuesig->GetBinContent(ibin+1) + h1_TagN_CCOther_nuesig->GetBinContent(ibin+1) + h1_TagN_NC_nuesig->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_numubar->GetBinContent(ibin+1) + h1_TagN_CC2p2h_numubar->GetBinContent(ibin+1) + h1_TagN_CCOther_numubar->GetBinContent(ibin+1) + h1_TagN_NC_numubar->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebarsig->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebarsig->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebarsig->GetBinContent(ibin+1) + h1_TagN_NC_nuebarsig->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebkg->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebkg->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebkg->GetBinContent(ibin+1) + h1_TagN_NC_nuebkg->GetBinContent(ibin+1)
                                   + h1_TagN_CCQE_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_CC2p2h_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_CCOther_nuebarbkg->GetBinContent(ibin+1) + h1_TagN_NC_nuebarbkg->GetBinContent(ibin+1);
    std::cout << "[ " << ibin << "] Tagged neutrons     : " << Gen_TaggedN_x_kinematics[ibin] << std::endl;
    std::cout << "[ " << ibin << "] Tagged true neutrons: " << Gen_NTagEff_x_kinematics[ibin] << std::endl;
  }

  /////  Normalizations  //////
#if 1
  h1_TagN_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagN_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagN_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagN_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagN_Noise_numu        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_Noise_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_Noise_numubar     -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_Noise_nuebarsig   -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_Noise_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_Noise_nuebarbkg   -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  TH1F* h1_TagN_merge = new TH1F("h1_TagN_merge", "", binnumber-1, xbins);
  h1_TagN_merge -> Add(h1_TagN_Noise_nuebarbkg);
  h1_TagN_merge -> Add(h1_TagN_Noise_nuebkg);
  h1_TagN_merge -> Add(h1_TagN_Noise_nuebarsig);
  h1_TagN_merge -> Add(h1_TagN_Noise_numubar);
  h1_TagN_merge -> Add(h1_TagN_Noise_nuesig);
  h1_TagN_merge -> Add(h1_TagN_Noise_numu);

  h1_TagN_merge -> Add(h1_TagN_NC_nuebarbkg);
  h1_TagN_merge -> Add(h1_TagN_NC_nuebkg);
  h1_TagN_merge -> Add(h1_TagN_NC_nuebarsig);
  h1_TagN_merge -> Add(h1_TagN_NC_numubar);
  h1_TagN_merge -> Add(h1_TagN_NC_nuesig);
  h1_TagN_merge -> Add(h1_TagN_NC_numu);

  h1_TagN_merge -> Add(h1_TagN_CCOther_nuebarbkg);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_nuebarbkg);
  h1_TagN_merge -> Add(h1_TagN_CCQE_nuebarbkg);
  h1_TagN_merge -> Add(h1_TagN_CCOther_nuebkg);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_nuebkg);
  h1_TagN_merge -> Add(h1_TagN_CCQE_nuebkg);
  h1_TagN_merge -> Add(h1_TagN_CCOther_nuebarsig);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_nuebarsig);
  h1_TagN_merge -> Add(h1_TagN_CCQE_nuebarsig);
  h1_TagN_merge -> Add(h1_TagN_CCOther_nuesig);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_nuesig);
  h1_TagN_merge -> Add(h1_TagN_CCQE_nuesig);

  h1_TagN_merge -> Add(h1_TagN_CCOther_numubar);
  h1_TagN_merge -> Add(h1_TagN_CCOther_numu);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_numubar);
  h1_TagN_merge -> Add(h1_TagN_CC2p2h_numu);
  h1_TagN_merge -> Add(h1_TagN_CCQE_numubar);
  h1_TagN_merge -> Add(h1_TagN_CCQE_numu);
  h1_TagN_merge -> SetLineColor(kViolet-7);
  h1_TagN_merge -> SetLineWidth(2);
  h1_TagN_merge -> SetFillColor(kViolet-9);
  h1_TagN_merge -> SetFillStyle(3004);
  h1_TagN_merge -> SetStats(0);
  GetHistoBinContent(binnumber, start, TaggedN_x_kinematics, h1_TagN_merge);
  //for (int ibin=0; ibin<binnumber-1; ibin++) std::cout << "Bin[" << ibin << "]: " << TaggedN_x_kinematics[ibin] << std::endl;

  TH1F* h1_NTagEff_merge = new TH1F("h1_NTagEff_merge", "", binnumber-1, xbins);

  h1_NTagEff_merge -> Add(h1_TagN_NC_nuebarbkg);
  h1_NTagEff_merge -> Add(h1_TagN_NC_nuebkg);
  h1_NTagEff_merge -> Add(h1_TagN_NC_nuebarsig);
  h1_NTagEff_merge -> Add(h1_TagN_NC_numubar);
  h1_NTagEff_merge -> Add(h1_TagN_NC_nuesig);
  h1_NTagEff_merge -> Add(h1_TagN_NC_numu);

  h1_NTagEff_merge -> Add(h1_TagN_CCOther_nuebarbkg);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_nuebarbkg);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_nuebarbkg);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_nuebkg);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_nuebkg);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_nuebkg);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_nuebarsig);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_nuebarsig);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_nuebarsig);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_nuesig);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_nuesig);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_nuesig);

  h1_NTagEff_merge -> Add(h1_TagN_CCOther_numubar);
  h1_NTagEff_merge -> Add(h1_TagN_CCOther_numu);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_numubar);
  h1_NTagEff_merge -> Add(h1_TagN_CC2p2h_numu);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_numubar);
  h1_NTagEff_merge -> Add(h1_TagN_CCQE_numu);
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

  TH1F* h1_TrueN_CCQE_nuesig    = (TH1F*)fin_nuesig->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_nuesig = (TH1F*)fin_nuesig->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_nuesig      = (TH1F*)fin_nuesig->Get(FileNCName);
  h1_TrueN_CCQE_nuesig -> SetStats(0);

  TH1F* h1_TrueN_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  h1_TrueN_CCQE_numubar -> SetStats(0);

  TH1F* h1_TrueN_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get(FileNCName);
  h1_TrueN_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_TrueN_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_nuebkg      = (TH1F*)fin_nuebkg->Get(FileNCName);
  h1_TrueN_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_TrueN_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get(FileCCQEName);
  TH1F* h1_TrueN_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(FileCC2p2hName);
  TH1F* h1_TrueN_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(FileCCOtherName);
  TH1F* h1_TrueN_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get(FileNCName);
  h1_TrueN_CCQE_nuebarbkg -> SetStats(0);

  h1_TrueN_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_TrueN_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_TrueN_CCOther_numu -> SetLineColor(kCyan-8);
  h1_TrueN_NC_numu      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_TrueN_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_TrueN_CCOther_numu -> SetFillColor(kCyan-8);
  h1_TrueN_NC_numu      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_TrueN_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_TrueN_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_TrueN_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_TrueN_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_TrueN_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_TrueN_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_TrueN_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_TrueN_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_TrueN_NC_numubar      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_TrueN_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_TrueN_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_TrueN_NC_numubar      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_TrueN_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_TrueN_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_TrueN_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_TrueN_NC_nuebarsig      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_TrueN_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_TrueN_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_TrueN_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_TrueN_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_TrueN_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_TrueN_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_TrueN_NC_nuebarbkg      -> SetLineColor(kSpring-9);
  h1_TrueN_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_TrueN_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_TrueN_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_TrueN_NC_nuebarbkg      -> SetFillColor(kSpring-9);

  for (int ibin=0; ibin<binnumber; ibin++) {
    Gen_TrueN_x_kinematics[ibin] = h1_TrueN_CCQE_numu->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_numu->GetBinContent(ibin+1) + h1_TrueN_CCOther_numu->GetBinContent(ibin+1) + h1_TrueN_NC_numu->GetBinContent(ibin+1)
                                 + h1_TrueN_CCQE_nuesig->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_nuesig->GetBinContent(ibin+1) + h1_TrueN_CCOther_nuesig->GetBinContent(ibin+1) + h1_TrueN_NC_nuesig->GetBinContent(ibin+1)
                                 + h1_TrueN_CCQE_numubar->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_numubar->GetBinContent(ibin+1) + h1_TrueN_CCOther_numubar->GetBinContent(ibin+1) + h1_TrueN_NC_numubar->GetBinContent(ibin+1)
                                 + h1_TrueN_CCQE_nuebarsig->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_nuebarsig->GetBinContent(ibin+1) + h1_TrueN_CCOther_nuebarsig->GetBinContent(ibin+1) + h1_TrueN_NC_nuebarsig->GetBinContent(ibin+1)
                                 + h1_TrueN_CCQE_nuebkg->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_nuebkg->GetBinContent(ibin+1) + h1_TrueN_CCOther_nuebkg->GetBinContent(ibin+1) + h1_TrueN_NC_nuebkg->GetBinContent(ibin+1)
                                 + h1_TrueN_CCQE_nuebarbkg->GetBinContent(ibin+1) + h1_TrueN_CC2p2h_nuebarbkg->GetBinContent(ibin+1) + h1_TrueN_CCOther_nuebarbkg->GetBinContent(ibin+1) + h1_TrueN_NC_nuebarbkg->GetBinContent(ibin+1);
    Gen_NTagEff_x_kinematics[ibin] /= Gen_TrueN_x_kinematics[ibin];
    std::cout << "[ " << ibin << "] True neutrons     : " << Gen_TrueN_x_kinematics[ibin] << std::endl;
    std::cout << "[ " << ibin << "] Tagging efficiency: " << Gen_NTagEff_x_kinematics[ibin] << std::endl;
  }

  /////  Normalizations  //////
#if 1
  h1_TrueN_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueN_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueN_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueN_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueN_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueN_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueN_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueN_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueN_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueN_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueN_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueN_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TrueN_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TrueN_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TrueN_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TrueN_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TrueN_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TrueN_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  TH1F* h1_TrueN_merge = new TH1F("h1_TrueN_merge", "", binnumber-1, xbins);
  h1_TrueN_merge -> Add(h1_TrueN_NC_nuebarbkg);
  h1_TrueN_merge -> Add(h1_TrueN_NC_nuebkg);
  h1_TrueN_merge -> Add(h1_TrueN_NC_nuebarsig);
  h1_TrueN_merge -> Add(h1_TrueN_NC_numubar);
  h1_TrueN_merge -> Add(h1_TrueN_NC_nuesig);
  h1_TrueN_merge -> Add(h1_TrueN_NC_numu);

  h1_TrueN_merge -> Add(h1_TrueN_CCOther_nuebarbkg);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_nuebarbkg);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_nuebarbkg);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_nuebkg);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_nuebkg);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_nuebkg);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_nuebarsig);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_nuebarsig);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_nuebarsig);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_nuesig);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_nuesig);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_nuesig);

  h1_TrueN_merge -> Add(h1_TrueN_CCOther_numubar);
  h1_TrueN_merge -> Add(h1_TrueN_CCOther_numu);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_numubar);
  h1_TrueN_merge -> Add(h1_TrueN_CC2p2h_numu);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_numubar);
  h1_TrueN_merge -> Add(h1_TrueN_CCQE_numu);
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

  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get(FileCCQEName);
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get(FileCC2p2hName);
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get(FileCCOtherName);
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get(FileNCName);
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get(FileCCOtherName);
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get(FileNCName);
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get(FileCCQEName);
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(FileCC2p2hName);
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get(FileCCOtherName);
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get(FileNCName);
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get(FileCCOtherName);
  TH1F* h1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get(FileNCName);
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get(FileCCOtherName);
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get(FileNCName);
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get(FileCCQEName);
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(FileCC2p2hName);
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(FileCCOtherName);
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get(FileNCName);
  h1_CCQE_nuebarbkg -> SetStats(0);

  h1_CCQE_numu    -> SetLineColor(kAzure-1);
  h1_CC2p2h_numu  -> SetLineColor(kAzure-5);
  h1_CCOther_numu -> SetLineColor(kCyan-8);
  h1_NC_numu      -> SetLineColor(kSpring-9);
  h1_CCQE_numu    -> SetFillColor(kAzure-1);
  h1_CC2p2h_numu  -> SetFillColor(kAzure-5);
  h1_CCOther_numu -> SetFillColor(kCyan-8);
  h1_NC_numu      -> SetFillColor(kSpring-9);

  h1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_NC_nuesig      -> SetFillColor(kSpring-9);

  h1_CCQE_numubar    -> SetLineColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetLineColor(kOrange+6);
  h1_CCOther_numubar -> SetLineColor(kOrange+0);
  h1_NC_numubar      -> SetLineColor(kSpring-9);
  h1_CCQE_numubar    -> SetFillColor(kOrange+7);
  h1_CC2p2h_numubar  -> SetFillColor(kOrange+6);
  h1_CCOther_numubar -> SetFillColor(kOrange+0);
  h1_NC_numubar      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_NC_nuebkg      -> SetFillColor(kSpring-9);

  h1_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetLineColor(kSpring-9);
  h1_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetFillColor(kSpring-9);

  for (int ibin=0; ibin<binnumber; ibin++) {
    Gen_N1Rmu_x_kinematics[ibin] = h1_CCQE_numu->GetBinContent(ibin+1) + h1_CC2p2h_numu->GetBinContent(ibin+1) + h1_CCOther_numu->GetBinContent(ibin+1) + h1_NC_numu->GetBinContent(ibin+1)
                                 + h1_CCQE_nuesig->GetBinContent(ibin+1) + h1_CC2p2h_nuesig->GetBinContent(ibin+1) + h1_CCOther_nuesig->GetBinContent(ibin+1) + h1_NC_nuesig->GetBinContent(ibin+1)
                                 + h1_CCQE_numubar->GetBinContent(ibin+1) + h1_CC2p2h_numubar->GetBinContent(ibin+1) + h1_CCOther_numubar->GetBinContent(ibin+1) + h1_NC_numubar->GetBinContent(ibin+1)
                                 + h1_CCQE_nuebarsig->GetBinContent(ibin+1) + h1_CC2p2h_nuebarsig->GetBinContent(ibin+1) + h1_CCOther_nuebarsig->GetBinContent(ibin+1) + h1_NC_nuebarsig->GetBinContent(ibin+1)
                                 + h1_CCQE_nuebkg->GetBinContent(ibin+1) + h1_CC2p2h_nuebkg->GetBinContent(ibin+1) + h1_CCOther_nuebkg->GetBinContent(ibin+1) + h1_NC_nuebkg->GetBinContent(ibin+1)
                                 + h1_CCQE_nuebarbkg->GetBinContent(ibin+1) + h1_CC2p2h_nuebarbkg->GetBinContent(ibin+1) + h1_CCOther_nuebarbkg->GetBinContent(ibin+1) + h1_NC_nuebarbkg->GetBinContent(ibin+1);
    std::cout << "[ " << ibin << "] 1Rmu: " << Gen_N1Rmu_x_kinematics[ibin] << std::endl;
  }


  /////  Normalizations  //////
#if 1
  h1_CCQE_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCQE_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCQE_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCQE_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCQE_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCQE_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CC2p2h_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CC2p2h_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CC2p2h_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CC2p2h_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CC2p2h_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CC2p2h_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_CCOther_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_CCOther_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_CCOther_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_CCOther_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_CCOther_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_CCOther_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_NC_numu           -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_NC_nuesig         -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_NC_numubar        -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_NC_nuebarsig      -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_NC_nuebkg         -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_NC_nuebarbkg      -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  TH1F* h1_N1Rmu_merge = new TH1F("h1_N1Rmu_merge", "", binnumber-1, xbins);
  h1_N1Rmu_merge -> Add(h1_NC_nuebarbkg);
  h1_N1Rmu_merge -> Add(h1_NC_nuebkg);
  h1_N1Rmu_merge -> Add(h1_NC_nuebarsig);
  h1_N1Rmu_merge -> Add(h1_NC_numubar);
  h1_N1Rmu_merge -> Add(h1_NC_nuesig);
  h1_N1Rmu_merge -> Add(h1_NC_numu);

  h1_N1Rmu_merge -> Add(h1_CCOther_nuebarbkg);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_nuebarbkg);
  h1_N1Rmu_merge -> Add(h1_CCQE_nuebarbkg);
  h1_N1Rmu_merge -> Add(h1_CCOther_nuebkg);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_nuebkg);
  h1_N1Rmu_merge -> Add(h1_CCQE_nuebkg);
  h1_N1Rmu_merge -> Add(h1_CCOther_nuebarsig);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_nuebarsig);
  h1_N1Rmu_merge -> Add(h1_CCQE_nuebarsig);
  h1_N1Rmu_merge -> Add(h1_CCOther_nuesig);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_nuesig);
  h1_N1Rmu_merge -> Add(h1_CCQE_nuesig);

  h1_N1Rmu_merge -> Add(h1_CCOther_numubar);
  h1_N1Rmu_merge -> Add(h1_CCOther_numu);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_numubar);
  h1_N1Rmu_merge -> Add(h1_CC2p2h_numu);
  h1_N1Rmu_merge -> Add(h1_CCQE_numubar);
  h1_N1Rmu_merge -> Add(h1_CCQE_numu);
  h1_N1Rmu_merge -> SetLineColor(kViolet-7);
  h1_N1Rmu_merge -> SetLineWidth(2);
  h1_N1Rmu_merge -> SetStats(0);
  GetHistoBinContent(binnumber, start, N1Rmu_x_kinematics, h1_N1Rmu_merge);
  //for (int ibin=0; ibin<binnumber-1; ibin++) std::cout << "Bin[" << ibin << "]: " << N1Rmu_x_kinematics[ibin] << std::endl;

  /////////////////////////////////////////////////////////////////////////////

  TH1F* h1_Denominator = new TH1F("h1_Denominator", "", binnumber-1, xbins);
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    h1_Denominator->fArray[ibin+1] = NTagEff_x_kinematics[ibin] * N1Rmu_x_kinematics[ibin];
  }

  TH1F* h1_AveTaggedN_x_kinematics = new TH1F("h1_AveTaggedN_x_kinematics", "", binnumber-1, xbins);
  h1_AveTaggedN_x_kinematics -> SetLineColor(kViolet-7);
  h1_AveTaggedN_x_kinematics -> SetLineWidth(2);
  h1_AveTaggedN_x_kinematics -> SetFillColor(kViolet-9);
  h1_AveTaggedN_x_kinematics -> SetFillStyle(3004);
  h1_AveTaggedN_x_kinematics -> SetStats(0);
  double AveTaggedN_x_kinematics[binnumber];
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    //AveTaggedN_x_kinematics[ibin] = ( TaggedN_x_kinematics[ibin] - rNoise*N1Rmu_x_kinematics[ibin] )/N1Rmu_x_kinematics[ibin];
    //AveTaggedN_x_kinematics[ibin] /= NTagEff_x_kinematics[ibin];
    AveTaggedN_x_kinematics[ibin] = TaggedN_x_kinematics[ibin] - rNoise*N1Rmu_x_kinematics[ibin];
    h1_AveTaggedN_x_kinematics->fArray[ibin+1] = AveTaggedN_x_kinematics[ibin];
  }
  h1_AveTaggedN_x_kinematics -> Sumw2();
  h1_AveTaggedN_x_kinematics -> Divide(h1_Denominator);

  double kinematics[binnumber]  = {0.};
  double dkinematics[binnumber] = {0.};
  double nMult[binnumber]       = {0.};
  double dnMult[binnumber]      = {0.};
  std::cout << "Mean neutron multiplicity" << std::endl;
  for (int i=0; i<binnumber; i++) {
    
    std::cout << "[ " << xbins[i] << ", " << xbins[i+1] << " ]" << std::endl;
    if (i!=binnumber-1) kinematics[i] = xbins[i] + (xbins[i+1] - xbins[i])/2.;
    else kinematics[i] = 2.0;

    std::cout << "kinematics: " << kinematics[i] << std::endl;

    nMult[i]  = h1_AveTaggedN_x_kinematics->GetBinContent(i+1);
    dnMult[i] = CalStatErr(Gen_N1Rmu_x_kinematics[i], Gen_TaggedN_x_kinematics[i], Gen_NTagEff_x_kinematics[i]);

    std::cout << "[### Bin" << i << " ###] " << std::endl;
    std::cout << "    #neutrino events    : " << N1Rmu_x_kinematics[i] << std::endl;
    std::cout << "    #tagged neutrons    : " << TaggedN_x_kinematics[i] << std::endl;
    std::cout << "    Tagging efficiency  : " << NTagEff_x_kinematics[i] << std::endl;
    std::cout << "    Neutron multiplicity: " << h1_AveTaggedN_x_kinematics->GetBinContent(i+1) 
              << " (p/m " << dnMult[i] << " )" << std::endl;
  }
  TGraphErrors* g_MCerr = new TGraphErrors(binnumber, kinematics, nMult, dkinematics, dnMult);
  g_MCerr -> SetLineWidth(3);
  g_MCerr -> SetMarkerColor(kViolet-7);
  g_MCerr -> SetLineColor(kViolet-7);


#if 0
  TGraphErrors* g_errbnd[binnumber];
  double x0[1] = {(0.+0.25)/2.};
  double x1[1] = {(0.25+0.5)/2.};
  double x2[1] = {(0.5+0.75)/2.};
  double x3[1] = {(0.75+1.5)/2.};
  double x4[1] = {(1.5+2.0)/2.};
  double e_x0[1] = {0.};
  double e_x1[1] = {0.};
  double e_x2[1] = {0.};
  double e_x3[1] = {0.};
  double e_x4[1] = {0.};
  double AveTaggedN0[1] = {1.37};
  double AveTaggedN1[1] = {1.68};
  double AveTaggedN2[1] = {2.38};
  double AveTaggedN3[1] = {3.99};
  double AveTaggedN4[1] = {3.76};
  double e_AveTaggedN0[2] = {0.614, 0.614};
  double e_AveTaggedN1[2] = {0.583};
  double e_AveTaggedN2[2] = {1.08};
  double e_AveTaggedN3[2] = {2.56};
  double e_AveTaggedN4[2] = {26.4};
  g_errbnd[0] = new TGraphErrors(1, x0, AveTaggedN0, e_x0, e_AveTaggedN0);
  g_errbnd[1] = new TGraphErrors(1, x1, AveTaggedN1, e_x1, e_AveTaggedN1);
  g_errbnd[2] = new TGraphErrors(1, x2, AveTaggedN2, e_x2, e_AveTaggedN2);
  g_errbnd[3] = new TGraphErrors(1, x3, AveTaggedN3, e_x3, e_AveTaggedN3);
  g_errbnd[4] = new TGraphErrors(1, x4, AveTaggedN4, e_x4, e_AveTaggedN4);
#endif




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
  //h1_AveTaggedN_x_kinematics -> Draw("E1");
  //h1_AveTaggedN_x_kinematics -> Draw("");
  //h1_AveTaggedN_x_kinematics -> Draw("hist same");
#if 0
  for (int i=0; i<binnumber; i++) {
    g_errbnd[i] -> SetFillStyle(3244);
    g_errbnd[i] -> SetFillColor(kViolet+1);
    g_errbnd[i] -> SetLineColor(kViolet-7);
    g_errbnd[i] -> SetLineWidth(2);
    //g_errbnd[i] -> Draw("3 SAME");
    g_errbnd[i] -> Draw("E1 SAME");
  }
#endif
  g_MCerr -> Draw("SAMEP");
  c1->RedrawAxis();
  
  TLatex* text1 = new TLatex(0.12, 0.82, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.05);
  TLatex* text2 = new TLatex(0.14, 0.77, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.14, 0.72, "-Acc. bkg. & decay-e subtracted");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  TLatex* text4 = new TLatex(0.14, 0.67, "-Tagging efficiency corrected");
  text4 -> SetNDC(1);
  text4 -> SetTextSize(0.04);
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
  //for (int ibin=0; ibin<binnumber-1; ibin++) {
  for (int ibin=0; ibin<binnumber; ibin++) {
    N_x_kinematics[ibin] = h1->GetBinContent(thisbin);
    std::cout << "Bin[" << ibin << "]=" << thisbin << ": " << N_x_kinematics[ibin] << std::endl;
    thisbin++;
  }
}


float CalStatErr(float N1Rmu, float NTagN, float NTagEff) {
  float dnMult = std::sqrt( NTagN ) / (NTagEff * N1Rmu) ; 
  return dnMult;
}


