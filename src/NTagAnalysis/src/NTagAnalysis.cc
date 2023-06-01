#include "NTagAnalysis.h"
#include "../../DecayeBox/inc/DecayeBox.h"
#include "../../NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "../../../include/NeutrinoEvents.h"

void NTagAnalysis::SetHistoFrame() {

  for (int i=0; i<TRUETYPE; i++) {
    h1_NTrueN[i]    = new TH1F(TString::Format("h1_NTrueN_type%d", i), "Truth Capture Neutrons; NTrueN; Entries", 12, 0, 12);
  }
  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueNmultiplicity[i] = new TH1F(TString::Format("h1_TrueNmultiplicity_mode%d", i), "Truth Capture Neutrons; NTrueN; Entries", 5, 0, 5);
    h1_TrueNmultiplicity[i] ->GetXaxis()->SetBinLabel(1, "0");
    h1_TrueNmultiplicity[i] ->GetXaxis()->SetBinLabel(2, "1");
    h1_TrueNmultiplicity[i] ->GetXaxis()->SetBinLabel(3, "2");
    h1_TrueNmultiplicity[i] ->GetXaxis()->SetBinLabel(4, "3");
    h1_TrueNmultiplicity[i] ->GetXaxis()->SetBinLabel(5, "4");

    h1_TagNmultiplicity[i] = new TH1F(TString::Format("h1_TagNmultiplicity_mode%d", i), "Tagged Capture Neutrons; NTagN; Entries", 5, 0, 5);
    h1_TagNmultiplicity[i] ->GetXaxis()->SetBinLabel(1, "0");
    h1_TagNmultiplicity[i] ->GetXaxis()->SetBinLabel(2, "1");
    h1_TagNmultiplicity[i] ->GetXaxis()->SetBinLabel(3, "2");
    h1_TagNmultiplicity[i] ->GetXaxis()->SetBinLabel(4, "3");
    h1_TagNmultiplicity[i] ->GetXaxis()->SetBinLabel(5, "4");
  }
  h1_TrueMuN = new TH1F("h1_TrueMuN", "h1_TrueMuN; Truth Capture Neutrons; Number of Neutrino Events", 10, 0, 10);
  h1_TrueNuN = new TH1F("h1_TrueNuN", "h1_TrueNuN; Truth Capture Neutrons; Number of Neutrino Events", 10, 0, 10);
  h1_TotGammaE   = new TH1F("h1_TotGammaE", "Truth Total Gamma Energy; E[MeV]; Entries", 100, 0, 10);
  for (int i=0; i<2; i++) {
    if (i==0) {
      h1_Enureso_All[i]           = new TH1F("h1_Enureso_All_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE[i]       = new TH1F("h1_Enureso_CCnonQE_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCQE[i]          = new TH1F("h1_Enureso_CCQE_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CC2p2h[i]        = new TH1F("h1_Enureso_CC2p2h_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap[i]  = new TH1F("h1_Enureso_CCRESdeltap_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp[i] = new TH1F("h1_Enureso_CCRESdeltapp_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0[i]  = new TH1F("h1_Enureso_CCRESdelta0_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCOther[i]       = new TH1F("h1_Enureso_CCOther_woTagN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC[i]            = new TH1F("h1_Enureso_NC_woTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

      h1_Enureso_CCQE_trueN[i]          = new TH1F("h1_Enureso_CCQE_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CC2p2h_trueN[i]        = new TH1F("h1_Enureso_CC2p2h_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap_trueN[i]  = new TH1F("h1_Enureso_CCRESdeltap_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp_trueN[i] = new TH1F("h1_Enureso_CCRESdeltapp_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0_trueN[i]  = new TH1F("h1_Enureso_CCRESdelta0_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCOther_trueN[i]       = new TH1F("h1_Enureso_CCOther_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC_trueN[i]            = new TH1F("h1_Enureso_NC_woTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
    }
    if (i==1) {
      h1_Enureso_All[i]           = new TH1F("h1_Enureso_All_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCnonQE[i]       = new TH1F("h1_Enureso_CCnonQE_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCQE[i]          = new TH1F("h1_Enureso_CCQE_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CC2p2h[i]        = new TH1F("h1_Enureso_CC2p2h_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap[i]  = new TH1F("h1_Enureso_CCRESdeltap_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp[i] = new TH1F("h1_Enureso_CCRESdeltapp_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0[i]  = new TH1F("h1_Enureso_CCRESdelta0_wTagN", "Neutrino Energy Resolution w/o Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCOther[i]       = new TH1F("h1_Enureso_CCOther_wTagN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC[i]            = new TH1F("h1_Enureso_NC_wTagN", "Neutrino Energy Resolution w/ Tagged Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);

      h1_Enureso_CCQE_trueN[i]          = new TH1F("h1_Enureso_CCQE_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CC2p2h_trueN[i]        = new TH1F("h1_Enureso_CC2p2h_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltap_trueN[i]  = new TH1F("h1_Enureso_CCRESdeltap_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_deltapp_trueN[i] = new TH1F("h1_Enureso_CCRESdeltapp_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCRES_delta0_trueN[i]  = new TH1F("h1_Enureso_CCRESdelta0_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_CCOther_trueN[i]       = new TH1F("h1_Enureso_CCOther_wTrueN", "Neutrino Energy Resolution w/o Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
      h1_Enureso_NC_trueN[i]            = new TH1F("h1_Enureso_NC_wTrueN", "Neutrino Energy Resolution w/ Truth Neutrons; (E^{true}_{#nu}-E^{reco}_{#nu})/E^{true}_{#nu}; Number of Neutrino Events", 60, -1, 1);
    }
  }

  h2_TrueNCapVtxXY = new TH2F("h2_TrueNCapVtxXY", "", 100, -20, 20, 100, -20, 20);
  h2_TrueNCapVtxRZ = new TH2F("h2_TrueNCapVtxRZ", "", 100, 0, 400, 100, -20, 20);

  h1_TrueNCapTime = new TH1F("h1_TrueNCapTime", "", 535, 0., 535);
  for (int i=0; i<4; i++) {
    //h1_RecoNCapTime[i] = new TH1F(TString::Format("h1_RecoNCapTime_type%d", i), "h1_RecoNCapTime; Reco Capture Time[#musec]; Number of Events", 250, 0., 535);
    h1_RecoNCapTime[i] = new TH1F(TString::Format("h1_RecoNCapTime_type%d", i), "h1_RecoNCapTime; Reco Capture Time[#musec]; Number of Events", 40, 0., 20);
    //h1_N50[i] = new TH1F(TString::Format("h1_N50_type%d", i), "h1_N50; N50; Number of Events", 80, 0., 80);
  }
  h1_mintimediff_NCap = new TH1F("h1_mintimediff_NCap", "h1_mintimediff_NCap; tscnd-FitT[#musec]; Number of Events", 200, -0.2, 0.2);
  h1_NCapVtxReso      = new TH1F("h1_NCapVtxReso", "h1_NCapVtxReso; Neutron Capture Vertex Resolution [cm]; Number of Events", 3000, 0, 300);

  h1_GenPrmNeutrons    = new TH1F("h1_GenPrmNeutrons", "h1_GenPrmNeutrons; Number of generated neutrons; Number of Events", 10, 0, 10);
  //h1_GenAftFSINeutrons = new TH1F("h1_GenAftFSINeutrons", "h1_GenAftFSINeutrons; Number of generated neutrons; Number of Events", 10, 0, 10);
  h1_GenAftSINeutrons  = new TH1F("h1_GenAftSINeutrons", "h1_GenAftSINeutrons; Number of generated neutrons; Number of Events", 10, 0, 10);
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(1, "0");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(2, "1");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(3, "2");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(4, "3");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(5, "4");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(6, "5");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(7, "6");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(8, "7");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(9, "8");
  h1_GenAftSINeutrons ->GetXaxis()->SetBinLabel(10, "9");
  //h1_GenAtSINeutrons   = new TH1F("h1_GenAtSINeutrons", "h1_GenAtSINeutrons; Number of generated neutrons; Number of Events", 10, 0, 10);
  h1_GenBefSINeutrons  = new TH1F("h1_GenBefSINeutrons", "h1_GenBefSINeutrons; Number of generated neutrons; Number of Events", 10, 0, 10);
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(1, "0");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(2, "1");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(3, "2");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(4, "3");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(5, "4");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(6, "5");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(7, "6");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(8, "7");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(9, "8");
  h1_GenBefSINeutrons ->GetXaxis()->SetBinLabel(10, "9");
  h1_GenBefSInE        = new TH1F("h1_GenBefSInE", "h1_GenBefSInE; Truth Neutron Energy[MeV]; Number of Events", 50, 0, 200);
  h1_GenSInE           = new TH1F("h1_GenSInE", "h1_GenSInE; Truth Neutron Energy[MeV]; Number of Events", 50, 0, 200);

  for (int i=0; i<4; i++) {
    h1_N1Rmu_x_Enu[i]     = new TH1F(TString::Format("h1_N1Rmu_x_Enu_mode%d", i), "N1Rmu_x_Enu; Reco Neutrino Energy [GeV]; Number of #nu Events", binnumber_nu-1, xEnubins);
    h1_N1Rmu_x_MuMom[i]   = new TH1F(TString::Format("h1_N1Rmu_x_MuMom_mode%d", i), "N1Rmu_x_MuMom; Reco #mu Momentum [GeV]; Number of #nu Events", binnumber_mu-1, xMuMombins);
    h1_N1Rmu_x_MuPt[i]    = new TH1F(TString::Format("h1_N1Rmu_x_MuPt_mode%d", i), "N1Rmu_x_MuPt; Reco #mu Transverse Momentum [GeV]; Number of #nu Events", binnumber_mu-1, xMuPtbins);
    h1_N1Rmu_x_Q2[i]      = new TH1F(TString::Format("h1_N1Rmu_x_Q2_mode%d", i), "N1Rmu_x_Q2; Reco Q^{2} [GeV^{2}]; Number of #nu Events", binnumber_mu-1, xQ2bins);
    h1_N1Rmu_x_MuAngle[i] = new TH1F(TString::Format("h1_N1Rmu_x_MuAngle_mode%d", i), "N1Rmu_x_MuAngle; Cosince of angle b/w #mu and beam directions; Number of #nu Events", binnumber_mu-1, xMuAnglebins);

    h1_TrueN_x_Enu[i]     = new TH1F(TString::Format("h1_TrueN_x_Enu_mode%d", i), "TrueN_x_Enu; Reco Neutrino Energy [GeV]; Number of Truth Neutrons", binnumber_nu-1, xEnubins);
    h1_TrueN_x_MuMom[i]   = new TH1F(TString::Format("h1_TrueN_x_MuMom_mode%d", i), "TrueN_x_MuMom; Reco #mu Momentum [GeV]; Number of Truth Neutrons", binnumber_mu-1, xMuMombins);
    h1_TrueN_x_MuPt[i]    = new TH1F(TString::Format("h1_TrueN_x_MuPt_mode%d", i), "TrueN_x_MuPt; Reco #mu Transverse Momentum [GeV]; Number of #nu Events", binnumber_mu-1, xMuPtbins);
    h1_TrueN_x_Q2[i]      = new TH1F(TString::Format("h1_TrueN_x_Q2_mode%d", i), "TrueN_x_Q2; Reco Q^{2} [GeV^{2}]; Number of #nu Events", binnumber_mu-1, xQ2bins);
    h1_TrueN_x_MuAngle[i] = new TH1F(TString::Format("h1_TrueN_x_MuAngle_mode%d", i), "TrueN_x_MuAngle; Cosince of angle b/w #mu and beam directions; Number of #nu Events", binnumber_mu-1, xMuAnglebins);

    h1_TrueN_x_nTraveld[i]   = new TH1F(TString::Format("h1_TrueN_x_nTraveld_mode%d", i), "True_x_nTranveld; Neutron Travel Distance [cm]; Number of truth neutrons", binnumber_n-1, xnTraveldbins);
    h1_TrueN_x_nTraveldL[i]  = new TH1F(TString::Format("h1_TrueN_x_nTraveldL_mode%d", i), "True_x_nTranveldL; Longitudinal Neutron Travel Distance [cm]; Number of truth neutrons", binnumber_n2-1, xnTraveldLbins);
    h1_TrueN_x_nTraveldT[i]  = new TH1F(TString::Format("h1_TrueN_x_nTraveldT_mode%d", i), "True_x_nTranveldT; Transverse Neutron Travel Distance [cm]; Number of truth neutrons", binnumber_n-1, xnTraveldTbins);
    h1_TrueN_x_MuStp_NCap[i] = new TH1F(TString::Format("h1_TrueN_x_MuStp_NCap_mode%d", i), "True_x_MuStp_NCap; Distance b/w #mu Stopping and n Capture vertices [cm]; Number of truth neutrons", binnumber_n-1, xMuStp_NCapbins);
    h1_TrueN_x_nAngle[i]     = new TH1F(TString::Format("h1_TrueN_x_nAngle_mode%d", i), "True_x_nAngle; Cosince of angle b/w n and beam directions; Number of truth neutrons", binnumber_n3-1, xnAnglebins);
  }
  for (int i=0; i<5; i++) {
    h1_TaggedN_x_Enu[i]     = new TH1F(TString::Format("h1_TaggedN_x_Enu_mode%d", i), "TaggedN_x_Enu; Reco Neutrino Energy [GeV]; Number of Tagged Neutrons", binnumber_nu-1, xEnubins);
    h1_TaggedN_x_MuMom[i]   = new TH1F(TString::Format("h1_TaggedN_x_MuMom_mode%d", i), "TaggedN_x_MuMom; Reco #mu Momentum [GeV]; Number of #nu Events", binnumber_mu-1, xMuMombins);
    h1_TaggedN_x_MuPt[i]    = new TH1F(TString::Format("h1_TaggedN_x_MuPt_mode%d", i), "TaggedN_x_MuPt; Reco #mu Transverse Momentum [GeV]; Number of #nu Events", binnumber_mu-1, xMuPtbins);
    h1_TaggedN_x_Q2[i]      = new TH1F(TString::Format("h1_TaggedN_x_Q2_mode%d", i), "TaggedN_x_Q2; Reco Q^{2} [GeV^{2}]; Number of #nu Events", binnumber_mu-1, xQ2bins);
    h1_TaggedN_x_MuAngle[i] = new TH1F(TString::Format("h1_TaggedN_x_MuAngle_mode%d", i), "TaggedN_x_MuAngle; Cosince of angle b/w #mu and beam directions; Number of #nu Events", binnumber_mu-1, xMuAnglebins);

    h1_TaggedN_x_nTraveld[i]   = new TH1F(TString::Format("h1_TaggedN_x_nTraveld_mode%d", i), "Tagged_x_nTranveld; Neutron Travel Distance [cm]; Number of tagged neutrons", binnumber_n-1, xnTraveldbins);
    h1_TaggedN_x_nTraveldL[i]  = new TH1F(TString::Format("h1_TaggedN_x_nTraveldL_mode%d", i), "Tagged_x_nTranveldL; Longitudinal Neutron Travel Distance [cm]; Number of tagged neutrons", binnumber_n2-1, xnTraveldLbins);
    h1_TaggedN_x_nTraveldT[i]  = new TH1F(TString::Format("h1_TaggedN_x_nTraveldT_mode%d", i), "Tagged_x_nTranveldT; Transverse Neutron Travel Distance [cm]; Number of tagged neutrons", binnumber_n-1, xnTraveldTbins);
    h1_TaggedN_x_MuStp_NCap[i] = new TH1F(TString::Format("h1_TaggedN_x_MuStp_NCap_mode%d", i), "Tagged_x_MuStp_NCap; Distance b/w #mu Stopping and n Capture vertices [cm]; Number of tagged neutrons", binnumber_n-1, xMuStp_NCapbins);
    h1_TaggedN_x_nAngle[i]     = new TH1F(TString::Format("h1_TaggedN_x_nAngle_mode%d", i), "Tagged_x_nAngle; Cosince of angle b/w n and beam directions; Number of tagged neutrons", binnumber_n3-1, xnAnglebins);
  }
  
}

void NTagAnalysis::SetHistoFormat() {
  for (int i=0; i<TRUETYPE; i++) {
    h1_NTrueN[i] -> SetLineWidth(2);
    h1_NTrueN[i] -> SetTitleOffset(1.4, "Y");
    h1_NTrueN[i] -> SetTitleSize(0.035, "Y");
    h1_NTrueN[i] -> SetLabelSize(0.033, "Y");
  }
  h1_NTrueN[0] -> SetLineColor(kViolet+3); //All truth neutrons
  h1_NTrueN[1] -> SetLineColor(kAzure-4);  //truth H-n neutrons
  h1_NTrueN[2] -> SetLineColor(kTeal-5);   //truth Gd-n neutrons

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueNmultiplicity[i] -> SetLineWidth(2);
    h1_TrueNmultiplicity[i] -> SetTitleOffset(1.4, "Y");
    h1_TrueNmultiplicity[i] -> SetTitleSize(0.035, "Y");
    h1_TrueNmultiplicity[i] -> SetLabelSize(0.033, "Y");
  }
  h1_TrueNmultiplicity[0] -> SetLineColor(kAzure-1);  //CCQE
  h1_TrueNmultiplicity[1] -> SetLineColor(kOrange+8); //CC non-QE
  h1_TrueNmultiplicity[2] -> SetLineColor(kPink+1);   //CCRES+
  h1_TrueNmultiplicity[3] -> SetLineColor(kPink-8);   //CCRES++
  h1_TrueNmultiplicity[4] -> SetLineColor(kGray+1);   //CCRES0
  h1_TrueNmultiplicity[5] -> SetLineColor(kTeal+9);   //NC

  h1_TotGammaE -> SetLineWidth(2);
  h1_TotGammaE -> SetLineColor(kAzure-4);
  h1_TotGammaE -> SetTitleOffset(1.4, "Y");
  h1_TotGammaE -> SetTitleSize(0.035, "Y");
  h1_TotGammaE -> SetLabelSize(0.033, "Y");

  for (int i=0; i<2; i++) {
    h1_Enureso_CCQE[i]          -> SetLineWidth(2);
    h1_Enureso_CC2p2h[i]        -> SetLineWidth(2);
    h1_Enureso_CCRES_deltap[i]  -> SetLineWidth(2);
    h1_Enureso_CCRES_deltapp[i] -> SetLineWidth(2);
    h1_Enureso_CCRES_delta0[i]  -> SetLineWidth(2);
    h1_Enureso_CCOther[i]       -> SetLineWidth(2);
    h1_Enureso_NC[i]            -> SetLineWidth(2);

    h1_Enureso_CCQE[i]          -> SetLineColor(kAzure-1);
    h1_Enureso_CC2p2h[i]        -> SetLineColor(kAzure-5);
    h1_Enureso_CCRES_deltap[i]  -> SetLineColor(kPink+1);
    h1_Enureso_CCRES_deltapp[i] -> SetLineColor(kPink-8);
    h1_Enureso_CCRES_delta0[i]  -> SetLineColor(kGray+1);
    h1_Enureso_CCOther[i]       -> SetLineColor(kCyan-6);
    h1_Enureso_NC[i]            -> SetLineColor(kTeal+9);

    h1_Enureso_CCQE[i]          -> SetFillColor(kAzure-1);
    h1_Enureso_CC2p2h[i]        -> SetFillColor(kAzure-5);
    h1_Enureso_CCRES_deltap[i]  -> SetFillColor(kPink+1);
    h1_Enureso_CCRES_deltapp[i] -> SetFillColor(kPink-8);
    h1_Enureso_CCRES_delta0[i]  -> SetFillColor(kGray+1);
    h1_Enureso_CCOther[i]       -> SetFillColor(kCyan-6);
    h1_Enureso_NC[i]            -> SetFillColor(kTeal+9);

    h1_Enureso_CCQE_trueN[i]          -> SetLineWidth(2);
    h1_Enureso_CC2p2h_trueN[i]        -> SetLineWidth(2);
    h1_Enureso_CCRES_deltap_trueN[i]  -> SetLineWidth(2);
    h1_Enureso_CCRES_deltapp_trueN[i] -> SetLineWidth(2);
    h1_Enureso_CCRES_delta0_trueN[i]  -> SetLineWidth(2);
    h1_Enureso_NC_trueN[i]            -> SetLineWidth(2);

    h1_Enureso_CCQE_trueN[i]          -> SetLineColor(kAzure-1);
    h1_Enureso_CC2p2h_trueN[i]        -> SetLineColor(kAzure-5);
    h1_Enureso_CCRES_deltap_trueN[i]  -> SetLineColor(kPink+1);
    h1_Enureso_CCRES_deltapp_trueN[i] -> SetLineColor(kPink-8);
    h1_Enureso_CCRES_delta0_trueN[i]  -> SetLineColor(kGray+1);
    h1_Enureso_CCOther_trueN[i]       -> SetLineColor(kCyan-6);
    h1_Enureso_NC_trueN[i]            -> SetLineColor(kTeal+9);

    h1_Enureso_CCQE_trueN[i]          -> SetFillColor(kAzure-1);
    h1_Enureso_CC2p2h_trueN[i]        -> SetFillColor(kAzure-5);
    h1_Enureso_CCRES_deltap_trueN[i]  -> SetFillColor(kPink+1);
    h1_Enureso_CCRES_deltapp_trueN[i] -> SetFillColor(kPink-8);
    h1_Enureso_CCRES_delta0_trueN[i]  -> SetFillColor(kGray+1);
    h1_Enureso_CCOther_trueN[i]       -> SetFillColor(kCyan-6);
    h1_Enureso_NC_trueN[i]            -> SetFillColor(kTeal+9);
  }
}



void NTagAnalysis::InitNeutrons() {
  AllTruthNeutrons     = 0;
  TruthHNeutrons       = 0;
  TruthGdNeutrons      = 0;
  AllTruthCCQENeutrons = 0;
  TruthCCQEHNeutrons   = 0;
  TruthCCQEGdNeutrons  = 0;
  AllTruthNeutronsinFV = 0;
  TruthHNeutronsinFV   = 0;
  TruthGdNeutronsinFV  = 0;

  PreEff   = 0.;
  PreHEff  = 0.;
  PreGdEff = 0.;

  PreEffinFV   = 0.;
  PreHEffinFV  = 0.;
  PreGdEffinFV = 0.;

  for (int i=0; i<WINSTEP; i++) {
    AllTruthNeutronsinSearch[i] = 0;
    TruthHNeutronsinSearch[i]   = 0;
    TruthGdNeutronsinSearch[i]  = 0;

    AllTruthNeutronsinSearchFV[i] = 0;
    TruthHNeutronsinSearchFV[i]   = 0;
    TruthGdNeutronsinSearchFV[i]  = 0;

    TruthDecayeinSearch[i]   = 0;

    AllCandidatesinWin[i]              = 0;
    TruthNeutroninCandidatesinWin[i]   = 0;
    TruthHNeutroninCandidatesinWin[i]  = 0;
    TruthGdNeutroninCandidatesinWin[i] = 0;
    TruthDecayeinCandidatesinWin[i]    = 0;
    TruthAccNoiseinCandidatesinWin[i]  = 0;

    AllCandidatesinWinFV[i]              = 0;
    TruthNeutroninCandidatesinWinFV[i]   = 0;
    TruthHNeutroninCandidatesinWinFV[i]  = 0;
    TruthGdNeutroninCandidatesinWinFV[i] = 0;
    TruthDecayeinCandidatesinWinFV[i]    = 0;
    TruthAccNoiseinCandidatesinWinFV[i]  = 0;

    for (int j=0; j<CUTSTEP; j++) {
      TaggedTruthNeutronsinWin[i][j]   = 0;
      TaggedTruthHNeutronsinWin[i][j]  = 0;
      TaggedTruthGdNeutronsinWin[i][j] = 0;
      MisTaggedDecayeinNlike[i][j]     = 0;
      MisTaggedAccNoiseinNlike[i][j]   = 0;
      AllNlikeCandidates[i][j]         = 0;

      TaggedTruthNeutronsinWinFV[i][j]   = 0;
      TaggedTruthHNeutronsinWinFV[i][j]  = 0;
      TaggedTruthGdNeutronsinWinFV[i][j] = 0;
      MisTaggedDecayeinNlikeFV[i][j]     = 0;
      MisTaggedAccNoiseinNlikeFV[i][j]   = 0;
      AllNlikeCandidatesFV[i][j]         = 0;

      TaggedTruthDecayeinWin[i][j]          = 0;
      MisTaggedTruthNeutronsinElike[i][j]   = 0;
      MisTaggedTruthHNeutronsinElike[i][j]  = 0;
      MisTaggedTruthGdNeutronsinElike[i][j] = 0;
      MisTaggedAccNoiseinElike[i][j]        = 0;
      AllElikeCandidates[i][j]              = 0;

      NoiseRate[i][j]  = 0.;
      eNoiseRate[i][j] = 0.;
    }

    NNEffinWin[i]    = 0.;
    NNHEffinWin[i]   = 0.;
    NNGdEffinWin[i]  = 0.;
    eNNEffinWin[i]   = 0.;
    eNNHEffinWin[i]  = 0.;
    eNNGdEffinWin[i] = 0.;

    OverallEffinWin[i]    = 0.;
    OverallHEffinWin[i]   = 0.;
    OverallGdEffinWin[i]  = 0.;
    eOverallEffinWin[i]   = 0.;
    eOverallHEffinWin[i]  = 0.;
    eOverallGdEffinWin[i] = 0.;

    WindowMax[i]  = 0.;
    eWindowMax[i] = 0.;
  }

  for (int i=0; i<CUTSTEP; i++) {
    NeutrinoEventswNoNlike[i]         = 0;
    NeutrinoEventswNlikes[i]          = 0;
    NeutrinoEventswOneNlike[i]        = 0;
    NeutrinoEventswOneNlikeDecaye[i]  = 0;
    NeutrinoEventswNoTruthNeutrons[i] = 0;

    NNEff[i]    = 0.;
    NNHEff[i]   = 0.;
    NNGdEff[i]  = 0.;
    eNNEff[i]   = 0.;
    eNNHEff[i]  = 0.;
    eNNGdEff[i] = 0.;

    NNEffinFV[i]   = 0.;
    NNHEffinFV[i]  = 0.;
    NNGdEffinFV[i] = 0.;

    OverallEff[i]    = 0.;
    OverallHEff[i]   = 0.;
    OverallGdEff[i]  = 0.;
    eOverallEff[i]   = 0.;
    eOverallHEff[i]  = 0.;
    eOverallGdEff[i] = 0.;

    OverallEffinFV[i]   = 0.;
    OverallHEffinFV[i]  = 0.;
    OverallGdEffinFV[i] = 0.;

    Purity[i]  = 0.;
    ePurity[i] = 0.;
  }

  for (int i=0; i<CUTSTEP-1; i++) {
    FillPurity[i]     = 0.;
    FillNoiseRate[i]  = 0.;
    FillTMVATH[i]     = 0.;

    FillePurity[i]    = 0.;
    FilleNoiseRate[i] = 0.;
    FilleTMVATH[i]    = 0.;
  }
}


//Generated neutrons, but not nessariliry captured neutrons
float NTagAnalysis::GetGenBefSIMom(CC0PiNumu *numu, Int_t *Iorgvc, Int_t *Iflvc) {
  float NeutronMom = 0.;
  for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
    //std::cout << "Particle[" << iprm << "]=" << numu->var<int>("Ipvc", iprm)
    //                                         << ", Iflvc=" << Iflvc[iprm] 
    //                                         << ", Ichvc=" << numu->var<int>("Ichvc", iprm)
    //                                         << ", Iorgvc=" <<Iorgvc[iprm] << std::endl;
    if (numu->var<int>("Ipvc", iprm)==static_cast<int>(PDGPID::NEUTRON) && Iorgvc[iprm]!=0) {
      //GenPrmNeutrons++;
      if (numu->var<int>("Ipvc", Iorgvc[iprm]-1)==static_cast<int>(PDGPID::NEUTRON) &&
          Iflvc[iprm]==static_cast<int>(NEUTINT::HADRONPROD)) 
      {
        //std::cout << " --> intermediate n" << std::endl;
        //GenPrmNeutrons--;
      }
      else {
        NeutronMom = numu->var<float>("Abspvc", iprm);
      }
    }

  }
  return NeutronMom;
}

int NTagAnalysis::GetTrueNBefSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]) {
//int NTagAnalysis::GetTrueNBefSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3], Float_t pscnd[][3]) {
  int TrueNBefSI = 0;

  std::vector<float> VtxPrntList;
  std::vector<float> VtxScndList;
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    if (numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::GAMMA) && 
        numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::NEUTRON) &&
        std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::MUON) &&
        numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::NEUTRONCAPTURE) &&
        iprntidx[iscnd]<0) 
    {
      //Find gamma from different neutrons
      float d_vtxprnt = std::sqrt( vtxprnt[iscnd][0]*vtxprnt[iscnd][0] +
                                   vtxprnt[iscnd][1]*vtxprnt[iscnd][1] +
                                   vtxprnt[iscnd][2]*vtxprnt[iscnd][2] );
      float vtxscndX  = numu->var<float>("vtxscnd", iscnd, 0);
      float vtxscndY  = numu->var<float>("vtxscnd", iscnd, 1);
      float vtxscndZ  = numu->var<float>("vtxscnd", iscnd, 2);
      float d_vtxscnd = std::sqrt( vtxscndX*vtxscndX +
                                   vtxscndY*vtxscndY +
                                   vtxscndZ*vtxscndZ );

      //First gamma
      if (VtxScndList.size()==0) {
        VtxPrntList.push_back(d_vtxprnt);
        VtxScndList.push_back(d_vtxscnd);
        if (iprntidx[ iprntidx[iscnd]-1 ]==0) TrueNBefSI++;
      }
      else {
        bool NewNeutron = false;
        for (UInt_t in=0; in<VtxPrntList.size(); in++) {
          if (VtxPrntList.at(in)!=d_vtxprnt) NewNeutron = true;
          else {
            for (UInt_t jn=0; jn<VtxScndList.size(); jn++) {
              if (VtxScndList.at(jn)!=d_vtxscnd) NewNeutron = true;
              else NewNeutron = false;
            }
          }
        }
  
        if (NewNeutron) {
          VtxScndList.push_back(d_vtxscnd);
          VtxPrntList.push_back(d_vtxprnt);
          if (iprntidx[ iprntidx[iscnd]-1 ]==0) TrueNBefSI++;
        }
      }

    }
  }
  return TrueNBefSI;
}

int NTagAnalysis::GetTrueNAftSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]) {
//int NTagAnalysis::GetTrueNAftSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3], Float_t pscnd[][3]) {
  int TrueNAftSI = 0;

  std::vector<float> VtxPrntList;
  std::vector<float> VtxScndList;
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    if (numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::GAMMA) && 
        numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::NEUTRON) &&
        std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::MUON) &&
        numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::NEUTRONCAPTURE) &&
        iprntidx[iscnd]>=0) 
    {
      //Find gamma from different neutrons
      float d_vtxprnt = std::sqrt( vtxprnt[iscnd][0]*vtxprnt[iscnd][0] +
                                   vtxprnt[iscnd][1]*vtxprnt[iscnd][1] +
                                   vtxprnt[iscnd][2]*vtxprnt[iscnd][2] );
      float vtxscndX  = numu->var<float>("vtxscnd", iscnd, 0);
      float vtxscndY  = numu->var<float>("vtxscnd", iscnd, 1);
      float vtxscndZ  = numu->var<float>("vtxscnd", iscnd, 2);
      float d_vtxscnd = std::sqrt( vtxscndX*vtxscndX +
                                   vtxscndY*vtxscndY +
                                   vtxscndZ*vtxscndZ );

      //First gamma
      if (VtxScndList.size()==0) {
        VtxPrntList.push_back(d_vtxprnt);
        VtxScndList.push_back(d_vtxscnd);
        //if (iprntidx[ iprntidx[iscnd]-1 ]==0) TrueNAftSI++;
        if (iprntidx[iscnd]>=0) TrueNAftSI++;
      }
      else {
        bool NewNeutron = false;
        for (UInt_t in=0; in<VtxPrntList.size(); in++) {
          if (VtxPrntList.at(in)!=d_vtxprnt) NewNeutron = true;
          else {
            for (UInt_t jn=0; jn<VtxScndList.size(); jn++) {
              if (VtxScndList.at(jn)!=d_vtxscnd) NewNeutron = true;
              else NewNeutron = false;
            }
          }
        }
  
        if (NewNeutron) {
          VtxScndList.push_back(d_vtxscnd);
          VtxPrntList.push_back(d_vtxprnt);
          //if (iprntidx[ iprntidx[iscnd]-1 ]==0) TrueNAftSI++;
          if (iprntidx[iscnd]>=0) TrueNAftSI++;
        }
      }

    }
  }
  return TrueNAftSI;
}


