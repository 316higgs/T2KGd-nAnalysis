#pragma once

#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/EvSelVar_t.h"
#include "../../DecayeBox/inc/DecayeBox.h"
#include "../../TreeManager/inc/TreeManager.h"
#include "../../../include/Const.h"
#include "TH1D.h"

//Selected events by 1R muon selection
TH1F* h1_1RmuonEvents;
TH1F* h1_Proto1RmuonEvents;
TH1F* h1_SelNuEvents[4];
TH1F* h1_SelTagN[4];
TH1F* h1_AllSelTagN;

TH1F* h1_evis[INTERACTIONTYPE];
TH1F* h1_dwall[INTERACTIONTYPE];
TH1F* h1_Nring[INTERACTIONTYPE];
TH1F* h1_emulikelihood[INTERACTIONTYPE];
TH1F* h1_Pmu[INTERACTIONTYPE];
TH1F* h1_Decaye[INTERACTIONTYPE];
TH1F* h1_pimulikelihood[INTERACTIONTYPE];

TH1F* h1_Allevis;
TH1F* h1_Alldwall;
TH1F* h1_AllNring;
TH1F* h1_Allemulikelihood;
TH1F* h1_AllPmu;
TH1F* h1_AllDecaye;
TH1F* h1_Allpimulikelihood;

class Gd1RmuonSelection {
  public:
  	Gd1RmuonSelection(){};
  	virtual ~Gd1RmuonSelection(){};

    float GetEvis(CC0PiNumu* numu);
    float GetDWall(CC0PiNumu* numu);
    int   GetNring(CC0PiNumu* numu);
    float GetemuLikelihood(CC0PiNumu* numu);
    float GetPmu(CC0PiNumu* numu);
    float GetpimuLikelihood(CC0PiNumu* numu);

    bool C1ApplyFCFV(EvSelVar_t evsel);
    bool C2Apply1R(EvSelVar_t evsel);
    bool C2Apply1RCheck(EvSelVar_t evsel, CC0PiNumu* numu, TreeManager* tree);
    bool C3Applymuonlike(EvSelVar_t evsel);
    bool C4ApplyPmu200MeV(EvSelVar_t evsel);
    bool C4ApplyPe1MeV(CC0PiNumu* numu);
    bool C5Applydecaye(EvSelVar_t evsel,
                       CC0PiNumu* numu,
                       DecayeBox decayebox, 
                       BeamMode::E_BEAM_MODE eMode, 
                       OscChan::E_OSC_CHAN eOsc,
                       float dtCut,
                       float N50CutMin,
                       float N50CutMax,
                       bool dtvsn50fill);
    bool C5ApplyProtodecaye(EvSelVar_t evsel);
    bool C6Applynotpionlike(EvSelVar_t evsel);

    bool Apply1RmuonSelection(EvSelVar_t evsel,
                              CC0PiNumu* numu,
                              DecayeBox decayebox, 
                              BeamMode::E_BEAM_MODE eMode, 
                              OscChan::E_OSC_CHAN eOsc,
                              float dtCut,
                              float N50CutMin,
                              float N50CutMax,
                              bool dtvsn50fill);
    bool ApplyProto1RmuonSelection(EvSelVar_t evsel);
    bool Apply1ReSelection(EvSelVar_t evsel,
                              CC0PiNumu* numu,
                              DecayeBox decayebox, 
                              BeamMode::E_BEAM_MODE eMode, 
                              OscChan::E_OSC_CHAN eOsc,
                              float dtCut,
                              float N50CutMin,
                              float N50CutMax,
                              bool dtvsn50fill);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdGd1RmuonSelection(TFile* fout);
    void WritePlots();
};