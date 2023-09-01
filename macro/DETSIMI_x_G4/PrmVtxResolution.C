#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

#define ONERINGMU_EVENTS 26132

void PrmVtxResolution(bool beammode) {

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
  TFile* fin_numu_detsim  = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");

  TFile* fin_numu_skg4    = new TFile("../../output/fhc/fhc.numu_x_numu.skg4MC.bonsaikeras_ToF.root");

  //TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu         = 63622;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  TH1F* h1_CCQE_numu_detsim    = (TH1F*)fin_numu_detsim->Get("NeutrinoOscillation/h1_PrmVtxReso_mode0");
  TH1F* h1_CC2p2h_numu_detsim  = (TH1F*)fin_numu_detsim->Get("NeutrinoOscillation/h1_PrmVtxReso_mode1");
  TH1F* h1_CCnonQE_numu_detsim = (TH1F*)fin_numu_detsim->Get("NeutrinoOscillation/h1_PrmVtxReso_mode2");
  TH1F* h1_NC_numu_detsim      = (TH1F*)fin_numu_detsim->Get("NeutrinoOscillation/h1_PrmVtxReso_mode3");


  TH1F* h1_CCQE_numu_skg4    = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_mode0");
  TH1F* h1_CC2p2h_numu_skg4  = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_mode1");
  TH1F* h1_CCnonQE_numu_skg4 = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_mode2");
  TH1F* h1_NC_numu_skg4      = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_mode3");

  TH1F* h1_PrmVtxResoX = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxResoX");
  TH1F* h1_PrmVtxResoY = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxResoY");
  TH1F* h1_PrmVtxResoZ = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxResoZ");

  TH2F* h2_PrmVtxReso  = (TH2F*)fin_numu_skg4->Get("NeutrinoOscillation/h2_PrmVtxReso");
  h2_PrmVtxReso -> SetStats(0);
  h2_PrmVtxReso -> SetYTitle("SKDETSIM-based MC d_{Reco} [m]");
  h2_PrmVtxReso -> SetTitleOffset(1.1, "Y");
  h2_PrmVtxReso -> SetXTitle("SKG4-based MC d_{Reco} [m]");
  h2_PrmVtxReso -> SetTitleOffset(1.2, "X");

  TH2F* h2_True_x_Reco = (TH2F*)fin_numu_skg4->Get("NeutrinoOscillation/h2_True_x_Reco");
  h2_True_x_Reco -> SetStats(0);
  //h2_True_x_Reco -> SetYTitle("SKG4-based fiTQun vertex d_{Reco} [m]");
  h2_True_x_Reco -> SetYTitle("SKDETSIM-based fiTQun vertex d_{Reco} [m]");
  h2_True_x_Reco -> SetTitleOffset(1.1, "Y");
  h2_True_x_Reco -> SetXTitle("True Primary Vertex d_{True} [m]");
  h2_True_x_Reco -> SetTitleOffset(1.2, "X");


  h1_PrmVtxResoX -> SetLineColor(kViolet-7);
  h1_PrmVtxResoX -> SetLineWidth(3);
  h1_PrmVtxResoX -> SetStats(0);
  h1_PrmVtxResoX -> SetYTitle("Neutrino Events");
  h1_PrmVtxResoX -> SetXTitle("SKDETSIM - SKG4 X [cm]");

  h1_PrmVtxResoY -> SetLineColor(kViolet-7);
  h1_PrmVtxResoY -> SetLineWidth(3);
  h1_PrmVtxResoY -> SetStats(0);
  h1_PrmVtxResoY -> SetYTitle("Neutrino Events");
  h1_PrmVtxResoY -> SetXTitle("SKDETSIM - SKG4 Y [cm]");

  h1_PrmVtxResoZ -> SetLineColor(kViolet-7);
  h1_PrmVtxResoZ -> SetLineWidth(3);
  h1_PrmVtxResoZ -> SetStats(0);
  h1_PrmVtxResoZ -> SetYTitle("Neutrino Events");
  h1_PrmVtxResoZ -> SetXTitle("SKDETSIM - SKG4 Z [cm]");


  TH1F* h1_PrmVtxReso_detsim = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_DETSIM");
  /*TH1F* h1_PrmVtxReso_detsim = new TH1F("h1_PrmVtxReso_detsim", "", 4000, 0, 200);
  h1_PrmVtxReso_detsim -> Add(h1_CCQE_numu_detsim, 1.);
  h1_PrmVtxReso_detsim -> Add(h1_CC2p2h_numu_detsim, 1.);
  h1_PrmVtxReso_detsim -> Add(h1_CCnonQE_numu_detsim, 1.);
  h1_PrmVtxReso_detsim -> Add(h1_NC_numu_detsim, 1.);*/

  h1_PrmVtxReso_detsim -> SetLineColor(kViolet-7);
  h1_PrmVtxReso_detsim -> SetLineWidth(3);
  h1_PrmVtxReso_detsim -> SetStats(0);
  h1_PrmVtxReso_detsim -> SetYTitle("Neutrino Events");
  h1_PrmVtxReso_detsim -> SetXTitle("Primary Vertex Resolution d_{True - Reco} [cm]");


  TH1F* h1_PrmVtxReso_skg4 = (TH1F*)fin_numu_skg4->Get("NeutrinoOscillation/h1_PrmVtxReso_G4");
  /*TH1F* h1_PrmVtxReso_skg4 = new TH1F("h1_PrmVtxReso_skg4", "", 4000, 0, 200);
  h1_PrmVtxReso_skg4 -> Add(h1_CCQE_numu_skg4, 1.);
  h1_PrmVtxReso_skg4 -> Add(h1_CC2p2h_numu_skg4, 1.);
  h1_PrmVtxReso_skg4 -> Add(h1_CCnonQE_numu_skg4, 1.);
  h1_PrmVtxReso_skg4 -> Add(h1_NC_numu_skg4, 1.);*/
  
  h1_PrmVtxReso_skg4 -> SetLineColor(kAzure-9);
  h1_PrmVtxReso_skg4 -> SetLineWidth(3);
  h1_PrmVtxReso_skg4 -> SetStats(0);


  /////  68 percentile line  //////
  //Double_t AllEvents_detsim = h1_PrmVtxReso_detsim -> Integral();
  //Double_t AllEvents_skg4   = h1_PrmVtxReso_skg4 -> Integral();
  Double_t AllEvents_detsim = ONERINGMU_EVENTS;
  Double_t AllEvents_skg4   = ONERINGMU_EVENTS;
  //std::cout << "All events: " << AllEvents_detsim << " (DETSIM), " << AllEvents_skg4 << " (SKG4)" << std::endl;

  double start     = 0.;   // start value
  double maximum   = 150.; // histo end [cm]
  const int BINS   = 180;  // Number of bins
  double interval  = (maximum - start)/BINS;   // bin witdh [cm]
  int    binnumber = h1_PrmVtxReso_skg4->FindBin(start); // get bin number
  
  Double_t OneSigmaEvents_detsim = 0.;
  Double_t tmpvalue_detsim       = 999.;
  Double_t OneSigmaReso_detsim   = 999.;

  Double_t OneSigmaEvents_skg4 = 0.;
  Double_t tmpvalue_skg4       = 999.;
  Double_t OneSigmaReso_skg4   = 999.;

  for (int ibin=0; ibin<BINS; ibin++) {
    float thisvalue = start+ibin*interval; // value of this bin

    OneSigmaEvents_detsim += h1_PrmVtxReso_detsim->GetBinContent(binnumber);
    OneSigmaEvents_skg4   += h1_PrmVtxReso_skg4->GetBinContent(binnumber);

    if (std::fabs(OneSigmaEvents_detsim/AllEvents_detsim - 0.682689492) < tmpvalue_detsim) {
      tmpvalue_detsim     = std::fabs(OneSigmaEvents_detsim/AllEvents_detsim - 0.682689492);
      OneSigmaReso_detsim = thisvalue;
    }

    if (std::fabs(OneSigmaEvents_skg4/AllEvents_skg4 - 0.682689492) < tmpvalue_skg4) {
      tmpvalue_skg4     = std::fabs(OneSigmaEvents_skg4/AllEvents_skg4 - 0.682689492);
      OneSigmaReso_skg4 = thisvalue;
    }

    //std::cout << "[### " << ibin << " ###] " << thisvalue << " cm, Area: " << (OneSigmaEvents/AllEvents)*100. << " %"<< std::endl;
    binnumber++;
  }
  std::cout << "OneSigmaReso(DETSIM): " << setprecision(6) << OneSigmaReso_detsim << " cm" << std::endl;
  std::cout << "OneSigmaReso(SKG4)  : " << OneSigmaReso_skg4 << " cm" << std::endl;

  float FrameMaximum = 2000.;
  float y[2] = {0., FrameMaximum+10.};
  float x_G4[2] = {OneSigmaReso_skg4, OneSigmaReso_skg4};
  TGraph* g_onesigma_G4 = new TGraph(2, x_G4, y);
  g_onesigma_G4 -> SetLineWidth(2);
  g_onesigma_G4 -> SetLineColor(kAzure-9);
  g_onesigma_G4 -> SetLineStyle(7);

  float x_DETSIM[2] = {OneSigmaReso_detsim, OneSigmaReso_detsim};
  TGraph* g_onesigma_DETSIM = new TGraph(2, x_DETSIM, y);
  g_onesigma_DETSIM -> SetLineWidth(2);
  g_onesigma_DETSIM -> SetLineColor(kViolet-7);
  g_onesigma_DETSIM -> SetLineStyle(7);



  gROOT -> SetStyle("Plain");

  TLegend* legend1 = new TLegend(0.3, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.35]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_PrmVtxReso_detsim, "SKDETSIM-based MC", "L");
  legend1 -> AddEntry(g_onesigma_DETSIM, TString::Format("#kern[-0.]{Resolution(SKDETSIM): %.1f cm}", OneSigmaReso_detsim), "L");
  legend1 -> AddEntry(h1_PrmVtxReso_skg4, "SKG4-based MC", "L");
  legend1 -> AddEntry(g_onesigma_G4, TString::Format("#kern[-0.]{Resolution(SKG4): %.1f cm}", OneSigmaReso_skg4), "L");
  legend1->SetFillColor(0);


