
#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17
#define SAMPLES 6

void CalPOTnorm() {
  
  TString OutDir = "../../output/fhc/";
  TString BeamMode = "fhc";
  TString OscMode[SAMPLES] = {"numu_x_numu", "numu_x_nue", "numubar_x_numubar", 
                              "numubar_x_nuebar", "nue_x_nue", "nuebar_x_nuebar"};
  TString Prefix = "newGdMC.bonsaikeras_ToF";
  std::cout << OutDir+BeamMode+"."+OscMode[0]+"."+Prefix+".root" << std::endl;
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras_ToF.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras_ToF.root");
  
  TFile* fin_skrate    = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
}