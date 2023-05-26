void NNcomparison() {

  //TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.root");
  //TFile* fin2 = new TFile("../../output/fhc/fhc.numubar_x_numubar.postNN.root");

  TFile* fin1 = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.root");

  TFile* fin2 = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");
  //TFile* fin2 = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");

  TH1F* h1_NNvar_Gd_1[12];
  TH1F* h1_NNvar_H_1[12];
  TH1F* h1_NNvar_AccNoise_1[12];
  TH1F* h1_NNvar_Decaye_1[12];

  TH1F* h1_NNvar_Gd_2[12];
  TH1F* h1_NNvar_H_2[12];
  TH1F* h1_NNvar_AccNoise_2[12];
  TH1F* h1_NNvar_Decaye_2[12];

  for (int i=0; i<12; i++) {
  	h1_NNvar_Gd_1[i]       = (TH1F*)fin1->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
  	h1_NNvar_H_1[i]        = (TH1F*)fin1->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
  	h1_NNvar_AccNoise_1[i] = (TH1F*)fin1->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_1[i]   = (TH1F*)fin1->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_2[i]       = (TH1F*)fin2->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_2[i]        = (TH1F*)fin2->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_2[i] = (TH1F*)fin2->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_2[i]   = (TH1F*)fin2->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

  	h1_NNvar_Gd_1[i]       -> SetStats(0);
  	h1_NNvar_H_1[i]        -> SetStats(0);
  	h1_NNvar_AccNoise_1[i] -> SetStats(0);
    h1_NNvar_Decaye_1[i]   -> SetStats(0);

    h1_NNvar_Gd_2[i]       -> SetStats(0);
    h1_NNvar_H_2[i]        -> SetStats(0);
    h1_NNvar_AccNoise_2[i] -> SetStats(0);
    h1_NNvar_Decaye_2[i]   -> SetStats(0);

    h1_NNvar_Gd_1[i]       -> SetLineWidth(1);
    h1_NNvar_H_1[i]        -> SetLineWidth(1);
    h1_NNvar_AccNoise_1[i] -> SetLineWidth(1);
    h1_NNvar_Decaye_1[i]   -> SetLineWidth(1);

    h1_NNvar_Gd_2[i]       -> SetLineWidth(1);
    h1_NNvar_H_2[i]        -> SetLineWidth(1);
    h1_NNvar_AccNoise_2[i] -> SetLineWidth(1);
    h1_NNvar_Decaye_2[i]   -> SetLineWidth(1);

    h1_NNvar_Gd_1[i] -> SetLineColor(kAzure-8);
    h1_NNvar_Gd_2[i] -> SetLineColor(kOrange-3);

    h1_NNvar_H_1[i] -> SetLineColor(kAzure-8);
    h1_NNvar_H_2[i] -> SetLineColor(kOrange-3);

    h1_NNvar_Decaye_1[i] -> SetLineColor(kAzure-8);
    h1_NNvar_Decaye_2[i] -> SetLineColor(kOrange-3);

    h1_NNvar_AccNoise_1[i] -> SetLineColor(kAzure-8);
    h1_NNvar_AccNoise_2[i] -> SetLineColor(kOrange-3);

    Double_t totGd_1 = h1_NNvar_Gd_1[i]->Integral();
    Double_t totGd_2 = h1_NNvar_Gd_2[i]->Integral();
    h1_NNvar_Gd_1[i] -> Scale(1./totGd_1);
    h1_NNvar_Gd_2[i] -> Scale(1./totGd_2);

    Double_t totH_1 = h1_NNvar_H_1[i]->Integral();
    Double_t totH_2 = h1_NNvar_H_2[i]->Integral();
    h1_NNvar_H_1[i] -> Scale(1./totH_1);
    h1_NNvar_H_2[i] -> Scale(1./totH_2);

    Double_t totDecaye_1 = h1_NNvar_Decaye_1[i]->Integral();
    Double_t totDecaye_2 = h1_NNvar_Decaye_2[i]->Integral();
    h1_NNvar_Decaye_1[i] -> Scale(1./totDecaye_1);
    h1_NNvar_Decaye_2[i] -> Scale(1./totDecaye_2);

    Double_t totAccNoise_1 = h1_NNvar_AccNoise_1[i]->Integral();
    Double_t totAccNoise_2 = h1_NNvar_AccNoise_2[i]->Integral();
    h1_NNvar_AccNoise_1[i] -> Scale(1./totAccNoise_1);
    h1_NNvar_AccNoise_2[i] -> Scale(1./totAccNoise_2);
  }

  TLegend* legend = new TLegend(0.3, 0.71, 0.89, 0.89);
  legend -> SetTextSize(0.06);
  //legend -> AddEntry(h1_NNvar_AccNoise_1[0], "#nu_{#mu}#rightarrow#nu_{#mu} MC", "L");
  //legend -> AddEntry(h1_NNvar_AccNoise_2[0], "#bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC", "L");
  //legend -> AddEntry(h1_NNvar_AccNoise_1[0], "NTag2022Apr, Noise", "L");
  //legend -> AddEntry(h1_NNvar_AccNoise_2[0], "NTag1.1.2, Noise", "L");
  //legend -> AddEntry(h1_NNvar_Gd_1[0], "NTag2022Apr, Gd", "L");
  //legend -> AddEntry(h1_NNvar_Gd_2[0], "NTag1.1.2, Gd", "L");
  //legend -> AddEntry(h1_NNvar_H_1[0], "NTag2022Apr, H", "L");
  //legend -> AddEntry(h1_NNvar_H_2[0], "NTag1.1.2, H", "L");
  legend -> AddEntry(h1_NNvar_Decaye_1[0], "NTag2022Apr, Dcye", "L");
  legend -> AddEntry(h1_NNvar_Decaye_2[0], "NTag1.1.2, Dcye", "L");
  legend -> SetFillColor(0);
  //legend->SetLineColor(0);
  //legend->SetFillColor(0);
  //legend->SetFillStyle(0);
  legend->SetBorderSize(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  //TCanvas* c1 = new TCanvas("c1", "c1", 700, 700);
  gPad->SetLogy();
  ///*
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
  	c1 -> cd(i+1);
    gPad->SetLogy();

    //h1_NNvar_Gd_1[i] -> Draw();
    //h1_NNvar_Gd_2[i] -> Draw("SAME");
    h1_NNvar_H_1[i] -> Draw();
    h1_NNvar_H_2[i] -> Draw("SAME");
    //h1_NNvar_AccNoise_1[i] -> Draw();
    //h1_NNvar_AccNoise_2[i] -> Draw("SAME");
    if (i==0) legend -> Draw();

    //h1_NNvar_AccNoise_1[i] -> Sumw2();
    //h1_NNvar_AccNoise_1[i] -> Divide(h1_NNvar_AccNoise_2[i]);
    //h1_NNvar_AccNoise_1[i] -> Draw("hist");
    
  }
  //*/

  //h1_NNvar_AccNoise_1[0] -> Draw();
  //h1_NNvar_AccNoise_2[0] -> Draw("SAME");
  //legend -> Draw();

}