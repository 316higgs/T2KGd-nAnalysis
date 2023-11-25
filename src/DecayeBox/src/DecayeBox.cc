#include "../include/NeutrinoEvents.h"
#include "../include/CommonTool.h"
#include "../include/Const.h"
#include "DecayeBox.h"
#include "TGaxis.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/DefOscChannels.h"


void DecayeBox::SetHistoFrame() {
  //h1_TaggedDecaye = new TH1F("h1_TaggedDecaye", "h1_TaggedDecaye; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCQE = new TH1F("h1_TaggedDecaye_CCQE", "h1_TaggedDecaye@CCQE; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_TaggedDecaye_CCpi = new TH1F("h1_TaggedDecaye_CCpi", "h1_TaggedDecaye@CCPi; Number of Tagged Decay-e; Number of Neutrino Events", 6, 0, 6);
  h1_mintimediff       = new TH1F("h1_mintimediff", "h1_mintimediff; dt-tscnd[#musec]; Number of Events", 2000, -0.006, 0.006);
  h1_DcyVtxReso        = new TH1F("h1_DcyVtxReso", "h1_DcyVtxReso; Decay-e Vertex Resolution[cm]; Number of Events", 2000, 0, 200);
  h1_pscnd             = new TH1F("h1_pscnd", "h1_pscnd; pscnd[MeV]; Number of Events", 80, 0, 80);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueDecaye[i] = new TH1F(TString::Format("h1_TrueDecaye_mode%d", i), "TrueDecaye; Number of Truth Decay-e; Number of Neutrino Events", 8, 0, 8);
    h1_TrueDecaye_vtx[i] = new TH1F(TString::Format("h1_TrueDecaye_vtx_mode%d", i), "TrueDecaye; Number of Truth Decay-e; Number of Neutrino Events", 8, 0, 8);
  }

  for (int i=0; i<4; i++) {
    h1_TaggedDecaye[i] = new TH1F(TString::Format("h1_TaggedDecaye_mode%d", i), "Reco #decay-e; Number of Reco Decay-e; Number of Neutrino Events", 6, 0, 6);
  }
  for (int i=0; i<3; i++) {
    h1_TaggedDecaye_CCPiTopo[i] = new TH1F(TString::Format("h1_TaggedDecaye_CCpi%d", i), "Reco #decay-e; Number of Reco Decay-e; Number of Neutrino Events", 6, 0, 6);
  }
  h1_mode = new TH1F("h1_mode", "h1_mode; mode; Number of Events", 28, 0, 28);
  h1_PiPlusFate = new TH1F("h1_PiPlusFate", "h1_PiPlusFate; iprtscnd; Number of Events", 2400, 0, 2400);
  h1_PiPlusMom_PiDcy  = new TH1F("h1_PiPlusMom_PiDcy", "h1_PiPlusMom; #pi^{+} momentum P_{#pi^{+}} [MeV]; Number of Events", 50, 0, 1000);
  h1_PiPlusMom_PiAbs  = new TH1F("h1_PiPlusMom_PiAbs", "h1_PiPlusMom; #pi^{+} momentum P_{#pi^{+}} [MeV]; Number of Events", 50, 0, 1000);
  h1_PiPlusMom_PiHad  = new TH1F("h1_PiPlusMom_PiHad", "h1_PiPlusMom; #pi^{+} momentum P_{#pi^{+}} [MeV]; Number of Events", 50, 0, 1000);
  h2_PiPlusMom_x_Enu  = new TH2F("h2_PiPlusMom_x_Enu", "h2_PiPlusMom_x_Enu; E_{#nu} [GeV]; #pi^{+} momentum P_{#pi^{+}} [MeV]", 60, 0, 3, 50, 0, 1000);


  h2_reso_x_pscnd = new TH2F("h2_reso_x_pscnd", "h2_reso_x_pscnd; dt - tscnd[#musec]; pscnd[MeV]", 100, -0.006, 0.006, 80, 0, 80);
  h2_reso_x_pscnd -> SetStats(0);
  h2_DcyVtxReso_x_pscnd = new TH2F("h2_DcyVtxReso_x_pscnd", "h2_DcyVtxReso_x_pscnd; Decay-e Vertex Resolution[cm]; pscnd[MeV]", 100, 0, 200, 40, 0, 80);
  h2_DcyVtxReso_x_pscnd -> SetStats(0);
  h2_DcyVtxReso_x_dwall = new TH2F("h2_DcyVtxReso_x_dwall", "h2_DcyVtxReso_x_dwall; Decay-e Vertex Resolution[cm]; Dwall[cm]", 100, 0, 200, 40, 0, 20);
  h2_DcyVtxReso_x_dwall -> SetStats(0);

  h2_dtn50        = new TH2F("h2_dtn50", "", 100, 0, 50, 40, 0, 400);

  h1_AllN50_preNN  = new TH1F("h1_AllN50_preNN", "", 40, 0, 400);
  h1_AllN50_postNN = new TH1F("h1_AllN50_postNN", "", 40, 0, 400);
  h1_AllN50_Nlike  = new TH1F("h1_AllN50_Nlike", "", 40, 0, 400);

  //h1_AllNHits_preNN  = new TH1F("h1_AllNHits_preNN", "", 25, 0, 50);
  //h1_AllNHits_postNN = new TH1F("h1_AllNHits_postNN", "", 25, 0, 50);
  //h1_AllNHits_Nlike  = new TH1F("h1_AllNHits_Nlike", "", 25, 0, 50);
  //h1_AllNHits_Elike  = new TH1F("h1_AllNHits_Elike", "", 25, 0, 50);
  h1_AllNHits_preNN  = new TH1F("h1_AllNHits_preNN", "", 25, 0, 400);
  h1_AllNHits_postNN = new TH1F("h1_AllNHits_postNN", "", 25, 0, 400);
  h1_AllNHits_Nlike  = new TH1F("h1_AllNHits_Nlike", "", 25, 0, 400);
  h1_AllNHits_Elike  = new TH1F("h1_AllNHits_Elike", "", 25, 0, 400);
  
  h1_AllFitT_preNN   = new TH1F("h1_AllFitT_preNN", "", 25, 0, 400);
  h1_AllFitT_postNN  = new TH1F("h1_AllFitT_postNN", "", 25, 0, 400);
  h1_AllFitT_Nlike   = new TH1F("h1_AllFitT_Nlike", "", 40, 0, 400);
  h1_AllFitT_Elike   = new TH1F("h1_AllFitT_Elike", "", 40, 0, 400);

  //h1_NHits_gtr = new TH1F("h1_NHits_gtr", "", 40, 0, 400);
  //h1_NHits_lss = new TH1F("h1_NHits_lss", "", 40, 0, 400);
  //h1_FitT_gtr  = new TH1F("h1_FitT_gtr", "", 40, 0, 200);
  //h1_FitT_lss  = new TH1F("h1_FitT_lss", "", 40, 0, 200);

  for (int i=0; i<INTERACTIONTYPE_FOR_MERGE; i++) {
    h1_N50_preNN[i]  = new TH1F(TString::Format("h1_N50_preNN_mode%d", i), "", 40, 0, 400);
    h1_N50_postNN[i] = new TH1F(TString::Format("h1_N50_postNN_mode%d", i), "", 40, 0, 400);
    h1_N50_Nlike[i]  = new TH1F(TString::Format("h1_N50_Nlike_mode%d", i), "", 40, 0, 400);
    h1_NHits_preNN[i]  = new TH1F(TString::Format("h1_NHits_preNN_mode%d", i), "", 25, 0, 50);
    h1_NHits_postNN[i] = new TH1F(TString::Format("h1_NHits_postNN_mode%d", i), "", 25, 0, 50);
    h1_NHits_Nlike[i]  = new TH1F(TString::Format("h1_NHits_Nlike_mode%d", i), "", 25, 0, 400);
    h1_NHits_Elike[i]  = new TH1F(TString::Format("h1_NHits_Elike_mode%d", i), "", 25, 0, 400);
    //h1_NHits_preNN[i]  = new TH1F(TString::Format("h1_NHits_preNN_mode%d", i), "", 40, 0, 400);
    //h1_NHits_postNN[i] = new TH1F(TString::Format("h1_NHits_postNN_mode%d", i), "", 40, 0, 400);
    //h1_NHits_Nlike[i]  = new TH1F(TString::Format("h1_NHits_Nlike_mode%d", i), "", 40, 0, 400);
    h1_FitT_preNN[i]   = new TH1F(TString::Format("h1_FitT_preNN_mode%d", i), "", 40, 0, 200);
    h1_FitT_postNN[i]  = new TH1F(TString::Format("h1_FitT_postNN_mode%d", i), "", 40, 0, 200);
    h1_FitT_Nlike[i]   = new TH1F(TString::Format("h1_FitT_Nlike_mode%d", i), "", 40, 0, 200);
    h1_FitT_Elike[i]   = new TH1F(TString::Format("h1_FitT_Elike_mode%d", i), "", 40, 0, 200);
  
    /*
    h1_NHits_CutBase1[i] = new TH1F(TString::Format("h1_NHits_CutBase1_mode%d", i), "", 50, 0, 50);
    h1_NHits_CutBase2[i] = new TH1F(TString::Format("h1_NHits_CutBase2_mode%d", i), "", 50, 0, 50);
    h1_NHits_CutBase3[i] = new TH1F(TString::Format("h1_NHits_CutBase3_mode%d", i), "", 50, 0, 50);
    h1_NHits_CutBase4[i] = new TH1F(TString::Format("h1_NHits_CutBase4_mode%d", i), "", 50, 0, 50);
    h1_NHits_CutBase5[i] = new TH1F(TString::Format("h1_NHits_CutBase5_mode%d", i), "", 50, 0, 50);
    h1_NHits_CutBase6[i] = new TH1F(TString::Format("h1_NHits_CutBase6_mode%d", i), "", 50, 0, 50);
    */
  }
}

