#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'CapVtxResolution.C('${BEAMMODE}')'
#root -l 'Goodness.C('${BEAMMODE}')'
#root -l 'TotGammaE.C('${BEAMMODE}')'
#root -l 'NeutronMult.C('${BEAMMODE}')'
root -l 'Distance.C('${BEAMMODE}')'
#root -l 'CapTime.C('${BEAMMODE}')'