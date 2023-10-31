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


#if 0
  TString CCQEhistname    = "NTagAnalysis/h1_TrueNmultiplicity_mode0";
  TString CC2p2hhistname  = "NTagAnalysis/h1_TrueNmultiplicity_mode1";
  TString CCOtherhistname = "NTagAnalysis/h1_TrueNmultiplicity_mode2";
  TString NChistname      = "NTagAnalysis/h1_TrueNmultiplicity_mode3";
  TString Xtitle          = "Number of True Neutron Captures";
#endif
#if 1
  TString CCQEhistname    = "NTagAnalysis/h1_TagNmultiplicity_mode0";
  TString CC2p2hhistname  = "NTagAnalysis/h1_TagNmultiplicity_mode1";
  TString CCOtherhistname = "NTagAnalysis/h1_TagNmultiplicity_mode2";
  TString NChistname      = "NTagAnalysis/h1_TagNmultiplicity_mode3";
  TString Xtitle          = "Number of Tagged Neutrons";
#endif


  TH1F* h1_CCQE_numu    = (TH1F*)fin_numu->Get(CCQEhistname);
  TH1F* h1_CC2p2h_numu  = (TH1F*)fin_numu->Get(CC2p2hhistname);
  TH1F* h1_CCOther_numu = (TH1F*)fin_numu->Get(CCOtherhistname);
  TH1F* h1_NC_numu      = (TH1F*)fin_numu->Get(NChistname);
  h1_CCQE_numu -> SetStats(0);

  TH1F* h1_CCQE_nuesig    = (TH1F*)fin_nuesig->Get(CCQEhistname);
  TH1F* h1_CC2p2h_nuesig  = (TH1F*)fin_nuesig->Get(CC2p2hhistname);
  TH1F* h1_CCOther_nuesig = (TH1F*)fin_nuesig->Get(CCOtherhistname);
  TH1F* h1_NC_nuesig      = (TH1F*)fin_nuesig->Get(NChistname);
  h1_CCQE_nuesig -> SetStats(0);

  TH1F* h1_CCQE_numubar    = (TH1F*)fin_numubar->Get(CCQEhistname);
  TH1F* h1_CC2p2h_numubar  = (TH1F*)fin_numubar->Get(CC2p2hhistname);
  TH1F* h1_CCOther_numubar = (TH1F*)fin_numubar->Get(CCOtherhistname);
  TH1F* h1_NC_numubar      = (TH1F*)fin_numubar->Get(NChistname);
  h1_CCQE_numubar -> SetStats(0);

  TH1F* h1_CCQE_nuebarsig     = (TH1F*)fin_nuebarsig->Get(CCQEhistname);
  TH1F* h1_CC2p2h_nuebarsig   = (TH1F*)fin_nuebarsig->Get(CC2p2hhistname);
  TH1F* h1_CCOther_nuebarsig  = (TH1F*)fin_nuebarsig->Get(CCOtherhistname);
  TH1F* h1_NC_nuebarsig       = (TH1F*)fin_nuebarsig->Get(NChistname);
  h1_CCQE_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_nuebkg    = (TH1F*)fin_nuebkg->Get(CCQEhistname);
  TH1F* h1_CC2p2h_nuebkg  = (TH1F*)fin_nuebkg->Get(CC2p2hhistname);
  TH1F* h1_CCOther_nuebkg = (TH1F*)fin_nuebkg->Get(CCOtherhistname);
  TH1F* h1_NC_nuebkg      = (TH1F*)fin_nuebkg->Get(NChistname);
  h1_CCQE_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get(CCQEhistname);
  TH1F* h1_CC2p2h_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get(CC2p2hhistname);
  TH1F* h1_CCOther_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(CCOtherhistname);
  TH1F* h1_NC_nuebarbkg      = (TH1F*)fin_nuebarbkg->Get(NChistname);
  h1_CCQE_nuebarbkg -> SetStats(0);


  TH1F* h1_CCQE_ggarnet_numu    = (TH1F*)fin_numu_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_numu  = (TH1F*)fin_numu_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_numu = (TH1F*)fin_numu_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_numu      = (TH1F*)fin_numu_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_numu -> SetStats(0);

  TH1F* h1_CCQE_ggarnet_nuesig    = (TH1F*)fin_nuesig_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_nuesig  = (TH1F*)fin_nuesig_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_nuesig = (TH1F*)fin_nuesig_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_nuesig      = (TH1F*)fin_nuesig_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_nuesig -> SetStats(0);

  TH1F* h1_CCQE_ggarnet_numubar    = (TH1F*)fin_numubar_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_numubar  = (TH1F*)fin_numubar_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_numubar = (TH1F*)fin_numubar_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_numubar      = (TH1F*)fin_numubar_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_numubar -> SetStats(0);

  TH1F* h1_CCQE_ggarnet_nuebarsig     = (TH1F*)fin_nuebarsig_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_nuebarsig   = (TH1F*)fin_nuebarsig_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_nuebarsig  = (TH1F*)fin_nuebarsig_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_nuebarsig       = (TH1F*)fin_nuebarsig_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_nuebarsig -> SetStats(0);

  TH1F* h1_CCQE_ggarnet_nuebkg    = (TH1F*)fin_nuebkg_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_nuebkg  = (TH1F*)fin_nuebkg_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_nuebkg = (TH1F*)fin_nuebkg_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_nuebkg      = (TH1F*)fin_nuebkg_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_nuebkg -> SetStats(0);

  TH1F* h1_CCQE_ggarnet_nuebarbkg    = (TH1F*)fin_nuebarbkg_ggarnet->Get(CCQEhistname);
  TH1F* h1_CC2p2h_ggarnet_nuebarbkg  = (TH1F*)fin_nuebarbkg_ggarnet->Get(CC2p2hhistname);
  TH1F* h1_CCOther_ggarnet_nuebarbkg = (TH1F*)fin_nuebarbkg_ggarnet->Get(CCOtherhistname);
  TH1F* h1_NC_ggarnet_nuebarbkg      = (TH1F*)fin_nuebarbkg_ggarnet->Get(NChistname);
  h1_CCQE_ggarnet_nuebarbkg -> SetStats(0);




  bool mode[6] = {1, 1, 1, 1, 1, 1};

  TH1F* h1_NeutronMult = new TH1F("h1_NeutronMult", "", 10, 0, 10);
  if (mode[5]) h1_NeutronMult -> Add(h1_NC_nuebarbkg);
  if (mode[4]) h1_NeutronMult -> Add(h1_NC_nuebkg);
  if (mode[3]) h1_NeutronMult -> Add(h1_NC_nuebarsig);
  if (mode[2]) h1_NeutronMult -> Add(h1_NC_numubar);
  if (mode[1]) h1_NeutronMult -> Add(h1_NC_nuesig);
  if (mode[0]) h1_NeutronMult -> Add(h1_NC_numu);

  if (mode[5]) h1_NeutronMult -> Add(h1_CCOther_nuebarbkg);
  if (mode[5]) h1_NeutronMult -> Add(h1_CC2p2h_nuebarbkg);
  if (mode[5]) h1_NeutronMult -> Add(h1_CCQE_nuebarbkg);
  if (mode[4]) h1_NeutronMult -> Add(h1_CCOther_nuebkg);
  if (mode[4]) h1_NeutronMult -> Add(h1_CC2p2h_nuebkg);
  if (mode[4]) h1_NeutronMult -> Add(h1_CCQE_nuebkg);
  if (mode[3]) h1_NeutronMult -> Add(h1_CCOther_nuebarsig);
  if (mode[3]) h1_NeutronMult -> Add(h1_CC2p2h_nuebarsig);
  if (mode[3]) h1_NeutronMult -> Add(h1_CCQE_nuebarsig);
  if (mode[1]) h1_NeutronMult -> Add(h1_CCOther_nuesig);
  if (mode[1]) h1_NeutronMult -> Add(h1_CC2p2h_nuesig);
  if (mode[1]) h1_NeutronMult -> Add(h1_CCQE_nuesig);

  if (mode[2]) h1_NeutronMult -> Add(h1_CCOther_numubar);
  if (mode[0]) h1_NeutronMult -> Add(h1_CCOther_numu);
  if (mode[2]) h1_NeutronMult -> Add(h1_CC2p2h_numubar);
  if (mode[0]) h1_NeutronMult -> Add(h1_CC2p2h_numu);
  if (mode[2]) h1_NeutronMult -> Add(h1_CCQE_numubar);
  if (mode[0]) h1_NeutronMult -> Add(h1_CCQE_numu);
  h1_NeutronMult -> SetLineColor(kViolet-7);
  h1_NeutronMult ->GetYaxis()->SetTitleSize(0.045);
  h1_NeutronMult ->GetYaxis()->SetTitleOffset(0.8);
  h1_NeutronMult ->GetYaxis()->SetLabelSize(0.04);
  ((TGaxis*)h1_NeutronMult->GetYaxis())->SetMaxDigits(3);
  h1_NeutronMult -> SetYTitle("Number of Neutrino Events");
  h1_NeutronMult ->GetXaxis()->SetLabelSize(0.05);
  h1_NeutronMult -> SetXTitle(Xtitle);
  for (int ibin=0; ibin<10; ibin++) h1_NeutronMult->GetXaxis()->SetBinLabel(ibin+1, TString::Format("%d", ibin));
  h1_NeutronMult -> SetLineWidth(3);
  h1_NeutronMult -> SetStats(0);


  TH1F* h1_NeutronMult_ggarnet = new TH1F("h1_NeutronMult_ggarnet", "", 10, 0, 10);
  if (mode[5]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_nuebarbkg);
  if (mode[4]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_nuebkg);
  if (mode[3]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_nuebarsig);
  if (mode[2]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_numubar);
  if (mode[1]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_nuesig);
  if (mode[0]) h1_NeutronMult_ggarnet -> Add(h1_NC_ggarnet_numu);

  if (mode[5]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_nuebarbkg);
  if (mode[5]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_nuebarbkg);
  if (mode[5]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_nuebarbkg);
  if (mode[4]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_nuebkg);
  if (mode[4]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_nuebkg);
  if (mode[4]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_nuebkg);
  if (mode[3]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_nuebarsig);
  if (mode[3]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_nuebarsig);
  if (mode[3]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_nuebarsig);
  if (mode[1]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_nuesig);
  if (mode[1]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_nuesig);
  if (mode[1]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_nuesig);

  if (mode[2]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_numubar);
  if (mode[0]) h1_NeutronMult_ggarnet -> Add(h1_CCOther_ggarnet_numu);
  if (mode[2]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_numubar);
  if (mode[0]) h1_NeutronMult_ggarnet -> Add(h1_CC2p2h_ggarnet_numu);
  if (mode[2]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_numubar);
  if (mode[0]) h1_NeutronMult_ggarnet -> Add(h1_CCQE_ggarnet_numu);
  h1_NeutronMult_ggarnet -> SetLineColor(kRed-6);
  //h1_NeutronMult_ggarnet -> SetXTitle("Number of True Neutron Captures");
  h1_NeutronMult_ggarnet -> SetYTitle("Number of Neutrino Events");
  h1_NeutronMult_ggarnet -> SetLineWidth(3);
  h1_NeutronMult_ggarnet -> SetStats(0);



  TLegend* legend1 = new TLegend(0.4, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_NeutronMult, "ANNRI_Gd-based MC", "L");
  legend1 -> AddEntry(h1_NeutronMult_ggarnet, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);


  gROOT -> SetStyle("Plain");

