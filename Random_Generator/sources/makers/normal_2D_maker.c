#include "./include/lib_random.c"
#include <sys/time.h>

/* 

	##	Random Maker 
	##	Mario Ambrosino v.1.0 16/04/2018
	##	Make random data (x,y) using Box-Muller and Marsaglia generator.
	##
	##	WARNING: use  as argument for the generator

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_data(Dimension, random_data);
	RANDOM seed;
	double start = 0, stop = 0, a = 0, b = 0;
	
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	
	//BOX-MULLER 2D
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = Normal_Random_1(&seed);
	random_data.y[i] = Normal_Random_1(&seed);
	}
	stop = clock();
	a = stop - start;
	
	Export_data(random_data, "./dataset/Norm1.dat");
	
	//MARSAGLIA 2D
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = Normal_Random_2(&seed);
	random_data.y[i] = Normal_Random_2(&seed);
	}
	stop = clock();
	b = stop - start;
	Export_data(random_data, "./dataset/Norm2.dat");
	
	Free_data(random_data);	

	printf("\nRelative Timing: \nBox-Muller: %lf; \nMarsaglia: %lf;\n", a / b, b / b);	
	return EXIT_SUCCESS;
}
