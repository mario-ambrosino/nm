/*Mario Ambrosino - 07 Giugno 2018

  Programma per la ricerca dei punti di minimo di una funzione reale tramite il
  metodo di bisezione per la ricerca di zeri della derivata e filtro sulla mono-
  tonia della successione ricorsiva

  Variabili:
  FLOAT[1] = min
  FLOAT[2] = max
  FLOAT[3] = epsilon
  INT[4] = mode : per la ricerca di minimo o massimo

   */

  #include <stdio.h>
  #include <stdlib.h>
  #include <math.h>

  void minima_search(double (*f)(double), double a, double b, double epsilon, int mode);
  double derivative(double (*f)(double), double x, double h);
  double func(double x);


  int main(int argc, char **argv) {
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double epsilon = atof(argv[3]);
    int mode = atoi(argv[4]);
    minima_search(func, a, b, epsilon, mode);
    return EXIT_SUCCESS;
  }

void minima_search(double (*f)(double), double a, double b, double epsilon, int mode) {
  int i = 1;
  double c = 0.5*(a+b);
  double delta = fabs(a-b);
    while (delta > epsilon) {

      double p;

      if (mode == 0) { // ricerca minimo
      c = 0.5 * (a + b);
      printf("%d; d:a = %lf; d:b= %lf; d:c= %lf;\n", i++, derivative(f,a,epsilon), derivative(f,b,epsilon), derivative(f,c,epsilon));
      p = derivative(f,a,epsilon) * derivative(f,c,epsilon);
      if (p > 0. ) {
        a = c;
      } else if (p < 0. && f(a) <= f(c)) {
        a = c;
      }
        else if ((p < 0.) && (f(a) > f(c))) {
        b = c;
      } else {
        a = b = c;
      }
      printf("%d; %e; %e; %e; %e\n", i++, a, b, 0.5*(a+b), fabs(3*M_PI/2 - c));
      delta = fabs (a-b);
      }

      if (mode == 1) { // ricerca massimo
      c = 0.5 * (a + b);
      printf("%d; d:a = %lf; d:b= %lf; d:c= %lf;\n", i++, derivative(f,a,epsilon), derivative(f,b,epsilon), derivative(f,c,epsilon));
      if (p > 0. ) {
        a = c;
      } else if (p < 0. && f(a) >= f(c)) {
        a = c;
      }
        else if ((p < 0.) && (f(a) < f(c))) {
        b = c;
      } else {
        a = b = c;
      }
      printf("%d; %e; %e; %e; %e\n", i++, a, b, 0.5*(a+b), fabs(0.5*M_PI - c));
      delta = fabs (a-b);
    }
  }
}

double derivative(double (*f)(double), double x, double h) {
  return (f(x+h)-f(x-h))/(2*h);
  }

double func( double x) {
    return sin(x);
  }