void NTagAnalysis::GetTruthNeutrons(float NTrueN,
                                    CC0PiNumu* numu, 
                                    std::vector<int> *Type,
                                    std::vector<float> *E,
                                    std::vector<float> *DWall)  
{
  int mode = TMath::Abs(numu->var<int>("mode"));

  AllTruthNeutrons += NTrueN;
  //h1_NTrueN[0] -> Fill(NTrueN);
  if (mode==1) {
    //h1_NTrueN[0] -> Fill(NTrueN);
    AllTruthCCQENeutrons += NTrueN;
  }

  //Truth neutrons event by event
  int NumTruthHNeutrons  = 0;
  int NumTruthGdNeutrons = 0;
  int NumTruthCCQEHNeutrons  = 0;
  int NumTruthCCQEGdNeutrons = 0;

  for (UInt_t jentry=0; jentry<E->size(); ++jentry) {
    //Truth neutrons
    if (Type->at(jentry)==2) {
      h1_TotGammaE -> Fill(E->at(jentry));

      //in FV
      if (DWall->at(jentry)>0.) AllTruthNeutronsinFV++;

      //Truth H-n neutrons
      if (E->at(jentry) < 6.) {
        TruthHNeutrons++;
        NumTruthHNeutrons++;

        if (mode==1) {
          TruthCCQEHNeutrons++;
          NumTruthCCQEHNeutrons++;
        }

        if (DWall->at(jentry)>0.) TruthHNeutronsinFV++;
      }
      //Truth Gd-n neutrons
      if (E->at(jentry) > 6.) {
        TruthGdNeutrons++;
        NumTruthGdNeutrons++;

        if (mode==1) {
          TruthCCQEGdNeutrons++;
          NumTruthCCQEGdNeutrons++;
        }

        if (DWall->at(jentry)>0.) TruthGdNeutronsinFV++;
      }
    }
  }

  //h1_NTrueN[1] -> Fill(NumTruthHNeutrons);
  //h1_NTrueN[2] -> Fill(NumTruthGdNeutrons);
  h1_NTrueN[1] -> Fill(NumTruthCCQEHNeutrons);
  h1_NTrueN[2] -> Fill(NumTruthCCQEGdNeutrons);
}


