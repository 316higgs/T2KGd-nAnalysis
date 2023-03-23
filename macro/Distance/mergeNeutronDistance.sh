#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'NeutronDistance_prm_x_n.C('${BEAMMODE}')'
#root -l 'NeutronDistance_mu_x_n.C('${BEAMMODE}')'
#root -l 'NeutronSrcLabelDistance.C('${BEAMMODE}')'

#root -l 'TagSubDistance.C('${BEAMMODE}')'
root -l 'TrueLabelDistance.C('${BEAMMODE}')'

#root -l 'NeutronEnergy.C('${BEAMMODE}')'