
void NeutronFrac() {

  TFile* fin_numu = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.cut1.root");

  TH1F* h1_PrmNFrac   = (TH1F*)fin_numu->Get("h1_PrmNFrac");
  TH1F* h1_SINFrac    = (TH1F*)fin_numu->Get("h1_SINFrac");
  TH1F* h1_OtherNFrac = (TH1F*)fin_numu->Get("h1_OtherNFrac");

  h1_PrmNFrac   -> SetLineColor(kPink-5);
  h1_SINFrac    -> SetLineColor(kSpring-5);
  h1_OtherNFrac -> SetLineColor(kViolet+2);

  h1_PrmNFrac   -> SetFillColor(kPink-5);
  h1_SINFrac    -> SetFillColor(kSpring-5);
  h1_OtherNFrac -> SetFillColor(kViolet+2);

  THStack* hs_NFrac = new THStack("hs_NFrac", "Neutron Fraction; Truth neutron energy[MeV]; Fraction of neutrons");
  hs_NFrac -> Add(h1_OtherNFrac);
  hs_NFrac -> Add(h1_SINFrac);
  hs_NFrac -> Add(h1_PrmNFrac);

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  hs_NFrac -> Draw();
  //h1_OtherNFrac -> Draw();
  c1->RedrawAxis();


  TLegend* legend1 = new TLegend(0.55, 0.4, 0.89, 0.7);
  legend1 -> SetTextSize(0.04);
  legend1->AddEntry((TObject*)0,"#kern[-0.3]{CCQE w/ tagged-n}","");
  legend1 -> AddEntry(h1_PrmNFrac, "Primary n", "F");
  legend1 -> AddEntry(h1_SINFrac, "SI n", "F");
  legend1 -> AddEntry(h1_OtherNFrac, "#mu capture n", "F");
  legend1->SetFillColor(0);
  legend1->Draw();
}