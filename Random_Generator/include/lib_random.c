#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "./include/lib_data.c"
#include <time.h>
#include <sys/time.h>

// GENERATORI LINEARI CONGRUENZIALI

typedef long long int RANDOM;

/*
	RANDU:
	Generatore RANDU.
	Fonte: P.S. p.283
*/

//DEFINIZIONI RANDU
#define MASK 123459876
#define A_DU 65539
#define M_DU 2147483648
#define FACTOR_DU (1.0/M_DU)

double RANDU(RANDOM *csi) {
	*csi ^= MASK;
	*csi = (A_DU * (*csi)) % M_DU;
	if (*csi < 0) *csi += M_DU;
	*csi ^= MASK;
	return *csi * FACTOR_DU;
}

/*
	RAN0:
	Generatore Minimal Standard di Park e Miller.
	Fonte: P.S. p.282
*/

//DEFINIZIONI DEL GENERATORE RAN0
#define A_0 16807
#define M_0 2147483647
#define Q_0 127773
#define R_0 2836
#define FACTOR_0 (1.0/M_0)

double RAN0_Simple(RANDOM *csi) {
	*csi ^= MASK;
	*csi = (A_0 * (*csi)) % M_0;
	if (*csi < 0) *csi += M_0;
	*csi ^= MASK;
	return *csi * FACTOR_0;
}

/* RAN0: Generatore Minimal Standard di Park e Miller con metodo di Schrage
	Fonte: N.R in C p.279 */

double RAN0_Schrage(RANDOM *csi) {
	long k;
	double output;
	*csi ^= MASK;
	k = (*csi) / Q_0;
	*csi = A_0 * ( (*csi) - Q_0 * k) - (k * R_0);
	if (*csi < 0) *csi += M_0;
	*csi ^= MASK;
	output = (*csi) * FACTOR_0;
	return output;
}

/*
	RAN1:
	Generatore Minimal Standard di Park e Miller n e con algoritmo di shuffling di Bays - Durham.
	La peculiarità di questo algoritmo sta nella richiesta di venire inizializato da un intero negativo.
	Fonte: N.R in C p.280
*/

	//PARAMETRI DEL GENERATORE RAN1
	#define A_1 16807
	#define M_1 2147483647
	#define Q_1 127773
	#define R_1 2836
	//PARAMETRI AGGIUNTIVI
	#define FACTOR_1 (1.0/M_1)
	#define NTAB 32
	#define NDIV (1+(M_1-1)/(NTAB))
	#define EPS 1.2e-16 //Corretto per i double
	#define RNMX (1.0-EPS)

double RAN1(RANDOM *csi) {
	//VARIABILI
	double output;
	long k;
	int j;
	static long y;
	static long T[NTAB];

	if ((*csi <= 0) || (!y)) {	// csi < 0 ==> inizializzazione
		if(-(*csi) < 1) *csi = 1;
		else *csi = -(*csi);
		for (j= NTAB + 7 ; j >= 0 ; j--) {
			k = (*csi) / Q_1;
			*csi = A_1 * ( (*csi) - k *  Q_1) - k * R_1;
			if (*csi < 0) *csi += M_1;
			if (j < NTAB) T[j] = *csi;	//dopo 7 giri a vuoto inizia a scrivere la tabella
		}
		y = T[0];
	}
	//LCG CORE Post inizializzazione
	k = (*csi) / Q_1;
	*csi = A_1 * ((*csi) % Q_1) - k * R_1;
	if (*csi < 0) *csi += M_1;
	//Shuffle - cfr. report
	j = y / NDIV;
	y = T[j];
	T[j] = *csi;
	if ((output = (*csi) * FACTOR_1) > RNMX) return RNMX;
	else return output;
}

/*
	RAN2:
	Generatore Minimal Standard di L'Ecuyer con metodo di Schrage e con algoritmo di shuffling di Bays - Durham
	Fonte: N.R in C p.280
*/

	//PARAMETRI DEL GENERATORE RAN2
	#define A_E1 40014
	#define A_E2 40692

	#define M_E1 2147483563
	#define M_E2 2147483399
	#define Q_E1 53668
	#define Q_E2 52774
	#define R_E1 12211
	#define R_E2 3791
	#define FACTOR_2 (1.0/M_E1)

	//DEFINIZIONI AGGIUNTIVE DEL GENERATORE RAN2
	#define T1 (M_E1-1)
	#define NDIV_2 (1+T1/NTAB)


