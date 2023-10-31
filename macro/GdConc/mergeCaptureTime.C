

void mergeCaptureTime() {

  TFile* fin_00263 = new TFile("output/CaptureTime.Gdconc0.026300.root");
  TFile* fin_00251 = new TFile("output/CaptureTime.Gdconc0.025100.root");

  TH1F* h1_CapTime_00263 = (TH1F*)fin_00263->Get("h1_TrueCapTime");
  TH1F* h1_CapTime_00251 = (TH1F*)fin_00251->Get("h1_TrueCapTime");

  //TH1F* h1_CapTime_00263 = (TH1F*)fin_00263->Get("h1_RecoCapTime");
  //TH1F* h1_CapTime_00251 = (TH1F*)fin_00251->Get("h1_RecoCapTime");

  h1_CapTime_00263 -> SetLineColor(kAzure+5);
  h1_CapTime_00263 -> SetLineWidth(3);
  h1_CapTime_00263 -> SetStats(0);

  h1_CapTime_00251 -> SetLineColor(kOrange+8);
  h1_CapTime_00251 -> SetLineWidth(3);


  TF1* f1_CapTime_00263 = new TF1("f1_CapTime_00263", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 10, 535);
  f1_CapTime_00263 -> SetParameter(0, 100);    // for LL option (if normalized, LL should be used)
  f1_CapTime_00263 -> SetParameter(1, 50);
  f1_CapTime_00263 -> SetParameter(2, 120);
  f1_CapTime_00263 -> SetParameter(3, 10);
  f1_CapTime_00263 -> SetLineColor(kAzure+5);
  f1_CapTime_00263 -> SetLineWidth(2);
  f1_CapTime_00263 -> SetLineStyle(7);
  f1_CapTime_00263 -> SetNpx(10000);

  TF1* f1_CapTime_00251 = new TF1("f1_CapTime_00251", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 10, 535);
  f1_CapTime_00251 -> SetParameter(0, 100);    // for LL option (if normalized, LL should be used)
  f1_CapTime_00251 -> SetParameter(1, 50);
  f1_CapTime_00251 -> SetParameter(2, 120);
  f1_CapTime_00251 -> SetParameter(3, 10);
  f1_CapTime_00251 -> SetLineColor(kOrange+8);
  f1_CapTime_00251 -> SetLineWidth(2);
  f1_CapTime_00251 -> SetLineStyle(7);
  f1_CapTime_00251 -> SetNpx(10000);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1", 1000,700);
  c1 -> SetGrid();
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();         // Vertical grid
  pad1->SetGridy();         // Vertical grid
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();               // pad1 becomes the current pad
  

  h1_CapTime_00263 -> Fit(f1_CapTime_00263, "rLL");
  h1_CapTime_00251 -> Fit(f1_CapTime_00251, "rLL");

  Double_t CapTime_00263    = f1_CapTime_00263->GetParameter(2);
  Double_t CapTimeErr_00263 = f1_CapTime_00263->GetParError(2);

  Double_t CapTime_00251    = f1_CapTime_00251->GetParameter(2);
  Double_t CapTimeErr_00251 = f1_CapTime_00251->GetParError(2);

  h1_CapTime_00263 -> SetMinimum(0.01);
  h1_CapTime_00263 -> Draw();
  h1_CapTime_00263 ->GetYaxis()->SetTitleSize(0.055);
  h1_CapTime_00263 ->GetYaxis()->SetTitleOffset(0.8);
  h1_CapTime_00263 ->GetYaxis()->SetLabelSize(0.05);
  h1_CapTime_00263 ->GetYaxis()->SetTitle("Number of True Neutron Captures");
  //h1_CapTime_00263 ->GetYaxis()->SetTitle("Number of Tagged Neutron Captures");
  h1_CapTime_00263 -> Draw();
  h1_CapTime_00251 -> Draw("SAME");
  h1_CapTime_00251 -> GetXaxis()->SetTitle("True Capture Time");
  c1 -> RedrawAxis();

  TLegend* legend1 = new TLegend(0.47, 0.5, 0.89, 0.89);
  legend1 -> SetTextSize(0.055);
  legend1->AddEntry((TObject*)0,"#kern[-0.4]{FHC 1R #mu sample}","");
  legend1 -> AddEntry(h1_CapTime_00263, "0.0263% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time = %.1f #pm %.1f #musec}", CapTime_00263, CapTimeErr_00263),"");
  legend1 -> AddEntry(h1_CapTime_00251, "0.0251% Gd_{2} (SO_{4})_{3} 8H_{2}O", "L");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.25]{Capture time = %.1f #pm %.1f #musec}", CapTime_00251, CapTimeErr_00251),"");
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
  TH1F *h1_CapTimeRatio = (TH1F*)h1_CapTime_00251->Clone("h1_CapTimeRatio");
  h1_CapTimeRatio->SetLineColor(kViolet-7);
  h1_CapTimeRatio->SetMinimum(0.7);  // Define Y ..
  h1_CapTimeRatio->SetMaximum(1.25); // .. range
  h1_CapTimeRatio ->GetYaxis()->SetTitleSize(0.16);
  h1_CapTimeRatio ->GetYaxis()->SetTitleOffset(0.28);
  h1_CapTimeRatio ->GetYaxis()->SetLabelSize(0.12);
  h1_CapTimeRatio ->GetYaxis()->SetTitle("Ratio     ");
  h1_CapTimeRatio ->GetXaxis()->SetTitleSize(0.16);
  h1_CapTimeRatio ->GetXaxis()->SetTitleOffset(0.8);
  h1_CapTimeRatio ->GetXaxis()->SetLabelSize(0.13);
  h1_CapTimeRatio -> GetXaxis()->SetTitle("True Capture Time [#mus]");
  //h1_CapTimeRatio -> GetXaxis()->SetTitle("Reconstructed Capture Time [#mus]");
  h1_CapTimeRatio->Sumw2();
  h1_CapTimeRatio->SetStats(0);      // No statistics on lower plot
  h1_CapTimeRatio->Divide(h1_CapTime_00263);
  h1_CapTimeRatio->SetMarkerStyle(21);
  h1_CapTimeRatio->Draw("histo");       // Draw the ratio plot

  TLegend* legend2 = new TLegend(0.47, 0.65, 0.89, 0.95);
  legend2 -> SetTextSize(0.13);
  legend2 -> AddEntry(h1_CapTimeRatio, "N_{#nu}(0.0251%) / N_{#nu}(0.0263%)", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
}