void NTagAnalysis::GetTruthNeutronsIntType(CC0PiNumu* numu, float NTrueN) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();

  //CCQE(1p1h)
  if (mode==1) {
    NTrueN_CCQE += NTrueN;
    NTrueN_CCQE_osc += NTrueN*OscProb;
    h1_TrueNmultiplicity[0] -> Fill(NTrueN, OscProb);
  }
  //CC 2p2h
  if (mode>=2 && mode<=10) {
    NTrueN_CC2p2h += NTrueN;
    NTrueN_CC2p2h_osc += NTrueN*OscProb;
    h1_TrueNmultiplicity[1] -> Fill(NTrueN, OscProb);
  }
  //CC other
  if (mode>10 && mode<=30) {
    NTrueN_CCOther += NTrueN;
    NTrueN_CCOther_osc += NTrueN*OscProb;
    h1_TrueNmultiplicity[2] -> Fill(NTrueN, OscProb);
  }
  //NC
  if (mode>=31) {
    NTrueN_NC += NTrueN;
    NTrueN_NC_osc += NTrueN;
    h1_TrueNmultiplicity[3] -> Fill(NTrueN);
  }
}

void NTagAnalysis::TrueNCapVtxProfile(std::vector<int> *Type, std::vector<float> *tagvx, 
                                                              std::vector<float> *tagvy, 
                                                              std::vector<float> *tagvz) 
{
  for (UInt_t itaggable=0; itaggable<Type->size(); itaggable++) {
    if (Type->at(itaggable)==2) {
      float NCapVtx[3] = {0., 0., 0.};
      NCapVtx[0] = tagvx->at(itaggable);
      NCapVtx[1] = tagvy->at(itaggable);
      NCapVtx[2] = tagvz->at(itaggable);
      h2_TrueNCapVtxXY -> Fill(NCapVtx[0]/100., NCapVtx[1]/100.);
      h2_TrueNCapVtxRZ -> Fill( (NCapVtx[0]*NCapVtx[0]+NCapVtx[1]*NCapVtx[1])/10000., NCapVtx[2]/100. );
    }
  }
}

void NTagAnalysis::GetTruthNeutronsinSearch(UInt_t truthneutrons, 
                                            std::vector<int> *Type,
                                            std::vector<float> *t,
                                            float WinMin,
                                            std::vector<float> *E,
                                            std::vector<float> *DWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
      if (Type->at(jentry)==2) {
        if (iwin==0 && t->at(jentry) > WinMin) {
          AllTruthNeutronsinSearch[iwin]++;
          if (DWall->at(jentry) > 0.) AllTruthNeutronsinSearchFV[iwin]++;

          if (E->at(jentry) < 6.) {
            TruthHNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthHNeutronsinSearchFV[iwin]++;
          }
          if (E->at(jentry) > 6.) {
            TruthGdNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthGdNeutronsinSearchFV[iwin]++;
          } 
        }
        if (iwin!=0 && t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) {
          AllTruthNeutronsinSearch[iwin]++;
          if (DWall->at(jentry) > 0.) AllTruthNeutronsinSearchFV[iwin]++;

          if (E->at(jentry) < 6.) {
            TruthHNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthHNeutronsinSearchFV[iwin]++;
          }
          if (E->at(jentry) > 6.) {
            TruthGdNeutronsinSearch[iwin]++;
            if (DWall->at(jentry) > 0.) TruthGdNeutronsinSearchFV[iwin]++;
          } 
        }
        //if (t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthNeutronsinSearch[iwin]++;
      }
    }
  }
}

void NTagAnalysis::GetTruthDecayeinSearch(UInt_t truthneutrons, 
                                            std::vector<int> *Type,
                                            std::vector<float> *t,
                                            float WinMin) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
      if (Type->at(jentry)==1) {
        if (iwin==0 && t->at(jentry) > WinMin) TruthDecayeinSearch[iwin]++;
        if (iwin!=0 && t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthDecayeinSearch[iwin]++;
        //if (t->at(jentry) > WinMin && t->at(jentry) < varwindowmax) TruthDecayeinSearch[iwin]++;
      }
    }
  }
}



bool NTagAnalysis::DecayelikeChecker(bool etagmode, float NHits, float FitT) {
  bool etagboxin = false;
  if (etagmode) {
  	if (NHits>50 && FitT<20) etagboxin = true;
  }
  return etagboxin;
}

void NTagAnalysis::TruthBreakdowninWindow(std::vector<float> *TagClass, 
                                          std::vector<float> *t,
                                          std::vector<float> *DWall,
                                          std::vector<float> *TagIndex,
                                          std::vector<float> *Label,
                                          std::vector<float> *FitT,
                                          std::vector<float> *TagDWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    for (UInt_t ican=0; ican<TagClass->size(); ++ican) {

      //if (Label->at(ican)==0) h1_hitsearch[0] -> Fill(FitT->at(ican));
      //if (Label->at(ican)==1) h1_hitsearch[1] -> Fill(FitT->at(ican));
      //if (Label->at(ican)==2 || Label->at(ican)==3) h1_hitsearch[2] -> Fill(FitT->at(ican));
      
      bool inwindow = false;  //Flag that indicates this candidate is in the time window, or not.
      bool inFV     = false;  //Flag that indicates this candidate is in FV, or not.
      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {
          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
          if (DWall->at(jentry) > 0.) inFV = true;
        }
      }

      //If this candidate is in the time window, count correponded truth neutrons and decay electorns
      if (inwindow==true) {
        AllCandidatesinWin[iwin]++;
        if (Label->at(ican)==2 || Label->at(ican)==3) TruthNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==2) TruthHNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==3) TruthGdNeutroninCandidatesinWin[iwin]++;
        if (Label->at(ican)==1) TruthDecayeinCandidatesinWin[iwin]++;

        if (inFV==true) {
          AllCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==2 || Label->at(ican)==3) TruthNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==2) TruthHNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==3) TruthGdNeutroninCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==1) TruthDecayeinCandidatesinWinFV[iwin]++;
        }
      }

      //If this candidate is in the time window, count correponded truth noise
      if (FitT->at(ican) < varwindowmax) {
        AllCandidatesinWin[iwin]++;
        if (Label->at(ican)==0) TruthAccNoiseinCandidatesinWin[iwin]++;

        if (TagDWall->at(ican) > 0.) {
          AllCandidatesinWinFV[iwin]++;
          if (Label->at(ican)==0) TruthAccNoiseinCandidatesinWinFV[iwin]++;
        }
      }

    }
  }
}


void NTagAnalysis::GetNlikeCandidatesinWindow(std::vector<float> *t,
                                              std::vector<float> *DWall,
                                              std::vector<float> *TagIndex,
                                              bool etagmode,
                                              std::vector<float> *NHits,
                                              std::vector<float> *FitT,
                                              std::vector<float> *TagOut,
                                              std::vector<float> *Label,
                                              std::vector<float> *TagDWall) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);

    for (UInt_t ican=0; ican<TagOut->size(); ican++) {
      //Flag that indicates this candidate is in the time window, or not.
      bool inwindow = false;
      //Flag that indicates this candidate is in FV, or not.
      //bool inFV     = false;
      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {

          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
          //if (DWall->at(jentry) > 0.) inFV = true;
        }
      }

      //If this candidate is in the time window, judge it is n-like or not.
      if (inwindow==true) {

        //threshold scan
        for (int ith=0; ith<CUTSTEP; ith++) {
          //Threshold
          if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
          if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

          if (etagmode) {
            //bool etagboxin = this->DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican));
            bool etagboxin = false;
            if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==2) TaggedTruthHNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==3) TaggedTruthGdNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) MisTaggedDecayeinNlike[iwin][ith]++;

            //if (inFV) {
            //  if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==2) TaggedTruthHNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==3) TaggedTruthGdNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) MisTaggedDecayeinNlikeFV[iwin][ith]++;
            //}
          }
          else {
            if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==2) TaggedTruthHNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==3) TaggedTruthGdNeutronsinWin[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) MisTaggedDecayeinNlike[iwin][ith]++;

            //if (inFV) {
            //  if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) TaggedTruthNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==2) TaggedTruthHNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==3) TaggedTruthGdNeutronsinWinFV[iwin][ith]++;
            //  if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) MisTaggedDecayeinNlikeFV[iwin][ith]++;
            //}
          }

        } //threshold scan
      }

      //Noise contamination in n-like candidates
      for (int ith=0; ith<CUTSTEP; ith++) {
        if (FitT->at(ican) < varwindowmax) {
          if (etagmode) {
            bool etagboxin = false;
            if (etagmode) {
              if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
            }
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==0) MisTaggedAccNoiseinNlike[iwin][ith]++;
            //if (TagDWall->at(ican) > 0.) {
            //  if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==0) MisTaggedAccNoiseinNlikeFV[iwin][ith]++;
            //}
          }
          else {
            if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==0) MisTaggedAccNoiseinNlike[iwin][ith]++;
            //if (TagDWall->at(ican) > 0.) {
            //  if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==0) MisTaggedAccNoiseinNlikeFV[iwin][ith]++;
            //}
          }
        }
      }

    } //candidates loop
  } //window scan
}


