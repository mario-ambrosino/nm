
#include <stdio.h>
#include <stdlib.h>
#include "./include/lib_data.c"
#include <math.h>
/*
	##	Histogram
	##	Mario Ambrosino v.1.0 19/04/2018
	##	Make Histogram data and produce a gnuplot histogram from existing sequence .dat file
	##
	##	WARNING: use  as argument for the generator
	## 1° Arg.: Input name_file
	## 2° Arg.: Num. Bins;
	## 3° Arg.: Output histogram
*/

int main(int argc, char **argv)  {
	//definizioni
	data input_data, histogram;
	char * input_file = argv[1];
	int nbin = atoi(argv[2]);
	input_data = Import_list(input_data, input_file);
	int i, j, N = input_data.Dim;
	double min = Min_X_data(input_data), max = Max_X_data(input_data);
	double lenght = max - min;
	double width_bin = lenght / nbin;
	histogram = new_data(2*nbin, histogram);
		// utilizzo struttura dati: x = label istogramma,
		// y = n.occorrenze nel bin
	// Costruzione istogramma
	for (i = 0 ; i <= N ; i++) {
		j = ceil((input_data.x[i] - min) / (width_bin));
		histogram.y[j]++;
	}
	for (i = 0 ; i < nbin + 2; i++) {
		histogram.x[i] = min + i * width_bin;
	}
	Export_data(histogram, argv[3]);
}
