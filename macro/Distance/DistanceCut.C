
void DistanceCut() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.ndistance.root");

  //TH1F* h1_truedistance = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_particle");
  TH1F* h1_truedistance_mu_gamma = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_mu_gamma");
  TH1F* h1_truedistance_mu_n     = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_mu_n");
  TH1F* h1_truedistance_nu_n     = (TH1F*)fin->Get("DistanceViewer/h1_truedistance_nu_n");
  h1_truedistance_mu_gamma -> SetFillColor(kOrange-2);
  h1_truedistance_mu_n     -> SetFillColor(kCyan-5);
  h1_truedistance_nu_n     -> SetFillColor(kRed-8);


  THStack* hs_distance = new THStack("hs_distance", "Truth Distance; Truth Distance[m]; Number of Events");
  hs_distance -> Add(h1_truedistance_nu_n);
  hs_distance -> Add(h1_truedistance_mu_n);
  hs_distance -> Add(h1_truedistance_mu_gamma);

  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  hs_distance -> Draw();

  TLegend* legend1 = new TLegend(0.35, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_truedistance_nu_n, "Neutrons from #nu interactions", "F");
  legend1 -> AddEntry(h1_truedistance_mu_n, "Neutrons from #mu^{-} captures", "F");
  legend1 -> AddEntry(h1_truedistance_mu_gamma, "#gamma from #mu^{-} captures", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
}