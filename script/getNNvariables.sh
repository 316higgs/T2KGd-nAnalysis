#!/bin/bash

make cleangetNNvariables
make getNNvariables.exe

if [ ! -f ./getNNvariables.exe ]; then
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

  #RUNNAME="preNN.newGdMC"
  RUNNAME="postNN.newGdMC"

  ESC=$(printf '\033')
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTBEAMMODE  : ${OUTBEAMMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] BEAMMODE_ARG : ${BEAMMODE_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OUTCHANNEL   : ${OUTCHANNEL}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] OSCCH_ARG    : ${OSCCH_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] MC_ARG       : ${MC_ARG}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] NTAGMODE     : ${NTAGMODE}"
  printf "${ESC}[31m%s${ESC}[m\n" "[### Analysis Option ###] RUNNAME      : ${RUNNAME}"


#<<COMMENTOUT
  ./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/${OUTBEAMMODE}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.fiTQun0026Gd.0\*.root\
                       ${DISK3}/Ntag/output/${NTAGMODE}/${OUTBEAMMODE}/${OUTCHANNEL}/${OUTBEAMMODE}.${OUTCHANNEL}.${OUTFLUXVER}.ntag0026Gd.\*.root\
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

###  Gd MC  ###
EXECUTE 0 1  ###  numu -> numu
EXECUTE 1 1  ###  numu -> nue
EXECUTE 2 1  ###  numubar -> numubar
EXECUTE 3 1  ###  numubar -> nuebar
EXECUTE 4 1  ###  nue -> nue
EXECUTE 5 1  ###  nuebar -> nuebar




<<COMMENTOUT
#### Pre NN #####
./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.oldntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.newGdMC.oldntag.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.newGdMC.oldntag.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.newGdMC.oldntag.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT



##### FHC numu -> numu Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

##### FHC numu -> nue Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_nue/fhc.numu_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_nue.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUESIG
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_nue/fhc.numu_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_nue.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUESIG
COMMENTOUT


##### FHC numubar -> numubar Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMUBAR
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMUBAR
COMMENTOUT


##### FHC numubar -> nuebar Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_nuebar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBARSIG
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_nuebar.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBARSIG
COMMENTOUT

##### FHC nue -> nue Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nue_x_nue/fhc.nue_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nue_x_nue.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUE
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nue_x_nue/fhc.nue_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nue_x_nue.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUE
COMMENTOUT

##### FHC nuebar -> nuebar Gd MC #####
<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBAR
COMMENTOUT

<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nuebar_x_nuebar.postNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.neutrino.postNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.ntag.postNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBAR
COMMENTOUT




#### neutron classification(mu- vs nu) #####
<<COMMENTOUT
./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip0.root\
                     $NTAGDIR3/tageoption/noinpmt/numu/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip0.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.ndistance.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.ndistance.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.ndistance.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

#### Post NN #####
#./getNNvariables.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.postNN.root\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.postNN.txt\
#                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.postNN.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMU


################################################


#### Pre NN #####
#./getNNvariables.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     ./output/fhc/fhc.numubar_x_numubar.preNN.muminus.root\
#                     ./result/fhc/fhc.numubar_x_numubar.neutrino.preNN.muminus.txt\
#                     ./result/fhc/fhc.numubar_x_numubar.ntag.preNN.muminus.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMUBAR

#### Post NN #####
#./getNNvariables.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                     ./output/fhc/fhc.numubar_x_numubar.postNN.root\
#                     ./result/fhc/fhc.numubar_x_numubar.neutrino.postNN.txt\
#                     ./result/fhc/fhc.numubar_x_numubar.ntag.postNN.txt\
#                     -MCType Gd\
#                     -ETAG ON\
#                     -BEAMMODE FHC\
#                     -OSCCH NUMUBAR

