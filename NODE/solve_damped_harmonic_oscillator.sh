#!/usr/bin/env bash

./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/eul.dat
./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/eul-crom.dat
./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/picard.dat
./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/pre-corr.dat
./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/RK2.dat
./exec/damped_harmonic_oscillator.exe 20000 4 0 0.0003 1 30 6 ./dataset/damped_harmonic_oscillator/RK4.dat
