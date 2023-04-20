#pragma once

#include "./Const.h"
#include "../src/DecayeBox/inc/DecayeBox.h"
#include "../src/Gd1RmuonSelection/inc/Gd1RmuonSelection.h"
//#include "../src/NeutrinoOscillation/inc/NeutrinoOscillation.h"

//#define SELECTIONCUTS 6
//#define INTERACTIONTYPE 7

int processmax = 0;

int AllParentNeutrinos = 0;

//1R muon selection
int ProtoSelectedParentNeutrinos[SELECTIONCUTS];
int SelectedParentNeutrinos[SELECTIONCUTS];
float SelectedCCQENeutrinos[SELECTIONCUTS];
float SelectedCC2p2hNeutrinos[SELECTIONCUTS];
float SelectedCCnonQENeutrinos[SELECTIONCUTS];
float SelectedNCNeutrinos[SELECTIONCUTS];
float SelectedCCQETagN[SELECTIONCUTS];
float SelectedCC2p2hTagN[SELECTIONCUTS];
float SelectedCCnonQETagN[SELECTIONCUTS];
float SelectedNCTagN[SELECTIONCUTS];

//Decay-e cut scan (after C.1-C.4 applying)
//dt = 20 us, 15 us, 10 us, 5 us, 3 us
int SelectedParentNeutrinos_dtScan[DecayeCutPoint];
int FinalSelectedParentNeutrinos_dtScan[DecayeCutPoint];
//N50 = 50, , 10 us, 5 us, 3 us
//int SelectedParentNeutrinos_N50Scan[DecayeCutPoint];

int CCQEwTaggedNeutrons      = 0; // #CCQE events w/ tagged-n
int CCQEwTaggedNeutrons_prm  = 0; // #CCQE events w/ tagged-n (nonzero truth primary neutrons)
int CCQEwTaggedNeutrons_scnd = 0; // #CCQE events w/ tagged-n (nonzero truth secondary neutrons)
int AllPrimaryNeutrons = 0;
int AllSINeutrons      = 0;
int AllOtherNeutrons   = 0;

void ResetNeutrinoEvents() {
  for (int i=0; i<SELECTIONCUTS; i++) {
    ProtoSelectedParentNeutrinos[i] = 0;
    SelectedParentNeutrinos[i]      = 0;
  }
  for (int i=0; i<DecayeCutPoint; i++) {
    SelectedParentNeutrinos_dtScan[i]      = 0;
    FinalSelectedParentNeutrinos_dtScan[i] = 0;
  }
}

//Selected neutrino events
int ProtoSelectedCCQEevents    = 0;
int ProtoSelectedCCnonQEevents = 0;
int ProtoSelectedNCevents      = 0;

int SelectedCCQEevents    = 0;
int SelectedCC2p2hevents  = 0;
int SelectedCCnonQEevents = 0;
int SelectedNCevents      = 0;

float OscillatedAll = 0.;

//Oscillated neutrino events with only legacy neutrino selection
float OscillatedCCQE    = 0.;
float OscillatedCCnonQE = 0.;
float OscillatedCCRES0  = 0.;
float OscillatedCCRESp  = 0.;
float OscillatedCCRESpp = 0.;
float OscillatedCCOther = 0.;
float OscillatedNC      = 0.;

//Oscillated neutrino events w/ tagged neutrons
float OscillatedCCQE_wTagN    = 0.;
float OscillatedCCnonQE_wTagN = 0.;
float OscillatedCCRES0_wTagN  = 0.;
float OscillatedCCRESp_wTagN  = 0.;
float OscillatedCCRESpp_wTagN = 0.;
float OscillatedCCOther_wTagN = 0.;
float OscillatedNC_wTagN      = 0.;

//Oscillated neutrino events w/o tagged neutrons
float OscillatedCCQE_woTagN    = 0.;
float OscillatedCCnonQE_woTagN = 0.;
float OscillatedCCRES0_woTagN  = 0.;
float OscillatedCCRESp_woTagN  = 0.;
float OscillatedCCRESpp_woTagN = 0.;
float OscillatedCCOther_woTagN = 0.;
float OscillatedNC_woTagN      = 0.;

