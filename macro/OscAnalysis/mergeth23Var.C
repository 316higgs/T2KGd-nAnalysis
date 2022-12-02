
void mergeth23Var(bool beammode) {
  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;

  //FHC
#if fhcflag
  //==== 0.532 ====
  TFile* f1 = new TFile("./output/fhc_05.root");
  //==== 0.511 ====
  TFile* f2 = new TFile("./output/fhc_0511.root");
  //==== 0.5 ====
  TFile* f3 = new TFile("./output/fhc_0532.root");
  //==== 0.55 ====
  TFile* f4 = new TFile("./output/fhc_055.root");
#endif

  //RHC
#if rhcflag
  //==== 0.532 ====
  TFile* f1 = new TFile("./output/rhc_0532.root");
  //==== 0.511 ====
  TFile* f2 = new TFile("./output/rhc_0511.root");
#endif

  TH1F* h1_NoNTag1 = (TH1F*)f1->Get("h1_NoNTag");
  TH1F* h1_NoNTag2 = (TH1F*)f2->Get("h1_NoNTag");
  TH1F* h1_NoNTag3 = (TH1F*)f3->Get("h1_NoNTag");
  TH1F* h1_NoNTag4 = (TH1F*)f4->Get("h1_NoNTag");
  h1_NoNTag1 -> SetLineColor(kViolet+2);
  h1_NoNTag2 -> SetLineColor(kAzure+7);
  h1_NoNTag3 -> SetLineColor(kRed-7);
  h1_NoNTag4 -> SetLineColor(kOrange+0);

  TH1F* h1_wTagN1  = (TH1F*)f1->Get("h1_wTagN");
  TH1F* h1_wTagN2  = (TH1F*)f2->Get("h1_wTagN");
  TH1F* h1_wTagN3  = (TH1F*)f3->Get("h1_wTagN");
  TH1F* h1_wTagN4  = (TH1F*)f4->Get("h1_wTagN");
  h1_wTagN1 -> SetLineColor(kViolet+2);
  h1_wTagN2 -> SetLineColor(kAzure+7);
  h1_wTagN3 -> SetLineColor(kRed-7);
  h1_wTagN4 -> SetLineColor(kOrange+0);

  TH1F* h1_woTagN1 = (TH1F*)f1->Get("h1_woTagN");
  TH1F* h1_woTagN2 = (TH1F*)f2->Get("h1_woTagN");
  TH1F* h1_woTagN3 = (TH1F*)f3->Get("h1_woTagN");
  TH1F* h1_woTagN4 = (TH1F*)f4->Get("h1_woTagN");
  h1_woTagN1 -> SetLineColor(kViolet+2);
  h1_woTagN2 -> SetLineColor(kAzure+7);
  h1_woTagN3 -> SetLineColor(kRed-7);
  h1_woTagN4 -> SetLineColor(kOrange+0);



  TCanvas* c1 = new TCanvas("c1", "No NTag", 900, 700);
  c1 -> SetGrid();
  h1_NoNTag4 -> SetStats(0);
  h1_NoNTag4 -> SetMaximum(17);
  h1_NoNTag4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_NoNTag4 -> SetYTitle("Number of Neutrino Events");
  h1_NoNTag4 -> Draw("SAME");
  h1_NoNTag3 -> Draw("SAME");
  h1_NoNTag2 -> Draw("SAME");
  h1_NoNTag1 -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.35, 0.57, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_NoNTag1, "sin^{2}#theta_{23}=0.5", "L");
  legend1 -> AddEntry(h1_NoNTag2, "sin^{2}#theta_{23}=0.511(maximal mixing)", "L");
  legend1 -> AddEntry(h1_NoNTag3, "sin^{2}#theta_{23}=0.532", "L");
  legend1 -> AddEntry(h1_NoNTag4, "sin^{2}#theta_{23}=0.55", "L");
  legend1->SetFillColor(0);
  legend1->Draw();

  TCanvas* c2 = new TCanvas("c2", "w/ TagN", 900, 700);
  c2 -> SetGrid();
  h1_wTagN4 -> SetStats(0);
  h1_wTagN4 -> SetMaximum(17);
  h1_wTagN4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_wTagN4 -> SetYTitle("Number of Neutrino Events");
  h1_wTagN4 -> Draw("SAME");
  h1_wTagN3 -> Draw("SAME");
  h1_wTagN2 -> Draw("SAME");
  h1_wTagN1 -> Draw("SAME");

  TCanvas* c3 = new TCanvas("c3", "w/o TagN", 900, 700);
  c3 -> SetGrid();
  h1_woTagN4 -> SetStats(0);
  h1_woTagN4 -> SetMaximum(17);
  h1_woTagN4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_woTagN4 -> SetYTitle("Number of Neutrino Events");
  h1_woTagN4 -> Draw("SAME");
  h1_woTagN3 -> Draw("SAME");
  h1_woTagN2 -> Draw("SAME");
  h1_woTagN1 -> Draw("SAME");

}

