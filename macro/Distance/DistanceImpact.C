

void DistanceImpact() {

  const int DATAPOINTS = 5;
  float NeutronDistance[DATAPOINTS];

  /////// CCQE //////
  float NoNTagCCQE[DATAPOINTS];
  float PwTagNCCQE[DATAPOINTS];
  float PwoTagNCCQE[DATAPOINTS];
  float EwTagNCCQE[DATAPOINTS];
  float EwoTagNCCQE[DATAPOINTS];
  float NoNTagCCQELine = 0.721;
  PwTagNCCQE[0]  = 0.562;  //0 m
  PwoTagNCCQE[0] = 0.806;  //0 m
  PwTagNCCQE[1]  = 0.527;  //1 m
  PwoTagNCCQE[1] = 0.803;  //1 m
  PwTagNCCQE[2]  = 0.492;  //2 m
  PwoTagNCCQE[2] = 0.796;  //2 m
  PwTagNCCQE[3]  = 0.469;  //3 m
  PwoTagNCCQE[3] = 0.788;  //3 m
  PwTagNCCQE[4]  = 0.445;  //4 m
  PwoTagNCCQE[4] = 0.782;  //4 m

  EwTagNCCQE[0]  = 0.274;  //0 m
  EwoTagNCCQE[0] = 0.726;  //0 m
  EwTagNCCQE[1]  = 0.219;  //1 m
  EwoTagNCCQE[1] = 0.783;  //1 m
  EwTagNCCQE[2]  = 0.169;  //2 m
  EwoTagNCCQE[2] = 0.831;  //2 m
  EwTagNCCQE[3]  = 0.138;  //3 m
  EwoTagNCCQE[3] = 0.862;  //3 m
  EwTagNCCQE[4]  = 0.114;  //4 m
  EwoTagNCCQE[4] = 0.886;  //4 m


  /////// CC-2p2h //////
  float NoNTagCC2p2h[DATAPOINTS];
  float PwTagNCC2p2h[DATAPOINTS];
  float PwoTagNCC2p2h[DATAPOINTS];
  float EwTagNCC2p2h[DATAPOINTS];
  float EwoTagNCC2p2h[DATAPOINTS];
  float NoNTagCC2p2hLine = 0.0989;
  PwTagNCC2p2h[0]  = 0.13;    //0 m
  PwoTagNCC2p2h[0] = 0.0819;  //0 m
  PwTagNCC2p2h[1]  = 0.134;   //1 m
  PwoTagNCC2p2h[1] = 0.0836;  //1 m
  PwTagNCC2p2h[2]  = 0.14;    //2 m
  PwoTagNCC2p2h[2] = 0.0856;  //2 m
  PwTagNCC2p2h[3]  = 0.136;   //3 m
  PwoTagNCC2p2h[3] = 0.0889;  //3 m
  PwTagNCC2p2h[4]  = 0.134;   //4 m
  PwoTagNCC2p2h[4] = 0.0909;  //4 m

  EwTagNCC2p2h[0]  = 0.462;   //0 m
  EwoTagNCC2p2h[0] = 0.538;   //0 m
  EwTagNCC2p2h[1]  = 0.407;   //1 m
  EwoTagNCC2p2h[1] = 0.593;   //1 m
  EwTagNCC2p2h[2]  = 0.349;   //2 m
  EwoTagNCC2p2h[2] = 0.651;   //2 m
  EwTagNCC2p2h[3]  = 0.292;   //3 m
  EwoTagNCC2p2h[3] = 0.708;   //3 m
  EwTagNCC2p2h[4]  = 0.251;   //4 m
  EwoTagNCC2p2h[4] = 0.749;   //4 m

  /////// CC-Other //////
  float NoNTagCCOther[DATAPOINTS];
  float PwTagNCCOther[DATAPOINTS];
  float PwoTagNCCOther[DATAPOINTS];
  float EwTagNCCOther[DATAPOINTS];
  float EwoTagNCCOther[DATAPOINTS];
  float NoNTagCCOtherLine = 0.134;
  PwTagNCCOther[0]  = 0.229;   //0 m
  PwoTagNCCOther[0] = 0.0831;  //0 m
  PwTagNCCOther[1]  = 0.247;   //1 m
  PwoTagNCCOther[1] = 0.0866;  //1 m
  PwTagNCCOther[2]  = 0.257;   //2 m
  PwoTagNCCOther[2] = 0.0941;  //2 m
  PwTagNCCOther[3]  = 0.264;   //3 m
  PwoTagNCCOther[3] = 0.0995;  //3 m
  PwTagNCCOther[4]  = 0.271;   //4 m
  PwoTagNCCOther[4] = 0.104;   //4 m

  EwTagNCCOther[0]  = 0.599;   //0 m
  EwoTagNCCOther[0] = 0.401;   //0 m
  EwTagNCCOther[1]  = 0.548;   //1 m
  EwoTagNCCOther[1] = 0.452;   //1 m
  EwTagNCCOther[2]  = 0.473;   //2 m
  EwoTagNCCOther[2] = 0.527;   //2 m
  EwTagNCCOther[3]  = 0.417;   //3 m
  EwoTagNCCOther[3] = 0.583;   //3 m
  EwTagNCCOther[4]  = 0.372;   //4 m
  EwoTagNCCOther[4] = 0.629;   //4 m

  /////// NC //////
  float NoNTagNC[DATAPOINTS];
  float PwTagNNC[DATAPOINTS];
  float PwoTagNNC[DATAPOINTS];
  float EwTagNNC[DATAPOINTS];
  float EwoTagNNC[DATAPOINTS];
  float NoNTagNCLine = 0.046;
  PwTagNNC[0]  = 0.0783;  //0 m
  PwoTagNNC[0] = 0.0285;  //0 m
  PwTagNNC[1]  = 0.0923;  //1 m
  PwoTagNNC[1] = 0.0263;  //1 m
  PwTagNNC[2]  = 0.111;   //2 m
  PwoTagNNC[2] = 0.0246;  //2 m
  PwTagNNC[3]  = 0.13;    //3 m
  PwoTagNNC[3] = 0.0235;  //3 m
  PwTagNNC[4]  = 0.149;   //4 m
  PwoTagNNC[4] = 0.0227;  //4 m

  EwTagNNC[0]  = 0.598;  //0 m
  EwoTagNNC[0] = 0.402;  //0 m
  EwTagNNC[1]  = 0.598;  //1 m
  EwoTagNNC[1] = 0.402;  //1 m
  EwTagNNC[2]  = 0.598;  //2 m
  EwoTagNNC[2] = 0.402;  //2 m
  EwTagNNC[3]  = 0.598;  //3 m
  EwoTagNNC[3] = 0.402;  //3 m
  EwTagNNC[4]  = 0.598;  //4 m
  EwoTagNNC[4] = 0.402;  //4 m

  //////// Significance ////////
  float SNoNTag[DATAPOINTS];
  float SwTagN[DATAPOINTS];
  float SwoTagN[DATAPOINTS];
  float NoNTagLine = 0.932;
  SwTagN[0]  = 0.789;  //0 m
  SwoTagN[0] = 0.972;  //0 m
  SwTagN[1]  = 0.745;  //1 m
  SwoTagN[1] = 0.971;  //1 m
  SwTagN[2]  = 0.696;  //2 m
  SwoTagN[2] = 0.969;  //2 m
  SwTagN[3]  = 0.662;  //3 m
  SwoTagN[3] = 0.966;  //3 m
  SwTagN[4]  = 0.626;  //4 m
  SwoTagN[4] = 0.964;  //4 m


  for (int i=0; i<DATAPOINTS; i++) {
  	NeutronDistance[i] = i;
  	NoNTagCCQE[i]    = NoNTagCCQELine;
  	NoNTagCC2p2h[i]  = NoNTagCC2p2hLine;
  	NoNTagCCOther[i] = NoNTagCCOtherLine;
  	NoNTagNC[i]      = NoNTagNCLine;
    SNoNTag[i]       = NoNTagLine;
  }

  TGraph* g_NoNTag_CCQE = new TGraph(DATAPOINTS, NeutronDistance, NoNTagCCQE);
  g_NoNTag_CCQE -> SetLineColor(kAzure-1);
  g_NoNTag_CCQE -> SetLineWidth(2);
  g_NoNTag_CCQE -> SetLineStyle(2);
  TGraph* g_PwTagN_CCQE  = new TGraph(DATAPOINTS, NeutronDistance, PwTagNCCQE);
  g_PwTagN_CCQE -> SetLineColor(kAzure-1);
  g_PwTagN_CCQE -> SetLineWidth(2);
  g_PwTagN_CCQE -> SetMarkerColor(kAzure-1);
  g_PwTagN_CCQE -> SetMarkerStyle(20);
  g_PwTagN_CCQE -> SetMarkerSize(1.5);
  TGraph* g_PwoTagN_CCQE = new TGraph(DATAPOINTS, NeutronDistance, PwoTagNCCQE);
  g_PwoTagN_CCQE -> SetLineColor(kAzure-1);
  g_PwoTagN_CCQE -> SetLineWidth(2);
  g_PwoTagN_CCQE -> SetMarkerColor(kAzure-1);
  g_PwoTagN_CCQE -> SetMarkerStyle(22);
  g_PwoTagN_CCQE -> SetMarkerSize(1.5);
  TGraph* g_EwTagN_CCQE  = new TGraph(DATAPOINTS, NeutronDistance, EwTagNCCQE);
  g_EwTagN_CCQE -> SetLineColor(kAzure-1);
  g_EwTagN_CCQE -> SetLineWidth(2);
  g_EwTagN_CCQE -> SetMarkerColor(kAzure-1);
  g_EwTagN_CCQE -> SetMarkerStyle(20);
  g_EwTagN_CCQE -> SetMarkerSize(1.5);
  TGraph* g_EwoTagN_CCQE = new TGraph(DATAPOINTS, NeutronDistance, EwoTagNCCQE);
  g_EwoTagN_CCQE -> SetLineColor(kAzure-1);
  g_EwoTagN_CCQE -> SetLineWidth(2);
  g_EwoTagN_CCQE -> SetMarkerColor(kAzure-1);
  g_EwoTagN_CCQE -> SetMarkerStyle(22);
  g_EwoTagN_CCQE -> SetMarkerSize(1.5);

  TGraph* g_NoNTag_CC2p2h = new TGraph(DATAPOINTS, NeutronDistance, NoNTagCC2p2h);
  g_NoNTag_CC2p2h -> SetLineColor(kAzure-5);
  g_NoNTag_CC2p2h -> SetLineWidth(2);
  g_NoNTag_CC2p2h -> SetLineStyle(2);
  TGraph* g_PwTagN_CC2p2h  = new TGraph(DATAPOINTS, NeutronDistance, PwTagNCC2p2h);
  g_PwTagN_CC2p2h -> SetLineColor(kAzure-5);
  g_PwTagN_CC2p2h -> SetLineWidth(2);
  g_PwTagN_CC2p2h -> SetMarkerColor(kAzure-5);
  g_PwTagN_CC2p2h -> SetMarkerStyle(20);
  g_PwTagN_CC2p2h -> SetMarkerSize(1.5);
  TGraph* g_PwoTagN_CC2p2h = new TGraph(DATAPOINTS, NeutronDistance, PwoTagNCC2p2h);
  g_PwoTagN_CC2p2h -> SetLineColor(kAzure-5);
  g_PwoTagN_CC2p2h -> SetLineWidth(2);
  g_PwoTagN_CC2p2h -> SetMarkerColor(kAzure-5);
  g_PwoTagN_CC2p2h -> SetMarkerStyle(22);
  g_PwoTagN_CC2p2h -> SetMarkerSize(1.5);
  TGraph* g_EwTagN_CC2p2h  = new TGraph(DATAPOINTS, NeutronDistance, EwTagNCC2p2h);
  g_EwTagN_CC2p2h -> SetLineColor(kAzure-5);
  g_EwTagN_CC2p2h -> SetLineWidth(2);
  g_EwTagN_CC2p2h -> SetMarkerColor(kAzure-5);
  g_EwTagN_CC2p2h -> SetMarkerStyle(20);
  g_EwTagN_CC2p2h -> SetMarkerSize(1.5);
  TGraph* g_EwoTagN_CC2p2h = new TGraph(DATAPOINTS, NeutronDistance, EwoTagNCC2p2h);
  g_EwoTagN_CC2p2h -> SetLineColor(kAzure-5);
  g_EwoTagN_CC2p2h -> SetLineWidth(2);
  g_EwoTagN_CC2p2h -> SetMarkerColor(kAzure-5);
  g_EwoTagN_CC2p2h -> SetMarkerStyle(22);
  g_EwoTagN_CC2p2h -> SetMarkerSize(1.5);

  TGraph* g_NoNTag_CCOther = new TGraph(DATAPOINTS, NeutronDistance, NoNTagCCOther);
  g_NoNTag_CCOther -> SetLineColor(kCyan-8);
  g_NoNTag_CCOther -> SetLineWidth(2);
  g_NoNTag_CCOther -> SetLineStyle(2);
  TGraph* g_PwTagN_CCOther  = new TGraph(DATAPOINTS, NeutronDistance, PwTagNCCOther);
  g_PwTagN_CCOther -> SetLineColor(kCyan-8);
  g_PwTagN_CCOther -> SetLineWidth(2);
  g_PwTagN_CCOther -> SetMarkerColor(kCyan-8);
  g_PwTagN_CCOther -> SetMarkerStyle(20);
  g_PwTagN_CCOther -> SetMarkerSize(1.5);
  TGraph* g_PwoTagN_CCOther = new TGraph(DATAPOINTS, NeutronDistance, PwoTagNCCOther);
  g_PwoTagN_CCOther -> SetLineColor(kCyan-8);
  g_PwoTagN_CCOther -> SetLineWidth(2);
  g_PwoTagN_CCOther -> SetMarkerColor(kCyan-8);
  g_PwoTagN_CCOther -> SetMarkerStyle(22);
  g_PwoTagN_CCOther -> SetMarkerSize(1.5);
  TGraph* g_EwTagN_CCOther  = new TGraph(DATAPOINTS, NeutronDistance, EwTagNCCOther);
  g_EwTagN_CCOther -> SetLineColor(kCyan-8);
  g_EwTagN_CCOther -> SetLineWidth(2);
  g_EwTagN_CCOther -> SetMarkerColor(kCyan-8);
  g_EwTagN_CCOther -> SetMarkerStyle(20);
  g_EwTagN_CCOther -> SetMarkerSize(1.5);
  TGraph* g_EwoTagN_CCOther = new TGraph(DATAPOINTS, NeutronDistance, EwoTagNCCOther);
  g_EwoTagN_CCOther -> SetLineColor(kCyan-8);
  g_EwoTagN_CCOther -> SetLineWidth(2);
  g_EwoTagN_CCOther -> SetMarkerColor(kCyan-8);
  g_EwoTagN_CCOther -> SetMarkerStyle(22);
  g_EwoTagN_CCOther -> SetMarkerSize(1.5);

  TGraph* g_NoNTag_NC = new TGraph(DATAPOINTS, NeutronDistance, NoNTagNC);
  g_NoNTag_NC -> SetLineColor(kTeal+9);
  g_NoNTag_NC -> SetLineWidth(2);
  g_NoNTag_NC -> SetLineStyle(2);
  TGraph* g_PwTagN_NC  = new TGraph(DATAPOINTS, NeutronDistance, PwTagNNC);
  g_PwTagN_NC -> SetLineColor(kTeal+9);
  g_PwTagN_NC -> SetLineWidth(2);
  g_PwTagN_NC -> SetMarkerColor(kTeal+9);
  g_PwTagN_NC -> SetMarkerStyle(20);
  g_PwTagN_NC -> SetMarkerSize(1.5);
  TGraph* g_PwoTagN_NC = new TGraph(DATAPOINTS, NeutronDistance, PwoTagNNC);
  g_PwoTagN_NC -> SetLineColor(kTeal+9);
  g_PwoTagN_NC -> SetLineWidth(2);
  g_PwoTagN_NC -> SetMarkerColor(kTeal+9);
  g_PwoTagN_NC -> SetMarkerStyle(22);
  g_PwoTagN_NC -> SetMarkerSize(1.5);
  TGraph* g_EwTagN_NC  = new TGraph(DATAPOINTS, NeutronDistance, EwTagNNC);
  g_EwTagN_NC -> SetLineColor(kTeal+9);
  g_EwTagN_NC -> SetLineWidth(2);
  g_EwTagN_NC -> SetMarkerColor(kTeal+9);
  g_EwTagN_NC -> SetMarkerStyle(20);
  g_EwTagN_NC -> SetMarkerSize(1.5);
  TGraph* g_EwoTagN_NC = new TGraph(DATAPOINTS, NeutronDistance, EwoTagNNC);
  g_EwoTagN_NC -> SetLineColor(kTeal+9);
  g_EwoTagN_NC -> SetLineWidth(2);
  g_EwoTagN_NC -> SetMarkerColor(kTeal+9);
  g_EwoTagN_NC -> SetMarkerStyle(22);
  g_EwoTagN_NC -> SetMarkerSize(1.5);

  TGraph* g_SNoNTag = new TGraph(DATAPOINTS, NeutronDistance, SNoNTag);
  g_SNoNTag -> SetLineColor(kTeal+9);
  g_SNoNTag -> SetLineWidth(2);
  g_SNoNTag -> SetLineStyle(2);
  TGraph* g_SwTagN  = new TGraph(DATAPOINTS, NeutronDistance, SwTagN);
  g_SwTagN -> SetLineColor(kTeal+9);
  g_SwTagN -> SetLineWidth(2);
  g_SwTagN -> SetMarkerColor(kTeal+9);
  g_SwTagN -> SetMarkerStyle(20);
  g_SwTagN -> SetMarkerSize(1.5);
  TGraph* g_SwoTagN = new TGraph(DATAPOINTS, NeutronDistance, SwoTagN);
  g_SwoTagN -> SetLineColor(kTeal+9);
  g_SwoTagN -> SetLineWidth(2);
  g_SwoTagN -> SetMarkerColor(kTeal+9);
  g_SwoTagN -> SetMarkerStyle(22);
  g_SwoTagN -> SetMarkerSize(1.5);


  TString notice = "No NTag";
  TText* textCCQE = new TText((float)DATAPOINTS-1.8, NoNTagCCQELine+0.01, notice);
  textCCQE -> SetTextSize(0.04);
  textCCQE -> SetTextColor(kAzure-1);
  TText* textCC2p2h = new TText((float)DATAPOINTS-1.8, NoNTagCC2p2hLine+0.01, notice);
  textCC2p2h -> SetTextSize(0.04);
  textCC2p2h -> SetTextColor(kAzure-5);
  TText* textCCOther = new TText((float)DATAPOINTS-1.8, NoNTagCCOtherLine+0.01, notice);
  textCCOther -> SetTextSize(0.04);
  textCCOther -> SetTextColor(kCyan-8);
  TText* textNC = new TText((float)DATAPOINTS-1.8, NoNTagNCLine+0.01, notice);
  textNC -> SetTextSize(0.04);
  textNC -> SetTextColor(kTeal+9);
  TText* textCCQE1 = new TText(3., 0.9, "CCQE");
  textCCQE1 -> SetTextSize(0.07);
  textCCQE1 -> SetTextColor(kAzure-1);
  TText* textCC2p2h1 = new TText(2.6, 0.9, "CC-2p2h");
  textCC2p2h1 -> SetTextSize(0.07);
  textCC2p2h1 -> SetTextColor(kAzure-5);
  TText* textCCOther1 = new TText(2.4, 0.9, "CC-Other");
  textCCOther1 -> SetTextSize(0.07);
  textCCOther1 -> SetTextColor(kCyan-8);
  TText* textNC1 = new TText(3.3, 0.9, "NC");
  textNC1 -> SetTextSize(0.07);
  textNC1 -> SetTextColor(kTeal+9);


#if 0
  TCanvas* c0 = new TCanvas("c0", "c0", 1000, 1000);
  c0 -> Divide(2, 2);
  c0 ->cd(1)-> SetGrid();
  TH1F* frame1 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame1 -> SetXTitle("Distance [m]");
  frame1 -> SetYTitle("Separation Purity in Sample");
  frame1 -> SetTitleOffset(1.2, "Y");
  g_NoNTag_CCQE -> Draw("L");
  g_PwTagN_CCQE  -> Draw("SAMEPL");
  g_PwoTagN_CCQE -> Draw("SAMEPL");
  textCCQE  -> Draw();
  textCCQE1 -> Draw();

  TLegend* legend1 = new TLegend(0.2, 0.2, 0.6, 0.4);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(g_PwTagN_CCQE, "1R#mu w/  tagged-n", "LP");
  legend1 -> AddEntry(g_PwoTagN_CCQE, "1R#mu w/o tagged-n", "LP");
  legend1->SetFillColor(0);
  legend1->Draw();

  c0 ->cd(2)-> SetGrid();
  TH1F* frame2 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame2 -> SetXTitle("Distance [m]");
  frame2 -> SetYTitle("Separation Purity in Sample");
  frame2 -> SetTitleOffset(1.2, "Y");
  g_NoNTag_CC2p2h -> Draw("L");
  g_PwTagN_CC2p2h  -> Draw("SAMEPL");
  g_PwoTagN_CC2p2h -> Draw("SAMEPL");
  textCC2p2h  -> Draw();
  textCC2p2h1 -> Draw();

  TLegend* legend2 = new TLegend(0.4, 0.4, 0.8, 0.6);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(g_PwTagN_CC2p2h, "1R#mu w/  tagged-n", "LP");
  legend2 -> AddEntry(g_PwoTagN_CC2p2h, "1R#mu w/o tagged-n", "LP");
  legend2->SetFillColor(0);
  legend2->Draw();

  c0 ->cd(3)-> SetGrid();
  TH1F* frame3 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame3 -> SetXTitle("Distance [m]");
  frame3 -> SetYTitle("Separation Purity in Sample");
  frame3 -> SetTitleOffset(1.2, "Y");
  g_NoNTag_CCOther -> Draw("L");
  g_PwTagN_CCOther  -> Draw("SAMEPL");
  g_PwoTagN_CCOther -> Draw("SAMEPL");
  textCCOther  -> Draw();
  textCCOther1 -> Draw();

  TLegend* legend3 = new TLegend(0.4, 0.4, 0.8, 0.6);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry(g_PwTagN_CCOther, "1R#mu w/  tagged-n", "LP");
  legend3 -> AddEntry(g_PwoTagN_CCOther, "1R#mu w/o tagged-n", "LP");
  legend3->SetFillColor(0);
  legend3->Draw();

  c0 ->cd(4)-> SetGrid();
  TH1F* frame4 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame4 -> SetXTitle("Distance [m]");
  frame4 -> SetYTitle("Separation Purity in Sample");
  frame4 -> SetTitleOffset(1.2, "Y");
  g_NoNTag_NC -> Draw("L");
  g_PwTagN_NC  -> Draw("SAMEPL");
  g_PwoTagN_NC -> Draw("SAMEPL");
  textNC  -> Draw();
  textNC1 -> Draw();

  TLegend* legend4 = new TLegend(0.4, 0.4, 0.8, 0.6);
  legend4 -> SetTextSize(0.04);
  legend4 -> AddEntry(g_PwTagN_NC, "1R#mu w/  tagged-n", "LP");
  legend4 -> AddEntry(g_PwoTagN_NC, "1R#mu w/o tagged-n", "LP");
  legend4->SetFillColor(0);
  legend4->Draw();
#endif
  
  //////////////////////////////////

#if 0
  TCanvas* c0 = new TCanvas("c0", "c0", 1000, 1000);
  c0 -> Divide(2, 2);
  c0 ->cd(1)-> SetGrid();
  TH1F* frame1 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame1 -> SetXTitle("Distance [m]");
  frame1 -> SetYTitle("Separation Efficiency in Sample");
  frame1 -> SetTitleOffset(1.2, "Y");
  g_EwTagN_CCQE  -> Draw("PL");
  g_EwoTagN_CCQE -> Draw("SAMEPL");
  textCCQE1 -> Draw();

  TLegend* legend1 = new TLegend(0.4, 0.4, 0.8, 0.6);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(g_EwTagN_CCQE, "1R#mu w/  tagged-n", "LP");
  legend1 -> AddEntry(g_EwoTagN_CCQE, "1R#mu w/o tagged-n", "LP");
  legend1->SetFillColor(0);
  legend1->Draw();

  c0 ->cd(2)-> SetGrid();
  TH1F* frame2 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame2 -> SetXTitle("Distance [m]");
  frame2 -> SetYTitle("Separation Efficiency in Sample");
  frame2 -> SetTitleOffset(1.2, "Y");
  g_EwTagN_CC2p2h  -> Draw("SAMEPL");
  g_EwoTagN_CC2p2h -> Draw("SAMEPL");
  textCC2p2h1 -> Draw();

  TLegend* legend2 = new TLegend(0.15, 0.67, 0.55, 0.87);
  legend2 -> SetTextSize(0.04);
  legend2 -> AddEntry(g_PwTagN_CC2p2h, "1R#mu w/  tagged-n", "LP");
  legend2 -> AddEntry(g_PwoTagN_CC2p2h, "1R#mu w/o tagged-n", "LP");
  legend2->SetFillColor(0);
  legend2->Draw();

  c0 ->cd(3)-> SetGrid();
  TH1F* frame3 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame3 -> SetXTitle("Distance [m]");
  frame3 -> SetYTitle("Separation Efficiency in Sample");
  frame3 -> SetTitleOffset(1.2, "Y");
  g_EwTagN_CCOther  -> Draw("SAMEPL");
  g_EwoTagN_CCOther -> Draw("SAMEPL");
  textCCOther1 -> Draw();

  TLegend* legend3 = new TLegend(0.15, 0.67, 0.55, 0.87);
  legend3 -> SetTextSize(0.04);
  legend3 -> AddEntry(g_PwTagN_CCOther, "1R#mu w/  tagged-n", "LP");
  legend3 -> AddEntry(g_PwoTagN_CCOther, "1R#mu w/o tagged-n", "LP");
  legend3->SetFillColor(0);
  legend3->Draw();

  c0 ->cd(4)-> SetGrid();
  TH1F* frame4 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame4 -> SetXTitle("Distance [m]");
  frame4 -> SetYTitle("Separation Efficiency in Sample");
  frame4 -> SetTitleOffset(1.2, "Y");
  g_EwTagN_NC  -> Draw("SAMEPL");
  g_EwoTagN_NC -> Draw("SAMEPL");
  textNC1 -> Draw();

  TLegend* legend4 = new TLegend(0.15, 0.67, 0.55, 0.87);
  legend4 -> SetTextSize(0.04);
  legend4 -> AddEntry(g_PwTagN_NC, "1R#mu w/  tagged-n", "LP");
  legend4 -> AddEntry(g_PwoTagN_NC, "1R#mu w/o tagged-n", "LP");
  legend4->SetFillColor(0);
  legend4->Draw();
#endif

  //////////////////////////////////

#if 1
  TCanvas* c0 = new TCanvas("c0", "c0", 1000, 1000);
  c0 -> SetGrid();
  TH1F* frame1 = gPad->DrawFrame(-0.1, 0., DATAPOINTS-0.9, 1.);
  frame1 -> SetXTitle("Distance [m]");
  frame1 -> SetYTitle("Separation Significance in Sample");
  frame1 -> SetTitleOffset(1.2, "Y");
  g_SNoNTag -> Draw("PL");
  g_SwTagN  -> Draw("SAMEPL");
  g_SwoTagN -> Draw("SAMEPL");
  //textCCQE1 -> Draw();

  TLegend* legend1 = new TLegend(0.4, 0.4, 0.8, 0.6);
  legend1 -> SetTextSize(0.04);
  legend1 -> AddEntry(g_SwTagN, "1R#mu w/  tagged-n", "LP");
  legend1 -> AddEntry(g_SwoTagN, "1R#mu w/o tagged-n", "LP");
  legend1->SetFillColor(0);
  legend1->Draw();
#endif

}

