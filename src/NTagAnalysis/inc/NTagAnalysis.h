#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include "TH1D.h"
#include "TFile.h"
#include "TGraphErrors.h"
//#include "/disk02/usr6/rakutsu/t2k/tmp/t2ksk-neutronh/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "/disk02/usr6/sedi/anat2ksk/src/cc0pinumu/inc/CC0PiNumu.h"
#include "../../DistanceViewer/inc/DistanceViewer.h"
#include "../../NeutrinoOscillation/inc/NeutrinoOscillation.h"
#include "../../../include/NeutrinoEvents.h"

#define TRUETYPE 3
#define WINSTEP 6
#define WINDOWMIN 3
#define NOISECUT 18

TH1F* h1_NTrueN[TRUETYPE];
TH1F* h1_TrueNmultiplicity[INTERACTIONTYPE]; //# of truth captured neutrons (neutrino interactions)
TH1F* h1_TrueMuN;  //# of truth captured neutrons (neutrons from mu capture)
TH1F* h1_TrueNuN;  //# of truth captured neutrons (neutrons from neutrino interactions)
TH1F* h1_TotGammaE;
int NTrueN_CCQE    = 0;
int NTrueN_CC2p2h  = 0;
int NTrueN_CCOther = 0;
int NTrueN_NC      = 0;
float NTrueN_CCQE_osc    = 0.;
float NTrueN_CC2p2h_osc  = 0.;
float NTrueN_CCOther_osc = 0.;
float NTrueN_NC_osc      = 0.;

//Neutrino energy resolution w/ truth neutrons & w/o truth neutrons
TH1F* h1_Enureso_CCQE_trueN[2];
TH1F* h1_Enureso_CC2p2h_trueN[2];
TH1F* h1_Enureso_CCRES_deltap_trueN[2];
TH1F* h1_Enureso_CCRES_deltapp_trueN[2];
TH1F* h1_Enureso_CCRES_delta0_trueN[2];
TH1F* h1_Enureso_CCOther_trueN[2];
TH1F* h1_Enureso_NC_trueN[2];

//Neutrino energy resolution w/ tagged neutrons & w/o tagged neutrons
TH1F* h1_Enureso_All[2];
TH1F* h1_Enureso_CCnonQE[2];
TH1F* h1_Enureso_CCQE[2];
TH1F* h1_Enureso_CC2p2h[2];
TH1F* h1_Enureso_CCRES_deltap[2];
TH1F* h1_Enureso_CCRES_deltapp[2];
TH1F* h1_Enureso_CCRES_delta0[2];
TH1F* h1_Enureso_CCOther[2];
TH1F* h1_Enureso_NC[2];

//Noise rate and efficiencies for window optimization
TGraphErrors* g_NoiseRate[WINSTEP];

TGraphErrors* g_NNEffwin;
TGraphErrors* g_NNHEffwin;
TGraphErrors* g_NNGdEffwin;
TGraphErrors* g_OverallEffwin;
TGraphErrors* g_OverallHEffwin;
TGraphErrors* g_OverallGdEffwin;

TGraphErrors* g_NNEff;
TGraphErrors* g_NNHEff;
TGraphErrors* g_NNGdEff;
TGraphErrors* g_OverallEff;
TGraphErrors* g_OverallHEff;
TGraphErrors* g_OverallGdEff;

TGraphErrors* g_Purity;
TGraphErrors* g_FillNoiseRate;

//Capture vertex resolution
TH1F* h1_TrueNCapTime;
TH1F* h1_RecoNCapTime[4];
TH1F* h1_N50[4];
TH1F* h1_mintimediff_NCap;
TH1F* h1_NCapVtxReso;

TH1F* h1_GenPrmNeutrons;
TH1F* h1_GenAftFSINeutrons;
TH1F* h1_GenAftSINeutrons;  // = h1_GenBefSINeutrons + h1_GenAtSINeutrons
TH1F* h1_GenBefSINeutrons;  // captured neutrons from nu+FSI
TH1F* h1_GenAtSINeutrons;   // captured neutrons from SI
int AllBefSINeutrons = 0;
int CapBefSINeutrons = 0;
TH1F* h1_GenBefSInE;
TH1F* h1_GenSInE;

int test1 = 0;
int test2 = 0;

