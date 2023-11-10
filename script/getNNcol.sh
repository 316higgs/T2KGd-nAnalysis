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
ESC=$(printf '\033')
if [ $type -eq 0 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  printf "${ESC}[31m%s${ESC}[m\n" " Type: Truth Noise"
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  Label="Noise"
fi
if [ $type -eq 1 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  printf "${ESC}[31m%s${ESC}[m\n" " Type: Truth Decay electron"
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  Label="Dcye"
fi
if [ $type -eq 2 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  printf "${ESC}[31m%s${ESC}[m\n" " Type: Trut H-n"
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  Label="H"
fi
if [ $type -eq 3 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  printf "${ESC}[31m%s${ESC}[m\n" " Type: Gd-n"
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  Label="Gd"
fi
if [ $type -eq 4 ]; then
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  printf "${ESC}[31m%s${ESC}[m\n" " Type: All"
  printf "${ESC}[31m%s${ESC}[m\n" "==========================="
  Label="All"
fi

### ./analysis1Rmu.exe [Noise(0)/H-n(1)/Gd-n(2)/All(3)] [NN input variable id1] [NN input variable id2]
### NOTE: id1 and id2 must be different!
mkdir ./tmp
filecount=0
for((ivar=1;ivar<15;ivar++))
do
  for((jvar=1;jvar<15;jvar++))
  do
  	filecount=$((++filecount))
    echo "(i, j) = ($ivar, $jvar)"
  	if [ ${ivar} -eq ${jvar} ]; then
  	  #./NNcorrelation.exe $type ${ivar} 0 ${filecount}   #Self Correlation(diagonal)
      ./NNcorrelation.exe $type\
                          ${ivar}\
                          0\
                          ${filecount}\
                          ${DISK3}/Ntag/output/bonsai_keras_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.0\*.root\
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
                          ${DISK3}/Ntag/output/bonsai_keras_prompt_vertex/fhc/numu_x_numu/fhc.numu_x_numu.13a.ntag0026Gd.0\*.root\
                          -MCType Gd\
                          -ETAG ON\
                          -BEAMMODE FHC\
                          -OSCCH NUMU

      #echo " "
    fi
    echo " "
  done
done

OUTPUT="./output/fhc/numu_x_numu.NNcol.${Label}.root"
root -l -q './macro/NNinputvariables/CorrelationMatrix.C("'${OUTPUT}'")'

rm -rf ./tmp


#COMMENTOUT