void DecayeBox::SetHistoFormat() {
  h1_TaggedDecaye_CCQE -> SetLineWidth(2);
  h1_TaggedDecaye_CCpi -> SetLineWidth(2);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    h1_TrueDecaye[i] -> SetLineWidth(2);
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_TrueDecaye[i] -> GetXaxis()->SetBinLabel(6, "5");
    h1_TrueDecaye_vtx[i] -> SetLineWidth(2);
  }

  for (int i=0; i<4; i++) {
    h1_TaggedDecaye[i] -> SetLineWidth(2);
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(1, "0");
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(2, "1");
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(3, "2");
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(4, "3");
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(5, "4");
    h1_TaggedDecaye[i] -> GetXaxis()->SetBinLabel(6, "5");
  }
}


//Get truth mu end vertex
bool DecayeBox::GetTrueMuEndVtx(OscChan::E_OSC_CHAN eOsc, Int_t *iprntidx, CC0PiNumu *numu, float *MuEndVtx) {
  bool PrmMuEnd = false;

#if 0
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    if ((std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) ||
         std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::NEUTRON)  ||
         std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::GAMMA)) && 
        (std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::PIPLUS) ||
         iprntidx[iscnd]<=0) &&
        numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY))
    {
      //decay-e from primary mu
      if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) &&
          std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) && 
          iprntidx[iscnd]<=0) 
      {
        //std::cout << "eOsc: " << eOsc << std::endl;
        //numu -> numu (find e-)
        if (eOsc==0 && numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::ELECTRON)) {
          PrmMuEnd = true;
          MuEndVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
          MuEndVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
          MuEndVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
          //std::cout << "  MuEndVtx = [" << MuEndVtx[0] << ", " << MuEndVtx[1] << ", " << MuEndVtx[2] << "]" << std::endl;
        }
        //numubar -> numubar (find e+)
        if (eOsc==3 && numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::POSITRON)) {
          PrmMuEnd = true;
          MuEndVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
          MuEndVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
          MuEndVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
          //std::cout << "  MuEndVtx = [" << MuEndVtx[0] << ", " << MuEndVtx[1] << ", " << MuEndVtx[2] << "]" << std::endl;
        }
      }
      //neutrons from primary mu
      else {
        PrmMuEnd = true;
        MuEndVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
        MuEndVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
        MuEndVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
        //std::cout << "  MuEndVtx = [" << MuEndVtx[0] << ", " << MuEndVtx[1] << ", " << MuEndVtx[2] << "]" << std::endl;
      }
    }
  }