//Oscillated neutrino events w/ truth neutrons
float OscillatedCCQE_wTrueN    = 0.;
float OscillatedCCnonQE_wTrueN = 0.;
float OscillatedCCRES0_wTrueN  = 0.;
float OscillatedCCRESp_wTrueN  = 0.;
float OscillatedCCRESpp_wTrueN = 0.;
float OscillatedCCOther_wTrueN = 0.;
float OscillatedNC_wTrueN      = 0.;

//Oscillated neutrino events w/o truth neutrons
float OscillatedCCQE_woTrueN    = 0.;
float OscillatedCCnonQE_woTrueN = 0.;
float OscillatedCCRES0_woTrueN  = 0.;
float OscillatedCCRESp_woTrueN  = 0.;
float OscillatedCCRESpp_woTrueN = 0.;
float OscillatedCCOther_woTrueN = 0.;
float OscillatedNC_woTrueN      = 0.;

//Oscillated neutrino events within [0.25 GeV, 1.5 GeV]
float NoOscLegacy   = 0.;
float NoOscOnlyCCQE = 0.;
float NoOscwoTrueN  = 0.;
float NoOscwoTagN   = 0.;

float OscLegacy   = 0.;
float OscOnlyCCQE = 0.;
float OscwoTrueN  = 0.;
float OscwoTagN   = 0.;


//1R muon selection + w/o truth neutrons
int SelectedNeutrinoswoTruthNeutrons = 0;
int ProtoSelectedNeutrinoswoTruthNeutrons = 0;

//Normalization
int GeneratedEvents = 0;


void Sequencial1RmuonSelection(Gd1RmuonSelection prmsel,
                               EvSelVar_t evsel,
                               CC0PiNumu* numu,
                               DecayeBox decayebox, 
                               BeamMode::E_BEAM_MODE eMode, 
                               OscChan::E_OSC_CHAN eOsc,
                               float dtCut,
                               float N50CutMin,
                               float N50CutMax,
                               bool dtvsn50fill) 
{
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  prmsel.GetDWall(numu);
  if (prmsel.C1ApplyFCFV(evsel)) {
    SelectedParentNeutrinos[0]++;
    ProtoSelectedParentNeutrinos[0]++;
    //if (mode==1)             SelectedCCQENeutrinos[0]++;
    //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[0]++;
    //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[0]++;
    if (mode==1)             SelectedCCQENeutrinos[0] += OscProb;
    if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[0] += OscProb;
    if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[0] += OscProb;
    if (mode>=31)            SelectedNCNeutrinos[0]++;
    prmsel.GetNring(numu);

    if (prmsel.C2Apply1R(evsel)) {
      SelectedParentNeutrinos[1]++;
      ProtoSelectedParentNeutrinos[1]++;
      //if (mode==1)             SelectedCCQENeutrinos[1]++;
      //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[1]++;
      //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[1]++;
      if (mode==1)             SelectedCCQENeutrinos[1] += OscProb;
      if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[1] += OscProb;
      if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[1] += OscProb;
      if (mode>=31)            SelectedNCNeutrinos[1]++;
      prmsel.GetemuLikelihood(numu);

      if (prmsel.C3Applymuonlike(evsel)) {
        SelectedParentNeutrinos[2]++;
        ProtoSelectedParentNeutrinos[2]++;
        //if (mode==1)             SelectedCCQENeutrinos[2]++;
        //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[2]++;
        //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[2]++;
        if (mode==1)             SelectedCCQENeutrinos[2] += OscProb;
        if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[2] += OscProb;
        if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[2] += OscProb;
        if (mode>=31)            SelectedNCNeutrinos[2]++;
        prmsel.GetPmu(numu);

        if (prmsel.C4ApplyPmu200MeV(evsel)) {
          SelectedParentNeutrinos[3]++;
          ProtoSelectedParentNeutrinos[3]++;
          //if (mode==1)             SelectedCCQENeutrinos[3]++;
          //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[3]++;
          //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[3]++;
          if (mode==1)             SelectedCCQENeutrinos[3] += OscProb;
          if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[3] += OscProb;
          if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[3] += OscProb;
          if (mode>=31)            SelectedNCNeutrinos[3]++;
          decayebox.GetTaggedDecaye(numu);
          //decayebox.GetDecayeTagPurity(numu, dtCut, N50CutMin, N50CutMax);

          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill)) {
            SelectedParentNeutrinos[4]++;
            //if (mode==1)             SelectedCCQENeutrinos[4]++;
            //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[4]++;
            //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[4]++;
            if (mode==1)             SelectedCCQENeutrinos[4] += OscProb;
            if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[4] += OscProb;
            if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[4] += OscProb;
            if (mode>=31)            SelectedNCNeutrinos[4]++;
            prmsel.GetpimuLikelihood(numu);

            if (prmsel.C6Applynotpionlike(evsel)) {
              SelectedParentNeutrinos[5]++;
              //if (mode==1)             SelectedCCQENeutrinos[5]++;
              //if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[5]++;
              //if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[5]++;
              if (mode==1)             SelectedCCQENeutrinos[5] += OscProb;
              if (mode>=2 && mode<=10) SelectedCC2p2hNeutrinos[5] += OscProb;
              if (mode>10 && mode<=30) SelectedCCnonQENeutrinos[5] += OscProb;
              if (mode>=31)            SelectedNCNeutrinos[5]++;
            }
          }

          if (prmsel.C5ApplyProtodecaye(evsel)) {
            ProtoSelectedParentNeutrinos[4]++;

            if (prmsel.C6Applynotpionlike(evsel)) {
              ProtoSelectedParentNeutrinos[5]++;
            }
          }
        }
      }
    }
  }
}

