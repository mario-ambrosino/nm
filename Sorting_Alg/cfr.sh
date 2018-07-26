#!/bin/bash
for i in `seq 1 1 $1`; do
  ./exe/uniform_maker.exe 10000 ./dataset/raw/${i}.dat
done

for j in `ls ./dataset/raw`; do
  for k in 1 2 3 4 5; do
    ./exe/sort.exe ./dataset/raw/${j} ${k} ./dataset/sorted/sort_${k}_${j} >> ./dataset/log.dat
  done
done
