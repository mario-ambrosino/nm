/*

  * Trasformata di Fourier Discreta (DFT)
  *
	Variabili

	[1] (string) input funzione
	[2] (string) output trasformata
	[3] (int) mode

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

void dft (cdata in, cdata out, int mode);
cdata new_cdata(int New_Dimension, cdata Input);
cdata Import_cdata(cdata Input, char name_file[]);
void Export_cdata(cdata Input, char name_file[]);

int main(int argc, char const *argv[]) {

	int mode = atoi(argv[3]);
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
	//genera struttura complessa output
  cdata output = new_cdata(input.Dim, output);
	//riempie la struttura complessa con trasformata
	start = clock();
  dft(input, output, mode);
	stop = clock();
	//esporta la struttura
	Export_cdata(output, transform_dat);
	printf("F:%s; %d; %lu;\n",transform_dat, input.Dim, (stop - start));
	free(input.z);
	free(output.z);
  return 0;
}

void dft (cdata in, cdata out, int mode){
	int k, t;
	double complex sum;
	int N = in.Dim;
	for(k = 0; k < N; k++) {
		sum = 0.0;
		for(t = 0; t < N ; t++) {
			double theta = 2 * M_PI * t * k / N;
			if (mode == 0) sum += in.z[t] * cexp( - I * theta);
			if (mode == 1) sum += in.z[t] * cexp( + I * theta);
		}
		out.z[k] = sum / sqrt(N);
  }
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
		fprintf(input_file, "%lf; %lf;\n", creal(Input.z[i]), cimag(Input.z[i]));
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
	Input = new_cdata(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		a = b = 0;
		fscanf(input_file, "%lf; %lf;\n", &a, &b);
		Input.z[i] = a + I * b;
		}
	fclose(input_file);
//	printf("\nImport Completed. %i cdata pair(s) found.", Input.Dim);
	return(Input);
}