const int binnumber_nu = 6;
const int binnumber_mu = 5;
double xEnubins[binnumber_nu]   = {0, 0.5, 1., 1.5, 2.5, 5.};
double xMuMombins[binnumber_mu] = {0, 0.5, 1.0, 2.0, 6.0};
double xMuPtbins[binnumber_mu]  = {0, 0.25, 0.5, 0.75, 1.5};
int N1Rmu_x_Enu[binnumber_nu]   = {0};
int N1Rmu_x_MuMom[binnumber_mu] = {0};
int N1Rmu_x_MuPt[binnumber_mu]  = {0};
TH1F* h1_N1Rmu_x_Enu;
TH1F* h1_N1Rmu_x_MuMom;
TH1F* h1_N1Rmu_x_MuPt;


int varwindowmax = 9999;

void SetWindowMax(int i) {
  switch (i) {
    case 0:
      varwindowmax = 535;
      break;
    case 1:
      varwindowmax = 400;
      break;
    case 2:
      varwindowmax = 350;
      break;
    case 3:
      varwindowmax = 300;
      break;
    case 4:
      varwindowmax = 250;
      break;
    case 5:
      varwindowmax = 200;
      break;
    default:
      std::cout << "varwindowmax is invalid." << std::endl;
      break;
  }
}

//Window max for scan graph
float WindowMax[WINSTEP]; //Step of time window scan
float eWindowMax[WINSTEP];

bool nonzeroTaggedNeutrons = false;
bool NoNeutron             = false;
bool NoNlike               = false;
bool OnlyOneisDecaye       = false;
bool OnlyOneNlike          = false;

void FlagReset() {
  nonzeroTaggedNeutrons = false;
  NoNlike               = false;
  NoNeutron             = false;
  OnlyOneisDecaye       = false;
  OnlyOneNlike          = false;
}



class NTagAnalysis {
  private:
    int AllTruthNeutrons;
    int TruthHNeutrons;
    int TruthGdNeutrons;
    int AllTruthCCQENeutrons;
    int TruthCCQEHNeutrons;
    int TruthCCQEGdNeutrons;
    int AllTruthNeutronsinFV;
    int TruthHNeutronsinFV;
    int TruthGdNeutronsinFV;

    //Truth particles in search window [3 us, XXX us]
    int AllTruthNeutronsinSearch[WINSTEP];
    int TruthHNeutronsinSearch[WINSTEP];
    int TruthGdNeutronsinSearch[WINSTEP];
    int AllTruthNeutronsinSearchFV[WINSTEP];
    int TruthHNeutronsinSearchFV[WINSTEP];
    int TruthGdNeutronsinSearchFV[WINSTEP];
    int TruthDecayeinSearch[WINSTEP];

    //All candidates in window [3 us, XXX us]
    int AllCandidatesinWin[WINSTEP];
    //Truth breakdown of candidates in window [3 us, XXX us]
    int TruthNeutroninCandidatesinWin[WINSTEP];
    int TruthHNeutroninCandidatesinWin[WINSTEP];
    int TruthGdNeutroninCandidatesinWin[WINSTEP];
    int TruthDecayeinCandidatesinWin[WINSTEP];
    int TruthAccNoiseinCandidatesinWin[WINSTEP];

    //All candidates in window [3 us, XXX us] and in FV
    int AllCandidatesinWinFV[WINSTEP];
    //Truth breakdown of candidates in window [3 us, XXX us] and in FV
    int TruthNeutroninCandidatesinWinFV[WINSTEP];
    int TruthHNeutroninCandidatesinWinFV[WINSTEP];
    int TruthGdNeutroninCandidatesinWinFV[WINSTEP];
    int TruthDecayeinCandidatesinWinFV[WINSTEP];
    int TruthAccNoiseinCandidatesinWinFV[WINSTEP];

