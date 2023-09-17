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
#define nThreshold 0.7


void mergeTagEff_x_dist(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;

  TFile* fin_promptkeras_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.promptkeras.root");   /// prompt_keras
  TFile* fin_promptkeras_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.promptkeras.root");       
  TFile* fin_promptkeras_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.promptkeras.root");
  TFile* fin_promptkeras_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.promptkeras.root"); 
  TFile* fin_promptkeras_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.promptkeras.root");        
  TFile* fin_promptkeras_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.promptkeras.root");  

  TFile* fin_bonsaikeras_ToF_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");   /// ToF bonsai_keras
  TFile* fin_bonsaikeras_ToF_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_bonsaikeras_ToF_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_bonsaikeras_ToF_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_bonsaikeras_ToF_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_bonsaikeras_ToF_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");

  TFile* fin_bonsaikeras_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras.root");   /// no-ToF bonsai_keras
  TFile* fin_bonsaikeras_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_bonsaikeras_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras.root");
  TFile* fin_bonsaikeras_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras.root");
  TFile* fin_bonsaikeras_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras.root");
  TFile* fin_bonsaikeras_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras.root");


  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");



  //////  prompt Keras w/ ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_promptkeras_numu = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_promptkeras_numu  = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_promptkeras_numu    = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");

  //////  BONSAI Keras w/ ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_bonsaikeras_ToF_numu = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_bonsaikeras_ToF_numu  = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_bonsaikeras_ToF_numu    = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");
  

  //////  BONSAI Keras w/o ToF-subtraction @ pre-selection  //////
  TH1D* h1_PreEff_bonsaikeras_numu = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_PreEff_dist");
  TH1D* h1_NNEff_bonsaikeras_numu  = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_NNEff_dist_thr14");
  TH1D* h1_Eff_bonsaikeras_numu    = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_OverallEff_dist_thr14");



  /////  Truth neutrons  /////
  TH1D* h1_TrueD_numu      = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_nuesig    = (TH1D*)fin_promptkeras_nuesig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_numubar   = (TH1D*)fin_promptkeras_numubar->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_nuebarsig = (TH1D*)fin_promptkeras_nuebarsig->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_nuebkg    = (TH1D*)fin_promptkeras_nuebkg->Get("DistanceViewer/h1_truedistance");
  TH1D* h1_TrueD_nuebarbkg = (TH1D*)fin_promptkeras_nuebarbkg->Get("DistanceViewer/h1_truedistance");

  /////  True candidates  /////
  TH1D* h1_nCanD_promptkeras_numu      = (TH1D*)fin_promptkeras_numu->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_promptkeras_nuesig    = (TH1D*)fin_promptkeras_nuesig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_promptkeras_numubar   = (TH1D*)fin_promptkeras_numubar->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_promptkeras_nuebarsig = (TH1D*)fin_promptkeras_nuebarsig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_promptkeras_nuebkg    = (TH1D*)fin_promptkeras_nuebkg->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_promptkeras_nuebarbkg = (TH1D*)fin_promptkeras_nuebarbkg->Get("DistanceViewer/h1_Candidatetruedistance");

  TH1D* h1_nCanD_bonsaikeras_numu      = (TH1D*)fin_bonsaikeras_numu->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_nuesig    = (TH1D*)fin_bonsaikeras_nuesig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_numubar   = (TH1D*)fin_bonsaikeras_numubar->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_nuebarsig = (TH1D*)fin_bonsaikeras_nuebarsig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_nuebkg    = (TH1D*)fin_bonsaikeras_nuebkg->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_nuebarbkg = (TH1D*)fin_bonsaikeras_nuebarbkg->Get("DistanceViewer/h1_Candidatetruedistance");

  TH1D* h1_nCanD_bonsaikeras_ToF_numu      = (TH1D*)fin_bonsaikeras_ToF_numu->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_ToF_nuesig    = (TH1D*)fin_bonsaikeras_ToF_nuesig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_ToF_numubar   = (TH1D*)fin_bonsaikeras_ToF_numubar->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_ToF_nuebarsig = (TH1D*)fin_bonsaikeras_ToF_nuebarsig->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_ToF_nuebkg    = (TH1D*)fin_bonsaikeras_ToF_nuebkg->Get("DistanceViewer/h1_Candidatetruedistance");
  TH1D* h1_nCanD_bonsaikeras_ToF_nuebarbkg = (TH1D*)fin_bonsaikeras_ToF_nuebarbkg->Get("DistanceViewer/h1_Candidatetruedistance");

  /////  Tagged truth neutrons  /////
  float ThrNum = nThreshold/0.05;
  std::cout << "n-like threshold: " << nThreshold << " (#" << (int)ThrNum << ")" << std::endl;
  TH1D* h1_TagnD_promptkeras_numu      = (TH1D*)fin_promptkeras_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_promptkeras_nuesig    = (TH1D*)fin_promptkeras_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_promptkeras_numubar   = (TH1D*)fin_promptkeras_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_promptkeras_nuebarsig = (TH1D*)fin_promptkeras_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_promptkeras_nuebkg    = (TH1D*)fin_promptkeras_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_promptkeras_nuebarbkg = (TH1D*)fin_promptkeras_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));

  TH1D* h1_TagnD_bonsaikeras_numu      = (TH1D*)fin_bonsaikeras_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_nuesig    = (TH1D*)fin_bonsaikeras_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_numubar   = (TH1D*)fin_bonsaikeras_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_nuebarsig = (TH1D*)fin_bonsaikeras_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_nuebkg    = (TH1D*)fin_bonsaikeras_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_nuebarbkg = (TH1D*)fin_bonsaikeras_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));

  TH1D* h1_TagnD_bonsaikeras_ToF_numu      = (TH1D*)fin_bonsaikeras_ToF_numu->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_ToF_nuesig    = (TH1D*)fin_bonsaikeras_ToF_nuesig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_ToF_numubar   = (TH1D*)fin_bonsaikeras_ToF_numubar->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_ToF_nuebarsig = (TH1D*)fin_bonsaikeras_ToF_nuebarsig->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_ToF_nuebkg    = (TH1D*)fin_bonsaikeras_ToF_nuebkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));
  TH1D* h1_TagnD_bonsaikeras_ToF_nuebarbkg = (TH1D*)fin_bonsaikeras_ToF_nuebarbkg->Get(TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum));


