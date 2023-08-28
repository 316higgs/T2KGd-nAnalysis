#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC

#define NDCYE 2


void CompareDecaye(bool beammode) {

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
  //Gd MC
  TFile* fin_numu_gd      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig_gd    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar_gd   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig_gd = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg_gd    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg_gd = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");

  //Pure water MC
  TFile* fin_numu_pw      = new TFile("../../output/fhc/fhc.numu_x_numu.water.root");
  TFile* fin_nuesig_pw    = new TFile("../../output/fhc/fhc.numu_x_nue.water.root");
  TFile* fin_numubar_pw   = new TFile("../../output/fhc/fhc.numubar_x_numubar.water.root");
  TFile* fin_nuebarsig_pw = new TFile("../../output/fhc/fhc.numubar_x_nuebar.water.root");
  TFile* fin_nuebkg_pw    = new TFile("../../output/fhc/fhc.nue_x_nue.water.root");
  TFile* fin_nuebarbkg_pw = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.water.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif


  TH1F* h1_numu_gd[4];
  TH1F* h1_nuesig_gd[4];
  TH1F* h1_numubar_gd[4];
  TH1F* h1_nuebarsig_gd[4];
  TH1F* h1_nuebkg_gd[4];
  TH1F* h1_nuebarbkg_gd[4];

  TH1F* h1_numu_boxgd[4];
  TH1F* h1_nuesig_boxgd[4];
  TH1F* h1_numubar_boxgd[4];
  TH1F* h1_nuebarsig_boxgd[4];
  TH1F* h1_nuebkg_boxgd[4];
  TH1F* h1_nuebarbkg_boxgd[4];

  TH1F* h1_numu_pw[4];
  TH1F* h1_nuesig_pw[4];
  TH1F* h1_numubar_pw[4];
  TH1F* h1_nuebarsig_pw[4];
  TH1F* h1_nuebkg_pw[4];
  TH1F* h1_nuebarbkg_pw[4];


  for (int i=0; i<4; i++) {
    h1_numu_boxgd[i]      = (TH1F*)fin_numu_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_numu_gd[i]         = (TH1F*)fin_numu_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy
    h1_nuesig_boxgd[i]    = (TH1F*)fin_nuesig_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_nuesig_gd[i]       = (TH1F*)fin_nuesig_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy
    h1_numubar_boxgd[i]   = (TH1F*)fin_numubar_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_numubar_gd[i]      = (TH1F*)fin_numubar_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy
    h1_nuebarsig_boxgd[i] = (TH1F*)fin_nuebarsig_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_nuebarsig_gd[i]    = (TH1F*)fin_nuebarsig_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy
    h1_nuebkg_boxgd[i]    = (TH1F*)fin_nuebkg_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_nuebkg_gd[i]       = (TH1F*)fin_nuebkg_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy
    h1_nuebarbkg_boxgd[i] = (TH1F*)fin_nuebarbkg_gd->Get(TString::Format("Gd1RmuonSelection/h1_Decaye_mode%d", i));  //Floor cut
    h1_nuebarbkg_gd[i]    = (TH1F*)fin_nuebarbkg_gd->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));    //Legacy

    h1_numu_pw[i]      = (TH1F*)fin_numu_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
    h1_nuesig_pw[i]    = (TH1F*)fin_nuesig_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
    h1_numubar_pw[i]   = (TH1F*)fin_numubar_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
    h1_nuebarsig_pw[i] = (TH1F*)fin_nuebarsig_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
    h1_nuebkg_pw[i]    = (TH1F*)fin_nuebkg_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
    h1_nuebarbkg_pw[i] = (TH1F*)fin_nuebarbkg_pw->Get(TString::Format("DecayeBox/h1_TaggedDecaye_mode%d", i));  //Legacy
  }


  ////  merged histograms  ////
  TH1F* h1_DcyE_gd[4];
  TH1F* h1_DcyE_boxgd[4];

  TH1F* h1_DcyE_pw[4];

  for (int i=0; i<4; i++) {
    h1_DcyE_gd[i] = new TH1F(TString::Format("h1_DcyE_gd_mode%d", i), "", 6, 0, 6);
    h1_DcyE_gd[i] -> Add(h1_numu_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_nuesig_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_numubar_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_nuebarsig_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_nuebkg_gd[i], 1.);
    h1_DcyE_gd[i] -> Add(h1_nuebarbkg_gd[i], 1.);

    h1_DcyE_gd[i] -> SetLineColor(kOrange+0);
    h1_DcyE_gd[i] -> SetLineStyle(7);
    h1_DcyE_gd[i] -> SetLineWidth(3);
    h1_DcyE_gd[i] -> SetStats(0);

    h1_DcyE_boxgd[i] = new TH1F(TString::Format("h1_DcyE_boxgd_mode%d", i), "", 6, 0, 6);
    h1_DcyE_boxgd[i] -> Add(h1_numu_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_nuesig_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_numubar_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_nuebarsig_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_nuebkg_boxgd[i], 1.);
    h1_DcyE_boxgd[i] -> Add(h1_nuebarbkg_boxgd[i], 1.);

    h1_DcyE_boxgd[i] -> SetLineColor(kOrange+0);
    h1_DcyE_boxgd[i] -> SetLineWidth(3);

    h1_DcyE_pw[i] = new TH1F(TString::Format("h1_DcyE_pw_mode%d", i), "", 6, 0, 6);
    h1_DcyE_pw[i] -> Add(h1_numu_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_nuesig_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_numubar_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_nuebarsig_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_nuebkg_pw[i], 1.);
    h1_DcyE_pw[i] -> Add(h1_nuebarbkg_pw[i], 1.);

    h1_DcyE_pw[i] -> SetLineColor(kAzure+1);
    h1_DcyE_pw[i] -> SetLineWidth(3);
    h1_DcyE_pw[i] -> SetStats(0);
    h1_DcyE_pw[i] -> SetXTitle("Number of Reconstructed Decay-e");
    h1_DcyE_pw[i] -> SetYTitle("Area Normalized");
    h1_DcyE_pw[i] ->GetYaxis()->SetTitleSize(0.045);
    h1_DcyE_pw[i] ->GetXaxis()->SetTitleSize(0.045);
    h1_DcyE_pw[i] ->GetYaxis()->SetTitleOffset(1.2);
    h1_DcyE_pw[i] ->GetYaxis()->SetLabelSize(0.036);
    h1_DcyE_pw[i] ->GetXaxis()->SetLabelSize(0.045);

    for (int j=0; j<6; j++) {
      h1_DcyE_gd[i]    -> GetXaxis()->SetBinLabel(j+1, TString::Format("%d", j));
      h1_DcyE_boxgd[i] -> GetXaxis()->SetBinLabel(j+1, TString::Format("%d", j));
      h1_DcyE_pw[i]    -> GetXaxis()->SetBinLabel(j+1, TString::Format("%d", j));
    }
    
  }


  TH1F* h1_DcyE_All_gd = new TH1F("h1_DcyE_All_gd", "", 6, 0, 6);
  h1_DcyE_All_gd -> Add(h1_DcyE_gd[0]);
  h1_DcyE_All_gd -> Add(h1_DcyE_gd[1]);
  h1_DcyE_All_gd -> Add(h1_DcyE_gd[2]);
  h1_DcyE_All_gd -> Add(h1_DcyE_gd[3]);
  h1_DcyE_All_gd -> SetLineColor(kOrange+0);
  h1_DcyE_All_gd -> SetLineStyle(7);
  h1_DcyE_All_gd -> SetLineWidth(3);
  Double_t tot_DcyE_All_gd = h1_DcyE_All_gd->Integral();
  h1_DcyE_All_gd -> Scale(1./tot_DcyE_All_gd);

  TH1F* h1_DcyE_All_boxgd = new TH1F("h1_DcyE_All_boxgd", "", 6, 0, 6);
  h1_DcyE_All_boxgd -> Add(h1_DcyE_boxgd[0]);
  h1_DcyE_All_boxgd -> Add(h1_DcyE_boxgd[1]);
  h1_DcyE_All_boxgd -> Add(h1_DcyE_boxgd[2]);
  h1_DcyE_All_boxgd -> Add(h1_DcyE_boxgd[3]);
  h1_DcyE_All_boxgd -> SetLineColor(kOrange+0);
  h1_DcyE_All_boxgd -> SetLineWidth(3);
  Double_t tot_DcyE_All_boxgd = h1_DcyE_All_boxgd->Integral();
  h1_DcyE_All_boxgd -> Scale(1./tot_DcyE_All_boxgd);

  TH1F* h1_DcyE_All_pw = new TH1F("h1_DcyE_All_pw", "", 6, 0, 6);
  h1_DcyE_All_pw -> Add(h1_DcyE_pw[0]);
  h1_DcyE_All_pw -> Add(h1_DcyE_pw[1]);
  h1_DcyE_All_pw -> Add(h1_DcyE_pw[2]);
  h1_DcyE_All_pw -> Add(h1_DcyE_pw[3]);
  h1_DcyE_All_pw -> SetLineColor(kAzure+1);
  h1_DcyE_All_pw -> SetLineWidth(3);
  Double_t tot_DcyE_All_pw = h1_DcyE_All_pw->Integral();
  h1_DcyE_All_pw -> Scale(1./tot_DcyE_All_pw);
  h1_DcyE_All_pw -> SetStats(0);
  h1_DcyE_All_pw ->GetXaxis()->SetTitle("Number of Reconstructed Decay-e");
  h1_DcyE_All_pw ->GetYaxis()->SetTitle("Area Normalized");
  h1_DcyE_All_pw ->GetYaxis()->SetTitleSize(0.045);
  h1_DcyE_All_pw ->GetXaxis()->SetTitleSize(0.045);
  h1_DcyE_All_pw ->GetYaxis()->SetTitleOffset(1.2);
  h1_DcyE_All_pw ->GetYaxis()->SetLabelSize(0.036);
  h1_DcyE_All_pw ->GetXaxis()->SetLabelSize(0.045);
  for (int j=0; j<6; j++) h1_DcyE_All_pw -> GetXaxis()->SetBinLabel(j+1, TString::Format("%d", j));
  


  TH1F* h1_DcyE_QElike_gd = new TH1F("h1_DcyE_QElike_gd", "", 6, 0, 6);
  h1_DcyE_QElike_gd -> Add(h1_DcyE_gd[0]);
  h1_DcyE_QElike_gd -> Add(h1_DcyE_gd[1]);
  h1_DcyE_QElike_gd -> SetLineColor(kOrange+0);
  h1_DcyE_QElike_gd -> SetLineStyle(7);
  h1_DcyE_QElike_gd -> SetLineWidth(3);
  Double_t tot_DcyE_QElike_gd = h1_DcyE_QElike_gd->Integral();
  h1_DcyE_QElike_gd -> Scale(1./tot_DcyE_QElike_gd);

  TH1F* h1_DcyE_QElike_boxgd = new TH1F("h1_DcyE_QElike_boxgd", "", 6, 0, 6);
  h1_DcyE_QElike_boxgd -> Add(h1_DcyE_boxgd[0]);
  h1_DcyE_QElike_boxgd -> Add(h1_DcyE_boxgd[1]);
  h1_DcyE_QElike_boxgd -> SetLineColor(kOrange+0);
  h1_DcyE_QElike_boxgd -> SetLineWidth(3);
  Double_t tot_DcyE_QElike_boxgd = h1_DcyE_QElike_boxgd->Integral();
  h1_DcyE_QElike_boxgd -> Scale(1./tot_DcyE_QElike_boxgd);

  TH1F* h1_DcyE_QElike_pw = new TH1F("h1_DcyE_QElike_pw", "", 6, 0, 6);
  h1_DcyE_QElike_pw -> Add(h1_DcyE_pw[0]);
  h1_DcyE_QElike_pw -> Add(h1_DcyE_pw[1]);
  h1_DcyE_QElike_pw -> SetLineColor(kAzure+1);
  h1_DcyE_QElike_pw -> SetLineWidth(3);
  Double_t tot_DcyE_QElike_pw = h1_DcyE_QElike_pw->Integral();
  h1_DcyE_QElike_pw -> Scale(1./tot_DcyE_QElike_pw);
  h1_DcyE_QElike_pw -> SetStats(0);
  h1_DcyE_QElike_pw ->GetXaxis()->SetTitle("Number of Reconstructed Decay-e");
  h1_DcyE_QElike_pw ->GetYaxis()->SetTitle("Area Normalized");
  h1_DcyE_QElike_pw ->GetYaxis()->SetTitleSize(0.045);
  h1_DcyE_QElike_pw ->GetXaxis()->SetTitleSize(0.045);
  h1_DcyE_QElike_pw ->GetYaxis()->SetTitleOffset(1.2);
  h1_DcyE_QElike_pw ->GetYaxis()->SetLabelSize(0.036);
  h1_DcyE_QElike_pw ->GetXaxis()->SetLabelSize(0.045);
  for (int j=0; j<6; j++) h1_DcyE_QElike_pw -> GetXaxis()->SetBinLabel(j+1, TString::Format("%d", j));

  for (int i=2; i<4; i++) {
    Double_t tot_DcyE_gd = h1_DcyE_gd[i]->Integral();
    h1_DcyE_gd[i] -> Scale(1./tot_DcyE_gd);

    Double_t tot_DcyE_boxgd = h1_DcyE_boxgd[i]->Integral();
    h1_DcyE_boxgd[i] -> Scale(1./tot_DcyE_boxgd);

    Double_t tot_DcyE_pw = h1_DcyE_pw[i]->Integral();
    h1_DcyE_pw[i] -> Scale(1./tot_DcyE_pw);
  }


  float y[2] = {0., 200.};
  float xC[2] = {NDCYE, NDCYE};
  TGraph* g_Cut = new TGraph(2, xC, y);
  g_Cut -> SetLineWidth(3);
  g_Cut -> SetLineColor(kViolet-8);
  g_Cut -> SetLineStyle(7);
  

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1400, 1200);
  c1 -> Divide(2, 2);
  for (int i=0; i<4; i++) {
    c1 -> cd(i+1) -> SetGrid();

    /*h1_DcyE_gd[i] ->GetXaxis()->SetTitle("Number of Reconstructed Decay-e");
    h1_DcyE_gd[i] ->GetYaxis()->SetTitle("Area Normalized");
    h1_DcyE_gd[i] ->GetYaxis()->SetTitleSize(0.05);
    h1_DcyE_gd[i] ->GetXaxis()->SetTitleSize(0.055);
    h1_DcyE_gd[i] ->GetYaxis()->SetTitleOffset(1.4);
    h1_DcyE_gd[i] ->GetYaxis()->SetLabelSize(0.036);
    h1_DcyE_gd[i] ->GetXaxis()->SetLabelSize(0.05);*/

    if (i>1) {
      h1_DcyE_pw[i]    -> Draw();
      h1_DcyE_gd[i]    -> Draw("SAME");
      h1_DcyE_boxgd[i] -> Draw("SAME");
      g_Cut            -> Draw("SAME");
    }
    else if (i==0) {
      h1_DcyE_All_pw    -> Draw();
      h1_DcyE_All_gd    -> Draw("SAME");
      h1_DcyE_All_boxgd -> Draw("SAME");
      g_Cut             -> Draw("SAME");
    }
    else if (i==1) {
      h1_DcyE_QElike_pw    -> Draw();
      h1_DcyE_QElike_gd    -> Draw("SAME");
      h1_DcyE_QElike_boxgd -> Draw("SAME");
      g_Cut                -> Draw("SAME");
    }

    TLegend* legend1 = new TLegend(0.45, 0.5, 0.89, 0.89);
    legend1 -> SetTextSize(0.045);
    if (i==0) legend1->AddEntry((TObject*)0,"#kern[-0.4]{All interactions}","");
    if (i==1) legend1->AddEntry((TObject*)0,"#kern[-0.4]{CC 1p1h+2p2h}","");
    if (i==2) legend1->AddEntry((TObject*)0,"#kern[-0.7]{CC other}","");
    if (i==3) legend1->AddEntry((TObject*)0,"#kern[-2.0]{NC}","");
    legend1->AddEntry((TObject*)0,"#kern[-0.4]{C1-C4 applied}","");
    legend1 -> AddEntry(h1_DcyE_pw[i], "Pure water", "L");
    legend1 -> AddEntry(h1_DcyE_gd[i], "Gd: #sub-event", "L");
    legend1 -> AddEntry(h1_DcyE_boxgd[i], "Gd: floor cut", "L");
    legend1->SetFillColor(0);
    legend1->Draw() ;
  }
#endif

}
