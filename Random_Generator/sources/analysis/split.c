#include <stdio.h>
#include <stdlib.h>
#include "./include/lib_data.c"
/*
	##	Histogram
	##	Mario Ambrosino v.1.0 19/04/2018
	##	Split data from 2-dimensional distribution to 1-dim sequence - for histogram
	##
	##	WARNING: use  as argument for the generator
	## 1° Arg.: Input name_file
	## 2° Arg.: Output histogram media
	## 3° Arg.: Output histogram st_dev
*/

int main(int argc, char **argv)  {
	data input_data;
	char * input_file = argv[1];
	input_data = Import_data(input_data, input_file);
	Export_1D_data(input_data,argv[2]);
	Export_y_data(input_data,argv[3]);
}
