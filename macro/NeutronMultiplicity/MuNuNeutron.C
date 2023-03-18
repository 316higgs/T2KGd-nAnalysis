
#define NUMUEVENTS 80624
#define NUMUBAREVENTS 71452

void MuNuNeutron() {

  TFile* fin_numu    = new TFile("../../output/fhc/fhc.numu_x_numu.NeutronVertex_mu_x_n.root");
  TFile* fin_numubar = new TFile("../../output/fhc/fhc.numubar_x_numubar.NeutronVertex_mu_x_n.root");

  TH1F* h1_TrueNuN_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueNuN");
  TH1F* h1_TrueMuN_numu = (TH1F*)fin_numu->Get("NTagAnalysis/h1_TrueMuN");
  //h1_GenBefSINeutrons_numu -> SetFillColor(kViolet-6);
  //h1_GenAtSINeutrons_numu  -> SetFillColor(kSpring-6);
  h1_TrueNuN_numu -> SetLineColor(kAzure+9);
  h1_TrueNuN_numu -> SetLineWidth(3);
  h1_TrueMuN_numu -> SetLineColor(kRed-7);
  h1_TrueMuN_numu -> SetLineWidth(3);
  //h1_GenBefSINeutrons_numu -> Scale(1./NUMUEVENTS);
  //h1_GenAtSINeutrons_numu  -> Scale(1./NUMUEVENTS);
  
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(1, "0");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(2, "1");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(3, "2");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(4, "3");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(5, "4");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(6, "5");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(7, "6");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(8, "7");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(9, "8");
  h1_TrueMuN_numu -> GetXaxis()->SetBinLabel(10, "9");
  h1_TrueMuN_numu -> SetStats(0);



  /*
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
  */



  TCanvas* c1 = new TCanvas("c1", "c1", 700, 500);
  c1 -> SetGrid();
  h1_TrueMuN_numu -> Draw("SAME");
  h1_TrueNuN_numu -> Draw("SAME");
  //hs_BrkDwn_numu -> Draw();

  TLegend* legend1 = new TLegend(0.4, 0.65, 0.87, 0.87);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.5]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  legend1 -> AddEntry(h1_TrueMuN_numu, "Neutrons from #mu captures", "L");
  legend1 -> AddEntry(h1_TrueNuN_numu, "Neutrons from #nu interactions", "L");
  legend1 -> SetFillColor(0);
  legend1 -> Draw();

}
