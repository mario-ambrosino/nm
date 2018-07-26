/*

  * Trasformata di Fourier Discreta veloce (FFT)
  *
	Variabili

	[1] (string) input funzione
	[2] (string) output trasformata

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>
#include <time.h>

//STRUTTURA DATI

struct complex_struct {
	double complex *z;	//complex
	int Dim;
};

typedef struct complex_struct cdata;

cdata new_cdata(int New_Dimension, cdata Input);
cdata Import_cdata(cdata Input, char name_file[]);
void Export_cdata(cdata Input, char name_file[]);

void fft (cdata in);
void revshuffle(cdata input);
unsigned int bitrev(unsigned int inp,unsigned int numbits);
int log_2(int n);
void cswap(cdata data, int in, int out);


int main(int argc, char const *argv[]) {

	long unsigned start = 0;                                  // variabili per timing
	long unsigned stop = 0;                                   // variabili per timing

	//importa nome funzione
	size_t len_in = strlen(argv[1]);
	char * import_dat = malloc(len_in+1);
	if(import_dat == NULL) return EXIT_FAILURE;
	strcpy(import_dat, argv[1]);
	//importa funzione
	cdata input = 	Import_cdata(input, import_dat);

	// importa nome output
	size_t len2_in = strlen(argv[2]);
	char * transform_dat = malloc(len2_in+1);
	if(transform_dat == NULL) return EXIT_FAILURE;
	strcpy(transform_dat, argv[2]);
	//riempie la struttura complessa con trasformata
	start = clock();
  fft(input);
	stop = clock();
	//esporta la struttura
	Export_cdata(input, transform_dat);
	printf("F:%s; %d; %lu;\n",transform_dat, input.Dim, (stop - start));
  free(input.z);
  return 0;
}

void fft (cdata in){
  int i;
	int N = in.Dim;
	revshuffle(in);
	//genera un vettore con le potenze di W
	cdata W = new_cdata(N/2, W);
	W.z[0] = 1;
	W.z[1]= cexp(2*M_PI*I / N);
	for(i = 2; i < N / 2; i++) {
			W.z[i] = cpow(W.z[1], i);
	}
	int n = 1;
	int a = N/2;
	for (int j = 0; j < log_2(N); j++) {
		for (int i = 0; i < N; i++) {
			if(!(i & n)) {
				double complex X = in.z[i];
				double complex Y = W.z[(i * a) % (n * a)] * in.z[i + n];
				in.z[i] = (X + Y) ;
				in.z[i+n] = (X - Y) ;
			}
		}
		n *= 2;
		a = a/2;
	}
	free(W.z);
}

void revshuffle(cdata input)
{
	unsigned int i, j;
	int N = input.Dim;
	unsigned int log2n = log_2(N);
	cdata output = new_cdata(N, output);
	for (i = 0; i < input.Dim; i++) {
		j = bitrev(i, log2n);
		if (i <= j) cswap(input, i, j);
	}
}

 unsigned int bitrev(unsigned  int input, unsigned int N) {
  unsigned int i, reversed = 0;
  for (i = 0; i < N; i++)
  {
    reversed = (reversed << 1) | (input & 1);
    input = input >> 1;
  }
  return reversed;
}

int log_2(int n)
{
  int res;
  for (res=0; n >= 2; res++)
    n = n >> 1;
  return res;
}

cdata new_cdata(int New_Dimension, cdata Input) {
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.z = (double complex *) calloc(Input.Dim, sizeof(double complex));
	if (Input.z == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

void Export_cdata(cdata Input, char name_file[]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
//		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf; %lf; %lf;\n", creal(Input.z[i]) / sqrt(Input.Dim), cimag(Input.z[i])/ sqrt(Input.Dim), cabs(Input.z[i]) / Input.Dim);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}

cdata Import_cdata(cdata Input, char name_file[]) {
	int i = 0, N = 0;
	double a = 0, b = 0;
	FILE *input_file = NULL;
	if ((input_file = fopen(name_file,"r")) == NULL ) {
		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
	char c;
   while( (c = getc(input_file))!=EOF ) if(c=='\n') N++;
   rewind(input_file);
   Input.Dim = N;

	 // controllo sulla potenza
	 if (fmod(log2(N),floor(log2(N)))!= 0) {
 		printf("\nWrong Dataset Cardinality.\nClosing...");
 		exit(EXIT_FAILURE);
 		}

	Input = new_cdata(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		a = b = 0;
		fscanf(input_file, "%lf; %lf;", &a, &b);
		Input.z[i] = a + I*b;
		}
	fclose(input_file);
//	printf("\nImport Completed. %i cdata pair(s) found.", Input.Dim);
	return(Input);
}


void cswap(cdata data, int in, int out) {
	double complex temp;
	temp = data.z[in];
	data.z[in] = data.z[out];
	data.z[out] = temp;
	}
