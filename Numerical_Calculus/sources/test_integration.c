#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Integrazione di una funzione a una variabile

PARAMETRI:
[1]: "a" (FLOAT) estremo inferiore di integrazione (unità di pigreco)
[2]: "b" (FLOAT)estremo superiore di integrazione (unità di pigreco)
[3]: "nmin" (INT) minimo numero di intervalli
[4]: "nmax" (INT) massimo numero di intervalli
[5]: "mode" (INT) modalità di funzionamento - cfr. Metodi

METODI:
[0]: rettangoli
[1]: trapezi
[2]: simpson
*/

//prototipi funzione
double function(double x);
double integrated_function(double a, double b);

int main(int argc, char *argv[]) {

  // parametri da tipizzare
  double a = M_PI * atof(argv[1]);
  double b = M_PI * atof(argv[2]);
  int nmin = atoi(argv[3]);
  int nmax = atoi(argv[4]);
  int mode = atoi(argv[5]);

  // variabili interne
  double sum = 0., spacing = 0.;
  int i,j;

  //metodo dei rettangoli
  if (mode == 0) {
    sum = 0;
    for(i = nmin ; i < nmax ; i++) {
      spacing = (b-a)/i;
      for (j = 0; j < i-1; j++) {
        sum += function(a+j*spacing);
      }
      sum *= spacing;
      printf("%d %e %e\n", i, sum, fabs(sum - 3.349523597959926));
    }
  }

  //metodo dei trapezi
  else if (mode == 1) {
    sum = 0;
    for(i = nmin ; i < nmax ; i++) {
      spacing = (b-a)/i;
      for (j = 0; j < i-1; j++) {
        sum += function(a+j*spacing) + function(a+(j+1)*spacing);
      }
      sum *= 0.5 * spacing;
      printf("%d %e %e\n", i, sum, fabs(sum - 3.349523597959926));
    }
  }
  // metodo di simpson
  else if (mode == 2) {
    sum = 0;
    for(i = nmin; i < nmax ; i++) {
      spacing = (b-a) / i;
      for (j = 0 ; j <= (i/2 - 1) ; j++) {
        sum += function(a + (2*j) * spacing) + 4 * function(a + (2*j+1) * spacing) + function(a + (2*j + 2) * spacing);
      }
      sum *= spacing/3;
      if (i%2 == 1) sum += (spacing/12)*(function(b) + 4 * function(b - (1 * spacing)) + function(b - (2 * spacing)));
      printf("%d %e %e\n", i, sum, fabs(sum - 3.349523597959926));
    }

    }

  return EXIT_SUCCESS;
}

double function(double x) {
  if(x == 0) return 1;
  else return sin(x)/x;
}
