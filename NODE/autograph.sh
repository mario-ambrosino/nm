#!/bin/bash
for FILE in *.datacart; do
    gnuplot <<- EOF
        set terminal png size 1024,1024 enhanced font "Cantarell ,20"
        set output "${FILE}.png"
        splot "${FILE}"  with points u 1:3:2
EOF
done
