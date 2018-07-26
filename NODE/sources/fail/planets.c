/*
		  Harmonic Oscillator
		  Mario Ambrosino v.1.0 15/06/2018

		 Arguments:
     [1] (INT): max step solution EPOCH;
     [2] (FLOAT): initial position;
     [3] (FLOAT): initial velocity;
     [4] (FLOAT): dt width;
     [5] (FLOAT): alpha;
     [6] (FLOAT): beta;
		 [7] (FLOAT): gamma;
		 [8] (FLOAT): ampl;
     [9] (INT): method;
     [10] (CHAR): name file
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct pendulum_struct {
	double *tm;
	double *theta;
	double *vl;
	double *en;
	int Dim;
}; typedef struct pendulum_struct pendulum;

// prototipi funzioni
pendulum new_4D_pendulum(int New_Dimension, pendulum Input);
void Export_4D_pendulum(pendulum Input, char name_file[255]);
void energy(double alpha, int time, pendulum pnd);
double dyn_funct(double ampl, double gamma, double alpha, double y, double beta, double v, double t);
void harmonic_oscillator_dynamic_step(pendulum pnd, int step, double dt, double alpha, double beta, double gamma, double ampl, int method);

int main(int argc, char *argv[]) {

  long int step = 0;
	int epoch = atoi(argv[1]);
  pendulum pnd = new_4D_pendulum(epoch, pnd);
	pendulum space = new_4D_pendulum(epoch, space);
  //Acquisizione indirizzo output
  size_t len = strlen(argv[10]);
  char * name_file = malloc(len+1);
  if(name_file == NULL) return EXIT_FAILURE;
  strcpy(name_file, argv[10]);

  //inizializzazione della dinamica
  double alpha = atof(argv[5]);                   // frequenza dell'oscillatore
	double beta = atof(argv[6]);                    // coefficiente di smorzamento
	double gamma = atof(argv[7]);										// frequenza della forzante
	double ampl = atof(argv[8]);										// ampiezza della forzante
	double dt = atof(argv[4]);                      // passo temporale
	int method = atoi(argv[9]);											// metodo di soluzione n.ODE
	double start = 0;                               // variabili per timing
  double a = 0;                                   // variabili per timing
  double stop = 0;                                // variabili per timing
  pnd.theta[0] = atof(argv[2]);                       // posizione iniziale del sist.
  pnd.vl[0] = atof(argv[3]);                       // velocità iniziale del sist.

  //dinamica
  start = clock();
  for(step = 0 ; step < epoch - 1 ; step++) {
    harmonic_oscillator_dynamic_step(pnd, step, dt, alpha, beta, gamma, ampl, method);
  }

  stop = clock();
  a = (stop - start) * 1000 / CLOCKS_PER_SEC;
	for(step = 0 ; step < epoch ; step++) {
		space.tm[step] = pnd.tm[step];
		space.theta[step] = cos(pnd.theta[step]);
		space.vl[step] = sin(pnd.theta[step]);
	}

  Export_4D_pendulum(pnd, name_file);
	Export_4D_pendulum(space, strcat(name_file, "acart"));
  printf("\nIntegration Completed.\nmethod: %i\nTiming: %lf ms\n", method, a);
  return 0;
}

/* FUNZIONI */

void energy(double alpha, int step, pendulum pnd) {
  // valutiamo 2E / m
  pnd.en[step] = pnd.vl[step]*pnd.vl[step] + alpha*pnd.theta[step]*pnd.theta[step];
}

double dyn_funct(double ampl, double gamma, double alpha, double y, double beta, double v, double t) {
  return (- alpha * sin(y) - beta * v + ampl * cos(gamma * t));
}

