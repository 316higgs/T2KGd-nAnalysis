#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'mergeNNinput.C('${BEAMMODE}')'
root -l 'mergeNNinputshape.C('${BEAMMODE}')'
#root -l 'NTagOut.C('${BEAMMODE}')'