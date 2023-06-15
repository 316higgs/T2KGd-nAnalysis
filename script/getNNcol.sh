#!/bin/bash

make cleanNNcorrelation
make NNcorrelation.exe

#need to source /home/rakutsu/disk2/t2k/tmp/t2ksk-neutronh/envntag.csh (exist the same script in this /analysis directory)
#source /home/rakutsu/disk2/t2k/tmp/t2ksk-neutronh/envntag.csh

#<<COMMENTOUT
if [ ! -f ./NNcorrelation.exe ]; then
  exit 2
fi

if [ -e ./tmp ]; then
  rm -rf ./tmp
fi

DISK3=/disk03/usr8/sedi


type=0
#type=1
#type=2
#type=3
#type=4
Label="All"
if [ $type -eq 0 ]; then
  echo "==========================="
  echo " Type: Truth Noise"
  echo "==========================="
  Label="Noise"
fi
if [ $type -eq 1 ]; then
  echo "==========================="
  echo " Type: Decay-e"
  echo "==========================="
  Label="Dcye"
fi
if [ $type -eq 2 ]; then
  echo "==========================="
  echo " Type: Truth H-n"
  echo "==========================="
  Label="H"
fi
if [ $type -eq 3 ]; then
  echo "==========================="
  echo " Type: Truth Gd-n"
  echo "==========================="
  Label="Gd"
fi
if [ $type -eq 4 ]; then
  echo "==========================="
  echo " Type: All"
  echo "==========================="
  Label="All"
fi

### ./analysis1Rmu.exe [Noise(0)/H-n(1)/Gd-n(2)/All(3)] [NN input variable id1] [NN input variable id2]
### NOTE: id1 and id2 must be different!
mkdir ./tmp
filecount=0
for((ivar=1;ivar<13;ivar++))
do
  for((jvar=1;jvar<13;jvar++))
  do
  	filecount=$((++filecount))
  	if [ ${ivar} -eq ${jvar} ]; then
  	  #./NNcorrelation.exe $type ${ivar} 0 ${filecount}   #Self Correlation(diagonal)
      ./NNcorrelation.exe $type\
                          ${ivar}\
                          0\
                          ${filecount}\
                          ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.0\*.root\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUMU
  	  #echo " "
  	else
      ./NNcorrelation.exe $type\
                          ${ivar}\
                          ${jvar}\
                          ${filecount}\
                          ${DISK3}/Ntag/output/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.0\*.root\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUMU

      #echo " "
    fi
  done
done

OUTPUT="./output/fhc/numu_x_numu.NNcol.${Label}.root"
root -l './macro/NNinputvariables/CorrelationMatrix.C("'${OUTPUT}'")'

rm -rf ./tmp


#COMMENTOUT
