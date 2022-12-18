#pragma once

#define SELECTIONCUTS 6
#define INTERACTIONTYPE 7
#define INTERACTIONTYPE_FOR_MERGE 4
#define DecayeCutPoint 5


enum class PDGPID
{
  ENU = 11,
  ELECTRON = 11,
  MUON = 13,
  MUNU = 14,
  GAMMA = 22,
  PROTON = 2212,
  NEUTRON = 2112,
  PIPLUS = 211,
  PI0 = 111
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

// for lmecscnd, IntID...
enum class GEANTINT
{
  DECAY = 5,
  HADRONIC = 12,
  HADRONIC_ELASTIC_COH = 13,
  NEUTRONCAPTURE = 18
};