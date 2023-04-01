#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'N1Rmu_x_kinematics.C('${BEAMMODE}')'
root -l 'TaggedN_x_kinematics.C('${BEAMMODE}')'