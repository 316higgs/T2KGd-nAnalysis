
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void RecoDistance() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }

  TH1F* h1_Distance[SAMPLES][NTAGLABEL];
  THStack* hs_Distance = new THStack("hs_Distance", "");
  TString DirName  = "DistanceViewer/";
  TString HistName = "h1_RecoNCapDistance";
  bool usesample[SAMPLES] = {1, 1, 1, 1, 1, 1};
  for (int isample=0; isample<SAMPLES; isample++) {
    for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      h1_Distance[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName+TString::Format("_mode%d", ilabel));
      SetMCHistColor_Label(ilabel, h1_Distance[isample][ilabel]);

      //  normalization
      ApplyNorm(h1_Distance[isample][ilabel], isample);
    }
  }


  for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
    for (int isample=0; isample<SAMPLES; isample++) {
      hs_Distance -> Add(h1_Distance[isample][ilabel]);
    }
  }


#if 1
  TFile* fin_data  = new TFile(fdata);
  TString HistData = "h1_AllRecoNCapDistance";
  TH1F* h1_Distance_data = (TH1F*)fin_data->Get(DirName+HistData);
  TH1F* h1_NHits_Elike_data = (TH1F*)fin_data->Get(DirName+HistData);

  h1_Distance_data -> SetMarkerStyle(20);
  h1_Distance_data -> SetMarkerSize(1.2);
  h1_Distance_data -> SetMarkerColor(DataColor);
  h1_Distance_data -> SetLineColor(DataColor);
  h1_Distance_data -> SetLineWidth(1.5);
#endif

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  //c2 -> SetLogy();
  hs_Distance -> Draw();
  hs_Distance ->GetYaxis()->SetTitleSize(0.038);
  hs_Distance ->GetYaxis()->SetTitleOffset(1.3);
  hs_Distance ->GetYaxis()->SetLabelSize(0.036);
  hs_Distance ->GetXaxis()->SetTitle("Travel Distance [m]");
  hs_Distance ->GetYaxis()->SetTitle("Number of Candidates");
  hs_Distance -> Draw();
  h1_Distance_data -> Draw("SAME E P");

  TLegend* legend1 = new TLegend(0.45, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.35]{FCFV applied}","");
  legend1 -> AddEntry(h1_Distance[0][0], "Acc. noise", "F");
  legend1 -> AddEntry(h1_Distance[0][1], "Decay-e", "F");
  legend1 -> AddEntry(h1_Distance[0][2], "H-n signal", "F");
  legend1 -> AddEntry(h1_Distance[0][3], "Gd-n signal", "F");
  legend1 -> Draw("SAME E P");
#endif

}

