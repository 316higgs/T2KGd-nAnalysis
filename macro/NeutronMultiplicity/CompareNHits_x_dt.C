
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define NNAPPLY 0


void CompareNHits_x_dt() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }


  TH1F* h1_NHits_gtr[SAMPLES];
  TH1F* h1_NHits_lss[SAMPLES];
  TH1F* h1_FitT_gtr[SAMPLES];
  TH1F* h1_FitT_lss[SAMPLES];
  TH1F* h1_merge_NHits_gtr = new TH1F("h1_merge_NHits_gtr", "", 40, 0, 400);
  TH1F* h1_merge_NHits_lss = new TH1F("h1_merge_NHits_lss", "", 40, 0, 400);
  TH1F* h1_merge_FitT_gtr  = new TH1F("h1_merge_FitT_gtr", "", 40, 0, 200);
  TH1F* h1_merge_FitT_lss  = new TH1F("h1_merge_FitT_lss", "", 40, 0, 200);
  TString DirName        = "DecayeBox/";
  TString HistName_NHits = "h1_NHits";
  TString HistName_FitT  = "h1_FitT";
  TString gtrName        = "_gtr";
  TString lssName        = "_lss";
  for (int isample=0; isample<SAMPLES; isample++) {
    h1_NHits_gtr[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+gtrName);
    h1_NHits_lss[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+lssName);
    h1_FitT_gtr[isample]  = (TH1F*)fin_MC[isample]->Get(DirName+HistName_FitT+gtrName);
    h1_FitT_lss[isample]  = (TH1F*)fin_MC[isample]->Get(DirName+HistName_FitT+lssName);
    ApplyNorm(h1_NHits_gtr[isample], isample);
    ApplyNorm(h1_NHits_lss[isample], isample);
    ApplyNorm(h1_FitT_gtr[isample], isample);
    ApplyNorm(h1_FitT_lss[isample], isample);
  }

  for (int isample=0; isample<SAMPLES; isample++) {
    h1_merge_NHits_gtr -> Add(h1_NHits_gtr[isample]);
    h1_merge_NHits_lss -> Add(h1_NHits_lss[isample]);
    h1_merge_FitT_gtr  -> Add(h1_FitT_gtr[isample]);
    h1_merge_FitT_lss  -> Add(h1_FitT_lss[isample]);
  }
  h1_merge_NHits_gtr -> SetLineColor(kViolet+2);
  h1_merge_NHits_lss -> SetLineColor(kViolet+2);
  h1_merge_FitT_gtr  -> SetLineColor(kViolet+2);
  h1_merge_FitT_lss  -> SetLineColor(kViolet+2);
  h1_merge_NHits_gtr -> SetLineWidth(3);
  h1_merge_NHits_lss -> SetLineWidth(3);
  h1_merge_FitT_gtr  -> SetLineWidth(3);
  h1_merge_FitT_lss  -> SetLineWidth(3);
  h1_merge_NHits_gtr -> SetStats(0);
  h1_merge_NHits_lss -> SetStats(0);
  h1_merge_FitT_gtr  -> SetStats(0);
  h1_merge_FitT_lss  -> SetStats(0);


  TFile* fin_data   = new TFile(fdata);
  TH1F* h1_NHits_gtr_data = (TH1F*)fin_data->Get(DirName+HistName_NHits+gtrName);
  TH1F* h1_NHits_lss_data = (TH1F*)fin_data->Get(DirName+HistName_NHits+lssName);
  TH1F* h1_FitT_gtr_data  = (TH1F*)fin_data->Get(DirName+HistName_FitT+gtrName);
  TH1F* h1_FitT_lss_data  = (TH1F*)fin_data->Get(DirName+HistName_FitT+lssName);

  h1_NHits_gtr_data -> SetStats(0);
  h1_NHits_gtr_data -> SetMarkerStyle(20);
  h1_NHits_gtr_data -> SetMarkerSize(1.2);
  h1_NHits_gtr_data -> SetMarkerColor(kBlack);
  h1_NHits_gtr_data -> SetLineColor(kBlack);
  h1_NHits_gtr_data -> SetLineWidth(1.5);

  h1_NHits_lss_data -> SetMarkerStyle(20);
  h1_NHits_lss_data -> SetMarkerSize(1.2);
  h1_NHits_lss_data -> SetMarkerColor(kBlack);
  h1_NHits_lss_data -> SetLineColor(kBlack);
  h1_NHits_lss_data -> SetLineWidth(1.5);

  h1_FitT_gtr_data -> SetMarkerStyle(20);
  h1_FitT_gtr_data -> SetMarkerSize(1.2);
  h1_FitT_gtr_data -> SetMarkerColor(kBlack);
  h1_FitT_gtr_data -> SetLineColor(kBlack);
  h1_FitT_gtr_data -> SetLineWidth(1.5);

  h1_FitT_lss_data -> SetMarkerStyle(20);
  h1_FitT_lss_data -> SetMarkerSize(1.2);
  h1_FitT_lss_data -> SetMarkerColor(kBlack);
  h1_FitT_lss_data -> SetLineColor(kBlack);
  h1_FitT_lss_data -> SetLineWidth(1.5);



