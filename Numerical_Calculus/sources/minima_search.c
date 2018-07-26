#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
  Programma per la ricerca del minimo di funzioni utilizzando
  il metodo di discesa del gradiente

  Variabili:
  [1]: (FLOAT)  posizione iniziale
  [2]: (FLOAT)  precisione numerica
  [3]: (LONG)   passo i-mo
  [4]; (LONG)   massimo numero di iterazioni

*/
double func(double x);
double NumDer(double (*f)(double), double x);
double gradesc(double (*f)(double), double x, double error, double mult, long max_step);


int main(int argc, char **argv) {
    double x = atof(argv[1]); // posizione iniziale del "cursore"
    double err = atof(argv[2]); // precisione numerica
    double mult = atof(argv[3]); // larghezza passo i-mo
    long max_step = atoi(argv[4]); //massimo numero di iterazioni
    printf("Minimum located at: %f\n", gradesc(func, x, err, mult, max_step));
    return EXIT_SUCCESS;
}


double func(double x) {
  return pow(x,4) + 5*pow(x,3) + 2*pow(x,2) + 2*x + 1;
}

double NumDer(double (*f)(double), double x) {
  // NumDerazione utilizzando il metodo a tre punti
  double h = 1e-4;
  return (f(x+h)-f(x-h))/(2*h);
  }

double gradesc(double (*f)(double), double x, double error, double mult, long max_step) {
    double curr_err = error + 1; // rende vera la condizione del primo while
    long step = 0;
    double prev;
    while((error < curr_err) && (step < max_step)) {
        prev = x;
        x -= NumDer(f, x) * mult / (step + 1);                         // discesa del gradiente
	      curr_err = fabs(prev-x);
        printf("\n%li %f %f", step, x, curr_err);
        step++;
    }
    return x;
}