#if 1
  ////  True neutrons (denominator)  ////
  TH1F* h1_TrueD_merge = new TH1F("h1_TrueD_merge", "", 10, 0, 5);
  h1_TrueD_merge -> Add(h1_TrueD_numu);
  h1_TrueD_merge -> Add(h1_TrueD_nuesig);
  h1_TrueD_merge -> Add(h1_TrueD_numubar);
  h1_TrueD_merge -> Add(h1_TrueD_nuebarsig);
  h1_TrueD_merge -> Add(h1_TrueD_nuebkg);
  h1_TrueD_merge -> Add(h1_TrueD_nuebarbkg);


  ////  Pre-selection efficiency (numerator)  /////
  TH1F* h1_PreEff_promptkeras_merge = new TH1F("h1_PreEff_promptkeras_merge", "", 10, 0, 5);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_numu);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuesig);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_numubar);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebarsig);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebkg);
  h1_PreEff_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebarbkg);

  TH1F* h1_PreEff_bonsaikeras_merge = new TH1F("h1_PreEff_bonsaikeras_merge", "", 10, 0, 5);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_numu);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuesig);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_numubar);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebarsig);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebkg);
  h1_PreEff_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebarbkg);

  TH1F* h1_PreEff_bonsaikeras_ToF_merge = new TH1F("h1_PreEff_bonsaikeras_ToF_merge", "", 10, 0, 5);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_numu);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuesig);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_numubar);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebarsig);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebkg);
  h1_PreEff_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebarbkg);


  ////  True candidate (denominator)  ////
  TH1F* h1_nCanD_promptkeras_merge = new TH1F("h1_nCanD_promptkeras_merge", "", 10, 0, 5);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_numu);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuesig);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_numubar);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebarsig);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebkg);
  h1_nCanD_promptkeras_merge -> Add(h1_nCanD_promptkeras_nuebarbkg);

  TH1F* h1_nCanD_bonsaikeras_merge = new TH1F("h1_nCanD_bonsaikeras_merge", "", 10, 0, 5);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_numu);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuesig);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_numubar);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebarsig);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebkg);
  h1_nCanD_bonsaikeras_merge -> Add(h1_nCanD_bonsaikeras_nuebarbkg);

  TH1F* h1_nCanD_bonsaikeras_ToF_merge = new TH1F("h1_nCanD_bonsaikeras_ToF_merge", "", 10, 0, 5);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_numu);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuesig);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_numubar);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebarsig);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebkg);
  h1_nCanD_bonsaikeras_ToF_merge -> Add(h1_nCanD_bonsaikeras_ToF_nuebarbkg);


  ////  NN efficiency (numerator)  ////
  TH1F* h1_NNEff_promptkeras_merge = new TH1F("h1_NNEff_promptkeras_merge", "", 10, 0, 5);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numu);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuesig);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numubar);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarsig);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebkg);
  h1_NNEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarbkg);

  TH1F* h1_NNEff_bonsaikeras_merge = new TH1F("h1_NNEff_bonsaikeras_merge", "", 10, 0, 5);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_numu);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuesig);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_numubar);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebarsig);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebkg);
  h1_NNEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebarbkg);

  TH1F* h1_NNEff_bonsaikeras_ToF_merge = new TH1F("h1_NNEff_bonsaikeras_ToF_merge", "", 10, 0, 5);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_numu);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuesig);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_numubar);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebarsig);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebkg);
  h1_NNEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebarbkg);


  ////  Overall efficiency (numerator)  ////
  TH1F* h1_TagEff_promptkeras_merge = new TH1F("h1_TagEff_promptkeras_merge", "", 10, 0, 5);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numu);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuesig);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_numubar);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarsig);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebkg);
  h1_TagEff_promptkeras_merge -> Add(h1_TagnD_promptkeras_nuebarbkg);

  TH1F* h1_TagEff_bonsaikeras_merge = new TH1F("h1_TagEff_bonsaikeras_merge", "", 10, 0, 5);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_numu);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuesig);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_numubar);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebarsig);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebkg);
  h1_TagEff_bonsaikeras_merge -> Add(h1_TagnD_bonsaikeras_nuebarbkg);

  TH1F* h1_TagEff_bonsaikeras_ToF_merge = new TH1F("h1_TagEff_bonsaikeras_ToF_merge", "", 10, 0, 5);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_numu);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuesig);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_numubar);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebarsig);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebkg);
  h1_TagEff_bonsaikeras_ToF_merge -> Add(h1_TagnD_bonsaikeras_ToF_nuebarbkg);
