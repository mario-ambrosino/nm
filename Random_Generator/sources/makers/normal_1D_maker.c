#include "./include/lib_random.c"
#include <sys/time.h>

/* 
	##	Random Maker 
	##	Mario Ambrosino v.1.0 16/04/2018
	##	Make random data (x,y) using Box-Muller and Marsaglia generator.
	##
	##	WARNING: use Dimension as argument for the generator
*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_1D_data(Dimension, random_data);
	RANDOM seed;
	
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	
	//BOX-MULLER 1D
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = Normal_Random_1(&seed);
	}	
	Export_1D_data(random_data, argv[2]);
	return EXIT_SUCCESS;
}
