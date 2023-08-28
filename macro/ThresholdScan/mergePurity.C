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

#define CUTSTEP 21

void mergePurity(bool beammode) {
  
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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");*/
#endif

#if 0
  ////  prompt_keras  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.promptkeras.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.promptkeras.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.promptkeras.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.promptkeras.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.promptkeras.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.promptkeras.root");
#endif

#if 0
  ////  bonsai_keras  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras.root");
#endif

#if 1
  ////  bonsai_keras w/ ToF  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
#endif

#if 0
  ////  -30%  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIm30.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIm30.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIm30.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIm30.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIm30.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIm30.root");
#endif

#if 0
  ////  +30%  ////
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.systSIp30.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.systSIp30.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.systSIp30.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.systSIp30.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.systSIp30.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.systSIp30.root");
#endif

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
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


  TH1F* h1_MisTagDcye_numu     = (TH1F*)fin_numu->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_numu       = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TagTrueN");

  TH1F* h1_MisTagDcye_nuesig     = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_nuesig       = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_TagTrueN");

  TH1F* h1_MisTagDcye_numubar     = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_numubar       = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_TagTrueN");

  TH1F* h1_MisTagDcye_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_nuebarsig       = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_TagTrueN");

  TH1F* h1_MisTagDcye_nuebkg     = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_nuebkg       = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_TagTrueN");

  TH1F* h1_MisTagDcye_nuebarbkg     = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_MisTagDcye");
  TH1F* h1_MisTagAccNoise_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_MisTagAccNoise");
  TH1F* h1_TagTrueN_nuebarbkg       = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_TagTrueN");


  /////  Normalizations  //////
#if 1
  h1_MisTagDcye_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_MisTagDcye_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_MisTagDcye_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_MisTagDcye_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_MisTagDcye_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_MisTagDcye_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_MisTagAccNoise_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_MisTagAccNoise_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_MisTagAccNoise_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_MisTagAccNoise_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_MisTagAccNoise_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_MisTagAccNoise_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagTrueN_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagTrueN_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagTrueN_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagTrueN_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagTrueN_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagTrueN_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  
  /////  Seletced 1Rmu events  /////
  TH1F* h1_Purity_merge = new TH1F("h1_TagTrueN_merge", "", 20, 0, 1);
  h1_Purity_merge -> Add(h1_TagTrueN_numu);
  h1_Purity_merge -> Add(h1_TagTrueN_nuesig);
  h1_Purity_merge -> Add(h1_TagTrueN_numubar);
  h1_Purity_merge -> Add(h1_TagTrueN_nuebarsig);
  h1_Purity_merge -> Add(h1_TagTrueN_nuebkg);
  h1_Purity_merge -> Add(h1_TagTrueN_nuebarbkg);
  h1_Purity_merge -> SetLineColor(kPink-5);
  h1_Purity_merge -> SetFillColor(kPink-2);
  h1_Purity_merge -> SetFillStyle(3004);
  h1_Purity_merge -> SetLineWidth(2);
  h1_Purity_merge -> SetStats(0);

  TH1F* h1_Nlike_merge = new TH1F("h1_Nlike_merge", "", 20, 0, 1);


  for (int ith=0; ith<CUTSTEP; ith++) {
    float TMVATH = 0.05*ith;
    std::cout << "[### " << TMVATH << " ###] " << std::endl;
    std::cout << "  [numu    ->  numu  ]Decay-e: " << h1_TagTrueN_numu->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numu    ->  nue   ]Decay-e: " << h1_TagTrueN_nuesig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> numubar]Decay-e: " << h1_TagTrueN_numubar->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> nuebar ]Decay-e: " << h1_TagTrueN_nuebarsig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nue     -> nue    ]Decay-e: " << h1_TagTrueN_nuebkg->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nuebar  -> nuebar ]Decay-e: " << h1_TagTrueN_nuebarbkg->GetBinContent(ith+1) << std::endl;
    float TagTrueN_merge = h1_TagTrueN_numu->GetBinContent(ith+1) +
                           h1_TagTrueN_nuesig->GetBinContent(ith+1) +
                           h1_TagTrueN_numubar->GetBinContent(ith+1) +
                           h1_TagTrueN_nuebarsig->GetBinContent(ith+1) +
                           h1_TagTrueN_nuebkg->GetBinContent(ith+1) +
                           h1_TagTrueN_nuebarbkg->GetBinContent(ith+1);
    std::cout << "  Total neutrons: " << TagTrueN_merge << std::endl;
    std::cout << "  [numu    ->  numu  ]Decay-e: " << h1_MisTagDcye_numu->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numu    ->  nue   ]Decay-e: " << h1_MisTagDcye_nuesig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> numubar]Decay-e: " << h1_MisTagDcye_numubar->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> nuebar ]Decay-e: " << h1_MisTagDcye_nuebarsig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nue     -> nue    ]Decay-e: " << h1_MisTagDcye_nuebkg->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nuebar  -> nuebar ]Decay-e: " << h1_MisTagDcye_nuebarbkg->GetBinContent(ith+1) << std::endl;
    float MisTagDcye_merge = h1_MisTagDcye_numu->GetBinContent(ith+1) +
                             h1_MisTagDcye_nuesig->GetBinContent(ith+1) +
                             h1_MisTagDcye_numubar->GetBinContent(ith+1) +
                             h1_MisTagDcye_nuebarsig->GetBinContent(ith+1) +
                             h1_MisTagDcye_nuebkg->GetBinContent(ith+1) +
                             h1_MisTagDcye_nuebarbkg->GetBinContent(ith+1);
    std::cout << "  Total Decay-e: " << MisTagDcye_merge << std::endl;

    std::cout << "  [numu    ->  numu  ]Acc.Noise: " << h1_MisTagAccNoise_numu->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numu    ->  nue   ]Acc.Noise: " << h1_MisTagAccNoise_nuesig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> numubar]Acc.Noise: " << h1_MisTagAccNoise_numubar->GetBinContent(ith+1) << std::endl;
    std::cout << "  [numubar -> nuebar ]Acc.Noise: " << h1_MisTagAccNoise_nuebarsig->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nue     -> nue    ]Acc.Noise: " << h1_MisTagAccNoise_nuebkg->GetBinContent(ith+1) << std::endl;
    std::cout << "  [nuebar  -> nuebar ]Acc.Noise: " << h1_MisTagAccNoise_nuebarbkg->GetBinContent(ith+1) << std::endl;
    float MisTagAccNoise_merge = h1_MisTagAccNoise_numu->GetBinContent(ith+1) +
                                 h1_MisTagAccNoise_nuesig->GetBinContent(ith+1) +
                                 h1_MisTagAccNoise_numubar->GetBinContent(ith+1) +
                                 h1_MisTagAccNoise_nuebarsig->GetBinContent(ith+1) +
                                 h1_MisTagAccNoise_nuebkg->GetBinContent(ith+1) +
                                 h1_MisTagAccNoise_nuebarbkg->GetBinContent(ith+1);
    std::cout << "  Total Acc.Noise: " << MisTagAccNoise_merge << std::endl;
    float Nlike_merge = TagTrueN_merge + MisTagDcye_merge + MisTagAccNoise_merge;
    std::cout << "  Total n-like: " << Nlike_merge << std::endl;
    std::cout << "  Purity: " << (h1_Purity_merge->GetBinContent(ith+1)/Nlike_merge)*100. << " %" << std::endl;

    h1_Nlike_merge -> SetBinContent(ith+1, Nlike_merge);
  }
  h1_Purity_merge -> Divide(h1_Nlike_merge);