#endif


  
  h1_PreEff_promptkeras_merge -> SetLineColor(kAzure+7);
  h1_PreEff_promptkeras_merge -> SetLineWidth(3);
  h1_PreEff_promptkeras_merge -> SetStats(0);
  h1_PreEff_promptkeras_merge -> SetTitleOffset(0.9, "Y");
  h1_PreEff_promptkeras_merge ->GetXaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_merge ->GetYaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_merge -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_PreEff_promptkeras_merge -> SetYTitle("Pre-selection Efficiency");
  h1_PreEff_promptkeras_merge -> Sumw2();
  h1_PreEff_promptkeras_merge -> Divide(h1_TrueD_merge);

  h1_PreEff_bonsaikeras_merge -> SetLineColor(kOrange+7);
  h1_PreEff_bonsaikeras_merge -> SetLineWidth(3);
  h1_PreEff_bonsaikeras_merge -> Sumw2();
  h1_PreEff_bonsaikeras_merge -> Divide(h1_TrueD_merge);

  h1_PreEff_bonsaikeras_ToF_merge -> SetLineColor(kSpring-5);
  h1_PreEff_bonsaikeras_ToF_merge -> SetLineWidth(3);
  h1_PreEff_bonsaikeras_ToF_merge -> Sumw2();
  h1_PreEff_bonsaikeras_ToF_merge -> Divide(h1_TrueD_merge);
  

  h1_NNEff_promptkeras_merge -> SetLineColor(kAzure+7);
  h1_NNEff_promptkeras_merge -> SetLineWidth(3);
  h1_NNEff_promptkeras_merge -> SetStats(0);
  h1_NNEff_promptkeras_merge -> SetTitleOffset(0.9, "Y");
  h1_NNEff_promptkeras_merge ->GetXaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_merge ->GetYaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_merge -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_NNEff_promptkeras_merge -> SetYTitle("NN Classification Efficiency");
  h1_NNEff_promptkeras_merge -> Sumw2();
  h1_NNEff_promptkeras_merge -> Divide(h1_nCanD_promptkeras_merge);

  h1_NNEff_bonsaikeras_merge -> SetLineColor(kOrange+7);
  h1_NNEff_bonsaikeras_merge -> SetLineWidth(3);
  h1_NNEff_bonsaikeras_merge -> Sumw2();
  h1_NNEff_bonsaikeras_merge -> Divide(h1_nCanD_bonsaikeras_merge);

  h1_NNEff_bonsaikeras_ToF_merge -> SetLineColor(kSpring-5);
  h1_NNEff_bonsaikeras_ToF_merge -> SetLineWidth(3);
  h1_NNEff_bonsaikeras_ToF_merge -> Sumw2();
  h1_NNEff_bonsaikeras_ToF_merge -> Divide(h1_nCanD_bonsaikeras_ToF_merge);


  h1_TagEff_promptkeras_merge -> SetLineColor(kAzure+7);
  h1_TagEff_promptkeras_merge -> SetLineWidth(3);
  h1_TagEff_promptkeras_merge -> SetStats(0);
  h1_TagEff_promptkeras_merge -> SetTitleOffset(0.9, "Y");
  h1_TagEff_promptkeras_merge ->GetXaxis()->SetTitleSize(0.045);
  h1_TagEff_promptkeras_merge ->GetYaxis()->SetTitleSize(0.045);
  h1_TagEff_promptkeras_merge -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_TagEff_promptkeras_merge -> SetYTitle("Overall Tagging Efficiency");
  h1_TagEff_promptkeras_merge -> Sumw2();
  h1_TagEff_promptkeras_merge -> Divide(h1_TrueD_merge);

  h1_TagEff_bonsaikeras_merge -> SetLineColor(kOrange+7);
  h1_TagEff_bonsaikeras_merge -> SetLineWidth(3);
  h1_TagEff_bonsaikeras_merge -> Sumw2();
  h1_TagEff_bonsaikeras_merge -> Divide(h1_TrueD_merge);

  h1_TagEff_bonsaikeras_ToF_merge -> SetLineColor(kSpring-5);
  h1_TagEff_bonsaikeras_ToF_merge -> SetLineWidth(3);
  h1_TagEff_bonsaikeras_ToF_merge -> Sumw2();
  h1_TagEff_bonsaikeras_ToF_merge -> Divide(h1_TrueD_merge);



  h1_PreEff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_PreEff_promptkeras_numu -> SetLineWidth(3);
  h1_PreEff_promptkeras_numu -> SetStats(0);
  h1_PreEff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_PreEff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_PreEff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_PreEff_promptkeras_numu -> SetYTitle("Pre-selection Efficiency");

  h1_PreEff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_PreEff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_PreEff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_PreEff_bonsaikeras_numu -> SetLineWidth(3);

  h1_NNEff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_NNEff_promptkeras_numu -> SetLineWidth(3);
  h1_NNEff_promptkeras_numu -> SetStats(0);
  h1_NNEff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_NNEff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_NNEff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_NNEff_promptkeras_numu -> SetYTitle("NN Classification Efficiency");

  h1_NNEff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_NNEff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_NNEff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_NNEff_bonsaikeras_numu -> SetLineWidth(3);

  h1_Eff_promptkeras_numu -> SetLineColor(kAzure+7);
  h1_Eff_promptkeras_numu -> SetLineWidth(3);
  h1_Eff_promptkeras_numu -> SetStats(0);
  h1_Eff_promptkeras_numu -> SetTitleOffset(0.9, "Y");
  h1_Eff_promptkeras_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_Eff_promptkeras_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_Eff_promptkeras_numu -> SetXTitle("Truth Neutron Travel Distance [m]");
  h1_Eff_promptkeras_numu -> SetYTitle("Overall Tagging Efficiency");

  h1_Eff_bonsaikeras_ToF_numu -> SetLineColor(kSpring-5);
  h1_Eff_bonsaikeras_ToF_numu -> SetLineWidth(3);

  h1_Eff_bonsaikeras_numu -> SetLineColor(kOrange+7);
  h1_Eff_bonsaikeras_numu -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.13, 0.16, 0.55, 0.35);
  legend1 -> SetTextSize(0.035);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_Eff_promptkeras_numu, "prompt Keras", "L");
  legend1 -> AddEntry(h1_Eff_bonsaikeras_ToF_numu, "BONSAI Keras", "L");
  legend1 -> AddEntry(h1_Eff_bonsaikeras_numu, "BONSAI Keras (no ToF)", "L");
  legend1 -> SetFillColor(0);

  TLegend* legend2 = new TLegend(0.13, 0.13, 0.6, 0.35);
  legend2 -> SetTextSize(0.035);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  //legend2 -> AddEntry((TObject*)0,"#kern[-0]{NN: Keras trained by SKG4 single n MC}","");
  legend2 -> AddEntry(h1_Eff_promptkeras_numu, "prompt Keras", "L");
  legend2 -> AddEntry(h1_Eff_bonsaikeras_ToF_numu, "BONSAI Keras", "L");
  legend2 -> AddEntry(h1_Eff_bonsaikeras_numu, "BONSAI Keras (no ToF)", "L");
  legend2 -> AddEntry((TObject*)0,"#kern[-0]{ (n-like threshold: 0.7)}","");
  legend2 -> SetFillColor(0);


  /////  for JPS
  TLegend* legend3 = new TLegend(0.13, 0.13, 0.6, 0.35);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  legend3 -> AddEntry(h1_Eff_promptkeras_numu, "Keras w/ prompt vertex", "L");
  legend3 -> AddEntry(h1_Eff_bonsaikeras_ToF_numu, "Keras w/ BONSAI vertex", "L");
  //legend3 -> AddEntry((TObject*)0,"#kern[-0]{ (n-like threshold: 0.7)}","");
  legend3 -> SetFillColor(0);


