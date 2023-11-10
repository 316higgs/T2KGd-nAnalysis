#!/bin/bash

make cleananalysis1Rmu_data
make analysis1Rmu_data.exe

if [ ! -f ./analysis1Rmu_data.exe ]; then
  exit 2
fi


ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis
DISK3=/disk03/usr8/sedi


EXECUTE()
{
  OUTBEAMMODE="fhc"
  BEAMMODE_ARG="RHC"
  if [[ "${OUTBEAMMODE}" == "fhc" ]]; then
    BEAMMODE_ARG=FHC
  fi

  ###  NTag setting  ###
  #PRESELMODE="no_prompt_vertex"
  PRESELMODE="prompt_vertex"

  #NNMODEL="tmva"
  NNMODEL="keras"
  
  DLYVTXTYPE="bonsai"
  #DLYVTXTYPE="prompt"

  NNSTYLE="${DLYVTXTYPE}_${NNMODEL}"
  NTAGMODE=${NNSTYLE}_${PRESELMODE}
  if [[ "${NNSTYLE}" == "prompt_keras" ]]; then
    NTAGMODE=${NNSTYLE}
  fi

  RUNNAME="run11"

  ESC=$(printf '\033')
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] NTAGMODE     : ${NTAGMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] RUNNAME      : ${RUNNAME}"


#<<COMMENTOUT
  ./analysis1Rmu_data.exe ${DISK3}/Run11Data/final.run86.fc.apfit.ontiming.21againcorr.fQv4r0c.root\
                          ${DISK3}/Ntag/output/Run11/final.run86.fc.apfit.ontiming.21againcorr.ntag.root\
                          ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/run11.${NTAGMODE}.root\
                          ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/run11.neutrino.${NTAGMODE}.txt\
                          ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/run11.ntag.${NTAGMODE}.txt\
                          -ETAG ON\
                          -BEAMMODE ${BEAMMODE_ARG}\
                          -OSCCH DATA
#COMMENTOUT
  echo " " 
}

EXECUTE 



