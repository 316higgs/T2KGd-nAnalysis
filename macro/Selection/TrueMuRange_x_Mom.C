
#define NA 6.0221409
#define FV 22.5
#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC

void TrueMuRange_x_Mom(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << POTSCALE << "x10^21 POT" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC " << POTSCALE << "x10^21 POT" << std::endl;

  //FHC
#if fhcflag
  //TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  //TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");

  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif

  //Normalization
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  //Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) );
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu         = 190292;
  Double_t GenN_numubar_x_numubar   = 190909;
  std::cout << "ExpN_numu_x_numu = " << ExpN_numu_x_numu << std::endl;
  std::cout << "GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "ExpN_numubar_x_numubar = " << ExpN_numubar_x_numubar << std::endl;
  std::cout << "GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;


  //////////////////////////////////////////////////
  //  True mu stopping range vs true mu momentum
  //////////////////////////////////////////////////
  TH2F* h2_TruePmu_x_TrueRange = (TH2F*)fin_numu->Get("DistanceViewer/h2_TruePmu_x_TrueRange");
  h2_TruePmu_x_TrueRange -> SetYTitle("Truth #mu range [m]");

  TF1* f1_TruePmu_x_TrueRange_LE = new TF1("f1_TruePmu_x_TrueRange_LE", "[0]*x^[1]", 0, 200);
  f1_TruePmu_x_TrueRange_LE -> SetParameter(0, 1);
  f1_TruePmu_x_TrueRange_LE -> SetParameter(1, 3);
  f1_TruePmu_x_TrueRange_LE -> SetLineWidth(2);
  f1_TruePmu_x_TrueRange_LE -> SetLineColor(kPink-3);

  TF1* f1_TruePmu_x_TrueRange_HE = new TF1("f1_TruePmu_x_TrueRange_HE", "[0]*x+[1]", 200, 1000);
  f1_TruePmu_x_TrueRange_HE -> SetParameter(1, 10);
  f1_TruePmu_x_TrueRange_HE -> SetParameter(1, 5);
  f1_TruePmu_x_TrueRange_HE -> SetLineWidth(2);
  f1_TruePmu_x_TrueRange_HE -> SetLineColor(kPink-3);
  f1_TruePmu_x_TrueRange_HE -> SetLineStyle(9);

#if 0
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  std::cout << "Low energy fit" << std::endl;
  h2_TruePmu_x_TrueRange -> Fit(f1_TruePmu_x_TrueRange_LE, "r");
  std::cout << " -------------------------------- " << std::endl;
  std::cout << "High energy fit" << std::endl;
  h2_TruePmu_x_TrueRange -> Fit(f1_TruePmu_x_TrueRange_HE, "r");
  h2_TruePmu_x_TrueRange -> Draw("COLZ");
  f1_TruePmu_x_TrueRange_LE -> Draw("SAME");
  f1_TruePmu_x_TrueRange_HE -> Draw("SAME");

  TLegend* legend1 = new TLegend(0.13, 0.6, 0.6, 0.89);
  legend1 -> SetTextSize(0.045);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.25]{FHC C1-C4 + #decay-e=1 (CC)}","");
  legend1 -> AddEntry(f1_TruePmu_x_TrueRange_LE, "A*P_{#mu}^{B} for P_{#mu} < 200 MeV", "L");
  legend1 -> AddEntry(f1_TruePmu_x_TrueRange_HE, "A*P_{#mu}+B for P_{#mu} #geq 200 MeV", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();
#endif


  //////////////////////////////////////////////////
  //  Reco mu stopping range vs reco mu momentum
  //////////////////////////////////////////////////
  TH2F* h2_RecoPmu_x_RecoRange = (TH2F*)fin_numu->Get("DistanceViewer/h2_RecoPmu_x_RecoRange");
  h2_RecoPmu_x_RecoRange -> SetYTitle("Reco #mu range [m]");

#if 0
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  h2_RecoPmu_x_RecoRange -> Draw("COLZ");
#endif


  //////////////////////////////////////////////////
  //  Primary muon momentum resolution
  //////////////////////////////////////////////////
  TH1F* h1_PrmMuReso = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_PrmMuMomReso");
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


  //////////////////////////////////////////////////
  //  True mu end vertex vs reco mu end vertex
  //////////////////////////////////////////////////
  TH2F* h2_PrmMuEndVtxReso = (TH2F*)fin_numu->Get("NeutrinoOscillation/h2_PrmMuEndVtxReso");
  h2_PrmMuEndVtxReso -> SetStats(0);

#if 0
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  c -> SetGrid();
  h2_PrmMuEndVtxReso -> SetXTitle("Truth Coordinate [cm]");
  h2_PrmMuEndVtxReso -> SetYTitle("Reco Coordinate [cm]");
  h2_PrmMuEndVtxReso -> SetTitleOffset(1.3, "Y");
  h2_PrmMuEndVtxReso -> Draw("COLZ");
#endif


  //////////////////////////////////////////////////
  //  Primary mu stopping vertex resolution
  //////////////////////////////////////////////////
  TH1F* h1_PrmMuEndVtxReso_numu    = (TH1F*)fin_numu->Get("NeutrinoOscillation/h1_PrmMuEndVtxReso");
  TH1F* h1_PrmMuEndVtxReso_numubar = (TH1F*)fin_numubar->Get("NeutrinoOscillation/h1_PrmMuEndVtxReso");
  h1_PrmMuEndVtxReso_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PrmMuEndVtxReso_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  
  TH1F* h1_PrmMuEndVtxReso = new TH1F("h1_PrmMuEndVtxReso", "Primary #mu End Vertex Resolution; d_{Reco. vs True}[cm]; Number of Events", 2000, 0, 200);
  h1_PrmMuEndVtxReso -> Add(h1_PrmMuEndVtxReso_numu, 1.);
  h1_PrmMuEndVtxReso -> Add(h1_PrmMuEndVtxReso_numubar, 1.);
  h1_PrmMuEndVtxReso -> SetLineColor(kViolet-7);
  h1_PrmMuEndVtxReso -> SetLineWidth(2);
  h1_PrmMuEndVtxReso -> SetStats(0);

  h1_PrmMuEndVtxReso -> SetLineWidth(2);
  h1_PrmMuEndVtxReso -> SetLineColor(kViolet+2);
  Double_t AllEvents = h1_PrmMuEndVtxReso -> Integral();
  float start    = 0.;    // start value
  float maximum  = 200.;  // histo end [cm]
  const int BINS = 2000;  // Number of bins
  float interval = (maximum - start)/BINS;   // bin witdh [cm]
  int   binnumber = h1_PrmMuEndVtxReso->FindBin(start); // get bin number
  float OneSigmaEvents = 0.;
  float tmpvalue = 999.;
  float OneSigmaReso = 999.;
  for (int ibin=0; ibin<BINS; ibin++) {
    float thisvalue = start+ibin*interval; // value of this bin
    OneSigmaEvents += h1_PrmMuEndVtxReso->GetBinContent(binnumber);
    if (std::fabs(OneSigmaEvents/AllEvents - 0.683) < tmpvalue) {
      tmpvalue     = std::fabs(OneSigmaEvents/AllEvents - 0.683);
      OneSigmaReso = thisvalue;
    }
    binnumber++;
  }
  std::cout << "OneSigmaReso: " << OneSigmaReso << " cm" << std::endl;

  float FrameMaximum = 6.;
  float y[2] = {0., FrameMaximum+10.};
  float x[2] = {OneSigmaReso, OneSigmaReso};
  TGraph* g_onesigma = new TGraph(2, x, y);
  g_onesigma -> SetLineWidth(2);
  g_onesigma -> SetLineColor(kViolet-8);
  g_onesigma -> SetLineStyle(7);

#if 1
  TCanvas* c = new TCanvas("c", "c", 900, 700);
  c -> SetGrid();
  h1_PrmMuEndVtxReso -> Draw("SAME");
  g_onesigma   -> Draw("SAME");
  c -> RedrawAxis();
#endif

}