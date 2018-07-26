/*
		  Harmonic Oscillator
		  Mario Ambrosino v.1.0 13/06/2018

		 Arguments:
     [1] (INT): max step solution EPOCH;
     [2] (FLOAT): initial position;
     [3] (FLOAT): initial velocity;
     [4] (FLOAT): dt width;
     [5] (FLOAT): beta;
     [6] (FLOAT): omega;
     [7] (INT): method;
     [8] (CHAR): name file
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct particle_struct {
	double *tm;
	double *ps;
	double *vl;
	double *trps;
	int Dim;
}; typedef struct particle_struct particle;

// prototipi funzioni
particle new_4D_particle(int New_Dimension, particle Input);
void Export_4D_particle(particle Input, char name_file[255]);
void true_ps(double omega, int step, double dt, particle ho);
double dyn_funct(double omega, double y, double v);
void harmonic_oscillator_dynamic_step(particle ho, int step, float dt, float omega, int method);

int main(int argc, char *argv[]) {

  long int step = 0;
	int epoch = atoi(argv[1]);
  int method = atoi(argv[7]);
  particle ho = new_4D_particle(epoch, ho);
  //Acquisizione indirizzo output
  size_t len = strlen(argv[8]);
  char * name_file = malloc(len+1);
  if(name_file == NULL) return EXIT_FAILURE;
  strcpy(name_file, argv[8]);
  //inizializzazione della dinamica
  double dt = atof(argv[4]);                      // passo temporale
  double omega = atof(argv[6]);                   // frequenza dell'oscillatore
  double start = 0;                               // variabili per timing
  double a = 0;                                   // variabili per timing
  double stop = 0;                                // variabili per timing
  ho.ps[0] = atof(argv[2]);                       // posizione iniziale del sist.
  ho.vl[0] = atof(argv[3]);                       // velocità iniziale del sist.

  //dinamica
  start = clock();
  for(step = 0 ; step < epoch - 1 ; step++) {
    harmonic_oscillator_dynamic_step(ho, step, dt, omega, method);
  }

  stop = clock();
  a = (stop - start) * 1000 / CLOCKS_PER_SEC;
  Export_4D_particle(ho, name_file);
  printf("\nIntegration Completed.\nMethod: %i\nTiming: %lf ms\n", method, a);
  return 0;
}

/* FUNZIONI */

void true_ps(double omega, int step, double dt, particle ho) {
  // valutiamo 2E / m
  ho.trps[step] = sqrt(pow((ho.ps[0]),2)+pow((ho.vl[0]/sqrt(omega)),2)) *cos(sqrt(omega)*dt*step + atan(-ho.vl[0]/(sqrt(omega)*ho.ps[0])));
}

double dyn_funct(double omega, double y, double v) {
  return (- omega * y);
}

void harmonic_oscillator_dynamic_step(particle ho, int step, float dt, float omega, int method) {
  int i = 0;
  if (method == 1) {
    // metodo di Eulero
    ho.vl[step+1] = ho.vl[step] + dt * dyn_funct(omega, ho.ps[step], ho.vl[step]);
    ho.ps[step+1] = ho.ps[step] + dt * ho.vl[step];
    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }
  if (method == 2) {
    // metodo di Eulero - Cromer
    ho.vl[step+1] = ho.vl[step] + dt * dyn_funct(omega, ho.ps[step], ho.vl[step]);
    ho.ps[step+1] = ho.ps[step] + dt * ho.vl[step+1];
    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }
  if (method == 3) {
    // metodo Picard con Starter Eulero iterato per 3 volte con integrazione.
      // Starter: Eulero
    ho.vl[step+1] = ho.vl[step] + dt * dyn_funct(omega, ho.ps[step], ho.vl[step]);
    ho.ps[step+1] = ho.ps[step] + dt * ho.vl[step];
      //Iterazione Picard per 3 volte
    for (i = 0; i < 3; i++) {
      ho.vl[step+1] = ho.vl[step] + dt * 0.5 * ( dyn_funct(omega, ho.ps[step+1],
                       ho.vl[step]) + dyn_funct(omega, ho.ps[step], ho.vl[step]));
      ho.ps[step+1] = ho.ps[step] + dt * 0.5 * ( ho.vl[step+1] + ho.vl[step] );
      }
    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }
  if (method == 4) {
    // metodo Predictor - Corrector: Predictor Eulero Rettangolo, Corrector Eulero Trapezio
    //Predictor: Eulero Rettangolare
    ho.vl[step+1] = ho.vl[step] + dt * dyn_funct(omega, ho.ps[step], ho.vl[step]);
    ho.ps[step+1] = ho.ps[step] + dt * ho.vl[step];
    //Corrector: Eulero Trapezio
    ho.vl[step+1] = ho.vl[step] + dt * 0.5 * ( dyn_funct(omega, ho.ps[step+1],
                     ho.vl[step+1]) + dyn_funct(omega, ho.ps[step], ho.vl[step]));
    ho.ps[step+1] = ho.ps[step] + dt * 0.5 * ( ho.vl[step+1] + ho.vl[step] );
    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }
  if (method == 5) {
    // RUNGE-KUTTA del secondo ordine
    double C1_ps = dt * ho.vl[step];
    double C1_vl = dt * dyn_funct(omega, ho.ps[step], ho.vl[step]);

    ho.ps[step+1] = ho.ps[step] + (ho.vl[step] + 0.5 * C1_vl) * dt;
    ho.vl[step+1] = ho.vl[step] + dyn_funct(omega, ho.ps[step] + 0.5 * C1_ps , ho.vl[step] + 0.5 * C1_vl) * dt;

    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }

  if (method == 6) {
    // RUNGE-KUTTA del quarto ordine
    //variabili associate alla posizione

    double k1_ps = ho.vl[step];
		double k1_vl = dyn_funct(omega, ho.ps[step], ho.vl[step]);

		double k2_ps = (ho.vl[step] + dt * 0.5 * k1_vl);
		double k2_vl = dyn_funct(omega, (ho.ps[step] + 0.5 * dt * k1_ps), ho.vl[step]);

		double k3_ps = (ho.vl[step] + dt * 0.5 * k2_vl);
		double k3_vl = dyn_funct(omega, (ho.ps[step] + 0.5 * dt * k2_ps), ho.vl[step]);

		double k4_ps = (ho.vl[step] + dt * k3_vl);
    double k4_vl = dyn_funct(omega, (ho.ps[step] + dt * k3_ps), ho.vl[step]);

    ho.ps[step+1] = ho.ps[step] + dt *(k1_ps + 2*k2_ps + 2*k3_ps + k4_ps) / 6;
    ho.vl[step+1] = ho.vl[step] + dt * (k1_vl + 2*k2_vl + 2*k3_vl + k4_vl) / 6;

    true_ps(omega, step, dt, ho);
    ho.tm[step+1] = dt * (step+1);
  }
}

// inclusione manuale

particle new_4D_particle(int New_Dimension, particle Input) {
	Input.Dim = New_Dimension;
//	printf("\nparticle[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.tm = (double *) calloc(Input.Dim, sizeof(double));
if (Input.tm == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
	exit(EXIT_FAILURE);
	}
	Input.ps = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.ps == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.vl = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.vl == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	Input.trps = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.trps == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

void Export_4D_particle(particle Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim - 1; i++) {
		fprintf(input_file, "%lf %lf %lf %lf\n", Input.tm[i], Input.ps[i], Input.vl[i], fabs(Input.ps[i]-Input.trps[i]));
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}
