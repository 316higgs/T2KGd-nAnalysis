#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

root -l 'SimpleNeutron.C('${BEAMMODE}')'
#root -l 'GenNeutron.C('${BEAMMODE}')'