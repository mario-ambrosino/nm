#include "./include/lib_random.c"
#include <sys/time.h>

/* 
	##	Gamma Random Maker 
	##	Mario Ambrosino v.1.0 18/04/2018
	##	Make gamma-distributed random sequence using Inversion method generator.
	##
	## Use 1° argument as Dimension
	##	Use 2° argument as alpha
	##	Use 3° argument as output_namefile

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_1D_data(Dimension, random_data);
	RANDOM seed;
	double alpha = atof(argv[2]);
	
	//GAMMA GENERATOR
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = Gamma_Random(&seed, alpha);
	}
	Export_1D_data(random_data, argv[3]);
	return EXIT_SUCCESS;
}