#if 0
  TH1F* h1_NoiseRate_merge = new TH1F("h1_NoiseRate_merge", "", 20, 0, 1);
  h1_NoiseRate_merge -> SetLineColor(kPink-5);
  h1_NoiseRate_merge -> SetFillColor(kPink-7);
  h1_NoiseRate_merge -> SetFillStyle(3004);
  h1_NoiseRate_merge -> SetLineWidth(2);
  h1_NoiseRate_merge -> SetStats(0);

  

  /////  Numerator  /////
  float correctionfactor = (535. - 3.)/(535. - 18.);
  h1_NoiseRate_merge -> Add(h1_MisTagDcye_numu, h1_MisTagAccNoise_numu, 1., correctionfactor);
  h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuesig, h1_MisTagAccNoise_nuesig, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_numubar, h1_MisTagAccNoise_numubar, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuebarsig, h1_MisTagAccNoise_nuebarsig, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuebkg, h1_MisTagAccNoise_nuebkg, 1., correctionfactor);
  //h1_NoiseRate_merge    -> Add(h1_MisTagDcye_nuebarbkg, h1_MisTagDcye_nuebarbkg, 1., correctionfactor);

  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_numu, 1.);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuesig, h1_MisTagAccNoise_nuesig, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_numubar, h1_MisTagAccNoise_numubar, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuebarsig, h1_MisTagAccNoise_nuebarsig, 1., correctionfactor);
  //h1_NoiseRate_merge -> Add(h1_MisTagDcye_nuebkg, h1_MisTagAccNoise_nuebkg, 1., correctionfactor);
  //h1_NoiseRate_merge    -> Add(h1_MisTagDcye_nuebarbkg, h1_MisTagDcye_nuebarbkg, 1., correctionfactor);

  /////  Denominator  /////
  h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_numu);
  h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_nuesig);
  //h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_numubar);
  //h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_nuebarsig);
  //h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_nuebkg);
  //h1_NuEvtC6_merge    -> Add(h1_NuEvtC6_nuebarbkg);

  ////  Noise Rate  /////
  h1_NoiseRate_merge -> Sumw2();
  h1_NoiseRate_merge -> Divide(h1_NuEvtC6_merge);

  std::cout << "1Rmu events: " << h1_NuEvtC6_merge->GetBinContent(1) << std::endl;
  for (int ith=0; ith<CUTSTEP; ith++) {
    float TMVATH = 0.05*ith;
    //std::cout << "[### n-likelihood=" << TMVATH << " ###] Decay-e: " << h1_NoiseRate_merge->GetBinContent(ith+1) << std::endl;
    std::cout << "[### n-likelihood=" << TMVATH << " ###] Noise Rate: " << h1_NoiseRate_merge->GetBinContent(ith+1)*100. << " %" << std::endl;
  }
