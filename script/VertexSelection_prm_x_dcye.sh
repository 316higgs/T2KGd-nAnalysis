#!/bin/bash

make cleanVertexSelection_prm_x_dcye
make VertexSelection_prm_x_dcye.exe

if [ ! -f ./VertexSelection_prm_x_dcye.exe ]; then
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

#### FHC numu x numu #####
#<<COMMENTOUT
./VertexSelection_prm_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_prm_x_dcye.beforecut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_prm_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_prm_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
#COMMENTOUT


##### FHC numubar -> numubar MC #####
#<<COMMENTOUT
./VertexSelection_prm_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.VertexSelection_prm_x_dcye.beforecut.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_prm_x_dcye.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_prm_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
#COMMENTOUT

###########################################

#### FHC numu x numu #####
<<COMMENTOUT
./VertexSelection_prm_x_dcye.exe $FITQUNDIR/0026Gd.numu/noinpmt/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                     $ANALYSISSTAGE/output/fhc/fhc.numu_x_numu.VertexSelection_prm_x_dcye.aftercut.root\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.neutrino.VertexSelection_prm_x_dcye.txt\
                     $ANALYSISSTAGE/result/fhc/fhc.numu_x_numu.ntag.VertexSelection_prm_x_dcye.txt\
                     -MCType Gd\
                     -ETAG ON\
                     -BEAMMODE FHC\
                     -OSCCH NUMU
COMMENTOUT


##### FHC numubar -> numubar MC #####
<<COMMENTOUT
./VertexSelection_prm_x_dcye.exe $FITQUNDIR/0026Gd.numubar/noinpmt/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   ./output/fhc/fhc.numubar_x_numubar.VertexSelection_prm_x_dcye.aftercut.root\
                   ./result/fhc/fhc.numubar_x_numubar.neutrino.VertexSelection_prm_x_dcye.txt\
                   ./result/fhc/fhc.numubar_x_numubar.ntag.VertexSelection_prm_x_dcye.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE FHC\
                   -OSCCH NUMUBAR
COMMENTOUT