    //n-like candidates
    //Taggged truth neutrons/Mis-tagged decay-e/Mis-tagged acc. noise
    int TaggedTruthNeutronsinWin[WINSTEP][CUTSTEP];
    int TaggedTruthHNeutronsinWin[WINSTEP][CUTSTEP];
    int TaggedTruthGdNeutronsinWin[WINSTEP][CUTSTEP];
    int MisTaggedDecayeinNlike[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinNlike[WINSTEP][CUTSTEP];
    int AllNlikeCandidates[WINSTEP][CUTSTEP];

    int TaggedTruthNeutronsinWinFV[WINSTEP][CUTSTEP];
    int TaggedTruthHNeutronsinWinFV[WINSTEP][CUTSTEP];
    int TaggedTruthGdNeutronsinWinFV[WINSTEP][CUTSTEP];
    int MisTaggedDecayeinNlikeFV[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinNlikeFV[WINSTEP][CUTSTEP];
    int AllNlikeCandidatesFV[WINSTEP][CUTSTEP];

    //e-like candidates
    //Taggged truth decay-e/Mis-tagged neutrons/Mis-tagged acc. noise
    int TaggedTruthDecayeinWin[WINSTEP][CUTSTEP];
    int MisTaggedTruthNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedTruthHNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedTruthGdNeutronsinElike[WINSTEP][CUTSTEP];
    int MisTaggedAccNoiseinElike[WINSTEP][CUTSTEP];
    int AllElikeCandidates[WINSTEP][CUTSTEP];

    //
    float NoiseRate[WINSTEP][CUTSTEP];
    float eNoiseRate[WINSTEP][CUTSTEP];

    //Efficiencies for window optimization
    float NNEffinWin[WINSTEP];
    float NNHEffinWin[WINSTEP];
    float NNGdEffinWin[WINSTEP];
    float eNNEffinWin[WINSTEP];
    float eNNHEffinWin[WINSTEP];
    float eNNGdEffinWin[WINSTEP];

    float OverallEffinWin[WINSTEP];
    float OverallHEffinWin[WINSTEP];
    float OverallGdEffinWin[WINSTEP];
    float eOverallEffinWin[WINSTEP];
    float eOverallHEffinWin[WINSTEP];
    float eOverallGdEffinWin[WINSTEP];

    //Integrated efficiencies
    float PreEff;
    float PreHEff;
    float PreGdEff;

    float PreEffinFV;
    float PreHEffinFV;
    float PreGdEffinFV;

    float NNEff[CUTSTEP];
    float NNHEff[CUTSTEP];
    float NNGdEff[CUTSTEP];
    float eNNEff[CUTSTEP];
    float eNNHEff[CUTSTEP];
    float eNNGdEff[CUTSTEP];

    float NNEffinFV[CUTSTEP];
    float NNHEffinFV[CUTSTEP];
    float NNGdEffinFV[CUTSTEP];

    float OverallEff[CUTSTEP];
    float OverallHEff[CUTSTEP];
    float OverallGdEff[CUTSTEP];
    float eOverallEff[CUTSTEP];
    float eOverallHEff[CUTSTEP];
    float eOverallGdEff[CUTSTEP];

    float OverallEffinFV[CUTSTEP];
    float OverallHEffinFV[CUTSTEP];
    float OverallGdEffinFV[CUTSTEP];

    float Purity[CUTSTEP];
    float ePurity[CUTSTEP];
    float FillPurity[CUTSTEP-1];
    float FillePurity[CUTSTEP-1];
    float FillNoiseRate[CUTSTEP-1];
    float FilleNoiseRate[CUTSTEP-1];
    float FillTMVATH[CUTSTEP-1];
    float FilleTMVATH[CUTSTEP-1];

    //Neutrino events with neutron information
    float NeutrinoEventswNoNlike[CUTSTEP];
    float NeutrinoEventswNlikes[CUTSTEP];
    float NeutrinoEventswOneNlike[CUTSTEP];
    float NeutrinoEventswOneNlikeDecaye[CUTSTEP];
    float NeutrinoEventswNoTruthNeutrons[CUTSTEP];

  public:
  	NTagAnalysis() {};
  	virtual ~NTagAnalysis() {};

    void InitNeutrons();

    //Get the number of truth neutrons based on NEUT variables
    //int GetGenPrmNeutrons(CC0PiNumu *numu, Int_t *Iorgvc, Int_t *Iflvc);
    //int GetGenAftFSINeutrons(CC0PiNumu *numu);
    //int GetGenAftSINeutrons(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]);
    //int GetGenSINeutrons(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]);

    float GetGenBefSIMom(CC0PiNumu *numu, Int_t *Iorgvc, Int_t *Iflvc);

    int GetTrueNBefSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]);
    int GetTrueNAftSI(CC0PiNumu *numu, Int_t *iprntidx, Float_t vtxprnt[][3]);

    //Get the number of truth neutrons based on NTag variables
    void GetTruthNeutrons(float NTrueN,
                          CC0PiNumu* numu, 
                          std::vector<int> *Type,
                          std::vector<float> *E,
                          std::vector<float> *DWall);

    void GetTruthNeutronsIntType(CC0PiNumu* numu, float NTrueN);

    void GetTruthNeutronsinSearch(UInt_t truthneutrons, 
                                  std::vector<int> *Type,
                                  std::vector<float> *t,
                                  float WinMin,
                                  std::vector<float> *E,
                                  std::vector<float> *DWall);
    void GetTruthDecayeinSearch(UInt_t truthneutrons, 
                                  std::vector<int> *Type,
                                  std::vector<float> *t,
                                  float WinMin);
    void SummaryTruthInfoinSearch(float WinMin, TString outputname);

