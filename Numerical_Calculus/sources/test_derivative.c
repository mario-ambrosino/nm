#include <stdio.h>
#include <stdlib.h>
#include <math.h>

  /*
    Programma per confrontare vari metodi di derivazione.
    Le funzioni saranno built-in modo da migliorare la portabilità dell'esegui-
    bile. Saranno presenti le seguenti realizzazioni:

    Per la derivazione al primo ordine:
    - Formula a due punti
    - Formula a tre punti
    - Formula a cinque punti

    Per la derivazione al secondo ordine:
    - Formula a tre punti
    - Formula a cinque punti.

    Cercherò di realizzare anche una sorta di calcolo del residuo medio tramite
    script associati.
    Non introdurrò controlli sulla regolarità della funzione.

    ## Argomenti
    1) INTEG metodo di derivazione MODE
    2) FLOAT spaziatura dei punti SPACING
    Mario Ambrosino - 31 Maggio 2018
  */
  //PROTOTIPI
  double func(double x);
  double dfunc(double x);
  double ddfunc(double x);

  double derive12(double (*f)(double), double x, double h);
  double derive13(double (*f)(double), double x, double h);
  double derive15(double (*f)(double), double x, double h);
  double derive23(double (*f)(double), double x, double h);
  double derive25(double (*f)(double), double x, double h);

  // Corpo del listato
  int main(int argc, char **argv) {
    int mode = atoi(argv[1]);
    double spacing = atof(argv[2]);
    double point = - M_PI;
    double derivative = 0.;
    double residual = 0.;
    int i;

    //Selezione della modalità di funzionamento: effettua la derivata e valuta il
    //residuo.
    for (i = 0; i < 25; i++) {
      if (mode == 1) {
        derivative = derive12(func, point, spacing);
        residual = derivative - dfunc(point);
      }
      else if (mode == 2) {
        derivative = derive13(func, point, spacing);
        residual = derivative - dfunc(point);
      }
      else if (mode == 3){
        derivative = derive15(func, point, spacing);
        residual = derivative - dfunc(point);
      }
      else if (mode == 4){
        derivative = derive23(func, point, spacing);
        residual = derivative - ddfunc(point);
      }
      else if (mode == 5){
        derivative = derive25(func, point, spacing);
        residual = derivative - ddfunc(point);
      }
      else {
        printf("Wrong Mode selected. Closing...");
        return EXIT_FAILURE;
      }
      printf("M:%i; S:%e; D:%f; %e; %e;\n", mode, spacing, point, derivative, residual);
      point += M_PI / 12. ;
    }
          return EXIT_SUCCESS;
  }
  //Funzione da derivare.
double func(double x) {
  return sin(x);
}
double dfunc(double x) {
  // Derivata prima teorica.
    return cos(x);
  }
  // Derivata seconda teorica.
double ddfunc(double x) {
    return -sin(x);
  }
  // Formula primo ordine - due punti - MODE 1
double derive12(double (*f)(double), double x, double h) {
  return (f(x+h)-f(x))/h;
}
  // Formula primo ordine - tre punti - MODE 2

double derive13(double (*f)(double), double x, double h) {
  return (f(x+h)-f(x-h))/(2*h);
  }
  // Formula primo ordine - cinque punti - MODE 3
double derive15(double (*f)(double), double x, double h) {
  return (f(x+2*h)+8*f(x+h)-8*f(x-h)-f(x-2*h))/(12*h);
  // ACHTUNG!!! La derivazione con questo metodo dilata la derivata di un fatto-
  // re di 3/2. TODO Da correggere. Sembra essere corretto utilizzando 20 invece
  // di 12.
  }
  // Formula secondo ordine - tre punti - MODE 4
  double derive23(double (*f)(double), double x, double h) {
    return (f(x+h)-2*f(x)+f(x-h))/(h*h);
    }
  // Formula secondo ordine - cinque punti - MODE 5
  double derive25(double (*f)(double), double x, double h) {
    return (-f(x+2*h)+16*f(x+h)-30*f(x)+16*f(x-h)-f(x-2*h))/(12*h*h);
    }
