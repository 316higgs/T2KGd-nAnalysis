

void TaggedN_run() {
  TFile* fin_data = new TFile("../../output/fhc/run11.bonsai_keras_prompt_vertex.root");
  TH1F* h1_FC_run   = (TH1F*)fin_data->Get("NTagAnalysis/h1_FC_run");
  TH1F* h1_1Rmu_run = (TH1F*)fin_data->Get("NTagAnalysis/h1_1Rmu_run");
  TH1F* h1_TagN_run = (TH1F*)fin_data->Get("NTagAnalysis/h1_TagN_run");

  h1_FC_run -> SetLineColor(kGray);
  h1_FC_run -> SetLineWidth(2);
  h1_FC_run -> SetStats(0);
  h1_FC_run -> SetFillStyle(3357);
  h1_FC_run -> SetFillColor(kGray);

  h1_1Rmu_run -> SetLineColor(kOrange-6);
  h1_1Rmu_run -> SetLineWidth(2);
  h1_1Rmu_run -> SetStats(0);
  h1_1Rmu_run -> SetFillStyle(3357);
  h1_1Rmu_run -> SetFillColor(kOrange-6);

  h1_TagN_run -> SetMarkerStyle(20);
  h1_TagN_run -> SetMarkerSize(1);
  h1_TagN_run -> SetMarkerColor(kBlack);
  h1_TagN_run -> SetLineColor(kBlack);
  h1_TagN_run -> SetLineWidth(3);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1", 900,500);
  c1 -> SetGrid();
  c1 -> SetTicks(1);
  h1_FC_run -> SetMaximum(5);
  h1_FC_run -> SetXTitle("#spill");
  h1_FC_run -> SetYTitle("Number of Tagged Neutrons");
  h1_FC_run -> GetXaxis()->SetTitleSize(0.045);
  h1_FC_run -> GetYaxis()->SetTitleSize(0.045);
  h1_FC_run -> GetYaxis()->SetLabelSize(0.038);
  h1_FC_run -> Draw("");
  h1_1Rmu_run -> Draw("SAME");
  h1_TagN_run -> Draw("SAME P");


  TLegend* legend1 = new TLegend(0.12, 0.6, 0.5, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.65]{T2K run 11}","");
  legend1 -> AddEntry(h1_FC_run, "FC events", "F");
  legend1 -> AddEntry(h1_1Rmu_run, "1R#mu events", "F");
  legend1 -> AddEntry(h1_TagN_run, "Tagged neutrons", "P");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


}