    void TruthBreakdowninWindow(std::vector<float> *TagClass, 
                                std::vector<float> *t,
                                std::vector<float> *DWall,
                                std::vector<float> *TagIndex,
                                std::vector<float> *Label,
                                std::vector<float> *FitT,
                                std::vector<float> *TagDWall);

    void GetNlikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *DWall,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label,
                                    std::vector<float> *TagDWall);
    void GetElikeCandidatesinWindow(std::vector<float> *t,
                                    std::vector<float> *TagIndex,
                                    bool etagmode,
                                    std::vector<float> *NHits,
                                    std::vector<float> *FitT,
                                    std::vector<float> *TagOut,
                                    std::vector<float> *Label);

    void GetNeutrinoEventswNTag(std::vector<float> *TagOut,
                                std::vector<float> *TagIndex,
                                std::vector<float> *NHits,
                                std::vector<float> *FitT,
                                std::vector<float> *Label,
                                float NTrueN,
                                bool etagmode,
                                CC0PiNumu* numu,
                                NeutrinoOscillation neuosc,
                                int NCUT,
                                float theta, float thetamin, float thetamax);

    void GetResolutionwTrueN(CC0PiNumu* numu, float NTrueN);

  	bool DecayelikeChecker(bool etagmode, float NHits, float FitT);

    void Set1RmuonSamplewNTag(bool NoNlike, CC0PiNumu* numu, float theta, float thetamin, float thetamax);

    //For neutron multiplicity measurement
    float GetTaggedNeutrons(std::vector<float> *TagOut,
                            float Threshold,
                            std::vector<float> *TagIndex,
                            std::vector<float> *NHits,
                            std::vector<float> *FitT,
                            std::vector<float> *Label,
                            bool etagmode);

    //Noise rate and efficiencies for window optimization
    void SetNoiseRateGraph();
    void GetEfficiencyforWinOpt();
    void SetEfficiencyGraph(int windowstep);

    //Integrated efficiencies as a function of TMVA threshold
    void GetPreEfficiency(int windowstep);
    void GetNNEfficiency(int windowstep);
    void GetOverallEfficiency(int windowstep);
    void GetPurity(int windowstep);

    //
    bool GetTrueMuNCapVtx(int iscnd, CC0PiNumu* numu, Int_t *ichildidx, float *MuNCapVtx);
    int  LabelTrueMuN(CC0PiNumu* numu, bool PrmMuEnd, Int_t *ichildidx);
    bool GetTrueNuNCapVtx(int iscnd, CC0PiNumu* numu, Int_t *iprntidx, Float_t vtxprnt[][3], std::vector<float> *VtxPrntList, std::vector<float> *VtxScndList, float *NuNCapVtx);
    int  LabelTrueNuN(CC0PiNumu* numu, bool PrmMuEnd, Int_t *iprntidx, Float_t vtxprnt[][3], std::vector<float> *VtxPrntList, std::vector<float> *VtxScndList);
    bool GetRecoNeutronCapVtx(UInt_t ican, 
                              float Threshold, 
                              std::vector<float> *NHits,
                              std::vector<float> *FitT, 
                              std::vector<float> *TagOut,
                              std::vector<float> *dvx, 
                              std::vector<float> *dvy, 
                              std::vector<float> *dvz, 
                              float *NCapVtx,
                              bool etagmode);
    int NCapVtxResEstimator(CC0PiNumu* numu, int NTrueN, Float_t *tscnd, Float_t vtxprnt[][3], 
                            bool etagmode, std::vector<float> *FitT, std::vector<float> *NHits, std::vector<float> *Label, std::vector<float> *TagOut, 
                            float TMVAThreshold, std::vector<float> *dvx, std::vector<float> *dvy, std::vector<float> *dvz);
    
    void N1Rmu_x_kinematics(float knmtcs, double* xbins, int* N1Rmu_x_knmtcs, TH1F* h1, int bintype);

    void SetHistoFrame();
    void SetHistoFormat();
    void cdNTagAnalysis(TFile* fout);
    void WritePlots();
};


float GetNoiseRate(int MisTaggedDecaye, int MisTaggedAccNoise, int ParentNeutrinos,
                   int varwindowmax, int windowmin, int noisecut) 
{
  float NoiseRate = ( MisTaggedDecaye + MisTaggedAccNoise*((float)(varwindowmax - WINDOWMIN)/(varwindowmax - NOISECUT)) )/ParentNeutrinos;
  return NoiseRate;
}

