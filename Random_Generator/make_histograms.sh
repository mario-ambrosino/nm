#!/bin/bash

./exe/histogram2.exe ./dataset/Gamma.dat 50 ./dataset/H_Gamma.dat
./exe/histogram2.exe ./dataset/Exp.dat 50 ./dataset/H_Exp.dat
./exe/histogram2.exe ./dataset/Uniform.dat 50 ./dataset/H_Uniform.dat
./exe/histogram2.exe ./dataset/Normal.dat 50 ./dataset/H_Normal.dat
echo 'Data Histogram Exported'
