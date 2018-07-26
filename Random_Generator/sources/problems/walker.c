#include "./include/lib_random.c"
#include <sys/time.h>
/* 
	##	Gaussian Random Walker 
	##	Mario Ambrosino v.1.0 19/04/2018
	##	
	## Use 1° argument as Max_Time 
	## Use 2° argument as Amplitude
	## Use 3° argument as output_namefile

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Dimension = atoi(argv[1]);
	double Amplitude = atoi(argv[2]);
	data history = new_3D_data(Dimension, history);
	RANDOM seed;
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = -tv.tv_usec;
	
	for (i = 1; i < Dimension; i++) {
		history.x[i] = i;
		history.y[i] += history.y[i-1] + Amplitude * Normal_Random_2(&seed);
		history.z[i] += history.z[i-1] + Amplitude * Normal_Random_2(&seed);
	}
	Export_3D_data(history, argv[3]);
	return EXIT_SUCCESS;
}
