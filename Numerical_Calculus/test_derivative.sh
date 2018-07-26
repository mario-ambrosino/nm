#!/bin/bash
for j in 1 2 3 4 5
  do
  for i in 1 2 3 4 5 6 7 8 9
    do
    ./exec/test_derivative.exe $j 1.e-$i | gawk -F: '{ print $4}' > ./dataset/derivative/mode$j-$i.dat
  done
done
