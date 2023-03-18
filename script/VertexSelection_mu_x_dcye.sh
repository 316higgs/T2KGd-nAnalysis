#!/bin/bash

make cleanVertexSelection_mu_x_dcye
make VertexSelection_mu_x_dcye.exe

if [ ! -f ./VertexSelection_mu_x_dcye.exe ]; then
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


###########################################
###########################################

### fiTQun decay-e

#### FHC numu x numu #####
#<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
#COMMENTOUT


##### FHC numubar -> numubar MC #####
#<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
#COMMENTOUT

###########################################
###########################################

### fiTQun decay-e

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/test.numu.dcyecut2.final.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/test.numubar.dcyecut2.final.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT


###########################################
###########################################

### Enu < 1 GeV

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.belowEnucut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.belowEnucut.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

###########################################
###########################################

### Enu > 1 GeV

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.aboveEnucut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.aboveEnucut.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT


###########################################
###########################################

### Pmu < 0.7 GeV

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.belowPmucut.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT

###########################################
###########################################

### Pmu > 0.7 GeV

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_mu_x_dcye.fqdcye.abovePmucut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_mu_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_mu_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_mu_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/fhc/fhc.numubar_x_numubar.VertexSelection_mu_x_dcye.fqdcye.abovePmucut.root\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_mu_x_dcye.txt\
                   $ANALYSISSTAGE/result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_mu_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT
