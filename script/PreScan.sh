#!/bin/bash

make cleananalysis1Rmu
make 
make cleanPreScan
make PreScan.exe

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

##### FHC numu -> numu Gd MC #####
####### Pre-eff best point ########
<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part001.skip0.root\
                   $NTAGDIR3/tageoption/noinpmt/numu/PreScan/NHITSTH10_TWIDTH280/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part001.skip0.root\
                   $ANALYSISSTAGE/output/test.NHITSTH10_TWIDTH280.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH10_TWIDTH280.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH10_TWIDTH280.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT


########## TWIDTH scan ############
#<<COMMENTOUT
./analysis1Rmu.exe ${DISK3}/${FITQUNVER}/output/fhc/fhc.numu_x_numu.13a.fiTQun0026Gd.\*.root\
                   ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.TWIDTH160.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.TWIDTH160.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
#COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH120.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH120.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH120.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH160.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH160.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH160.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH240.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH240.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH240.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH280.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH280.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH280.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT


########## NHITSTH scan ############
<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH10.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH10_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH10_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH15.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH15_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH15_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH25.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH25_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH35.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH35_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH35_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT

<<COMMENTOUT
./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF.TWIDTH200.NHITSTH45.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.test.NHITSTH45_TWIDTH200.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH45_TWIDTH200.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMU
COMMENTOUT



########## TWIDTH scan ############
<<COMMENTOUT
#TWIDTH=120, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 120\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=160, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 160\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/tageoption//fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=240, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 240\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=280, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/TWIDTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/TWIDTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 280\
              -NHITSTH 25\
              -WINDOW 0
echo " "


########## NHITSTH scan ############
#TWIDTH=200, NHITSTH=10
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan0/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 10\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=15
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan1/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 15\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=25
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/tageoption//fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 25\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=35
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan2/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 35\
              -WINDOW 0
echo " "
#TWIDTH=200, NHITSTH=45
./PreScan.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              $NTAGDIR/PreScan/NHITSTHScan/EtagON/Scan3/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
              ./output/NHITSTHScan/fhc.numu_x_numu.0026Gd.noToF\
              ./result/fhc.numu_x_numu.0026Gd.noToF\
              -MCType Gd\
              -ETAG ON\
              -TWIDTH 200\
              -NHITSTH 45\
              -WINDOW 0
echo " "
COMMENTOUT

