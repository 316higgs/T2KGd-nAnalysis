#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'TrueDistance.C('${BEAMMODE}')'        ### neutron travel distance (neutrino interaction type)
#root -l 'TrueDistance_nsrc.C('${BEAMMODE}')'    ### neutron travel distance (neutron sources)
#root -l 'TrueMom_nsrc.C('${BEAMMODE}')'    ### neutron momentum (neutron sources)

#root -l 'NeutronDistance_prm_x_n.C('${BEAMMODE}')'
#root -l 'NeutronDistance_mu_x_n.C('${BEAMMODE}')'
#root -l 'NeutronSrcLabelDistance.C('${BEAMMODE}')'

#root -l 'TagSubDistance.C('${BEAMMODE}')'
#root -l 'TrueLabelDistance.C('${BEAMMODE}')'

#root -l 'NeutronEnergy.C('${BEAMMODE}')'


root -l 'mergeTagEff_x_dist.C('${BEAMMODE}')'


#root -l 'systSIDistance.C('${BEAMMODE}')'