#endif

#if 1
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {

    int mode = TMath::Abs(numu->var<int>("mode"));

    //std::cout << "Particle[" << iscnd << "]=" << numu->var<int>("iprtscnd", iscnd)
    //          << ", iprntprt=" << numu->var<int>("iprntprt", iscnd)
    //          << ", iprntidx=" << iprntidx[iscnd]  
    //          << ", lmecscnd=" << numu->var<int>("lmecscnd", iscnd) 
    //          << ", vtxscnd=[" << numu->var<float>("vtxscnd", iscnd, 0) << ", " 
    //          << numu->var<float>("vtxscnd", iscnd, 1) << ", " 
    //          << numu->var<float>("vtxscnd", iscnd, 2) << "]" << std::endl;

    if (std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) &&
        (std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::PIPLUS)) &&
        numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY))
    {
      //NC has some events with mu(->decay-e) from pi or K
      //if (std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]))!=static_cast<int>(PDGPID::PIPLUS) &&
      //    std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]))!=static_cast<int>(PDGPID::KPLUS)) {
      if (mode<=30) {
        //std::cout << "---> Parent: " << numu->var<int>("iprntprt", iprntidx[iscnd]-1) << std::endl;
        PrmMuEnd = true;
        MuEndVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
        MuEndVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
        MuEndVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
        //std::cout << "  MuEndVtx = [" << MuEndVtx[0] << ", " << MuEndVtx[1] << ", " << MuEndVtx[2] << "]" << std::endl;
      }
    }
  }
  
  //if (!PrmMuEnd) std::cout << "!!! No mu end vertex" << std::endl;
  //std::cout << " " << std::endl;
#endif

  return PrmMuEnd;
}


//Get truth pi decay vertex
bool DecayeBox::GetTruePiDcyVtx(OscChan::E_OSC_CHAN eOsc, int iscnd, Int_t *iprntidx, CC0PiNumu *numu, float *PiDcyVtx) {
  bool PiDcyE = false;
  if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
      std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))==static_cast<int>(PDGPID::PIPLUS) &&
      numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY))
  {
    PiDcyE = true;
    PiDcyVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
    PiDcyVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
    PiDcyVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
    //std::cout << "  PiDcyVtx = [" << PiDcyVtx[0] << ", " << PiDcyVtx[1] << ", " << PiDcyVtx[2] << "]" << std::endl;
  }
  else if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) &&
           std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) && 
           iprntidx[iscnd]==0) 
    {
      //numu -> numu (find e+)
      if (eOsc==0 && numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::POSITRON)) {
        PiDcyE = true;
        PiDcyVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
        PiDcyVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
        PiDcyVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
        //std::cout << "  PiDcyVtx = [" << PiDcyVtx[0] << ", " << PiDcyVtx[1] << ", " << PiDcyVtx[2] << "]" << std::endl;
      }
      //numubar -> numubar (find e+)
      if (eOsc==3 && numu->var<int>("iprtscnd", iscnd)==-static_cast<int>(PDGPID::POSITRON)) {
        PiDcyE = true;
        PiDcyVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
        PiDcyVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
        PiDcyVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
        //std::cout << "  MuDcyVtx = [" << MuDcyVtx[0] << ", " << MuDcyVtx[1] << ", " << MuDcyVtx[2] << "]" << std::endl;
      }
    }
  return PiDcyE;
}

bool DecayeBox::CC0PiFilter(CC0PiNumu* numu) {
  bool CC0pi = false;
  for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
    if (( numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::PROTON) || 
          numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::NEUTRON) ) &&
        ( std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::PIPLUS) ||
          numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::PI0) ) &&
        ( numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY) || 
          numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::HADRONIC) || 
          numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::HADRONIC_ELASTIC_COH) ) ) 
    {
      CC0pi = true;
    }
  }
  return CC0pi;
}

//Get truth (primary)mu decay vertex
bool DecayeBox::GetTruePrmMuDcyVtx(OscChan::E_OSC_CHAN eOsc, int iscnd, Int_t *iprntidx, CC0PiNumu *numu, float *MuDcyVtx) {
  bool PrmMuDcyE = false;
  if (std::fabs(numu->var<int>("iprtscnd", iscnd))==static_cast<int>(PDGPID::ELECTRON) && 
      std::fabs(numu->var<int>("iprntprt", iscnd))==static_cast<int>(PDGPID::MUON) &&
      std::fabs(numu->var<int>("iprntprt", iprntidx[iscnd]-1))!=static_cast<int>(PDGPID::PIPLUS) &&
      numu->var<int>("lmecscnd", iscnd)==static_cast<int>(GEANTINT::DECAY))
  {
    //numu -> numu (find e-)
    if (eOsc==0 && 
        numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::ELECTRON) && 
        numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::MUON) && 
        iprntidx[iscnd]<=0) 
    {
      PrmMuDcyE = true;
      MuDcyVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
      MuDcyVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
      MuDcyVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
      //std::cout << "  MuDcyVtx = [" << MuDcyVtx[0] << ", " << MuDcyVtx[1] << ", " << MuDcyVtx[2] << "]" << std::endl;
    }
    //numubar -> numubar (find e+)
    if (eOsc==3 && 
        numu->var<int>("iprtscnd", iscnd)==static_cast<int>(PDGPID::POSITRON) && 
        numu->var<int>("iprntprt", iscnd)==static_cast<int>(PDGPID::ANTIMUON) && 
        iprntidx[iscnd]<=0) 
    {
      PrmMuDcyE = true;
      MuDcyVtx[0] = numu->var<float>("vtxscnd", iscnd, 0);
      MuDcyVtx[1] = numu->var<float>("vtxscnd", iscnd, 1);
      MuDcyVtx[2] = numu->var<float>("vtxscnd", iscnd, 2);
      //std::cout << "  MuDcyVtx = [" << MuDcyVtx[0] << ", " << MuDcyVtx[1] << ", " << MuDcyVtx[2] << "]" << std::endl;
    }
  }
  return PrmMuDcyE;
}

