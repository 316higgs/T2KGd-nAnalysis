#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'SelectedEvents.C('${BEAMMODE}')'
root -l 'mergeDcyePerform.C('${BEAMMODE}')'