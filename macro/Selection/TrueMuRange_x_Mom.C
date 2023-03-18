
void TrueMuRange_x_Mom() {

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");

  TH2F* h2_TruePmu_x_TrueRange = (TH2F*)fin->Get("DistanceViewer/h2_TruePmu_x_TrueRange");
  h2_TruePmu_x_TrueRange -> SetYTitle("Truth #mu range [m]");

  TF1* f1_TruePmu_x_TrueRange_LE = new TF1("f1_TruePmu_x_TrueRange_LE", "[0]*x^[1]", 0, 1000);
  f1_TruePmu_x_TrueRange_LE -> SetParameter(0, 1);
  f1_TruePmu_x_TrueRange_LE -> SetParameter(1, 3);
  f1_TruePmu_x_TrueRange_LE -> SetLineWidth(2);
  f1_TruePmu_x_TrueRange_LE -> SetLineColor(kPink-3);

  TF1* f1_TruePmu_x_TrueRange_HE = new TF1("f1_TruePmu_x_TrueRange_HE", "[0]*x", 200, 1000);
  f1_TruePmu_x_TrueRange_HE -> SetParameter(0, 1);
  //f1_TruePmu_x_TrueRange_HE -> SetParameter(1, 3);
  f1_TruePmu_x_TrueRange_HE -> SetLineWidth(2);
  f1_TruePmu_x_TrueRange_HE -> SetLineColor(kPink-3);

#if 0
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  h2_TruePmu_x_TrueRange -> Fit(f1_TruePmu_x_TrueRange_LE, "r");
  //h2_TruePmu_x_TrueRange -> Fit(f1_TruePmu_x_TrueRange_HE, "r");
  h2_TruePmu_x_TrueRange -> Draw("COLZ");
  f1_TruePmu_x_TrueRange_LE -> Draw("SAME");
  //f1_TruePmu_x_TrueRange_HE -> Draw("SAME");
#endif



  TH1F* h1_PrmMuReso = (TH1F*)fin->Get("NeutrinoOscillation/h1_PrmMuMomReso");
  h1_PrmMuReso -> SetLineWidth(2);
  h1_PrmMuReso -> SetLineColor(kViolet+2);

  TF1* f1_PrmMuReso = new TF1("f1_PrmMuReso", "[0]*exp(-(x-[1])**2/(2*[2]**2))", -0.2, 0.2);
  f1_PrmMuReso -> SetParameter(0, 5000);
  f1_PrmMuReso -> SetParameter(1, 0);
  f1_PrmMuReso -> SetParameter(2, 1);
  f1_PrmMuReso -> SetLineWidth(2);
  f1_PrmMuReso -> SetLineColor(kOrange-3);

#if 0
  gStyle->SetOptFit(1111);
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  //std::cout << "Primary muon momentum resolution: " << h1_PrmMuReso->GetRMS() << std::endl;
  h1_PrmMuReso -> SetTitleOffset(1.3, "X");
  h1_PrmMuReso -> SetTitleOffset(1.3, "Y");
  h1_PrmMuReso -> Fit(f1_PrmMuReso);
  h1_PrmMuReso -> Draw();
  f1_PrmMuReso -> Draw("SAME");
#endif


  TH2F* h2_PrmMuEndVtxReso = (TH2F*)fin->Get("NeutrinoOscillation/h2_PrmMuEndVtxReso");
  h2_PrmMuEndVtxReso -> SetStats(0);

#if 1
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  h2_PrmMuEndVtxReso -> SetXTitle("Truth Coordinate [cm]");
  h2_PrmMuEndVtxReso -> SetYTitle("Reco Coordinate [cm]");
  h2_PrmMuEndVtxReso -> SetTitleOffset(1.3, "Y");
  h2_PrmMuEndVtxReso -> Draw("COLZ");
#endif

}