#!/bin/bash
#genera la sequenza di dati
for i in `seq 4 1 10`; do
  j=$((2**$i))
  ./exe/uniform_maker.exe ${j} ./dataset/raw/uniform_${j}.dat
  ./exe/sinus_maker.exe ${j} ./dataset/raw/sinus_${j}.dat
  ./exe/step_maker.exe ${j} ./dataset/raw/step_${j}.dat
  ./exe/function_maker.exe ${j} ./dataset/raw/function_${j}.dat
  ./exe/door_maker.exe ${j} ./dataset/raw/door_${j}.dat
done
#effettua le trasformate e antitrasformate
for times in in `seq 1 1 30`; do
  for k in `ls ./dataset/raw`; do
    ./exe/dft.exe ./dataset/raw/${k} ./dataset/dft/dft_${k} 0 >> ./dataset/log_dft.dat
    ./exe/fft.exe ./dataset/raw/${k} ./dataset/fft/fft_${k} >> ./dataset/log_fft.dat
    ./exe/dft.exe ./dataset/dft/dft_${k} ./dataset/idft/idft_${k} 1 >> ./dataset/void.dat
    ./exe/dft.exe ./dataset/fft/fft_${k} ./dataset/ifft/ifft_${k} 1 >> ./dataset/void.dat
  done
done
#estrae le colonne di n.dati vs tempi
for n in uniform sinus step function door; do
cat ./dataset/log_dft.dat | grep ${n} | gawk -v FS=";" '{ print $2 $3}' > ./dataset/log/dft_${n}.dat
cat ./dataset/log_fft.dat | grep ${n} | gawk -v FS=";" '{ print $2 $3}' > ./dataset/log/fft_${n}.dat
done

for p in `ls ./dataset/log`; do
  for q in `seq 4 1 10`; do
    w=$((2**$q))
    cat ./dataset/log/${p} | grep "${w} ;*" | gawk -v FS=" " '{ print $2}' > ./dataset/log2/${p}_${w}.dat
    cat ./dataset/log/${p} | grep "${w} ;*" | gawk -v FS=" " '{ print $2}' > ./dataset/log2/${p}_${w}.dat
  done
done

#rimuove i log generati tramite append
#rm ./dataset/log_dft.dat ./dataset/log_fft.dat ./dataset/void.dat
for l in `ls ./dataset/log2`; do
  ./exe/histogram.exe ./dataset/log2/${l} 50 ./dataset/histogram/h_${l}.dat
done
