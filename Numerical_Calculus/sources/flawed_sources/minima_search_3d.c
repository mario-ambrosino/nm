#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

/*
Minimizzazione di una funzione a M variabili utilizzando il "metodo del gradien-
te". Realizzata in 3 dimensioni.

Il listato è elaborato sulla base del paragrafo 18.2.2 del PS.

PARAMETRI

[1] (FLOAT) - componente x del punto iniziale;
[2] (FLOAT) - componente y del punto iniziale;
[3] (FLOAT) - componente z del punto iniziale;

*/

double functional(double *x, int n);
void copy(double *src, double *dest, int n);
void add(double *input, double a, double *output, int n);
double derivative(double (*f)(double *, int), double *x, int n, int j, double h);
void gradient(double (*f)(double *, int), double *x, double *grad, int n,
              double epsilon);
void opposite(double *x, int n);
void dump(double *x, int n, int count, ...);
void linmin(double (*f)(double *, int), double *x, double *u, int n,
	    double epsilon);
double norm(double *a, double *b, int n);

#define M 3
#define AAA 26.3
#define BBB 2.12
#define CCC 142.23
#define nprecision 1.E-6

int main(int argc, char const *argv[]) {

  double x1[M], x2[M], grad[M];
  double epsilon;
  int i;

  // acquisizione parametri in input;
  x1[0] = atof(argv[1]);
  x1[1] = atof(argv[2]);
  x1[2] = atof(argv[3]);
  epsilon = atof(argv[4]);

  do {
    copy(x1, x2, M);
    gradient(functional, x1, grad, M, epsilon);
    opposite(grad, M);
    printf("\n");
    dump(grad, M, 0);
    printf("\n");
    dump(x1, M, 1, functional(x1, M));
    printf("\n");
    linmin(functional, x1, grad, M, epsilon);
  } while (norm(x1, x2, M) > epsilon);

  return EXIT_SUCCESS;
}

// DEFINIZIONE FUNZIONE
double functional(double *x, int n) {
  return 16*(x[0] - AAA) * (x[0] - AAA) + 40 * (x[1] - BBB) * (x[1] - BBB) + 32 * (x[2] - CCC) * (x[2] - CCC);
}

void copy(double *src, double *dest, int n) {
  /* copia il vettore src nel vettore dest */
  int i;
  for (i = 0; i < n; i++) {
    dest[i] = src[i];
  }
}

void add(double *input, double a, double *output, int n) {
  int i;
  for (i = 0; i < n; i++) {
    output[i] += a * input[i];
  }
}

double derivative(double (*f)(double *, int), double *x, int n, int j, double h) {
  double output = -(*f)(x, n);
  double temp = x[j];
  x[j] += h;
  output += (*f)(x, n);
  output /= h;
  x[j] = temp;
  return output;
}

double dFdLambda(double (*f)(double *, int), double *x, double *u, int n,
		 double epsilon) {
  /* calcola la derivata di f(x+lambda*u) rispetto a lambda nel punto x */
  double *x_back = (double *)calloc(n, sizeof(double));
  double derivative = 0.;
  copy(x, x_back, n);
  derivative -= (*f)(x, n);
  add(x, epsilon, u, n);
  derivative += (*f)(x, n);
  derivative /= epsilon;
  copy(x_back, x, n);
  free(x_back);
  return derivative;
}

double dF2dLambda2(double (*f)(double *, int), double *x, double *u,
		   int n, double epsilon) {
  /* calcola la derivata seconda di f(x+lambda*u) rispetto a lambda
     nel punto */
  double der1, der2, der;
  double *x_back = (double *)calloc(n, sizeof(double));
  /* salva la posizione corrente */
  copy(x, x_back, n);
  der1 = dFdLambda((*f), x, u, n, epsilon);
  /* calcola x + epsilon*u */
  add(x, epsilon, u, n);
  der2 = dFdLambda((*f), x, u, n, epsilon);
  der = (der2 - der1) / epsilon;
  /* rimette a posto le coordinate */
  copy(x_back, x, n);
  free(x_back);
  return der;
}

void gradient(double (*f)(double *, int), double *x, double *grad, int n,
              double epsilon) {
  /* calcola il gradiente di x e lo restituisce in grad */
  int i;
  for (i = 0; i < n; i++) {
    grad[i] = derivative((*f), x, n, i, epsilon);
  }
}

void opposite(double *x, int n) {
  /* cambia x in -x */
  int i;
  for (i = 0; i < n; i++) {
    x[i] = -x[i];
  }
}

double norm(double *a, double *b, int n) {
  /* restituisce sqrt(|b-a|^2) */
  double d = 0.;
  int i;
  for (i = 0; i < n; i++) {
    d += (a[i]-b[i])*(a[i]-b[i]);
  }
  return sqrt(d);
}

void linmin(double (*f)(double *, int), double *x, double *u, int n,
	    double epsilon) {
  double derA, derB, derC;
  double lambda = epsilon, lambdamin, lambdamax;
  double *x_back = (double *)calloc(n, sizeof(double));
  /* salva la posizione corrente */
  copy(x, x_back, n);
  /* trova due valori di lambda per cui le derivate sono discordi */
  derA = dFdLambda((*f), x, u, n, epsilon);
  derC = derA;
  while ((derA * derC) >= 0) {
    copy(x_back, x, n);
    add(x, lambda, u, n);
    derC = dFdLambda((*f), x, u, n, epsilon);
    lambda *= 2.;
  }
  /* ora usa il metodo di bisezione per risolvere f'(x) = 0 */
  lambdamin = 0;
  lambdamax = lambda;
  lambda = 0.5 *(lambdamin + lambdamax);
  do {
    copy(x_back, x, n);
    add(x, lambdamin, u, n);
    derA = dFdLambda((*f), x, u, n, epsilon);
    copy(x_back, x, n);
    add(x, lambda, u, n);
    derB = dFdLambda((*f), x, u, n, epsilon);
    copy(x_back, x, n);
    add(x, lambdamax, u, n);
    derC = dFdLambda((*f), x, u, n, epsilon);
    if ((derA * derB) > 0) {
      lambdamin = lambda;
    } else if ((derA * derB) < 0) {
      lambdamax = lambda;
    } else {
      lambdamin = lambdamax = lambda;
    }
    lambda = 0.5 *(lambdamin + lambdamax);
  } while (fabs(lambdamin-lambdamax) > epsilon);
  /* calcola la posizione raggiunta */
  copy(x_back, x, n);
  add(x, lambda, u, n);
  free(x_back);
}

void dump(double *x, int n, int count, ...) {
  int i;
  va_list optionalParameters;

  for (i = 0; i < n; i++) {
    printf("%+f ", x[i]);
  }
  va_start(optionalParameters, count);
  for (i = 0; i < count; i++) {
    printf("%+f ", va_arg(optionalParameters, double));
  }
  va_end(optionalParameters);
}
