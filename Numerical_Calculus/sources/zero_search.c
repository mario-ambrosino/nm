/*
  Programma per la ricerca degli zeri di funzioni utilizzando
  i seguenti metodi:

  1) metodo di bisezione
  2) metodo di Newton
  3) metodo delle secanti

  Mario Ambrosino - 05 Giugno 2018
  Variabili:
  FLOAT[1] = min
  FLOAT[2] = max
  FLOAT[3] = epsilon
  INT[4] = mode
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long double func(long double x);
long double dfunc(long double x);

int main(int argc, char **argv) {
  long double a = atof(argv[1]);
  long double b = atof(argv[2]);
  long double oc = b, temp;
  long double c = 0.5*(a+b);
  long double delta = fabs(a-b);
  long double epsilon = atof(argv[3]);
  int mode = atoi(argv[4]);
  int i = 1;

// METODO DI BISEZIONE
if(mode == 1) {
  while (delta > epsilon) {
    double p;
    c = 0.5 * (a + b);
    p = func(a)*func(c);
    if (p > 0.) {
      a = c;
  }  else if (p < 0.) {
    b = c;
  } else {
    a = b = c;
  }
  printf("%d; %Le; %Le; %Le; %Le\n", i++, a, b, 0.5*(a+b), fabsl(0.5*M_PI - c));
  delta = fabs (a-b);
  }
}

// METODO DI NEWTON
if(mode == 2) {
  while (delta > epsilon) {
    double p;
    c = c - func(c)/dfunc(c);
    p = func(a)*func(c);
    if (p > 0.) {
      a = c;
  }  else if (p < 0.) {
    b = c;
  } else {
    a = b = c;
  }
  printf("%d; %Le; %Le; %Le; %Le\n", i++, a, b, 0.5*(a+b), fabsl(0.5*M_PI - c));
  delta = fabs (a-b);
  }
}

// METODO DELLA SECANTE
if(mode == 3) {
  while (delta > epsilon) {
    double p;
    temp = oc;
    oc = c;
    c = c - func(c)*(c-temp)/(func(c)-func(temp));
    p = func(a)*func(c);
    if (p > 0.) {
      a = c;
  }  else if (p < 0.) {
    b = c;
  } else {
    a = b = c;
  }
  printf("%d; %Le; %Le; %Le; %Le\n", i++, a, b, 0.5*(a+b), fabsl(0.5*M_PI - c));
  delta = fabs (a-b);
  }
}

return EXIT_SUCCESS;
}

long double func(long double x) {
  return cos(x);
}

long double dfunc(long double x) {
  return -sin(x);
}