void Sequencial1ReSelection(Gd1RmuonSelection prmsel,
                               EvSelVar_t evsel,
                               CC0PiNumu* numu,
                               DecayeBox decayebox, 
                               BeamMode::E_BEAM_MODE eMode, 
                               OscChan::E_OSC_CHAN eOsc,
                               float dtCut,
                               float N50CutMin,
                               float N50CutMax,
                               bool dtvsn50fill) 
{
  prmsel.GetDWall(numu);
  if (prmsel.C1ApplyFCFV(evsel)) {
    SelectedParentNeutrinos[0]++;
    prmsel.GetNring(numu);

    if (prmsel.C2Apply1R(evsel)) {
      SelectedParentNeutrinos[1]++;
      prmsel.GetemuLikelihood(numu);

      if (prmsel.C3Applymuonlike(evsel)==false) {
        SelectedParentNeutrinos[2]++;
        prmsel.GetPmu(numu);

        if (prmsel.C4ApplyPe1MeV(numu)) {
          SelectedParentNeutrinos[3]++;
          decayebox.GetTaggedDecaye(numu);

          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill)) {
            SelectedParentNeutrinos[4]++;
            prmsel.GetpimuLikelihood(numu);

            if (prmsel.C6Applynotpionlike(evsel)) {
              SelectedParentNeutrinos[5]++;
            }
          }
        }
      }
    }
  }
}

int DecayeCutScan(Gd1RmuonSelection prmsel,
                   EvSelVar_t evsel,
                   CC0PiNumu* numu,
                   DecayeBox decayebox, 
                   BeamMode::E_BEAM_MODE eMode, 
                   OscChan::E_OSC_CHAN eOsc) 
{
  if (prmsel.C1ApplyFCFV(evsel)) {

    if (prmsel.C2Apply1R(evsel)) {

      if (prmsel.C3Applymuonlike(evsel)) {

        if (prmsel.C4ApplyPmu200MeV(evsel)) {

          //std::cout << "[### DecayeCutScan() ###] fqnse = " << numu->var<int>("fqnse") << std::endl;
          decayebox.GetDecayeInBox(numu, eMode, eOsc, 20., 50., 400., true);
          //decayebox.GetDecayeInBox(numu, eMode, eOsc, 15., 50., 400., true);
          //decayebox.GetDecayeInBox(numu, eMode, eOsc, 10., 50., 400., false);
          //decayebox.GetDecayeInBox(numu, eMode, eOsc, 5., 50., 400., false);
          //decayebox.GetDecayeInBox(numu, eMode, eOsc, 3., 50., 400., false);
          

          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false)) {
            SelectedParentNeutrinos_dtScan[0]++;
            //std::cout << " [------<-] dt=20us: passed" << std::endl;

            if (prmsel.C6Applynotpionlike(evsel)) {
              FinalSelectedParentNeutrinos_dtScan[0]++;
            }
          }
          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 15., 50., 400., false)) {
            SelectedParentNeutrinos_dtScan[1]++;
            //std::cout << " [-----<--] dt=15us: passed" << std::endl;

            if (prmsel.C6Applynotpionlike(evsel)) {
              FinalSelectedParentNeutrinos_dtScan[1]++;
            }
          }
          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 10., 50., 400., false)) {
            SelectedParentNeutrinos_dtScan[2]++;
            //std::cout << " [----<---] dt=10us: passed" << std::endl;

            if (prmsel.C6Applynotpionlike(evsel)) {
              FinalSelectedParentNeutrinos_dtScan[2]++;
            }
          }
          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 5., 50., 400., false)) {
            SelectedParentNeutrinos_dtScan[3]++;
            //std::cout << " [---<----] dt= 5us: passed" << std::endl;

            if (prmsel.C6Applynotpionlike(evsel)) {
              FinalSelectedParentNeutrinos_dtScan[3]++;
            }
          }
          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 3., 50., 400., false)) {
            SelectedParentNeutrinos_dtScan[4]++;
            //std::cout << " [--<-----] dt= 3us: passed" << std::endl;

            if (prmsel.C6Applynotpionlike(evsel)) {
              FinalSelectedParentNeutrinos_dtScan[4]++;
            }
          }

        }
      }
    }
  }
  //std::cout << " " << std::endl;

  return 0;
}