void harmonic_oscillator_dynamic_step(pendulum pnd, int step, double dt, double alpha, double beta, double gamma, double ampl, int method) {
  int i = 0;
  if (method == 1) {
    // metodo di Eulero
    pnd.vl[step+1] = pnd.vl[step] + dt * dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]);
    pnd.theta[step+1] = pnd.theta[step] + dt * pnd.vl[step];
    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }
  if (method == 2) {
    // metodo di Eulero - Cromer
    pnd.vl[step+1] = pnd.vl[step] + dt * dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]);
    pnd.theta[step+1] = pnd.theta[step] + dt * pnd.vl[step+1];
    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }
  if (method == 3) {
    // metodo Picard con Starter Eulero iterato per 3 volte con integrazione.
      // Starter: Eulero
    pnd.vl[step+1] = pnd.vl[step] + dt * dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]);
    pnd.theta[step+1] = pnd.theta[step] + dt * pnd.vl[step];
      //Iterazione Picard per 3 volte
    for (i = 0; i < 3; i++) {
      pnd.vl[step+1] = pnd.vl[step] + dt * 0.5 * ( dyn_funct(ampl, gamma, alpha, pnd.theta[step+1], beta,
                       pnd.vl[step+1], pnd.tm[step]+dt) + dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta,pnd.vl[step], pnd.tm[step]));
      pnd.theta[step+1] = pnd.theta[step] + dt * 0.5 * ( pnd.vl[step+1] + pnd.vl[step] );
      }
    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }
  if (method == 4) {
    // metodo Predictor - Corrector: Predictor Eulero Rettangolo, Corrector Eulero Trapezio
    //Predictor: Eulero Rettangolare
    pnd.vl[step+1] = pnd.vl[step] + dt * dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]);
    pnd.theta[step+1] = pnd.theta[step] + dt * pnd.vl[step];
    //Corrector: Eulero Trapezio
    pnd.vl[step+1] = pnd.vl[step] + dt * 0.5 * ( dyn_funct(ampl, gamma, alpha, pnd.theta[step+1], beta,
                     pnd.vl[step+1], pnd.tm[step] + dt) + dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]));
    pnd.theta[step+1] = pnd.theta[step] + dt * 0.5 * ( pnd.vl[step+1] + pnd.vl[step] );
    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }
  if (method == 5) {
    // RUNGE-KUTTA del secondo ordine
    double C1_theta = dt * pnd.vl[step];
    double C1_vl = dt * dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step] + 0.5 * dt);

    pnd.theta[step+1] = pnd.theta[step] + (pnd.vl[step] + 0.5 * C1_vl) * dt;
    pnd.vl[step+1] = pnd.vl[step] + dyn_funct(ampl, gamma, alpha, pnd.theta[step] + 0.5 * C1_theta, beta, pnd.vl[step] + 0.5 * C1_vl, pnd.tm[step] + 0.5 * dt) * dt;

    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }

  if (method == 6) {
    // RUNGE-KUTTA del quarto ordine
    //variabili associate alla posizione

    double k1_theta = pnd.vl[step];
		double k1_vl = dyn_funct(ampl, gamma, alpha, pnd.theta[step], beta, pnd.vl[step], pnd.tm[step]);

		double k2_theta = (pnd.vl[step] + dt * 0.5 * k1_vl);
		double k2_vl = dyn_funct(ampl, gamma, alpha, pnd.theta[step] + 0.5 * dt * k1_theta, beta, k2_theta, pnd.tm[step] + 0.5 * dt);

		double k3_theta = (pnd.vl[step] + dt * 0.5 * k2_vl);
		double k3_vl = dyn_funct(ampl, gamma, alpha, pnd.theta[step] + 0.5 * dt * k2_theta, beta,  k3_theta, pnd.tm[step] + 0.5 * dt);

		double k4_theta = (pnd.vl[step] + dt * k3_vl);
    double k4_vl = dyn_funct(ampl, gamma, alpha, pnd.theta[step] + dt * k3_theta, beta, k4_theta, pnd.tm[step] + dt);

    pnd.theta[step+1] = pnd.theta[step] + dt *(k1_theta + 2*k2_theta + 2*k3_theta + k4_theta) / 6;
    pnd.vl[step+1] = pnd.vl[step] + dt * (k1_vl + 2*k2_vl + 2*k3_vl + k4_vl) / 6;

    energy(alpha, step, pnd);
    pnd.tm[step+1] = dt * (step+1);
  }
}

// inclusione manuale

pendulum new_4D_pendulum(int New_Dimension, pendulum Input) {
	Input.Dim = New_Dimension;
//	printf("\npendulum[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.tm = (double *) calloc(Input.Dim, sizeof(double));
if (Input.tm == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
	exit(EXIT_FAILURE);
	}
	Input.theta = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.theta == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.vl = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.vl == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	Input.en = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.en == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

void Export_4D_pendulum(pendulum Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf %lf %lf %lf\n", Input.tm[i], Input.theta[i], Input.vl[i], Input.en[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}
