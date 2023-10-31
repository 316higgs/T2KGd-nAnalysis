#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

#root -l 'TrueMom_GenNbeforeSI.C('${BEAMMODE}')'    ### generated neutron momentum (neutron sources)
#root -l 'TrueMom_CapNbeforeSI.C('${BEAMMODE}')'    ### captured neutron momentum (neutron sources)
#root -l 'TrueMom_CapN.C('${BEAMMODE}')'    ### captured neutron momentum (neutron sources)
#root -l 'TrueEkin_CapN.C('${BEAMMODE}')'    ### captured neutron momentum (neutron sources)
root -l 'TrueMom_CapN_systSI.C('${BEAMMODE}')'    ### captured neutron momentum (neutron sources)