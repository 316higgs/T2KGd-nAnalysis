#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

root -l 'mergeNNinput.C('${BEAMMODE}')'        ### stack
#root -l 'mergeNNinputshape.C('${BEAMMODE}')'   ### shape comparison
#root -l 'NTagOut.C('${BEAMMODE}')'