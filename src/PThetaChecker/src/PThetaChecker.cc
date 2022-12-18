#include "PThetaChecker.h"
#include "TH1D.h"

void PThetaChecker::SetHistoFrame() {
  for (int i=0; i<SAMPLE; i++) {
    h1_leptonp[i]     = new TH1F(TString::Format("h1_leptonp_sample%d", i), "Lepton Momentum; Lepton Momentum[GeV]; Number of Events", 60, 0., 3.);
    h1_leptontheta[i] = new TH1F(TString::Format("h1_leptontheta_sample%d", i), "Lepton Angle; Lepton Angle cos#theta; Number of Events", 100, -1, 1);
    h1_Enu[i]         = new TH1F(TString::Format("h1_Enu_sample%d", i), "Reco. Neutrino Energy; Reconstructed Neutrino Energy[GeV]; Number of Neutrino Events", 60, 0, 3);
  }
}

void PThetaChecker::SetHistoFormat() {
  for (int i=0; i<SAMPLE; i++) {
    switch (i) {
      case 0:
        h1_leptonp[i]     -> SetLineColor(kSpring-8);
        h1_leptonp[i]     -> SetFillColor(kSpring-8);
        h1_leptontheta[i] -> SetLineColor(kSpring-8);
        h1_leptontheta[i] -> SetFillColor(kSpring-8);
        h1_Enu[i]         -> SetLineColor(kSpring-8);
        h1_Enu[i]         -> SetFillColor(kSpring-8);
        break;
      case 1:
        h1_leptonp[i]     -> SetLineColor(kRed-7);
        h1_leptonp[i]     -> SetFillColor(kRed-7);
        h1_leptontheta[i] -> SetLineColor(kRed-7);
        h1_leptontheta[i] -> SetFillColor(kRed-7);
        h1_Enu[i]         -> SetLineColor(kRed-7);
        h1_Enu[i]         -> SetFillColor(kRed-7);
        break;
      case 2:
        h1_leptonp[i]     -> SetLineColor(kViolet+2);
        h1_leptonp[i]     -> SetFillColor(kViolet+2);
        h1_leptontheta[i] -> SetLineColor(kViolet+2);
        h1_leptontheta[i] -> SetFillColor(kViolet+2);
        h1_Enu[i]         -> SetLineColor(kViolet+2);
        h1_Enu[i]         -> SetFillColor(kViolet+2);
        break;
    }
  }
}


float PThetaChecker::GetRecoEnu(CC0PiNumu* numu, int sampleID) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float Enu = numu->var<float>("erec");
  if (sampleID==2) h1_Enu[0] -> Fill(Enu/1000.); // No NTag separation
  if (sampleID==1) h1_Enu[1] -> Fill(Enu/1000.); // w/  TagN
  if (sampleID==0) h1_Enu[2] -> Fill(Enu/1000.); // w/o TagN
  return Enu;
}


void PThetaChecker::cdPThetaChecker(TFile* fout) {
  fout -> mkdir("PThetaChecker");
  fout -> cd("PThetaChecker");
}

void PThetaChecker::WritePlots() {
  for (int i=0; i<SAMPLE; i++) {
    h1_Enu[i] -> Write();
  }
}
