#include "./include/lib_data.c"
#include <string.h>
#include <math.h>

/*
	##	Function Maker
	##	Mario Ambrosino v.1.0 28/06/2018.

	[1] numero di punti
	[2] nome fil
*/

int main (int argc, char **argv)  {

	int i = 0;
	int N = atoi(argv[1]);
	data function_data = new_data(N, function_data);
	size_t len1_in = strlen(argv[2]);
	char * function_dat = malloc(len1_in+1);
	if(function_dat == NULL) return EXIT_FAILURE;
	strcpy(function_dat, argv[2]);

	for (i = 0 ; i < N ; i++)
	{
		function_data.x[i] = 2*M_PI * i / (N - 1);
		function_data.y[i] = sin(function_data.x[i]);
	}

	Export_y_data(function_data, function_dat);

	return EXIT_SUCCESS;
}
