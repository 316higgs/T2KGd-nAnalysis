
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define NNAPPLY 0


void CompareNHits_var() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }


  TH1F* h1_NHits[SAMPLES][NTAGLABEL];
  TH1F* h1_NHits_mvar[SAMPLES][NTAGLABEL];
  TH1F* h1_NHits_pvar[SAMPLES][NTAGLABEL];
  TH1F* h1_mergeNHits      = new TH1F("h1_mergeNHits", "", 100, 0, 100);
  TH1F* h1_mergeNHits_mvar = new TH1F("h1_mergeNHits_mvar", "", 100, 0, 100);
  TH1F* h1_mergeNHits_pvar = new TH1F("h1_mergeNHits_pvar", "", 100, 0, 100);
  TString DirName  = "DecayeBox/";
  TString HistName = "h1_NHits";
  for (int isample=0; isample<SAMPLES; isample++) {
    for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      h1_NHits[isample][ilabel]      = (TH1F*)fin_MC[isample]->Get(DirName+HistName+"_nominal_"+TString::Format("mode%d", ilabel));
      h1_NHits_mvar[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName+"_mvar_"+TString::Format("mode%d", ilabel));
      h1_NHits_pvar[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName+"_pvar_"+TString::Format("mode%d", ilabel));
  
      //  normalization
      ApplyNorm(h1_NHits[isample][ilabel], isample);
      ApplyNorm(h1_NHits_mvar[isample][ilabel], isample);
      ApplyNorm(h1_NHits_pvar[isample][ilabel], isample);

      h1_mergeNHits      -> Add(h1_NHits[isample][ilabel]);
      h1_mergeNHits_mvar -> Add(h1_NHits_mvar[isample][ilabel]);
      h1_mergeNHits_pvar -> Add(h1_NHits_pvar[isample][ilabel]);
    }
  }

  h1_mergeNHits -> SetLineWidth(3);
  h1_mergeNHits -> SetLineColor(kSpring+4);
  h1_mergeNHits -> SetFillColor(kSpring+2);
  h1_mergeNHits -> SetFillStyle(3356);
  h1_mergeNHits -> SetStats(0);

  h1_mergeNHits_mvar -> SetLineWidth(3);
  h1_mergeNHits_mvar -> SetLineColor(kAzure+2);
  h1_mergeNHits_mvar -> SetStats(0);

  h1_mergeNHits_pvar -> SetLineWidth(3);
  h1_mergeNHits_pvar -> SetLineColor(kRed-3);
  h1_mergeNHits_pvar -> SetStats(0);


  TLatex* text1 = new TLatex(0.63, 0.95, "FHC 1R#mu, post-NN");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);

  TLatex* text2 = new TLatex(0.75, 0.91, "dt < 20 #mus");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.045);

  TLegend* legend1 = new TLegend(0.55, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry(h1_mergeNHits, "Nominal MC", "F");
  legend1 -> AddEntry(h1_mergeNHits_mvar, "-2% NHits", "L");
  legend1 -> AddEntry(h1_mergeNHits_pvar, "+2% NHits", "L");
  legend1->SetFillColor(0);


  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  //h1_mergeNHits -> Fit(f1_NHits_middle, "r");
  //h1_mergeNHits -> SetMinimum(1e-4);
  //h1_mergeNHits -> SetMaximum(1e4);
  h1_mergeNHits ->GetYaxis()->SetTitleSize(0.038);
  h1_mergeNHits ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergeNHits ->GetYaxis()->SetLabelSize(0.036);
  h1_mergeNHits ->GetXaxis()->SetTitle("NHits");
  h1_mergeNHits ->GetYaxis()->SetTitle("Number of Candidates");
  h1_mergeNHits -> Draw("");
  h1_mergeNHits_mvar -> Draw("SAME");
  h1_mergeNHits_pvar -> Draw("SAME");

  text1 -> Draw();
  text2 -> Draw();
  legend1->Draw();




  /*TFile* fin_data   = new TFile(fdata);
  TH1F* h1_NHits_postNN_data = (TH1F*)fin_data->Get(DirName+HistName_NHits+StageName);
  TH1F* h1_NHits_lt20us_data = (TH1F*)fin_data->Get(DirName+HistName_NHits+StageName+"_lt20us");
  TH1F* h1_NHits_gt20us_data = (TH1F*)fin_data->Get(DirName+HistName_NHits+StageName+"_gt20us");

  h1_NHits_postNN_data -> SetMarkerStyle(20);
  h1_NHits_postNN_data -> SetMarkerSize(1.2);
  h1_NHits_postNN_data -> SetMarkerColor(kBlack);
  h1_NHits_postNN_data -> SetLineColor(kBlack);
  h1_NHits_postNN_data -> SetLineWidth(1.5);

  h1_NHits_lt20us_data -> SetMarkerStyle(20);
  h1_NHits_lt20us_data -> SetMarkerSize(1.2);
  h1_NHits_lt20us_data -> SetMarkerColor(kBlack);
  h1_NHits_lt20us_data -> SetLineColor(kBlack);
  h1_NHits_lt20us_data -> SetLineWidth(1.5);

  h1_NHits_gt20us_data -> SetMarkerStyle(20);
  h1_NHits_gt20us_data -> SetMarkerSize(1.2);
  h1_NHits_gt20us_data -> SetMarkerColor(kBlack);
  h1_NHits_gt20us_data -> SetLineColor(kBlack);
  h1_NHits_gt20us_data -> SetLineWidth(1.5);


  float NHits_mc             = 0.;
  float NHits_lt20us_mc      = 0.;
  float NHits_lt20us_lt50_mc = 0.;
  float NHits_lt20us_gt50_mc = 0.;
  float NHits_gt20us_mc      = 0.;

  float NHits_data             = 0.;
  float NHits_lt20us_data      = 0.;
  float NHits_lt20us_lt50_data = 0.;
  float NHits_lt20us_gt50_data = 0.;
  float NHits_gt20us_data      = 0.;
  for (int ibin=0; ibin<42; ibin++) {
    NHits_mc        += h1_mergeNHits->GetBinContent(ibin+1);
    NHits_lt20us_mc += h1_mergeNHits_lt20us->GetBinContent(ibin+1);
    NHits_gt20us_mc += h1_mergeNHits_gt20us->GetBinContent(ibin+1);
    if (ibin<5) NHits_lt20us_lt50_mc += h1_mergeNHits_lt20us->GetBinContent(ibin+1);
    else NHits_lt20us_gt50_mc += h1_mergeNHits_lt20us->GetBinContent(ibin+1);

    NHits_data        += h1_NHits_postNN_data->GetBinContent(ibin+1);
    NHits_lt20us_data += h1_NHits_lt20us_data->GetBinContent(ibin+1);
    NHits_gt20us_data += h1_NHits_gt20us_data->GetBinContent(ibin+1);
    if (ibin<5) NHits_lt20us_lt50_data += h1_NHits_lt20us_data->GetBinContent(ibin+1);
    else NHits_lt20us_gt50_data += h1_NHits_lt20us_data->GetBinContent(ibin+1);
  }
  std::cout << "#candidates(MC)  : " << NHits_mc << std::endl;
  std::cout << "  dt < 20 us     : " << NHits_lt20us_mc << std::endl;
  std::cout << "                   " << NHits_lt20us_lt50_mc << "(NHits<50) + " << NHits_lt20us_gt50_mc << "(NHits>50)" << std::endl;
  std::cout << "  dt > 20 us     : " << NHits_gt20us_mc << std::endl;
  std::cout << "#candidates(data): " << NHits_data << std::endl;
  std::cout << "  dt < 20 us     : " << NHits_lt20us_data << std::endl;
  std::cout << "                   " << NHits_lt20us_lt50_data << "(NHits<50) + " << NHits_lt20us_gt50_data << "(NHits>50)" << std::endl;
  std::cout << "  dt > 20 us     : " << NHits_gt20us_data << std::endl;*/


  // area normalizaion
#if 0
  Double_t tot_mergeNHits_lt20us = h1_mergeNHits_lt20us->Integral();
  TH1F* h1_mergeNHits_lt20us_wgt = (TH1F*)h1_mergeNHits_lt20us->Clone();
  h1_mergeNHits_lt20us_wgt -> Scale(1./tot_mergeNHits_lt20us);

  Double_t tot_NHits_lt20us_data = h1_NHits_lt20us_data->Integral();
  TH1F* h1_NHits_lt20us_wgt_data = (TH1F*)h1_NHits_lt20us_data->Clone();
  h1_NHits_lt20us_wgt_data -> Sumw2();
  h1_NHits_lt20us_wgt_data -> Scale(1./tot_NHits_lt20us_data);
#endif


  //////  Data / MC  //////
  /*TH1F* h1_wgt_lt20us = new TH1F("h1_wgt_lt20us", "", 42, 0, 420);
  h1_wgt_lt20us = (TH1F*)h1_NHits_lt20us_wgt_data->Clone();
  h1_wgt_lt20us -> Divide(h1_mergeNHits_lt20us_wgt);

  Double_t wgt[5] = {0.};
  float NHits_var_mc = 0.;
  for (int ibin=0; ibin<5; ibin++) {
    std::cout << h1_wgt_lt20us->GetBinContent(ibin+1) << std::endl;
    wgt[ibin] = h1_wgt_lt20us->GetBinContent(ibin+1);
    NHits_var_mc += h1_mergeNHits_lt20us->GetBinContent(ibin+1)*wgt[ibin];
  }
  std::cout << "#candidates(var): " << NHits_var_mc << std::endl;*/



#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  //h1_mergeNHits -> Fit(f1_NHits_middle, "r");
  //h1_mergeNHits -> SetMinimum(1e-4);
  h1_mergeNHits -> SetMaximum(1e4);
  h1_mergeNHits ->GetYaxis()->SetTitleSize(0.038);
  h1_mergeNHits ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergeNHits ->GetYaxis()->SetLabelSize(0.036);
  h1_mergeNHits ->GetXaxis()->SetTitle("NHits");
  h1_mergeNHits ->GetYaxis()->SetTitle("Area Normalized");
  h1_mergeNHits -> Draw("");
  h1_NHits_postNN_data -> Draw("SAME E P");

  /*TLegend* legend1 = new TLegend(0.55, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1->AddEntry((TObject*)0,"#kern[-0.32]{FCFV post-NN}","");
  legend1 -> AddEntry(h1_NHits[0][3], "Gd-n signal", "F");
  legend1 -> AddEntry(h1_NHits[0][2], "H-n signal", "F");
  legend1 -> AddEntry(h1_NHits[0][1], "Decay-e", "F");
  legend1 -> AddEntry(h1_NHits[0][0], "Acc. noise", "F");
  legend1->SetFillColor(0);
  legend1->Draw();*/
#endif
  

#if 0

  TLatex* text1 = new TLatex(0.68, 0.95, "FCFV, post-NN");
  text1 -> SetNDC(1);
  text1 -> SetTextSize(0.045);

  TLatex* text2 = new TLatex(0.75, 0.91, "dt < 20 #mus");
  text2 -> SetNDC(1);
  text2 -> SetTextSize(0.045);

  TLatex* text3 = new TLatex(0.75, 0.91, "dt > 20 #mus");
  text3 -> SetNDC(1);
  text3 -> SetTextSize(0.045);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  c1 -> SetLogy();
  h1_mergeNHits_lt20us -> SetMaximum(1e4);
  h1_mergeNHits_lt20us ->GetYaxis()->SetTitleSize(0.038);
  h1_mergeNHits_lt20us ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergeNHits_lt20us ->GetYaxis()->SetLabelSize(0.036);
  h1_mergeNHits_lt20us ->GetXaxis()->SetTitle("NHits");
  h1_mergeNHits_lt20us ->GetYaxis()->SetTitle("Area Normalized");
  h1_mergeNHits_lt20us -> Draw("");
  h1_NHits_lt20us_data -> Draw("SAME E P");
  text1 -> Draw();
  text2 -> Draw();


  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  h1_mergeNHits_gt20us -> SetMaximum(1e4);
  h1_mergeNHits_gt20us ->GetYaxis()->SetTitleSize(0.038);
  h1_mergeNHits_gt20us ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergeNHits_gt20us ->GetYaxis()->SetLabelSize(0.036);
  h1_mergeNHits_gt20us ->GetXaxis()->SetTitle("NHits");
  h1_mergeNHits_gt20us ->GetYaxis()->SetTitle("Area Normalized");
  h1_mergeNHits_gt20us -> Draw("");
  h1_NHits_gt20us_data -> Draw("SAME E P");
  text1 -> Draw();
  text3 -> Draw();
#endif



}