void NTagAnalysis::GetElikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label) 
{
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);

    for (UInt_t ican=0; ican<TagOut->size(); ican++) {
      //Flag that indicates this candidate is in the time window, or not.
      bool inwindow = false;

      //Find corresponded truth info that matches with ican candidate
      for (UInt_t jentry=0; jentry<t->size(); ++jentry) {
        if (TagIndex->at(ican)!=-1 && jentry==(UInt_t)TagIndex->at(ican)) {

          //Check this candidate is in the time window, or not through true time info
          //if not, skip this ican
          if (t->at(jentry) < varwindowmax) inwindow = true;
        }
      }

      //If this candidate is in the time window, judge it is n-like or not.
      if (inwindow==true) {

        //threshold scan
        for (int ith=0; ith<CUTSTEP; ith++) {
          //Threshold
          if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
          if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;

          if (etagmode) {
            //bool etagboxin = this->DecayelikeChecker(etagmode, NHits->at(ican), FitT->at(ican));
            bool etagboxin = false;
            if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==1) TaggedTruthDecayeinWin[iwin][ith]++;

            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && (Label->at(ican)==2 || Label->at(ican)==3)) MisTaggedTruthNeutronsinElike[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==2) MisTaggedTruthHNeutronsinElike[iwin][ith]++;
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==3) MisTaggedTruthGdNeutronsinElike[iwin][ith]++;
          }
        } //threshold scan
      }

      //Noise contamination in n-like candidates
      for (int ith=0; ith<CUTSTEP; ith++) {
        if (FitT->at(ican) < varwindowmax) {
          if (etagmode) {
            bool etagboxin = false;
            if (etagmode) {
              if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
            }
            if (TagOut->at(ican)>TMVATH[ith] && etagboxin==true && Label->at(ican)==0) MisTaggedAccNoiseinElike[iwin][ith]++;
          }
        }
      }

    } //candidates loop
  } //window scan
}

void NTagAnalysis::Set1RmuonSamplewNTag(bool NoNlike, CC0PiNumu* numu, float theta, float thetamin, float thetamax) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  float RecoEnu = numu->var<float>("erec");

  if (theta>thetamin && theta<thetamax) {

    if (NoNlike) {

      //All CC
      if (mode<31) {
        //### [CATEGORY: w/o tagged neutrons] ###
        h1_All_NoOsc_woNeutron        -> Fill(RecoEnu/1000.);
        h1_All_OscProbRatio_woNeutron -> Fill(RecoEnu/1000., OscProb);

        //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          NoOscwoTagN++;
          OscwoTagN += OscProb;
        }
      }
    }


    //CCQE(1p1h)
    if (mode==1) {
      if (NoNlike) {
        h1_OscProb_woNeutron[0] -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCQE_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[0] -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCQE_wTagN += OscProb;
      }
    }

    //CC 2p2h
    if (mode>=2 && mode<=10) {
      if (NoNlike) {
        h1_OscProb_woNeutron[1] -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCnonQE_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[1] -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCnonQE_wTagN += OscProb;
      }
    }

    //CC non-QE
    if (mode>=2 && mode<=30) {
      if (NoNlike) h1_OscProbCCnonQE_woNeutron -> Fill(RecoEnu/1000., OscProb);
      else h1_OscProbCCnonQE_wNeutron -> Fill(RecoEnu/1000., OscProb);
    }

    //CC other (CCRES+CC other)
    if (mode>10 && mode<=30) {
      if (NoNlike) h1_OscProbCCOther_woNeutron -> Fill(RecoEnu/1000., OscProb);
      else h1_OscProbCCOther_wNeutron -> Fill(RecoEnu/1000., OscProb);
    }

    //CC RES (Delta+)
    if (mode==13) {
      if (NoNlike) {
        h1_OscProb_woNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESp_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[3]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESp_wTagN += OscProb;
      }
    }
    //CC RES (Delta++)
    if (mode==11) {
      if (NoNlike) {
        h1_OscProb_woNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESpp_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[4]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRESpp_wTagN += OscProb;
      }
    }
    //CC RES (Delta0)
    if (mode==12) {
      if (NoNlike) {
        h1_OscProb_woNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRES0_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[5]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCRES0_wTagN += OscProb;
      }
    }

    //CC Others
    if (mode>=14 && mode<=30) {
      if (NoNlike) {
        h1_OscProb_woNeutron[6]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCOther_woTagN += OscProb;
      }
      else {
        h1_OscProb_wNeutron[6]      -> Fill(RecoEnu/1000., OscProb);
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedCCOther_wTagN += OscProb;
      }
    }

    //NC
    if (mode>=31) {

      if (NoNlike) {

        //### [CATEGORY: w/o tagged neutrons] ###
        h1_All_NoOsc_woNeutron        -> Fill(RecoEnu/1000.);
        h1_All_OscProbRatio_woNeutron -> Fill(RecoEnu/1000.);

        //Count oscillated neutrino events within [0.25 GeV, 1.5 GeV]
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          NoOscwoTagN++;
          OscwoTagN ++;

          OscillatedNC_woTagN++;
        }

        h1_OscProb_woNeutron[2] -> Fill(RecoEnu/1000.);
      }
      else {
        h1_OscProb_wNeutron[2] -> Fill(RecoEnu/1000.);

        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) OscillatedNC_wTagN++;
      }
    }

  } //muon angle cut
}


void NTagAnalysis::GetNeutrinoEventswNTag(std::vector<float> *TagOut,
                                          std::vector<float> *TagIndex,
                                          std::vector<float> *NHits,
                                          std::vector<float> *FitT,
                                          std::vector<float> *Label,
                                          float NTrueN,
                                          bool etagmode,
                                          CC0PiNumu* numu,
                                          NeutrinoOscillation neuosc,
                                          int NCUT,
                                          float theta, float thetamin, float thetamax) 
{
  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;

  for (int ith=0; ith<CUTSTEP; ith++) {

    //Count the number of tagged neutrons
    int NumTaggedNeutrons       = 0;  //Number of n-like candidates of this event
    int NumTruthNeutronsinNlike = 0;  //Number of truth neutrons in n-like candidates of this event
    int NumTruthDecayeinNlike   = 0;  //Number of truth decay-e in n-like candidates of this event
    FlagReset();

    for (UInt_t ican=0; ican<TagOut->size(); ++ican) {

      //Check whether this candidate is n-like or e-like(for e-tagging ON)
      bool etagboxin = false;
      if (etagmode){
        if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false) NumTaggedNeutrons++;
        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
        if (TagOut->at(ican)>TMVATH[ith] && etagboxin==false && Label->at(ican)==1) NumTruthDecayeinNlike++;
      }
      else {
        if (TagOut->at(ican)>TMVATH[ith]) NumTaggedNeutrons++;
        if (TagOut->at(ican)>TMVATH[ith] && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
        if (TagOut->at(ican)>TMVATH[ith] && Label->at(ican)==1) NumTruthDecayeinNlike++;
      }       
    }

    if (NumTaggedNeutrons==0) NoNlike = true;
    if (NumTaggedNeutrons>=1) nonzeroTaggedNeutrons = true;
    if (NumTaggedNeutrons==1) OnlyOneNlike = true;
    if (NumTaggedNeutrons==1 && NumTruthDecayeinNlike!=0) OnlyOneisDecaye = true;
    if (NumTruthNeutronsinNlike==0) NoNeutron = true;


    //Get reconstructed energy distribution w/(o) tagged neutrons
    if (ith==NCUT) this -> Set1RmuonSamplewNTag(NoNlike, numu, theta, thetamin, thetamax);
    

    //=== w/o tagged neutrons ===
    if (NoNlike==true) {
      NeutrinoEventswNoNlike[ith]+=neuosc.OscProbCalculator(numu, false);

      if (ith==NCUT) {

        //Neutrino energy resolution
        test1++;

        //See neutrino energy at osillation maximum
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          //All interactions
          h1_Enureso_All[0] -> Fill(EnuReso);
          //CC non-QE
          if (mode>=2 && mode<=30) h1_Enureso_CCnonQE[0] -> Fill(EnuReso);
          //CCQE(1p1h)
          if (mode==1) h1_Enureso_CCQE[0] -> Fill(EnuReso);
          //CC-2p2h
          if (mode>=2 && mode<=10) h1_Enureso_CC2p2h[0] -> Fill(EnuReso);
          //CC RES(Delta++)
          if (mode==11) h1_Enureso_CCRES_deltapp[0] -> Fill(EnuReso);
          //CC RES(Delta0)
          if (mode==12) h1_Enureso_CCRES_delta0[0] -> Fill(EnuReso);
          //CC RES(Delta+)
          if (mode==13) h1_Enureso_CCRES_deltap[0] -> Fill(EnuReso);
          //CC-other
          //should be included CCRES?
          if (mode>=14 && mode<=30) h1_Enureso_CCOther[0] -> Fill(EnuReso);
          //NC
          if (mode>=31) h1_Enureso_NC[0] -> Fill(EnuReso);
        }
        
      }
      
    }
    

    //=== w/ tagged neutrons ===
    if (nonzeroTaggedNeutrons==true) {
      NeutrinoEventswNlikes[ith]+=neuosc.OscProbCalculator(numu, false);

      if (ith==NCUT) {

        //Neutrino energy resolution
        test2++;

        //See neutrino energy at osillation maximum
        if (RecoEnu/1000. > 0.25 && RecoEnu/1000. < 1.5) {
          //All interactions
          h1_Enureso_All[1] -> Fill(EnuReso);
          //CC non-QE
          if (mode>=2 && mode<=30) h1_Enureso_CCnonQE[1] -> Fill(EnuReso);
          //CCQE(1p1h)
          if (mode==1) h1_Enureso_CCQE[1] -> Fill(EnuReso);
          //CC-2p2h
          if (mode>=2 && mode<=10) h1_Enureso_CC2p2h[1] -> Fill(EnuReso);
          //CC RES(Delta++)
          if (mode==11) h1_Enureso_CCRES_deltapp[1] -> Fill(EnuReso);
          //CC RES(Delta0)
          if (mode==12) h1_Enureso_CCRES_delta0[1] -> Fill(EnuReso);
          //CC RES(Delta+)
          if (mode==13) h1_Enureso_CCRES_deltap[1] -> Fill(EnuReso);
          //CC-other(not include CCRES)
          //should be included CCRES?
          if (mode>=14 && mode<=30) h1_Enureso_CCOther[1] -> Fill(EnuReso);
          //NC
          if (mode>=31) h1_Enureso_NC[1] -> Fill(EnuReso);
        }
      }
    }


    //See neutrino events that have one n-like candidate
    //if (OnlyOneNlike==true) NeutrinoEventswOneNlike[0][ith]++;
    //if (OnlyOneNlike==true) NeutrinoEventswOneNlike[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (OnlyOneNlike==true) NeutrinoEventswOneNlike[ith]+=neuosc.OscProbCalculator(numu, false);

    //See neutrino events that have one n-like candidate, but it is truth decay-e
    //if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[0][ith]++;
    //if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (OnlyOneisDecaye==true) NeutrinoEventswOneNlikeDecaye[ith]+=neuosc.OscProbCalculator(numu, false);

    //See neutrino events that have no tagged truth neutrons
    //if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[0][ith]++;
    //if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[0][ith]+=neuosc.OscProbCalculator(numu, false);
    if (nonzeroTaggedNeutrons==true && NoNeutron==true) NeutrinoEventswNoTruthNeutrons[ith]+=neuosc.OscProbCalculator(numu, false);
  }
}


void NTagAnalysis::GetResolutionwTrueN(CC0PiNumu* numu, float NTrueN) {

  int mode = TMath::Abs(numu->var<int>("mode"));
  float TrueEnu = numu->var<float>("pnu", 0);
  float RecoEnu = numu->var<float>("erec");
  float EnuReso = (TrueEnu - RecoEnu/1000.)/TrueEnu;

  if (NTrueN==0) {
    //CCQE
    if (mode==1) h1_Enureso_CCQE_trueN[0] -> Fill(EnuReso);
    //CC-2p2h
    if (mode>=2 && mode<=10) h1_Enureso_CC2p2h_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta++)
    if (mode==11) h1_Enureso_CCRES_deltapp_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta0)
    if (mode==12) h1_Enureso_CCRES_delta0_trueN[0] -> Fill(EnuReso);
    //CC RES (Delta+)
    if (mode==13) h1_Enureso_CCRES_deltap_trueN[0] -> Fill(EnuReso);
    //CC-other
    //should be included CCRES?
    if (mode>=14 && mode<=30) h1_Enureso_CCOther_trueN[0] -> Fill(EnuReso);
    //NC
    if (mode>=31) h1_Enureso_NC_trueN[0] -> Fill(EnuReso);
  }
  else {
    //CCQE
    if (mode==1) h1_Enureso_CCQE_trueN[1] -> Fill(EnuReso);
    //CC non-QE
    if (mode>=2 && mode<=10) h1_Enureso_CC2p2h_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta++)
    if (mode==11) h1_Enureso_CCRES_deltapp_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta0)
    if (mode==12) h1_Enureso_CCRES_delta0_trueN[1] -> Fill(EnuReso);
    //CC RES (Delta+)
    if (mode==13) h1_Enureso_CCRES_deltap_trueN[1] -> Fill(EnuReso);
    //CC-other
    //should be included CCRES?
    if (mode>=14 && mode<=30) h1_Enureso_CCOther_trueN[1] -> Fill(EnuReso);
    //NC
    if (mode>=31) h1_Enureso_NC_trueN[1] -> Fill(EnuReso);
  }
}


