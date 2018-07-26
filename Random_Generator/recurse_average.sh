#!/bin/bash

# $1: N: Num. of tests
# S2: M: Num. of samples for each test
	for i in $`seq 0 2000 8000`; do
		./central_limit_theorem.sh $i 50
		mv ./dataset/central/H_media.dat ./dataset/central/average/m_$i.dat
		mv ./dataset/central/H_stdev.dat ./dataset/central/average/s_$i.dat
		./exe/split.exe ./dataset/central/average/m_$i.dat ./dataset/central/split/x_$i.dat ./dataset/central/split/y_$i.dat
		./exe/split.exe ./dataset/central/average/s_$i.dat ./dataset/central/split/ex_$i.dat ./dataset/central/void
		./exe/reduced_analysis.exe ./dataset/central/split/x_$i.dat >> ./dataset/central/average.dat
		./exe/reduced_analysis.exe ./dataset/central/split/y_$i.dat >> ./dataset/central/st_dev.dat
		./exe/reduced_analysis.exe ./dataset/central/split/ex_$i.dat >> ./dataset/central/est_dev.dat
		rm ./dataset/central/void
		clear
		echo "sequence $i done"
		done
