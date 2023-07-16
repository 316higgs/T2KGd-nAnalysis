#pragma once

// Primary-selection
#define SELECTIONCUTS 6
#define INTERACTIONTYPE 7
#define INTERACTIONTYPE_FOR_MERGE 4
#define DecayeCutPoint 5

// NTag
#define CUTSTEP 21

float TMVATH[CUTSTEP];
float eTMVATH[CUTSTEP];

void InitNTagVariables() {
  for (int i=0; i<CUTSTEP; i++) {
    if (CUTSTEP==11) TMVATH[i] = 0.1*i;
    if (CUTSTEP==21) TMVATH[i] = 0.05*i;
    eTMVATH[i] = 0.;
  }
}


enum class PDGPID
{
  ENU = 12,
  ELECTRON = 11,
  POSITRON = -11,
  MUON = 13,
  ANTIMUON = -13,
  MUNU = 14,
  GAMMA = 22,
  PROTON = 2212,
  NEUTRON = 2112,
  PIPLUS = 211,
  PI0 = 111,
  KPLUS=321,
  DEUTRON=100045
};

enum class GEANTPID 
{
  GAMMA = 1,
  POSITRON = 2,
  ELECTRON = 3,
  NEUTRINO = 4,
  MUPLUS = 5,
  MUMINUS = 6,
  PI0 = 7,
  PIPLUS = 8,
  PIMINUS = 9,
  NEUTRON = 13,
  PROTON = 14
};

// for Iflvc
enum class NEUTINT
{
  INITIAL = -1,
  DETERMINEDLATER = 0,
  DECAY = 1,
  ESCAPE = 2,
  ABSORPTION = 3,
  CHARGEEXCHANGE = 4,
  NOTCONSIDER = 5,
  EMSHOWER = 6,
  HADRONPROD = 7
};

// for lmecscnd, IntID...
enum class GEANTINT
{
  DECAY = 5,
  BREMSS = 9,
  HADRONIC = 12,
  HADRONIC_ELASTIC_COH = 13,
  NEUTRONCAPTURE = 18
};

//SK geometry constant
const float tankR = 16.9; // m
const float tankZ = 18.1; // m

//fiTQun
const int FQ_EHYP = 1;
const int FQ_MUHYP = 2;

const int PrmEvent = 0;

// MeV
const float EMASS  = 0.510998;   // MeV
const float MUMASS = 105.65836;  // MeV
const float NMASS  = 939.565346; // MeV
const float PMASS  = 938.272013; // MeV


