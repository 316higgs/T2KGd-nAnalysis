

void mergeSelectedEvents() {

  TFile* fin_00263 = new TFile("output/SelectedNuEvents.Gdconc0.026300.root");
  TFile* fin_00251 = new TFile("output/SelectedNuEvents.Gdconc0.025100.root");

  TH1F* h1_SelEff_00263 = (TH1F*)fin_00263->Get("h1_NuEvt_merge");
  TH1F* h1_SelEff_00251 = (TH1F*)fin_00251->Get("h1_NuEvt_merge");

  h1_SelEff_00263 -> SetLineColor(kAzure+5);
  h1_SelEff_00263 -> SetLineWidth(3);
  h1_SelEff_00263 -> SetStats(0);

  h1_SelEff_00251 -> SetLineColor(kOrange+8);
  h1_SelEff_00251 -> SetLineWidth(3);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1", 1000,700);
  c1 -> SetGrid();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->SetGridy();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  
  //h1_SelEff_00263 -> SetMaximum(180);
  h1_SelEff_00263 -> Draw();
  h1_SelEff_00263 ->GetYaxis()->SetTitleSize(0.055);
  h1_SelEff_00263 ->GetYaxis()->SetTitleOffset(0.8);
  h1_SelEff_00263 ->GetYaxis()->SetLabelSize(0.05);
  h1_SelEff_00263 ->GetYaxis()->SetTitle("Number of #nu Events");
  h1_SelEff_00263 -> Draw();
  h1_SelEff_00251 -> Draw("SAME");
  c1 -> RedrawAxis();

  TLegend* legend1 = new TLegend(0.47, 0.5, 0.89, 0.89);
  legend1 -> SetTextSize(0.055);
  legend1->AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_SelEff_00263, "0.0263% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend1 -> AddEntry(h1_SelEff_00251, "0.0251% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend1->SetFillColor(0);
  legend1->Draw();


  c1->cd();          // Go back to the main canvas before defining pad2
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.3);
  pad2->SetGridx(); // vertical grid
  pad2->SetGridy(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad

  gROOT -> SetStyle("Plain");
  TH1F *h1_SelEffRatio = (TH1F*)h1_SelEff_00251->Clone("h1_SelEffRatio");
  h1_SelEffRatio->SetLineColor(kViolet-7);
  h1_SelEffRatio->SetMinimum(0.8);  // Define Y ..
  h1_SelEffRatio->SetMaximum(1.35); // .. range
  h1_SelEffRatio ->GetYaxis()->SetTitleSize(0.16);
  h1_SelEffRatio ->GetYaxis()->SetTitleOffset(0.28);
  h1_SelEffRatio ->GetYaxis()->SetLabelSize(0.12);
  h1_SelEffRatio ->GetYaxis()->SetTitle("Ratio     ");
  h1_SelEffRatio ->GetXaxis()->SetLabelSize(0.15);
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(1, "C1.FCFV");
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(2, "C2.#Ring=1");
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(3, "C3.#mu-like");
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(4, "C4.P_{#mu}> 200 MeV/c");
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(5, "C5.#decay-e#leq1");
  h1_SelEffRatio -> GetXaxis()->SetBinLabel(6, "C6.Not #pi^{#pm}-like");
  h1_SelEffRatio->Sumw2();
  h1_SelEffRatio->SetStats(0);      // No statistics on lower plot
  h1_SelEffRatio->Divide(h1_SelEff_00263);
  h1_SelEffRatio->SetMarkerStyle(21);
  h1_SelEffRatio->Draw("histo");       // Draw the ratio plot

  TLegend* legend2 = new TLegend(0.47, 0.65, 0.89, 0.95);
  legend2 -> SetTextSize(0.13);
  legend2 -> AddEntry(h1_SelEffRatio, "N_{#nu}(0.0251%) / N_{#nu}(0.0263%)", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
}