//Get an estimation of muon stopping vertex from truth stopping range
float DecayeBox::GetRecoMuEndVtx(CC0PiNumu* numu, float *MuEndVtx) {

  //fiTQun parameters
  float RecoMuMom = numu->var<float>("fq1rmom", PrmEvent, FQ_MUHYP); // [MeV]
  float RecoMuDir[3] = {0., 0., 0.};
  RecoMuDir[0] = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 0);
  RecoMuDir[1] = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 1);
  RecoMuDir[2] = numu->var<float>("fq1rdir", PrmEvent, FQ_MUHYP, 2);
  float RecoPrmVtx[3] = {0., 0., 0.};
  RecoPrmVtx[0] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 0); // [cm]
  RecoPrmVtx[1] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 1); // [cm]
  RecoPrmVtx[2] = numu->var<float>("fq1rpos", PrmEvent, FQ_MUHYP, 2); // [cm]

  //fitting parameters (determined through true mu momentum vs mu range)
  if (RecoMuMom<200) {
    // Format: R[cm] = A x Pmu^B
    const float A = 1.04e-6;
    const float B = 2.43;
    //Predicted mu stopping vertex
    MuEndVtx[0] = RecoPrmVtx[0] + A*std::pow(RecoMuMom, B)*100.*RecoMuDir[0]; // [cm]
    MuEndVtx[1] = RecoPrmVtx[1] + A*std::pow(RecoMuMom, B)*100.*RecoMuDir[1]; // [cm]
    MuEndVtx[2] = RecoPrmVtx[2] + A*std::pow(RecoMuMom, B)*100.*RecoMuDir[2]; // [cm]
  }
  else if (RecoMuMom>=200) {
    // Format: R[cm] = A x Pmu + B
    const float A = 0.00482;
    const float B = -0.611;
    //Predicted mu stopping vertex
    MuEndVtx[0] = RecoPrmVtx[0] + (A*RecoMuMom + B)*100.*RecoMuDir[0]; // [cm]
    MuEndVtx[1] = RecoPrmVtx[1] + (A*RecoMuMom + B)*100.*RecoMuDir[1]; // [cm]
    MuEndVtx[2] = RecoPrmVtx[2] + (A*RecoMuMom + B)*100.*RecoMuDir[2]; // [cm]
  }
  //std::cout << "  MuEndVtx = [" << MuEndVtx[0] << ", " << MuEndVtx[1] << ", " << MuEndVtx[2] << "]" << std::endl;

  //Return the predicted mu range
  float RecoMuRange = GetSimpleDistance(RecoPrmVtx, MuEndVtx); // [cm]

  return RecoMuRange;
}


//Get truth (primary)mu decay vertex
bool DecayeBox::GetTruePrmMuMom(Float_t Pvc[][3], CC0PiNumu *numu, float *MuMom) {
  bool PrmMu = false;
  //int mode = TMath::Abs(numu->var<int>("mode"));
  for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
    if (numu->var<int>("Ipvc", iprm)==static_cast<int>(PDGPID::MUON)) {
      PrmMu = true;
      MuMom[0] = Pvc[iprm][0];
      MuMom[1] = Pvc[iprm][1];
      MuMom[2] = Pvc[iprm][2];
    }
  }
  return PrmMu;
}

//Get reco decay-e generation vertex
bool DecayeBox::GetRecoDcyEGenVtx(int iscnd, CC0PiNumu* numu, float *RecoDcyEVtx) {
  bool RecoDcyE = false;

  /// get dt and N50 of this subevent, and check whether this subevent is inside of the box or not.
  /// If this subevent is in the box, get its fq1rpos
  float dt  = numu->var<float>("fq1rt0", iscnd, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP);
  float N50 = numu->var<int>("fqn50", iscnd);
  //if (dt/1000. < 20. && N50 >= 50. && N50 <= 400.) {
  bool inbox = false;
  if ( dt/1000. < 1.5 ) inbox = true;
  else if ( dt/1000. < 20. && dt/1000. < 0.25*N50-7.5 ) inbox = true;
  if (inbox==true) {
    RecoDcyE = true;

    RecoDcyEVtx[0] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 0);
    RecoDcyEVtx[1] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 1);
    RecoDcyEVtx[2] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 2);

    int mode = TMath::Abs(numu->var<int>("mode"));
    if (mode==1) DcyE_CCQE++;
    if (mode>=2 && mode<=10) DcyE_CC2p2h++;
    if (mode>10 && mode<=30) DcyE_CCnonQE++;
    if (mode>=31) DcyE_NC++;
  }
  
  //RecoDcyEVtx[0] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 0);
  //RecoDcyEVtx[1] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 1);
  //RecoDcyEVtx[2] = numu->var<float>("fq1rpos", iscnd, FQ_EHYP, 2);
  //std::cout << "  RecoDcyVtx = [" << RecoDcyEVtx[0] << ", " << RecoDcyEVtx[1] << ", " << RecoDcyEVtx[2] << "]" << std::endl;

  return RecoDcyE;
}