#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  h1_merge_NHits_gtr -> SetMinimum(1e-4);
  h1_merge_NHits_gtr -> SetMaximum(1e8);
  h1_merge_NHits_gtr -> Draw();
  h1_merge_NHits_gtr ->GetYaxis()->SetTitleSize(0.038);
  h1_merge_NHits_gtr ->GetYaxis()->SetTitleOffset(1.3);
  h1_merge_NHits_gtr ->GetYaxis()->SetLabelSize(0.036);
  h1_merge_NHits_gtr ->GetXaxis()->SetTitle("NHits");
  h1_merge_NHits_gtr ->GetYaxis()->SetTitle("Number of Candidates");
  h1_merge_NHits_gtr -> Draw();
  h1_NHits_gtr_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.3, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output > 0.7 && dt > 20 #mu s}","");
  legend2 -> AddEntry(h1_merge_NHits_gtr, "MC", "F");
  legend2 -> AddEntry(h1_NHits_gtr_data, "Data", "P");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  h1_merge_NHits_lss -> SetMinimum(1e-4);
  h1_merge_NHits_lss -> SetMaximum(1e8);
  h1_merge_NHits_lss -> Draw();
  h1_merge_NHits_lss ->GetYaxis()->SetTitleSize(0.038);
  h1_merge_NHits_lss ->GetYaxis()->SetTitleOffset(1.3);
  h1_merge_NHits_lss ->GetYaxis()->SetLabelSize(0.036);
  h1_merge_NHits_lss ->GetXaxis()->SetTitle("NHits");
  h1_merge_NHits_lss ->GetYaxis()->SetTitle("Number of Candidates");
  h1_merge_NHits_lss -> Draw();
  h1_NHits_lss_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.3, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output > 0.7 && dt < 20 #mu s}","");
  legend2 -> AddEntry(h1_merge_NHits_lss, "MC", "F");
  legend2 -> AddEntry(h1_NHits_lss_data, "Data", "P");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  h1_merge_FitT_gtr -> SetMinimum(1e-4);
  h1_merge_FitT_gtr -> SetMaximum(1e8);
  h1_merge_FitT_gtr -> Draw();
  h1_merge_FitT_gtr ->GetYaxis()->SetTitleSize(0.038);
  h1_merge_FitT_gtr ->GetYaxis()->SetTitleOffset(1.3);
  h1_merge_FitT_gtr ->GetYaxis()->SetLabelSize(0.036);
  h1_merge_FitT_gtr ->GetXaxis()->SetTitle("FitT [#mu s]");
  h1_merge_FitT_gtr ->GetYaxis()->SetTitle("Number of Candidates");
  h1_merge_FitT_gtr -> Draw();
  h1_FitT_gtr_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.3, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output > 0.7 && NHits > 50}","");
  legend2 -> AddEntry(h1_merge_FitT_gtr, "MC", "F");
  legend2 -> AddEntry(h1_NHits_gtr_data, "Data", "P");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  h1_merge_FitT_lss -> SetMinimum(1e-4);
  h1_merge_FitT_lss -> SetMaximum(1e8);
  h1_merge_FitT_lss -> Draw();
  h1_merge_FitT_lss ->GetYaxis()->SetTitleSize(0.038);
  h1_merge_FitT_lss ->GetYaxis()->SetTitleOffset(1.3);
  h1_merge_FitT_lss ->GetYaxis()->SetLabelSize(0.036);
  h1_merge_FitT_lss ->GetXaxis()->SetTitle("FitT [#mu s]");
  h1_merge_FitT_lss ->GetYaxis()->SetTitle("Number of Candidates");
  h1_merge_FitT_lss -> Draw();
  h1_NHits_lss_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.3, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output > 0.7 && N50 < 50}","");
  legend2 -> AddEntry(h1_merge_FitT_lss, "MC", "F");
  legend2 -> AddEntry(h1_FitT_lss_data, "Data", "P");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif
  
}

