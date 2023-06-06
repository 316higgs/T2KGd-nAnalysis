#!/bin/bash

GetPreEff() 
{
	FILE=$1
	#grep -r '\[   Pre    \]' ${FILE}
	grep -r 'PreEff' ${FILE}
	grep -r 'PreHEff' ${FILE}
    grep -r 'PreGdEff' ${FILE}
}

<<COMMENTOUT
echo "##### TWIDTH=120, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH120.txt
echo " "
echo "##### TWIDTH=160, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH160.txt
echo " "
echo "##### TWIDTH=200, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH200.txt
echo " "
echo "##### TWIDTH=240, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH240.txt
echo " "
echo "##### TWIDTH=280, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.test.NHITSTH25_TWIDTH280.txt
COMMENTOUT

#<<COMMENTOUT
echo "##### TWIDTH=200, NHITSTH=15 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.NHITSTH15.txt
echo " "
echo "##### TWIDTH=200, NHITSTH=20 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.NHITSTH20.txt
echo " "
echo "##### TWIDTH=200, NHITSTH=25 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.newGdMC.txt
echo " "
echo "##### TWIDTH=200, NHITSTH=30 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.NHITSTH30.txt
echo " "
echo "##### TWIDTH=200, NHITSTH=35 ######"
GetPreEff ../../result/fhc/fhc.numu_x_numu.ntag.NHITSTH35.txt
#COMMENTOUT