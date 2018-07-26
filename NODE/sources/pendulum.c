/*
		  Pendulum Simulator
		  Mario Ambrosino v.1.0 15/06/2018

		 Arguments:
     [1] (INT): max step solution EPOCH;
     [2] (FLOAT): initial position;
     [3] (FLOAT): initial velocity;
     [4] (FLOAT): dt width;
     [5] (FLOAT): k;
     [6] (FLOAT): gamma;
		 [7] (FLOAT): omega;
		 [8] (FLOAT): AA;
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
	int Dim;
}; typedef struct pendulum_struct pendulum;

// prototipi funzioni
pendulum new_4D_pendulum(int New_Dimension, pendulum Input);
void Export_4D_pendulum(pendulum Input, char name_file[]);
void energy(double k, int time, pendulum pnd);
double dyn_funct(double AA, double omega, double k, double y, double gamma, double v, double t);
void pendulum_dynamic_step(pendulum pnd, int step, double dt, double k, double gamma, double omega, double AA);

int main(int argc, char *argv[]) {

  long int step = 0;
	int epoch = atoi(argv[1]);
  pendulum pnd = new_4D_pendulum(epoch, pnd);

  //Acquisizione indirizzo output
  size_t len = strlen(argv[9]);
  char * name_file = malloc(len+1);
  if(name_file == NULL) return EXIT_FAILURE;
  strcpy(name_file, argv[9]);

  //inizializzazione della dinamica
  double k = atof(argv[5]);                   // frequenza dell'oscillatore
	double gamma = atof(argv[6]);                    // coefficiente di smorzamento
	double omega = atof(argv[7]);										// frequenza della forzante
	double AA = atof(argv[8]);										// ampiezza della forzante
	double dt = atof(argv[4]);                      // passo temporale
	double start = 0;                               // variabili per timing
  double a = 0;                                   // variabili per timing
  double stop = 0;                                // variabili per timing
  pnd.theta[0] = atof(argv[2]);                       // posizione iniziale del sist.
  pnd.vl[0] = atof(argv[3]);                       // velocità iniziale del sist.

  //dinamica
  start = clock();
  for(step = 0 ; step < epoch - 1 ; step++) {
    pendulum_dynamic_step(pnd, step, dt, k, gamma, omega, AA);
		if (step > 0) {
		pnd.theta[step-1] = (pnd.theta[step-1]+ M_PI) - 2*M_PI*floor((pnd.theta[step-1]+M_PI)/(2*M_PI));
  	}
	}

  stop = clock();
  a = (stop - start) * 1000 / CLOCKS_PER_SEC;

  Export_4D_pendulum(pnd, name_file);
  printf("\nIntegration Completed.\nTiming: %lf ms\n", a);
  return 0;
}

/* FUNZIONI */

double dyn_funct(double AA, double omega, double k, double y, double gamma, double v, double t) {
  return (- k * sin(y) - gamma * v + AA * cos(omega * t));
}

void pendulum_dynamic_step(pendulum pnd, int step, double dt, double k, double gamma, double omega, double AA) {
    // RUNGE-KUTTA del quarto ordine
    double k1_theta = pnd.vl[step];
		double k1_vl = dyn_funct(AA, omega, k, pnd.theta[step], gamma, pnd.vl[step], pnd.tm[step]);

		double k2_theta = (pnd.vl[step] + dt * 0.5 * k1_vl);
		double k2_vl = dyn_funct(AA, omega, k, pnd.theta[step] + 0.5 * dt * k1_theta, gamma, k2_theta, pnd.tm[step] + 0.5 * dt);

		double k3_theta = (pnd.vl[step] + dt * 0.5 * k2_vl);
		double k3_vl = dyn_funct(AA, omega, k, pnd.theta[step] + 0.5 * dt * k2_theta, gamma,  k3_theta, pnd.tm[step] + 0.5 * dt);

		double k4_theta = (pnd.vl[step] + dt * k3_vl);
    double k4_vl = dyn_funct(AA, omega, k, pnd.theta[step] + dt * k3_theta, gamma, k4_theta, pnd.tm[step] + dt);

    pnd.theta[step+1] = pnd.theta[step] + dt *(k1_theta + 2*k2_theta + 2*k3_theta + k4_theta) / 6;
    pnd.vl[step+1] = pnd.vl[step] + dt * (k1_vl + 2*k2_vl + 2*k3_vl + k4_vl) / 6;
		//correzione periodica da Tao Pang


    pnd.tm[step+1] = dt * (step+1);
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
	return Input;
}

void Export_4D_pendulum(pendulum Input, char name_file[]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf %lf %lf\n", Input.tm[i], Input.theta[i], Input.vl[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}
