#include "./include/lib_random.c"
#include <sys/time.h>

/* 
	##	Exponential Random Maker 
	##	Mario Ambrosino v.1.0 16/04/2018
	##	Mario Ambrosino v.2.0 20/04/2018 : millsec seed
	##	Make exponential-distributed random sequence using Inversion method generator.
	##
	## Use 1° argument as Dimension
	##	Use 2° argument as lambda
	## Use 3° argument as output filename

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_1D_data(Dimension, random_data);
	RANDOM seed;
	double lambda = atof(argv[2]);
	
	//EXPONENTIAL GENERATOR
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = Exp_Random(&seed, lambda);
	}
	Export_1D_data(random_data, argv[3]);
	return EXIT_SUCCESS;
}
