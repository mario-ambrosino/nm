#include "./include/lib_random.c"
#include <sys/time.h>

/* 

	##	Random Maker 
	##	Mario Ambrosino v.1.0 16/04/2018
	##	Make random data (x,y) using different LCGs.
	##
	##	WARNING: use  as argument for the generator

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	data random_data = new_3D_data(Dimension, random_data);
	RANDOM seed;
	srand48(seed);
	double start = 0, stop = 0, a = 0, b = 0, c = 0, d = 0, e = 0;
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	//SIMPLE 0
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = RAN0_Simple(&seed);
	random_data.y[i] = RAN0_Simple(&seed);
	random_data.z[i] = RAN0_Simple(&seed);
	}
	stop = clock();
	a = stop - start;
	
	Export_3D_data(random_data, "./dataset/R31.dat");
	
	//SCHRAGE 0
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = RAN0_Schrage(&seed);
	random_data.y[i] = RAN0_Schrage(&seed);
	random_data.z[i] = RAN0_Schrage(&seed);
	}
	stop = clock();
	b = stop - start;
	Export_3D_data(random_data, "./dataset/R32.dat");
	
	//RAN1 
	gettimeofday(&tv, 0);
	seed = -tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = RAN1(&seed);
	random_data.y[i] = RAN1(&seed);
	random_data.z[i] = RAN1(&seed);
	}
	stop = clock();
	c = stop - start;
	Export_3D_data(random_data, "./dataset/R33.dat");
	
	//RAN2
	gettimeofday(&tv, 0);
	seed = -tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = RAN2(&seed);
	random_data.y[i] = RAN2(&seed);
	random_data.z[i] = RAN2(&seed);
	}	
	stop = clock();
	d = stop - start;
	Export_3D_data(random_data, "./dataset/R34.dat");
	
	
	//RANDU
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = RANDU(&seed);
	random_data.y[i] = RANDU(&seed);
	random_data.z[i] = RANDU(&seed);
	}	
	stop = clock();
	d = stop - start;
	Export_3D_data(random_data, "./dataset/R35.dat");

	//RAS
	gettimeofday(&tv, 0);
	seed = tv.tv_usec;
	start = clock();
	for (i = 0 ; i < Dimension ; i++) {
	random_data.x[i] = lrand48() / (double) RAND_MAX;
	random_data.y[i] = lrand48() / (double) RAND_MAX;
	random_data.z[i] = lrand48() / (double) RAND_MAX;
	}	
	stop = clock();
	e = stop - start;
	Export_3D_data(random_data, "./dataset/R36.dat");	
	
	Free_data(random_data);	

	printf("\nRelative Timing (vs land48()): \nRAN0.1: %lf; \nRAN0.2: %lf; \nRAN1.1: %lf; \nRAN2.1: %lf; \n", a / e, b / e, c / e, d / e);	
	return EXIT_SUCCESS;
}