void NTagAnalysis::SummaryTruthInfoinSearch(float WinMin, TString outputname) {
  std::ofstream ofs(outputname);
  if (!ofs) {
    std::cout << "Can not open .txt file: " << outputname << std::endl;
  }
  ofs << "[Truth Info] All Truth Neutrons(Gd+H)      : " << AllTruthNeutrons     << std::endl;
  ofs << "[Truth Info] Truth H-n Neutrons            : " << TruthHNeutrons       << std::endl;
  ofs << "[Truth Info] Truth Gd-n Neutrons           : " << TruthGdNeutrons      << std::endl;

  ofs << "[Truth Info] All Truth CCQE Neutrons(Gd+H) : " << AllTruthCCQENeutrons     << std::endl;
  ofs << "[Truth Info] Truth CCQE H-n Neutrons       : " << TruthCCQEHNeutrons       << std::endl;
  ofs << "[Truth Info] Truth CCQE Gd-n Neutrons      : " << TruthCCQEGdNeutrons      << std::endl;

  //ofs << "[Truth Info] All Truth Neutrons(Gd+H) in FV: " << AllTruthNeutronsinFV << std::endl;
  //ofs << "[Truth Info] Truth H-n Neutrons in FV      : " << TruthHNeutronsinFV   << std::endl;
  //ofs << "[Truth Info] Truth Gd-n Neutrons in FV     : " << TruthGdNeutronsinFV  << std::endl;
  //ofs << " " << std::endl;
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    SetWindowMax(iwin);
    ofs << "===== [" << WinMin << " us, " << varwindowmax << " us] =====" << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << AllTruthNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthHNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthGdNeutronsinSearch[iwin] << std::endl;
    ofs << "[Truth Info] Truth Decay e in [" << WinMin << " us, " << varwindowmax << " us] : " << TruthDecayeinSearch[iwin]   << std::endl;

    //ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << AllTruthNeutronsinSearchFV[iwin] << std::endl;
    //ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthHNeutronsinSearchFV[iwin] << std::endl;
    //ofs << "[Truth Info] Truth Neutrons in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthGdNeutronsinSearchFV[iwin] << std::endl;

    ofs << "[Candidates] Truth Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us]     : " << TruthNeutroninCandidatesinWin[iwin]   << std::endl;
    ofs << "[Candidates] Truth H-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] : " << TruthHNeutroninCandidatesinWin[iwin]  << std::endl;
    ofs << "[Candidates] Truth Gd-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us]: " << TruthGdNeutroninCandidatesinWin[iwin] << std::endl;
    ofs << "[Candidates] Truth Decay e in Candidates in [" << WinMin << " us, " << varwindowmax << " us]      : " << TruthDecayeinCandidatesinWin[iwin]    << std::endl;
    ofs << "[Candidates] Truth Acc. Noise in Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << TruthAccNoiseinCandidatesinWin[iwin]  << std::endl;
    ofs << "[Candidates] All Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << AllCandidatesinWin[iwin] << std::endl;

    //ofs << "[Candidates] Truth Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV     : " << TruthNeutroninCandidatesinWinFV[iwin]   << std::endl;
    //ofs << "[Candidates] Truth H-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV : " << TruthHNeutroninCandidatesinWinFV[iwin]  << std::endl;
    //ofs << "[Candidates] Truth Gd-n Neutrons in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV: " << TruthGdNeutroninCandidatesinWinFV[iwin] << std::endl;
    //ofs << "[Candidates] Truth Decay e in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV      : " << TruthDecayeinCandidatesinWinFV[iwin]    << std::endl;
    //ofs << "[Candidates] Truth Acc. Noise in Candidates in [" << WinMin << " us, " << varwindowmax << " us] in FV   : " << TruthAccNoiseinCandidatesinWinFV[iwin]  << std::endl;
    //ofs << "[Candidates] All Candidates in [" << WinMin << " us, " << varwindowmax << " us]   : " << AllCandidatesinWinFV[iwin] << std::endl;

    GetPreEfficiency(iwin);
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd+H): " << PreEff*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(H)   : " << PreHEff*100 << " %" << std::endl;
    ofs << "[   Pre    ] Pre-selection Efficiency(Gd)  : " << PreGdEff*100 << " %" << std::endl;
    //ofs << "[   Pre    ] Pre-selection Efficiency(Gd+H) in FV: " << PreEffinFV*100 << " %" << std::endl;
    //ofs << "[   Pre    ] Pre-selection Efficiency(H) in FV   : " << PreHEffinFV*100 << " %" << std::endl;
    //ofs << "[   Pre    ] Pre-selection Efficiency(Gd) in FV  : " << PreGdEffinFV*100 << " %" << std::endl;

    for (int ith=0; ith<CUTSTEP; ith++) {
      if (CUTSTEP==11) TMVATH[ith] = 0.1*ith;
      if (CUTSTEP==21) TMVATH[ith] = 0.05*ith;
      ofs << "[    NN    ] ===== Threshold: " << TMVATH[ith] << " =====" << std::endl;
      ofs << "[    NN    ]  ----------- n-like candidates -----------"   << std::endl;
      ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window: " << TaggedTruthNeutronsinWin[iwin][ith]   << std::endl;
      ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window  : " << TaggedTruthHNeutronsinWin[iwin][ith]  << std::endl;
      ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window : " << TaggedTruthGdNeutronsinWin[iwin][ith] << std::endl;
      ofs << "[    NN    ] Mis-tagged Truth Decay-e in Search Window   : " << MisTaggedDecayeinNlike[iwin][ith]     << std::endl;
      ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window      : " << MisTaggedAccNoiseinNlike[iwin][ith]   << std::endl;
      AllNlikeCandidates[iwin][ith] = TaggedTruthNeutronsinWin[iwin][ith] 
                                    + MisTaggedDecayeinNlike[iwin][ith]
                                    + MisTaggedAccNoiseinNlike[iwin][ith];
      ofs << "[    NN    ] All Tagged Neutrons (n-like candidates)     : " << AllNlikeCandidates[iwin][ith] << std::endl;

      //ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window in FV: " << TaggedTruthNeutronsinWinFV[iwin][ith]   << std::endl;
      //ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window in FV  : " << TaggedTruthHNeutronsinWinFV[iwin][ith]  << std::endl;
      //ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window in FV : " << TaggedTruthGdNeutronsinWinFV[iwin][ith] << std::endl;
      //ofs << "[    NN    ] Mis-tagged Truth Decay-e in Search Window in FV   : " << MisTaggedDecayeinNlikeFV[iwin][ith]     << std::endl;
      //ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window in FV      : " << MisTaggedAccNoiseinNlikeFV[iwin][ith]   << std::endl;
      //AllNlikeCandidatesFV[iwin][ith] = TaggedTruthNeutronsinWinFV[iwin][ith] 
      //                                + MisTaggedDecayeinNlikeFV[iwin][ith]
      //                                + MisTaggedAccNoiseinNlikeFV[iwin][ith];
      //ofs << "[    NN    ] All Tagged Neutrons (n-like candidates)     : " << AllNlikeCandidatesFV[iwin][ith] << std::endl;

      NoiseRate[iwin][ith] = GetNoiseRate(MisTaggedDecayeinNlike[iwin][ith], MisTaggedAccNoiseinNlike[iwin][ith], SelectedParentNeutrinos[5],
                                          varwindowmax, WINDOWMIN, NOISECUT);
      ofs << "[    NN    ] Noise Rate: " << NoiseRate[iwin][ith]*100. << " %" << std::endl;
      ofs << "[    NN    ]  ----------- e-like candidates -----------"   << std::endl;
      ofs << "[    NN    ] Tagged Truth Decay-e in Search Window       : " << TaggedTruthDecayeinWin[iwin][ith]          << std::endl;
      ofs << "[    NN    ] Tagged Truth Neutrons(Gd+H) in Search Window: " << MisTaggedTruthNeutronsinElike[iwin][ith]   << std::endl;
      ofs << "[    NN    ] Tagged Truth H-n Neutrons in Search Window  : " << MisTaggedTruthHNeutronsinElike[iwin][ith]  << std::endl;
      ofs << "[    NN    ] Tagged Truth Gd-n Neutrons in Search Window : " << MisTaggedTruthGdNeutronsinElike[iwin][ith] << std::endl;
      ofs << "[    NN    ] Mis-tagged Acc. Noise in Search Window      : " << MisTaggedAccNoiseinElike[iwin][ith]        << std::endl;
      AllElikeCandidates[iwin][ith] = TaggedTruthDecayeinWin[iwin][ith] 
                                    + MisTaggedTruthNeutronsinElike[iwin][ith]
                                    + MisTaggedAccNoiseinElike[iwin][ith];
      ofs << "[    NN    ] All Tagged decay-e (e-like candidates)      : " << AllElikeCandidates[iwin][ith] << std::endl;
      
      GetNNEfficiency(iwin);
      ofs << "[    NN    ] NN Efficiency(Gd+H): " << NNEff[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(H)   : " << NNHEff[ith]*100 << " %" << std::endl;
      ofs << "[    NN    ] NN Efficiency(Gd)  : " << NNGdEff[ith]*100 << " %" << std::endl;
      //ofs << "[    NN    ] NN Efficiency(Gd+H) in FV: " << NNEffinFV[ith]*100 << " %" << std::endl;
      //ofs << "[    NN    ] NN Efficiency(H) in FV   : " << NNHEffinFV[ith]*100 << " %" << std::endl;
      //ofs << "[    NN    ] NN Efficiency(Gd) in FV  : " << NNGdEffinFV[ith]*100 << " %" << std::endl;

      GetOverallEfficiency(iwin);
      ofs << "[  Overall ] Overall Efficiency(Gd+H): " << OverallEff[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(H)   : " << OverallHEff[ith]*100 << " %" << std::endl;
      ofs << "[  Overall ] Overall Efficiency(Gd)  : " << OverallGdEff[ith]*100 << " %" << std::endl;
      //ofs << "[  Overall ] Overall Efficiency(Gd+H) in FV: " << OverallEffinFV[ith]*100 << " %" << std::endl;
      //ofs << "[  Overall ] Overall Efficiency(H) in FV   : " << OverallHEffinFV[ith]*100 << " %" << std::endl;
      //ofs << "[  Overall ] Overall Efficiency(Gd) in FV  : " << OverallGdEffinFV[ith]*100 << " %" << std::endl;
      GetPurity(iwin);
      ofs << "[  Purity  ] Purity: " << Purity[ith]*100 << std::endl;
    }
    ofs << " " << std::endl;
  }
  ofs << " " << std::endl;
  for (int ith=0; ith<CUTSTEP; ith++) {
    ofs << "[    NN    ] ===== Threshold: " << TMVATH[ith] << " =====" << std::endl;
    ofs << "[    NN    ] ===== 1R muon Samples with NTag Info ====="   << std::endl;
    ofs << "[    NN    ] Neutrino Events with No Tagged Neutrons: " << NeutrinoEventswNoNlike[ith]         << std::endl;
    ofs << "[    NN    ] Neutrino Events with Tagged Neutrons   : " << NeutrinoEventswNlikes[ith]          << std::endl;
    ofs << "[    NN    ] Neutrino Events with Only One Nlike    : " << NeutrinoEventswOneNlike[ith]        << std::endl;
    ofs << "[    NN    ] Neutrino Events with One Nlike Decay-e : " << NeutrinoEventswOneNlikeDecaye[ith]  << std::endl;
    ofs << "[    NN    ] Neutrino Events with No Truth Neutrons : " << NeutrinoEventswNoTruthNeutrons[ith] << std::endl;
  }
}

void NTagAnalysis::SetNoiseRateGraph() {

  for (int i=0; i<WINSTEP; i++) {
    g_NoiseRate[i] = new TGraphErrors(CUTSTEP, TMVATH, NoiseRate[i], eTMVATH, eNoiseRate[i]);
    g_NoiseRate[i] -> SetMarkerSize(1.0);
    g_NoiseRate[i] -> SetMarkerStyle(20);

    switch (i) {
      case 0:
        g_NoiseRate[i] -> SetMarkerColor(kViolet-7);
        g_NoiseRate[i] -> SetLineColor(kViolet-7);
        break;
      case 1:
        g_NoiseRate[i] -> SetMarkerColor(kAzure+1);
        g_NoiseRate[i] -> SetLineColor(kAzure+1);
        break;
      case 2:
        g_NoiseRate[i] -> SetMarkerColor(kTeal+5);
        g_NoiseRate[i] -> SetLineColor(kTeal+5);
        break;
      case 3:
        g_NoiseRate[i] -> SetMarkerColor(kYellow-3);
        g_NoiseRate[i] -> SetLineColor(kYellow-3);
        break;
      case 4:
        g_NoiseRate[i] -> SetMarkerColor(kOrange+7);
        g_NoiseRate[i] -> SetLineColor(kOrange+7);
        break;
      case 5:
        g_NoiseRate[i] -> SetMarkerColor(kRed-3);
        g_NoiseRate[i] -> SetLineColor(kRed-3);
        break;
      case 6:
        g_NoiseRate[i] -> SetMarkerColor(kPink-8);
        g_NoiseRate[i] -> SetLineColor(kPink-8);
        break;
    }
  }
}

//Estimate efficiencies as a funxtion of time window and n-llikelihood
void NTagAnalysis::GetEfficiencyforWinOpt() {
  //Threshold that noise rate becomes ~2%
  //note that this loop inverts the order of time window!(starts from 200 us, but not 535 us)
  int inthr[WINSTEP];       //inthr = threshold / 0.05  !!! should be set by hand !!!
  int inwin[WINSTEP];       //index of window step that correponds to above calculation
  //float WindowMax[WINSTEP]; //Step of time window scan
  for (int iwin=0; iwin<WINSTEP; iwin++) {
    switch (iwin) {
      case 0: //200us
        //inthr[iwin] = 10;
        inthr[iwin] = 8;
        inwin[iwin] = 5;
        WindowMax[iwin] = 200;
        break;
      case 1: //250us
        //inthr[iwin] = 11;
        inthr[iwin] = 9;
        inwin[iwin] = 4;
        WindowMax[iwin] = 250;
        break;
      case 2: //300us
        //inthr[iwin] = 12;
        inthr[iwin] = 9;
        inwin[iwin] = 3;
        WindowMax[iwin] = 300;
        break;
      case 3: //350us
        //inthr[iwin] = 13;
        inthr[iwin] = 10;
        inwin[iwin] = 2;
        WindowMax[iwin] = 350;
        break;
      case 4: //400us
        //inthr[iwin] = 13;
        inthr[iwin] = 11;
        inwin[iwin] = 1;
        WindowMax[iwin] = 400;
        break;
      case 5: //535us
        //inthr[iwin] = 14;
        inthr[iwin] = 11;
        inwin[iwin] = 0;
        WindowMax[iwin] = 535;
        break;
    }

    NNEffinWin[iwin]   = (float)TaggedTruthNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthNeutroninCandidatesinWin[inwin[iwin]];
    NNHEffinWin[iwin]  = (float)TaggedTruthHNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthHNeutroninCandidatesinWin[inwin[iwin]];
    NNGdEffinWin[iwin] = (float)TaggedTruthGdNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthGdNeutroninCandidatesinWin[inwin[iwin]];

    OverallEffinWin[iwin]   = (float)TaggedTruthNeutronsinWin[inwin[iwin]][inthr[iwin]] / AllTruthNeutronsinFV;
    OverallHEffinWin[iwin]  = (float)TaggedTruthHNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthHNeutronsinFV;
    OverallGdEffinWin[iwin] = (float)TaggedTruthGdNeutronsinWin[inwin[iwin]][inthr[iwin]] / TruthGdNeutronsinFV;
  }
}

void NTagAnalysis::GetPreEfficiency(int windowstep) {
  //Pre-selection (count truth neutrons from 3 usec up to windowstep maximum)
  //PreEff       = (float)TruthNeutroninCandidatesinWin[windowstep] / AllTruthNeutronsinSearch[windowstep];
  //PreHEff      = (float)TruthHNeutroninCandidatesinWin[windowstep] / TruthHNeutronsinSearch[windowstep];
  //PreGdEff     = (float)TruthGdNeutroninCandidatesinWin[windowstep] / TruthGdNeutronsinSearch[windowstep];
  PreEff       = (float)TruthNeutroninCandidatesinWin[windowstep] / AllTruthNeutrons;
  PreHEff      = (float)TruthHNeutroninCandidatesinWin[windowstep] / TruthHNeutrons;
  PreGdEff     = (float)TruthGdNeutroninCandidatesinWin[windowstep] / TruthGdNeutrons;

  //PreEffinFV   = (float)TruthNeutroninCandidatesinWinFV[windowstep] / AllTruthNeutronsinSearchFV[windowstep];
  //PreHEffinFV  = (float)TruthHNeutroninCandidatesinWinFV[windowstep] / TruthHNeutronsinSearchFV[windowstep];
  //PreGdEffinFV = (float)TruthGdNeutroninCandidatesinWinFV[windowstep] / TruthGdNeutronsinSearchFV[windowstep];
}

