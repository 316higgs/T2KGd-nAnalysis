#pragma once

//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "../../../include/NeutrinoEvents.h"
#include "TH2D.h"

#define SAMPLE 3

//All
TH1F* h1_leptonp[SAMPLE];
TH1F* h1_leptontheta[SAMPLE];
TH1F* h1_Enu[SAMPLE];

class PThetaChecker {
  public:
  	PThetaChecker() {};
  	virtual ~PThetaChecker() {};

    float GetRecoEnu(CC0PiNumu* numu, int sampleID);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdPThetaChecker(TFile* fout);
    void WritePlots();
};
