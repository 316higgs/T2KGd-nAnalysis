#!/bin/bash

make cleananalysis1Rmu
make 

if [ ! -f ./analysis1Rmu.exe ]; then
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

  SIVARMODE=0
  SIVAR=m30
  if [ ${SIVARMODE} -eq 1 ]; then
    SIVAR=p30
  fi

  #RUNNAME="water"
  #RUNNAME="NNoptnewGdMC"
  #RUNNAME="newGdMC.promptkeras"
  #RUNNAME="newGdMC.bonsaikeras"
  #RUNNAME="newGdMC.bonsaikeras_ToF"
  #RUNNAME="newGdMC.bonsaikeras_ToF_0511"
  #RUNNAME="newGdMC.bonsaikeras_ToF_0530"
  #RUNNAME="newGdMC.bonsaikeras_ToF_0570"
  #RUNNAME="systSI${SIVAR}.bonsaikeras_ToF"
  RUNNAME="ggarnet.bonsaikeras_ToF"


  ESC=$(printf '\033')
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTBEAMMODE  : ${OUTBEAMMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] BEAMMODE_ARG : ${BEAMMODE_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTCHANNEL   : ${OUTCHANNEL}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OSCCH_ARG    : ${OSCCH_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] MC_ARG       : ${MC_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] NTAGMODE     : ${NTAGMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] RUNNAME      : ${RUNNAME}"

<<COMMENTOUT
  FILENUM=0
  if [ ${OSCMODE} -eq 0 ]; then
    FILENUM=0
  elif [ ${OSCMODE} -eq 1 ]; then
    FILENUM=1
  elif [ ${OSCMODE} -eq 2 ]; then
    FILENUM=2
  elif [ ${OSCMODE} -eq 3 ]; then
    FILENUM=4
  elif [ ${OSCMODE} -eq 4 ]; then
    FILENUM=1
  elif [ ${OSCMODE} -eq 5 ]; then
    FILENUM=4
  fi
  ./analysis1Rmu.exe ${PUREWATER}/${OUTBEAMMODE}/${OUTCHANNEL}/neut.${OUTBEAMMODE}.${OUTCHANNEL}.0${FILENUM}\*.0\*.t2kfcFQ.root\
                     ${DISK3}/Ntag/output/${NTAGMODE}/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG OFF\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
COMMENTOUT


<<COMMENTOUT
  ./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                     ${DISK3}/Ntag/output/${NTAGMODE}/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG ON\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
COMMENTOUT

#### SI ####
<<COMMENTOUT
  ./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/systSI/${SIVAR}/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                     ${DISK3}/Ntag/output/systSI/${SIVAR}/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.0\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG ON\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
COMMENTOUT

#### GGARNET ####
#<<COMMENTOUT
  ./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/ggarnet/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                     ${DISK3}/Ntag/output/ggarnet/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
                     ${ANALYSISSTAGE}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${RUNNAME}.root\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.neutrino.${RUNNAME}.txt\
                     ${ANALYSISSTAGE}/result/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.ntag.${RUNNAME}.txt\
                     -MCType ${MC_ARG}\
                     -ETAG ON\
                     -BEAMMODE ${BEAMMODE_ARG}\
                     -OSCCH ${OSCCH_ARG}
#COMMENTOUT
  echo " " 
}

###  pure water MC  ###
#EXECUTE 0 0  ###  numu -> numu
#EXECUTE 1 0  ###  numu -> nue  
#EXECUTE 2 0  ###  numubar -> numubar
#EXECUTE 3 0  ###  numubar -> nuebar
#EXECUTE 4 0  ###  nue -> nue
#EXECUTE 5 0  ###  nuebar -> nuebar

###  Gd MC  ###
EXECUTE 0 1  ###  numu -> numu
EXECUTE 1 1  ###  numu -> nue
EXECUTE 2 1  ###  numubar -> numubar
EXECUTE 3 1  ###  numubar -> nuebar
EXECUTE 4 1  ###  nue -> nue
EXECUTE 5 1  ###  nuebar -> nuebar



