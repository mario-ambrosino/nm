#!/bin/bash

# $1: N: Num. of tests
# S2: M: Num. of samples for each test
	for i in $`seq 1 1 ${1}`; do
		./exe/exp_maker.exe ${2} 137 ./dataset/central/input/${i}.dat
		done
	for j in $`seq 1 1 ${1}`; do
		./exe/reduced_analysis.exe ./dataset/central/input/${j}.dat >> ./dataset/central/output.dat
		done
	./exe/split.exe ./dataset/central/output.dat ./dataset/central/output_media.dat ./dataset/central/output_stdev.dat
	./exe/histogram2.exe ./dataset/central/output_media.dat 51 ./dataset/central/H_media.dat
	./exe/histogram2.exe ./dataset/central/output_stdev.dat 51 ./dataset/central/H_stdev.dat