int DecayeBox::GetDecayeInBox(CC0PiNumu* numu, 
	                            BeamMode::E_BEAM_MODE eMode, 
	                            OscChan::E_OSC_CHAN eOsc,
	                            float dtCut,
	                            float N50CutMin,
	                            float N50CutMax,
                              bool histofill) 
{
  float OscProb = numu->getOscWgt();
  int Decaye = 0;
  const int nse = numu->var<int>("fqnse");
  int mode = TMath::Abs(numu->var<int>("mode"));

  //bool fillthem = false;  //for checking of naturalness of dt scan results
  //int fillcounter = 0;    //for checking of naturalness of dt scan results
  for (int jsub=1; jsub<nse; jsub++) {
    //float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);  //wrong
    float dt  = numu->var<float>("fq1rt0", jsub, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP); //new
    float N50 = numu->var<int>("fqn50", jsub);
    //std::cout << " Matched fiTQun decya-e in the box: " << MatchedBoxfQdcye << std::endl;
    if (histofill==true) {
      if (!data) {
        if (mode<31) h2_dtn50 -> Fill(dt/1000., N50, OscProb);
        else h2_dtn50 -> Fill(dt/1000., N50);
      }
      else {
        h2_dtn50 -> Fill(dt/1000., N50);
      }
    }
    TaggedDecaye++;

    //if (dt/1000. > 15. && dt/1000. < 20.) fillthem = true;
    //if (dt/1000. > 15. && dt/1000. < 20. && N50 >=50 && N50 <= 400) fillcounter++;

    //if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) Decaye++;
    if ( dt/1000. < 1.5 ) Decaye++;
    else if ( dt/1000. < 20. && dt/1000. < 0.25*N50-7.5 ) Decaye++;
  }

  TaggedDecayeinBox += Decaye;


  //for checking of naturalness of dt scan results
  //if (fillcounter==2) fillthem = true;
  //else if (fillcounter==2) std::cout << "#decay-e in box: " << fillcounter << std::endl;

  /*for (int jsub=1; jsub<nse; jsub++) {
    float dt  = numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0);
    float N50 = numu->var<int>("fqn50", jsub);
    if (histofill==true && fillthem==true) h2_dtn50 -> Fill(dt/1000., N50);
  }*/
  return Decaye;
}



