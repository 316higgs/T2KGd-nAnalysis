#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "./syst_input.h"

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


  // pure water results
  TFile* fin_purewater = new TFile("../PureWater/output/purewater_results.root");
  TH1F* h1_fhc_nmult_x_pt_MC               = (TH1F*)fin_purewater->Get("h1_fhc_nmult_x_pt_MC");    // MC central value
  TGraphErrors* g_fhc_nmult_x_pt_MC        = (TGraphErrors*)fin_purewater->Get("Graph;1"); // MC error bars
  TGraphAsymmErrors* g_fhc_nmult_x_pt_Data = (TGraphAsymmErrors*)fin_purewater->Get("gTrMomAveData_fhc_statsys;1");      // Data


  // run11 data
  TFile* fin_data = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");


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
  std::cout << "Alpha(TN)   : " << NA*FV*1.e-6 << std::endl;
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
  float  N1Rmu_x_kinematics[binnumber];
  float  TaggedN_x_kinematics[binnumber];
  float  N1Rmu_x_kinematics_data[binnumber];
  float  TaggedN_x_kinematics_data[binnumber];
  float  NTagEff_x_kinematics[binnumber];
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
  
  TH1F* h1_TagN_data = (TH1F*)fin_data->Get(FileCCQEName);
  GetHistoBinContent(binnumber, start, TaggedN_x_kinematics_data, h1_TagN_data);

  /////////////////////////////////////////////////////////////////////////////

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
  
  TH1F* h1_N1Rmu_data = (TH1F*)fin_data->Get(FileCCQEName);
  GetHistoBinContent(binnumber, start, N1Rmu_x_kinematics_data, h1_N1Rmu_data);


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
    AveTaggedN_x_kinematics[ibin] = TaggedN_x_kinematics[ibin] - rNoise*N1Rmu_x_kinematics[ibin];
    h1_AveTaggedN_x_kinematics->fArray[ibin+1] = AveTaggedN_x_kinematics[ibin];
  }
  h1_AveTaggedN_x_kinematics -> Sumw2();
  h1_AveTaggedN_x_kinematics -> Divide(h1_Denominator);

  double kinematics[binnumber]  = {0.};
  double dkinematics[binnumber] = {0.};
  double nMult[binnumber]       = {0.};
  double dnMult[binnumber]      = {0.};
  std::cout << "[ MC ] Mean neutron multiplicity" << std::endl;
  for (int i=0; i<binnumber; i++) {
    
    if (i!=binnumber-1) kinematics[i] = xbins[i] + (xbins[i+1] - xbins[i])/2.;
    else kinematics[i] = 2.0;

    nMult[i]  = h1_AveTaggedN_x_kinematics->GetBinContent(i+1);
    dnMult[i] = CalStatErr(Gen_N1Rmu_x_kinematics[i], Gen_TaggedN_x_kinematics[i], Gen_NTagEff_x_kinematics[i]);

    std::cout << "[ " << xbins[i] << ", " << xbins[i+1] << " ]" << std::endl;
    std::cout << "kinematics: " << kinematics[i] << std::endl;
    std::cout << "[### Bin" << i << " ###] " << std::endl;
    std::cout << "    #neutrino events    : " << N1Rmu_x_kinematics[i] << std::endl;
    std::cout << "    #tagged neutrons    : " << TaggedN_x_kinematics[i] << std::endl;
    std::cout << "    Tagging efficiency  : " << NTagEff_x_kinematics[i] << std::endl;
    std::cout << "    Neutron multiplicity: " << h1_AveTaggedN_x_kinematics->GetBinContent(i+1)  
              << " p/m " << dnMult[i] << " ( flactional error: " << (dnMult[i]/nMult[i])*100. << " % )" << std::endl;
  }

  TGraphErrors* g_MCerr = new TGraphErrors(binnumber, kinematics, nMult, dkinematics, dnMult);
  g_MCerr -> SetLineWidth(3);
  g_MCerr -> SetMarkerColor(kViolet-7);
  g_MCerr -> SetLineColor(kViolet-7);



