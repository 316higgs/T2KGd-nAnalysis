#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'CaptureTime.C('${BEAMMODE}')'
root -l 'Distance.C('${BEAMMODE}')'