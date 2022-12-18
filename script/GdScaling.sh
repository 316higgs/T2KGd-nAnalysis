#!/bin/bash

make cleanGdScaling
make GdScaling.exe

if [ ! -f ./GdScaling.exe ]; then
  exit 2
fi

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

####### sin^2 theta23 = 0.532 #########
#### FHC numu x numu #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.003conc.0532.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.003conc.0532.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.003conc.0532.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.003conc.0532.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.003conc.0532.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.003conc.0532.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

###########################################

####### sin^2 theta23 = 0.5 #########
#### FHC numu x numu #####
#<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.003conc.05.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.003conc.05.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.003conc.05.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
#COMMENTOUT

##### FHC numubar -> numubar MC #####
#<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.003conc.05.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.003conc.05.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.003conc.05.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
#COMMENTOUT

###########################################

####### sin^2 theta23 = 0.511 #########
#### FHC numu x numu #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.003conc.0511.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.003conc.0511.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.003conc.0511.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.003conc.0511.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.003conc.0511.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.003conc.0511.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

###########################################

####### sin^2 theta23 = 0.55 #########
#### FHC numu x numu #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.003conc.055.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.003conc.055.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.003conc.055.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT

##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./GdScaling.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.003conc.055.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.003conc.055.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.003conc.055.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