<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numu_x_numu/neut.fhc.numu_x_numu.00\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/numu_x_numu.water.root\
                   $ANALYSISSTAGE/result/fhc/numu_x_numu.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numu_x_nue/neut.fhc.numu_x_nue.01\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/numu_x_nue.water.root\
                   $ANALYSISSTAGE/result/fhc/numu_x_nue.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUESIG
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numubar_x_numubar/neut.fhc.numubar_x_numubar.02\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.water.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numubar_x_numubar/neut.fhc.numubar_x_nuebar.04\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_nuebar.water.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUEBARSIG
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numu_x_nue/neut.fhc.nue_x_nue.01\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/nue_x_nue.water.root\
                   $ANALYSISSTAGE/result/fhc/nue_x_nue.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUE
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe ${PUREWATER}/fhc/numubar_x_numubar/neut.fhc.nuebar_x_nuebar.04\*.0\*.t2kfcFQ.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.nuebar_x_nuebar.water.root\
                   $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.water.txt\
                   $ANALYSISSTAGE/result/fhc/null.txt\
                   -MCType Water\
                   -ETAG OFF\
                   -BEAMMODE FHC\
                   -OSCCH NUEBAR
COMMENTOUT




####################################################################
##### FHC numu -> numu Gd MC #####
<<COMMENTOUT
#####  new Gd MC (NN optimized)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (Nominal)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT


