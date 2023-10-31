#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l -q 'SelectedEvents.C('${BEAMMODE}')'

root -l -q 'CaptureTime.C('${BEAMMODE}')'

#root -l -q 'Distance.C('${BEAMMODE}')'

#root -l -q 'NeutronMult.C('${BEAMMODE}')'