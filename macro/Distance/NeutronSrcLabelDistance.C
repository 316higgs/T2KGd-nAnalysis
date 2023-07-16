#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

#define NA 6.0221409
#define FV 22.5
//#define POTSCALE 1.96  //Run1-10 FHC
//#define POTSCALE 1.63  //Run1-10 RHC
#define POTSCALE 0.17  //Run1-10 FHC

void NeutronSrcLabelDistance(bool beammode) {

  //FHC
/*#if fhcflag
  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");
  TFile* fin_skrate  = new TFile("./fhc.sk_rate_tmp.root");
#endif

  //RHC
#if rhcflag
  TFile* fin_numu    = new TFile("../../output/rhc/rhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/rhc/rhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");
  TFile* fin_skrate  = new TFile("./rhc.sk_rate_tmp.root");
#endif*/

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


  TH1F* h1_BefSIn_numu = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_nu_BefSIn");
  TH1F* h1_SIn_numu    = (TH1F*)fin_numu->Get("DistanceViewer/h1_truedistance_nu_SIn");

  TH1F* h1_BefSIn_numubar = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_nu_BefSIn");
  TH1F* h1_SIn_numubar    = (TH1F*)fin_numubar->Get("DistanceViewer/h1_truedistance_nu_SIn");

  h1_BefSIn_numu    -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_BefSIn_numubar -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );
  h1_SIn_numu       -> Scale( (ExpN_numu_x_numu)/(GenN_numu_x_numu) );
  h1_SIn_numubar    -> Scale( (ExpN_numubar_x_numubar)/(GenN_numubar_x_numubar) );

  h1_BefSIn_numu -> SetLineColor(kAzure-9);
  h1_SIn_numu    -> SetLineColor(kAzure+1);

#if 0
  h1_BefSIn_numu -> SetLineWidth(3);
  h1_SIn_numu    -> SetLineWidth(3);
  h1_BefSIn_numu -> SetYTitle("Area Normalized");
  h1_BefSIn_numu -> SetStats(0);

  Double_t BefSIn_numu = h1_BefSIn_numu->Integral();
  Double_t SIn_numu    = h1_SIn_numu->Integral();
  h1_BefSIn_numu -> Scale(1./BefSIn_numu);
  h1_SIn_numu    -> Scale(1./SIn_numu);
  gROOT -> SetStyle("Plain");
  TCanvas* c2 = new TCanvas("c1", "c1", 900, 700);
  c2 -> SetGrid();
  //h1_SIn_numu -> SetMaximum(FrameMaximum);
  h1_BefSIn_numu -> Draw("SAME");
  h1_SIn_numu -> Draw("SAME");

  TLegend* legend2 = new TLegend(0.4, 0.65, 0.89, 0.89);
  legend2 -> SetTextSize(0.04);
  if (beammode) legend2->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend2->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");
  legend2 -> AddEntry(h1_BefSIn_numu, "#nu_{#mu} Primary or FSI neutrons", "L");
  legend2 -> AddEntry(h1_SIn_numu, "#nu_{#mu} SI neutrons", "L");
  legend2->SetFillColor(0);
  legend2->Draw();
#endif

  h1_BefSIn_numu -> SetFillColor(kAzure-9);
  h1_SIn_numu    -> SetFillColor(kAzure+1);

  h1_BefSIn_numubar -> SetLineColor(kOrange+6);
  h1_SIn_numubar    -> SetLineColor(kOrange+1);

  h1_BefSIn_numubar -> SetFillColor(kOrange+6);
  h1_SIn_numubar    -> SetFillColor(kOrange+1);

  //THStack* hs_TruePrmMuEnd_x_TrueNCap = new THStack("hs_TruePrmMuEnd_x_TrueNCap", "Neutron-related distance; Distance from #mu End Vertex[m]; Number of Events");
  THStack* hs_TruePrmMuEnd_x_TrueNCap = new THStack("hs_TruePrmMuEnd_x_TrueNCap", "Neutron-related distance; Distance from Primary Vertex[m]; Number of Events");
#if fhcflag
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numu);
#endif
#if rhcflag
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_SIn_numubar);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numu);
  hs_TruePrmMuEnd_x_TrueNCap -> Add(h1_BefSIn_numubar);
#endif

  //float FrameMaximum = 4.;
  float FrameMaximum = 9.;

#if 1
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  if (beammode) hs_TruePrmMuEnd_x_TrueNCap -> SetMaximum(FrameMaximum);
  else hs_TruePrmMuEnd_x_TrueNCap -> SetMaximum(50);
  hs_TruePrmMuEnd_x_TrueNCap -> Draw();
  c1 -> RedrawAxis();

  
  TLegend* legend1 = new TLegend(0.4, 0.45, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  if (beammode) legend1->AddEntry((TObject*)0,"#kern[-0.25]{FHC 1R #mu sample (0.01% Gd)}","");
  else legend1->AddEntry((TObject*)0,"#kern[-0.15]{RHC 1R #mu sample (0.01% Gd)}","");
  legend1 -> AddEntry(h1_BefSIn_numu, "#nu_{#mu} Primary or FSI neutrons", "F");
  legend1 -> AddEntry(h1_BefSIn_numubar, "#bar{#nu}_{#mu} Primary or FSI neutrons", "F");
  legend1 -> AddEntry(h1_SIn_numu, "#nu_{#mu} SI neutrons", "F");
  legend1 -> AddEntry(h1_SIn_numubar, "#bar{#nu}_{#mu} SI neutrons", "F");
  legend1->SetFillColor(0);
  legend1->Draw() ;
#endif

}
