

void CompareNeutronDistance() {
  TFile* fin1 = new TFile("./NeutronDistance_mu_x_n.osc.root");
  TFile* fin2 = new TFile("./NeutronDistance_mu_x_n.osc.Enucut.root");

  TH1F* h1_distance_nu_n_1 = (TH1F*)fin1->Get("h1_distance_nu_n");
  TH1F* h1_distance_mu_n_1 = (TH1F*)fin1->Get("h1_distance_mu_n");

  TH1F* h1_distance_nu_n_2 = (TH1F*)fin2->Get("h1_distance_nu_n");
  TH1F* h1_distance_mu_n_2 = (TH1F*)fin2->Get("h1_distance_mu_n");
  h1_distance_mu_n_2 -> SetLineColor(kRed-10);
  h1_distance_nu_n_2 -> SetLineColor(kBlue-10);

  Double_t tot_distance_nu_n_1 = h1_distance_nu_n_1->Integral();
  h1_distance_nu_n_1 -> Scale(1./tot_distance_nu_n_1);
  Double_t tot_distance_nu_n_2 = h1_distance_nu_n_2->Integral();
  h1_distance_nu_n_2 -> Scale(1./tot_distance_nu_n_2);
  Double_t tot_distance_mu_n_1 = h1_distance_mu_n_1->Integral();
  h1_distance_mu_n_1 -> Scale(1./tot_distance_mu_n_1);
  Double_t tot_distance_mu_n_2 = h1_distance_mu_n_2->Integral();
  h1_distance_mu_n_2 -> Scale(1./tot_distance_mu_n_2);

  h1_distance_mu_n_1 -> SetYTitle("Area Normalized");

  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  h1_distance_mu_n_1 -> Draw("SAME");
  h1_distance_mu_n_2 -> Draw("SAME");
  h1_distance_nu_n_1 -> Draw("SAME");
  h1_distance_nu_n_2 -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.15, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_distance_nu_n_1, "#mu decay - n(from #nu) capture vtx", "L");
  legend1 -> AddEntry(h1_distance_nu_n_2, "#mu decay - n(from #nu) capture vtx (E_{#nu}<1GeV)", "L");
  legend1 -> AddEntry(h1_distance_mu_n_1, "#mu capture - n(from #mu) capture vtx", "L");
  legend1 -> AddEntry(h1_distance_mu_n_2, "#mu capture - n(from #mu) capture vtx (E_{#nu}<1GeV)", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
}