#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_PrmVtxReso_detsim -> SetTitleOffset(1.2, "Y");
  h1_PrmVtxReso_detsim -> SetTitleOffset(1.1, "X");
  h1_PrmVtxReso_detsim -> GetXaxis()->SetTitleSize(0.04);
  h1_PrmVtxReso_detsim -> GetYaxis()->SetTitleSize(0.04);
  h1_PrmVtxReso_detsim -> Draw("SAME");
  h1_PrmVtxReso_skg4   -> Draw("SAME");
  g_onesigma_G4        -> Draw("SAME");
  g_onesigma_DETSIM    -> Draw("SAME");
  c1 -> RedrawAxis();
  legend1->Draw();
#endif


  TF1* f1_sigmaX = new TF1("f1_sigmaX", "[0] * exp( -(x - [1])*(x - [1]) / (2*[2]*[2]) )", -20, 20);
  f1_sigmaX -> SetParameter(0, 1000);
  f1_sigmaX -> SetParameter(1, 10);
  f1_sigmaX -> SetParameter(2, 20);
  f1_sigmaX -> SetLineColor(kAzure-8);
  f1_sigmaX -> SetLineWidth(3);
  f1_sigmaX -> SetNpx(10000);

  TF1* f1_sigmaY = new TF1("f1_sigmaY", "[0] * exp( -(x - [1])*(x - [1]) / (2*[2]*[2]) )", -20, 20);
  f1_sigmaY -> SetParameter(0, 1000);
  f1_sigmaY -> SetParameter(1, 10);
  f1_sigmaY -> SetParameter(2, 20);
  f1_sigmaY -> SetLineColor(kAzure-8);
  f1_sigmaY -> SetLineWidth(3);
  f1_sigmaY -> SetNpx(10000);

  TF1* f1_sigmaZ = new TF1("f1_sigmaZ", "[0] * exp( -(x - [1])*(x - [1]) / (2*[2]*[2]) )", -20, 20);
  f1_sigmaZ -> SetParameter(0, 1000);
  f1_sigmaZ -> SetParameter(1, 10);
  f1_sigmaZ -> SetParameter(2, 20);
  f1_sigmaZ -> SetLineColor(kAzure-8);
  f1_sigmaZ -> SetLineWidth(3);
  f1_sigmaZ -> SetNpx(10000);
  