///////////////////////////////////////////////////////////
//  data
  TH1F* h1_Denominator_data = new TH1F("h1_Denominator_data", "", binnumber-1, xbins);
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    h1_Denominator_data->fArray[ibin+1] = NTagEff_x_kinematics[ibin] * N1Rmu_x_kinematics_data[ibin];
  }

  TH1F* h1_AveTaggedN_x_kinematics_data = new TH1F("h1_AveTaggedN_x_kinematics_data", "", binnumber-1, xbins);
  h1_AveTaggedN_x_kinematics_data -> SetMarkerStyle(20);
  h1_AveTaggedN_x_kinematics_data -> SetMarkerSize(1.5);
  h1_AveTaggedN_x_kinematics_data -> SetMarkerColor(kBlack);
  h1_AveTaggedN_x_kinematics_data -> SetLineColor(kBlack);
  h1_AveTaggedN_x_kinematics_data -> SetLineWidth(1.5);
  double AveTaggedN_x_kinematics_data[binnumber];
  std::cout << "[ Data ] Mean neutron multiplicity" << std::endl;
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    AveTaggedN_x_kinematics_data[ibin] = TaggedN_x_kinematics_data[ibin] - rNoise*N1Rmu_x_kinematics_data[ibin];
    h1_AveTaggedN_x_kinematics_data->fArray[ibin+1] = AveTaggedN_x_kinematics_data[ibin];

    std::cout << "[### Bin" << i << " ###] " << std::endl;
    std::cout << "    #neutrino events    : " << N1Rmu_x_kinematics_data[ibin] << std::endl;
    std::cout << "    #tagged neutrons    : " << TaggedN_x_kinematics_data[ibin] << std::endl;
    std::cout << "    Tagging efficiency  : " << NTagEff_x_kinematics[ibin] << std::endl;
  }
  h1_AveTaggedN_x_kinematics_data -> Sumw2();
  h1_AveTaggedN_x_kinematics_data -> Divide(h1_Denominator_data);

  //double Stat_x_Pt[5] = {0.502224, 0.191513, 0.533866, 0., 0.};
  double nMult_data[binnumber]      = {0.};
  double dnMult_data_Up[binnumber]  = {0.};
  double dnMult_data_Low[binnumber] = {0.};
  double dnMult_syst_data_Up[binnumber]  = {0.};
  double dnMult_syst_data_Low[binnumber] = {0.};
  for (int ibin=0; ibin<binnumber-1; ibin++) {
    nMult_data[ibin] = h1_AveTaggedN_x_kinematics_data -> GetBinContent(ibin+1);
    dnMult_data_Up[ibin]  = sqrt( Stat_x_Pt[ibin]*Stat_x_Pt[ibin]
                                + TotSyst_x_Pt_Upper[ibin]*TotSyst_x_Pt_Upper[ibin]);
    dnMult_data_Low[ibin] = sqrt( Stat_x_Pt[ibin]*Stat_x_Pt[ibin]
                                + TotSyst_x_Pt_Lower[ibin]*TotSyst_x_Pt_Lower[ibin]);
    dnMult_syst_data_Up[ibin]  = TotSyst_x_Pt_Upper[ibin];
    dnMult_syst_data_Low[ibin] = TotSyst_x_Pt_Lower[ibin];
    std::cout << "Multiplicity: " << nMult_data[ibin] << " +" << dnMult_data_Up[ibin] << "/-" << dnMult_data_Low[ibin] << std::endl;
  }

  TGraphAsymmErrors* g_DataErr = new TGraphAsymmErrors(binnumber, kinematics, nMult_data, dkinematics, dkinematics, dnMult_data_Low, dnMult_data_Up);
  g_DataErr -> SetLineWidth(2);
  g_DataErr -> SetMarkerSize(1.5);
  g_DataErr -> SetMarkerStyle(20);
  g_DataErr -> SetMarkerColor(kBlack);
  g_DataErr -> SetLineColor(kBlack);

  TGraphAsymmErrors* g_DataSystErr = new TGraphAsymmErrors(binnumber, kinematics, nMult_data, dkinematics, dkinematics, dnMult_syst_data_Low, dnMult_syst_data_Up);
  g_DataSystErr -> SetLineWidth(2);
  g_DataSystErr -> SetMarkerSize(1.5);
  g_DataSystErr -> SetMarkerStyle(20);
  g_DataSystErr -> SetMarkerColor(kBlack);
  g_DataSystErr -> SetLineColor(kBlack);



///////////////////////////////////////////////////////////
#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  c1 -> SetTicks(1);
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
  
  h1_AveTaggedN_x_kinematics -> Draw("histo"); // 0.01% Gd MC
  g_MCerr -> Draw("SAMEP");

  h1_fhc_nmult_x_pt_MC  -> Draw("SAME");   // pure water MC
  g_fhc_nmult_x_pt_MC   -> Draw("SAME E P ");

  g_fhc_nmult_x_pt_Data -> Draw("SAME E P");  // pure water data

  h1_AveTaggedN_x_kinematics_data -> Draw("SAMEP"); // run 11 data
  //g_DataSystErr -> Draw("SAME E P");
  g_DataErr -> Draw("SAME E P");

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

#if 0
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
  text4 -> Draw();
#endif

#if 1

  int GdDataColor = kOrange-6;
  h1_AveTaggedN_x_kinematics -> SetLineColor(kOrange+0);
  h1_AveTaggedN_x_kinematics -> SetFillColor(kOrange-4);
  h1_AveTaggedN_x_kinematics -> SetLineWidth(3);
  g_MCerr -> SetLineColor(kOrange+0);

  h1_AveTaggedN_x_kinematics_data -> SetMarkerColor(GdDataColor);
  h1_AveTaggedN_x_kinematics_data -> SetLineColor(GdDataColor);
  h1_AveTaggedN_x_kinematics_data -> SetLineWidth(2);
  g_DataErr -> SetLineColor(GdDataColor);
  g_DataErr -> SetMarkerColor(GdDataColor);

  h1_fhc_nmult_x_pt_MC -> SetLineColor(kAzure+1);
  g_fhc_nmult_x_pt_MC  -> SetLineColor(kAzure+1);
  h1_fhc_nmult_x_pt_MC -> SetLineWidth(3);

  g_fhc_nmult_x_pt_Data -> SetMarkerColor(kAzure-1);
  g_fhc_nmult_x_pt_Data -> SetMarkerSize(1.5);
  g_fhc_nmult_x_pt_Data -> SetMarkerStyle(21);
  g_fhc_nmult_x_pt_Data -> SetLineColor(kAzure-1);
  g_fhc_nmult_x_pt_Data -> SetLineWidth(2);


  TLegend* legend1 = new TLegend(0.12, 0.65, 0.48, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.32]{FHC 1R #mu sample}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_AveTaggedN_x_kinematics, "0.01% Gd MC", "F");
  legend1 -> AddEntry(h1_AveTaggedN_x_kinematics_data, "Run 11 data", "LP");
  legend1 -> AddEntry(h1_fhc_nmult_x_pt_MC, "Pure water MC", "L");
  legend1 -> AddEntry(g_fhc_nmult_x_pt_Data, "Pure water data", "LP");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif


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


