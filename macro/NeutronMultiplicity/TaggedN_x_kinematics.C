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

void TaggedN_x_kinematics(bool beammode) {

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

  h1_CCQE_nuesig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuesig -> SetLineColor(kViolet-1);
  h1_NC_nuesig      -> SetLineColor(kSpring-9);
  h1_Noise_nuesig   -> SetLineColor(kYellow+2);
  h1_CCQE_nuesig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuesig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuesig -> SetFillColor(kViolet-1);
  h1_NC_nuesig      -> SetFillColor(kSpring-9);
  h1_Noise_nuesig   -> SetFillColor(kYellow+2);

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

  h1_CCQE_nuebarsig    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetLineColor(kViolet-1);
  h1_NC_nuebarsig      -> SetLineColor(kSpring-9);
  h1_Noise_nuebarsig   -> SetLineColor(kYellow+2);
  h1_CCQE_nuebarsig    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarsig  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarsig -> SetFillColor(kViolet-1);
  h1_NC_nuebarsig      -> SetFillColor(kSpring-9);
  h1_Noise_nuebarsig   -> SetFillColor(kYellow+2);

  h1_CCQE_nuebkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebkg -> SetLineColor(kViolet-1);
  h1_NC_nuebkg      -> SetLineColor(kSpring-9);
  h1_Noise_nuebkg   -> SetLineColor(kYellow+2);
  h1_CCQE_nuebkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebkg -> SetFillColor(kViolet-1);
  h1_NC_nuebkg      -> SetFillColor(kSpring-9);
  h1_Noise_nuebkg   -> SetFillColor(kYellow+2);

  h1_CCQE_nuebarbkg    -> SetLineColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetLineColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetLineColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetLineColor(kSpring-9);
  h1_Noise_nuebarbkg   -> SetLineColor(kYellow+2);
  h1_CCQE_nuebarbkg    -> SetFillColor(kViolet-1);
  h1_CC2p2h_nuebarbkg  -> SetFillColor(kViolet-1);
  h1_CCOther_nuebarbkg -> SetFillColor(kViolet-1);
  h1_NC_nuebarbkg      -> SetFillColor(kSpring-9);
  h1_Noise_nuebarbkg   -> SetFillColor(kYellow+2);



  /////  Normalizations  //////
#if 0
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

  h1_Noise_numu        -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_Noise_nuesig      -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_Noise_numubar     -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_Noise_nuebarsig   -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_Noise_nuebkg      -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_Noise_nuebarbkg   -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

#if 1
  float NTagN = 0.;
  for (int i=0; i<binnumber; i++) {
    std::cout << "[### Bin" << i << " ###] [numu    -> numu   ] : " <<  h1_CCQE_numu->GetBinContent(i+1) +
                                                                        h1_CC2p2h_numu->GetBinContent(i+1) +
                                                                        h1_CCOther_numu->GetBinContent(i+1) +
                                                                        h1_NC_numu->GetBinContent(i+1) + 
                                                                        h1_Noise_numu->GetBinContent(i+1) << std::endl;
    std::cout << "[### Bin" << i << " ###] [numu    -> nue    ] : " <<  h1_CCQE_nuesig->GetBinContent(i+1) +
                                                                        h1_CC2p2h_nuesig->GetBinContent(i+1) +
                                                                        h1_CCOther_nuesig->GetBinContent(i+1) +
                                                                        h1_NC_nuesig->GetBinContent(i+1) +
                                                                        h1_Noise_nuesig->GetBinContent(i+1) << std::endl;
    std::cout << "[### Bin" << i << " ###] [numubar -> numubar] : " <<  h1_CCQE_numubar->GetBinContent(i+1) +
                                                                        h1_CC2p2h_numubar->GetBinContent(i+1) +
                                                                        h1_CCOther_numubar->GetBinContent(i+1) +
                                                                        h1_NC_numubar->GetBinContent(i+1) +
                                                                        h1_Noise_numubar->GetBinContent(i+1) << std::endl;
    std::cout << "[### Bin" << i << " ###] [numubar -> nuebar ] : " <<  h1_CCQE_nuebarsig->GetBinContent(i+1) +
                                                                        h1_CC2p2h_nuebarsig->GetBinContent(i+1) +
                                                                        h1_CCOther_nuebarsig->GetBinContent(i+1) +
                                                                        h1_NC_nuebarsig->GetBinContent(i+1) +
                                                                        h1_Noise_nuebarsig->GetBinContent(i+1) << std::endl;
    std::cout << "[### Bin" << i << " ###] [nue     -> nue    ] : " <<  h1_CCQE_nuebkg->GetBinContent(i+1) +
                                                                        h1_CC2p2h_nuebkg->GetBinContent(i+1) +
                                                                        h1_CCOther_nuebkg->GetBinContent(i+1) +
                                                                        h1_NC_nuebkg->GetBinContent(i+1) +
                                                                        h1_Noise_nuebkg->GetBinContent(i+1) << std::endl;
    std::cout << "[### Bin" << i << " ###] [nuebar  -> nuebar ] : " <<  h1_CCQE_nuebarbkg->GetBinContent(i+1) +
                                                                        h1_CC2p2h_nuebarbkg->GetBinContent(i+1) +
                                                                        h1_CCOther_nuebarbkg->GetBinContent(i+1) +
                                                                        h1_NC_nuebarbkg->GetBinContent(i+1) +
                                                                        h1_Noise_nuebarbkg->GetBinContent(i+1) << std::endl;
    //std::cout << "Number of 1Rmu events: " << N1Rmu << std::endl;
    float ThisNTagN = h1_CCQE_numu->GetBinContent(i+1) + h1_CC2p2h_numu->GetBinContent(i+1) + h1_CCOther_numu->GetBinContent(i+1) + h1_NC_numu->GetBinContent(i+1) + h1_Noise_numu->GetBinContent(i+1)
                   + h1_CCQE_nuesig->GetBinContent(i+1) + h1_CC2p2h_nuesig->GetBinContent(i+1) + h1_CCOther_nuesig->GetBinContent(i+1) + h1_NC_nuesig->GetBinContent(i+1) + h1_Noise_nuesig->GetBinContent(i+1)
                   + h1_CCQE_numubar->GetBinContent(i+1) + h1_CC2p2h_numubar->GetBinContent(i+1) + h1_CCOther_numubar->GetBinContent(i+1) + h1_NC_numubar->GetBinContent(i+1) + h1_Noise_numubar->GetBinContent(i+1)
                   + h1_CCQE_nuebarsig->GetBinContent(i+1) + h1_CC2p2h_nuebarsig->GetBinContent(i+1) + h1_CCOther_nuebarsig->GetBinContent(i+1) + h1_NC_nuebarsig->GetBinContent(i+1) + h1_Noise_nuebarsig->GetBinContent(i+1)
                   + h1_CCQE_nuebkg->GetBinContent(i+1) + h1_CC2p2h_nuebkg->GetBinContent(i+1) + h1_CCOther_nuebkg->GetBinContent(i+1) + h1_NC_nuebkg->GetBinContent(i+1) + h1_Noise_nuebkg->GetBinContent(i+1)
                   + h1_CCQE_nuebarbkg->GetBinContent(i+1) + h1_CC2p2h_nuebarbkg->GetBinContent(i+1) + h1_CCOther_nuebarbkg->GetBinContent(i+1) + h1_NC_nuebarbkg->GetBinContent(i+1) + h1_Noise_nuebarbkg->GetBinContent(i+1);
    //float ThisNTagN = h1_CCQE_numu->GetBinContent(i+1) + h1_CC2p2h_numu->GetBinContent(i+1) + h1_CCOther_numu->GetBinContent(i+1) + h1_NC_numu->GetBinContent(i+1) + h1_Noise_numu->GetBinContent(i+1);
    NTagN += ThisNTagN;
    std::cout << "Number of tagged neutrons: " << ThisNTagN << " (total: " << NTagN << ")" << std::endl;
  }
#endif


  THStack* hs_merge = new THStack("hs_merge", "");
#if fhcflag
  hs_merge -> Add(h1_Noise_nuebarbkg);
  hs_merge -> Add(h1_Noise_nuebkg);
  hs_merge -> Add(h1_Noise_nuebarsig);
  hs_merge -> Add(h1_Noise_numubar);
  hs_merge -> Add(h1_Noise_nuesig);
  hs_merge -> Add(h1_Noise_numu);

  hs_merge -> Add(h1_NC_nuebarbkg);
  hs_merge -> Add(h1_NC_nuebkg);
  hs_merge -> Add(h1_NC_nuebarsig);
  hs_merge -> Add(h1_NC_numubar);
  hs_merge -> Add(h1_NC_nuesig);
  hs_merge -> Add(h1_NC_numu);

  hs_merge -> Add(h1_CCOther_nuebarbkg);
  hs_merge -> Add(h1_CC2p2h_nuebarbkg);
  hs_merge -> Add(h1_CCQE_nuebarbkg);
  hs_merge -> Add(h1_CCOther_nuebkg);
  hs_merge -> Add(h1_CC2p2h_nuebkg);
  hs_merge -> Add(h1_CCQE_nuebkg);
  hs_merge -> Add(h1_CCOther_nuebarsig);
  hs_merge -> Add(h1_CC2p2h_nuebarsig);
  hs_merge -> Add(h1_CCQE_nuebarsig);
  hs_merge -> Add(h1_CCOther_nuesig);
  hs_merge -> Add(h1_CC2p2h_nuesig);
  hs_merge -> Add(h1_CCQE_nuesig);

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

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //hs_merge -> SetMaximum(8);
  if (KnmtcName=="Enu" || KnmtcName=="MuMom" || KnmtcName=="MuPt" || KnmtcName=="Q2") hs_merge -> SetMaximum(14);
  else hs_merge -> SetMaximum(18);
  hs_merge -> Draw();
  hs_merge ->GetYaxis()->SetTitleSize(0.038);
  hs_merge ->GetYaxis()->SetTitleOffset(1.1);
  hs_merge ->GetYaxis()->SetLabelSize(0.036);
  if (KnmtcName=="Enu")     hs_merge->GetXaxis()->SetTitle("Reconstructed Neutrino Energy [GeV]");
  if (KnmtcName=="MuMom")   hs_merge->GetXaxis()->SetTitle("Reconstructed #mu Momentum [GeV]");
  if (KnmtcName=="MuPt")    hs_merge->GetXaxis()->SetTitle("Reconstructed #mu Transverse Momentum [GeV]");
  if (KnmtcName=="Q2")      hs_merge->GetXaxis()->SetTitle("Reconstructed Q^{2}(CCQE Assumption) [GeV^{2}]");
  if (KnmtcName=="MuAngle") hs_merge->GetXaxis()->SetTitle("Cosine of Angle b/w #mu and Beam Directions");
  hs_merge->GetYaxis()->SetTitle("Number of Tagged Neutrons");
  hs_merge -> Draw();
  c1->RedrawAxis();
  
  float xmin = 0.45;
  float xmax = 0.89;
  if (KnmtcName=="MuAngle") {
    xmin = 0.15;
    xmax = 0.59;
  }
  TLegend* legend1 = new TLegend(xmin, 0.45, xmax, 0.89);
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
  legend1 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1 -> AddEntry(h1_Noise_numu, "Acc. bkg. + decay-e", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}

int SetHistoBinNumber(TString KnmtcName) {
  int binnumber = 0;
  if (KnmtcName=="Enu") binnumber = 6;
  else binnumber = 5;
  return binnumber;
}