#if 0
  TCanvas* cX = new TCanvas("cX", "cX", 900, 700);
  cX -> SetGrid();
  h1_PrmVtxResoX -> GetXaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoX -> GetYaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoX -> Draw("");
  h1_PrmVtxResoX -> Fit(f1_sigmaX, "r");
  f1_sigmaX -> Draw("SAME");

  float RMSX   = h1_PrmVtxResoX->GetRMS();
  float SigmaX = f1_sigmaX->GetParameter(2);
  TLegend* legendX = new TLegend(0.55, 0.65, 0.89, 0.89);
  legendX -> SetTextSize(0.04);
  legendX -> AddEntry(h1_PrmVtxResoX, TString::Format("#kern[-0.]{RMS = %.1f cm}", RMSX), "L");
  legendX -> AddEntry(f1_sigmaX, TString::Format("#kern[-0.]{#sigma = %.1f cm}", SigmaX), "L");
  legendX -> AddEntry()
  legendX->SetFillColor(0);
  legendX -> Draw();

  
  TCanvas* cY = new TCanvas("cY", "cY", 900, 700);
  cY -> SetGrid();
  h1_PrmVtxResoY -> GetXaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoY -> GetYaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoY -> Draw("");
  h1_PrmVtxResoY -> Fit(f1_sigmaY, "r");
  f1_sigmaY -> Draw("SAME");

  float RMSY   = h1_PrmVtxResoY->GetRMS();
  float SigmaY = f1_sigmaY->GetParameter(2);
  TLegend* legendY = new TLegend(0.55, 0.65, 0.89, 0.89);
  legendY -> SetTextSize(0.04);
  legendY -> AddEntry(h1_PrmVtxResoY, TString::Format("#kern[-0.]{RMS = %.1f cm}", RMSY), "L");
  legendY -> AddEntry(f1_sigmaY, TString::Format("#kern[-0.]{#sigma = %.1f cm}", SigmaY), "L");
  legendY -> AddEntry()
  legendY->SetFillColor(0);
  legendY -> Draw();


  TCanvas* cZ = new TCanvas("cZ", "cZ", 900, 700);
  cZ -> SetGrid();
  h1_PrmVtxResoZ -> GetXaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoZ -> GetYaxis()->SetTitleSize(0.045);
  h1_PrmVtxResoZ -> Draw("");
  h1_PrmVtxResoZ -> Fit(f1_sigmaZ, "r");
  f1_sigmaZ -> Draw("SAME");
  
  float RMSZ   = h1_PrmVtxResoZ->GetRMS();
  float SigmaZ = f1_sigmaZ->GetParameter(2);
  TLegend* legendZ = new TLegend(0.55, 0.65, 0.89, 0.89);
  legendZ -> SetTextSize(0.04);
  legendZ -> AddEntry(h1_PrmVtxResoZ, TString::Format("#kern[-0.]{RMS = %.1f cm}", RMSZ), "L");
  legendZ -> AddEntry(f1_sigmaZ, TString::Format("#kern[-0.]{#sigma = %.1f cm}", SigmaZ), "L");
  legendZ -> AddEntry()
  legendZ->SetFillColor(0);
  legendZ -> Draw();
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h2_PrmVtxReso -> GetXaxis()->SetTitleSize(0.04);
  h2_PrmVtxReso -> GetYaxis()->SetTitleSize(0.04);
  h2_PrmVtxReso -> Draw("COLZ");
#endif

#if 0
  TCanvas* c3 = new TCanvas("c3", "c3", 900, 700);
  c3 -> SetGrid();
  h2_True_x_Reco -> GetXaxis()->SetTitleSize(0.04);
  h2_True_x_Reco -> GetYaxis()->SetTitleSize(0.04);
  h2_True_x_Reco -> Draw("COLZ");
#endif



}