int DecayeBox::GetDecayeTagPurity(CC0PiNumu* numu,
                                  Float_t *tscnd, 
                                  Float_t pscnd[][3],
                                  float dtCut,
                                  float N50CutMin,
                                  float N50CutMax) {

  float OscProb = numu->getOscWgt();
  int mode = TMath::Abs(numu->var<int>("mode"));
  
  //Check the existence of secondary particles
  int nse_true = numu->var<int>("nscndprt");
  if (nse_true==0) return 0;  //if no secondary particles, skip this event
  //if (nse_reco<=1) return 0;  //if no subevents, skip this event

  //Make truth decay-e list
  std::vector<float> tscndlist;
  std::vector<float> pscndlist;
  std::vector<float> vtxscndXlist;
  std::vector<float> vtxscndYlist;
  std::vector<float> vtxscndZlist;
  for (int jsub=0; jsub<nse_true; jsub++) {
    if (std::fabs(numu->var<int>("iprtscnd", jsub))==static_cast<int>(PDGPID::ELECTRON) &&
        std::fabs(numu->var<int>("iprntprt", jsub))==static_cast<int>(PDGPID::MUON) &&
        std::fabs(numu->var<int>("lmecscnd", jsub))==static_cast<int>(GEANTINT::DECAY))
    {
      //std::cout << "  [true] push_back numu->tscnd = " << (numu->var<float>("tscnd", jsub))/1000. << " us" << std::endl;
      //tscndlist.push_back( (numu->var<float>("tscnd", jsub))/1000. );

      //std::cout << "  [true] push_back tscnd = " << tscnd[jsub]/1000. << " us" << std::endl;
      tscndlist.push_back( tscnd[jsub]/1000. );
      float pscndmom = std::sqrt(pscnd[jsub][0]*pscnd[jsub][0] +
                                 pscnd[jsub][1]*pscnd[jsub][1] +
                                 pscnd[jsub][2]*pscnd[jsub][2]);
      pscndlist.push_back(pscndmom);
      vtxscndXlist.push_back(numu->var<float>("vtxscnd", jsub, 0));
      vtxscndYlist.push_back(numu->var<float>("vtxscnd", jsub, 1));
      vtxscndZlist.push_back(numu->var<float>("vtxscnd", jsub, 2));

      //AllTrueDcye++;
      if (mode<31) AllTrueDcye += OscProb;
      else AllTrueDcye++;

    }
  }


  int nse_reco = numu->var<int>("fqnse");
  if (nse_reco<=1) return 0;  //if no subevents, skip this event

  //Make reco decay-e list
  std::vector<float> dtlist;
  std::vector<float> N50list;
  std::vector<float> fq1rposXlist;
  std::vector<float> fq1rposYlist;
  std::vector<float> fq1rposZlist;
  
  for (int jsub=1; jsub<nse_reco; jsub++) {
    //std::cout << "  [reco] push_back dt = " << (numu->var<float>("fq1rt0", 1, jsub) - numu->var<float>("fq1rt0", 2, 0))/1000. << " us" << std::endl;
    dtlist.push_back( (numu->var<float>("fq1rt0", jsub, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP))/1000. );
    N50list.push_back( numu->var<int>("fqn50", jsub) );
    fq1rposXlist.push_back(numu->var<float>("fq1rpos", jsub, FQ_EHYP, 0));
    fq1rposYlist.push_back(numu->var<float>("fq1rpos", jsub, FQ_EHYP, 1));
    fq1rposZlist.push_back(numu->var<float>("fq1rpos", jsub, FQ_EHYP, 2));

    float dt  = numu->var<float>("fq1rt0", jsub, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP);
    float N50 = numu->var<int>("fqn50", jsub);
    //if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) AllfQdcye++;
    //AllfQdcye++;
    if (mode<31) AllfQdcye += OscProb;
    else AllfQdcye ++;
    //if (dt/1000. < dtCut && N50 >= N50CutMin && N50 <= N50CutMax) BoxfQdcye++;

    ////  Box cut  ////
    //if ( dt/1000. < 1.5 ) BoxfQdcye++;
    //else if ( dt/1000. < 20. && dt/1000. < 0.25*N50-7.5 ) BoxfQdcye++;
    if ( dt/1000. < 1.5 ) {
      if (mode<31) BoxfQdcye += OscProb;
      else BoxfQdcye++;
    }
    else if ( dt/1000. < 20. && dt/1000. < 0.25*N50-7.5 ) {
      if (mode<31) BoxfQdcye += OscProb;
      else BoxfQdcye++;
    }
  }

  //std::vector<int> skip_itr_reco;
  std::vector<int> fin_itr_true; //final minimum truth
  std::vector<int> fin_itr_reco; //final minimum reco
  
  int truecounter = numu->var<int>("nscndprt");
  int recocounter = numu->var<int>("fqnse") - 1; //minus means subtraction of the primary lepton
  bool loopfinisher = false;
  while (loopfinisher==false) {

    //std::cout << "[### DecayeBox::GetDecayeTagPurity() ###] true:reco = " << truecounter << " : " << recocounter << std::endl;

    ///////////////////////////////////
    //1. Find pre-minimum pair
    //  1 truth -> all reco
    ///////////////////////////////////
    int tmp_itr_true = 999; //pre-minimum true
    int tmp_itr_reco = 999; //pre-minimum reco
    //Truth loop
    float pre_min = 9999999.; //time difference of the minimum reco. particle for the itrue-th particle
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {
      
      //Check
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      //std::cout << "[true# " << itrue+1 << "]";
      float this_tscnd = tscndlist.at(itrue);
      //std::cout << "  tscnd = " << this_tscnd << " us" << std::endl;

      //Reco loop
      for (long unsigned int ireco=0; ireco<dtlist.size(); ireco++) {

        //Check
        bool done_this_reco = false;
        for (long unsigned int imin=0; imin<fin_itr_reco.size(); imin++) {
          if (ireco == (long unsigned int)fin_itr_reco.at(imin)) done_this_reco = true;
        }
        if (done_this_reco==true) continue;

        //std::cout << "   [reco# " << ireco+1 << "]";
        float this_dt = dtlist.at(ireco);
        //std::cout << "  dt = " << this_dt << " us" << std::endl;

        float timediff = std::fabs( this_dt - this_tscnd );
        //std::cout << "  Time diff. = " << timediff << " us" << std::endl;

        //update (pre-minimum pair)
        if (pre_min > timediff) {
          pre_min = timediff;
          tmp_itr_true = itrue;
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
    float min_dt        = 0.;
    float min_N50       = 0.;
    float resolution    = 0.;
    float vtxresolution = 0.;
    float min_pscnd     = 0.;
    float dwall         = 0.;
    bool  inbox         = false;
    for (long unsigned int itrue=0; itrue<tscndlist.size(); itrue++) {

      //Check
      bool done_this_true = false;
      for (long unsigned int imin=0; imin<fin_itr_true.size(); imin++) {
        if (itrue == (long unsigned int)fin_itr_true.at(imin)) done_this_true = true;
      }
      if (done_this_true==true) continue;

      float this_tscnd    = tscndlist.at(itrue);
      float this_pscnd    = pscndlist.at(itrue);
      float this_vtxscndX = vtxscndXlist.at(itrue);
      float this_vtxscndY = vtxscndYlist.at(itrue);
      float this_vtxscndZ = vtxscndZlist.at(itrue);
      //std::cout << "  vtxscnd=[" << this_vtxscndX << ", " << this_vtxscndY << ", " << this_vtxscndZ << "]" << std::endl;

      //extract pre-minimum
      float this_dt       = 999.;
      float this_N50      = 0.;
      float this_fq1rposX = 0.;
      float this_fq1rposY = 0.;
      float this_fq1rposZ = 0.;
      for (long unsigned int ireco=0; ireco<dtlist.size(); ireco++) {
        if (ireco == (long unsigned int)tmp_itr_reco) {
          //std::cout << "   [reco# " << ireco+1 << "]";
          this_dt  = dtlist.at(ireco);
          this_N50 = N50list.at(ireco);
          //std::cout << "  dt = " << this_dt << " us" << std::endl;
          this_fq1rposX = fq1rposXlist.at(ireco);
          this_fq1rposY = fq1rposYlist.at(ireco);
          this_fq1rposZ = fq1rposZlist.at(ireco);
          //std::cout << "  fq1rpos=[" << this_fq1rposX << ", " << this_fq1rposY << ", " << this_fq1rposZ << "]" << std::endl;
        }
      }

      float tmp_reso     = this_dt - this_tscnd;
      float tmp_dt       = this_dt;
      float tmp_N50      = this_N50;
      float tmp_vtxresoX = this_vtxscndX - this_fq1rposX;
      float tmp_vtxresoY = this_vtxscndY - this_fq1rposY;
      float tmp_vtxresoZ = this_vtxscndZ - this_fq1rposZ;
      float tmp_vtxreso  = std::sqrt( tmp_vtxresoX*tmp_vtxresoX +
                                      tmp_vtxresoY*tmp_vtxresoY +
                                      tmp_vtxresoZ*tmp_vtxresoZ );
      float tmp_dwall    = GetDWall(this_vtxscndX, this_vtxscndY, this_vtxscndZ);

      //Final update (minimal time difference pair)
      float timediff = std::fabs( this_dt - this_tscnd );
      if (fin_min > timediff) {
        fin_min       = timediff;
        tmp2_itr_true = itrue;
        min_dt        = tmp_dt;
        min_N50       = tmp_N50;
        resolution    = tmp_reso;
        vtxresolution = tmp_vtxreso;
        min_pscnd     = this_pscnd;
        dwall         = tmp_dwall;

        //This minimum reco is in the box
        //if (min_dt < dtCut && min_N50 >= N50CutMin && min_N50 <= N50CutMax) inbox = true;
        if ( min_dt < 1.5 ) inbox = true;
        else if ( min_dt < 20. && min_dt < 0.25*min_N50-7.5 ) inbox = true;
      }
    }

    //Conclude the final minimum pair
    fin_itr_true.push_back(tmp2_itr_true);
    fin_itr_reco.push_back(tmp_itr_reco);
    //std::cout << "[Final-minimum] true:reco = " << tmp2_itr_true+1 << " : " << tmp_itr_reco+1 << std::endl;
    //std::cout << "                Final-minimum time diff. = " << fin_min << " us" << std::endl;

    // Fill minimum pair info
    //if (fillthem==true) {
    if (resolution!=0) {
      h1_mintimediff  -> Fill(resolution);
      h1_DcyVtxReso   -> Fill(vtxresolution);
      h1_pscnd        -> Fill(min_pscnd);
      h2_reso_x_pscnd -> Fill(resolution, min_pscnd);
      h2_DcyVtxReso_x_pscnd -> Fill(vtxresolution, min_pscnd);
      h2_DcyVtxReso_x_dwall -> Fill(vtxresolution, dwall/100.);

      //if (min_dt/1000. < dtCut && min_N50 >= N50CutMin && min_N50 <= N50CutMax) MatchedBoxfQdcye++;
      //if (inbox==true) MatchedBoxfQdcye++;
      if (inbox==true) {
        if (mode<31) MatchedBoxfQdcye += OscProb;
        else MatchedBoxfQdcye++;
      }

      if (mode<31) MatchedfQdcye += OscProb;
      else MatchedfQdcye++;
    }

    //Decrement the number of truth particles at last
    truecounter -= 1;
    recocounter -= 1;

    loopfinisher = (truecounter==0 || recocounter==0);
    //std::cout << "-----------------" << std::endl; 
  }
  //std::cout << " " << std::endl;

  //Get the number of tagged truth decay-e
  TaggedTrueDecaye += fin_itr_reco.size();

  //Clean up
  fin_itr_true.clear();
  fin_itr_reco.clear();

  return 0;
}


// Get reco particle list accepted by the floor cut
std::vector<int> DecayeBox::GetSelectedfQSubEvt(CC0PiNumu* numu) {
  std::vector<int> SelectedfQSubEvt;
  SelectedfQSubEvt.clear();
  std::vector<float> dtlist(numu->var<int>("fqnse")-1);
  for (int ireco=1; ireco<numu->var<int>("fqnse"); ireco++) {
    dtlist[ireco-1] = (numu->var<float>("fq1rt0", ireco, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP))/1000.; 
    float N50 = numu->var<int>("fqn50", ireco);
    if (floorcut) {
      if ( dtlist[ireco-1] < 1.5 ) SelectedfQSubEvt.push_back(ireco);
      else if ( dtlist[ireco-1] < 20. && dtlist[ireco-1] < 0.25*N50-7.5 ) SelectedfQSubEvt.push_back(ireco);
    }
    else {
      if ( dtlist[ireco-1] < 20. && N50 > 50. ) SelectedfQSubEvt.push_back(ireco);
    }
  }
  return SelectedfQSubEvt;
}

// Get reco particle list with timing matching result between truth and reco particles (true of false)
std::vector<bool> DecayeBox::GetMatchedTrueDecaye(CC0PiNumu* numu, Int_t nmue, Float_t *tscnd) {
  // initialization
  std::vector<bool> DcyeMatching;
  DcyeMatching.assign(TMath::Max( numu->var<int>("fqnse"), 1 ), false);
  
  // prompt
  if (nmue==0 && numu->var<int>("nscndprt")>0) {
    if ( std::fabs(numu->var<int>("iprntprt", 0))==static_cast<int>(PDGPID::MUON) &&
         std::fabs(numu->var<int>("lmecscnd", 0))==static_cast<int>(GEANTINT::DECAY) ) {
      DcyeMatching[0] = true;
    }
  }

  std::vector<float> tdiff;
  std::vector<int> used_TrueDcye;
  for (int ireco=1; ireco<numu->var<int>("fqnse"); ireco++) {
    
    if (numu->var<int>("nscndprt")==0) break;
    
    // time difference for matching
    for (int iscnd=0; iscnd<numu->var<int>("nscndprt"); iscnd++) {
      tdiff.push_back( std::fabs( tscnd[iscnd] - (numu->var<float>("fq1rt0", ireco, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP) ) ) );  // ns
    }
    
    // get truth secondary particle with the minimum time diff from ireco. 
    int min_idx = std::distance( tdiff.begin(), std::min_element(tdiff.begin(), tdiff.end()) );
    
    if (tdiff[min_idx] < 50.) {
      // check if this truth particle is already matched with other reco particle
      if ( std::find( used_TrueDcye.begin(), used_TrueDcye.end(), min_idx ) != used_TrueDcye.end() ) continue;
      used_TrueDcye.push_back(min_idx);

      // found
      if ( std::fabs(numu->var<int>("iprntprt", min_idx))==static_cast<int>(PDGPID::MUON) &&
           std::fabs(numu->var<int>("lmecscnd", min_idx))==static_cast<int>(GEANTINT::DECAY) ) {
        DcyeMatching[ireco] = true;
      }
    }
    tdiff.clear();
  }
  return DcyeMatching;
}


void DecayeBox::DecayeMatching(CC0PiNumu* numu, Int_t nmue, Float_t *tscnd) {

  std::vector<int> SelectedfQSubEvt = this->GetSelectedfQSubEvt(numu);
  std::vector<bool> DcyeMatching    = this->GetMatchedTrueDecaye(numu, nmue, tscnd);

  int   mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  for (int ireco=1; ireco<numu->var<int>("fqnse"); ireco++) {
    //double dt = (numu->var<float>("fq1rt0", ireco, FQ_EHYP) - numu->var<float>("fq1rt0", 0, FQ_MUHYP))/1000.;  // us

    // reject ireco
    if ( std::find( SelectedfQSubEvt.begin(), SelectedfQSubEvt.end(), ireco ) == SelectedfQSubEvt.end() ) {
      if ( DcyeMatching[ireco] ) {
        if (mode<31) RejectedMatchedTrueDcye += OscProb;
        else RejectedMatchedTrueDcye ++;
      }
    }
    // accept ireco
    else {
      if ( DcyeMatching[ireco] ) {
        if (mode<31) SelectedMatchTrueDcye += OscProb;
        else SelectedMatchTrueDcye ++;
      }
      else {
        if (mode<31) SelectedfQdcye += OscProb;
        else SelectedfQdcye ++;
      }
    }
  }

}


int DecayeBox::GetTruthDecaye(CC0PiNumu* numu, int NumDcyE) {
  int   mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();

  //CCQE(1p1h)
  if (mode==1) h1_TrueDecaye[0] -> Fill(NumDcyE, OscProb);
  //CC 2p2h
  if (mode>=2 && mode<=10) h1_TrueDecaye[1] -> Fill(NumDcyE, OscProb);
  //NC
  if (mode>=31) h1_TrueDecaye[2] -> Fill(NumDcyE);
  //CC RES (Delta+)
  if (mode==13) h1_TrueDecaye[3] -> Fill(NumDcyE, OscProb);
  //CC RES (Delta++)
  if (mode==11) h1_TrueDecaye[4] -> Fill(NumDcyE, OscProb);
  //CC RES (Delta0)
  if (mode==12) h1_TrueDecaye[5] -> Fill(NumDcyE, OscProb);
  //CC other
  if (mode>10 && mode<=30) h1_TrueDecaye[6] -> Fill(NumDcyE, OscProb);

  return NumDcyE;
}


//  #fiTQun sub-events
int DecayeBox::GetTaggedDecaye(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();

  //CCQE
  if (mode==1) h1_TaggedDecaye_CCQE -> Fill(numu->var<int>("fqdcye"), OscProb);

  //CC pion productions
  if (mode==11 || mode==12 || mode==13 || mode==21) h1_TaggedDecaye_CCpi -> Fill(numu->var<int>("fqdcye"), OscProb);

  //int NumFQDcyE = numu->var<int>("fqdcye");
  int NumFQDcyE = numu->var<int>("fqnse") - 1;
  if (mode==1)             h1_TaggedDecaye[0] -> Fill(NumFQDcyE, OscProb);
  if (mode>=2 && mode<=10) h1_TaggedDecaye[1] -> Fill(NumFQDcyE, OscProb);
  if (mode>10 && mode<=30) h1_TaggedDecaye[2] -> Fill(NumFQDcyE, OscProb);
  if (mode>=31)            h1_TaggedDecaye[3] -> Fill(NumFQDcyE);

  return numu->var<int>("fqdcye");
}


void DecayeBox::cdDecayeBox(TFile* fout) {
  fout -> mkdir("DecayeBox");
  fout -> cd("DecayeBox");
}


void DecayeBox::WritePlots() {

  /*Double_t tot_decaye_CCQE = h1_TaggedDecaye_CCQE->Integral();
  h1_TaggedDecaye_CCQE -> Scale(1./tot_decaye_CCQE);
  h1_TaggedDecaye_CCQE -> Write();

  Double_t tot_decaye_CCpi = h1_TaggedDecaye_CCpi->Integral();
  h1_TaggedDecaye_CCpi -> Scale(1./tot_decaye_CCpi);
  h1_TaggedDecaye_CCpi -> Write();
  h1_mode -> Write();
  h1_PiPlusFate -> Write();
  h1_PiPlusMom_PiDcy -> Write();
  h1_PiPlusMom_PiAbs -> Write();
  h1_PiPlusMom_PiHad -> Write();
  h2_PiPlusMom_x_Enu -> Write();*/

  h1_mintimediff -> Write();
  h1_DcyVtxReso  -> Write();
  h1_pscnd       -> Write();

  h2_reso_x_pscnd -> Write();
  h2_DcyVtxReso_x_pscnd -> Write();
  h2_DcyVtxReso_x_dwall -> Write();

  h2_dtn50    -> Scale(1./SelectedParentNeutrinos[3]);
  SaveThisHist(h2_dtn50);
  for (int i=0; i<INTERACTIONTYPE_FOR_MERGE; i++) {
    SaveThisHist(h1_N50_preNN[i]);
    SaveThisHist(h1_N50_postNN[i]);
    SaveThisHist(h1_N50_Nlike[i]);
    SaveThisHist(h1_NHits_preNN[i]);
    SaveThisHist(h1_NHits_postNN[i]);
    h1_NHits_Nlike[i] -> Write();
    h1_NHits_Elike[i] -> Write();
    SaveThisHist(h1_FitT_preNN[i]);
    SaveThisHist(h1_FitT_postNN[i]);
    h1_FitT_Nlike[i] -> Write();
    h1_FitT_Elike[i] -> Write();
    /*
    SaveThisHist(h1_NHits_CutBase1[i]);
    SaveThisHist(h1_NHits_CutBase2[i]);
    SaveThisHist(h1_NHits_CutBase3[i]);
    SaveThisHist(h1_NHits_CutBase4[i]);
    SaveThisHist(h1_NHits_CutBase5[i]);
    SaveThisHist(h1_NHits_CutBase6[i]);
    */
  }
  SaveThisHist(h1_AllN50_preNN);
  SaveThisHist(h1_AllN50_postNN);
  SaveThisHist(h1_AllN50_Nlike);

  SaveThisHist(h1_AllNHits_preNN);
  SaveThisHist(h1_AllNHits_postNN);
  SaveThisHist(h1_AllNHits_Nlike);
  SaveThisHist(h1_AllNHits_Elike);

  SaveThisHist(h1_AllFitT_preNN);
  SaveThisHist(h1_AllFitT_postNN);
  SaveThisHist(h1_AllFitT_Nlike);
  SaveThisHist(h1_AllFitT_Elike);

  //SaveThisHist(h1_NHits_gtr);
  //SaveThisHist(h1_NHits_lss);
  //SaveThisHist(h1_FitT_gtr);
  //SaveThisHist(h1_FitT_lss);

  for (int i=0; i<INTERACTIONTYPE; i++) {
    //Double_t tot_truedecaye = h1_TrueDecaye[i]->Integral();
    //h1_TrueDecaye[i] -> Scale(1./tot_truedecaye);
    h1_TrueDecaye[i] -> Write();

    //Double_t tot_truedecaye_vtx = h1_TrueDecaye_vtx[i]->Integral();
    //h1_TrueDecaye_vtx[i] -> Scale(1./tot_truedecaye_vtx);
    h1_TrueDecaye_vtx[i] -> Write();
  }

  //Double_t tot_decaye = h1_TaggedDecaye->Integral();
  //h1_TaggedDecaye -> Scale(1./tot_decaye);
  //h1_TaggedDecaye -> Write();
  for (int i=0; i<4; i++) h1_TaggedDecaye[i] -> Write();
  for (int i=0; i<3; i++) h1_TaggedDecaye_CCPiTopo[i] -> Write();
}
