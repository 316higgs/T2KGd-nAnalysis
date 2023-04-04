#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

##### prompt-related kinematics #####
#root -l 'N1Rmu_x_kinematics.C('${BEAMMODE}')'
#root -l 'TaggedN_x_kinematics.C('${BEAMMODE}')'
#root -l 'NTagEff_x_kinematics.C('${BEAMMODE}')'
#root -l 'AveTaggedN_x_kinematics.C('${BEAMMODE}')'

##### neutron-related kinematics #####
root -l 'TaggedN_x_nkinematics.C('${BEAMMODE}')'