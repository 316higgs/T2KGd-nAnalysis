

void CaptureTime() {

  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");

  TH1F* h1_TrueCapTime_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNCapTime");
  h1_TrueCapTime_numu -> SetLineColor(kViolet-6);
  h1_TrueCapTime_numu -> SetLineWidth(2);
  h1_TrueCapTime_numu -> SetStats(0);
  h1_TrueCapTime_numu -> SetXTitle("True Capture Time [#musec]");
  h1_TrueCapTime_numu -> SetYTitle("Number of Captured Neutrons");
  Double_t tot_True = h1_TrueCapTime_numu->Integral();
  //h1_TrueCapTime_numu -> Scale(1./tot_True);

  TH1F* h1_RecoCapTime_Accnoise_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type0");
  h1_RecoCapTime_Accnoise_numu -> SetFillColor(kGray+2);
  h1_RecoCapTime_Accnoise_numu -> SetLineColor(kGray+2);
  TH1F* h1_RecoCapTime_dcye_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type1");
  h1_RecoCapTime_dcye_numu -> SetFillColor(kYellow-3);
  h1_RecoCapTime_dcye_numu -> SetLineColor(kYellow-3);
  TH1F* h1_RecoCapTime_H_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type2");
  h1_RecoCapTime_H_numu -> SetFillColor(kAzure-4);
  h1_RecoCapTime_H_numu -> SetLineColor(kAzure-4);
  TH1F* h1_RecoCapTime_Gd_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_RecoNCapTime_type3");
  h1_RecoCapTime_Gd_numu -> SetFillColor(kTeal-5);
  h1_RecoCapTime_Gd_numu -> SetLineColor(kTeal-5);

  THStack* hs_RecoCapTime_numu = new THStack("hs_RecoCapTime_numu", "Reco Captured Time; Reconstructed Capture Time [#mu sec]; Number of Events");
  hs_RecoCapTime_numu -> Add(h1_RecoCapTime_Accnoise_numu);
  hs_RecoCapTime_numu -> Add(h1_RecoCapTime_dcye_numu);
  //hs_RecoCapTime_numu -> Add(h1_RecoCapTime_H_numu);
  //hs_RecoCapTime_numu -> Add(h1_RecoCapTime_Gd_numu);

  TF1* f1_CapTime = new TF1("f", "[0] * (1-exp(-[1]*x)) * exp(-x/[2]) + [3]", 0, 535);
  f1_CapTime -> SetParameter(0, 500);
  f1_CapTime -> SetParameter(1, 10);
  f1_CapTime -> SetParameter(2, 150);
  f1_CapTime -> SetParameter(3, 10);
  f1_CapTime -> SetLineColor(kPink-9);
  f1_CapTime -> SetNpx(10000);


  gStyle->SetOptFit(1111);
  /////////// True Capture Time //////////
#if 1
  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  c1 -> SetGrid();
  h1_TrueCapTime_numu -> Fit(f1_CapTime);
  //h1_TrueCapTime_numu -> Fit(f1_CapTime);
  h1_TrueCapTime_numu -> Draw();
  f1_CapTime -> Draw("SAME");
  //c1->RedrawAxis();

  Double_t CapTime = f1_CapTime->GetParameter(2);
  Double_t CapTimeErr = f1_CapTime->GetParError(2);

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.05);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{FHC 1R #mu sample (#nu_{#mu}#rightarrow#nu_{#mu})}","");
  legend1 -> AddEntry(h1_TrueCapTime_numu, "0.01% Gd MC", "L");
  legend1 -> AddEntry(f1_CapTime, "A*(1-e^{-B*t})*exp(-x/C)+D", "L");
  legend1 -> AddEntry((TObject*)0,TString::Format("#kern[-0.2]{Capture time = %.1f #pm %.1f #musec}", CapTime, CapTimeErr),"");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif

  /////////// Reco Capture Time //////////
#if 0
  //TH1F* h1_RecoCapTime = new TH1F("h1_RecoCapTime", "Reco Captrued Time; Reconstructed Capture Time [#mu sec]; Number of Events", 250, 0, 535);
  TH1F* h1_RecoCapTime = new TH1F("h1_RecoCapTime", "Reco Captrued Time; Reconstructed Capture Time [#mu sec]; Number of Events", 40, 0, 20);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Accnoise_numu, 1.);
  h1_RecoCapTime -> Add(h1_RecoCapTime_dcye_numu, 1.);
  h1_RecoCapTime -> Add(h1_RecoCapTime_H_numu, 1.);
  h1_RecoCapTime -> Add(h1_RecoCapTime_Gd_numu, 1.);
  h1_RecoCapTime -> SetLineColor(kTeal+7);
  h1_RecoCapTime -> SetLineWidth(2);
  h1_RecoCapTime -> SetStats(0);
  h1_RecoCapTime -> Fit(f1_CapTime);

  Double_t tot_Reco_H  = h1_RecoCapTime_H_numu->Integral();
  Double_t tot_Reco_Gd = h1_RecoCapTime_Gd_numu->Integral();
  //h1_RecoCapTime_H_numu  -> Scale(1./(tot_Reco_H+tot_Reco_Gd));
  //h1_RecoCapTime_Gd_numu -> Scale(1./(tot_Reco_H+tot_Reco_Gd));
  //h1_RecoCapTime_H_numu  -> Scale(1./tot_True);
  //h1_RecoCapTime_Gd_numu -> Scale(1./tot_True);

  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  c1 -> SetGrid();
  hs_RecoCapTime_numu -> Draw();
  //h1_TrueCapTime_numu -> Draw("SAME");
  //f1_CapTime -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.87, 0.87);
  legend1 -> SetTextSize(0.035);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Truth #nu CCQE}","");
  legend1 -> AddEntry(h1_RecoCapTime_Accnoise_numu, "Acc. noise", "F");
  legend1 -> AddEntry(h1_RecoCapTime_dcye_numu, "Decay-e", "F");
  legend1 -> AddEntry(h1_RecoCapTime_H_numu, "H-n signal", "F");
  legend1 -> AddEntry(h1_RecoCapTime_Gd_numu, "Gd-n signal", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


  TF1* f1_DcyTime = new TF1("f", "[0] * exp(-x/[1]) + [2]", 0, 20);
  f1_DcyTime -> SetParameter(0, 500);
  f1_DcyTime -> SetParameter(1, 10);
  f1_DcyTime -> SetParameter(2, 10);
  f1_DcyTime -> SetLineColor(kViolet+2);


  /////////// Only noise study //////////
#if 0
  TH1F* h1_NHits_Accnoise_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type0");
  h1_NHits_Accnoise_numu -> SetFillColor(kGray+2);
  h1_NHits_Accnoise_numu -> SetLineColor(kGray+2);
  TH1F* h1_NHits_dcye_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type1");
  h1_NHits_dcye_numu -> SetFillColor(kYellow-3);
  h1_NHits_dcye_numu -> SetLineColor(kYellow-3);
  TH1F* h1_NHits_H_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type2");
  h1_NHits_H_numu -> SetFillColor(kAzure-4);
  h1_NHits_H_numu -> SetLineColor(kAzure-4);
  TH1F* h1_NHits_Gd_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_N50_type3");
  h1_NHits_Gd_numu -> SetFillColor(kTeal-5);
  h1_NHits_Gd_numu -> SetLineColor(kTeal-5);

  THStack* hs_NHits_numu = new THStack("hs_NHits_numu", "NHits; NHits; Number of Events");
  hs_NHits_numu -> Add(h1_NHits_Accnoise_numu);
  hs_NHits_numu -> Add(h1_NHits_dcye_numu);
  hs_NHits_numu -> Add(h1_NHits_H_numu);
  hs_NHits_numu -> Add(h1_NHits_Gd_numu);


  //TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  //c1 -> SetGrid();
  //hs_RecoCapTime_numu -> Draw();
  //h1_TrueCapTime_numu -> Draw("SAME");
  //f1_DcyTime -> Draw("SAME");
  //c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.87, 0.87);
  legend1 -> SetTextSize(0.035);
  //legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Truth #nu CCQE}","");
  legend1 -> AddEntry(h1_RecoCapTime_Accnoise_numu, "Acc. noise", "F");
  legend1 -> AddEntry(h1_RecoCapTime_dcye_numu, "Decay-e", "F");
  legend1 -> AddEntry(h1_RecoCapTime_H_numu, "H-n signal", "F");
  legend1 -> AddEntry(h1_RecoCapTime_Gd_numu, "Gd-n signal", "F");
  legend1 -> SetFillColor(0);
  //legend1 -> Draw();

  TCanvas* c2 = new TCanvas("c2", "c2", 700, 500);
  c2 -> SetGrid();
  hs_NHits_numu -> Draw();
  c2->RedrawAxis();
  legend1 -> Draw();
#endif

}
