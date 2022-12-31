
void NeutronDistance() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex.root");

  TH1F* h1_truedistance_mu_n = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_mu_n");
  TH1F* h1_truedistance_nu_n = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_nu_n");
  //h1_truedistance_mu_n -> SetFillColor(kCyan-5);
  //h1_truedistance_nu_n -> SetFillColor(kRed-8);
  h1_truedistance_nu_n -> SetStats(0);
  h1_truedistance_nu_n -> SetYTitle("Number of Events");

  THStack* hs_distance = new THStack("hs_distance", "Truth Distance; Truth Distance[m]; Number of Events");
  hs_distance -> Add(h1_truedistance_nu_n);
  hs_distance -> Add(h1_truedistance_mu_n);

  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  //hs_distance -> Draw();
  h1_truedistance_nu_n -> Draw("SAME");
  h1_truedistance_mu_n -> Draw("SAME");
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.8);
  legend1 -> SetTextSize(0.04);
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_truedistance_nu_n, "Prm vtx vs n cap vtx", "L");
  legend1 -> AddEntry(h1_truedistance_mu_n, "Prm vtx vs #mu cap vtx", "L");
  //legend1 -> AddEntry(h1_truedistance_mu_gamma, "#gamma from #mu^{-} captures", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
}