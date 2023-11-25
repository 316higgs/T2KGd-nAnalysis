
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define NNAPPLY 0


void NHits() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }

  TH1F* h1_NHits_Nlike[SAMPLES][NTAGLABEL];
  TH1F* h1_NHits_Elike[SAMPLES][NTAGLABEL];
  TH1F* h1_FitT_Nlike[SAMPLES][NTAGLABEL];
  TH1F* h1_FitT_Elike[SAMPLES][NTAGLABEL];
  //TH1F* h1_mergeNHits_Nlike = new TH1F("h1_mergeNHits_Nlike", "", 25, 0, 400);
  //TH1F* h1_mergeNHits_Elike = new TH1F("h1_mergeNHits_Elike", "", 25, 0, 400);
  THStack* hs_NHits_Nlike = new THStack("hs_NHits_Nlike", "");
  THStack* hs_NHits_Elike = new THStack("hs_NHits_Elike", "");
  THStack* hs_FitT_Nlike  = new THStack("hs_FitT_Nlike", "");
  THStack* hs_FitT_Elike  = new THStack("hs_FitT_Elike", "");
  TString DirName        = "DecayeBox/";
  TString HistName_NHits = "h1_NHits";
  TString HistName_FitT  = "h1_FitT";
  bool usesample[SAMPLES] = {1, 1, 1, 1, 1, 1};
  for (int isample=0; isample<SAMPLES; isample++) {
    for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      h1_NHits_Nlike[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Nlike"+TString::Format("_mode%d", ilabel));
      h1_NHits_Elike[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Elike"+TString::Format("_mode%d", ilabel));
      SetMCHistColor_Label(ilabel, h1_NHits_Nlike[isample][ilabel]);
      SetMCHistColor_Label(ilabel, h1_NHits_Elike[isample][ilabel]);

      //  normalization
      //ApplyNorm(h1_NHits_Nlike[isample][ilabel], isample);
      //ApplyNorm(h1_NHits_Elike[isample][ilabel], isample);
    }

    //h1_NHits_Nlike[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Nlike");
    //h1_NHits_Elike[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Elike");

    //  normalization
    //ApplyNorm(h1_NHits_Nlike[isample], isample);
    //ApplyNorm(h1_NHits_Elike[isample], isample);
  }


  for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
    for (int isample=0; isample<SAMPLES; isample++) {
      //h1_mergeNHits_Nlike -> Add(h1_NHits_Nlike[isample]);
      //h1_mergeNHits_Elike -> Add(h1_NHits_Elike[isample]);
      hs_NHits_Nlike -> Add(h1_NHits_Nlike[isample][ilabel]);
      hs_NHits_Elike -> Add(h1_NHits_Elike[isample][ilabel]);
    }
  }
  /*
  h1_mergeNHits_Elike -> SetStats(0);
  h1_mergeNHits_Elike -> SetLineWidth(2);
  h1_mergeNHits_Elike -> SetLineColor(DecayEColor);
  //h1_mergeNHits_Elike -> SetFillStyle(3357);
  //h1_mergeNHits_Elike -> SetFillColor(DecayEColor);

  h1_mergeNHits_Nlike -> SetStats(0);
  h1_mergeNHits_Nlike -> SetLineWidth(2);
  h1_mergeNHits_Nlike -> SetLineColor(NeutronColor);
  //h1_mergeNHits_Nlike -> SetFillStyle(3357);
  //h1_mergeNHits_Nlike -> SetFillColor(NeutronColor);
  */


  TFile* fin_data   = new TFile(fdata);
  TString HistData_NHits = "h1_AllNHits";
  TH1F* h1_NHits_Nlike_data = (TH1F*)fin_data->Get(DirName+HistData_NHits+"_Nlike");
  TH1F* h1_NHits_Elike_data = (TH1F*)fin_data->Get(DirName+HistData_NHits+"_Elike");

  h1_NHits_Nlike_data -> SetMarkerStyle(20);
  h1_NHits_Nlike_data -> SetMarkerSize(1.2);
  h1_NHits_Nlike_data -> SetMarkerColor(DataColor);
  h1_NHits_Nlike_data -> SetLineColor(DataColor);
  h1_NHits_Nlike_data -> SetLineWidth(1.5);

  h1_NHits_Elike_data -> SetMarkerStyle(20);
  h1_NHits_Elike_data -> SetMarkerSize(1.2);
  h1_NHits_Elike_data -> SetMarkerColor(DataColor);
  h1_NHits_Elike_data -> SetLineColor(DataColor);
  h1_NHits_Elike_data -> SetLineWidth(1.5);



