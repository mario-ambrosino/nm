#!/bin/bash

./exe/walker1D.exe 10000 1000 1 ./dataset/walkings/aged1.dat ./dataset/walkings/aged2.dat
for i in $`seq 1 1 10`; do
	./exe/walker.exe 10000 1 ./dataset/walkings/walk_$i.dat
	done 
