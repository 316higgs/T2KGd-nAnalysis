
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void CutSelection_NHits() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    std::cout << "Input: " << fname << std::endl;
    //fin_MC[isample] = new TFile(fname);
    //fin_MC[isample] = new TFile("../../output/fhc/fhc."+OscMode[isample]+".preNN.newGdMC_bonsai_keras_prompt_vertex.root");
    //fin_MC[isample] = new TFile("../../output/fhc/fhc."+OscMode[isample]+".preNN.newGdMC_prompt_keras.root");
    fin_MC[isample] = new TFile("../../output/fhc/fhc."+OscMode[isample]+".newGdMC.promptkeras.root");
  }

  TH1F* h1_NHits[SAMPLES][NTAGLABEL];
  THStack* hs_NHits = new THStack("hs_NHits", "");
  TString DirName  = "DecayeBox/";
  TString HistName = "h1_NHits_CutBase6";
  //TString DirName   = "NNInputVariables/";
  //TString HistName  = "h1_NNvar";
  TString LabelName = "_AccNoise";
  for (int isample=0; isample<SAMPLES; isample++) {
  	for (int ilabel=0; ilabel<NTAGLABEL; ilabel++) {
      if (ilabel==0) LabelName = "_AccNoise";
      if (ilabel==1) LabelName = "_Decaye";
      if (ilabel==2) LabelName = "_H";
      if (ilabel==3) LabelName = "_Gd";
      TString thishist = DirName+HistName+TString::Format("_mode%d", ilabel);
      std::cout << "Get hist: " << thishist << std::endl;
      h1_NHits[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(thishist);
  	  //h1_NHits[isample][ilabel] = (TH1F*)fin_MC[isample]->Get(DirName+HistName+LabelName+"_type0");
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

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  //c1 -> SetLogy();
  //hs_NHits -> SetMinimum(1e-5);
  hs_NHits -> SetMaximum(8);
  hs_NHits -> Draw();
  hs_NHits ->GetYaxis()->SetTitleSize(0.038);
  hs_NHits ->GetYaxis()->SetTitleOffset(1.3);
  hs_NHits ->GetYaxis()->SetLabelSize(0.036);
  hs_NHits ->GetXaxis()->SetTitle("NHits");
  hs_NHits ->GetYaxis()->SetTitle("Number of Candidates");
  hs_NHits -> Draw();

  TLegend* legend1 = new TLegend(0.55, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R#mu sample}","");
  legend1 -> AddEntry(h1_NHits[0][0], "Acc. noise", "F");
  legend1 -> AddEntry(h1_NHits[0][1], "Decay-e", "F");
  legend1 -> AddEntry(h1_NHits[0][2], "H-n signal", "F");
  legend1 -> AddEntry(h1_NHits[0][3], "Gd-n signal", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif

}