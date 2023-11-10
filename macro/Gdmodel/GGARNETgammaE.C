

#define FILENUM 50

void GGARNETgammaE() {

  std::vector<float> EachGammaEList;
  std::vector<float> TotGammaEList;

  TH1F* h1_TotGammaE = new TH1F("h1_TotGammaE", "", 400, 0, 10000);
  //TH1F* h1_TotGammaE = new TH1F("h1_TotGammaE", "", 10000, 7000, 10000);
  h1_TotGammaE -> SetStats(0);

  int allcapture_evt = 0;
  for (int ifile=0; ifile<FILENUM; ifile++) {

  	// read files
  	TString fname = TString::Format("/disk03/usr8/sedi/SKDETSIM_15/output/Log/test_run.Count0%02d.log", ifile);
    std::ifstream fin(fname);
    if (fin.fail()) {
      std::cout << "Could not open: " << fname << std::endl;
      return 1;	
    }
    else std::cout << "Open: " << fname << std::endl;

    // data extraction
    TString findGetGammas;
    int capture_evt = 0;
    while ( 1 ) {
      TString hoge;
      int NumGammas = 0;
      float GammaE = 0.;
      float TotGammaE = 0.;

      fin >> hoge;
      if (hoge=="gamma-rays:") {
      	fin >> NumGammas;
      	//std::cout << "[ #" << capture_evt << " ] gamma-rays: " << NumGammas << ", ";
      	if (capture_evt!=0) {
      	  for (int igamma=0; igamma<NumGammas; igamma++) {
      	  	fin >> GammaE;
      	  	TotGammaE += GammaE;
      	  	EachGammaEList.push_back(GammaE);
      	  	//std::cout << GammaE << " MeV, ";
      	  }
      	  TotGammaEList.push_back(TotGammaE);
      	}
      	capture_evt++;
      	//std::cout << " " << std::endl;
      }

      if (fin.eof()) break;
    }
    allcapture_evt += capture_evt-1;  // except the first gamma
    std::cout << "#all events: " << allcapture_evt << ", vector size: " << TotGammaEList.size() << std::endl;
    if (allcapture_evt!=TotGammaEList.size()) std::cout << "\e[38;5;A0m\e[1m Bug???? \e[0m" << std::endl;

#if 1
    // vector operation
    for (UInt_t ievt=0; ievt<TotGammaEList.size(); ievt++) {
      std::cout << "Total gamma energy: " << TotGammaEList.at(ievt) << " MeV" << std::endl;
      h1_TotGammaE -> Fill(TotGammaEList.at(ievt)*1000.);
    }
#endif
    
  }


  gROOT -> SetStyle("Plain");
#if 1

  TLegend* legend1 = new TLegend(0.14, 0.75, 0.6, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(h1_TotGammaE, "GGARNET-based MC", "L");
  legend1 -> SetFillColor(0);

  TCanvas* c1 = new TCanvas("c1", "c1", 900, 700);
  c1 -> SetGrid();
  c1 -> SetLogy();
  h1_TotGammaE -> SetLineWidth(2);
  h1_TotGammaE -> SetLineColor(kRed-6);
  h1_TotGammaE -> SetXTitle("Total #gamma Energy [keV]");
  h1_TotGammaE -> SetYTitle("Number of True Neutron Captures");
  h1_TotGammaE ->Draw();
  legend1 -> Draw();
#endif
  
}