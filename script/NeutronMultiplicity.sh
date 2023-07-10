#!/bin/bash

make cleanNeutronMultiplicity
make NeutronMultiplicity.exe

if [ ! -f ./NeutronMultiplicity.exe ]; then
  exit 2
fi

PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining
NTAGDIR3=/disk03/usr8/sedi/Ntag/output/w.mccomb/sk6/NNtraining
ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis

DISK3=/disk03/usr8/sedi
FITQUNVER=fiTQun_v4

######
# 1st index: fiTQun input
# 2nd index: NTag input
# 3rd index: ROOT output 
# 4th index: Result summary .txt output
# 5th index: -MCType(fixed)
# 6th index: Gd/Water
# 7th index: -ETAG(fixed)
# 8th index: decay-e-tagging ON/OFF

##### FHC numu -> numu Gd MC #####
#<<COMMENTOUT
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_numu.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_numu.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUMU
#COMMENTOUT

####################################################################
##### FHC numu -> nue Gd MC #####
#<<COMMENTOUT
#####  new Gd MC  ######
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/numu_x_nue/fhc.numu_x_nue.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.numu_x_nue.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numu_x_nue.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUESIG
#COMMENTOUT

####################################################################
##### FHC numubar -> numubar Gd MC #####
#<<COMMENTOUT
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_numubar.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_numubar.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUMUBAR
#COMMENTOUT

####################################################################
##### FHC numubar -> nuebar Gd MC #####
#<<COMMENTOUT
#####  new Gd MC  ######
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.numubar_x_nuebar.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.numubar_x_nuebar.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUEBARSIG
#COMMENTOUT

####################################################################
##### FHC nue -> nue Gd MC #####
#<<COMMENTOUT
#####  new Gd MC  ######
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/nue_x_nue/fhc.nue_x_nue.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.nue_x_nue.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.nue_x_nue.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUE
#COMMENTOUT

####################################################################
##### FHC nubaer -> nuebar Gd MC #####
#<<COMMENTOUT
#####  new Gd MC  ######
./NeutronMultiplicity.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                          ${DISK3}/Ntag/output/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                          ${ANALYSISSTAGE}/output/fhc/fhc.nuebar_x_nuebar.NNoptnewGdMC.Nmult.root\
                          ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.NNoptneutrino.newGdMC.Nmult.txt\
                          ${ANALYSISSTAGE}/result/fhc/fhc.nuebar_x_nuebar.NNoptntag.newGdMC.Nmult.txt\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUEBAR
#COMMENTOUT





