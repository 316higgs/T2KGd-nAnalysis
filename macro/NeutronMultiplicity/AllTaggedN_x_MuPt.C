#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"


#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17


void AllTaggedN_x_MuPt(bool beammode) {

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
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.Nmult.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.newGdMC.Nmult.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.newGdMC.Nmult.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.newGdMC.Nmult.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.newGdMC.Nmult.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.newGdMC.Nmult.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif

  // Normalization factors
  TH1F* h1_skrate_numu_x_numu       = (TH1F*)fin_skrate->Get("skrate_numu_x_numu");
  TH1F* h1_skrate_numu_x_nue        = (TH1F*)fin_skrate->Get("skrate_numu_x_nue");
  TH1F* h1_skrate_numubar_x_numubar = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_numu_bar");
  TH1F* h1_skrate_numubar_x_nuebar  = (TH1F*)fin_skrate->Get("skrate_numu_bar_x_nue_bar");
  TH1F* h1_skrate_nue_x_nue         = (TH1F*)fin_skrate->Get("skrate_nue_x_nue");
  TH1F* h1_skrate_nuebar_x_nuebar   = (TH1F*)fin_skrate->Get("skrate_nue_bar_x_nue_bar");
  Double_t ExpN_numu_x_numu         = h1_skrate_numu_x_numu->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numu_x_nue          = h1_skrate_numu_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_numubar   = h1_skrate_numubar_x_numubar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_numubar_x_nuebar    = h1_skrate_numubar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nue_x_nue           = h1_skrate_nue_x_nue->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t ExpN_nuebar_x_nuebar     = h1_skrate_nuebar_x_nuebar->Integral() * ( (NA*FV*1.e-6) / (50.e-3) ) * POTSCALE;
  Double_t GenN_numu_x_numu       = 63622;
  Double_t GenN_numu_x_nue        = 63538;
  Double_t GenN_numubar_x_numubar = 63444;
  Double_t GenN_numubar_x_nuebar  = 63460;
  Double_t GenN_nue_x_nue         = 63423;
  Double_t GenN_nuebar_x_nuebar   = 63652;
  std::cout << "Misc. factor: " << (NA*FV*1.e-6) / (50.e-3) << std::endl;
  std::cout << "[numu  -> numu ] ExpN_numu_x_numu = " << h1_skrate_numu_x_numu->Integral() << std::endl;
  std::cout << "[numu  -> numu ] GenN_numu_x_numu = " << GenN_numu_x_numu << std::endl;
  std::cout << "[numu  -> numu ] Normalization factor for numu_x_numu      : " << (ExpN_numu_x_numu)/(GenN_numu_x_numu) << std::endl;
  std::cout << "[numu  -> nue  ] ExpN_numu_x_nue = " << h1_skrate_numu_x_nue->Integral() << std::endl;
  std::cout << "[numu  -> nue  ] GenN_numu_x_nue = " << GenN_numu_x_nue << std::endl;
  std::cout << "[numu  -> nue  ] Normalization factor for numu_x_nue       : " << (ExpN_numu_x_nue)/(GenN_numu_x_nue) << std::endl;
  std::cout << "[numub -> numub] ExpN_numubar_x_numubar = " << h1_skrate_numubar_x_numubar->Integral() << std::endl;
  std::cout << "[numub -> numub] GenN_numubar_x_numubar = " << GenN_numubar_x_numubar << std::endl;
  std::cout << "[numub -> numub] Normalization factor for numubar_x_numubar: " << (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) << std::endl;
  std::cout << "[numub -> nueb ] ExpN_numubar_x_nuebar = " << h1_skrate_numubar_x_nuebar->Integral() << std::endl;
  std::cout << "[numub -> nueb ] GenN_numubar_x_nuebar = " << GenN_numubar_x_nuebar << std::endl;
  std::cout << "[numub -> nueb ] Normalization factor for numubar_x_nuebar: " << (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) << std::endl;
  std::cout << "[nue   -> nue  ] ExpN_nue_x_nue = " << h1_skrate_nue_x_nue->Integral() << std::endl;
  std::cout << "[nue   -> nue  ] GenN_nue_x_nue = " << GenN_nue_x_nue << std::endl;
  std::cout << "[nue   -> nue  ] Normalization factor for nue_x_nue: " << (ExpN_nue_x_nue)/(GenN_nue_x_nue) << std::endl;
  std::cout << "[nueb  -> nueb ] ExpN_nuebar_x_nuebar = " << h1_skrate_nuebar_x_nuebar->Integral() << std::endl;
  std::cout << "[nueb  -> nueb ] GenN_nuebar_x_nuebar = " << GenN_nuebar_x_nuebar << std::endl;
  std::cout << "[nueb  -> nueb ] Normalization factor for nuebar_x_nuebar: " << (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) << std::endl;

  
  TString LowPtName  = "NTagAnalysis/h1_TaggedN_LowPt";
  TString HighPtName = "NTagAnalysis/h1_TaggedN_HighPt";

  TH1F* h1_TagN_LowPt_numu      = (TH1F*)fin_numu->Get(LowPtName);
  TH1F* h1_TagN_LowPt_nuesig    = (TH1F*)fin_nuesig->Get(LowPtName);
  TH1F* h1_TagN_LowPt_numubar   = (TH1F*)fin_numubar->Get(LowPtName);
  TH1F* h1_TagN_LowPt_nuebarsig = (TH1F*)fin_nuebarsig->Get(LowPtName);
  TH1F* h1_TagN_LowPt_nuebkg    = (TH1F*)fin_nuebkg->Get(LowPtName);
  TH1F* h1_TagN_LowPt_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(LowPtName);
  h1_TagN_LowPt_numu -> SetStats(0);


  TH1F* h1_TagN_HighPt_numu      = (TH1F*)fin_numu->Get(HighPtName);
  TH1F* h1_TagN_HighPt_nuesig    = (TH1F*)fin_nuesig->Get(HighPtName);
  TH1F* h1_TagN_HighPt_numubar   = (TH1F*)fin_numubar->Get(HighPtName);
  TH1F* h1_TagN_HighPt_nuebarsig = (TH1F*)fin_nuebarsig->Get(HighPtName);
  TH1F* h1_TagN_HighPt_nuebkg    = (TH1F*)fin_nuebkg->Get(HighPtName);
  TH1F* h1_TagN_HighPt_nuebarbkg = (TH1F*)fin_nuebarbkg->Get(HighPtName);
  h1_TagN_LowPt_numu -> SetStats(0);


  /////  Normalizations  //////
#if 1
  h1_TagN_LowPt_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_LowPt_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_LowPt_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_LowPt_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_LowPt_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_LowPt_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_TagN_HighPt_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_TagN_HighPt_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_TagN_HighPt_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_TagN_HighPt_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_TagN_HighPt_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_TagN_HighPt_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif


  TH1F* h1_TagN_LowPt_merge = new TH1F("h1_TagN_LowPt_merge", "", 10, 0, 10);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_nuebarbkg);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_nuebkg);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_nuebarsig);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_numubar);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_nuesig);
  h1_TagN_LowPt_merge -> Add(h1_TagN_LowPt_numu);
  h1_TagN_LowPt_merge -> SetLineColor(kPink-6);
  h1_TagN_LowPt_merge -> SetLineWidth(3);
  h1_TagN_LowPt_merge -> SetStats(0);


  TH1F* h1_TagN_HighPt_merge = new TH1F("h1_TagN_HighPt_merge", "", 10, 0, 10);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_nuebarbkg);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_nuebkg);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_nuebarsig);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_numubar);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_nuesig);
  h1_TagN_HighPt_merge -> Add(h1_TagN_HighPt_numu);
  h1_TagN_HighPt_merge -> SetLineColor(kViolet-7);
  h1_TagN_HighPt_merge -> SetLineWidth(3);
  h1_TagN_HighPt_merge -> SetStats(0);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  h1_TagN_LowPt_merge ->GetYaxis()->SetTitleSize(0.038);
  h1_TagN_LowPt_merge ->GetYaxis()->SetTitleOffset(1.1);
  h1_TagN_LowPt_merge ->GetXaxis()->SetLabelSize(0.045);
  h1_TagN_LowPt_merge ->GetYaxis()->SetLabelSize(0.036);
  h1_TagN_LowPt_merge->GetXaxis()->SetTitle("Number of Tagged Neutrons");
  h1_TagN_LowPt_merge->GetYaxis()->SetTitle("Entries");
  for (int ibin=0; ibin<10; ibin++) h1_TagN_LowPt_merge->GetXaxis()->SetBinLabel(ibin+1, TString::Format("%d", ibin));
  h1_TagN_LowPt_merge  -> Draw();
  h1_TagN_HighPt_merge -> Draw("SAME");
  c1->RedrawAxis();

  TLegend* legend1 = new TLegend(0.45, 0.7, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_TagN_LowPt_merge, "P_{T} < 0.5 GeV", "L");
  legend1 -> AddEntry(h1_TagN_HighPt_merge, "P_{T} #geq 0.5 GeV", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


  /*
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.newGdMC.Nmult.root");

  TH2D* h2_allTaggedN_x_MuPt = (TH2D*)fin->Get("NTagAnalysis/h2_allTaggedN_x_MuPt");
  h2_allTaggedN_x_MuPt -> SetStats(0);
  //h2_allTaggedN_x_MuPt -> GetYaxis()->SetLabelSize(0.045);
  h2_allTaggedN_x_MuPt -> SetTitleOffset(1.1, "Y");
  //h2_allTaggedN_x_MuPt -> GetXaxis()->SetLabelSize(0.045);
  h2_allTaggedN_x_MuPt -> SetTitleOffset(1.2, "X");
  h2_allTaggedN_x_MuPt -> SetXTitle("Reconstructed #mu Transverse Momentum [GeV]");
  h2_allTaggedN_x_MuPt -> SetYTitle("Number of Tagged Neutron");
  h2_allTaggedN_x_MuPt -> GetXaxis()->SetTitleSize(0.04);
  h2_allTaggedN_x_MuPt -> GetYaxis()->SetTitleSize(0.04);
  ((TGaxis*)h2_allTaggedN_x_MuPt->GetYaxis())->SetMaxDigits(3);

  //for (int i=0; i<10; i++) h2_allTaggedN_x_MuPt -> SetBinContent(i+1, TString::Format("%d", i));

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1000, 700);
  c1 -> SetGrid();
  h2_allTaggedN_x_MuPt -> Draw("COLZ");
  */



}