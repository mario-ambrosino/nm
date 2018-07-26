#!/bin/bash
for i in `ls ./dataset/derivative | grep mode`
  do
  gawk -v FS=";" '{ print $3}' ./dataset/derivative/$i > ./dataset/derivative/errors/$i
  echo "$i" >> ./dataset/derivative_analysis.dat
  ./exec/reduced_analysis.exe ./dataset/derivative/errors/$i >> ./dataset/derivative_analysis_all.dat
done

for k in 1 2 3 4 5
  do
    for j in `ls ./dataset/derivative | grep mode$k-`
    do
    gawk -v FS=";" '{ print $3}' ./dataset/derivative/$j > ./dataset/derivative/errors/$j
    ./exec/reduced_analysis.exe ./dataset/derivative/errors/$j >> ./dataset/derivative_analysis_mode$k.dat
  done
done
