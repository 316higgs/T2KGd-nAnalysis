#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'SelVal.C('${BEAMMODE}')'
root -l 'SelectionVar.C('${BEAMMODE}')'
#root -l 'Evis.C('${BEAMMODE}')'