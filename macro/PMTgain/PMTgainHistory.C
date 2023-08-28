#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"
#include "TLatex.h"

#define PRODPERIOD  5
#define LINEJAN2021 4710
#define LINEJUN2021 4874
//#define DATALENGTH 163   // LINEJUN2021 - LINEJAN2021 -1

void PMTgainHistory() {
  
  TString fname = "./water.ave10.2";
  std::ifstream fin(fname);
  if (fin.fail()) {
    std::cout << "File: " << fname << std::endl;
    return 1;
  }
  else std::cout << "File: " << fname << " loaded..." << std::endl;

  int dataline = 1;
  TString datatime;
  int date = 0;
  float PMTgain[PRODPERIOD] = {0.};
  float DateArray[LINEJUN2021 - LINEJAN2021 - 1] = {0.};                 // for TGraph
  float PMTgainArray[PRODPERIOD][ LINEJUN2021 - LINEJAN2021 - 1] = {0.};  // for TGraph
  while ( 1 ) {
    TString previous_datatime;
    TString hoge;

    previous_datatime = datatime;
    
    // data extraction
    fin >> hoge >> datatime;
    for (int ihoge=0; ihoge<14; ihoge++) fin >> hoge;
    fin >> PMTgain[0] >> PMTgain[1] >> PMTgain[2] >> PMTgain[3] >> PMTgain[4];
    dataline++;

    // around run 11
    if (dataline>LINEJAN2021 && dataline<LINEJUN2021) {

      if (datatime != previous_datatime) {
        DateArray[date] = date;
        std::cout << "[ " << date <<", Array: " << DateArray[date] << " ] data time: " << datatime;
        for (int iprod=0; iprod<PRODPERIOD; iprod++) {
          PMTgainArray[iprod][date] = PMTgain[iprod];
          std::cout << ", PMT gain[" << iprod << "] = " << PMTgainArray[iprod][date];
        }
        date++;
      }
      else {
        DateArray[date] = date-1;
        std::cout << "[ " << date << ", Array: " << DateArray[date]  << " ]                       ";
        for (int iprod=0; iprod<PRODPERIOD; iprod++) {
          PMTgainArray[iprod][date] = PMTgain[iprod];
          std::cout << "PMT gain[" << iprod << "] = " << PMTgainArray[iprod][date] << ", ";
        }
        date++;
      }
      std::cout << "" << std::endl;
    }
    
    if (dataline==LINEJUN2021+1) break;
  }

  std::cout << "# of data: " << date << std::endl;
  
  TGraph* g_PMTgain[PRODPERIOD];
  for (int iprod=0; iprod<PRODPERIOD; iprod++) {
    g_PMTgain[iprod] = new TGraph(LINEJUN2021-LINEJAN2021-1, DateArray, PMTgainArray[iprod]);
    g_PMTgain[iprod] -> SetMarkerStyle(20);
    g_PMTgain[iprod] -> SetMarkerSize(0.6);
  }
  g_PMTgain[0] -> SetMarkerColor(kGray+3);
  g_PMTgain[1] -> SetMarkerColor(kRed-4);
  g_PMTgain[2] -> SetMarkerColor(kSpring-5);
  g_PMTgain[3] -> SetMarkerColor(kAzure+2);
  g_PMTgain[4] -> SetMarkerColor(kOrange-3);


  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  TH1F* frame = gPad->DrawFrame(-5, 0.9, LINEJUN2021-LINEJAN2021, 1.2);
  //frame -> SetXTitle("Data Time");
  frame -> SetYTitle("PMT Gain");
  frame -> SetTitleOffset(1.2, "Y");
  frame -> GetYaxis()->SetLabelSize(0.04);
  frame -> GetYaxis()->SetTitleOffset(1.1);
  //frame -> GetXaxis()->SetTitleOffset(1.1);
  frame -> GetXaxis()->SetLabelSize(0.035);
  frame -> GetXaxis()->SetTitleSize(0.045);
  frame -> GetYaxis()->SetTitleSize(0.045);
  frame -> GetXaxis()->SetLabelColor(kWhite);
  //frame -> GetXaxis()->SetTimeDisplay(1);
  //frame -> GetXaxis()->SetTimeFormat("#splitline{  %Y}{%b %d}");
  //frame -> GetXaxis()->SetLimits(t1, t2);
  for (int iprod=0; iprod<PRODPERIOD; iprod++) g_PMTgain[iprod] -> Draw("SAMEP");

  float TimeX[4] = {0.};
  TimeX[0] = 0.1;   // Jan
  TimeX[1] = 0.25;  // Feb
  TimeX[2] = 0.39;  // Mar
  TimeX[3] = 0.55;  // Apr
  TimeX[4] = 0.7;   // May
  for (int i=0; i<5; i++) {
    TText* text1 = new TText(TimeX[i], 0.06, "2021");
    text1 -> SetTextSize(0.035);
    text1 -> SetTextColor(kBlack);
    text1 -> SetNDC(1);
    text1 -> Draw();

    TString day   = "Jan. 1";
    if (i==1) day = "Feb. 1";
    if (i==2) day = "Mar. 1";
    if (i==3) day = "Apr. 1";
    if (i==4) day = "May. 1";
    TText* text2 = new TText(TimeX[i]-0.01, 0.03, day);
    text2 -> SetTextSize(0.035);
    text2 -> SetTextColor(kBlack);
    text2 -> SetNDC(1);
    text2 -> Draw();
  }

  TLegend* legend1 = new TLegend(0.55, 0.55, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.2]{PMT production period:}","");
  legend1 -> AddEntry(g_PMTgain[0], "~1995", "P");
  legend1 -> AddEntry(g_PMTgain[1], "1996-1997", "P");
  legend1 -> AddEntry(g_PMTgain[2], "1998-2003", "P");
  legend1 -> AddEntry(g_PMTgain[3], "2004", "P");
  legend1 -> AddEntry(g_PMTgain[4], "2005-", "P");
  legend1->SetFillColor(0);
  legend1->Draw();

}