#endif


#if 1
  TCanvas* c = new TCanvas("c", "c", 700, 700);
  c -> SetGrid();
  h1_Purity_merge -> Draw();
  h1_Purity_merge -> SetMinimum(0.);
  h1_Purity_merge -> SetMaximum(1.);
  h1_Purity_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_Purity_merge ->GetYaxis()->SetTitleOffset(1.2);
  //h1_Purity_merge ->GetYaxis()->SetLabelSize(0.04);
  h1_Purity_merge ->GetYaxis()->SetTitle("Purity");
  h1_Purity_merge ->GetYaxis()->SetTitleSize(0.04);
  h1_Purity_merge ->GetXaxis()->SetTitleSize(0.04);
  h1_Purity_merge ->GetXaxis()->SetTitle("n-likelihood");
  h1_Purity_merge -> Draw("histo");
  //h1_Purity_merge -> Draw("SAME");
  //h1_Purity_merge -> Draw("SAME");

  float xMinPos = 1; // x-minimum where you want to set
  float xMaxPos = 1; // x-maximum where you want to set
  float yMinPos = 0; // y-minimum where you want to set
  float yMaxPos = 1; // y-maximum where you want to set
  float SetPos  = 1;
  TGaxis* axis = new TGaxis(xMinPos,yMinPos,xMaxPos,yMaxPos, 0, SetPos, 510, "+L");
  //axis -> SetTitle("Purity");
  //axis -> SetTitleSize(0.035);
  //axis -> SetTitleColor(kPink-5);
  axis -> SetLabelColor(kWhite);
  //axis -> SetLabelSize(0.035);
  axis -> Draw();

  TLatex* text1 = new TLatex(0.35, 0.35, "T2K FHC Run11 (0.01% Gd)");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);
  TLatex* text2 = new TLatex(0.38, 0.3, "-1R #mu sample");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.04);
  TLatex* text3 = new TLatex(0.38, 0.25, "-Gd(n,#gamma)+p(n,#gamma)");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.04);
  text1 -> Draw();
  text2 -> Draw();
  text3 -> Draw();
#endif

}
