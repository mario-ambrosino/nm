/*
	## Ricerca del periodo di un generatore 
	##
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./include/lib_random.c"

long Max_Period(long a, long b, long m, long seed) {
	
	long i, j;
	long value, vector[1000000];
	
	value = seed;
	vector[0] = value;
	for (i = 1; i <= m; i++) {
		value = (a * value + b) % m;
		vector[i] = value;
		for (j = 0; j < i; j++) {
			if (vector[j] == value) {
				return(i - j);
			}
		}
	}
	exit(EXIT_FAILURE);
}

int main (int argc, char **argv) {
	int i, a, b, m;
	RANDOM seed = -time(0);
	int max = 0;
	int dim = atoi(argv[1]);
	
	for (i = 0; i < dim; i++) {
		a = (int) 10000 * RAN2(&seed);
		b = (int) 10000 * RAN2(&seed);
		m = (int) 10000 * RAN2(&seed);
		max = Max_Period(a, b, m, seed);
		printf("\n%d %d %d %d;", a, b, m, max);
	}	
	return EXIT_SUCCESS;
	}
