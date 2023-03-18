#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'SubDistance.C('${BEAMMODE}')'
root -l 'fQSubDistance.C('${BEAMMODE}')'
#root -l 'TrueLabelDistance.C('${BEAMMODE}')'

#root -l 'PrmDistance.C('${BEAMMODE}')'