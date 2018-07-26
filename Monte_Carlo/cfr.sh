#!/bin/bash
for N in `seq 1000 1000 100000`; do
  echo ${N}
./exe/mc.exe 0 0 1 ${N} 15 0.4 >> ./dat/0_log.dat
./exe/mc.exe 1 0 1 ${N} 15 0.4 >> ./dat/1_log.dat
done

cat ./dat/0_log.dat | gawk -v FS=";" '{ print $2}' > ./dat/0.dat
cat ./dat/1_log.dat | gawk -v FS=";" '{ print $2}' > ./dat/1.dat

for N in `seq 1000 1000 100000`; do
cat ./dat/0.dat | grep ${N} | gawk -v FS=" " '{ print $2}' > ./dat/0_${N}.dat |
cat ./dat/1.dat | grep ${N} | gawk -v FS=" " '{ print $2}' > ./dat/1_${N}.dat
done

for N in `seq 1000 1000 100000`; do
var=${N}
./exe/analysis.exe ./dat/0_${N}.dat | gawk -v FS=" "  '{ print var " " $1 " " $2}' >> ./dat/m_0.dat
./exe/analysis.exe ./dat/1_${N}.dat | gawk -v FS=" "  '{ print var " " $1 " " $2}' >> ./dat/m_1.dat
done
