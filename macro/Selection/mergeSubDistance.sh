#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

root -l 'SubDistance.C('${BEAMMODE}')'

#root -l 'PrmDistance.C('${BEAMMODE}')'