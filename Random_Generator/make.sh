#!/bin/bash
# Generatori uniformi
gcc ./sources/makers/uniform_1D_maker.c -Wall -I./ -lm -o ./exe/uniform_1D_maker.exe -O3
gcc ./sources/makers/uniform_2D_maker.c -Wall -I./ -lm -o ./exe/uniform_2D_maker.exe -O3
gcc ./sources/makers/uniform_3D_maker.c -Wall -I./ -lm -o ./exe/uniform_3D_maker.exe -O3
# Generatori non uniformi
gcc ./sources/makers/exp_maker.c -Wall -I./ -lm -o ./exe/exp_maker.exe -O3
gcc ./sources/makers/gamma_maker.c -Wall -I./ -lm -o ./exe/gamma_maker.exe -O3
gcc ./sources/makers/normal_1D_maker.c -Wall -I./ -lm -o ./exe/normal_1D_maker.exe -O3
gcc ./sources/makers/normal_2D_maker.c -Wall -I./ -lm -o ./exe/normal_2D_maker.exe -O3
# Strumenti di Analisi
gcc ./sources/analysis/random_analysis.c -Wall -I./ -lm -o ./exe/random_analysis.exe -O3
gcc ./sources/analysis/histogram.c -Wall -I./ -lm -o ./exe/histogram.exe -O3
gcc ./sources/analysis/period.c -I./ -Wall -lm -o ./exe/period.exe -O3
gcc ./sources/analysis/sample_period.c -I./ -Wall -lm -o ./exe/period2.exe -O3
gcc ./sources/analysis/reduced_analysis.c -I./ -Wall -lm -o ./exe/reduced_analysis.exe -O3
gcc ./sources/analysis/histogram2.c -I./ -Wall -lm -o ./exe/histogram2.exe -O3
gcc ./sources/analysis/split.c -I./ -Wall -lm -o ./exe/split.exe
# Problemi
gcc ./sources/problems/hitmissmeasure.c -I./ -Wall -lm -o ./exe/hitmiss.exe -O3
gcc ./sources/problems/walker.c -I./ -Wall -lm -o ./exe/walker.exe -O3
gcc ./sources/problems/walker1D.c -I./ -Wall -lm -o ./exe/walker1D.exe -O3

echo
echo 'Make Process Completed'
