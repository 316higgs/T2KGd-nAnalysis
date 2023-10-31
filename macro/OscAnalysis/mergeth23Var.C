
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
#if 1
#if fhcflag
  TFile* f1 = new TFile("./output/fhc_0511.root");
  TFile* f2 = new TFile("./output/fhc_0530.root");
  TFile* f3 = new TFile("./output/fhc_0561.root");
  TFile* f4 = new TFile("./output/fhc_0570.root");
#endif
#endif

#if 0
#if fhcflag
  TFile* f1 = new TFile("./output/fhc_003conc_0511.root");
  TFile* f2 = new TFile("./output/fhc_003conc_0530.root");
  TFile* f3 = new TFile("./output/fhc_003conc_0561.root");
  TFile* f4 = new TFile("./output/fhc_003conc_0570.root");
#endif
#endif


  TH1F* h1_NoNTag1 = (TH1F*)f1->Get("h1_NoNTag");
  TH1F* h1_NoNTag2 = (TH1F*)f2->Get("h1_NoNTag");
  TH1F* h1_NoNTag3 = (TH1F*)f3->Get("h1_NoNTag");
  TH1F* h1_NoNTag4 = (TH1F*)f4->Get("h1_NoNTag");
  h1_NoNTag1 -> SetLineColor(kViolet+2);
  h1_NoNTag2 -> SetLineColor(kAzure+7);
  h1_NoNTag3 -> SetLineColor(kRed-3);
  h1_NoNTag3 -> SetFillColor(kPink-4);
  h1_NoNTag3 -> SetFillStyle(3004);
  h1_NoNTag4 -> SetLineColor(kOrange-2);

  TH1F* h1_wTagN1  = (TH1F*)f1->Get("h1_wTagN");
  TH1F* h1_wTagN2  = (TH1F*)f2->Get("h1_wTagN");
  TH1F* h1_wTagN3  = (TH1F*)f3->Get("h1_wTagN");
  TH1F* h1_wTagN4  = (TH1F*)f4->Get("h1_wTagN");
  h1_wTagN1 -> SetLineColor(kViolet+2);
  h1_wTagN2 -> SetLineColor(kAzure+7);
  h1_wTagN3 -> SetLineColor(kRed-3);
  h1_wTagN3 -> SetFillColor(kPink-4);
  h1_wTagN3 -> SetFillStyle(3004);
  h1_wTagN4 -> SetLineColor(kOrange-2);

  TH1F* h1_woTagN1 = (TH1F*)f1->Get("h1_woTagN");
  TH1F* h1_woTagN2 = (TH1F*)f2->Get("h1_woTagN");
  TH1F* h1_woTagN3 = (TH1F*)f3->Get("h1_woTagN");
  TH1F* h1_woTagN4 = (TH1F*)f4->Get("h1_woTagN");
  h1_woTagN1 -> SetLineColor(kViolet+2);
  h1_woTagN2 -> SetLineColor(kAzure+7);
  h1_woTagN3 -> SetLineColor(kRed-3);
  h1_woTagN3 -> SetFillColor(kPink-4);
  h1_woTagN3 -> SetFillStyle(3004);
  h1_woTagN4 -> SetLineColor(kOrange-2);


  TH1F* h1_bnd = new TH1F("h1_bnd", "", 60, 0, 3);
  h1_bnd -> SetLineColor(kRed-3);
  h1_bnd -> SetFillColor(kGray+1);
  h1_bnd -> SetFillStyle(3004);
  int   BINNUM    = 60;
  float LowerEdge = 0.;
  float UpperEdge = 3.;
  float interval  = (UpperEdge - LowerEdge)/BINNUM;
  const int   TH23VAR   = 4;
  float N_NoNTag[TH23VAR] = {0.};
  float N_wTagN[TH23VAR]  = {0.};
  float N_woTagN[TH23VAR] = {0.};
  for (int ibin=0; ibin<BINNUM; ibin++) {
    float thisEnu = interval*ibin;
    if (thisEnu>=0.5 && thisEnu<=0.7) {
      //std::cout << "[ Bin " << ibin << " ] Enu = " << thisEnu << " GeV" << std::endl;
      //std::cout << "  th23 = 0.511 : " << h1_NoNTag1->GetBinContent(ibin+1) << " (No NTag), " << h1_wTagN1->GetBinContent(ibin+1) << " (w/ TagN), " << h1_woTagN1->GetBinContent(ibin+1) << " (w/o TagN)" << std::endl;
      //std::cout << "  th23 = 0.530 : " << h1_NoNTag2->GetBinContent(ibin+1) << " (No NTag), " << h1_wTagN2->GetBinContent(ibin+1) << " (w/ TagN), " << h1_woTagN2->GetBinContent(ibin+1) << " (w/o TagN)" << std::endl;
      //std::cout << "  th23 = 0.561 : " << h1_NoNTag3->GetBinContent(ibin+1) << " (No NTag), " << h1_wTagN3->GetBinContent(ibin+1) << " (w/ TagN), " << h1_woTagN3->GetBinContent(ibin+1) << " (w/o TagN)" << std::endl;
      //std::cout << "  th23 = 0.570 : " << h1_NoNTag4->GetBinContent(ibin+1) << " (No NTag), " << h1_wTagN4->GetBinContent(ibin+1) << " (w/ TagN), " << h1_woTagN4->GetBinContent(ibin+1) << " (w/o TagN)" << std::endl;

      N_NoNTag[0] += h1_NoNTag1->GetBinContent(ibin+1);
      N_NoNTag[1] += h1_NoNTag2->GetBinContent(ibin+1);
      N_NoNTag[2] += h1_NoNTag3->GetBinContent(ibin+1);
      N_NoNTag[3] += h1_NoNTag4->GetBinContent(ibin+1);

      N_wTagN[0] += h1_wTagN1->GetBinContent(ibin+1);
      N_wTagN[1] += h1_wTagN2->GetBinContent(ibin+1);
      N_wTagN[2] += h1_wTagN3->GetBinContent(ibin+1);
      N_wTagN[3] += h1_wTagN4->GetBinContent(ibin+1);

      N_woTagN[0] += h1_woTagN1->GetBinContent(ibin+1);
      N_woTagN[1] += h1_woTagN2->GetBinContent(ibin+1);
      N_woTagN[2] += h1_woTagN3->GetBinContent(ibin+1);
      N_woTagN[3] += h1_woTagN4->GetBinContent(ibin+1);

      h1_bnd -> SetBinContent(ibin+1, h1_NoNTag3->GetBinContent(ibin+1));
    }
  }

  std::cout << "th23 = 0.511 : " << N_NoNTag[0] << " (No NTag), " << N_wTagN[0] << " (w/ TagN), " << N_woTagN[0] << " (w/o TagN)" << std::endl;
  std::cout << "th23 = 0.530 : " << N_NoNTag[1] << " (No NTag), " << N_wTagN[1] << " (w/ TagN), " << N_woTagN[1] << " (w/o TagN)" << std::endl;
  std::cout << "th23 = 0.561 : " << N_NoNTag[2] << " (No NTag), " << N_wTagN[2] << " (w/ TagN), " << N_woTagN[2] << " (w/o TagN)" << std::endl;
  std::cout << "th23 = 0.570 : " << N_NoNTag[3] << " (No NTag), " << N_wTagN[3] << " (w/ TagN), " << N_woTagN[3] << " (w/o TagN)" << std::endl;


  gROOT -> SetStyle("Plain");
