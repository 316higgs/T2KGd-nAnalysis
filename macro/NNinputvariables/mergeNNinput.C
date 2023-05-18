
TString GetNNVarName(int vartype);
TString GetNNVarAxisName(int vartype);

void mergeNNinput() {
  
  //TFile* finnumu = new TFile("../../output/fhc/fhc.numu_x_numu.preNN.newGdMC.root");
  TFile* finnumu = new TFile("../../output/fhc/fhc.numu_x_numu.postNN.newGdMC.root");

  TH1F* h1_NNvar_Gd_numu[12];
  TH1F* h1_NNvar_H_numu[12];
  TH1F* h1_NNvar_AccNoise_numu[12];
  TH1F* h1_NNvar_Decaye_numu[12];

  THStack* hs_NNvar_numu[12];

  for (int i=0; i<12; i++) {
  	h1_NNvar_Gd_numu[i]       = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Gd_type%d", i));
    h1_NNvar_H_numu[i]        = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_H_type%d", i));
    h1_NNvar_AccNoise_numu[i] = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_AccNoise_type%d", i));
    h1_NNvar_Decaye_numu[i]   = (TH1F*)finnumu->Get(TString::Format("NNInputVariables/h1_NNvar_Decaye_type%d", i));

    h1_NNvar_Gd_numu[i]       -> SetFillColor(kTeal-5);
    h1_NNvar_H_numu[i]        -> SetFillColor(kAzure-4);
    h1_NNvar_Decaye_numu[i]   -> SetFillColor(kYellow-3);
    h1_NNvar_AccNoise_numu[i] -> SetFillColor(kGray+2);

    TString hsname = GetNNVarName(i);
    hs_NNvar_numu[i] = new THStack(TString::Format("hs_NNvar_numu_var%d", i), hsname);
    hs_NNvar_numu[i] -> Add(h1_NNvar_AccNoise_numu[i]);
    hs_NNvar_numu[i] -> Add(h1_NNvar_Decaye_numu[i]);
    hs_NNvar_numu[i] -> Add(h1_NNvar_H_numu[i]);
    hs_NNvar_numu[i] -> Add(h1_NNvar_Gd_numu[i]);
  }

  TLegend* legend = new TLegend(0.4, 0.4, 0.87, 0.87);
  legend -> SetTextSize(0.06);
  //legend -> AddEntry((TObject*)0,"#kern[-0.23]{Pre-NN}","");
  legend -> AddEntry((TObject*)0,"#kern[-0.23]{Post-NN}","");
  legend -> AddEntry(h1_NNvar_Gd_numu[0], "Gd-n signal", "F");
  legend -> AddEntry(h1_NNvar_H_numu[0], "H-n signal", "F");
  legend -> AddEntry(h1_NNvar_Decaye_numu[0], "Decay-e", "F");
  legend -> AddEntry(h1_NNvar_AccNoise_numu[0], "Acc. noise", "F");
  legend -> SetFillColor(0);

  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1", "c1", 1200, 1000);
  c1 -> Divide(4,3);
  for (int i=0; i<12; i++) {
    c1 -> cd(i+1);
    //gPad->SetLogy();
    hs_NNvar_numu[i] -> Draw();
    TString varname = GetNNVarAxisName(i);
    hs_NNvar_numu[i] -> GetXaxis()->SetTitle(varname);
    hs_NNvar_numu[i] -> GetYaxis()->SetTitle("Number of Events");
    hs_NNvar_numu[i] -> Draw();
    if (i==11) legend -> Draw();
  }
}


TString GetNNVarName(int vartype) {
	TString histtitle;
  	switch (vartype) {
  	  case 0:
  	    histtitle = "NHits";
  	    break;
  	  case 1:
  	    histtitle = "N200";
  	    break;
  	  case 2:
  	    histtitle = "TRMS";
  	    break;
      case 3:
  	    histtitle = "DWall";
  	    break;
  	  case 4:
  	    histtitle = "DWallMeanDir";
  	    break;
  	  case 5:
  	    histtitle = "OpeningAngleMean";
  	    break;
      case 6:
  	    histtitle = "OpeningAngleStdev";
  	    break;
  	  case 7:
  	    histtitle = "OpeningAngleSkew";
  	    break;
  	  case 8:
  	    histtitle = "MeanDirAngleMean";
  	    break;
  	  case 9:
  	    histtitle = "MeanDirAngleRMS";
  	    break;
  	  case 10:
  	    histtitle = "Beta1; Beta1";
  	    break;
  	  case 11:
  	    histtitle = "Beta5; Beta5";
  	    break;
  	}
  return histtitle;
}

TString GetNNVarAxisName(int vartype) {
  TString varname;
  switch (vartype) {
  	  case 0:
  	    varname = "NHits";
  	    break;
  	  case 1:
  	    varname = "N200";
  	    break;
  	  case 2:
  	    varname = "TRMS [nsec]";
  	    break;
      case 3:
  	    varname = "DWall [cm]";
  	    break;
  	  case 4:
  	    varname = "DWallMeanDir [cm]";
  	    break;
  	  case 5:
  	    varname = "OpeningAngleMean [deg]";
  	    break;
      case 6:
  	    varname = "OpeningAngleStdev [deg]";
  	    break;
  	  case 7:
  	    varname = "OpeningAngleSkew";
  	    break;
  	  case 8:
  	    varname = "MeanDirAngleMean [deg]";
  	    break;
  	  case 9:
  	    varname = "MeanDirAngleRMS [deg]";
  	    break;
  	  case 10:
  	    varname = "Beta1";
  	    break;
  	  case 11:
  	    varname = "Beta5";
  	    break;
  	}
  return varname;
}
