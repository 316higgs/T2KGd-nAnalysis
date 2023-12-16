
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
  TString StageName      = "_postNN";
  //TString StageName      = "_Nlike";
  for (int isample=0; isample<SAMPLES; isample++) {
    float TaggedNeutrons = 0;
    for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      h1_NHits[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+StageName+TString::Format("_mode%d", ilabel));

      TaggedNeutrons += h1_NHits[isample][ilabel]->GetEntries();
      //TaggedNeutrons += h1_NHits[isample][ilabel]->Integral();

      SetMCHistColor_Label(ilabel, h1_NHits[isample][ilabel]);

      //  normalization
      ApplyNorm(h1_NHits[isample][ilabel], isample);
    }
    std::cout << "[ " << isample << " ] NHits: " << TaggedNeutrons << std::endl;
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
  h1_NHits_postNN_data -> SetMarkerColor(kBlack);
  h1_NHits_postNN_data -> SetLineColor(kBlack);
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
  h1_NHits_postNN_data -> Draw("SAME E P");

  TLegend* legend1 = new TLegend(0.55, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1->AddEntry((TObject*)0,"#kern[-0.32]{FCFV post-NN}","");
  legend1 -> AddEntry(h1_NHits[0][3], "Gd-n signal", "F");
  legend1 -> AddEntry(h1_NHits[0][2], "H-n signal", "F");
  legend1 -> AddEntry(h1_NHits[0][1], "Decay-e", "F");
  legend1 -> AddEntry(h1_NHits[0][0], "Acc. noise", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif
  
}

