

#define NUMUEVENTS 80624
#define NUMUBAREVENTS 71452

void GeneratedNeutrons() {

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");

  TH1F* h1_GenBefFSI_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenBefFSINeutrons");
  TH1F* h1_GenBefSI_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAtSI_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenAftSINeutrons");
  TH1F* h1_GenAftSI_numu = new TH1F("h1_GenAftSI_numu", "", 10, 0, 10);
  h1_GenAftSI_numu -> Add(h1_GenBefSI_numu);
  h1_GenAftSI_numu -> Add(h1_GenAtSI_numu);
  for (int i=0; i<10; i++) h1_GenAftSI_numu->GetXaxis()->SetBinLabel(i+1, TString::Format("%d", i));
  h1_GenBefFSI_numu -> SetLineWidth(3);
  h1_GenBefSI_numu  -> SetLineWidth(3);
  h1_GenAftSI_numu  -> SetLineWidth(3);
  h1_GenBefFSI_numu -> SetStats(0);
  h1_GenBefSI_numu  -> SetStats(0);
  h1_GenAftSI_numu  -> SetStats(0);
  h1_GenBefFSI_numu -> SetFillColor(kViolet-6);
  h1_GenBefSI_numu  -> SetFillColor(kViolet-6);
  h1_GenAftSI_numu  -> SetFillColor(kViolet-6);
  h1_GenBefFSI_numu -> SetFillStyle(3004);
  h1_GenBefSI_numu  -> SetFillStyle(3004);
  h1_GenAftSI_numu  -> SetFillStyle(3004);
  h1_GenBefFSI_numu -> SetLineColor(kViolet-6);
  h1_GenBefSI_numu  -> SetLineColor(kViolet-6);
  h1_GenAftSI_numu  -> SetLineColor(kViolet-6);
  //h1_GenBefSI_numu -> Scale(1./NUMUEVENTS);
  //h1_GenAtSI_numu  -> Scale(1./NUMUEVENTS);
  Double_t tot_BefFSI_numu = h1_GenBefFSI_numu->Integral();
  Double_t tot_BefSI_numu  = h1_GenBefSI_numu->Integral();
  Double_t tot_AftSI_numu  = h1_GenAftSI_numu->Integral();
  h1_GenBefFSI_numu -> Scale(1./tot_BefFSI_numu);
  h1_GenBefSI_numu  -> Scale(1./tot_BefSI_numu);
  h1_GenAftSI_numu  -> Scale(1./tot_AftSI_numu);

  TH1F* h1_GenBefFSI_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenBefFSINeutrons");
  TH1F* h1_GenBefSI_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAtSI_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenAftSINeutrons");
  TH1F* h1_GenAftSI_numubar = new TH1F("h1_GenAftSI_numubar", "", 10, 0, 10);
  h1_GenAftSI_numubar -> Add(h1_GenBefSI_numubar);
  h1_GenAftSI_numubar -> Add(h1_GenAtSI_numubar);
  h1_GenBefFSI_numubar -> SetLineWidth(3);
  h1_GenBefSI_numubar  -> SetLineWidth(3);
  h1_GenAftSI_numubar  -> SetLineWidth(3);
  h1_GenBefFSI_numubar -> SetFillColor(kOrange+7);
  h1_GenBefSI_numubar  -> SetFillColor(kOrange+7);
  h1_GenAftSI_numubar  -> SetFillColor(kOrange+7);
  h1_GenBefFSI_numubar -> SetFillStyle(3004);
  h1_GenBefSI_numubar  -> SetFillStyle(3004);
  h1_GenAftSI_numubar  -> SetFillStyle(3004);
  h1_GenBefFSI_numubar -> SetLineColor(kOrange+7);
  h1_GenBefSI_numubar  -> SetLineColor(kOrange+7);
  h1_GenAftSI_numubar  -> SetLineColor(kOrange+7);
  //h1_GenBefSI_numubar -> Scale(1./NUMUBAREVENTS);
  //h1_GenAtSI_numubar  -> Scale(1./NUMUBAREVENTS);
  Double_t tot_BefFSI_numubar = h1_GenBefFSI_numubar->Integral();
  Double_t tot_BefSI_numubar  = h1_GenBefSI_numubar->Integral();
  Double_t tot_AftSI_numubar  = h1_GenAftSI_numubar->Integral();
  h1_GenBefFSI_numubar -> Scale(1./tot_BefFSI_numubar);
  h1_GenBefSI_numubar  -> Scale(1./tot_BefSI_numubar);
  h1_GenAftSI_numubar  -> Scale(1./tot_AftSI_numubar);


  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_GenBefFSI_numu -> SetMaximum(1.1);
  h1_GenBefFSI_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_GenBefFSI_numu ->GetYaxis()->SetTitleOffset(1.);
  h1_GenBefFSI_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefFSI_numu ->GetXaxis()->SetLabelSize(0.04);
  h1_GenBefFSI_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_GenBefFSI_numu->GetYaxis()->SetTitle("Area Normalized");
  h1_GenBefFSI_numu->GetXaxis()->SetTitle("Number of Generated Neutrons(MC Truth)");
  h1_GenBefFSI_numu -> Draw();
  h1_GenBefFSI_numubar -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.6, 0.68, 0.89, 0.89);
  legend1 -> SetTextSize(0.045);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Before FSI (All #nu interaction)}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Before FSI (CCQE)}","");
  legend1 -> AddEntry(h1_GenBefFSI_numu, "#nu_{#mu}#rightarrow#nu_{#mu} MC", "L");
  legend1 -> AddEntry(h1_GenBefFSI_numubar, "#bar#nu_{#mu}#rightarrow#bar#nu_{#mu} MC", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h1_GenBefSI_numu -> SetMaximum(1.1);
  h1_GenBefSI_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_GenBefSI_numu ->GetYaxis()->SetTitleOffset(1.);
  h1_GenBefSI_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_GenBefSI_numu ->GetXaxis()->SetLabelSize(0.04);
  h1_GenBefSI_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_GenBefSI_numu->GetYaxis()->SetTitle("Area Normalized");
  h1_GenBefSI_numu->GetXaxis()->SetTitle("Number of Generated Neutrons(MC Truth)");
  h1_GenBefSI_numu -> Draw();
  h1_GenBefSI_numubar -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.6, 0.68, 0.89, 0.89);
  legend2 -> SetTextSize(0.045);
  //legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{Before SI (All #nu interaction)}","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{Before SI (CCQE)}","");
  legend2 -> AddEntry(h1_GenBefSI_numu, "#nu_{#mu}#rightarrow#nu_{#mu} MC", "L");
  legend2 -> AddEntry(h1_GenBefSI_numubar, "#bar#nu_{#mu}#rightarrow#bar#nu_{#mu} MC", "L");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();


  TCanvas* c3 = new TCanvas("c3", "c3", 900, 700);
  c3 -> SetGrid();
  h1_GenAftSI_numu -> SetMaximum(1.1);
  h1_GenAftSI_numu ->GetYaxis()->SetTitleSize(0.045);
  h1_GenAftSI_numu ->GetYaxis()->SetTitleOffset(1.);
  h1_GenAftSI_numu ->GetYaxis()->SetLabelSize(0.036);
  h1_GenAftSI_numu ->GetXaxis()->SetLabelSize(0.04);
  h1_GenAftSI_numu ->GetXaxis()->SetTitleSize(0.045);
  h1_GenAftSI_numu->GetYaxis()->SetTitle("Area Normalized");
  h1_GenAftSI_numu->GetXaxis()->SetTitle("Number of Captured Neutrons(MC Truth)");
  h1_GenAftSI_numu -> Draw();
  h1_GenAftSI_numubar -> Draw("SAME");

  TLegend* legend3 = new TLegend(0.6, 0.68, 0.89, 0.89);
  legend3 -> SetTextSize(0.045);
  //legend3 -> AddEntry((TObject*)0,"#kern[-0.2]{After SI (All #nu interaction)}","");
  legend3 -> AddEntry((TObject*)0,"#kern[-0.2]{After SI (CCQE)}","");
  legend3 -> AddEntry(h1_GenBefSI_numu, "#nu_{#mu}#rightarrow#nu_{#mu} MC", "L");
  legend3 -> AddEntry(h1_GenBefSI_numubar, "#bar#nu_{#mu}#rightarrow#bar#nu_{#mu} MC", "L");
  legend3 -> SetFillColor(0);
  legend3 -> Draw();

}
