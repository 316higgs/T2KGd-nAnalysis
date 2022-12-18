#!/bin/bash

make cleancreateOAinputs
make createOAinputs.exe

if [ ! -f ./createOAinputs.exe ]; then
  exit 2
fi


PUREWATER=/home/rakutsu/disk2/t2k/regene_mc/files/fcfq_fqmr_root
#FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output
#FITQUNDIR=/disk02/usr6/sedi/fiTQun/converted_output/DeltaPforEmiss0Added
FITQUNDIR=/disk03/usr8/sedi/fiTQun/converted_output/DeltaPforEmiss0Added
NTAGDIR=/disk02/usr6/sedi/Ntag/output/w.mccomb/sk6/NNtraining
NTAGDIR3=/disk03/usr8/sedi/Ntag/output/w.mccomb/sk6/NNtraining
ANALYSISSTAGE=/home/sedi/neutrontag/t2ksk-neutronh/SKGd_MC/analysis/T2KGdAnalysis
DISK3=/disk03/usr8/sedi/OA2021/outputsample/rhc

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

##### No NTag #####

<<COMMENTOUT
echo " "
echo "numu_x_numu No NTag info"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.OAinput.cut1.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.OAinput.cut1.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.OAinput.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU\
                   -SAMPLE YES\
                   $DISK3/rhc.numu_x_numu.OAinput\
                   -NTAGINFO NO
COMMENTOUT

<<COMMENTOUT
echo " "
echo "numubar_x_numubar No NTag info"
./createOAinputs.exe $FITQUNDIR/0026Gd.numubar/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.OAinput.cut1.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.neutrino.OAinput.cut1.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.ntag.OAinput.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR\
                   -SAMPLE YES\
                   $DISK3/rhc.numubar_x_numubar.OAinput\
                   -NTAGINFO NO
COMMENTOUT

############################


##### NTag separation #####

#<<COMMENTOUT
echo " "
echo "numu_x_numu"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numu_x_numu.OAinput.cut1.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.neutrino.OAinput.cut1.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numu_x_numu.ntag.OAinput.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMU\
                   -SAMPLE YES\
                   $DISK3/rhc.numu_x_numu.OAinput\
                   -NTAGINFO YES
#COMMENTOUT

#<<COMMENTOUT
echo " "
echo "numubar_x_numubar"
./createOAinputs.exe $FITQUNDIR/0026Gd.numubar/numubar_x_numubar.fiTQun.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $NTAGDIR/tageoption/noinpmt/numubar_x_numubar.ntag.0026Gd.NEUTcount0\*.part00\*.skip\*.root\
                   $ANALYSISSTAGE/output/rhc/rhc.numubar_x_numubar.OAinput.cut1.root\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.neutrino.OAinput.cut1.txt\
                   $ANALYSISSTAGE/result/rhc/rhc.numubar_x_numubar.ntag.OAinput.cut1.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUMUBAR\
                   -SAMPLE YES\
                   $DISK3/rhc.numubar_x_numubar.OAinput\
                   -NTAGINFO YES
#COMMENTOUT

#<<COMMENTOUT
echo " "
echo "numu_x_nue"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
                   $ANALYSISSTAGE/output/rhc/test.root\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUESIG\
                   -SAMPLE NO\
                   $DISK3/rhc.numu_x_nue.OAinput\
                   -NTAGINFO YES

echo " "
echo "numubar_x_nuebar"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
                   $ANALYSISSTAGE/output/rhc/test.root\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUEBARSIG\
                   -SAMPLE NO\
                   $DISK3/rhc.numubar_x_nuebar.OAinput\
                   -NTAGINFO YES

echo " "
echo "nue_x_nue"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
                   $ANALYSISSTAGE/output/rhc/test.root\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUE\
                   -SAMPLE NO\
                   $DISK3/rhc.nue_x_nue.OAinput\
                   -NTAGINFO YES

echo " "
echo "nuebar_x_nuebar"
./createOAinputs.exe $FITQUNDIR/0026Gd.numu/numu_x_numu.fiTQun.0026Gd.NEUTcount000.part001.skip0.root\
                   $NTAGDIR/tageoption/noinpmt/numu_x_numu.ntag.0026Gd.NEUTcount000.part001.skip0.root\
                   $ANALYSISSTAGE/output/rhc/test.root\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   $ANALYSISSTAGE/result/rhc/test.txt\
                   -MCType Gd\
                   -ETAG ON\
                   -BEAMMODE RHC\
                   -OSCCH NUEBAR\
                   -SAMPLE NO\
                   $DISK3/rhc.nuebar_x_nuebar.OAinput\
                   -NTAGINFO YES
#COMMENTOUT
