#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.49  //Run1-9 FHC
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run11 FHC


void SimpleNeutron(bool beammode) {

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



  bool TruthNeutron = true;
  //bool TruthNeutron = false;

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


  /////////////  Truth neutrons  ////////////////
#if TruthNeutron
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
#endif

  /////////////  Reco neutrons  ////////////////
#if !TruthNeutron
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  
  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebarsig    = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_nuebarsig      = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
#endif

  h1_CCQE_numu    -> SetStats(0);
  h1_CCQE_numubar -> SetStats(0);

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

#if 0
  float TaggedN_numu      = 0.;
  float CCQE_numu = 0.;
  float CC2p2h_numu = 0.;
  float CCOther_numu = 0.;
  float NC_numu = 0.;
  float TaggedN_nuesig    = 0.;
  float TaggedN_numubar   = 0.;
  float TaggedN_nuebarsig = 0.;
  float TaggedN_nuebkg    = 0.;
  float TaggedN_nuebarbkg = 0.;
  for (int ibin=0; ibin<50; ibin++) {
  //for (int ibin=0; ibin<20; ibin++) {
    CCQE_numu    += ibin*h1_CCQE_numu->GetBinContent(ibin+1);
    CC2p2h_numu  += ibin*h1_CC2p2h_numu->GetBinContent(ibin+1);
    CCOther_numu += ibin*h1_CCOther_numu->GetBinContent(ibin+1);
    NC_numu      += ibin*h1_NC_numu->GetBinContent(ibin+1);

    TaggedN_numu      += ibin*( h1_CCQE_numu->GetBinContent(ibin+1) + 
                                h1_CC2p2h_numu->GetBinContent(ibin+1) +
                                h1_CCOther_numu->GetBinContent(ibin+1) +
                                h1_NC_numu->GetBinContent(ibin+1) );
    TaggedN_nuesig    += ibin*( h1_CCQE_nuesig->GetBinContent(ibin+1) + 
                                h1_CC2p2h_nuesig->GetBinContent(ibin+1) +
                                h1_CCOther_nuesig->GetBinContent(ibin+1) +
                                h1_NC_nuesig->GetBinContent(ibin+1) );
    TaggedN_numubar   += ibin*( h1_CCQE_numubar->GetBinContent(ibin+1) + 
                                h1_CC2p2h_numubar->GetBinContent(ibin+1) +
                                h1_CCOther_numubar->GetBinContent(ibin+1) +
                                h1_NC_numubar->GetBinContent(ibin+1) );
    TaggedN_nuebarsig += ibin*( h1_CCQE_nuebarsig->GetBinContent(ibin+1) + 
                                h1_CC2p2h_nuebarsig->GetBinContent(ibin+1) +
                                h1_CCOther_nuebarsig->GetBinContent(ibin+1) +
                                h1_NC_nuebarsig->GetBinContent(ibin+1) );
    TaggedN_nuebkg    += ibin*( h1_CCQE_nuebkg->GetBinContent(ibin+1) + 
                                h1_CC2p2h_nuebkg->GetBinContent(ibin+1) +
                                h1_CCOther_nuebkg->GetBinContent(ibin+1) +
                                h1_NC_nuebkg->GetBinContent(ibin+1) );
    TaggedN_nuebarbkg += ibin*( h1_CCQE_nuebarbkg->GetBinContent(ibin+1) + 
                                h1_CC2p2h_nuebarbkg->GetBinContent(ibin+1) +
                                h1_CCOther_nuebarbkg->GetBinContent(ibin+1) +
                                h1_NC_nuebarbkg->GetBinContent(ibin+1) );
  }
  std::cout << "CCQE   : " << CCQE_numu << std::endl;
  std::cout << "CC2p2h : " << CC2p2h_numu << std::endl;
  std::cout << "CCOther: " << CCOther_numu << std::endl;
  std::cout << "NC     : " << NC_numu << std::endl;
  std::cout << "[numu    -> numu   ]: " << TaggedN_numu << std::endl;
  std::cout << "[numu    -> nue    ]: " << TaggedN_nuesig << std::endl;
  std::cout << "[numubar -> numubar]: " << TaggedN_numubar << std::endl;
  std::cout << "[numubar -> nuebar ]: " << TaggedN_nuebarsig << std::endl;
  std::cout << "[nue     -> nue    ]: " << TaggedN_nuebkg << std::endl;
  std::cout << "[nuebar  -> nuebar ]: " << TaggedN_nuebarbkg << std::endl;
#endif


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


  THStack* hs_Neutron = new THStack("hs_Neutron", "");
#if fhcflag
  hs_Neutron -> Add(h1_NC_nuebarbkg);
  hs_Neutron -> Add(h1_NC_nuebkg);
  hs_Neutron -> Add(h1_NC_nuebarsig);
  hs_Neutron -> Add(h1_NC_numubar);
  hs_Neutron -> Add(h1_NC_nuesig);
  hs_Neutron -> Add(h1_NC_numu);

  hs_Neutron -> Add(h1_CCOther_nuebarbkg);
  hs_Neutron -> Add(h1_CC2p2h_nuebarbkg);
  hs_Neutron -> Add(h1_CCQE_nuebarbkg);
  hs_Neutron -> Add(h1_CCOther_nuebkg);
  hs_Neutron -> Add(h1_CC2p2h_nuebkg);
  hs_Neutron -> Add(h1_CCQE_nuebkg);
  hs_Neutron -> Add(h1_CCOther_nuebarsig);
  hs_Neutron -> Add(h1_CC2p2h_nuebarsig);
  hs_Neutron -> Add(h1_CCQE_nuebarsig);
  hs_Neutron -> Add(h1_CCOther_nuesig);
  hs_Neutron -> Add(h1_CC2p2h_nuesig);
  hs_Neutron -> Add(h1_CCQE_nuesig);

  hs_Neutron -> Add(h1_CCOther_numubar);
  hs_Neutron -> Add(h1_CCOther_numu);
  hs_Neutron -> Add(h1_CC2p2h_numubar);
  hs_Neutron -> Add(h1_CC2p2h_numu);
  hs_Neutron -> Add(h1_CCQE_numubar);
  hs_Neutron -> Add(h1_CCQE_numu);
#endif


  TFile* fin_data = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");
  TH1F*   h1_data = (TH1F*)fin_data->Get("NTagAnalysis/h1_AllTagNmultiplicity");
  h1_data -> SetMarkerStyle(20);
  h1_data -> SetMarkerSize(1.5);
  h1_data -> SetMarkerColor(kBlack);
  h1_data -> SetLineColor(kBlack);
  h1_data -> SetLineWidth(1.5);



#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  if (TruthNeutron) hs_Neutron -> SetMaximum(15);
  else hs_Neutron -> SetMaximum(23);
  hs_Neutron -> Draw();
  hs_Neutron ->GetYaxis()->SetTitleSize(0.038);
  hs_Neutron ->GetYaxis()->SetTitleOffset(1.3);
  hs_Neutron ->GetYaxis()->SetLabelSize(0.036);
  if (TruthNeutron) hs_Neutron ->GetXaxis()->SetTitle("Neutron Multiplicity");
  else hs_Neutron ->GetXaxis()->SetTitle("Tagged Neutron Multiplicity");
  hs_Neutron ->GetYaxis()->SetTitle("Number of Events");
  hs_Neutron -> Draw();
  if (!TruthNeutron) h1_data    -> Draw("SAME E P");
  c1->RedrawAxis();
  
  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CCQE_numu, "#nu_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CCQE_numubar, "#bar{#nu}_{#mu} CCQE(1p1h)", "F");
  legend1 -> AddEntry(h1_CC2p2h_numu, "#nu_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CC2p2h_numubar, "#bar{#nu}_{#mu} CC-2p2h", "F");
  legend1 -> AddEntry(h1_CCOther_numu, "#nu_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCOther_numubar, "#bar{#nu}_{#mu} CC-other", "F");
  legend1 -> AddEntry(h1_CCQE_nuesig, "#nu_{e} / #bar#nu_{e} CC", "F");
  legend1 -> AddEntry(h1_NC_numu, "NC", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}