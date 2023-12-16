#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'SelectedEvents.C('${BEAMMODE}')'
root -l 'SelectionVar.C('${BEAMMODE}')'
#root -l 'Evis.C('${BEAMMODE}')'

#root -l 'CompareSelEff.C('${BEAMMODE}')'