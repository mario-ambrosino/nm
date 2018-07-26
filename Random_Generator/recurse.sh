#!/bin/bash

# $1: N: Num. of tests
# S2: M: Num. of samples for each test
		./central_limit_theorem.sh 1000 100
		mv ./dataset/central/H_media.dat ./dataset/central/uniform/mUniform_1000.dat
		mv ./dataset/central/H_stdev.dat ./dataset/central/uniform/sUniform_1000.dat
	for i in $`seq 1000 1000 10000`; do 
		./central_limit_theorem.sh $i 100
		mv ./dataset/central/H_media.dat ./dataset/central/uniform/mUniform_$i.dat
		mv ./dataset/central/H_stdev.dat ./dataset/central/uniform/sUniform_$i.dat
		echo "Sequence $i done"
		done
