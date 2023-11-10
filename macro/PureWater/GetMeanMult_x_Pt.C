

#define BINNUM 5

void GetMeanMult_x_Pt() {

  TString fname = "/disk03/usr8/sedi/PureWater/nmeas_results.2019May.conststaterr.root";
  TFile* fin = new TFile(fname);

  TGraphErrors* gMC = (TGraphErrors*)fin->Get("gTrMomAveMC_fhc");  // MC
  TGraphAsymmErrors* gData = (TGraphAsymmErrors*)fin->Get("gTrMomAveData_fhc_statsys");  // Data (stat+syst)

  double xMuPtbins[BINNUM] = {0, 0.25, 0.5, 0.75, 1.5};


  TH1F* h1_fhc_nmult_x_pt_MC   = new TH1F("h1_fhc_nmult_x_pt_MC", "", BINNUM-1, xMuPtbins);
  TH1F* h1_fhc_nmult_x_pt_Data = new TH1F("h1_fhc_nmult_x_pt_Data", "", BINNUM-1, xMuPtbins);


  Double_t x[BINNUM]        = {0.};
  Double_t dx[BINNUM]       = {0.};
  Double_t yMC[BINNUM]      = {0.};
  Double_t yData[BINNUM]    = {0.};
  Double_t dyMC[BINNUM]     = {0.};
  Double_t dyData_U[BINNUM] = {0.};
  Double_t dyData_B[BINNUM] = {0.};
  for (int ibin=0; ibin<BINNUM; ibin++) {
  	gMC   -> GetPoint(ibin, x[ibin], yMC[ibin]);
  	gData -> GetPoint(ibin, x[ibin], yData[ibin]);
    dyMC[ibin]     = gMC->GetErrorY(ibin);
    dyData_U[ibin] = gData->GetErrorYhigh(ibin);
    dyData_B[ibin] = gData->GetErrorYlow(ibin);

  	std::cout << "[BIN " << ibin << "] MC = " << yMC[ibin] << " +/- " << dyMC[ibin] << std::endl;
  	std::cout << "        Data = " << yData[ibin] << " + " << dyData_U[ibin] << " / -" << dyData_B[ibin] << std::endl;
    h1_fhc_nmult_x_pt_MC -> SetBinContent(ibin+1, yMC[ibin]);
  }

  h1_fhc_nmult_x_pt_MC -> SetLineColor(kOrange-5);
  h1_fhc_nmult_x_pt_MC -> SetLineWidth(2);

  TGraphErrors* g_nmult_x_pt_MC = new TGraphErrors(BINNUM, x, yMC, dx, dyMC);
  g_nmult_x_pt_MC -> SetLineColor(kOrange-5);
  g_nmult_x_pt_MC -> SetLineWidth(3);

  gData -> SetLineWidth(2);

#if 1
  TCanvas* c1 = new TCanvas("c1", "", 900, 700);
  c1 -> SetGrid();
  c1 -> SetTicks(1);
  TH1F* frame = new TH1F("frame", "", BINNUM-1, xMuPtbins);
  frame -> GetYaxis()->SetRangeUser(0., 5.);
  frame -> GetXaxis()->CenterTitle();
  //frame->GetYaxis()->CenterTitle();
  //frame->GetXaxis()->SetTitleOffset(1.0);
  frame -> GetYaxis()->SetTitleOffset(1.1);
  //frame->GetXaxis()->SetLabelOffset(0.01);
  frame -> GetYaxis()->SetTitleSize(0.045);
  //frame->GetXaxis()->SetTitleSize(0.065);
  frame -> GetYaxis()->SetTitle( "Mean neutron multiplicity" );
  frame -> SetStats(0);
  //frame->GetXaxis()->SetLabelSize(0.125);
  //frame->GetXaxis()->SetBinLabel(1, Form("#color[%d]{#bf{FHC}}", kBlue+2));
  //frame->GetXaxis()->SetBinLabel(2, Form("#color[%d]{#bf{RHC}}", kRed+2));
  frame -> Draw();
  gMC   -> Draw("2 SAME");
  gData -> Draw("P SAME");
  h1_fhc_nmult_x_pt_MC -> Draw("SAME");
  g_nmult_x_pt_MC -> Draw("SAMEP");
#endif  


  TString foutname = "output/purewater_results.root";
  TFile* fout = new TFile(foutname, "RECREATE");
  fout -> cd();
  gMC   -> Write();  // Akutsu-san's format
  gData -> Write();

  h1_fhc_nmult_x_pt_MC -> Write(); // My format
  g_nmult_x_pt_MC      -> Write();


}