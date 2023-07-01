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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
#COMMENTOUT

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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numu_x_nue/fhc.numu_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_nue.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_nue.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUESIG
#COMMENTOUT

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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_numubar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_numubar/fhc.numubar_x_numubar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMUBAR
#COMMENTOUT

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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numubar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/numubar_x_nuebar/fhc.numubar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numubar_x_nuebar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numubar_x_nuebar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBARSIG
#COMMENTOUT

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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nue_x_nue.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nue_x_nue/fhc.nue_x_nue.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nue_x_nue.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nue_x_nue.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUE
#COMMENTOUT

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
#<<COMMENTOUT
./getNNvariables.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.nuebar_x_nuebar.13a.fiTQun0026Gd.\*.root\
                     ${DISK3}/Ntag/output/fhc/nuebar_x_nuebar/fhc.nuebar_x_nuebar.13a.NNoptntag0026Gd.\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.nuebar_x_nuebar.preNN.newGdMC.root\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.neutrino.preNN.newGdMC.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.nuebar_x_nuebar.ntag.preNN.newGdMC.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUEBAR
#COMMENTOUT

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

