#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

OSCMODE="numu_x_numu"
#TYPE="All"
#TYPE="Dcye"
TYPE="Gd"
#TYPE="H"
#TYP="Noise"
OUTPUT="${OSCMODE}.NNcol.${TYPE}.root"
root -l 'CorrelationMatrix.C('${OUTPUT}')'