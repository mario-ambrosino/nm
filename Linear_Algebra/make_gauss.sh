#!/bin/bash
export LFC_HOST='lfc-gilda.ct.infn.it'

echo Programma Dimostrativo per Gilda
echo Eliminazione di Gauss-Jordan
echo
echo Cambio autorizzazioni per file eseguibili ...
chmod 777 ./exe/make_matrix.exe
chmod 777 ./exe/gauss.exe
echo Cambio autorizzazioni eseguito.
echo Scrittura Matrice A Random ${1} X ${1} ...
./exe/make_matrix.exe ${1} $1 A.matrix
echo Scrittura Matrice A Completata.
echo Scrittura Matrice B Random ${1} X 1 ...
./exe/make_matrix.exe ${1} 1 B.matrix
echo Scrittura Matrice B Completata.
echo Scrittura Matrice Triangolare...
./exe/gauss.exe A.matrix B.matrix 0 > T.matrix
echo Scrittura Matrice Triangolare Completata.
echo Scrittura Matrice Soluzione Sistema...
./exe/gauss.exe A.matrix B.matrix 1 > S.matrix
echo Scrittura Matrice Soluzione Sistema Completata...
echo Scrittura Determinante matrice...
./exe/gauss.exe A.matrix B.matrix 2
echo Fine Programma.