<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.bonsaikeras_ToF.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.bonsaikeras_ToF.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.bonsaikeras_ToF.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (prompt Keras, ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/prompt_keras/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.promptkeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.promptkeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.promptkeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC, old NTag  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.oldntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.oldntag.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.oldntag.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.oldntag.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC w/ ToF-subtraction  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/wToF/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.newGdMC.wToF.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.neutrino.newGdMC.wToF.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.ntag.newGdMC.wToF.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
#####  old Gd MC  ######
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

####################################################################
##### FHC numu -> nue Gd MC #####
<<COMMENTOUT
#####  new Gd MC  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numu_x_nue/fhc.numu_x_nue.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_nue.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUESIG
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numu_x_nue/fhc.numu_x_nue.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_nue.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUESIG
COMMENTOUT


####################################################################
##### FHC numubar -> numubar Gd MC #####
<<COMMENTOUT
#####  new Gd MC  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_numubar.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
#####  old Gd MC  ######
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.etagON.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.etagON.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

####################################################################
##### FHC numubar -> nuebar Gd MC #####
<<COMMENTOUT
#####  new Gd MC  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUEBARSIG
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_nuebar.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUEBARSIG
COMMENTOUT


#####  old Gd MC  ######
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.noinpmt.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.noinpmt.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.noinpmt.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

####################################################################
##### FHC nue -> nue Gd MC #####
<<COMMENTOUT
#####  new Gd MC  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/nue_x_nue/fhc.nue_x_nue.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.nue_x_nue.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUE
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/nue_x_nue/fhc.nue_x_nue.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.nue_x_nue.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUE
COMMENTOUT

####################################################################
##### FHC nubaer -> nuebar Gd MC #####
<<COMMENTOUT
#####  new Gd MC  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.NNoptneutrino.newGdMC.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.NNoptntag.newGdMC.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUEBAR
COMMENTOUT

<<COMMENTOUT
#####  new Gd MC (BONSAI Keras, No ToF-subtraction @ pre-selection)  ######
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/bonsai_keras_no_prompt_vertex/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.ntag0026Gd.\*.root\
                   ${ANALYSISSTAGE}/output/fhc/fhc.nuebar_x_nuebar.newGdMC.bonsaikeras.root\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.neutrino.newGdMC.bonsaikeras.txt\
                   ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.ntag.newGdMC.bonsaikeras.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUEBAR
COMMENTOUT




<<COMMENTOUT
  #### with muon angle ####
  #### costheta23 = 0.532 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.cut1.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.cut1.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
  #### with muon angle ####
  #### costheta23 = 0.511 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.cut1.maximalmix.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.cut1.maximalmix.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.cut1.maximalmix.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
  #### with muon angle ####
  #### costheta23 = 0.5 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.cut1.0.5.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.cut1.0.5.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.cut1.0.5.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
  #### with muon angle ####
  #### costheta23 = 0.55 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.cut1.0.55.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.cut1.0.55.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.cut1.0.55.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/test.root\
                   $ANALYSISSTAGE/result/fhc/test.neutrino.txt\
                   $ANALYSISSTAGE/result/fhc/test.ntag.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.CCpi.cut1.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.CCpi.cut1.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.CCpi.cut1.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

###------------------------------------------------

<<COMMENTOUT
##### FHC numubar -> numubar MC #####
#### costheta23 = 0.5 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.etagON.0.5.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.0.5.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.0.5.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### FHC numubar -> numubar MC #####
#### costheta23 = 0.511 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.etagON.maximalmix.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.maximalmix.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.maximalmix.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### FHC numubar -> numubar MC #####
#### costheta23 = 0.532 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.etagON.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### FHC numubar -> numubar MC #####
#### costheta23 = 0.55 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.etagON.0.55.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.etagON.0.55.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.etagON.0.55.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT


<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.nuesig/numu_x_nue.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR3/tageoption/noinpmt/nuesig/numu_x_nue.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_nue.etagON.cut1.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.neutrino.etagON.cut1.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.ntag.etagON.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUESIG
COMMENTOUT



##### RHC ------------------------------------------------------------------------- #####
<<COMMENTOUT
##### RHC numu -> numu MC #####
  #### with muon angle ####
  #### costheta23 = 0.5 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.etagON.cut1.0.5.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.etagON.cut1.0.5.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.etagON.cut1.0.5.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
##### RHC numu -> numu MC #####
  #### with muon angle ####
  #### costheta23 = 0.511 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.etagON.cut1.maximalmix.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.etagON.cut1.maximalmix.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.etagON.cut1.maximalmix.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
##### RHC numu -> numu MC #####
#### costheta23 = 0.532 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.etagON.cut1.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.etagON.cut1.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.etagON.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
##### RHC numu -> numu MC #####
  #### with muon angle ####
  #### costheta23 = 0.55 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.etagON.cut1.0.55.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.etagON.cut1.0.55.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.etagON.cut1.0.55.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU
COMMENTOUT

###------------------------------------------------

<<COMMENTOUT
##### RHC numubar -> numubar MC #####
#### costheta23 = 0.5 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/rhc/rhc.numubar_x_numubar.etagON.0.5.root\
                   ./result/rhc/rhc.numubar_x_numubar.neutrino.etagON.0.5.txt\
                   ./result/rhc/rhc.numubar_x_numubar.ntag.etagON.0.5.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### RHC numubar -> numubar MC #####
#### costheta23 = 0.511 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/rhc/rhc.numubar_x_numubar.etagON.maximalmix.root\
                   ./result/rhc/rhc.numubar_x_numubar.neutrino.etagON.maximalmix.txt\
                   ./result/rhc/rhc.numubar_x_numubar.ntag.etagON.maximalmix.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### RHC numubar -> numubar MC #####
#### costheta23 = 0.532 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.etagON.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.neutrino.etagON.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.ntag.etagON.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
##### RHC numubar -> numubar MC #####
#### costheta23 = 0.55 ####
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/rhc/rhc.numubar_x_numubar.etagON.0.55.root\
                   ./result/rhc/rhc.numubar_x_numubar.neutrino.etagON.0.55.txt\
                   ./result/rhc/rhc.numubar_x_numubar.ntag.etagON.0.55.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR
COMMENTOUT

###------------------------------------------------


