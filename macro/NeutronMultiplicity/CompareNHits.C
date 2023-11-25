
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define NNAPPLY 0


void CompareNHits() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }


  TH1F* h1_NHits[SAMPLES][NTAGLABEL];
  THStack* hs_NHits = new THStack("hs_NHits", "");
  TString DirName        = "DecayeBox/";
  TString HistName_NHits = "h1_NHits";
  //TString StageName      = "_preNN";
  //TString StageName      = "_postNN";
  TString StageName      = "_Nlike";
  for (int isample=0; isample<SAMPLES; isample++) {
    for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      h1_NHits[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+StageName+TString::Format("_mode%d", ilabel));
      SetMCHistColor_Label(ilabel, h1_NHits[isample][ilabel]);

      //  normalization
      ApplyNorm(h1_NHits[isample][ilabel], isample);
    }
  }

  for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
    for (int isample=0; isample<SAMPLES; isample++) {
      hs_NHits -> Add(h1_NHits[isample][ilabel]);
    }
  }


  TFile* fin_data   = new TFile(fdata);
  TString DirName        = "DecayeBox/";
  TString HistData_NHits = "h1_AllNHits";
  TString Stage_preNN    = "_preNN";
  TString Stage_postNN   = "_postNN";
  TString Stage_Nlike    = "_Nlike";
  TH1F* h1_NHits_preNN_data  = (TH1F*)fin_data->Get(DirName+HistData_NHits+Stage_preNN);
  TH1F* h1_NHits_postNN_data = (TH1F*)fin_data->Get(DirName+HistData_NHits+Stage_postNN);
  TH1F* h1_NHits_Nlike_data  = (TH1F*)fin_data->Get(DirName+HistData_NHits+Stage_Nlike);

  h1_NHits_preNN_data -> SetStats(0);
  h1_NHits_preNN_data -> SetMarkerStyle(20);
  h1_NHits_preNN_data -> SetMarkerSize(1.2);
  h1_NHits_preNN_data -> SetMarkerColor(kBlack);
  h1_NHits_preNN_data -> SetLineColor(kBlack);
  h1_NHits_preNN_data -> SetLineWidth(1.5);

  h1_NHits_postNN_data -> SetMarkerStyle(20);
  h1_NHits_postNN_data -> SetMarkerSize(1.2);
  h1_NHits_postNN_data -> SetMarkerColor(kPink-5);
  h1_NHits_postNN_data -> SetLineColor(kPink-5);
  h1_NHits_postNN_data -> SetLineWidth(1.5);

  h1_NHits_Nlike_data -> SetMarkerStyle(20);
  h1_NHits_Nlike_data -> SetMarkerSize(1.2);
  h1_NHits_Nlike_data -> SetMarkerColor(kAzure-6);
  h1_NHits_Nlike_data -> SetLineColor(kAzure-6);
  h1_NHits_Nlike_data -> SetLineWidth(1.5);



#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  c2 -> SetLogy();
  hs_NHits -> SetMinimum(1e-4);
  hs_NHits -> SetMaximum(1e8);
  hs_NHits -> Draw();
  hs_NHits ->GetYaxis()->SetTitleSize(0.038);
  hs_NHits ->GetYaxis()->SetTitleOffset(1.3);
  hs_NHits ->GetYaxis()->SetLabelSize(0.036);
  hs_NHits ->GetXaxis()->SetTitle("NHits");
  hs_NHits ->GetYaxis()->SetTitle("Number of Candidates");
  hs_NHits -> Draw();
  h1_NHits_preNN_data -> Draw("SAME E P");
  h1_NHits_postNN_data -> Draw("SAME E P");
  h1_NHits_Nlike_data -> Draw("SAME E P");

  TLegend* legend2 = new TLegend(0.3, 0.6, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.65]{FCFV}","");
  legend2 -> AddEntry(h1_NHits_preNN_data, "pre-NN", "P");
  legend2 -> AddEntry(h1_NHits_postNN_data, "NN output > 0.7", "P");
  legend2 -> AddEntry(h1_NHits_Nlike_data, "NN output > 0.7 && not e-like", "P");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();
#endif
  
}