gROOT -> SetStyle("Plain");
#if 0
  TCanvas* ctruen = new TCanvas("ctruen","ctruen", 900, 700);
  ctruen -> SetGrid();
  ctruen -> cd();
  h1_TrueD_merge -> Draw();
  //legend1 -> Draw();
#endif


#if 0
  /// Pre-selection ////////////////////////////////
  TCanvas* cpreeff = new TCanvas("cpreeff","cpreeff", 900, 700);
  cpreeff -> SetGrid();
  cpreeff -> cd();

  //h1_PreEff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0.2, 1.0);
  //h1_PreEff_promptkeras_numu     -> Draw();
  //h1_PreEff_bonsaikeras_ToF_numu -> Draw("SAME");
  //h1_PreEff_bonsaikeras_numu     -> Draw("SAME");

  h1_PreEff_promptkeras_merge -> GetYaxis() -> SetRangeUser(0., 1.0);
  h1_PreEff_promptkeras_merge     -> Draw();
  h1_PreEff_bonsaikeras_ToF_merge -> Draw("SAME");
  h1_PreEff_bonsaikeras_merge     -> Draw("SAME");

  legend1 -> Draw();
#endif


#if 0
  /// NN classification ////////////////////////////////
  TCanvas* cnneff = new TCanvas("cnneff","cnneff", 900, 700);
  cnneff -> SetGrid();
  cnneff -> cd();

  //h1_NNEff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0., 1.0);
  //h1_NNEff_promptkeras_numu     -> Draw();
  //h1_NNEff_bonsaikeras_ToF_numu -> Draw("SAME");
  //h1_NNEff_bonsaikeras_numu     -> Draw("SAME");

  h1_NNEff_promptkeras_merge -> GetYaxis() -> SetRangeUser(0., 1.0);
  h1_NNEff_promptkeras_merge     -> Draw();
  h1_NNEff_bonsaikeras_ToF_merge -> Draw("SAME");
  h1_NNEff_bonsaikeras_merge     -> Draw("SAME");

  legend2 -> Draw();
