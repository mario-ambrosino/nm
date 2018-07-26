#include "./include/lib_random.c"
#include <sys/time.h>

/* 
	##	Gaussian Random Walker - Mario Ambrosino 
	##	v.1.0 19/04/2018
	##	v.2.0 20/04/2018: seed con tempi ai usec
	##							adattato all'analisi con script shell
	## Use 1° argument as Max_Time_Step
	## Use 2° argument as Num_Trial
	## Use 3° argument as Amplitude
	## Use 4° argument as output_namefile for last random path
	## Use 5° argument as output_namefile for average path
*/

int main (int argc, char **argv)  {
	
	int i, j;
	int Dimension = atoi(argv[1]);
	int Trials = atoi(argv[2]);
	double Amplitude = atof(argv[3]);
	data hist1 = new_data(Dimension, hist1);
	data hist2 = new_3D_data(Dimension, hist2);
	RANDOM seed;
	struct timeval tv;
	gettimeofday(&tv, 0);
	seed = -tv.tv_usec;
	
	printf("\nSeed = %Lu\n", seed);
	for (j = 0; j < Trials; j++) {
		hist1.x[0] = hist1.y[0] = 0; 
		for (i = 1; i < Dimension; i++) {
			hist1.x[i] = hist2.x[i] = i;
			hist1.y[i] = hist1.y[i-1] + Amplitude*Normal_Random_1(&seed);
			hist2.y[i] += hist1.y[i] * hist1.y[i];
			hist2.z[i] += hist2.y[i] * hist2.y[i];
		} 	
	}
	//make average
	for (i = 0 ; i < Dimension ; i++) {
		hist2.y[i] /= Trials;
		hist2.z[j] /= Trials;
	}
	//valutate st.deviation at each step
	for (i = 0 ; i < Dimension ; i++) {
		hist2.z[i] -= hist2.y[i]*hist2.y[i];
		hist2.z[i] = sqrt(hist2.z[i]); 
	}		
	//Esporta l'ultimo cammino
	Export_data (hist1, argv[3]);
	//Esporta il cammino medio
	Export_3D_data(hist2, argv[4]);
	return EXIT_SUCCESS;
}
