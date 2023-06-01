#pragma once

//#include "../../../include/NTagVariables.h"
#include "../../../include/Const.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "TH1D.h"
#include "TH2D.h"

float DistanceMax = 5.;

//Truth distance distribution
TH1F* h1_truedistance;
TH1F* h1_truedistance_CCQE;
TH1F* h1_truedistance_CC2p2h;
TH1F* h1_truedistance_CCOther;
TH1F* h1_truedistance_CCnonQE;
TH1F* h1_truedistance_NC;


TH1F* h1_truedistance_nu_n;      //mu stopping - neutron capture vtx
TH1F* h1_truedistance_mu_n;      //mu stopping - neutron capture vtx
TH1F* h1_truedistance_prm_nu_n;  //primary - neutron capture vtx
TH1F* h1_truedistance_prm_mu_n;  //primary - neutron capture vtx
TH1F* h1_truedistance_nu_BefSIn; 
TH1F* h1_truedistance_nu_SIn;
TH1F* h1_TruePrmMuEnd_x_TagNCap[4];
TH1F* h1_TruePrmMuEnd_x_TagNCap_MuN;
TH1F* h1_TruePrmMuEnd_x_TagNCap_NuN;
TH2F* h2_TruePrmMuEnd_x_TagNCap_x_Pmu;
TH2F* h2_Prm_NCap_x_MuStp_x_NCap;
TH1F* h1_RecoPrmMuEnd_x_TagNCap[4];
TH1F* h1_RecoPrmMuEnd_x_TagNCap_MuN;
TH1F* h1_RecoPrmMuEnd_x_TagNCap_NuN;

TH1F* h1_truedistance_mudecay;  // |primary vtx - mu decay vertex|
TH1F* h1_truedistance_pidecay;  // |primary vtx - pi+ decay vertex|
TH1F* h1_TruePrmMuEnd_x_fQDcyE[7];  //CCQE, CC2p2h, CCother, NC, CCother(CC0pi, CC1pi, CCXpi)
TH1F* h1_TruePrmMuEnd_x_fQDcyE_MuDcy;
TH1F* h1_TruePrmMuEnd_x_fQDcyE_PiDcy;
TH2F* h2_TruePrmMuEnd_x_fQDcyE_x_Enu;
TH2F* h2_TruePrmMuEnd_x_fQDcyE_x_Pmu;
TH1F* h1_Erec[6];

TH2F* h2_TruePmu_x_TrueRange;
TH2F* h2_RecoPmu_x_RecoRange;
TH1F* h1_RecoMuTrack;
TH2F* h2_MuTrack_x_Prm_NCap;
TH2F* h2_MuTrack_x_MuStp_x_NCap;
TH2F* h2_Enu_x_MuTrack;
TH2F* h2_Enu_x_Prm_NCap;
TH2F* h2_Enu_x_MuStp_NCap;

//TH2F* h2_truedistance_x_mom;

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

    float TakeDistance(float *Vtx1, float *Vtx2);
    float TakeTransversalDistance(float *Dir, float *Vtx1, float *Vtx2);

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