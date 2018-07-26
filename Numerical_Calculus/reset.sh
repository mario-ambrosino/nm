#!/bin/bash

for i in $`ls ./dataset/derivative -m`; do
  $a=date +'%Y%m%d%H%M%S%N'
mv ./dataset/derivative/$i ./backup/derivative/$a$i.dat
done