void NTagAnalysis::GetNNEfficiency(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    NNEff[ith]       = (float)TaggedTruthNeutronsinWin[windowstep][ith] / TruthNeutroninCandidatesinWin[windowstep];
    NNHEff[ith]      = (float)TaggedTruthHNeutronsinWin[windowstep][ith] / TruthHNeutroninCandidatesinWin[windowstep];
    NNGdEff[ith]     = (float)TaggedTruthGdNeutronsinWin[windowstep][ith] / TruthGdNeutroninCandidatesinWin[windowstep];

    //NNEffinFV[ith]   = (float)TaggedTruthNeutronsinWinFV[windowstep][ith] / TruthNeutroninCandidatesinWinFV[windowstep];
    //NNHEffinFV[ith]  = (float)TaggedTruthHNeutronsinWinFV[windowstep][ith] / TruthHNeutroninCandidatesinWinFV[windowstep];
    //NNGdEffinFV[ith] = (float)TaggedTruthGdNeutronsinWinFV[windowstep][ith] / TruthGdNeutroninCandidatesinWinFV[windowstep];
  }
}

void NTagAnalysis::GetOverallEfficiency(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    //OverallEff[ith]       = (float)TaggedTruthNeutronsinWin[windowstep][ith] / AllTruthNeutronsinSearch[windowstep];
    //OverallHEff[ith]      = (float)TaggedTruthHNeutronsinWin[windowstep][ith] / TruthHNeutronsinSearch[windowstep];
    //OverallGdEff[ith]     = (float)TaggedTruthGdNeutronsinWin[windowstep][ith] / TruthGdNeutronsinSearch[windowstep];
    OverallEff[ith]       = (float)TaggedTruthNeutronsinWin[windowstep][ith] / AllTruthNeutrons;
    OverallHEff[ith]      = (float)TaggedTruthHNeutronsinWin[windowstep][ith] / TruthHNeutrons;
    OverallGdEff[ith]     = (float)TaggedTruthGdNeutronsinWin[windowstep][ith] / TruthGdNeutrons;

    //OverallEffinFV[ith]   = (float)TaggedTruthNeutronsinWinFV[windowstep][ith] / AllTruthNeutronsinSearchFV[windowstep];
    //OverallHEffinFV[ith]  = (float)TaggedTruthHNeutronsinWinFV[windowstep][ith] / TruthHNeutronsinSearchFV[windowstep];
    //OverallGdEffinFV[ith] = (float)TaggedTruthGdNeutronsinWinFV[windowstep][ith] / TruthGdNeutronsinSearchFV[windowstep];
  }
}

void NTagAnalysis::GetPurity(int windowstep) {
  for (int ith=0; ith<CUTSTEP; ith++) {
    Purity[ith] = (float)TaggedTruthNeutronsinWin[windowstep][ith] / AllNlikeCandidates[windowstep][ith];
  }
}


void NTagAnalysis::SetEfficiencyGraph(int windowstep) {
  g_NNEffwin        = new TGraphErrors(WINSTEP, WindowMax, NNEffinWin, eWindowMax, eNNEffinWin);
  g_NNHEffwin       = new TGraphErrors(WINSTEP, WindowMax, NNHEffinWin, eWindowMax, eNNHEffinWin);
  g_NNGdEffwin      = new TGraphErrors(WINSTEP, WindowMax, NNGdEffinWin, eWindowMax, eNNGdEffinWin);
  g_OverallEffwin   = new TGraphErrors(WINSTEP, WindowMax, OverallEffinWin, eWindowMax, eOverallEffinWin);
  g_OverallHEffwin  = new TGraphErrors(WINSTEP, WindowMax, OverallHEffinWin, eWindowMax, eOverallHEffinWin);
  g_OverallGdEffwin = new TGraphErrors(WINSTEP, WindowMax, OverallGdEffinWin, eWindowMax, eOverallGdEffinWin);
  g_NNEffwin   -> SetMarkerColor(kPink-5);
  g_NNEffwin   -> SetLineColor(kPink-5);
  g_NNEffwin   -> SetMarkerStyle(20);
  g_NNEffwin   -> SetMarkerSize(1.0);
  g_NNHEffwin  -> SetMarkerColor(kAzure-4);
  g_NNHEffwin  -> SetLineColor(kAzure-4);
  g_NNHEffwin  -> SetMarkerStyle(20);
  g_NNHEffwin  -> SetMarkerSize(1.0);
  g_NNGdEffwin -> SetMarkerColor(kTeal-5);
  g_NNGdEffwin -> SetLineColor(kTeal-5);
  g_NNGdEffwin -> SetMarkerStyle(20);
  g_NNGdEffwin -> SetMarkerSize(1.0);
  g_OverallEffwin   -> SetMarkerColor(kPink-5);
  g_OverallEffwin   -> SetLineColor(kPink-5);
  g_OverallEffwin   -> SetMarkerStyle(20);
  g_OverallEffwin   -> SetMarkerSize(1.0);
  g_OverallHEffwin  -> SetMarkerColor(kAzure-4);
  g_OverallHEffwin  -> SetLineColor(kAzure-4);
  g_OverallHEffwin  -> SetMarkerStyle(20);
  g_OverallHEffwin  -> SetMarkerSize(1.0);
  g_OverallGdEffwin -> SetMarkerColor(kTeal-5);
  g_OverallGdEffwin -> SetLineColor(kTeal-5);
  g_OverallGdEffwin -> SetMarkerStyle(20);
  g_OverallGdEffwin -> SetMarkerSize(1.0);

  //windowstep=0 for [3 us, 535 us]
  GetPreEfficiency(windowstep);
  GetNNEfficiency(windowstep);
  GetOverallEfficiency(windowstep);
  GetPurity(windowstep);
  g_NNEff        = new TGraphErrors(CUTSTEP, TMVATH, NNEff, eTMVATH, eNNEff);
  g_NNHEff       = new TGraphErrors(CUTSTEP, TMVATH, NNHEff, eTMVATH, eNNHEff);
  g_NNGdEff      = new TGraphErrors(CUTSTEP, TMVATH, NNGdEff, eTMVATH, eNNGdEff);
  g_OverallEff   = new TGraphErrors(CUTSTEP, TMVATH, OverallEff, eTMVATH, eOverallEff);
  g_OverallHEff  = new TGraphErrors(CUTSTEP, TMVATH, OverallHEff, eTMVATH, eOverallHEff);
  g_OverallGdEff = new TGraphErrors(CUTSTEP, TMVATH, OverallGdEff, eTMVATH, eOverallGdEff);
  g_NNEff   -> SetMarkerColor(kPink-5);
  g_NNEff   -> SetLineColor(kPink-5);
  g_NNEff   -> SetMarkerStyle(20);
  g_NNEff   -> SetMarkerSize(1.0);
  g_NNHEff  -> SetMarkerColor(kAzure-4);
  g_NNHEff  -> SetLineColor(kAzure-4);
  g_NNHEff  -> SetMarkerStyle(20);
  g_NNHEff  -> SetMarkerSize(1.0);
  g_NNGdEff -> SetMarkerColor(kTeal-5);
  g_NNGdEff -> SetLineColor(kTeal-5);
  g_NNGdEff -> SetMarkerStyle(20);
  g_NNGdEff -> SetMarkerSize(1.0);
  g_OverallEff   -> SetMarkerColor(kPink-5);
  g_OverallEff   -> SetLineColor(kPink-5);
  g_OverallEff   -> SetMarkerStyle(20);
  g_OverallEff   -> SetMarkerSize(1.0);
  g_OverallHEff  -> SetMarkerColor(kAzure-4);
  g_OverallHEff  -> SetLineColor(kAzure-4);
  g_OverallHEff  -> SetMarkerStyle(20);
  g_OverallHEff  -> SetMarkerSize(1.0);
  g_OverallGdEff -> SetMarkerColor(kTeal-5);
  g_OverallGdEff -> SetLineColor(kTeal-5);
  g_OverallGdEff -> SetMarkerStyle(20);
  g_OverallGdEff -> SetMarkerSize(1.0);

  
  //make 20-point(not 21-point) purity curve
  for (int i=0; i<CUTSTEP-1; i++) {
    FillPurity[i]  = Purity[i];
    FillTMVATH[i]  = TMVATH[i];
    FilleTMVATH[i] = eTMVATH[i];
  }
  g_Purity = new TGraphErrors(CUTSTEP-1, FillTMVATH, FillPurity, FilleTMVATH, FillePurity);
  g_Purity -> SetMarkerColor(kPink-5);
  g_Purity -> SetLineColor(kPink-5);
  g_Purity -> SetMarkerStyle(20);
  g_Purity -> SetMarkerSize(1.0);

  //make 20-point(not 21-point) noise rate curve
  for (int i=0; i<CUTSTEP-1; i++) {
    FillNoiseRate[i] = NoiseRate[windowstep][i+1];
    FillTMVATH[i]  = TMVATH[i+1];
    FilleTMVATH[i] = eTMVATH[i+1];
  }
  g_FillNoiseRate = new TGraphErrors(CUTSTEP-1, FillTMVATH, FillNoiseRate, FilleTMVATH, FilleNoiseRate);
  g_FillNoiseRate -> SetMarkerColor(kGray+3);
  g_FillNoiseRate -> SetLineColor(kGray+3);
  g_FillNoiseRate -> SetMarkerStyle(20);
  g_FillNoiseRate -> SetMarkerSize(1.0);

  float ROC_Purity[CUTSTEP-2];
  float ROC_NoiseRate[CUTSTEP-2];
  int ipoint = 0;
  for (int i=0; i<CUTSTEP; i++) {
    if (i==0 || i==20) continue; // skip: noise rate@thr=0 is >>100%, and purity@thr=1 is -nan
    else {
      std::cout << "[### i=" << i << ", Thr=" << TMVATH[i] << " ###] Purity: " << Purity[i]*100. << "%, Noise rate: " << NoiseRate[windowstep][i]*100. << "%" << std::endl;
      ROC_Purity[ipoint] = Purity[i];
      ROC_NoiseRate[ipoint] = NoiseRate[windowstep][i];
      ipoint++;
    }
  }

  g_ROC = new TGraph(CUTSTEP-2, ROC_NoiseRate, ROC_Purity);
  g_ROC -> SetMarkerColor(kAzure+5);
  g_ROC -> SetLineColor(kAzure+5);
  g_ROC -> SetMarkerStyle(20);
  g_ROC -> SetMarkerSize(1.0);
}


float NTagAnalysis::GetTaggedNeutrons(std::vector<float> *TagOut,
                                      float Threshold,
                                      std::vector<float> *TagIndex,
                                      std::vector<float> *NHits,
                                      std::vector<float> *FitT,
                                      std::vector<float> *Label,
                                      bool etagmode) 
{
  //Count the number of tagged neutrons
  int NumTaggedNeutrons       = 0;  //Number of n-like candidates of this event
  int NumTruthNeutronsinNlike = 0;  //Number of truth neutrons in n-like candidates of this event
  int NumTruthDecayeinNlike   = 0;  //Number of truth decay-e in n-like candidates of this event

  for (UInt_t ican=0; ican<TagOut->size(); ++ican) {

    //Check whether this candidate is n-like or e-like(for e-tagging ON)
    bool etagboxin = false;
    if (etagmode){
      if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

      if (TagOut->at(ican)>Threshold && etagboxin==false) NumTaggedNeutrons++;
      if (TagOut->at(ican)>Threshold && etagboxin==false && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;
      if (TagOut->at(ican)>Threshold && etagboxin==false && Label->at(ican)==1) NumTruthDecayeinNlike++;
    }
    else {
      if (TagOut->at(ican)>Threshold) NumTaggedNeutrons++;
      if (TagOut->at(ican)>Threshold && (Label->at(ican)==2 || Label->at(ican)==3)) NumTruthNeutronsinNlike++;        
      if (TagOut->at(ican)>Threshold && Label->at(ican)==1) NumTruthDecayeinNlike++;
    }       
  }
  return NumTaggedNeutrons;  
}

float NTagAnalysis::GetTaggedNoise(std::vector<float> *TagOut,
                                   float Threshold,
                                   std::vector<float> *TagIndex,
                                   std::vector<float> *NHits,
                                   std::vector<float> *FitT,
                                   std::vector<float> *Label,
                                   bool etagmode) 
{
  int NumTaggedNoise = 0;
  for (UInt_t ican=0; ican<TagOut->size(); ++ican) {
    //Check whether this candidate is n-like or e-like(for e-tagging ON)
    bool etagboxin = false;
    if (etagmode){
      if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
      if (TagOut->at(ican)>Threshold && etagboxin==false && (Label->at(ican)==0 || Label->at(ican)==1)) NumTaggedNoise++;
    }
    else {
      if (TagOut->at(ican)>Threshold && (Label->at(ican)==0 || Label->at(ican)==1)) NumTaggedNoise++;
    }       
  }
  return NumTaggedNoise;
}

bool NTagAnalysis::GetTrueMuNCapVtx(int iscnd, CC0PiNumu* numu, Int_t *ichildidx, float *MuNCapVtx) {
  bool MuNCap = false;

  if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::NEUTRON) &&
      numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY)) 
  {
    if (std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) && 
        numu->var<int>("lmecscnd", ichildidx[iscnd]-1)==static_cast<int>(GEANTINT::NEUTRONCAPTURE))
    {
      MuNCap = true;
      MuNCapVtx[0] = numu->var<float>("vtxscnd", ichildidx[iscnd]-1, 0);
      MuNCapVtx[1] = numu->var<float>("vtxscnd", ichildidx[iscnd]-1, 1);
      MuNCapVtx[2] = numu->var<float>("vtxscnd", ichildidx[iscnd]-1, 2);
      //std::cout << "  MuNCapVtx=[" << MuNCapVtx[0] << ", " << MuNCapVtx[1] << ", " << MuNCapVtx[2] << "]" << std::endl;
    }
  } 
  return MuNCap;
}

int NTagAnalysis::LabelTrueMuN(CC0PiNumu* numu, bool PrmMuEnd, Int_t *ichildidx) {
  int TrueMuN = 0;
  float MuNCapVtx[3] = {0., 0., 0.};  //neutron(from mu capture) capture vertex
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    bool PrmMuCap = this->GetTrueMuNCapVtx(iscnd, numu, ichildidx, MuNCapVtx);
    if (PrmMuEnd && PrmMuCap) TrueMuN++;
  }
  return TrueMuN;
}

