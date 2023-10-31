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


void Distance(bool beammode) {

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


  TString TrueD_histname = "DistanceViewer/h1_truedistance";
  float ThrNum = nThreshold/0.05;
  TString TagD_histname = TString::Format("DistanceViewer/h1_Tagtruedistance_thr%d", (int)ThrNum);


  TH1F* h1_TrueD_numu      = (TH1F*)fin_numu->Get(TrueD_histname);
  TH1F* h1_TrueD_nuesig    = (TH1F*)fin_nuesig->Get(TrueD_histname);
  TH1F* h1_TrueD_numubar   = (TH1F*)fin_numubar->Get(TrueD_histname);
  TH1F* h1_TrueD_nuebarsig = (TH1F*)fin_nuebarsig->Get(TrueD_histname);
  TH1F* h1_TrueD_nuebkg    = (TH1F*)fin_nuebkg->Get(TrueD_histname);
  TH1F* h1_TrueD_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(TrueD_histname);

  TH1F* h1_TrueD_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get(TrueD_histname);
  TH1F* h1_TrueD_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get(TrueD_histname);
  TH1F* h1_TrueD_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get(TrueD_histname);
  TH1F* h1_TrueD_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get(TrueD_histname);
  TH1F* h1_TrueD_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get(TrueD_histname);
  TH1F* h1_TrueD_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get(TrueD_histname);


  TH1F* h1_TagD_numu      = (TH1F*)fin_numu->Get(TagD_histname);
  TH1F* h1_TagD_nuesig    = (TH1F*)fin_nuesig->Get(TagD_histname);
  TH1F* h1_TagD_numubar   = (TH1F*)fin_numubar->Get(TagD_histname);
  TH1F* h1_TagD_nuebarsig = (TH1F*)fin_nuebarsig->Get(TagD_histname);
  TH1F* h1_TagD_nuebkg    = (TH1F*)fin_nuebkg->Get(TagD_histname);
  TH1F* h1_TagD_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(TagD_histname);

  TH1F* h1_TagD_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get(TagD_histname);
  TH1F* h1_TagD_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get(TagD_histname);
  TH1F* h1_TagD_ggarnet_numubar   = (TH1F*)fin_numubar_ggarnet->Get(TagD_histname);
  TH1F* h1_TagD_ggarnet_nuebarsig = (TH1F*)fin_nuebarsig_ggarnet->Get(TagD_histname);
  TH1F* h1_TagD_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get(TagD_histname);
  TH1F* h1_TagD_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get(TagD_histname);




  bool mode[6] = {1, 1, 1, 1, 1, 1};

  TH1F* h1_TrueD = new TH1F("h1_TrueD", "", 10, 0, 5);
  if (mode[5]) h1_TrueD -> Add(h1_TrueD_nuebarbkg);
  if (mode[4]) h1_TrueD -> Add(h1_TrueD_nuebkg);
  if (mode[3]) h1_TrueD -> Add(h1_TrueD_nuebarsig);
  if (mode[2]) h1_TrueD -> Add(h1_TrueD_numubar);
  if (mode[1]) h1_TrueD -> Add(h1_TrueD_nuesig);
  if (mode[0]) h1_TrueD -> Add(h1_TrueD_numu);
  h1_TrueD -> SetLineColor(kViolet-7);
  h1_TrueD ->GetYaxis()->SetTitleSize(0.045);
  h1_TrueD ->GetYaxis()->SetTitleOffset(0.8);
  h1_TrueD ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_TrueD->GetYaxis())->SetMaxDigits(3);
  h1_TrueD -> SetYTitle("Number of Neutrino Events");
  h1_TrueD ->GetXaxis()->SetLabelSize(0.035);
  h1_TrueD -> SetXTitle("True Travel Distance [m]");
  h1_TrueD -> SetLineWidth(3);
  h1_TrueD -> SetStats(0);


  TH1F* h1_TrueD_ggarnet = new TH1F("h1_TrueD_ggarnet", "", 10, 0, 5);
  if (mode[5]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_nuebarbkg);
  if (mode[4]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_nuebkg);
  if (mode[3]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_nuebarsig);
  if (mode[2]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_numubar);
  if (mode[1]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_nuesig);
  if (mode[0]) h1_TrueD_ggarnet -> Add(h1_TrueD_ggarnet_numu);
  h1_TrueD_ggarnet -> SetLineColor(kRed-6);
  h1_TrueD_ggarnet ->GetYaxis()->SetTitleSize(0.045);
  h1_TrueD_ggarnet ->GetYaxis()->SetTitleOffset(0.8);
  h1_TrueD_ggarnet ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_TrueD_ggarnet->GetYaxis())->SetMaxDigits(3);
  h1_TrueD_ggarnet -> SetYTitle("Number of Neutrino Events");
  h1_TrueD_ggarnet ->GetXaxis()->SetLabelSize(0.035);
  h1_TrueD_ggarnet -> SetXTitle("True Travel Distance [m]");
  h1_TrueD_ggarnet -> SetLineWidth(3);
  h1_TrueD_ggarnet -> SetStats(0);


  TH1F* h1_TagD = new TH1F("h1_TagD", "", 10, 0, 5);
  if (mode[5]) h1_TagD -> Add(h1_TagD_nuebarbkg);
  if (mode[4]) h1_TagD -> Add(h1_TagD_nuebkg);
  if (mode[3]) h1_TagD -> Add(h1_TagD_nuebarsig);
  if (mode[2]) h1_TagD -> Add(h1_TagD_numubar);
  if (mode[1]) h1_TagD -> Add(h1_TagD_nuesig);
  if (mode[0]) h1_TagD -> Add(h1_TagD_numu);
  h1_TagD -> SetLineColor(kViolet-7);
  h1_TagD ->GetYaxis()->SetTitleSize(0.045);
  h1_TagD ->GetYaxis()->SetTitleOffset(0.8);
  h1_TagD ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_TagD->GetYaxis())->SetMaxDigits(3);
  h1_TagD -> SetYTitle("Number of Neutrino Events");
  h1_TagD ->GetXaxis()->SetLabelSize(0.04);
  h1_TagD -> SetXTitle("True Travel Distance [m]");
  h1_TagD -> SetLineWidth(3);
  h1_TagD -> SetStats(0);

  Double_t tot_TagD = h1_TagD->Integral();
  //h1_TagD -> Scale(1./tot_TagD);


  TH1F* h1_TagD_ggarnet = new TH1F("h1_TagD_ggarnet", "", 10, 0, 5);
  if (mode[5]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_nuebarbkg);
  if (mode[4]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_nuebkg);
  if (mode[3]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_nuebarsig);
  if (mode[2]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_numubar);
  if (mode[1]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_nuesig);
  if (mode[0]) h1_TagD_ggarnet -> Add(h1_TagD_ggarnet_numu);
  h1_TagD_ggarnet -> SetLineColor(kRed-6);
  h1_TagD_ggarnet ->GetYaxis()->SetTitleSize(0.045);
  h1_TagD_ggarnet ->GetYaxis()->SetTitleOffset(0.8);
  h1_TagD_ggarnet ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_TagD_ggarnet->GetYaxis())->SetMaxDigits(3);
  h1_TagD_ggarnet -> SetYTitle("Number of Neutrino Events");
  h1_TagD_ggarnet ->GetXaxis()->SetLabelSize(0.035);
  h1_TagD_ggarnet -> SetXTitle("True Travel Distance [m]");
  h1_TagD_ggarnet -> SetLineWidth(3);
  h1_TagD_ggarnet -> SetStats(0);

  Double_t tot_TagD_ggarnet = h1_TagD_ggarnet->Integral();
  h1_TagD_ggarnet -> Scale(tot_TagD/tot_TagD_ggarnet);


  TLegend* legend1 = new TLegend(0.4, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{- True neutron captures}","");
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{- Tagged neutrons}","");
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{- Tagged neutrons (norm.)}","");
  legend1 -> AddEntry(h1_TrueD, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(h1_TrueD_ggarnet, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //h1_Distance -> SetMaximum(10000);
  h1_TrueD -> Draw("SAME");
  h1_TrueD_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c1 -> RedrawAxis();
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  //h1_Distance -> SetMaximum(10000);
  h1_TagD -> Draw("SAME");
  h1_TagD_ggarnet -> Draw("SAME");
  legend1 -> Draw();
  c2 -> RedrawAxis();
#endif

}

