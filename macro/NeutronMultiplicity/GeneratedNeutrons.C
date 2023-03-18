

#define NUMUEVENTS 80624
#define NUMUBAREVENTS 71452

void GeneratedNeutrons() {

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");

  TH1F* h1_GenBefSINeutrons_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAtSINeutrons_numu  = (TH1F*)fin_numu->Get("NTagAnalysis/h1_GenAtSINeutrons");
  h1_GenBefSINeutrons_numu -> SetFillColor(kViolet-6);
  h1_GenAtSINeutrons_numu  -> SetFillColor(kSpring-6);
  h1_GenBefSINeutrons_numu -> SetLineColor(kViolet-6);
  h1_GenAtSINeutrons_numu  -> SetLineColor(kSpring-6);
  //h1_GenBefSINeutrons_numu -> Scale(1./NUMUEVENTS);
  //h1_GenAtSINeutrons_numu  -> Scale(1./NUMUEVENTS);


  THStack* hs_BrkDwn_numu = new THStack("hs_BrkDwn_numu", "Captured Neutrons; Number of Captured Neutrons; Normalized by # of #nu Events");
  hs_BrkDwn_numu -> Add(h1_GenBefSINeutrons_numu);
  hs_BrkDwn_numu -> Add(h1_GenAtSINeutrons_numu);

  TH1F* h1_GenBefSINeutrons_numubar = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenBefSINeutrons");
  TH1F* h1_GenAtSINeutrons_numubar  = (TH1F*)fin_numubar->Get("NTagAnalysis/h1_GenAtSINeutrons");
  h1_GenBefSINeutrons_numubar -> SetFillColor(kViolet-6);
  h1_GenAtSINeutrons_numubar  -> SetFillColor(kSpring-6);
  h1_GenBefSINeutrons_numubar -> SetLineColor(kViolet-6);
  h1_GenAtSINeutrons_numubar  -> SetLineColor(kSpring-6);
  //h1_GenBefSINeutrons_numubar -> Scale(1./NUMUBAREVENTS);
  //h1_GenAtSINeutrons_numubar  -> Scale(1./NUMUBAREVENTS);

  THStack* hs_BrkDwn_numubar = new THStack("hs_BrkDwn_numubar", "Captured Neutrons; Number of Captured Neutrons; Normalized by # of #nu Events");
  hs_BrkDwn_numubar -> Add(h1_GenBefSINeutrons_numubar);
  hs_BrkDwn_numubar -> Add(h1_GenAtSINeutrons_numubar);



  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  c1 -> SetGrid();
  hs_BrkDwn_numu -> Draw();

  TLegend* legend1 = new TLegend(0.4, 0.55, 0.87, 0.87);
  legend1 -> SetTextSize(0.035);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{Truth #nu CCQE}","");
  legend1 -> AddEntry(h1_GenBefSINeutrons_numu, "Captured neutrons from #nu + FSI", "F");
  legend1 -> AddEntry(h1_GenAtSINeutrons_numu, "Captured neutrons from SI", "F");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();


  TCanvas* c2 = new TCanvas("c2", "c2", 700, 500);
  c2 -> SetGrid();
  hs_BrkDwn_numubar -> Draw();

  TLegend* legend2 = new TLegend(0.4, 0.55, 0.87, 0.87);
  legend2 -> SetTextSize(0.035);
  legend2 -> AddEntry((TObject*)0,"#kern[-0.2]{Truth #bar{#nu} CCQE}","");
  legend2 -> AddEntry(h1_GenBefSINeutrons_numubar, "Captured neutrons from #nu + FSI", "F");
  legend2 -> AddEntry(h1_GenAtSINeutrons_numubar, "Captured neutrons from SI", "F");
  legend2 -> SetFillColor(0);
  legend2 -> Draw();

}