#if 0
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_NoNTag4 -> SetStats(0);
  h1_NoNTag4 -> SetMaximum(2.1);
  h1_NoNTag4 ->GetYaxis()->SetTitleSize(0.045);
  h1_NoNTag4 ->GetXaxis()->SetTitleSize(0.045);
  h1_NoNTag4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_NoNTag4 -> SetYTitle("Number of Neutrino Events");
  h1_NoNTag4 -> Draw();
  h1_NoNTag3 -> Draw("SAME");
  //h1_bnd     -> Draw("SAME");
  h1_NoNTag2 -> Draw("SAME");
  h1_NoNTag1 -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.35, 0.57, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.03% Gd)}","");
  legend1 -> AddEntry(h1_NoNTag1, "sin^{2}#theta_{23}=0.511(maximal mixing)", "L");
  legend1 -> AddEntry(h1_NoNTag2, "sin^{2}#theta_{23}=0.53", "L");
  legend1 -> AddEntry(h1_NoNTag3, "sin^{2}#theta_{23}=0.561(nominal MC)", "L");
  legend1 -> AddEntry(h1_NoNTag4, "sin^{2}#theta_{23}=0.57", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

#if 0
  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h1_wTagN4 -> SetStats(0);
  h1_wTagN4 -> SetMaximum(2.1);
  h1_wTagN4 ->GetYaxis()->SetTitleSize(0.045);
  h1_wTagN4 ->GetXaxis()->SetTitleSize(0.045);
  h1_wTagN4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_wTagN4 -> SetYTitle("Number of Neutrino Events");
  h1_wTagN4 -> Draw("SAME");
  h1_wTagN3 -> Draw("SAME");
  h1_wTagN2 -> Draw("SAME");
  h1_wTagN1 -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.35, 0.55, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend2 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.03% Gd)}","");
  legend2 -> AddEntry((TObject*)0,"#kern[-0.65]{w/ neutrons}","");
  legend2 -> AddEntry(h1_NoNTag1, "sin^{2}#theta_{23}=0.511(maximal mixing)", "L");
  legend2 -> AddEntry(h1_NoNTag2, "sin^{2}#theta_{23}=0.53", "L");
  legend2 -> AddEntry(h1_NoNTag3, "sin^{2}#theta_{23}=0.561(nominal MC)", "L");
  legend2 -> AddEntry(h1_NoNTag4, "sin^{2}#theta_{23}=0.57", "L");
  legend2->SetFillColor(0);
  legend2->Draw();


  TCanvas* c3 = new TCanvas("c3", "c3", 900, 700);
  c3 -> SetGrid();
  h1_woTagN4 -> SetStats(0);
  h1_woTagN4 -> SetMaximum(2.1);
  h1_woTagN4 ->GetYaxis()->SetTitleSize(0.045);
  h1_woTagN4 ->GetXaxis()->SetTitleSize(0.045);
  h1_woTagN4 -> SetXTitle("Reconstructed Neutrino Energy E_{#nu}[GeV]");
  h1_woTagN4 -> SetYTitle("Number of Neutrino Events");
  h1_woTagN4 -> Draw("SAME");
  h1_woTagN3 -> Draw("SAME");
  h1_woTagN2 -> Draw("SAME");
  h1_woTagN1 -> Draw("SAME");
  
  TLegend* legend3 = new TLegend(0.35, 0.55, 0.89, 0.89);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend3 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (0.03% Gd)}","");
  legend3 -> AddEntry((TObject*)0,"#kern[-0.6]{w/o neutrons}","");
  legend3 -> AddEntry(h1_NoNTag1, "sin^{2}#theta_{23}=0.511(maximal mixing)", "L");
  legend3 -> AddEntry(h1_NoNTag2, "sin^{2}#theta_{23}=0.53", "L");
  legend3 -> AddEntry(h1_NoNTag3, "sin^{2}#theta_{23}=0.561(nominal MC)", "L");
  legend3 -> AddEntry(h1_NoNTag4, "sin^{2}#theta_{23}=0.57", "L");
  legend3->SetFillColor(0);
  legend3->Draw();
#endif

}