double RAN2(RANDOM *csi) {
	//VARIABILI
	double output;
	RANDOM csi2 = 123456789;
	long k;
	int j;
	static long y;
	static long T[NTAB];

	//
	if ((*csi <= 0)) {	// csi < 0 ==> inizializzazione
		if(-(*csi) < 1) *csi = 1;	// se è pari a 0 lo riassegna al valore 1
		else *csi = -(*csi);
		csi2 = *csi;
		for (j= NTAB + 7 ; j >= 0 ; j--) {
			// LCG CORE
			k = (*csi) / Q_E1;
			*csi = A_E1 * (*csi - k * Q_E1) - k * R_E1;
			if (*csi < 0) *csi += M_E1;
			// LCG CORE
			if (j < NTAB) T[j] = *csi;	//dopo 7 giri a vuoto inizia a scrivere la tabella
		}
		y = T[0];
	}
	//LCG CORE 1
	k = (*csi) / Q_E1;
	*csi = A_E1 * (*csi - k * Q_E1) - (k * R_E1);
	if (*csi < 0) *csi += M_E1;

	//LGC CORE 2
	k = (csi2) / Q_E2;
	csi2 = A_E2 * (csi2 - k * Q_E2) - (k * R_E2);
	if (csi2 < 0) csi2 += M_E2;

	//Shuffle
	j = y / NDIV_2;
	y = T[j] - csi2;  //sottrae invece di aggiungere
	T[j] = *csi;
	if (y < 1) y += T1;
	if ((output = *csi * FACTOR_2) > RNMX) return RNMX;
	else return output;
}

// FINE GLC

// NON-UNIFORM GENERATORS

//Fa uso di L'Ecuyer e utilizza direttamente le funzioni trigonometriche.
double Normal_Random_1(RANDOM *csi) {
	double output;
	double r1 = RAN2(csi);
	double r2 = RAN2(csi);
	double y1 = sqrt(- 2.0 * log(r1)) * cos(2.0 * M_PI * r2);
	double y2 = sqrt(- 2.0 * log(r1)) * sin(2.0 * M_PI * r2);
	double rand = RAN2(csi);
	if (rand <= 0.5) output = y1;
	else output =  y2;
	return output;
}

//Generatore Polare di Marsaglia.
double Normal_Random_2(RANDOM *csi) {
	double r1  = 0, r2 = 0, s2 = 0, s = 0, output = 0;
	//Genera numeri nel quadrato [-1;1]x[-1;1] e scarta i punti fuori dal cerchio unitario
	do {
	r1 = 2 * RAN2(csi) - 1;
	r2 = 2 * RAN2(csi) - 1;
	s2 = r1 * r1 + r2 * r2;
	s = (s2); } while ((s2 >= 1.) || (s2 <= 0.));
	output =  sqrt(- 2.0 * log(s) / s) * r2;
	return output;
}

//Generatore di distribuzione esponenziale
double Exp_Random(RANDOM *csi, double lambda) {
	double  dummy = 0., output;
	do {dummy = RAN2(csi);} while (dummy == 0.);
	output =  -log(dummy);
	return output * lambda ;
}

//Generatore di punti gamma-distribuiti con tecnica di rigetto
double Gamma_Random(RANDOM *csi, int a) {
	// definizioni
	int j;
	double x, y, v1, v2, e, s, m;
	// controllo positività parametro "a"
	if (a < 1) return EXIT_FAILURE;
	// per parametri piccoli utilizza semplicemente la funzione esponenziale
	if (a < 6) {
		x = 1.0;
		for (j = 1; j <= a; j++) x *= RAN2(csi);
		x = -log(x);
	} else {
		do {
			do {
				do {
					v1 = RAN2(csi);
					v2 = 2.0 * RAN2(csi) - 1.0;
				} while (v1*v1 + v2*v2 > 1.0);
				y = v2/v1; // ha generato il valore di una funzione tangente
				m = a - 1;
				s = sqrt(2.0*m - 1.0);
				x = s + y*m;
			} while (x <= 0.0);
			e = (1.0 + y*y)*exp(m*log(x/m)-s*y);
		} while (RAN2(csi) > e);
	}
	return x;
}

int coin_toss(int faces, RANDOM *csi) {
	return (int) faces * RAN2(csi);
}
