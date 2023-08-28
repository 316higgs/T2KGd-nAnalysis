#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

root -l 'mergeEff.C('${BEAMMODE}')'
#root -l 'mergeNoiseRate.C('${BEAMMODE}')'
#root -l 'mergePurity.C('${BEAMMODE}')'