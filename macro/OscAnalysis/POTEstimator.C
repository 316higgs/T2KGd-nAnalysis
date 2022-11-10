

void POTEstimator() {
  //FHC
  TFile* fin_numu_x_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar_x_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.root");
  TFile* fin_numu_x_nue    = new TFile("../../output/fhc/fhc.numu_x_nue.etagON.cut1.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");

  //Normalization by 1e21 POT
  std::cout << "[### channel: numu -> numu ###]" << std::endl;
  //### STEP1: Get the number of neutrino interaction in FV for FHC(or RHC) 10^21 POT
  TH1F* h1_skrate_numu_x_numu = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  //Double_t Ne21_numu_x_numu   = h1_skrate_numu_x_numu->Integral();
  Double_t Ne21_numu_x_numu   = 1373.8715753;
  std::cout << "  Ne21 = " << Ne21_numu_x_numu << std::endl;

  //### STEP2: Get the number of neutrino interaction in FV at Gd MC
  //           (Calculated by wallv > 2m)
  Double_t Ngen_numu_x_numu   = 190292;
  std::cout << "  Ngen = " << Ngen_numu_x_numu << std::endl;

  //### STEP3: Get the normalization factor Ne21/Ngen
  Double_t norm_numu_x_numu = (Ne21_numu_x_numu)/(Ngen_numu_x_numu);
  std::cout << "  Normalization factor for numu_x_numu: " << norm_numu_x_numu << std::endl;
  TH1F* h1_Erec_numu_x_numu = (TH1F*)fin_numu_x_numu->Get("NeutrinoOscillation/h1_All_OscProb");
  Double_t Ngen_1Rmu_numu_x_numu = h1_Erec_numu_x_numu->Integral();
  //Double_t Ngen_1Rmu_numu_x_numu = 80522;
  std::cout << "  Number of 1Rmu @ Gd MC    : " << Ngen_1Rmu_numu_x_numu << std::endl;

  //### STEP4: Get the number of 1Rmu events(for each channel) at Gd MC with FHC(or RHC) 10^21 POT data
  h1_Erec_numu_x_numu -> Scale(norm_numu_x_numu);
  Double_t Ne21_1Rmu_numu_x_numu = h1_Erec_numu_x_numu->Integral();
  std::cout << "  Number of 1Rmu @ 10^21 POT: " << Ne21_1Rmu_numu_x_numu << std::endl;

  //--------------------------------------

  std::cout << "[### channel: numubar -> numubar ###]" << std::endl;
  //### STEP1: Get the number of neutrino interaction in FV for FHC(or RHC) 10^21 POT
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  //Double_t Ne21_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral();
  Double_t Ne21_numubar_x_numubar   = 48.4951744134;
  std::cout << "  Ne21 = " << Ne21_numubar_x_numubar << std::endl;

  //### STEP2: Get the number of neutrino interaction in FV at Gd MC
  //           (Calculated by wallv > 2m)
  Double_t Ngen_numubar_x_numubar   = 190909;
  std::cout << "  Ngen = " << Ngen_numubar_x_numubar << std::endl;

  //### STEP3: Get the normalization factor Ne21/Ngen
  Double_t norm_numubar_x_numubar = (Ne21_numubar_x_numubar)/(Ngen_numubar_x_numubar);
  std::cout << "  Normalization factor for numubar_x_numubar: " << norm_numubar_x_numubar << std::endl;
  TH1F* h1_Erec_numubar_x_numubar = (TH1F*)fin_numubar_x_numubar->Get("NeutrinoOscillation/h1_All_OscProb");
  //TH1F* h1_Erec_numubar_x_numubar = (TH1F*)fin_numubar_x_numubar->Get("NeutrinoOscillation/h1_AllEnureco");
  Double_t Ngen_1Rmu_numubar_x_numubar = h1_Erec_numubar_x_numubar->Integral();
  //Double_t Ngen_1Rmu_numubar_x_numubar = 71169;
  std::cout << "  Number of 1Rmu @ Gd MC    : " << Ngen_1Rmu_numubar_x_numubar << std::endl;

  //### STEP4: Get the number of 1Rmu events(for each channel) at Gd MC with FHC(or RHC) 10^21 POT data
  h1_Erec_numubar_x_numubar -> Scale(norm_numubar_x_numubar);
  Double_t Ne21_1Rmu_numubar_x_numubar = h1_Erec_numubar_x_numubar->Integral();
  std::cout << "  Number of 1Rmu @ 10^21 POT: " << Ne21_1Rmu_numubar_x_numubar << std::endl;

  //--------------------------------------

  std::cout << "[### channel: numu -> nue ###]" << std::endl;
  //### STEP1: Get the number of neutrino interaction in FV for FHC(or RHC) 10^21 POT
  TH1F* h1_skrate_numu_x_nue = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  Double_t Ne21_numu_x_nue   = h1_skrate_numu_x_nue->Integral();
  std::cout << "  Ne21 = " << Ne21_numu_x_nue << std::endl;

  //### STEP2: Get the number of neutrino interaction in FV at Gd MC
  //           (Calculated by wallv > 2m)
  Double_t Ngen_numu_x_nue   = 190548;
  std::cout << "  Ngen = " << Ngen_numu_x_nue << std::endl;

  //### STEP3: Get the normalization factor Ne21/Ngen
  Double_t norm_numu_x_nue = (Ne21_numu_x_nue)/(Ngen_numu_x_nue);
  std::cout << "  Normalization factor for numu_x_nue: " << norm_numu_x_nue << std::endl;
  TH1F* h1_Erec_numu_x_nue = (TH1F*)fin_numu_x_nue->Get("NeutrinoOscillation/h1_All_OscProb");
  Double_t Ngen_1Rmu_numu_x_nue = h1_Erec_numu_x_nue->Integral();
  //Double_t Ngen_1Rmu_numu_x_numu = 80522;
  std::cout << "  Number of 1Rmu @ Gd MC    : " << Ngen_1Rmu_numu_x_nue << std::endl;

  //### STEP4: Get the number of 1Rmu events(for each channel) at Gd MC with FHC(or RHC) 10^21 POT data
  h1_Erec_numu_x_nue -> Scale(norm_numu_x_nue);
  Double_t Ne21_1Rmu_numu_x_nue = h1_Erec_numu_x_nue->Integral();
  std::cout << "  Number of 1Rmu @ 10^21 POT: " << Ne21_1Rmu_numu_x_nue << std::endl;

  //--------------------------------------

  //### STEP5: Get the number of 1Rmu events at Gd MC with FHC(or RHC) 10^21 POT data
  Double_t Ngen_1Rmu = Ngen_1Rmu_numu_x_numu
                     + Ngen_1Rmu_numubar_x_numubar;
                     //+ Ngen_1Rmu_numu_x_nue;
  Double_t Ne21_1Rmu = Ne21_1Rmu_numu_x_numu
                     + Ne21_1Rmu_numubar_x_numubar;
                     //+ Ne21_1Rmu_numu_x_nue;
  std::cout << "[### Total ###]" << std::endl;
  std::cout << "  Number of 1Rmu @ Gd MC    : " << Ngen_1Rmu << std::endl;
  std::cout << "  Number of 1Rmu @ 10^21 POT: " << Ne21_1Rmu << std::endl;

  Double_t targetPOT = 1.9664;
  Double_t scale = (targetPOT*Ne21_1Rmu)/Ngen_1Rmu;
  std::cout << "  POT scaling factor for " << targetPOT << " POT: " << scale << std::endl;

}