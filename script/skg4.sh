#!/bin/bash

make cleanskg4analysis
make skg4analysis.exe

if [ ! -f ./skg4analysis.exe ]; then
  exit 2
fi

PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
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

  OUTFLUXVER="13a"

  OUTCHANNEL="numu_x_numu"
  OSCCH_ARG="NUMU"
  if [ ${OSCMODE} -eq 0 ]; then
    OUTCHANNEL="numu_x_numu"
    OSCCH_ARG="NUMU"
  elif [ ${OSCMODE} -eq 1 ]; then
    OUTCHANNEL="numu_x_nue"
    OSCCH_ARG="NUESIG"
  elif [ ${OSCMODE} -eq 2 ]; then
    OUTCHANNEL="numubar_x_numubar"
    OSCCH_ARG="NUMUBAR"
  elif [ ${OSCMODE} -eq 3 ]; then
    OUTCHANNEL="numubar_x_nuebar"
    OSCCH_ARG="NUEBARSIG"
  elif [ ${OSCMODE} -eq 4 ]; then
    OUTCHANNEL="nue_x_nue"
    OSCCH_ARG="NUE"
  elif [ ${OSCMODE} -eq 5 ]; then
    OUTCHANNEL="nuebar_x_nuebar"
    OSCCH_ARG="NUEBAR"
  fi

  MC_ARG=Gd
  if [ ${MCMODE} -eq 0 ]; then
    MC_ARG=Water
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


  RUNNAME="skg4MC.bonsaikeras_ToF"

  ESC=$(printf '\033')
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTBEAMMODE  : ${OUTBEAMMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] BEAMMODE_ARG : ${BEAMMODE_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTCHANNEL   : ${OUTCHANNEL}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OSCCH_ARG    : ${OSCCH_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] NTAGMODE     : ${NTAGMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] RUNNAME      : ${RUNNAME}"

#<<COMMENTOUT
  ./skg4analysis.exe ${DISK3}/${FITQUNVER}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                     ${DISK3}/Ntag/output/skg4/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG ON\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
#COMMENTOUT

<<COMMENTOUT
  ./skg4analysis.exe ${DISK3}/${FITQUNVER}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                     ${DISK3}/Ntag/output/${NTAGMODE}/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG ON\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
COMMENTOUT
  echo " " 
}

###  Gd MC  ###
EXECUTE 0 1  ###  numu -> numu
#EXECUTE 1 1  ###  numu -> nue
#EXECUTE 2 1  ###  numubar -> numubar
#EXECUTE 3 1  ###  numubar -> nuebar
#EXECUTE 4 1  ###  nue -> nue
#EXECUTE 5 1  ###  nuebar -> nuebar

