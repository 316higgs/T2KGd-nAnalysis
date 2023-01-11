
void NeutronContribution() {

  TFile* fin_numu = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");

  TH1F* h1_PrmNeutronE_pi0 = (TH1F*)fin_numu->Get("h1_PrmNeutronE_type0");
  TH1F* h1_PrmNeutronE_pip = (TH1F*)fin_numu->Get("h1_PrmNeutronE_type1");
  TH1F* h1_PrmNeutronE_n   = (TH1F*)fin_numu->Get("h1_PrmNeutronE_type2");
  TH1F* h1_PrmNeutronE_p   = (TH1F*)fin_numu->Get("h1_PrmNeutronE_type3");
  h1_PrmNeutronE_n -> SetStats(0);

  TH1F* h1_ScndNeutronE_SI  = (TH1F*)fin_numu->Get("h1_ScndNeutronE_type0");
  TH1F* h1_ScndNeutronE_mu  = (TH1F*)fin_numu->Get("h1_ScndNeutronE_type1");
  TH1F* h1_ScndNeutronE_pip = (TH1F*)fin_numu->Get("h1_ScndNeutronE_type2");
  TH1F* h1_ScndNeutronE_n   = (TH1F*)fin_numu->Get("h1_ScndNeutronE_type3");
  TH1F* h1_ScndNeutronE_p   = (TH1F*)fin_numu->Get("h1_ScndNeutronE_type4");
  h1_ScndNeutronE_SI -> SetStats(0);

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_PrmNeutronE_n   -> Draw("SAME");
  h1_PrmNeutronE_p   -> Draw("SAME");
  h1_PrmNeutronE_pi0 -> Draw("SAME");
  h1_PrmNeutronE_pip -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.47, 0.47, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_PrmNeutronE_n, "Parent = Neutron", "F");
  legend1 -> AddEntry(h1_PrmNeutronE_p, "Parent = Proton", "F");
  legend1 -> AddEntry(h1_PrmNeutronE_pi0, "Parent = #pi^{0}", "F");
  legend1 -> AddEntry(h1_PrmNeutronE_pip, "Parent = #pi^{+}", "F");
  legend1->SetFillColor(0);
  legend1->Draw();

  TCanvas* c2 = new TCanvas("c2", "c2", 900, 700);
  c2 -> SetGrid();
  h1_ScndNeutronE_SI  -> Draw("SAME");
  h1_ScndNeutronE_mu  -> Draw("SAME");
  h1_ScndNeutronE_p   -> Draw("SAME");
  h1_ScndNeutronE_n   -> Draw("SAME");
  h1_ScndNeutronE_pip -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.32, 0.47, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(h1_ScndNeutronE_SI, "Parent = SI Neutron", "F");
  legend2 -> AddEntry(h1_ScndNeutronE_mu, "Parent = #mu^{-}", "F");
  legend2 -> AddEntry(h1_ScndNeutronE_p, "Parent = Proton", "F");
  legend2 -> AddEntry(h1_ScndNeutronE_n, "Parent = Hadronic Decay Neutron", "F");
  legend2 -> AddEntry(h1_ScndNeutronE_pip, "Parent = #pi^{+}", "F");
  legend2->SetFillColor(0);
  legend2->Draw();
}