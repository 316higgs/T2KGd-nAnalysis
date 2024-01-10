
#include "../CommonTool/CommonTool.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void nAngle_CapN() {

  for (int isample=0; isample<SAMPLES; isample++) {
    TString fname = OutDir+BeamMode+"."+OscMode[isample]+"."+Prefix+".root";
    fin_MC[isample] = new TFile(fname);
  }

  TH1F* h1_nAngle_BefSIn[SAMPLES];
  TH1F* h1_nAngle_SIn[SAMPLES];
  TH1F* h1_mergenAngle_BefSIn = new TH1F("h1_mergenAngle_BefSIn", "", 10, -1, 1);
  TH1F* h1_mergenAngle_SIn    = new TH1F("h1_mergenAngle_SIn", "", 10, -1, 1);
  TString DirName  = "NTagAnalysis/";
  for (int isample=0; isample<SAMPLES; isample++) {
  	h1_nAngle_BefSIn[isample] = (TH1F*)fin_MC[isample]->Get(DirName+"h1_nAngle_BefSIn");
  	h1_nAngle_SIn[isample]    = (TH1F*)fin_MC[isample]->Get(DirName+"h1_nAngle_SIn");

  	//ApplyNorm(h1_nAngle_BefSIn[isample], isample);
  	//ApplyNorm(h1_nAngle_SIn[isample], isample);

  	h1_mergenAngle_BefSIn -> Add(h1_nAngle_BefSIn[isample]);
  	h1_mergenAngle_SIn    -> Add(h1_nAngle_SIn[isample]);
  }

  //std::cout << "Before SI: " << h1_mergenAngle_BefSIn->Integral() << std::endl;
  //std::cout << "After SI : " << h1_mergenAngle_SIn->Integral() << std::endl;

  h1_mergenAngle_BefSIn -> SetLineWidth(3);
  h1_mergenAngle_BefSIn -> SetLineColor(kRed-3);
  h1_mergenAngle_BefSIn -> SetFillColor(kRed-9);
  h1_mergenAngle_BefSIn -> SetFillStyle(3004);
  h1_mergenAngle_BefSIn -> SetStats(0);

  h1_mergenAngle_SIn -> SetLineWidth(3);
  h1_mergenAngle_SIn -> SetLineColor(kOrange-3);
  h1_mergenAngle_SIn -> SetFillColor(kOrange-2);
  h1_mergenAngle_SIn -> SetFillStyle(3004);
  h1_mergenAngle_SIn -> SetStats(0);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_mergenAngle_SIn -> SetMinimum(0);
  h1_mergenAngle_SIn -> SetMaximum(11000);
  h1_mergenAngle_SIn ->GetYaxis()->SetTitleSize(0.038);
  h1_mergenAngle_SIn ->GetYaxis()->SetTitleOffset(1.3);
  h1_mergenAngle_SIn ->GetYaxis()->SetLabelSize(0.036);
  h1_mergenAngle_SIn ->GetXaxis()->SetTitle("Cosine of Angle between n and Beam Directions");
  h1_mergenAngle_SIn ->GetYaxis()->SetTitle("Number of Neutron Captures");
  h1_mergenAngle_SIn -> Draw("");
  h1_mergenAngle_BefSIn -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.12, 0.65, 0.67, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.45]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_mergenAngle_BefSIn , "Primary #nu int. + FSI (Captured)", "L");
  legend1 -> AddEntry(h1_mergenAngle_SIn, "SI (Captured)", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


}