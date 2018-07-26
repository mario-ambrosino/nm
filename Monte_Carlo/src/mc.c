/*
  Programma valutazione e confronto dei metodi di Montecarlo diretto e
  Metropolis

  Argomenti:

  [1] (int) modalità di integrazione MC - 0: diretto, 1: Metropolis
  [2] (float) estremo a;
  [3] (float) estremo b;
  [4] (int) numero di campionamenti;
  [5] (int) numero di salti (METROPOLIS)
  [6] (float) passo h (METROPOLIS)
  [5] (float)

*/
#include "./inc/lib_montecarlo.c"

double function(double x) {
  return x*x;
}

int main(int argc, char *argv[]) {

  int mode = atoi(argv[1]);
  double a = atof(argv[2]);
  double b = atof(argv[3]);
  int N = atoi(argv[4]);
  int nskip = atoi(argv[5]);
  double h = atof(argv[6]);

  double S = 0.;
  double dS = 0.;
  double accept = 100.;

  if (mode == 0) {
    MC_0(&S, &dS, a, b, N, function);
  }

  else if (mode == 1) {
      double z = 0.46265167; // valido solo per l'integrazione in [0:1]
  //  double z = integration_trpz(MC_1_W, 10000000, a, b);
  //  printf("Z = %f \n", z);
    accept = MC_1(&S, &dS, a, b, N, nskip, h, function, MC_1_W, z);
  }

  //printf("M = %d N = 1%d Accept: %f; %f %f\n", mode, N, accept, S, dS);
  printf("%f; %d %f %f\n",accept, N, fabs(S - 0.3333333333333), dS);

  return EXIT_SUCCESS;
}
