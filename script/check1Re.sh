#!/bin/bash

make cleananalysis1Re
make analysis1Re.exe

if [ ! -f ./analysis1Re.exe ]; then
  echo "[### analysis1Re ###]  No exexutable file."
  exit 2
fi

PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining
NTAGDIR3=/disk03/usr8/sedi/Ntag/output/w.mccomb/sk6/NNtraining
ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis

######
# 1st index: fiTQun input
# 2nd index: NTag input
# 3rd index: ROOT output 
# 4th index: Result summary .txt output
# 5th index: -MCType(fixed)
# 6th index: Gd/Water
# 7th index: -ETAG(fixed)
# 8th index: decay-e-tagging ON/OFF
######

./analysis1Re.exe $FITQUNDIR/0026Gd.nuesig/numu_x_nue.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR3/tageoption/noinpmt/numu_x_nue.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_nue.1ReSelection.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.neutrino.1ReSelection.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.ntag.1ReSelection.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUE
#COMMENTOUT