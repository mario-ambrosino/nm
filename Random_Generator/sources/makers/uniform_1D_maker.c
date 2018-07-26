#include "./include/lib_random.c"
#include <sys/time.h>
/* 

	##	Random Maker 
	##	Mario Ambrosino v.1.0 16/04/2018
	##	Make uniform random sequence made by argv[1] elements using L'Ecuyer and exporting in argv[2].
	##

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_1D_data(Dimension, random_data);
	
	RANDOM seed;
	
	//RAN2
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = -tv.tv_usec;
	for (i = 0 ; i < Dimension ; i++) 
	{
		random_data.x[i] = RAN2(&seed);
	}	
	Export_1D_data(random_data, argv[2]);
	
	return EXIT_SUCCESS;
}