#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_NeutronMult -> SetMaximum(10000);
  h1_NeutronMult -> Draw("SAME");
  h1_NeutronMult_ggarnet -> Draw("SAME");
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
  h1_NeutronMult -> SetMinimum(0.01);
  h1_NeutronMult -> SetMaximum(10000);
  h1_NeutronMult -> Draw("SAME");
  h1_NeutronMult_ggarnet -> Draw("SAME");
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
  TH1F *h1_NeutronMultRatio = (TH1F*)h1_NeutronMult_ggarnet->Clone("h1_NeutronMultRatio");
  h1_NeutronMultRatio->SetLineColor(kViolet-7);
  h1_NeutronMultRatio->SetMinimum(0.7);  // Define Y ..
  h1_NeutronMultRatio->SetMaximum(1.25); // .. range
  h1_NeutronMultRatio ->GetYaxis()->SetTitleSize(0.16);
  h1_NeutronMultRatio ->GetYaxis()->SetTitleOffset(0.28);
  h1_NeutronMultRatio ->GetYaxis()->SetLabelSize(0.12);
  h1_NeutronMultRatio ->GetYaxis()->SetTitle("Ratio  ");
  h1_NeutronMultRatio ->GetXaxis()->SetTitleSize(0.16);
  h1_NeutronMultRatio ->GetXaxis()->SetTitleOffset(0.8);
  h1_NeutronMultRatio ->GetXaxis()->SetLabelSize(0.13);
  //h1_NeutronMultRatio -> GetXaxis()->SetTitle("Number of True Neutron Captures");
  h1_NeutronMultRatio -> GetXaxis()->SetTitle("Number of Tagged Neutrons");

  h1_NeutronMultRatio->Sumw2();
  h1_NeutronMultRatio->SetStats(0);      // No statistics on lower plot
  h1_NeutronMultRatio->Divide(h1_NeutronMult);
  h1_NeutronMultRatio->SetMarkerStyle(21);
  h1_NeutronMultRatio->Draw("histo");       // Draw the ratio plot
#endif

}

