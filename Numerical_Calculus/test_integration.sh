#!/bin/bash
rm ./dataset/rettangolo.dat
rm ./dataset/trapezio.dat
rm ./dataset/simpson.dat
for i in $`seq $1 $1 $2`; do
(( j = $i+1 ))
./exec/test_integration.exe -3 3 $i $j 0 >> ./dataset/rettangolo.dat
./exec/test_integration.exe -3 3 $i $j 1 >> ./dataset/trapezio.dat
./exec/test_integration.exe -3 3 $i $j 2 >> ./dataset/simpson.dat
done
