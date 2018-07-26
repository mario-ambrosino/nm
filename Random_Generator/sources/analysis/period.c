/*
	## Ricerca del periodo di un generatore 
	## nota: senza librerie personali
	##
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
	printf("Period not Found\n");
	exit(EXIT_FAILURE);
}

int main (int argc, char **argv) {
	long a = atoi(argv[1]);
	long b = atoi(argv[2]); 
	long m = atoi(argv[3]);
	long seed = time(0);
	long max = 0;
	
	max = Max_Period(a, b, m, seed);
	printf("MAX_PERIOD = %lu", max);
	return EXIT_SUCCESS;
	}
