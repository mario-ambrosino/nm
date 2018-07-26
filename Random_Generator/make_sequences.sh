#!/bin/bash

./exe/uniform_1D_maker.exe 100000 ./dataset/Uniform.dat
./exe/normal_1D_maker.exe 100000 ./dataset/Normal.dat
./exe/exp_maker.exe 100000 100 ./dataset/Exp.dat
./exe/gamma_maker.exe 100000 100 ./dataset/Gamma.dat
echo 'Random Dataset Exported'
