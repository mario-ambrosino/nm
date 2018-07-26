//DERIVAZIONE

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

//INTEGRAZIONE

double integration_rect(double (*f)(double), int npoints, double a, double b) {
  int j;
  double sum = 0;
  double spacing = (b-a)/npoints;
  for (j = 0; j < npoints-1; j++) {
    sum += function(a+j*spacing);
  }
  sum *= spacing;
  return sum;
  }

double integration_trpz(double (*f)(double), int npoints, double a, double b) {
  int j;
  double sum = 0;
  double spacing = (b-a)/npoints;
  for (j = 0; j < npoints-1; j++) {
    sum += function(a+j*spacing) + function(a+(j+1)*spacing);
  }
  sum *= 0.5 * spacing;
  return sum;
  }

double integration_simp(double (*f)(double), int npoints, double a, double b) {
  int j;
  double sum = 0;
  double spacing = (b-a)/npoints;
  for (j = 0 ; j <= (npoints/2 - 1) ; j++) {
    sum += function(a + (2*j) * spacing) + 4 * function(a + (2*j+1) * spacing) + function(a + (2*j + 2) * spacing);
  }
  sum *= spacing/3;
  if (npoints%2 == 1) sum += (spacing/12)*(function(b) + 4 * function(b - (1 * spacing)) + function(b - (2 * spacing)));
  return sum;
}
