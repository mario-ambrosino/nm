#include <stdio.h>
#include <stdlib.h>
#define N 100

void swap(double *a, double *b) {
double temp;
temp = *a;
*a = *b;
*b = temp;
}

void input_sqmatrix_HUM_SH(int *n, double matrix[N][N]) {
	int i, j, k;
	// controlli sull'immissione
	printf("\nRoutine di immissione elementi matriciali. MAX %ix%i\n", N, N);
	do {	*n = 0;
		k=0;
		printf("\nInserire il numero di equazioni del sistema lineare: ");
		scanf("%d",n);
		if ((*n <= 0)||(*n > N)) {
			k=0;
			printf("\nWARNING:\n Inserire un valore nel range (0,MAX). Prego riprova:\n");
			} else {k=1;}
		} while (!k);
	//scrittura matrice
	for (i=0; i < *n; i++) {
		for (j=0; j < *n; j++) {
			printf("\nM[%i,%i]: ", i, j);
			scanf("%lf", &matrix[i][j]);
			}
		}
	}

void input_array_fixed_n_HUM_SH(const int *n, double array[]) {
	int i;
	//scrittura vettore
	printf("\nRoutine di immissione componenti di un vettore a %d componenti\n", *n );
	for (i=0; i < *n; i++) {
		printf("\nVector[%i]: ", i);
		scanf("%lf", &array[i]);
		}
	}



void triangularize_matrix(const int *n, double A[][N], double b[]){

	double C;
	int i, j, k;

	for(i = 0; i < *n; i++) {
	//controllo sul pivot
		if (A[i][i]) {
			C = A[i][i];
	//divide la riga i-ma per il pivot
			for(j = i; j < *n; j++) {
				A[i][j] /= C;
				}
	//divide l'i-mo t.noto per il pivot
			b[i] /= C;
	//sottrae l'equazione normalizzata dalle altre'
				for(k = i+1; k < *n; k++) {
					C = A[k][i];
					for(j = i; j < *n; j++) {
						A[k][j] -= A[i][j]*C;
						}
					b[k] -= C*b[i];
					}
				}
		 else {				// nel caso il pivot fosse nullo
			for(j=i; j < *n; j++) {		// inverte le righe.
				swap(&A[i][j],&A[i+1][j]);
				}
			}
		}
	}

void linear_solution(const int *n, double A[][N], double b[], double x[]){
	int i, k;
	double S;
	for(k = *n-1; k >= 0; k--){
		S = 0.;
		for (i = k+1; i < *n; i++) {
			S += A[k][i] * x[i];
			}
		x[k] = b[k] - S;
		}
	}

void print_solution(const int *n, double x[]){
	int i;
	printf("\n\nSoluzione del sistema lineare:\n\n");
	for (i = 0; i < *n; i++) {
		printf("x[%d] = %lf\n", i, x[i]);
		}
	 }

int main(){
	int n;
	double x[N], b[N], a[N][N];
	printf("\nRisoluzione di un sistema lineare AX=B tramite metodo di Gauss.\nN. massimo di equazioni: 100\n");
	printf("\nInserire la matrice dei coefficienti\n\n");
	input_sqmatrix_HUM_SH(&n, a);
	printf("\nInserire il vettore colonna dei termini noti\n\n");
	input_array_fixed_n_HUM_SH(&n, b);
	triangularize_matrix(&n, a, b);
	linear_solution(&n, a, b, x);
	print_solution(&n, x);
	return 0;
	}
