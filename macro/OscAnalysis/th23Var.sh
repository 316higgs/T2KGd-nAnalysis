#!/bin/bash


###################################################
##  STEP1. Specify beam mode
##         -FHC: true
##         -RHC: false
###################################################
BEAMMODE=true
#BEAMMODE=false

OUTDIR="./output"
#OUTNAME="${OUTDIR}/fhc_0532"
#OUTNAME="${OUTDIR}/fhc_0511"
#OUTNAME="${OUTDIR}/fhc_05"
OUTNAME="${OUTDIR}/fhc_055"

#OUTNAME="${OUTDIR}/rhc_0532"
#OUTNAME="${OUTDIR}/rhc_0511"
#OUTNAME="${OUTDIR}/rhc_05"
#OUTNAME="${OUTDIR}/rhc_055"

root -l -q 'th23Var.C('${BEAMMODE}', "'${OUTNAME}'")'

