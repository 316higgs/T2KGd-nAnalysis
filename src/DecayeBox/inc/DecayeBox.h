#pragma once

#include "../../../include/Const.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH2D.h"

//number of decay-e
TH1F* h1_TaggedDecaye[4];
TH1F* h1_TaggedDecaye_CCPiTopo[3];
TH1F* h1_mode;
TH1F* h1_PiPlusFate;
TH1F* h1_PiPlusMom_PiDcy;
TH1F* h1_PiPlusMom_PiAbs;
TH1F* h1_PiPlusMom_PiHad;
TH2F* h2_PiPlusMom_x_Enu;
TH1F* h1_TaggedDecaye_CCQE;
TH1F* h1_TaggedDecaye_CCpi;
TH1F* h1_mintimediff;
TH1F* h1_DcyVtxReso;
TH1F* h1_pscnd;
//TH1F* h1_iprtscnd;
TH1F* h1_TrueDecaye[INTERACTIONTYPE];     //original (C1-C3)
TH1F* h1_TrueDecaye_vtx[INTERACTIONTYPE]; //add vtx cut

//dt vs N50 for decay-e cut
TH2D* h2_dtn50;

TH2F* h2_reso_x_pscnd;
TH2F* h2_DcyVtxReso_x_pscnd;
TH2F* h2_DcyVtxReso_x_dwall;

//int NumHotSpot = 0;
int TaggedTrueDecaye = 0;
int TaggedDecayeinBox = 0; //for new selection
int TaggedDecaye      = 0; //for older selection

//Variables for purity & efficiency calculation
/*int AllTrueDcye   = 0;
int AllfQdcye     = 0;
int BoxfQdcye     = 0;
int MatchedfQdcye = 0;*/

float AllTrueDcye   = 0.;
float AllfQdcye     = 0.;
float BoxfQdcye     = 0.;
float MatchedfQdcye = 0.;

int DcyE_CCQE = 0;
int DcyE_CC2p2h = 0;
int DcyE_CCnonQE = 0;
int DcyE_NC = 0;

class DecayeBox {
  public:
  	DecayeBox(){};
  	virtual ~DecayeBox(){};

  	bool GetTrueMuEndVtx(OscChan::E_OSC_CHAN eOsc, Int_t *iprntidx, CC0PiNumu *numu, float *MuEndVtx);
    bool GetTruePiRange();
    bool GetTruePiDcyVtx(OscChan::E_OSC_CHAN eOsc, int iscnd, Int_t *iprntidx, CC0PiNumu *numu, float *PiDcyVtx);
    bool GetTruePrmMuDcyVtx(OscChan::E_OSC_CHAN eOsc, int iscnd, Int_t *iprntidx, CC0PiNumu *numu, float *MuDcyVtx);
    float GetRecoMuEndVtx(CC0PiNumu* numu, float *MuEndVtx);
    bool GetTruePrmMuMom(Float_t Pvc[][3], CC0PiNumu *numu, float *MuMom);
    bool GetRecoDcyEGenVtx(int iscnd, CC0PiNumu* numu, float *RecoDcyEVtx);
    bool CC0PiFilter(CC0PiNumu* numu);

  	int GetDecayeInBox(CC0PiNumu* numu, 
  		               BeamMode::E_BEAM_MODE eMode, 
  		               OscChan::E_OSC_CHAN eOsc,
  		               float dtCut,
	                   float N50CutMin,
	                   float N50CutMax,
	                   bool histofill);

    int GetDecayeTagPurity(CC0PiNumu* numu,
  		                     Float_t *tscnd,
  		                     Float_t pscnd[][3],
  		                     float dtCut,
	                         float N50CutMin,
	                         float N50CutMax);

    int GetTruthDecaye(CC0PiNumu* numu, int NumDcyE);
  	int GetTaggedDecaye(CC0PiNumu* numu);

  	void SetHistoFrame();
  	void SetHistoFormat();
    void cdDecayeBox(TFile* fout);
  	void WritePlots();
};
