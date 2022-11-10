
TH2F* h2_ipnu;
TH1F* h1_Ipvc;
TH1F* h1_iprntprt;
//TH1F* h1_iprtscnd;
//TH2F* h2_iprtscnd_lmecscnd;
TH2F* h2_iprtscnd_iprntprt;
TH2F* h2_iprtscnd_iflgscnd;

void SetVECTHisto() {
  h2_ipnu     = new TH2F("h1_ipnu", "ipnu; numnu; ipnu", 9, 1, 10, 219, 10, 2200);
  h2_ipnu -> SetStats(0);

  h1_Ipvc     = new TH1F("h1_Ipvc", "Ipvc; Ipvc; Number of Events", 10, 10, 20);
  h1_iprntprt = new TH1F("h1_iprntprt", "iprntprt; iprntprt; Number of Events", 2490, 10, 2500);
  //h1_iprtscnd = new TH1F("h1_iprtscnd", "iprtscnd; iprtscnd; Number of Events", 2490, 10, 2500);
  //h2_iprtscnd_lmecscnd = new TH2F("h2_iprtscnd_lmecscnd", "iprtscnd vs lmecscnd; iprtscnd; lmecscnd", 2490, 10, 2500, 25, 5, 30);
  h2_iprtscnd_iprntprt = new TH2F("h2_iprtscnd_iprntprt", "iprtscnd vs iprntprt; iprtscnd; iprntprt", 2490, 10, 2500, 2490, 10, 2500);
  h2_iprtscnd_iflgscnd = new TH2F("h2_iprtscnd_iflgscnd", "iprtscnd vs iflgscnd; iprtscnd; iflgscnd", 2490, 10, 2500, 10, -1, 9);
}

void FillVECTHisto(CC0PiNumu* numu) {

  //Number of particle at neutrino interaction
  int numnu = numu->var<int>("numnu");
  for (int inu=1; inu<numnu; inu++) {
  	int ipnu = numu->var<int>("ipnu", inu);
  	h2_ipnu -> Fill(numnu, ipnu);
  }


  //Number of the primary particles
  int Npvc = numu->var<int>("Npvc");
  for (int iprm=0; iprm<Npvc; iprm++) {
  	int Ipvc = numu->var<int>("Ipvc", iprm);
  	h1_Ipvc -> Fill(Ipvc);
  }

  //Number of the secondary particles of this event
  int nscndprt = numu->var<int>("nscndprt");
  for (int iscnd=0; iscnd<nscndprt; iscnd++) {

  	//PID of iscnd-th secondary particle
  	int iprtscnd = numu->var<int>("iprtscnd", iscnd);
  	//h1_iprtscnd -> Fill(iprtscnd);

    //PID of the parent particle of iscnd-th secondary particle
    int iprntprt = numu-> var<int>("iprntprt", iscnd);
    h1_iprntprt -> Fill(iprntprt);

    int lmecscnd = numu->var<int>("lmecscnd", iscnd);

    //h2_iprtscnd_lmecscnd -> Fill(iprtscnd, lmecscnd);
    h2_iprtscnd_iprntprt -> Fill(iprtscnd, iprntprt);
  }
}

void WriteVECTHisto() {
  h2_ipnu     -> Write();
  h1_Ipvc     -> Write();
  h1_iprntprt -> Write();
  //h1_iprtscnd -> Write();
  //h2_iprtscnd_lmecscnd -> Write();
  h2_iprtscnd_iprntprt -> Write();
  h2_iprtscnd_iflgscnd -> Write();
}
