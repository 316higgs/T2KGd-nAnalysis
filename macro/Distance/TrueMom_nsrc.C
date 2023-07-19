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


void TrueMom_nsrc(bool beammode) {

  int fhcflag = 1;
  int rhcflag = 0;
  if (!beammode) {
    std::cout << "[### Beam mode ###] RHC" << std::endl;
    fhcflag = 0;
    rhcflag = 1;
  }
  else std::cout << "[### Beam mode ###] FHC" << std::endl;


  //FHC
#if fhcflag
  TFile* fin_numu      = new TFile("../../output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root");
  TFile* fin_nuesig    = new TFile("../../output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root");
  TFile* fin_numubar   = new TFile("../../output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root");
  TFile* fin_nuebarsig = new TFile("../../output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root");
  TFile* fin_nuebkg    = new TFile("../../output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root");
  TFile* fin_nuebarbkg = new TFile("../../output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root");

  TFile* fin_skrate  = new TFile("/disk03/usr8/sedi/NEUTvect_5.6.3/skrate/fhc_sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.etagON.cut1.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.etagON.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
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
  Double_t GenN_numubar_x_nuebar  = 63463;
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

#if 1
  TH1F* h1_PrmFSI_numu    = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_numu -> SetStats(0);

  TH1F* h1_PrmFSI_nuesig    = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_nuesig  = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_nuesig = (TH1F*)fin_nuesig->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_nuesig -> SetStats(0);

  TH1F* h1_PrmFSI_numubar    = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_numubar -> SetStats(0);

  TH1F* h1_PrmFSI_nuebarsig     = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_nuebarsig   = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_nuebarsig  = (TH1F*)fin_nuebarsig->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_nuebarsig -> SetStats(0);

  TH1F* h1_PrmFSI_nuebkg    = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_nuebkg  = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_nuebkg = (TH1F*)fin_nuebkg->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_nuebkg -> SetStats(0);

  TH1F* h1_PrmFSI_nuebarbkg    = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_GenBefSIMom");
  TH1F* h1_SI_nuebarbkg  = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_GenSIMom");
  //TH1F* h1_MuCap_nuebarbkg = (TH1F*)fin_nuebarbkg->Get("NTagAnalysis/h1_truedistance_MuCapn");
  h1_PrmFSI_nuebarbkg -> SetStats(0);
#endif

  h1_PrmFSI_numu -> SetLineColor(kAzure-9);
  h1_PrmFSI_numu -> SetFillColor(kAzure-9);
  h1_SI_numu     -> SetLineColor(kViolet-8);
  h1_SI_numu     -> SetFillColor(kViolet-8);
  //h1_MuCap_numu  -> SetLineColor(kSpring+5);
  //h1_MuCap_numu  -> SetFillColor(kSpring+5);

  h1_PrmFSI_nuesig -> SetLineColor(kAzure-9);
  h1_PrmFSI_nuesig -> SetFillColor(kAzure-9);
  h1_SI_nuesig     -> SetLineColor(kViolet-8);  
  h1_SI_nuesig     -> SetFillColor(kViolet-8);
  //h1_MuCap_nuesig  -> SetLineColor(kSpring+5);
  //h1_MuCap_nuesig  -> SetFillColor(kSpring+5);

  h1_PrmFSI_numubar -> SetLineColor(kAzure-9);
  h1_PrmFSI_numubar -> SetFillColor(kAzure-9);
  h1_SI_numubar     -> SetLineColor(kViolet-8);
  h1_SI_numubar     -> SetFillColor(kViolet-8);
  //h1_MuCap_numubar  -> SetLineColor(kSpring+5);
  //h1_MuCap_numubar  -> SetFillColor(kSpring+5);

  h1_PrmFSI_nuebarsig -> SetLineColor(kAzure-9);
  h1_PrmFSI_nuebarsig -> SetFillColor(kAzure-9);
  h1_SI_nuebarsig     -> SetLineColor(kViolet-8);
  h1_SI_nuebarsig     -> SetFillColor(kViolet-8);
  //h1_MuCap_nuebarsig  -> SetLineColor(kSpring+5);
  //h1_MuCap_nuebarsig  -> SetFillColor(kSpring+5);

  h1_PrmFSI_nuebkg -> SetLineColor(kAzure-9);
  h1_PrmFSI_nuebkg -> SetFillColor(kAzure-9);
  h1_SI_nuebkg     -> SetLineColor(kViolet-8);
  h1_SI_nuebkg     -> SetFillColor(kViolet-8);
  //h1_MuCap_nuebkg  -> SetLineColor(kSpring+5);
  //h1_MuCap_nuebkg  -> SetFillColor(kSpring+5);

  h1_PrmFSI_nuebarbkg -> SetLineColor(kAzure-9);
  h1_PrmFSI_nuebarbkg -> SetFillColor(kAzure-9);
  h1_SI_nuebarbkg     -> SetLineColor(kViolet-8);
  h1_SI_nuebarbkg     -> SetFillColor(kViolet-8);
  //h1_MuCap_nuebarbkg  -> SetLineColor(kSpring+5);
  //h1_MuCap_nuebarbkg  -> SetFillColor(kSpring+5);

  /////  Normalizations  //////
#if 1
  h1_PrmFSI_numu         -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_PrmFSI_nuesig       -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_PrmFSI_numubar      -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_PrmFSI_nuebarsig    -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_PrmFSI_nuebkg       -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_PrmFSI_nuebarbkg    -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  h1_SI_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_SI_nuesig     -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  h1_SI_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_SI_nuebarsig  -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  h1_SI_nuebkg     -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  h1_SI_nuebarbkg  -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );

  //h1_MuCap_numu      -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  //h1_MuCap_nuesig    -> Scale( (ExpN_numu_x_nue)/(GenN_numu_x_nue) );
  //h1_MuCap_numubar   -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  //h1_MuCap_nuebarsig -> Scale( (ExpN_numubar_x_nuebar)/(GenN_numubar_x_nuebar) );
  //h1_MuCap_nuebkg    -> Scale( (ExpN_nue_x_nue)/(GenN_nue_x_nue) );
  //h1_MuCap_nuebarbkg -> Scale( (ExpN_nuebar_x_nuebar)/(GenN_nuebar_x_nuebar) );
#endif

  /////  Merged #Selected Neutrinos  //////
  THStack* hs_Mom = new THStack("hs_Mom", "");
#if fhcflag
  //hs_Mom -> Add(h1_MuCap_nuebarbkg);
  //hs_Mom -> Add(h1_MuCap_nuebkg);
  //hs_Mom -> Add(h1_MuCap_nuebarsig);
  //hs_Mom -> Add(h1_MuCap_nuesig);
  //hs_Mom -> Add(h1_MuCap_numubar);
  //hs_Mom -> Add(h1_MuCap_numu);

  hs_Mom -> Add(h1_SI_nuebarbkg);
  hs_Mom -> Add(h1_SI_nuebkg);
  hs_Mom -> Add(h1_SI_nuebarsig);
  hs_Mom -> Add(h1_SI_nuesig);
  hs_Mom -> Add(h1_SI_numubar);
  hs_Mom -> Add(h1_SI_numu);

  hs_Mom -> Add(h1_PrmFSI_nuebarbkg);
  hs_Mom -> Add(h1_PrmFSI_nuebkg);
  hs_Mom -> Add(h1_PrmFSI_nuebarsig);
  hs_Mom -> Add(h1_PrmFSI_nuesig);
  hs_Mom -> Add(h1_PrmFSI_numubar);
  hs_Mom -> Add(h1_PrmFSI_numu);
#endif

  // 1D hist for each neutron source
  /*TH1F* h1_PrmFSI = new TH1F("h1_PrmFSI", "", 10, 0, 5);
  h1_PrmFSI -> SetLineColor(kAzure-9);
  h1_PrmFSI -> SetStats(0);
  h1_PrmFSI -> SetLineWidth(3);
  h1_PrmFSI -> Add(h1_PrmFSI_nuebarbkg);
  h1_PrmFSI -> Add(h1_PrmFSI_nuebkg);
  h1_PrmFSI -> Add(h1_PrmFSI_nuebarsig);
  h1_PrmFSI -> Add(h1_PrmFSI_nuesig);
  h1_PrmFSI -> Add(h1_PrmFSI_numubar);
  h1_PrmFSI -> Add(h1_PrmFSI_numu);
  Double_t tot_PrmFSI = h1_PrmFSI->Integral();
  h1_PrmFSI -> Scale(1./tot_PrmFSI);

  TH1F* h1_SI = new TH1F("h1_SI", "", 10, 0, 5);
  h1_SI -> SetLineColor(kViolet-8);
  h1_SI -> SetStats(0);
  h1_SI -> SetLineWidth(3);
  h1_SI -> Add(h1_SI_nuebarbkg);
  h1_SI -> Add(h1_SI_nuebkg);
  h1_SI -> Add(h1_SI_nuebarsig);
  h1_SI -> Add(h1_SI_nuesig);
  h1_SI -> Add(h1_SI_numubar);
  h1_SI -> Add(h1_SI_numu);
  Double_t tot_SI = h1_SI->Integral();
  h1_SI -> Scale(1./tot_SI);*/

  /*TH1F* h1_MuCap = new TH1F("h1_MuCap", "", 10, 0, 5);
  h1_MuCap -> SetLineColor(kSpring+5);
  h1_MuCap -> SetStats(0);
  h1_MuCap -> SetLineWidth(3);
  h1_MuCap -> Add(h1_MuCap_nuebarbkg);
  h1_MuCap -> Add(h1_MuCap_nuebkg);
  h1_MuCap -> Add(h1_MuCap_nuebarsig);
  h1_MuCap -> Add(h1_MuCap_nuesig);
  h1_MuCap -> Add(h1_MuCap_numubar);
  h1_MuCap -> Add(h1_MuCap_numu);
  Double_t tot_MuCap = h1_MuCap->Integral();
  h1_MuCap -> Scale(1./tot_MuCap);*/


  gROOT -> SetStyle("Plain");
#if 1
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  if (beammode) hs_Mom -> SetMaximum(10);
  hs_Mom -> Draw();
  hs_Mom ->GetYaxis()->SetTitleSize(0.038);
  hs_Mom ->GetYaxis()->SetTitleOffset(1.3);
  hs_Mom ->GetYaxis()->SetLabelSize(0.036);
  hs_Mom ->GetXaxis()->SetTitle("Initial Momentum of Truth Captured Neutrons [MeV]");
  hs_Mom ->GetYaxis()->SetTitle("Number of Truth Neutrons");
  hs_Mom -> Draw();
  //h1 -> SetMaximum(20);
  //h1 -> Draw();
  c1 -> RedrawAxis();

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_PrmFSI_numu, "Primary #nu interaction + FSI", "F");
  legend1 -> AddEntry(h1_SI_numu, "SI", "F");
  //legend1 -> AddEntry(h1_MuCap_numu, "#mu^{-} capture neutrons", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif


#if 0
  TCanvas* c2 = new TCanvas("c2","c2",900,700);
  c2 -> SetGrid();
  h1_PrmFSI ->GetYaxis()->SetTitleSize(0.038);
  h1_PrmFSI ->GetYaxis()->SetTitleOffset(1.3);
  h1_PrmFSI ->GetYaxis()->SetLabelSize(0.036);
  h1_PrmFSI ->GetXaxis()->SetTitle("Truth Distance btw #nu and n capture vertices [m]");
  h1_PrmFSI ->GetYaxis()->SetTitle("Area Normalized");
  h1_PrmFSI -> Draw("SAME");
  h1_SI     -> Draw("SAME");
  //h1_MuCap  -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.4, 0.55, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.2]{FHC 1R #mu sample (0.01% Gd)}","");
  //else legend1->AddEntry((TObject*)0,"#kern[-0.2]{RHC 1R #mu sample (0.01% Gd)}","");
  legend2 -> AddEntry(h1_PrmFSI, "Primary #nu interaction + FSI", "L");
  legend2 -> AddEntry(h1_SI, "SI", "L");
  //legend2 -> AddEntry(h1_MuCap, "#mu^{-} capture neutrons", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif
}