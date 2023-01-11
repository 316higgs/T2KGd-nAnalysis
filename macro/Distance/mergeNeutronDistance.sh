#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'NeutronDistance_prm_x_n.C('${BEAMMODE}')'

root -l 'NeutronDistance_mu_x_n.C('${BEAMMODE}')'