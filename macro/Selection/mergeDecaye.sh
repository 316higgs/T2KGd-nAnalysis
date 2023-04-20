#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'SimpleDecaye.C('${BEAMMODE}')'
#root -l 'CompareDecaye.C('${BEAMMODE}')'
root -l 'dtn50.C('${BEAMMODE}')'


#root -l 'CCPiDecaye.C('${BEAMMODE}')'

#root -l 'VtxCutDecaye.C('${BEAMMODE}')'