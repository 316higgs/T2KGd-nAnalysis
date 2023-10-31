#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

OUTDIR="./output"
#OUTNAME="${OUTDIR}/fhc_0511"
#OUTNAME="${OUTDIR}/fhc_0530"
#OUTNAME="${OUTDIR}/fhc_0561"
#OUTNAME="${OUTDIR}/fhc_0570"

#OUTNAME="${OUTDIR}/fhc_003conc_0511"
#OUTNAME="${OUTDIR}/fhc_003conc_0530"
OUTNAME="${OUTDIR}/fhc_003conc_0561"
#OUTNAME="${OUTDIR}/fhc_003conc_0570"

root -l -q 'th23Var.C('${BEAMMODE}', "'${OUTNAME}'")'

