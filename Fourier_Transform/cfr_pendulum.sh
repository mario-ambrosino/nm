#!/bin/bash
#estrae i valori angolari dal dataset del pendolo
for p in `ls ./dataset/raw_pendulum`; do
  cat ./dataset/raw_pendulum/${p} | gawk -v FS=" " '{ print $2 " 0.0000"}' > ./dataset/extracted_pendulum/${p}
  ./exe/fft.exe ./dataset/extracted_pendulum/${p} ./dataset/extracted_pendulum/fft_${p}
  cat ./dataset/extracted_pendulum/fft_${p} | gawk -v FS=";" '{ print $3}' > ./dataset/extracted_pendulum/pow_${p}
done
