#!/bin/bash
for i in $`seq $1 $2 $3`; do
./exec/test_integration.exe $1 $i 3000 3001 1 >> ./dataset/integrate.dat
done
