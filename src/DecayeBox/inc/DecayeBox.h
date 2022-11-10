#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH2D.h"

//number of decay-e
TH1F* h1_TaggedDecaye;
TH1F* h1_TaggedDecaye_CCQE;
TH1F* h1_TaggedDecaye_CCpi;
TH1F* h1_mintimediff;
TH1F* h1_pscnd;
TH1F* h1_iprtscnd;

//dt vs N50 for decay-e cut
TH2D* h2_dtn50;

TH2F* h2_reso_x_pscnd;
TH2F* h2_reso_x_iprtscnd;
TH2F* h2_reso_x_lmecscnd;
TH2F* h2_iprtscnd_lmecscnd;

int NumHotSpot = 0;
int TaggedTrueDecaye = 0;
int TaggedDecayeinBox = 0; //for new selection
int TaggedDecaye      = 0; //for older selection

class DecayeBox {
  public:
  	DecayeBox(){};
  	virtual ~DecayeBox(){};

  	int GetDecayeInBox(CC0PiNumu* numu, 
  		               BeamMode::E_BEAM_MODE eMode, 
  		               OscChan::E_OSC_CHAN eOsc,
  		               float dtCut,
	                   float N50CutMin,
	                   float N50CutMax,
	                   bool histofill);

  	/*int GetDecayeTagPurity(CC0PiNumu* numu,
  		                     std::vector<float> *tscndlist,
  		                     float dtCut,
	                         float N50CutMin,
	                         float N50CutMax);*/
    int GetDecayeTagPurity(CC0PiNumu* numu,
  		                     Float_t *tscnd,
  		                     Float_t pscnd[][3],
  		                     Int_t *itrkscnd,
  		                     float dtCut,
	                         float N50CutMin,
	                         float N50CutMax);

  	int GetTaggedDecaye(CC0PiNumu* numu);

  	void SetHistoFrame();
  	void SetHistoFormat();
    void cdDecayeBox(TFile* fout);
  	void WritePlots();
};