#endif 

#if 1
  /// Overall ////////////////////////////////
  TCanvas* cEff = new TCanvas("cEff","Overall Eff", 900, 700);
  cEff -> SetGrid();
  cEff -> cd();

  //h1_Eff_promptkeras_numu -> GetYaxis() -> SetRangeUser(0., 0.7);
  //h1_Eff_promptkeras_numu     -> Draw();
  //h1_Eff_bonsaikeras_ToF_numu -> Draw("SAME");
  //h1_Eff_bonsaikeras_numu     -> Draw("SAME");

  h1_TagEff_promptkeras_merge -> GetYaxis() -> SetRangeUser(0., 0.7);
  h1_TagEff_promptkeras_merge     -> Draw();
  h1_TagEff_bonsaikeras_ToF_merge -> Draw("SAME");
  //h1_TagEff_bonsaikeras_merge     -> Draw("SAME");

  //legend2 -> Draw();
  legend3 -> Draw();

  /*h1_TagEff_promptkeras_merge -> GetYaxis() -> SetRangeUser(0., 0.7);
  h1_TagEff_promptkeras_merge -> Sumw2();
  h1_TagEff_promptkeras_merge -> Divide(h1_TrueD_merge);
  h1_TagEff_promptkeras_merge -> Draw("histo");*/
#endif

}

