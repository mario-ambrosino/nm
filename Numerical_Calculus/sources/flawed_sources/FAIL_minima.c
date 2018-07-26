/*Mario Ambrosino - 05 Giugno 2018

  Programma per la ricerca dei punti di minimo di un funzionale utilizzando
  il metodo di discesa del gradiente.

  Ricostruito da Cap. 18 P.S.
  Variabili:

  [1] condizione iniziale "x"
  [2] condizione iniziale "y"
  [3] condizione iniziale "z"
  [4] condizione passo*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#define M 3
#define AAA 26.3
#define BBB 2.12
#define CCC 142.23
#define nprecision 1.E-6

int main (int argc, char **argv) {
  double x1[M], x2[M], grad[M];
  double epsilon;
  int i;

  // input parametri da console:
  x1[0] = atof[argv[1]]
  x1[1] = atof[argv[2]]
  x1[2] = atof[argv[3]]
  epsilon = atof[argv[4]]
  do{
    copy(x1,x2,M);
    gradient(functional, x, grad, M, nprecision);
    dump(grad, M, 0);
    dump(x, M, 1, functional(x, M));
    printf("\n");

  }
  return EXIT_SUCCESS;
}



// DEFINIZIONE FUNZIONE
double functional(double *x, int N) {
  return 16*(x[0] - AAA) * (x[0] - AAA) + 40 * (x[1] - BBB) * (x[1] - BBB) + 32 * (x[2] - CCC) * (x[2] - CCC);
}

// STRUMENTI ANALITICI
void gradient(double (*f)(double *, int), double *x, double *grad, int n, double precision){
  int i;
  for (i = 0; i < n; i++) {
    grad[i] = derivative((*f), x, M, i, precision);
  }
}

double part_derive(double (*f)(double *, int), double *x, int n, int j, double h) {
  double derivative = -(*f)(x, n);
  double temp = x[j];
  x[j] += h;
  der += (*f)(x, n);
  der /= h;
  x[j] = temp;
  return der;
}

// OPERAZIONI SUI PUNTI
void opposite(double *x, int n) {
  int i;
  for (i = 0; i < n; i++) {
    x[i] = -x[i];
  }
}

void sum(double *x, double a, double *y, int n) {
  int i;
  for (i = 0; i < n; i++) {
    x[i] += a*y[i];
  }
}

void copy(double *in, double *out, int n) {
  int i;
  for (i = 0; i < n; i++) {
    in[i] = out[i];
  }
}