#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  c1 -> SetLogy();
  hs_N50 -> SetMinimum(1e-5);
  hs_N50 -> SetMaximum(1e7);
  hs_N50 -> Draw();
  hs_N50 ->GetYaxis()->SetTitleSize(0.038);
  hs_N50 ->GetYaxis()->SetTitleOffset(1.3);
  hs_N50 ->GetYaxis()->SetLabelSize(0.036);
  hs_N50 ->GetXaxis()->SetTitle("N50");
  hs_N50 ->GetYaxis()->SetTitle("Number of Candidates");
  hs_N50 -> Draw();
  h1_N50_data -> Draw("SAME E P");

  TLegend* legend1 = new TLegend(0.3, 0.5, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.27]{FCFV applied (pre-NN)}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.29]{FCFV, NN output>0.7}","");
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FCFV, NN output>0.7 && not e-like}","");
  legend1 -> AddEntry(h1_N50[0][0], "Acc. noise", "F");
  legend1 -> AddEntry(h1_N50[0][1], "Decay-e", "F");
  legend1 -> AddEntry(h1_N50[0][2], "H-n signal", "F");
  legend1 -> AddEntry(h1_N50[0][3], "Gd-n signal", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  //hs_NHits_Nlike -> SetMinimum(1e-4);
  //hs_NHits_Nlike -> SetMaximum(40);
  hs_NHits_Nlike -> Draw();
  hs_NHits_Nlike ->GetYaxis()->SetTitleSize(0.038);
  hs_NHits_Nlike ->GetYaxis()->SetTitleOffset(1.3);
  hs_NHits_Nlike ->GetYaxis()->SetLabelSize(0.036);
  hs_NHits_Nlike ->GetXaxis()->SetTitle("NHits");
  hs_NHits_Nlike ->GetYaxis()->SetTitle("Number of Candidates");
  hs_NHits_Nlike -> Draw();
  h1_NHits_Nlike_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.5, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output>0.7}","");
  legend2 -> AddEntry(hs_NHits_Nlike, "MC neutron-like", "F");
  legend2 -> AddEntry(h1_NHits_Nlike_data, "Data neutron-like", "LP");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif

#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  //hs_NHits_Nlike -> SetMinimum(1e-4);
  //hs_NHits_Nlike -> SetMaximum(40);
  h1_mergeNHits_Nlike -> Draw();
  h1_mergeNHits_Nlike ->GetYaxis()->SetTitleSize(0.038);
  h1_mergeNHits_Nlike ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergeNHits_Nlike ->GetYaxis()->SetLabelSize(0.036);
  h1_mergeNHits_Nlike ->GetXaxis()->SetTitle("NHits");
  h1_mergeNHits_Nlike ->GetYaxis()->SetTitle("Number of Candidates");
  h1_mergeNHits_Nlike -> Draw();
  h1_mergeNHits_Elike -> Draw("SAME");
  h1_NHits_Elike_data -> Draw("SAME E P");
  h1_NHits_Nlike_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.5, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  //legend2 -> AddEntry((TObject*)0,"#kern[-0.27]{FCFV applied (pre-NN)}","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{FCFV, NN output>0.7}","");
  //legend2 -> AddEntry((TObject*)0,"#kern[-0.25]{FCFV, NN output>0.7 && not e-like}","");
  legend2 -> AddEntry(h1_mergeNHits_Nlike, "MC neutron-like", "F");
  legend2 -> AddEntry(h1_mergeNHits_Elike, "MC decay electron-like", "F");
  legend2 -> AddEntry(h1_NHits_Nlike_data, "Data neutron-like", "LP");
  legend2 -> AddEntry(h1_NHits_Elike_data, "Data decay electron-like", "LP");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif
  
}

