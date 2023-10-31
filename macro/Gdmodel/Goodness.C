#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void Goodness(bool beammode) {

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  TFile* fin_numu_ggarnet      = new TFile("../../output/fhc/fhc.numu_x_numu.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuesig_ggarnet    = new TFile("../../output/fhc/fhc.numu_x_nue.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_numubar_ggarnet   = new TFile("../../output/fhc/fhc.numubar_x_numubar.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_ggarnet = new TFile("../../output/fhc/fhc.numubar_x_nuebar.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebkg_ggarnet    = new TFile("../../output/fhc/fhc.nue_x_nue.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg_ggarnet = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.ggarnet.bonsaikeras_ToF.root");

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


  TH1F* h1_Goodness_AccNoise_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_Goodness_mode0");

  TH1F* h1_Goodness_AccNoise_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");
  TH1F* h1_Goodness_AccNoise_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode0");

  TH1F* h1_Goodness_DcyE_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_Goodness_mode1");

  TH1F* h1_Goodness_DcyE_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");
  TH1F* h1_Goodness_DcyE_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode1");

  TH1F* h1_Goodness_Hn_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_Goodness_mode2");

  TH1F* h1_Goodness_Hn_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");
  TH1F* h1_Goodness_Hn_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode2");

  TH1F* h1_Goodness_Gdn_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_Goodness_mode3");

  TH1F* h1_Goodness_Gdn_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");
  TH1F* h1_Goodness_Gdn_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_Goodness_mode3");


  bool mode[6] = {1, 1, 1, 1, 1, 1};

  int maximum = 1;
  int BINS    = 100;

  TH1F* h1_Goodness = new TH1F("h1_Goodness", "", BINS, 0, maximum);
  if (mode[5]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_nuebarbkg);
    h1_Goodness -> Add(h1_Goodness_DcyE_nuebarbkg);
    h1_Goodness -> Add(h1_Goodness_Hn_nuebarbkg);
    h1_Goodness -> Add(h1_Goodness_Gdn_nuebarbkg);
  }
  if (mode[4]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_nuebkg);
    h1_Goodness -> Add(h1_Goodness_DcyE_nuebkg);
    h1_Goodness -> Add(h1_Goodness_Hn_nuebkg);
    h1_Goodness -> Add(h1_Goodness_Gdn_nuebkg);
  }
  if (mode[3]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_nuebarsig);
    h1_Goodness -> Add(h1_Goodness_DcyE_nuebarsig);
    h1_Goodness -> Add(h1_Goodness_Hn_nuebarsig);
    h1_Goodness -> Add(h1_Goodness_Gdn_nuebarsig);
  }
  if (mode[2]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_numubar);
    h1_Goodness -> Add(h1_Goodness_DcyE_numubar);
    h1_Goodness -> Add(h1_Goodness_Hn_numubar);
    h1_Goodness -> Add(h1_Goodness_Gdn_numubar);
  }
  if (mode[1]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_nuesig);
    h1_Goodness -> Add(h1_Goodness_DcyE_nuesig);
    h1_Goodness -> Add(h1_Goodness_Hn_nuesig);
    h1_Goodness -> Add(h1_Goodness_Gdn_nuesig);
  }
  if (mode[0]) {
    h1_Goodness -> Add(h1_Goodness_AccNoise_numu);
    h1_Goodness -> Add(h1_Goodness_DcyE_numu);
    h1_Goodness -> Add(h1_Goodness_Hn_numu);
    h1_Goodness -> Add(h1_Goodness_Gdn_numu);
  }
  h1_Goodness -> SetLineColor(kViolet-7);
  h1_Goodness -> SetXTitle("BONSAI Goodness");
  h1_Goodness -> SetYTitle("Number of Events");
  h1_Goodness -> SetLineWidth(2);
  h1_Goodness -> SetStats(0);

  Double_t tot_Goodness = h1_Goodness->Integral();

  TH1F* h1_Goodness_ggarnet = new TH1F("h1_Goodness_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebarbkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebarbkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebarbkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebarbkg);
  }
  if (mode[4]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebkg);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebkg);
  }
  if (mode[3]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebarsig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebarsig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebarsig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebarsig);
  }
  if (mode[2]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_numubar);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_numubar);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_numubar);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_numubar);
  }
  if (mode[1]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuesig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuesig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuesig);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuesig);
  }
  if (mode[0]) {
    h1_Goodness_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_numu);
    h1_Goodness_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_numu);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Hn_ggarnet_numu);
    h1_Goodness_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_numu);
  }
  h1_Goodness_ggarnet -> SetLineColor(kRed-6);
  h1_Goodness_ggarnet -> SetXTitle("BONSAI Goodness");
  h1_Goodness_ggarnet -> SetYTitle("Number of Events");
  h1_Goodness_ggarnet -> SetLineWidth(2);
  h1_Goodness_ggarnet -> SetStats(0);

  Double_t tot_Goodness_ggarnet = h1_Goodness_ggarnet->Integral();
  h1_Goodness_ggarnet -> Scale(tot_Goodness/tot_Goodness_ggarnet);



  TH1F* h1_Goodness_AccNoise = new TH1F("h1_Goodness_AccNoise", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_nuebarbkg);
  if (mode[4]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_nuebkg);
  if (mode[3]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_nuebarsig);
  if (mode[2]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_numubar);
  if (mode[1]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_nuesig);
  if (mode[0]) h1_Goodness_AccNoise -> Add(h1_Goodness_AccNoise_numu);
  h1_Goodness_AccNoise -> SetLineColor(kViolet-7);
  h1_Goodness_AccNoise -> SetXTitle("BONSAI Goodness");
  h1_Goodness_AccNoise -> SetYTitle("Number of Events");
  h1_Goodness_AccNoise -> SetLineWidth(2);
  h1_Goodness_AccNoise -> SetStats(0);

  Double_t tot_Goodness_AccNoise = h1_Goodness_AccNoise->Integral();

  TH1F* h1_Goodness_AccNoise_ggarnet = new TH1F("h1_Goodness_AccNoise_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebarbkg);
  if (mode[4]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebkg);
  if (mode[3]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuebarsig);
  if (mode[2]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_numubar);
  if (mode[1]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_nuesig);
  if (mode[0]) h1_Goodness_AccNoise_ggarnet -> Add(h1_Goodness_AccNoise_ggarnet_numu);
  h1_Goodness_AccNoise_ggarnet -> SetLineColor(kRed-6);
  h1_Goodness_AccNoise_ggarnet -> SetXTitle("BONSAI Goodness");
  h1_Goodness_AccNoise_ggarnet -> SetYTitle("Number of Events");
  h1_Goodness_AccNoise_ggarnet -> SetLineWidth(2);
  h1_Goodness_AccNoise_ggarnet -> SetStats(0);

  Double_t tot_Goodness_AccNoise_ggarnet = h1_Goodness_AccNoise_ggarnet->Integral();
  h1_Goodness_AccNoise_ggarnet -> Scale(tot_Goodness_AccNoise/tot_Goodness_AccNoise_ggarnet);



  TH1F* h1_Goodness_DcyE = new TH1F("h1_Goodness_DcyE", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_nuebarbkg);
  if (mode[4]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_nuebkg);
  if (mode[3]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_nuebarsig);
  if (mode[2]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_numubar);
  if (mode[1]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_nuesig);
  if (mode[0]) h1_Goodness_DcyE -> Add(h1_Goodness_DcyE_numu);
  h1_Goodness_DcyE -> SetLineColor(kViolet-7);
  h1_Goodness_DcyE -> SetXTitle("BONSAI Goodness");
  h1_Goodness_DcyE -> SetYTitle("Number of Events");
  h1_Goodness_DcyE -> SetLineWidth(2);
  h1_Goodness_DcyE -> SetStats(0);

  Double_t tot_Goodness_DcyE = h1_Goodness_DcyE->Integral();

  TH1F* h1_Goodness_DcyE_ggarnet = new TH1F("h1_Goodness_DcyE_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebarbkg);
  if (mode[4]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebkg);
  if (mode[3]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuebarsig);
  if (mode[2]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_numubar);
  if (mode[1]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_nuesig);
  if (mode[0]) h1_Goodness_DcyE_ggarnet -> Add(h1_Goodness_DcyE_ggarnet_numu);
  h1_Goodness_DcyE_ggarnet -> SetLineColor(kRed-6);
  h1_Goodness_DcyE_ggarnet -> SetXTitle("BONSAI Goodness");
  h1_Goodness_DcyE_ggarnet -> SetYTitle("Number of Events");
  h1_Goodness_DcyE_ggarnet -> SetLineWidth(2);
  h1_Goodness_DcyE_ggarnet -> SetStats(0);

  Double_t tot_Goodness_DcyE_ggarnet = h1_Goodness_DcyE_ggarnet->Integral();
  h1_Goodness_DcyE_ggarnet -> Scale(tot_Goodness_DcyE/tot_Goodness_DcyE_ggarnet);



  TH1F* h1_Goodness_Hn = new TH1F("h1_Goodness_Hn", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_nuebarbkg);
  if (mode[4]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_nuebkg);
  if (mode[3]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_nuebarsig);
  if (mode[2]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_numubar);
  if (mode[1]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_nuesig);
  if (mode[0]) h1_Goodness_Hn -> Add(h1_Goodness_Hn_numu);
  h1_Goodness_Hn -> SetLineColor(kViolet-7);
  h1_Goodness_Hn -> SetXTitle("BONSAI Goodness");
  h1_Goodness_Hn -> SetYTitle("Number of Events");
  h1_Goodness_Hn -> SetLineWidth(2);
  h1_Goodness_Hn -> SetStats(0);

  Double_t tot_Goodness_Hn = h1_Goodness_Hn->Integral();

  TH1F* h1_Goodness_Hn_ggarnet = new TH1F("h1_Goodness_Hn_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebarbkg);
  if (mode[4]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebkg);
  if (mode[3]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuebarsig);
  if (mode[2]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_numubar);
  if (mode[1]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_nuesig);
  if (mode[0]) h1_Goodness_Hn_ggarnet -> Add(h1_Goodness_Hn_ggarnet_numu);
  h1_Goodness_Hn_ggarnet -> SetLineColor(kRed-6);
  h1_Goodness_Hn_ggarnet -> SetXTitle("BONSAI Goodness");
  h1_Goodness_Hn_ggarnet -> SetYTitle("Number of Events");
  h1_Goodness_Hn_ggarnet -> SetLineWidth(2);
  h1_Goodness_Hn_ggarnet -> SetStats(0);

  Double_t tot_Goodness_Hn_ggarnet = h1_Goodness_Hn_ggarnet->Integral();
  h1_Goodness_Hn_ggarnet -> Scale(tot_Goodness_Hn/tot_Goodness_Hn_ggarnet);



  TH1F* h1_Goodness_Gdn = new TH1F("h1_Goodness_Gdn", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_nuebarbkg);
  if (mode[4]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_nuebkg);
  if (mode[3]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_nuebarsig);
  if (mode[2]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_numubar);
  if (mode[1]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_nuesig);
  if (mode[0]) h1_Goodness_Gdn -> Add(h1_Goodness_Gdn_numu);
  h1_Goodness_Gdn -> SetLineColor(kViolet-7);
  h1_Goodness_Gdn -> SetXTitle("BONSAI Goodness");
  h1_Goodness_Gdn -> SetYTitle("Number of Events");
  h1_Goodness_Gdn -> SetLineWidth(2);
  h1_Goodness_Gdn -> SetStats(0);

  Double_t tot_Goodness_Gdn = h1_Goodness_Gdn->Integral();

  TH1F* h1_Goodness_Gdn_ggarnet = new TH1F("h1_Goodness_Gdn_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebarbkg);
  if (mode[4]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebkg);
  if (mode[3]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuebarsig);
  if (mode[2]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_numubar);
  if (mode[1]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_nuesig);
  if (mode[0]) h1_Goodness_Gdn_ggarnet -> Add(h1_Goodness_Gdn_ggarnet_numu);
  h1_Goodness_Gdn_ggarnet -> SetLineColor(kRed-6);
  h1_Goodness_Gdn_ggarnet -> SetXTitle("BONSAI Goodness");
  h1_Goodness_Gdn_ggarnet -> SetYTitle("Number of Events");
  h1_Goodness_Gdn_ggarnet -> SetLineWidth(2);
  h1_Goodness_Gdn_ggarnet -> SetStats(0);

  Double_t tot_Goodness_Gdn_ggarnet = h1_Goodness_Gdn_ggarnet->Integral();
  h1_Goodness_Gdn_ggarnet -> Scale(tot_Goodness_Gdn/tot_Goodness_Gdn_ggarnet);





  TLegend* legend1 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.26]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_Goodness, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(h1_Goodness_ggarnet, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);

  TLegend* legend2 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.26]{FHC 1R #mu sample (0.01% Gd)}","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.37]{- Acc. noise}","");
  legend2 -> AddEntry(h1_Goodness, "ANNRI_Gd-based MC", "L");
  legend2 -> AddEntry(h1_Goodness_ggarnet, "GGARNET-based MC", "L");
  legend2 -> SetFillColor(0);

  TLegend* legend3 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry((TObject*)0,"#kern[-0.26]{FHC 1R #mu sample (0.01% Gd)}","");
  legend3 -> AddEntry((TObject*)0,"#kern[-0.33]{- Decay electron}","");
  legend3 -> AddEntry(h1_Goodness, "ANNRI_Gd-based MC", "L");
  legend3 -> AddEntry(h1_Goodness_ggarnet, "GGARNET-based MC", "L");
  legend3 -> SetFillColor(0);

  TLegend* legend4 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend4 -> SetTextSize(0.04);
  legend4 -> AddEntry((TObject*)0,"#kern[-0.26]{FHC 1R #mu sample (0.01% Gd)}","");
  legend4 -> AddEntry((TObject*)0,"#kern[-0.6]{- p(n,#gamma)}","");
  legend4 -> AddEntry(h1_Goodness, "ANNRI_Gd-based MC", "L");
  legend4 -> AddEntry(h1_Goodness_ggarnet, "GGARNET-based MC", "L");
  legend4 -> SetFillColor(0);

  TLegend* legend5 = new TLegend(0.45, 0.65, 0.89, 0.89);
  legend5 -> SetTextSize(0.04);
  legend5 -> AddEntry((TObject*)0,"#kern[-0.26]{FHC 1R #mu sample (0.01% Gd)}","");
  legend5 -> AddEntry((TObject*)0,"#kern[-0.6]{- Gd(n,#gamma)}","");
  legend5 -> AddEntry(h1_Goodness, "ANNRI_Gd-based MC", "L");
  legend5 -> AddEntry(h1_Goodness_ggarnet, "GGARNET-based MC", "L");
  legend5 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_Goodness -> SetMaximum(28000);
  ((TGaxis*)h1_Goodness->GetYaxis())->SetMaxDigits(3);
  h1_Goodness -> Draw("SAME");
  h1_Goodness_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();
#endif

#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_Goodness_AccNoise -> SetMaximum(28000);
  ((TGaxis*)h1_Goodness_AccNoise->GetYaxis())->SetMaxDigits(3);
  h1_Goodness_AccNoise -> Draw("SAME");
  h1_Goodness_AccNoise_ggarnet -> Draw("SAME");
  legend2 -> Draw();
  c1 -> RedrawAxis();

  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h1_Goodness_DcyE -> SetMaximum(1000);
  ((TGaxis*)h1_Goodness_DcyE->GetYaxis())->SetMaxDigits(3);
  h1_Goodness_DcyE -> Draw("SAME");
  h1_Goodness_DcyE_ggarnet -> Draw("SAME");
  legend3 -> Draw();
  c2 -> RedrawAxis();

  TCanvas* c3 = new TCanvas("c3", "c3", 900, 700);
  c3 -> SetGrid();
  h1_Goodness_Hn -> SetMaximum(1000);
  ((TGaxis*)h1_Goodness_Hn->GetYaxis())->SetMaxDigits(3);
  h1_Goodness_Hn -> Draw("SAME");
  h1_Goodness_Hn_ggarnet -> Draw("SAME");
  legend4 -> Draw();
  c3 -> RedrawAxis();

  TCanvas* c4 = new TCanvas("c4", "c4", 900, 700);
  c4 -> SetGrid();
  h1_Goodness_Gdn -> SetMaximum(2000);
  ((TGaxis*)h1_Goodness_Gdn->GetYaxis())->SetMaxDigits(3);
  h1_Goodness_Gdn -> Draw("SAME");
  h1_Goodness_Gdn_ggarnet -> Draw("SAME");
  legend5 -> Draw();
  c4 -> RedrawAxis();
#endif

}

