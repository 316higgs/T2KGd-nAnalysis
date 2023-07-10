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
root -l 'AveTaggedN_x_kinematics.C('${BEAMMODE}')'

##### neutron-related kinematics #####
#root -l 'TaggedN_x_nkinematics.C('${BEAMMODE}')' #### tag-n vs neutron-related kinematics (POT scaling)
#root -l 'TaggedN_x_nkinematics_NormNTagN.C('${BEAMMODE}')' #### tag-n vs neutron-related kinematics (#tag-n normalization)
#root -l 'TrueN_x_nkinematics.C('${BEAMMODE}')'    #### true-n vs neutron-related kinematics