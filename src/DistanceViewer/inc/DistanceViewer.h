#pragma once

#include "../../../include/NTagVariables.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH1D.h"


//Truth distance distribution
TH1F* h1_truedistance;
TH1F* h1_truedistance_CCQE;
TH1F* h1_truedistance_CC2p2h;
TH1F* h1_truedistance_CCOther;
TH1F* h1_truedistance_CCnonQE;
TH1F* h1_truedistance_NC;
//TH1F* h1_truedistance_CCRESdeltap;
//TH1F* h1_truedistance_CCRESdeltapp;
//TH1F* h1_truedistance_CCRESdelta0;

TH1F* h1_truedistance_particle; //test
TH1F* h1_truedistance_nu_n;
TH1F* h1_truedistance_mu;
TH1F* h1_truedistance_mu_n;
TH1F* h1_truedistance_mu_gamma;

TH1F* h1_truedistance_decaye;   // |primary vtx - decay-e genated vertex|
TH1F* h1_truedistance_mudecay;  // |primary vtx - mu decay vertex|
TH1F* h1_truedistance_pidecay;  // |primary vtx - pi+ decay vertex|


//Truth distance distribution of truth neutrons in candidates
TH1F* h1_Candidatetruedistance;

//Truth distance distribution of tagged truth neutrons
TH1F* h1_Tagtruedistance[CUTSTEP];

//Efficiency as a function of the distance
TH1F* h1_PreEff_dist;
TH1F* h1_NNEff_dist[CUTSTEP];
TH1F* h1_OverallEff_dist[CUTSTEP];


class DistanceViewer {
  public:
    DistanceViewer() {};
    virtual ~DistanceViewer() {};

    float GetTruthDistance(CC0PiNumu *numu,
                           float capturevtxx,
    	                     float capturevtxy,
    	                     float capturevtxz,
    	                     float primaryvtxx,
    	                     float primaryvtxy,
    	                     float primaryvtxz);


    void GetPreEffDistance(int tagindex,
                           UInt_t matchtrue,
                           float capturevtxx,
                           float capturevtxy,
                           float capturevtxz,
                           float primaryvtxx,
                           float primaryvtxy,
                           float primaryvtxz);

    void GetOverallEffDistance(int ith,
                               int tagindex,
                               UInt_t matchtrue,
                               float capturevtxx,
                               float capturevtxy,
                               float capturevtxz,
                               float primaryvtxx,
                               float primaryvtxy,
                               float primaryvtxz);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdDistanceViewer(TFile* fout);
    void WritePlots();
};