void Sequencial1RmuonSelection_Pion(Gd1RmuonSelection prmsel,
                                    EvSelVar_t evsel,
                                    CC0PiNumu* numu,
                                    DecayeBox decayebox, 
                                    BeamMode::E_BEAM_MODE eMode, 
                                    OscChan::E_OSC_CHAN eOsc,
                                    float dtCut,
                                    float N50CutMin,
                                    float N50CutMax,
                                    bool dtvsn50fill) 
{
  //CC pion productions
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==11 || mode==12 || mode==13 || mode==21) {
    if (prmsel.C1ApplyFCFV(evsel)) {
      SelectedParentNeutrinos[0]++;
      ProtoSelectedParentNeutrinos[0]++;

      if (prmsel.C2Apply1R(evsel)) {
        SelectedParentNeutrinos[1]++;
        ProtoSelectedParentNeutrinos[1]++;

        if (prmsel.C3Applymuonlike(evsel)) {
          SelectedParentNeutrinos[2]++;
          ProtoSelectedParentNeutrinos[2]++;

          if (prmsel.C4ApplyPmu200MeV(evsel)) {
            SelectedParentNeutrinos[3]++;
            ProtoSelectedParentNeutrinos[3]++;

            if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, dtCut, N50CutMin, N50CutMax, dtvsn50fill)) {
              SelectedParentNeutrinos[4]++;

              if (prmsel.C6Applynotpionlike(evsel)) {
                SelectedParentNeutrinos[5]++;
              }
            }

            if (prmsel.C5ApplyProtodecaye(evsel)) {
              ProtoSelectedParentNeutrinos[4]++;

              if (prmsel.C6Applynotpionlike(evsel)) {
                ProtoSelectedParentNeutrinos[5]++;
              }
            }
          }
        }
      }
    }
  }
}


//Count #neutrino events with respect to neutrino interactions
void GetSelectedModeEvents(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==1) SelectedCCQEevents++;
  if (mode>=2 && mode<=10) SelectedCC2p2hevents++;
  if (mode>10 && mode<=30) SelectedCCnonQEevents++;
  if (mode>=31) SelectedNCevents++;
}

void GetProtoSelectedModeEvents(CC0PiNumu* numu) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode==1) ProtoSelectedCCQEevents++;
  if (mode>=2 && mode<=30) ProtoSelectedCCnonQEevents++;
  if (mode>=31) ProtoSelectedNCevents++;
}


void GetNeutrinoInteraction(int ientry, int mode) {
  if (mode==1) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CCQE" << std::endl;
  }
  else if (mode>=2 && mode<=10) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CC 2p2h" << std::endl;
  }
  else if (mode==13) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CC RES(Delta+)" << std::endl;
  }
  else if (mode==11) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CC RES(Delta++)" << std::endl;
  }
  else if (mode==12) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CC RES(Delta0)" << std::endl;
  }
  else if (mode>13 && mode<=30) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: CC other" << std::endl;
  }
  else if (mode>=31) {
    std::cout << "[### " << ientry << " ###] Neutrino interaction: NC" << std::endl;
  }
}


