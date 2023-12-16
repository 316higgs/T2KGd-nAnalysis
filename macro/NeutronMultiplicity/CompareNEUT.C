
#include "../CommonTool/CommonTool.h"

void CompareNEUT() {
  TFile* fin_5_3_3 = new TFile("./output/NEUT5.3.3.root");
  TFile* fin_5_6_3 = new TFile("./output/NEUT5.6.3.root");

  TString hname_GenBefSI        = "h1_GenBefSI_FSI";
  TString hname_GenBefSI_nucFSI = "h1_GenBefSI_nucFSI";
  TString hname_GenBefSI_piFSI  = "h1_GenBefSI_piFSI";
  TString hname_GenBefSI_deexc  = "h1_GenBefSI_deexc";

  TH1F* h1_GenBefSI_FSI_5_3_3    = (TH1F*)fin_5_3_3->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_5_3_3 = (TH1F*)fin_5_3_3->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_5_3_3  = (TH1F*)fin_5_3_3->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_5_3_3  = (TH1F*)fin_5_3_3->Get(hname_GenBefSI_deexc);

  TH1F* h1_GenBefSI_FSI_5_6_3    = (TH1F*)fin_5_6_3->Get(hname_GenBefSI);
  TH1F* h1_GenBefSI_nucFSI_5_6_3 = (TH1F*)fin_5_6_3->Get(hname_GenBefSI_nucFSI);
  TH1F* h1_GenBefSI_piFSI_5_6_3  = (TH1F*)fin_5_6_3->Get(hname_GenBefSI_piFSI);
  TH1F* h1_GenBefSI_deexc_5_6_3  = (TH1F*)fin_5_6_3->Get(hname_GenBefSI_deexc);

  int GdColor = kOrange-6;
  int PWColor = kAzure+1;
  h1_GenBefSI_FSI_5_3_3 -> SetLineColor(PWColor);
  h1_GenBefSI_FSI_5_6_3 -> SetLineColor(GdColor);
  //ApplyAreaNorm(h1_GenBefSI_FSI_5_3_3);
  //ApplyAreaNorm(h1_GenBefSI_FSI_5_6_3);
  //Double_t GdProd = 100000*SAMPLES;
  //Double_t PWProd = 608262+130644+571513+123119+132241+120350;
  //  FCFV (Osc.)
  Double_t GdProd = 16884.9+5960.52+26950.2+6138.77+45768.1+42963.9;
  Double_t PWProd = 176471+12784.4+279639+14296.3+92089.3+85283.4;
  //  wallv
  //Double_t GdProd = 63622+63538+63444+63460+63423+63652;
  //Double_t PWProd = 448378+100190+429594+98073+105070+98053;
  //  1Rmu (No osc.)
  //Double_t GdProd = 26132+218+24816+265+272+316;
  //Double_t PWProd = 249629+410+224607+542+500+639;
  //  1Rmu (Osc.)
  //Double_t GdProd = 6044.42+200.84+13118.6+251.295+270.982+315.689;
  //Double_t PWProd = 54932+370.262+117986+523.307+498.924+638.474;
  std::cout << "#neutrons (Gd)        : " << h1_GenBefSI_FSI_5_6_3->Integral() << std::endl;
  std::cout << "#neutrons (pure water): " << h1_GenBefSI_FSI_5_3_3->Integral() << std::endl;
  std::cout << "Normalization         : " << GdProd/PWProd << std::endl;
  h1_GenBefSI_FSI_5_3_3 -> Scale( GdProd/PWProd );


#if 0
  gROOT -> SetStyle("Plain");
  TCanvas* c1 = new TCanvas("c1","c1",900,700);
  c1 -> SetGrid();
  h1_GenBefSI_FSI_5_6_3 ->GetXaxis()->SetTitleSize(0.045);
  h1_GenBefSI_FSI_5_6_3 ->GetYaxis()->SetTitleSize(0.045);
  h1_GenBefSI_FSI_5_6_3 ->GetYaxis()->SetTitleOffset(1.1);
  h1_GenBefSI_FSI_5_6_3 ->GetYaxis()->SetLabelSize(0.04);
  h1_GenBefSI_FSI_5_6_3 ->GetXaxis()->SetTitle("Truth Neutron Momentum [MeV]");
  h1_GenBefSI_FSI_5_6_3 ->GetYaxis()->SetTitle("Area Normalized");
  h1_GenBefSI_FSI_5_6_3 -> Draw("SAME");
  h1_GenBefSI_FSI_5_3_3 -> Draw("SAME");
  
  
  TLegend* legend1 = new TLegend(0.45, 0.6, 0.89, 0.89);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry((TObject*)0,"#kern[-0.3]{All generaated neutrons}","");
  legend1 -> AddEntry((TObject*)0,"#kern[-0.6]{(Before SI)}","");
  legend1 -> AddEntry(h1_GenBefSI_FSI_5_3_3, "NEUT 5.3.3", "L");
  legend1 -> AddEntry(h1_GenBefSI_FSI_5_6_3, "NEUT 5.6.3", "L");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

}