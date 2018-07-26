#include "./inc/lib_random.c"

void MC_0(double *S, double *dS, double a, double b, int N, double (*f)(double));
double MC_1(double *S, double *dS, double a, double b, int N, int nskip, double h, double (*func)(double), double (*W)(double), double z);
void MC_1_step(double a, double b, double h, double *x, double * w, int *iaccept, RANDOM *seed);
double MC_1_W(double x);
double integration_trpz(double (*f)(double), int npoints, double a, double b);

//direct Monte Carlo Method
void MC_0(double *S, double *dS, double a, double b, int N, double (*f)(double)) {
  int i = 0;

  //Scelta del SEED
  struct timeval tv;
  gettimeofday(&tv, 0);
  RANDOM seed = -tv.tv_usec;

  double x;

  for (i = 0; i < N; i++) {
    x = a + (b - a) * RAN2(&seed);
    *S += f(x);
    *dS += (f(x)) * (f(x));
  }
  *S *= (b - a) / N;;
  *dS /= N;
  *dS = sqrt(fabs(*dS - *S * (*S)) / (N));
}

//Metropolis Monte Carlo Method
double MC_1(double *S, double *dS, double a, double b, int N, int nskip, double h, double (*func)(double), double (*W)(double), double z) {

  int i, iaccept = 0;
  int ntotal = N * nskip;
  double x, w, g;

  //Scelta del SEED
  struct timeval tv;
  gettimeofday(&tv, 0);
  RANDOM seed = -tv.tv_usec;

  x = (b-a)*RAN2(&seed);
  w = MC_1_W(x);

  for (i = 0; i < ntotal; i++) {
    MC_1_step(a, b, h, &x, &w, &iaccept, &seed);
    if(i%nskip == 0) {
      g = func(x) / MC_1_W(x);
      *S = *S + g;
      *dS = *dS + g*g;
    }
  }
  *S = *S / (double) N;
  *dS /= (double) N;
  *dS = sqrt(fabs(*dS - (*S) * (*S)) / (N));
  *S *= z;
  *dS *= z;
  double accept = 100.0 * (iaccept) / ntotal;
  return accept;
}

  void MC_1_step(double a, double b, double h, double *x, double * w, int *iaccept, RANDOM *seed) {
    double x_old = *x;
    *x = (*x) + 2 * h * (RAN2(seed) - 0.5);
    if (((*x)<a) || ((*x)>b)) (*x) = x_old;
    else {
      double wnew = MC_1_W((*x));
      if (wnew / (*w) > RAN2(seed)) {
        (*w) = wnew;
        (*iaccept) = (*iaccept) + 1;
      }
      else {
        (*x) = x_old;
      }
  }
}

double MC_1_W(double x){
  return exp(x*x)-1;
}

double integration_trpz(double (*f)(double), int npoints, double a, double b) {
  int j;
  double sum = 0;
  double spacing = (b-a)/npoints;
  for (j = 0; j < npoints-1; j++) {
    sum += f(a+j*spacing) + f(a+(j+1)*spacing);
  }
  sum *= 0.5 * spacing;
  return sum;
}
