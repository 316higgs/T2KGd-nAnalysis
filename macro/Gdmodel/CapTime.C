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


void CapTime(bool beammode) {

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
  /*TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");*/

  TFile* fin_numu_ggarnet      = new TFile("../../output/fhc/fhc.numu_x_numu.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuesig_ggarnet    = new TFile("../../output/fhc/fhc.numu_x_nue.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_numubar_ggarnet   = new TFile("../../output/fhc/fhc.numubar_x_numubar.ggarnet.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig_ggarnet = new TFile("../../output/fhc/fhc.numubar_x_nuebar.ggarnet.bonsaikeras_ToF.root");
  //TFile* fin_nuebkg_ggarnet    = new TFile("../../output/fhc/fhc.nue_x_nue.ggarnet.bonsaikeras_ToF.root");
  //TFile* fin_nuebarbkg_ggarnet = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.ggarnet.bonsaikeras_ToF.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


#if 1
  TString histname    = "NTagAnalysis/h1_TrueNCapTime";
#endif

  TH1F* h1_CapTime_numu      = (TH1F*)fin_numu->Get(histname);
  TH1F* h1_CapTime_nuesig    = (TH1F*)fin_nuesig->Get(histname);
  TH1F* h1_CapTime_numubar   = (TH1F*)fin_numubar->Get(histname);
  TH1F* h1_CapTime_nuebarsig = (TH1F*)fin_nuebarsig->Get(histname);
  //TH1F* h1_CapTime_nuebkg    = (TH1F*)fin_nuebkg->Get(histname);
  //TH1F* h1_CapTime_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(histname);


  TH1F* h1_CapTime_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get(histname);
  TH1F* h1_CapTime_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get(histname);
  TH1F* h1_CapTime_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get(histname);
  TH1F* h1_CapTime_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get(histname);
  //TH1F* h1_CapTime_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get(histname);
  //TH1F* h1_CapTime_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get(histname);



  bool mode[6] = {1, 1, 1, 1, 0, 0};

  TH1F* h1_CapTime = new TH1F("h1_CapTime", "", 107, 0, 535);
  if (mode[5]) h1_CapTime -> Add(h1_CapTime_nuebarbkg);
  if (mode[4]) h1_CapTime -> Add(h1_CapTime_nuebkg);
  if (mode[3]) h1_CapTime -> Add(h1_CapTime_nuebarsig);
  if (mode[2]) h1_CapTime -> Add(h1_CapTime_numubar);
  if (mode[1]) h1_CapTime -> Add(h1_CapTime_nuesig);
  if (mode[0]) h1_CapTime -> Add(h1_CapTime_numu);
  h1_CapTime -> SetLineColor(kViolet-7);
  h1_CapTime ->GetYaxis()->SetTitleSize(0.045);
  h1_CapTime ->GetYaxis()->SetTitleOffset(0.8);
  h1_CapTime ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_CapTime->GetYaxis())->SetMaxDigits(3);
  h1_CapTime -> SetYTitle("Number of Neutrino Events");
  h1_CapTime ->GetXaxis()->SetLabelSize(0.035);
  h1_CapTime -> SetXTitle("True Capture Time [#mus]");
  h1_CapTime -> SetLineWidth(3);
  h1_CapTime -> SetStats(0);


  TH1F* h1_CapTime_ggarnet = new TH1F("h1_CapTime_ggarnet", "", 107, 0, 535);
  if (mode[5]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_nuebarbkg);
  if (mode[4]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_nuebkg);
  if (mode[3]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_nuebarsig);
  if (mode[2]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_numubar);
  if (mode[1]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_nuesig);
  if (mode[0]) h1_CapTime_ggarnet -> Add(h1_CapTime_ggarnet_numu);
  h1_CapTime_ggarnet -> SetLineColor(kRed-6);
  //h1_CapTime_ggarnet -> SetXTitle("Number of True Neutron Captures");
  h1_CapTime_ggarnet -> SetYTitle("Number of Neutrino Events");
  h1_CapTime_ggarnet -> SetLineWidth(3);
  h1_CapTime_ggarnet -> SetStats(0);


  TLegend* legend1 = new TLegend(0.4, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_CapTime, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(h1_CapTime_ggarnet, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //h1_CapTime -> SetMaximum(10000);
  h1_CapTime -> Draw("SAME");
  h1_CapTime_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();
#endif

#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetLogy();
  c1 -> SetGrid();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->SetGridy();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  h1_CapTime -> SetMinimum(0.01);
  h1_CapTime -> SetMaximum(10000);
  h1_CapTime -> Draw("SAME");
  h1_CapTime_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();

  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  gROOT -> SetStyle("Plain");
  TH1F *h1_CapTimeRatio = (TH1F*)h1_CapTime_ggarnet->Clone("h1_CapTimeRatio");
  h1_CapTimeRatio->SetLineColor(kViolet-7);
  h1_CapTimeRatio->SetMinimum(0.7);  // Define Y ..
  h1_CapTimeRatio->SetMaximum(1.25); // .. range
  h1_CapTimeRatio ->GetYaxis()->SetTitleSize(0.16);
  h1_CapTimeRatio ->GetYaxis()->SetTitleOffset(0.28);
  h1_CapTimeRatio ->GetYaxis()->SetLabelSize(0.12);
  h1_CapTimeRatio ->GetYaxis()->SetTitle("Ratio  ");
  h1_CapTimeRatio ->GetXaxis()->SetTitleSize(0.16);
  h1_CapTimeRatio ->GetXaxis()->SetTitleOffset(0.8);
  h1_CapTimeRatio ->GetXaxis()->SetLabelSize(0.13);
  //h1_CapTimeRatio -> GetXaxis()->SetTitle("Number of True Neutron Captures");
  h1_CapTimeRatio -> GetXaxis()->SetTitle("Number of Tagged Neutrons");

  h1_CapTimeRatio->Sumw2();
  h1_CapTimeRatio->SetStats(0);      // No statistics on lower plot
  h1_CapTimeRatio->Divide(h1_CapTime);
  h1_CapTimeRatio->SetMarkerStyle(21);
  h1_CapTimeRatio->Draw("histo");       // Draw the ratio plot
#endif

}

