#!/usr/bin/env bash

./exec/harmonic_oscillator.exe 2000 2 0 0.02 0 3 1 ./dataset/harmonic_oscillator/eul.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.02 0 3 2 ./dataset/harmonic_oscillator/eul-crom.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.02 0 3 3 ./dataset/harmonic_oscillator/picard.datz
./exec/harmonic_oscillator.exe 2000 2 0 0.02 0 3 4 ./dataset/harmonic_oscillator/pre-corr.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.02 0 3 5 ./dataset/harmonic_oscillator/RK2.dat
./exec/harmonic_oscillator.exe 200000 2 0 0.02 0 3 6 ./dataset/harmonic_oscillator/RK4.dat


./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 3 6 ./dataset/harmonic_oscillator/3.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 4 6 ./dataset/harmonic_oscillator/4.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 5 6 ./dataset/harmonic_oscillator/5.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 6 6 ./dataset/harmonic_oscillator/6.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 7 6 ./dataset/harmonic_oscillator/7.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 8 6 ./dataset/harmonic_oscillator/8.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 10 6 ./dataset/harmonic_oscillator/10.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 15 6 ./dataset/harmonic_oscillator/15.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 60 6 ./dataset/harmonic_oscillator/60.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 100 6 ./dataset/harmonic_oscillator/100.dat
./exec/harmonic_oscillator.exe 2000 2 0 0.002 0 200 6 ./dataset/harmonic_oscillator/200.dat
