#include "include/NeutrinoEvents.h"
//#include "TH1F.h"

TH2F* h2_ipnu;
TH1F* h1_Ipvc;
TH1F* h1_iprntprt;
TH1F* h1_Iflvc;
TH1F* h1_iprtscnd;
TH2F* h2_iprtscnd_lmecscnd;
//TH2F* h2_iprtscnd_iprntprt;
//TH2F* h2_iprtscnd_iflgscnd;

TH1F* h1_PrmNeutron;
TH1F* h1_ScndNeutron;
TH1F* h1_PrmNeutronE[4];  //Each parent contribution to primary neutrons
TH1F* h1_ScndNeutronE[3]; //Each parent contribution to SI neutrons

TH1F* h1_OverallN;
TH1F* h1_PrmNFrac;   //Integrated contributions to primary neutrons
TH1F* h1_SINFrac;    //Integrated contributions to SI neutrons
TH1F* h1_OtherNFrac; //Integrated contributions to Other neutrons

void SetVECTHisto() {
  h2_ipnu     = new TH2F("h1_ipnu", "ipnu; numnu; ipnu", 9, 1, 10, 219, 10, 2200);
  h2_ipnu -> SetStats(0);

  h1_Ipvc     = new TH1F("h1_Ipvc", "Ipvc; Ipvc; Number of Events", 2490, 10, 2500);
  h1_iprntprt = new TH1F("h1_iprntprt", "iprntprt; iprntprt; Number of Events", 2490, 10, 2500);
  h1_Iflvc    = new TH1F("h1_Iflvc", "Iflvc; Iflvc; Number of Events", 10, 0, 10);
  h1_iprtscnd = new TH1F("h1_iprtscnd", "iprtscnd; iprtscnd; Number of Events", 2490, 10, 2500);
  h2_iprtscnd_lmecscnd = new TH2F("h2_iprtscnd_lmecscnd", "iprtscnd vs lmecscnd; iprtscnd; lmecscnd", 2490, 10, 2500, 25, 5, 30);
  h2_iprtscnd_lmecscnd -> SetStats(0);
  //h2_iprtscnd_iprntprt = new TH2F("h2_iprtscnd_iprntprt", "iprtscnd vs iprntprt; iprtscnd; iprntprt", 2490, 10, 2500, 2490, 10, 2500);
  //h2_iprtscnd_iflgscnd = new TH2F("h2_iprtscnd_iflgscnd", "iprtscnd vs iflgscnd; iprtscnd; iflgscnd", 2490, 10, 2500, 10, -1, 9);


  h1_PrmNeutron   = new TH1F("h1_PrmNeutron", "h1_PrmNeutron; Ipvc; Number of Events", 2490, 10, 2500);
  h1_PrmNeutron   -> SetStats(0);
  h1_ScndNeutron  = new TH1F("h1_ScndNeutron", "h1_ScndNeutron; iprtscnd; Number of Events", 2490, 10, 2500);
  h1_ScndNeutron  -> SetStats(0);

  for (int i=0; i<4; i++) {
    h1_PrmNeutronE[i]  = new TH1F(TString::Format("h1_PrmNeutronE_type%d", i), "h1_PrmNeutronE; Truth Neutron Momentum[MeV]; Number of Events", 50, 900, 1200);
    h1_PrmNeutronE[i]  -> SetLineWidth(3);
  }
  for (int i=0; i<3; i++) {
    h1_ScndNeutronE[i] = new TH1F(TString::Format("h1_ScndNeutronE_type%d", i), "h1_ScndNeutronE; Truth Neutron Momentum[MeV]; Number of Events", 50, 900, 1200);
    h1_ScndNeutronE[i] -> SetLineWidth(3);
  }
  //h1_PrmNeutronE  = new TH1F("h1_PrmNeutronE", "h1_PrmNeutronE; Truth Neutron Momentum[MeV]; Number of Events", 600, 800, 1400);
  //h1_ScndNeutronE = new TH1F("h1_ScndNeutronE", "h1_ScndNeutronE; Truth Neutron Momentum[MeV]; Number of Events", 600, 80, 1400);
  h1_PrmNeutronE[0] -> SetLineColor(kGray+1);   //pi0
  h1_PrmNeutronE[1] -> SetLineColor(kRed-9);    //pi+
  h1_PrmNeutronE[2] -> SetLineColor(kViolet+2); //n
  h1_PrmNeutronE[3] -> SetLineColor(kRed-4);    //p

  h1_ScndNeutronE[0] -> SetLineColor(kTeal+3);   //FSI
  h1_ScndNeutronE[1] -> SetLineColor(kSpring-6); //SI
  h1_ScndNeutronE[2] -> SetLineColor(kAzure+1);  //mu
  //h1_ScndNeutronE[3] -> SetLineColor(kRed-9);    //pi+

  h1_OverallN   = new TH1F("h1_OverallN", "All n; Truth neutron energy; Fraction", 21, 939, 960);
  h1_PrmNFrac   = new TH1F("h1_PrmNFrac", "Prm n; Truth neutron energy; Fraction of primary neutrons", 21, 939, 960);
  h1_SINFrac    = new TH1F("h1_SINFrac", "SI n; Truth neutron energy; Fraction of SI neutrons", 21, 939, 960);
  h1_OtherNFrac = new TH1F("h1_OtherNFrac", "Other n; Truth neutron energy; Fraction of other neutrons", 21, 939, 960);
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
    //h2_iprtscnd_iprntprt -> Fill(iprtscnd, iprntprt);
  }
}

void WriteVECTHisto() {
  //h2_ipnu     -> Write();
  h1_Ipvc     -> Write();
  //h1_iprntprt -> Write();
  h1_iprtscnd -> Write();
  h2_iprtscnd_lmecscnd -> Write();
  //h2_iprtscnd_iprntprt -> Write();
  //h2_iprtscnd_iflgscnd -> Write();
  h1_Iflvc -> Write();

  if (CCQEwTaggedNeutrons_prm!=0)  h1_PrmNeutron  -> Scale(1./CCQEwTaggedNeutrons_prm);
  if (CCQEwTaggedNeutrons_scnd!=0) h1_ScndNeutron -> Scale(1./CCQEwTaggedNeutrons_scnd);
  h1_PrmNeutron  -> Write();
  h1_ScndNeutron -> Write();

  for (int i=0; i<4; i++) h1_PrmNeutronE[i]  -> Write();
  for (int i=0; i<3; i++) h1_ScndNeutronE[i] -> Write();

  h1_OverallN   -> Write();

  //h1_PrmNFrac   -> Sumw2();
  //h1_PrmNFrac   -> Divide(h1_OverallN);
  h1_PrmNFrac   -> Write();

  //h1_SINFrac   -> Sumw2();
  //h1_SINFrac   -> Divide(h1_OverallN);
  h1_SINFrac   -> Write();

  //h1_OtherNFrac   -> Sumw2();
  //h1_OtherNFrac   -> Divide(h1_OverallN);
  h1_OtherNFrac   -> Write();
}