bool NTagAnalysis::GetTrueNuNCapVtx(int iscnd, CC0PiNumu* numu, Int_t *iprntidx, Float_t vtxprnt[][3], std::vector<float> *VtxPrntList, std::vector<float> *VtxScndList, float *NuNCapVtx) 
{
  bool NuNCap = false;

  if (numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::GAMMA) && 
      numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::NEUTRON) &&
      std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::MUON) &&
      numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::NEUTRONCAPTURE)) 
  {

    //Find gamma from different neutrons
    float d_vtxprnt = std::sqrt( vtxprnt[iscnd][0]*vtxprnt[iscnd][0] +
                                 vtxprnt[iscnd][1]*vtxprnt[iscnd][1] +
                                 vtxprnt[iscnd][2]*vtxprnt[iscnd][2] );
    float vtxscndX  = numu->var<float>("vtxscnd", iscnd, 0);
    float vtxscndY  = numu->var<float>("vtxscnd", iscnd, 1);
    float vtxscndZ  = numu->var<float>("vtxscnd", iscnd, 2);
    float d_vtxscnd = std::sqrt( vtxscndX*vtxscndX +
                                 vtxscndY*vtxscndY +
                                 vtxscndZ*vtxscndZ );
    //First gamma
    if (VtxScndList->size()==0) {
      NuNCap = true;
      VtxPrntList->push_back(d_vtxprnt);
      VtxScndList->push_back(d_vtxscnd);
      NuNCapVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
      NuNCapVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
      NuNCapVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
      //std::cout << "  NuNCapVtx=[" << NuNCapVtx[0] << ", " << NuNCapVtx[1] << ", " << NuNCapVtx[2] << "]" << std::endl;
    }
    else {
      bool NewNeutron = false;
      for (UInt_t in=0; in<VtxPrntList->size(); in++) {
        if (VtxPrntList->at(in)!=d_vtxprnt) NewNeutron = true;
        else {
          for (UInt_t jn=0; jn<VtxScndList->size(); jn++) {
            if (VtxScndList->at(jn)!=d_vtxscnd) NewNeutron = true;
            else NewNeutron = false;
          }
        }
      }

      if (NewNeutron) {
        NuNCap = true;
        VtxScndList->push_back(d_vtxscnd);
        VtxPrntList->push_back(d_vtxprnt);
        NuNCapVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
        NuNCapVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
        NuNCapVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
        //std::cout << "  NuNCapVtx=[" << NuNCapVtx[0] << ", " << NuNCapVtx[1] << ", " << NuNCapVtx[2] << "]" << std::endl;
      }
    }

  }
  return NuNCap;
}

int NTagAnalysis::LabelTrueNuN(CC0PiNumu* numu, bool PrmMuEnd, Int_t *iprntidx, Float_t vtxprnt[][3], std::vector<float> *VtxPrntList, std::vector<float> *VtxScndList) 
{
  int TrueNuN = 0;
  float NuNCapVtx[3] = {0., 0., 0.};  //neutron(from primary interaction) capture vertex
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    bool NuNCap = this->GetTrueNuNCapVtx(iscnd, numu, iprntidx, vtxprnt, VtxPrntList, VtxScndList, NuNCapVtx);
    if (PrmMuEnd && NuNCap) TrueNuN++;
  }
  return TrueNuN;
}

bool NTagAnalysis::GetRecoNeutronCapVtx(UInt_t ican, 
                                        float Threshold, 
                                        std::vector<float> *NHits,
                                        std::vector<float> *FitT, 
                                        std::vector<float> *TagOut,
                                        std::vector<float> *dvx, 
                                        std::vector<float> *dvy, 
                                        std::vector<float> *dvz, 
                                        float *NCapVtx,
                                        bool etagmode) 
{
  bool NCap = false;

  bool etagboxin = false;
  if (etagmode){
    if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;

    if (TagOut->at(ican)>Threshold && etagboxin==false) {
      NCap = true;
      NCapVtx[0] = dvx->at(ican);
      NCapVtx[1] = dvy->at(ican);
      NCapVtx[2] = dvz->at(ican);
      //std::cout << "[### " << ican <<" ###]  NCapVtx=[" << NCapVtx[0] << ", " << NCapVtx[1] << ", " << NCapVtx[2] << "]" << std::endl;
    }
  }
  else {
    if (TagOut->at(ican)>Threshold) {
      NCap = true;
      NCapVtx[0] = dvx->at(ican);
      NCapVtx[1] = dvy->at(ican);
      NCapVtx[2] = dvz->at(ican);
      //std::cout << "[### " << ican <<" ###]  NCapVtx=[" << NCapVtx[0] << ", " << NCapVtx[1] << ", " << NCapVtx[2] << "]" << std::endl;
    }
  }
  return NCap;
}



int NTagAnalysis::NCapVtxResEstimator(CC0PiNumu* numu, int NTrueN, Float_t *tscnd, Float_t vtxprnt[][3], 
                                      bool etagmode, std::vector<float> *FitT, std::vector<float> *NHits, std::vector<float> *Label, std::vector<float> *TagOut, 
                                      float TMVAThreshold, std::vector<float> *dvx, std::vector<float> *dvy, std::vector<float> *dvz) 
{

  //check the existence of true capture neutrons in a neutrino event
  if (NTrueN==0) return 0;

  //Make truth neutron list
  int TrueNCap = 0;
  std::vector<float> tscndlist;
  std::vector<float> vtxscndXlist;
  std::vector<float> vtxscndYlist;
  std::vector<float> vtxscndZlist;
  for (int jsub=0; jsub<numu->var<int>("nscndprt"); jsub++) {
    //std::cout << "Particle[" << jsub << "] = " << numu->var<int>("iprtscnd", jsub)
    //          << ", Parent = " << numu->var<int>("iprntprt", jsub) 
    //          << ", lmecscnd = " << numu->var<int>("lmecscnd", jsub) 
    //          << ", [" << numu->var<float>("vtxscnd", jsub, 0) << ", "
    //                   << numu->var<float>("vtxscnd", jsub, 1) << ", "
    //                   << numu->var<float>("vtxscnd", jsub, 2) << "], tscnd = " << tscnd[jsub]/1000. << " us" << std::endl;

    //Find gamma from neutron capture (do not remove muon capture neutrons)
    if ( std::fabs(numu->var<int>("iprtscnd", jsub))==static_cast<int>(PDGPID::GAMMA) &&
         numu->var<int>("iprntprt", jsub)==static_cast<int>(PDGPID::NEUTRON) &&
         numu->var<int>("lmecscnd", jsub)==static_cast<int>(GEANTINT::NEUTRONCAPTURE) )
    {
      //tscndlist.push_back( tscnd[iscnd]/1000. );
      float vtxscndX  = numu->var<float>("vtxscnd", jsub, 0);
      float vtxscndY  = numu->var<float>("vtxscnd", jsub, 1);
      float vtxscndZ  = numu->var<float>("vtxscnd", jsub, 2);

      //First gamma
      if (vtxscndXlist.size()==0) {
        vtxscndXlist.push_back(vtxscndX);
        vtxscndYlist.push_back(vtxscndY);
        vtxscndZlist.push_back(vtxscndZ);
        tscndlist.push_back(tscnd[jsub]/1000.);
        TrueNCap++;
        //h1_mintimediff_NCap -> Fill(tscnd[jsub]/1000.);
        //h1_TrueNCapTime -> Fill(tscnd[jsub]/1000.);
      }
      else {
        bool NewNeutron = false;
        for (UInt_t jn=0; jn<vtxscndXlist.size(); jn++) {
          if (std::fabs(tscndlist.at(jn)-tscnd[jsub]/1000.) > 1.e-4 && 
              (vtxscndXlist.at(jn)!=vtxscndX || vtxscndYlist.at(jn)!=vtxscndY || vtxscndZlist.at(jn)!=vtxscndZ)) 
          {
            NewNeutron = true;
          }
          else NewNeutron = false;
          //std::cout << "  Time difference: " << std::fabs(tscndlist.at(jn)-tscnd[jsub]/1000.) << ", NewNeutron: " << NewNeutron <<  std::endl;
        }

        if (NewNeutron) {
          vtxscndXlist.push_back(vtxscndX);
          vtxscndYlist.push_back(vtxscndY);
          vtxscndZlist.push_back(vtxscndZ);
          tscndlist.push_back(tscnd[jsub]/1000.);
          TrueNCap++;
          //h1_TrueNCapTime -> Fill(tscnd[jsub]/1000.);
        }
      }

    }
  }
  //if (NTrueN!=TrueNCap) std::cout << "NTrueN != TrueNCap" << std::endl;
  //std::cout << "NTrueN: " << NTrueN << ", TrueNCap: " << TrueNCap << ", tscndlist: " << tscndlist.size() << std::endl;
  //std::cout << " " << std::endl;


  //check the exostence of reco capture neutrons in a neutrino event
  if (TagOut->size()==0) return 0;

  //Make reco neutron list
  int RecoNCap = 0;
  std::vector<float> FitTlist;
  std::vector<float> dvxlist;
  std::vector<float> dvylist;
  std::vector<float> dvzlist;
  for (UInt_t ican=0; ican<TagOut->size(); ican++) {
    bool etagboxin = false;
    if (etagmode){
      //if (Label->at(ican)==0) h1_N50[0] -> Fill(NHits->at(ican));
      //if (Label->at(ican)==1) h1_N50[1] -> Fill(NHits->at(ican));
      //if (Label->at(ican)==2) h1_N50[2] -> Fill(NHits->at(ican));
      //if (Label->at(ican)==3) h1_N50[3] -> Fill(NHits->at(ican));

      if (NHits->at(ican)>50 && FitT->at(ican)<20) etagboxin = true;
      if (TagOut->at(ican)>TMVAThreshold && etagboxin==false) {
        RecoNCap++;
        //std::cout << "FitT: " << FitT->at(ican) << std::endl;
        FitTlist.push_back(FitT->at(ican));
        dvxlist.push_back(dvx->at(ican));
        dvylist.push_back(dvy->at(ican));
        dvzlist.push_back(dvz->at(ican));
        if (Label->at(ican)==0) h1_RecoNCapTime[0] -> Fill(FitT->at(ican));  //noise
        if (Label->at(ican)==1) h1_RecoNCapTime[1] -> Fill(FitT->at(ican));  //decay-e
        if (Label->at(ican)==2) h1_RecoNCapTime[2] -> Fill(FitT->at(ican));  //H-n
        if (Label->at(ican)==3) h1_RecoNCapTime[3] -> Fill(FitT->at(ican));  //Gd-n

        //if (Label->at(ican)==0) h1_N50[0] -> Fill(NHits->at(ican));
        //if (Label->at(ican)==1) h1_N50[1] -> Fill(NHits->at(ican));
        //if (Label->at(ican)==2) h1_N50[2] -> Fill(NHits->at(ican));
        //if (Label->at(ican)==3) h1_N50[3] -> Fill(NHits->at(ican));
      }
    }
    else {
      if (TagOut->at(ican)>TMVAThreshold) {
        RecoNCap++;
        FitTlist.push_back(FitT->at(ican));
        dvxlist.push_back(dvx->at(ican));
        dvylist.push_back(dvy->at(ican));
        dvzlist.push_back(dvz->at(ican));
      }
    }
  }

  ///*
  std::vector<int> fin_itr_true; //final minimum pair true
  std::vector<int> fin_itr_reco; //final minimum pair reco

  int truecounter = TrueNCap;
  int recocounter = RecoNCap;
  bool loopfinisher = false;
  while (loopfinisher==false) {

    ///////////////////////////////////
    //1. Find pre-minimum pair
    //  1 truth -> all reco
    ///////////////////////////////////
    //int tmp_itr_true = 999; //pre-minimum true
    int tmp_itr_reco = 999; //pre-minimum reco
    //Truth loop
    float pre_min = 9999999.; //time difference of the minimum reco particle for the itrue-th particle
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {

      //Check 
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      float this_tscnd = tscndlist.at(itrue);

      //Reco loop
      for (long unsigned int ireco=0; ireco<FitTlist.size(); ireco++) {

        //Check
        bool done_this_reco = false;
        for (long unsigned int imin=0; imin<fin_itr_reco.size(); imin++) {
          if (ireco == (long unsigned int)fin_itr_reco.at(imin)) done_this_reco = true;
        }
        if (done_this_reco==true) continue;

        float this_FitT = FitTlist.at(ireco);

        float timediff = std::fabs( this_FitT - this_tscnd );

        //update (pre-minimum pair)
        if (pre_min > timediff) {
          pre_min = timediff;
          //tmp_itr_true = itrue;
          tmp_itr_reco = ireco;
        }
      }

    }
    //std::cout << "[Pre-minimum] true:reco = " << tmp_itr_true+1 << " : " << tmp_itr_reco+1 << std::endl;
    //std::cout << "              Pre-minimum time diff. = " << pre_min << " us" << std::endl;


    ///////////////////////////////////
    //2. Conclude minimum pair
    //  pre-minimum reco -> all truth
    ///////////////////////////////////
    int tmp2_itr_true = 999; //tentative final-minimum truth
    //Truth loop
    float fin_min       = 9999999.;
    //float min_dt        = 0.;
    //float min_N50       = 0.;
    float resolution    = 0.;
    float vtxresolution = 0.;
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {

      //Check
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      float this_tscnd    = tscndlist.at(itrue);
      float this_vtxscndX = vtxscndXlist.at(itrue);
      float this_vtxscndY = vtxscndYlist.at(itrue);
      float this_vtxscndZ = vtxscndZlist.at(itrue);
      //std::cout << "  vtxscnd=[" << this_vtxscndX << ", " << this_vtxscndY << ", " << this_vtxscndZ << "]" << std::endl;

      //extract pre-minimum
      float this_dt  = 999.;
      float this_dvx = 0.;
      float this_dvy = 0.;
      float this_dvz = 0.;
      for (long unsigned int ireco=0; ireco<FitTlist.size(); ireco++) {
        if (ireco == (long unsigned int)tmp_itr_reco) {
          //std::cout << "   [reco# " << ireco+1 << "]";
          this_dt  = FitTlist.at(ireco);
          this_dvx = dvxlist.at(ireco);
          this_dvy = dvylist.at(ireco);
          this_dvz = dvzlist.at(ireco);
        }
      }

      float tmp_reso     = this_dt - this_tscnd;
      float tmp_vtxresoX = this_vtxscndX - this_dvx;
      float tmp_vtxresoY = this_vtxscndY - this_dvy;
      float tmp_vtxresoZ = this_vtxscndZ - this_dvz;
      float tmp_vtxreso  = std::sqrt( tmp_vtxresoX*tmp_vtxresoX +
                                      tmp_vtxresoY*tmp_vtxresoY +
                                      tmp_vtxresoZ*tmp_vtxresoZ );

      //Final update (minimal time difference pair)
      float timediff = std::fabs( this_dt - this_tscnd );
      if (fin_min > timediff) {
        fin_min       = timediff;
        tmp2_itr_true = itrue;
        resolution    = tmp_reso;
        vtxresolution = tmp_vtxreso;
      }
    }

    //Conclude the final minimum pair
    fin_itr_true.push_back(tmp2_itr_true);
    fin_itr_reco.push_back(tmp_itr_reco);
    //std::cout << "[Final-minimum] true:reco = " << tmp2_itr_true+1 << " : " << tmp_itr_reco+1 << std::endl;
    //std::cout << "                Final-minimum time diff. = " << fin_min << " us" << std::endl;
    //if (fillthem==true) {
    //if (resolution!=0) {
      h1_mintimediff_NCap -> Fill(resolution);
      h1_NCapVtxReso      -> Fill(vtxresolution);
    //}

    //Decrement the number of truth particles at last
    truecounter -= 1;
    recocounter -= 1;

    loopfinisher = (truecounter==0 || recocounter==0);
    //std::cout << "-----------------" << std::endl;

  }//*/

  return 0;
}

