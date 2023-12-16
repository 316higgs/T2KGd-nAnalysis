
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17

#define NNAPPLY 0


void CompareNHits_label() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }


  TH1F* h1_NHits_Nlike[SAMPLES];
  TH1F* h1_NHits_Elike[SAMPLES];
  TH1F* h1_mergeNHits_Nlike = new TH1F("h1_mergeNHits_Nlike", "", 40, 0, 400);
  TH1F* h1_mergeNHits_Elike = new TH1F("h1_mergeNHits_Elike", "", 40, 0, 400);
  TString DirName        = "DecayeBox/";
  TString HistName_NHits = "h1_AllNHits";
  float TaggedNeutrons = 0;
  for (int isample=0; isample<SAMPLES; isample++) {
    h1_NHits_Nlike[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Nlike");
    h1_NHits_Elike[isample] = (TH1F*)fin_MC[isample]->Get(DirName+HistName_NHits+"_Elike");

    std::cout << "[ " << isample << " ] NHits: " << h1_NHits_Nlike[isample]->GetEntries() << "+" << h1_NHits_Elike[isample]->GetEntries() << std::endl;
    TaggedNeutrons += h1_NHits_Nlike[isample]->GetEntries()+h1_NHits_Elike[isample]->GetEntries();
    //std::cout << "[ " << isample << " ] NHits: " << h1_NHits_Nlike[isample]->Integral() << "+" << h1_NHits_Elike[isample]->Integral() << std::endl;
    //TaggedNeutrons += h1_NHits_Nlike[isample]->Integral()+h1_NHits_Elike[isample]->Integral();

    //  normalization
    ApplyNorm(h1_NHits_Nlike[isample], isample);
    ApplyNorm(h1_NHits_Elike[isample], isample);

    h1_mergeNHits_Nlike -> Add(h1_NHits_Nlike[isample]);
    h1_mergeNHits_Elike -> Add(h1_NHits_Elike[isample]);
  }
  std::cout << "Total: " << TaggedNeutrons << std::endl;
  std::cout << "  N-like: " << h1_mergeNHits_Nlike->GetEntries() << std::endl;
  std::cout << "  E-like: " << h1_mergeNHits_Elike->GetEntries() << std::endl;

  h1_mergeNHits_Nlike -> SetLineColor(kSpring+4);
  h1_mergeNHits_Nlike -> SetFillColor(kSpring+4);
  h1_mergeNHits_Elike -> SetLineColor(kYellow-6);
  h1_mergeNHits_Elike -> SetFillColor(kYellow-6);

  THStack* hs_NHits = new THStack("hs_NHits", "");
  hs_NHits -> Add(h1_mergeNHits_Elike);
  hs_NHits -> Add(h1_mergeNHits_Nlike);


  TFile* fin_data   = new TFile(fdata);
  TString DirName        = "DecayeBox/";
  TString HistData_NHits = "h1_AllNHits";
  TString Stage_postNN   = "_postNN";
  TH1F* h1_NHits_postNN_data = (TH1F*)fin_data->Get(DirName+HistData_NHits+Stage_postNN);

  h1_NHits_postNN_data -> SetMarkerStyle(20);
  h1_NHits_postNN_data -> SetMarkerSize(1.2);
  h1_NHits_postNN_data -> SetMarkerColor(kBlack);
  h1_NHits_postNN_data -> SetLineColor(kBlack);
  h1_NHits_postNN_data -> SetLineWidth(1.5);



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


  TLegend* legend1 = new TLegend(0.55, 0.65, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1->AddEntry((TObject*)0,"#kern[-0.32]{FCFV post-NN}","");
  legend1 -> AddEntry(h1_mergeNHits_Nlike, "n-like", "F");
  legend1 -> AddEntry(h1_mergeNHits_Elike, "decay e-like", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif
  
}

