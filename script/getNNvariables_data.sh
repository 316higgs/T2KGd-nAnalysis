#!/bin/bash

make cleangetNNvariables_data
make getNNvariables_data.exe

if [ ! -f ./getNNvariables_data.exe ]; then
  exit 2
fi

FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining
NTAGDIR3=/disk03/usr8/sedi/Ntag/output/w.mccomb/sk6/NNtraining
ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis

DISK3=/disk03/usr8/sedi
FITQUNVER=fiTQun_v4


EXECUTE()
{
  OSCMODE=$1
  MCMODE=$2

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

  #RUNNAME="preNN.run11.FCFVvalid"
  #RUNNAME="postNN.run11.FCFVvalid"
  #RUNNAME="preNN.run11"
  RUNNAME="postNN.run11"

  ESC=$(printf '\033')
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTBEAMMODE  : ${OUTBEAMMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] NTAGMODE     : ${NTAGMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] RUNNAME      : ${RUNNAME}"


#<<COMMENTOUT
  ./getNNvariables_data.exe ${DISK3}/Run11Data/final.run86.fc.apfit.ontiming.21againcorr.fQv4r0c.root\
                            ${DISK3}/Ntag/output/Run11/final.run86.fc.apfit.ontiming.21againcorr.ntag.root\
                            ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${RUNNAME}.${NTAGMODE}.root\
                            ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${RUNNAME}.neutrino.${NTAGMODE}.txt\
                            ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${RUNNAME}.ntag.${NTAGMODE}.txt\
                            -ETAG ON\
                            -BEAMMODE ${BEAMMODE_ARG}\
                            -OSCCH DATA
#COMMENTOUT
  echo " " 
}

EXECUTE 


