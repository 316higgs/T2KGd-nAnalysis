#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'PrmVtxResolution.C('${BEAMMODE}')'
root -l 'DcyVtxResolution.C('${BEAMMODE}')'