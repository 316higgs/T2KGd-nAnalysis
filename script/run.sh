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
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/noToFoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   ./output/fhc/fhc.numu.etagOFF.root\
#                   ./result/fhc/fhc.numu.neutrino.etagOFF.txt\
#                   ./result/fhc/fhc.numu.ntag.etagOFF.txt\
#                   -MCType Gd\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

#<<COMMENTOUT
#./analysis1Rmu.exe $PUREWATER/fhc/numu_x_numu/neut.fhc.numu_x_numu.00\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/numu_x_numu.water.root\
#                   $ANALYSISSTAGE/result/fhc/numu_x_numu.water.txt\
#                   $ANALYSISSTAGE/result/fhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

#./analysis1Rmu.exe $PUREWATER/fhc/numu_x_nue/neut.fhc.numu_x_nue.01\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/numu_x_nue.water.root\
#                   $ANALYSISSTAGE/result/fhc/numu_x_nue.water.txt\
#                   $ANALYSISSTAGE/result/fhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUESIG

#./analysis1Rmu.exe $PUREWATER/fhc/numubar_x_numubar/neut.fhc.numubar_x_numubar.02\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.water.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.water.txt\
#                   $ANALYSISSTAGE/result/fhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMUBAR

#./analysis1Rmu.exe $PUREWATER/rhc/numubar_x_numubar/neut.rhc.numubar_x_numubar.0\*.0\*.t2kfcFQ.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.water.root\
#                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.water.txt\
#                   $ANALYSISSTAGE/result/rhc/null.txt\
#                   -MCType Water\
#                   -ETAG OFF\
#                   -BEAMMODE RHC\
#                   -OSCCH NUMUBAR



##### FHC numu -> numu Gd MC #####
#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/fhc.numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/fhc.numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU

#./analysis1Rmu.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
#                   $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.etagON.noinpmt.root\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.etagON.noinpmt.txt\
#                   $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.etagON.noinpmt.txt\
#                   -MCType Gd\
#                   -ETAG ON\
#                   -BEAMMODE FHC\
#                   -OSCCH NUMU


#<<COMMENTOUT
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
#COMMENTOUT

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