void NTagAnalysis::GetTrueNCapTime(std::vector<float> *t, std::vector<int> *Type) {
  for (UInt_t itaggable=0; itaggable<t->size(); itaggable++) {
    if (Type->at(itaggable)==2) h1_TrueNCapTime -> Fill(t->at(itaggable));
  }
}

void NTagAnalysis::N1Rmu_x_kinematics(CC0PiNumu* numu, float knmtcs, double* xbins, int* N1Rmu_x_knmtcs, TH1F** h1, int bintype) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  switch (bintype) {
    case 0:
      for (int ibin=0; ibin<binnumber_nu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          N1Rmu_x_knmtcs[ibin]++;
          if (mode==1)             h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10) h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30) h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)            h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      if (knmtcs>xbins[binnumber_nu-1]) {
        N1Rmu_x_knmtcs[binnumber_nu-1]++;
        if (mode==1)             h1[0] -> Fill(knmtcs, OscProb);
        if (mode>=2 && mode<=10) h1[1] -> Fill(knmtcs, OscProb);
        if (mode>10 && mode<=30) h1[2] -> Fill(knmtcs, OscProb);
        if (mode>=31)            h1[3] -> Fill(knmtcs, OscProb);
      }
      break;
    case 1:
      for (int ibin=0; ibin<binnumber_mu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          N1Rmu_x_knmtcs[ibin]++;
          if (mode==1)             h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10) h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30) h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)            h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      if (knmtcs>xbins[binnumber_mu-1]) {
        N1Rmu_x_knmtcs[binnumber_mu-1]++;
        if (mode==1)             h1[0] -> Fill(knmtcs, OscProb);
        if (mode>=2 && mode<=10) h1[1] -> Fill(knmtcs, OscProb);
        if (mode>10 && mode<=30) h1[2] -> Fill(knmtcs, OscProb);
        if (mode>=31)            h1[3] -> Fill(knmtcs, OscProb);
      }
      break;
    default:
      break;
  }
}

void NTagAnalysis::TaggedN_x_kinematics(CC0PiNumu* numu, int TaggedN, int TaggedNoise, float knmtcs, double* xbins, int* TaggedN_x_knmtcs, TH1F** h1, int bintype) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  switch (bintype) {
    case 0:
      for (int ibin=0; ibin<binnumber_nu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          //Tagged truth neutrons
          for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
            TaggedN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
          //Tagged noise
          for (int itagn=0; itagn<TaggedNoise; itagn++) {
            TaggedN_x_knmtcs[ibin]++;
            h1[4] -> Fill(knmtcs, OscProb);
          }
        }
      }
      if (knmtcs>xbins[binnumber_nu-1]) {
        for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
          TaggedN_x_knmtcs[binnumber_nu-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
        for (int itagn=0; itagn<TaggedNoise; itagn++) {
          TaggedN_x_knmtcs[binnumber_nu-1]++;
          h1[4] -> Fill(knmtcs, OscProb);
        }
      }
      break;
    case 1:
      for (int ibin=0; ibin<binnumber_mu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
            TaggedN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
          for (int itagn=0; itagn<TaggedNoise; itagn++) {
            TaggedN_x_knmtcs[ibin]++;
            h1[4] -> Fill(knmtcs, OscProb);
          }
        }
      }
      if (knmtcs>xbins[binnumber_mu-1]) {
        for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
          TaggedN_x_knmtcs[binnumber_mu-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
        for (int itagn=0; itagn<TaggedNoise; itagn++) {
          TaggedN_x_knmtcs[binnumber_mu-1]++;
          h1[4] -> Fill(knmtcs, OscProb);
        }
      }
      break;
    default:
      break;
  }
}

void NTagAnalysis::TrueN_x_kinematics(CC0PiNumu* numu, std::vector<int> *Type, std::vector<float> *t, float WinMin, float knmtcs, double* xbins, int* TrueN_x_knmtcs, TH1F** h1, int bintype) {
  if (Type->size()==0) return;
  int TrueN = 0;
  for (UInt_t itrue=0; itrue<Type->size(); itrue++) {
    if (Type->at(itrue)==2 && t->at(itrue)>WinMin) TrueN++;
  }

  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  switch (bintype) {
    case 0:
      for (int ibin=0; ibin<binnumber_nu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          for (int itruen=0; itruen<TrueN; itruen++) {
            TrueN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
        }
      }
      if (knmtcs>xbins[binnumber_nu-1]) {
        for (int itruen=0; itruen<TrueN; itruen++) {
          TrueN_x_knmtcs[binnumber_nu-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      break;
    case 1:
      for (int ibin=0; ibin<binnumber_mu-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          for (int itruen=0; itruen<TrueN; itruen++) {
            TrueN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
        }
      }
      if (knmtcs>xbins[binnumber_mu-1]) {
        for (int itruen=0; itruen<TrueN; itruen++) {
          TrueN_x_knmtcs[binnumber_mu-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      break;
    default:
      break;
  }
}


void NTagAnalysis::TrueN_x_Neutronkinematics(CC0PiNumu* numu, float knmtcs, double* xbins, int* TrueN_x_knmtcs, TH1F** h1, int bintype) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  switch (bintype) {
    case 0:
      for (int ibin=0; ibin<binnumber_n-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          TrueN_x_knmtcs[ibin]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n-1]) {
        TrueN_x_knmtcs[binnumber_n-1]++;
        if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
        if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
        if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
        if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
      }
      break;
    case 1:
      for (int ibin=0; ibin<binnumber_n2-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          TrueN_x_knmtcs[ibin]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n2-1]) {
        TrueN_x_knmtcs[binnumber_n2-1]++;
        if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
        if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
        if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
        if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
      }
      break;
    case 2:
      for (int ibin=0; ibin<binnumber_n3-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          TrueN_x_knmtcs[ibin]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n3-1]) {
        TrueN_x_knmtcs[binnumber_n3-1]++;
        if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
        if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
        if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
        if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
      }
      break;
    default:
      break;
  }
}


void NTagAnalysis::TaggedN_x_Neutronkinematics(CC0PiNumu* numu, std::vector<float> *Label, UInt_t ican, float knmtcs, double* xbins, int* TaggedN_x_knmtcs, TH1F** h1, int bintype) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  switch (bintype) {
    case 0:
      for (int ibin=0; ibin<binnumber_n-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          //Tagged truth neutrons
          //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
          if (Label->at(ican)==2 || Label->at(ican)==3) {
            TaggedN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
          //}
          //Tagged noise
          //for (int itagn=0; itagn<TaggedNoise; itagn++) {
          else {
            TaggedN_x_knmtcs[ibin]++;
            h1[4] -> Fill(knmtcs, OscProb);
          }
          //}
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n-1]) {
        //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
        if (Label->at(ican)==2 || Label->at(ican)==3) {
          TaggedN_x_knmtcs[binnumber_n-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
        //}
        //for (int itagn=0; itagn<TaggedNoise; itagn++) {
        else {
          TaggedN_x_knmtcs[binnumber_n-1]++;
          h1[4] -> Fill(knmtcs, OscProb);
        }
        //}
      }
      break;
    case 1:
      for (int ibin=0; ibin<binnumber_n2-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          //Tagged truth neutrons
          //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
          if (Label->at(ican)==2 || Label->at(ican)==3) {
            TaggedN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
          //}
          //Tagged noise
          //for (int itagn=0; itagn<TaggedNoise; itagn++) {
          else {
            TaggedN_x_knmtcs[ibin]++;
            h1[4] -> Fill(knmtcs, OscProb);
          }
          //}
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n2-1]) {
        //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
        if (Label->at(ican)==2 || Label->at(ican)==3) {
          TaggedN_x_knmtcs[binnumber_n2-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
        //}
        //for (int itagn=0; itagn<TaggedNoise; itagn++) {
        else {
          TaggedN_x_knmtcs[binnumber_n2-1]++;
          h1[4] -> Fill(knmtcs, OscProb);
        }
        //}
      }
      break;
    case 2:
      for (int ibin=0; ibin<binnumber_n3-1; ibin++) {
        if (knmtcs>=xbins[ibin] && knmtcs<xbins[ibin+1]) {
          //Tagged truth neutrons
          //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
          if (Label->at(ican)==2 || Label->at(ican)==3) {
            TaggedN_x_knmtcs[ibin]++;
            if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
            if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
            if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
            if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
          }
          //}
          //Tagged noise
          //for (int itagn=0; itagn<TaggedNoise; itagn++) {
          else {
            TaggedN_x_knmtcs[ibin]++;
            h1[4] -> Fill(knmtcs, OscProb);
          }
          //}
        }
      }
      //out of visual range
      if (knmtcs>xbins[binnumber_n3-1]) {
        //for (int itagn=0; itagn<TaggedN-TaggedNoise; itagn++) {
        if (Label->at(ican)==2 || Label->at(ican)==3) {
          TaggedN_x_knmtcs[binnumber_n3-1]++;
          if (mode==1)              h1[0] -> Fill(knmtcs, OscProb);
          if (mode>=2 && mode<=10)  h1[1] -> Fill(knmtcs, OscProb);
          if (mode>10 && mode<=30)  h1[2] -> Fill(knmtcs, OscProb);
          if (mode>=31)             h1[3] -> Fill(knmtcs, OscProb);
        }
        //}
        //for (int itagn=0; itagn<TaggedNoise; itagn++) {
        else {
          TaggedN_x_knmtcs[binnumber_n3-1]++;
          h1[4] -> Fill(knmtcs, OscProb);
        }
        //}
      }
      break;
    default:
      break;
  }
}



void NTagAnalysis::cdNTagAnalysis(TFile* fout) {
  fout -> mkdir("NTagAnalysis");
  fout -> cd("NTagAnalysis");
}

void NTagAnalysis::WritePlots() {

  h1_GenPrmNeutrons    -> Write();
  h1_GenAftSINeutrons  -> Write();
  h1_GenBefSINeutrons  -> Write();

  h1_TrueNCapTime -> Write();
  for (int i=0; i<4; i++) {
    h1_RecoNCapTime[i] -> Write();
    //h1_N50[i] -> Write();
  }
  h1_mintimediff_NCap -> Write();
  h1_NCapVtxReso -> Write();

  h1_GenBefSInE -> Write();
  h1_GenSInE    -> Write();

  h2_TrueNCapVtxXY -> Write();
  h2_TrueNCapVtxRZ -> Write();

  for (int i=0; i<4; i++) {
    h1_N1Rmu_x_Enu[i]     -> Write();
    h1_N1Rmu_x_MuMom[i]   -> Write();
    h1_N1Rmu_x_MuPt[i]    -> Write();
    h1_N1Rmu_x_Q2[i]      -> Write();
    h1_N1Rmu_x_MuAngle[i] -> Write();

    h1_TrueN_x_Enu[i]     -> Write();
    h1_TrueN_x_MuMom[i]   -> Write();
    h1_TrueN_x_MuPt[i]    -> Write();
    h1_TrueN_x_Q2[i]      -> Write();
    h1_TrueN_x_MuAngle[i] -> Write();

    h1_TrueN_x_nTraveld[i]   -> Write();
    h1_TrueN_x_nTraveldL[i]  -> Write();
    h1_TrueN_x_nTraveldT[i]  -> Write();
    h1_TrueN_x_MuStp_NCap[i] -> Write();
    h1_TrueN_x_nAngle[i]     -> Write();
  }

  for (int i=0; i<5; i++) {
    h1_TaggedN_x_Enu[i]     -> Write();
    h1_TaggedN_x_MuMom[i]   -> Write();
    h1_TaggedN_x_MuPt[i]    -> Write();
    h1_TaggedN_x_Q2[i]      -> Write();
    h1_TaggedN_x_MuAngle[i] -> Write();

    h1_TaggedN_x_nTraveld[i]   -> Write();
    h1_TaggedN_x_nTraveldL[i]  -> Write();
    h1_TaggedN_x_nTraveldT[i]  -> Write();
    h1_TaggedN_x_MuStp_NCap[i] -> Write();
    h1_TaggedN_x_nAngle[i]     -> Write();
  }
  
  for (int i=0; i<TRUETYPE; i++) {
  //  Double_t tot = h1_NTrueN[i]->Integral();
    //h1_NTrueN[i] -> Scale(1./tot);
    h1_NTrueN[i] -> Write();
    //h1_hitsearch[i] -> Write();
  }
  h1_TrueMuN -> Write();
  h1_TrueNuN -> Write();
  h1_TotGammaE -> Write();

  for (int i=0; i<2; i++) {
    h1_Enureso_All[i]           -> Write();
    h1_Enureso_CCnonQE[i]       -> Write();
    h1_Enureso_CCQE[i]          -> Write();
    h1_Enureso_CC2p2h[i]        -> Write();
    h1_Enureso_CCRES_deltap[i]  -> Write();
    h1_Enureso_CCRES_deltapp[i] -> Write();
    h1_Enureso_CCRES_delta0[i]  -> Write();
    h1_Enureso_CCOther[i]       -> Write();
    h1_Enureso_NC[i]            -> Write();

    h1_Enureso_CCQE_trueN[i]          -> Write();
    h1_Enureso_CC2p2h_trueN[i]        -> Write();
    h1_Enureso_CCRES_deltap_trueN[i]  -> Write();
    h1_Enureso_CCRES_deltapp_trueN[i] -> Write();
    h1_Enureso_CCRES_delta0_trueN[i]  -> Write();
    h1_Enureso_CCOther_trueN[i]       -> Write();
    h1_Enureso_NC_trueN[i]            -> Write();
  }

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueNmultiplicity[i] -> Write();
    h1_TagNmultiplicity[i]  -> Write();
  }

  //Noise rate as a function of TagOut for each time window
  for (int i=0; i<WINSTEP; i++) g_NoiseRate[i] -> Write();  //Graph1-6
  //Efficiency as a function of the maximum of time window
  g_NNEffwin        -> Write();  //Graph7
  g_NNHEffwin       -> Write();  //Graph8
  g_NNGdEffwin      -> Write();  //Graph9
  g_OverallEffwin   -> Write();  //Graph10
  g_OverallHEffwin  -> Write();  //Graph11
  g_OverallGdEffwin -> Write();  //Graph12

  //Efficiency as a funtcion of TagOut
  g_NNEff         -> Write();  //Graph13
  g_NNHEff        -> Write();  //Graph14
  g_NNGdEff       -> Write();  //Graph15
  g_OverallEff    -> Write();  //Graph16
  g_OverallHEff   -> Write();  //Graph17
  g_OverallGdEff  -> Write();  //Graph18
  //Purity as a funtcion of TagOut
  g_Purity        -> Write();  //Graph19
  //Noise rate as a funtcion of TagOut at a ceratin time window
  g_FillNoiseRate -> Write();  //Graph20
  g_ROC           -> Write();  //Graph21
}

