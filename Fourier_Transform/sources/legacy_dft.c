/*

  * Programma che esegue la trasformata di fourier di x*(1-x)
  * nell'intervallo [0.1]
  *

  [1] (int) numero di punti N
	[2] (string) output funzione
	[3] (string) output trasformata
	[4] (string) output antitrasformata
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <complex.h>

//STRUTTURA DATI
struct complex_struct {
	double *x;					//real
	double complex *y;	//complex
	int Dim;
};

typedef struct complex_struct cdata;

double func(double x);
cdata evaluate_func (double (*f)(double), cdata out);
cdata evaluate_dft (cdata in, cdata out);
double complex gcoeff (cdata in, int j);
double complex dft (cdata in, int k);
cdata new_cdata(int New_Dimension, cdata Input);
void Export_cdata(cdata Input, char name_file[]);


double N = 128;

int main(int argc, char const *argv[]) {

  N = atoi(argv[1]);

	// valutazione funzione
	size_t len1_in = strlen(argv[2]);
	char * function_dat = malloc(len1_in+1);
	if(function_dat == NULL) return EXIT_FAILURE;
	strcpy(function_dat, argv[2]);
  cdata fun = new_cdata(N, fun);
	fun = evaluate_func(func, fun);
	Export_cdata(fun, function_dat);

	// valutazione trasformata
	size_t len2_in = strlen(argv[3]);
	char * transform_dat = malloc(len2_in+1);
	if(transform_dat == NULL) return EXIT_FAILURE;
	strcpy(transform_dat, argv[3]);
  cdata tf = new_cdata(N, tf);
  tf = evaluate_dft(fun, tf);
	Export_cdata(tf, transform_dat);

  //valutazione antitrasfromata
	/*
	size_t len_in = strlen(argv[4]);
	char * antitransform_dat = malloc(len_in+1);
	if(antitransform_dat == NULL) return EXIT_FAILURE;
	strcpy(antitransform_dat, argv[4]);
  cdata ttf = new_cdata(N, ttf);
 */

  return 0;
}

double func(double x) {
  return x*(1-x);
}

cdata evaluate_func (double (*f)(double), cdata out){
  int i;
  double h = 1 / (N - 1);
  for(i = 0; i < N; i++) {
    out.x[i] = h*i;
    out.y[i] = f(out.x[i]);
  }
  return out;
}

cdata evaluate_dft (cdata in, cdata out){
  int i;
  double h = 2*M_PI / ((N - 1)*(N - 1));
  for(i = 0; i < N; i++) {
		out.x[i] = h*i;
    out.y[i] = dft(in, i);
  }
  return out;
}

double complex gcoeff (cdata in, int j) {
  int k;
  double complex ft;
  for( k = 0; k < N ; k++) {
    ft += in.y[k] * cexp( -2 * I * M_PI * k * j / N);
  }
  ft /= sqrt(N);
  return ft;
}

double complex dft (cdata in, int k) {
  int j;
  double complex dft;
  for( j = 0; j < N ; j++) {
    dft += gcoeff(in,j) * cexp( 2 * I * M_PI * k * j / N);
  }
  dft /= sqrt(N);
	return dft;
}

cdata new_cdata(int New_Dimension, cdata Input) {
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.x == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.y = (double complex *) calloc(Input.Dim, sizeof(double complex));
	if (Input.y == NULL) {
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
		fprintf(input_file, "%lf %lf %lf\n", Input.x[i], creal(Input.y[i]), cimag(Input.y[i]));
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}
