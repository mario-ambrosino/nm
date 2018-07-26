/*
  Programma per effettuare integrazione adattiva utilizzando la regola di Simpson
  Mario Ambrosino - 02 Giugno 2018

  Variabili: [1] FLOAT Controllo Errore
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// parametri fissati

#define MIN 0
#define MAX M_PI / 2
#define RESULT 1
#define MAX_ITERATION 10025

  double func(double x);
  double Simpson0(double h, double fa, double fb, double fc);
  double Simpson1(double h, double fa, double fb, double fc, double fd, double fe);
  void hilbert_extend (int order, double data[2][MAX_ITERATION]);
  double average(double a, double b);

  int main(int argc, char **argv) {

    int i;
    double error = atof(argv[1]);

    double data[2][MAX_ITERATION];
    double order = 2;
    double h = MAX - MIN;
    double s0, s1;

    // init
    data[0][0] = MIN;
    data[0][4] = MAX;
    data[0][2] = average(data[0][0],data[0][4]);
    data[0][1] = average(data[0][0],data[0][2]);
    data[0][3] = average(data[0][2],data[0][4]);

    data[1][0] = func(data[0][0]);
    data[1][1] = func(data[0][1]);
    data[1][2] = func(data[0][2]);
    data[1][3] = func(data[0][3]);
    data[1][4] = func(data[0][4]);

    s0 = Simpson0(h, data[1][0], data[1][2], data[1][4]);
    s1 = Simpson1(h, data[1][0], data[1][1], data[1][2], data[1][3], data[1][4]);

    //ciclo
    while (fabs(s1-s0) >= error) {
      s0 = 0, s1 = 0;
      hilbert_extend(order, data);
      order++;

      for (i = 0; i < order; i++) {
        h = data[0][2]-data[0][0];
        s0 += Simpson0(data[0][2]-data[0][0], data[1][4*i], data[1][4*i+2], data[1][4*i+4]);
        s1 += Simpson1(data[0][1]-data[0][0], data[1][4*i], data[1][4*i+1], data[1][4*i+2], data[1][4*i+3],data[1][4*i+4]);
        printf("%i - %lf ; %lf\n",i ,s0, s1);
        printf("Punti: %lf, %lf, %lf, %lf, %lf \n", data[1][0], data[1][1], data[1][2], data[1][3], data[1][4]);
        }
    }
    return EXIT_SUCCESS;
}

  //Funzione da integrare.
double func(double x) {
  return sin(x);
}

double Simpson0(double h, double fa, double fb, double fc){
  return h*(fa+4*fb+fc)/6;
}

double Simpson1(double h, double fa, double fb, double fc, double fd, double fe){
  return h*(fa+4*fb+2*fc+4*fd+fe)/12;
}

void hilbert_extend (int order, double data[2][MAX_ITERATION]) {
  int i;
  // fase di copia
  for(i = order ; i >= 0 ; i--) {
    data[0][2*i] = data[0][i];
    data[1][2*i] = data[1][i];
  }

  // scrittura dei nuovi valori
  for(i = 0 ; i < order ; i++) {
    data[0][2*i+1] = average(data[0][2*i], data[0][2*i+2]);
    data[1][2*i+1] = func(data[0][2*i+1]);
  }
}

double average(double a, double b) {
  return (a+b)/2;
}