int GetCCPiTopology(CC0PiNumu* numu) {
  int NumCCPi = 0;
  int mode = TMath::Abs(numu->var<int>("mode"));
  if (mode<=30) {
    for (int iprm=0; iprm<numu->var<int>("Npvc"); iprm++) {
      //std::cout << "Particle[" << iprm << "]=" << numu->var<int>("Ipvc", iprm)
      //                                         << ", Ichvc=" << numu->var<int>("Ichvc", iprm) << std::endl;
      if (std::fabs(numu->var<int>("Ipvc", iprm))==static_cast<int>(PDGPID::PIPLUS) ||
          std::fabs(numu->var<int>("Ipvc", iprm))==static_cast<int>(PDGPID::PI0))
        NumCCPi++;
    }
  }
  return NumCCPi;
}


void GetSelectedTagN(Gd1RmuonSelection prmsel, 
                     EvSelVar_t evsel, 
                     CC0PiNumu* numu, 
                     DecayeBox decayebox, 
                     BeamMode::E_BEAM_MODE eMode, 
                     OscChan::E_OSC_CHAN eOsc,
                     float dtCut,
                     float N50CutMin,
                     float N50CutMax,
                     bool dtvsn50fill,
                     int TagN) {
  int mode = TMath::Abs(numu->var<int>("mode"));
  float OscProb = numu->getOscWgt();
  if (prmsel.C1ApplyFCFV(evsel)) {
    if (mode==1)             SelectedCCQETagN[0] += TagN*OscProb;
    if (mode>=2 && mode<=10) SelectedCC2p2hTagN[0] += TagN*OscProb;
    if (mode>10 && mode<=30) SelectedCCnonQETagN[0] += TagN*OscProb;
    if (mode>=31)            SelectedNCTagN[0] += TagN;
    if (prmsel.C2Apply1R(evsel)) {
      if (mode==1)             SelectedCCQETagN[1] += TagN*OscProb;
      if (mode>=2 && mode<=10) SelectedCC2p2hTagN[1] += TagN*OscProb;
      if (mode>10 && mode<=30) SelectedCCnonQETagN[1] += TagN*OscProb;
      if (mode>=31)            SelectedNCTagN[1] += TagN;
      if (prmsel.C3Applymuonlike(evsel)) {
        if (mode==1)             SelectedCCQETagN[2] += TagN*OscProb;
        if (mode>=2 && mode<=10) SelectedCC2p2hTagN[2] += TagN*OscProb;
        if (mode>10 && mode<=30) SelectedCCnonQETagN[2] += TagN*OscProb;
        if (mode>=31)            SelectedNCTagN[2] += TagN;
        if (prmsel.C4ApplyPmu200MeV(evsel)) {
          if (mode==1)             SelectedCCQETagN[3] += TagN*OscProb;
          if (mode>=2 && mode<=10) SelectedCC2p2hTagN[3] += TagN*OscProb;
          if (mode>10 && mode<=30) SelectedCCnonQETagN[3] += TagN*OscProb;
          if (mode>=31)            SelectedNCTagN[3] += TagN;
          if (prmsel.C5Applydecaye(evsel, numu, decayebox, eMode, eOsc, 20., 50., 400., false)) {
            if (mode==1)             SelectedCCQETagN[4] += TagN*OscProb;
            if (mode>=2 && mode<=10) SelectedCC2p2hTagN[4] += TagN*OscProb;
            if (mode>10 && mode<=30) SelectedCCnonQETagN[4] += TagN*OscProb;
            if (mode>=31)            SelectedNCTagN[4] += TagN;
            if (prmsel.C6Applynotpionlike(evsel)) {
              if (mode==1)             SelectedCCQETagN[5] += TagN*OscProb;
              if (mode>=2 && mode<=10) SelectedCC2p2hTagN[5] += TagN*OscProb;
              if (mode>10 && mode<=30) SelectedCCnonQETagN[5] += TagN*OscProb;
              if (mode>=31)            SelectedNCTagN[5] += TagN;
            }
          }
        }
      }
    }
  }
}


