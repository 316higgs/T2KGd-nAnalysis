#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"
#include <iomanip>

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void NeutronMult(bool beammode) {

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

#if 0
  float Gdconc = 0.0263;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
#endif

#if 1
  float Gdconc = 0.0251;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.00251GdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.00251GdMC.bonsaikeras_ToF.root");
#endif

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

  
  ////  True neutrons  ////
  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode0");
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode1");
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode2");
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TrueNmultiplicity_mode3");
  h1_CCQE_nuebarbkg -> SetStats(0);


  ////  Tagged neutrons  ////
  TH1F* h1_TagN_CCQE_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_numu -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_nuesig      = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_nuesig -> SetStats(0);

  TH1F* h1_TagN_CCQE_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_numubar      = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_numubar -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_nuebkg      = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_TagN_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode0");
  TH1F* h1_TagN_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode1");
  TH1F* h1_TagN_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode2");
  TH1F* h1_TagN_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagNmultiplicity_mode3");
  h1_TagN_CCQE_nuebarbkg -> SetStats(0);


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
#endif



  /////  Merged neutrons  //////
  TH1F* h1_TrueN = new TH1F("h1_TrueN", "", 10, 0, 10);
  h1_TrueN -> SetLineColor(kViolet+3);
  h1_TrueN -> SetLineWidth(2);
  h1_TrueN -> SetStats(0);
  h1_TrueN -> SetXTitle("Number of True Neutron Captures");
  h1_TrueN -> SetYTitle("Number of Neutrino Events");
  h1_TrueN -> GetXaxis()->SetTitleSize(0.045);
  h1_TrueN -> GetYaxis()->SetTitleSize(0.045);

  TH1F* h1_TagN = new TH1F("h1_TagN", "", 10, 0, 10);
  h1_TagN -> SetLineColor(kViolet+3);
  h1_TagN -> SetLineWidth(2);
  h1_TagN -> SetStats(0);
  h1_TagN -> SetXTitle("Number of Tagged Neutron Captures");
  h1_TagN -> SetYTitle("Number of Neutrino Events");
  h1_TagN -> GetXaxis()->SetTitleSize(0.045);
  h1_TagN -> GetYaxis()->SetTitleSize(0.045);

#if fhcflag
  h1_TrueN -> Add(h1_NC_nuebarbkg);
  h1_TrueN -> Add(h1_NC_nuebkg);
  h1_TrueN -> Add(h1_NC_nuebarsig);
  h1_TrueN -> Add(h1_NC_numubar);
  h1_TrueN -> Add(h1_NC_nuesig);
  h1_TrueN -> Add(h1_NC_numu);

  h1_TrueN -> Add(h1_CCOther_nuebarbkg);
  h1_TrueN -> Add(h1_CC2p2h_nuebarbkg);
  h1_TrueN -> Add(h1_CCQE_nuebarbkg);
  h1_TrueN -> Add(h1_CCOther_nuebkg);
  h1_TrueN -> Add(h1_CC2p2h_nuebkg);
  h1_TrueN -> Add(h1_CCQE_nuebkg);
  h1_TrueN -> Add(h1_CCOther_nuebarsig);
  h1_TrueN -> Add(h1_CC2p2h_nuebarsig);
  h1_TrueN -> Add(h1_CCQE_nuebarsig);
  h1_TrueN -> Add(h1_CCOther_nuesig);
  h1_TrueN -> Add(h1_CC2p2h_nuesig);
  h1_TrueN -> Add(h1_CCQE_nuesig);

  h1_TrueN -> Add(h1_CCOther_numubar);
  h1_TrueN -> Add(h1_CCOther_numu);
  h1_TrueN -> Add(h1_CC2p2h_numubar);
  h1_TrueN -> Add(h1_CC2p2h_numu);
  h1_TrueN -> Add(h1_CCQE_numubar);
  h1_TrueN -> Add(h1_CCQE_numu);


  h1_TagN -> Add(h1_TagN_NC_nuebarbkg);
  h1_TagN -> Add(h1_TagN_NC_nuebkg);
  h1_TagN -> Add(h1_TagN_NC_nuebarsig);
  h1_TagN -> Add(h1_TagN_NC_numubar);
  h1_TagN -> Add(h1_TagN_NC_nuesig);
  h1_TagN -> Add(h1_TagN_NC_numu);

  h1_TagN -> Add(h1_TagN_CCOther_nuebarbkg);
  h1_TagN -> Add(h1_TagN_CC2p2h_nuebarbkg);
  h1_TagN -> Add(h1_TagN_CCQE_nuebarbkg);
  h1_TagN -> Add(h1_TagN_CCOther_nuebkg);
  h1_TagN -> Add(h1_TagN_CC2p2h_nuebkg);
  h1_TagN -> Add(h1_TagN_CCQE_nuebkg);
  h1_TagN -> Add(h1_TagN_CCOther_nuebarsig);
  h1_TagN -> Add(h1_TagN_CC2p2h_nuebarsig);
  h1_TagN -> Add(h1_TagN_CCQE_nuebarsig);
  h1_TagN -> Add(h1_TagN_CCOther_nuesig);
  h1_TagN -> Add(h1_TagN_CC2p2h_nuesig);
  h1_TagN -> Add(h1_TagN_CCQE_nuesig);

  h1_TagN -> Add(h1_TagN_CCOther_numubar);
  h1_TagN -> Add(h1_TagN_CCOther_numu);
  h1_TagN -> Add(h1_TagN_CC2p2h_numubar);
  h1_TagN -> Add(h1_TagN_CC2p2h_numu);
  h1_TagN -> Add(h1_TagN_CCQE_numubar);
  h1_TagN -> Add(h1_TagN_CCQE_numu);
#endif


  TString foutname = TString::Format("output/NeutronMult.Gdconc%f.root", Gdconc);
  TFile* fout = new TFile(foutname, "RECREATE");
  fout -> cd();
  h1_TrueN -> Write();
  h1_TagN  -> Write();

}