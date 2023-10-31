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


void CapVtxResolution(bool beammode) {

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


  TH1F* h1_NCapVtxReso_numu      = (TH1F*)fin_numu->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_numubar   = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_nuebarsig = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_NCapVtxReso");

  TH1F* h1_NCapVtxReso_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");
  TH1F* h1_NCapVtxReso_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get("NTagAnalysis/h1_NCapVtxReso");

  bool mode[6] = {1, 1, 1, 1, 1, 1};

#if 0
  //  Normalization 
  if (mode[0]) h1_NCapVtxReso_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  if (mode[1]) h1_NCapVtxReso_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  if (mode[2]) h1_NCapVtxReso_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  if (mode[3]) h1_NCapVtxReso_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  if (mode[4]) h1_NCapVtxReso_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  if (mode[5]) h1_NCapVtxReso_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  int maximum = 500;
  int BINS    = 880;

  TH1F* h1_NCapVtxReso = new TH1F("h1_NCapVtxReso", "", BINS, 0, maximum);
  if (mode[5]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_nuebarbkg);
  if (mode[4]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_nuebkg);
  if (mode[3]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_nuebarsig);
  if (mode[2]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_numubar);
  if (mode[1]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_nuesig);
  if (mode[0]) h1_NCapVtxReso -> Add(h1_NCapVtxReso_numu);
  h1_NCapVtxReso -> SetLineColor(kViolet-7);
  h1_NCapVtxReso -> SetXTitle("d_{Reco. vs True}[cm]");
  h1_NCapVtxReso -> SetYTitle("Number of Events");
  h1_NCapVtxReso -> SetLineWidth(2);
  h1_NCapVtxReso -> SetStats(0);

  Double_t tot_NCapVtxReso = h1_NCapVtxReso->Integral();

  TH1F* h1_NCapVtxReso_ggarnet = new TH1F("h1_NCapVtxReso_ggarnet", "", BINS, 0, maximum);
  if (mode[5]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_nuebarbkg);
  if (mode[4]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_nuebkg);
  if (mode[3]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_nuebarsig);
  if (mode[2]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_numubar);
  if (mode[1]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_nuesig);
  if (mode[0]) h1_NCapVtxReso_ggarnet -> Add(h1_NCapVtxReso_ggarnet_numu);
  h1_NCapVtxReso_ggarnet -> SetLineColor(kRed-6);
  h1_NCapVtxReso_ggarnet -> SetXTitle("d_{Reco. vs True}[cm]");
  h1_NCapVtxReso_ggarnet -> SetYTitle("Number of Events");
  h1_NCapVtxReso_ggarnet -> SetLineWidth(2);
  h1_NCapVtxReso_ggarnet -> SetStats(0);

  Double_t tot_NCapVtxReso_ggarnet = h1_NCapVtxReso_ggarnet->Integral();
  h1_NCapVtxReso_ggarnet -> Scale(tot_NCapVtxReso/tot_NCapVtxReso_ggarnet);


  Double_t AllEvents         = h1_NCapVtxReso -> Integral();
  Double_t AllEvents_ggarnet = h1_NCapVtxReso_ggarnet -> Integral();
  //std::cout << "All events: " << AllEvents << std::endl;
  float start    = 0.;   // start value
  //float maximum  = 300.; // histo end [cm]
  //const int BINS = 100;  // Number of bins
  //const int BINS = 680;  // Number of bins
  float interval  = ((float)maximum - start)/BINS;   // bin witdh [cm]

  int   binnumber         = h1_NCapVtxReso->FindBin(start); // get bin number
  int   binnumber_ggarnet = h1_NCapVtxReso_ggarnet->FindBin(start); // get bin number

  float OneSigmaEvents = 0.;
  float tmpvalue       = 999.;
  float OneSigmaReso   = 999.;
  float OneSigmaEvents_ggarnet = 0.;
  float tmpvalue_ggarnet       = 999.;
  float OneSigmaReso_ggarnet   = 999.;
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisvalue = start+ibin*interval; // value of this bin

    OneSigmaEvents += h1_NCapVtxReso->GetBinContent(binnumber);
    if (std::fabs(OneSigmaEvents/AllEvents - 0.683) < tmpvalue) {
      tmpvalue     = std::fabs(OneSigmaEvents/AllEvents - 0.683);
      OneSigmaReso = thisvalue;
    }

    OneSigmaEvents_ggarnet += h1_NCapVtxReso_ggarnet->GetBinContent(binnumber);
    //std::cout << OneSigmaEvents_ggarnet << std::endl;
    if (std::fabs(OneSigmaEvents_ggarnet/AllEvents_ggarnet - 0.683) < tmpvalue_ggarnet) {
      tmpvalue_ggarnet     = std::fabs(OneSigmaEvents_ggarnet/AllEvents_ggarnet - 0.683);
      OneSigmaReso_ggarnet = thisvalue;
    }
    //std::cout << "[### " << ibin << " ###] " << thisvalue << " cm, Area: " << (OneSigmaEvents/AllEvents)*100. << " %"<< std::endl;
    binnumber++;
  }
  std::cout << "OneSigmaReso(ANNRI_Gd): " << OneSigmaReso << " cm" << std::endl;
  std::cout << "OneSigmaReso(GGARNET) : " << OneSigmaReso_ggarnet << " cm" << std::endl;



  float FrameMaximum = 200.;
  float y[2] = {0., FrameMaximum+10.};
  float x[2] = {OneSigmaReso, OneSigmaReso};
  TGraph* g_onesigma = new TGraph(2, x, y);
  g_onesigma -> SetLineWidth(2);
  g_onesigma -> SetLineColor(kViolet+8);
  g_onesigma -> SetLineStyle(7);

  float x_ggarnet[2] = {OneSigmaReso_ggarnet, OneSigmaReso_ggarnet};
  TGraph* g_onesigma_ggarnet = new TGraph(2, x_ggarnet, y);
  g_onesigma_ggarnet -> SetLineWidth(2);
  g_onesigma_ggarnet -> SetLineColor(kPink+2);
  g_onesigma_ggarnet -> SetLineStyle(7);

  TLegend* legend1 = new TLegend(0.3, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_NCapVtxReso, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(g_onesigma, TString::Format("#kern[-0.]{Resolution(ANNRI_Gd): %.1f cm}", OneSigmaReso), "L");
  legend1 -> AddEntry(h1_NCapVtxReso_ggarnet, "GGARNET-based MC", "L");
  legend1 -> AddEntry(g_onesigma_ggarnet, TString::Format("#kern[-0.]{Resolution(GGARNET): %.1f cm}", OneSigmaReso_ggarnet), "L");
  legend1 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_NCapVtxReso -> Draw("SAME");
  g_onesigma -> Draw("SAME");
  h1_NCapVtxReso_ggarnet -> Draw("SAME");
  g_onesigma_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();
#endif

}