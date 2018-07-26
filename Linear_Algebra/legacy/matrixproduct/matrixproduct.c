#include <stdio.h>
#include <stdlib.h>
#define MAX 20

void input_matrix_HUM_SH(int *m , int *n, int matrix[MAX][MAX]) {
	int i, j, k;
	// controlli sull'immissione
	printf("Routine di immissione elementi matriciali. MAX %ix%i\n", MAX, MAX);
	do {	*m = 0;
		k=0;
		printf("\nInserire il numero di righe della matrice: ");
		scanf("%d",m);
		if ((*m <= 0)||(*m > MAX)) {
			k=0;			
			printf("\nWARNING:\n Inserire un valore nel range (0,MAX). Prego riprova:\n");
			} else {k=1;}
		} while (!k);
	do {	*n = 0;
		 	printf("\nInserire il numero di colonne della matrice: ");
		scanf("%d",n);
		if ((*n <= 0)||(*n > MAX)) {
			k=0;			
			printf("\nWARNING:\n Inserire un valore nel range (0,MAX). Prego riprova:\n");
			} else {k=1;}
		} while (!k);
	//scrittura matrice	
	for (i=0; i < *m; i++) {
		for (j=0; j < *n; j++) {
			printf("\nM[%i][%i]: ", i, j);
			scanf("%d", &matrix[i][j]);	
			}
		}
	}

void input_matrix_fixedrow_HUM_SH(int *m , int *n, int matrix[MAX][MAX]) {
	int i, j, k;
	// controlli sull'immissione
	do {	*n = 0;
		 	printf("\nInserire il numero di colonne della matrice: ");
		scanf("%d",n);
		if ((*n <= 0)||(*n > MAX)) {
			k=0;			
			printf("\nWARNING:\n Inserire un valore nel range (0,MAX). Prego riprova:\n");
			} else {k=1;}
		} while (!k);
	//scrittura matrice	
	for (i=0; i < *m; i++) {
		for (j=0; j < *n; j++) {
			printf("\nM[%i][%i]: ", i, j);
			scanf("%d", &matrix[i][j]);	
			}
		}
	}
//void print_control_matrix(int *m , int *n, int matrix) {
void print_matrix(int *m , int *n, int matrix[MAX][MAX]) { 
	int i, j;
	for (i=0; i < *m; i++) {
		printf("(");
		for (j=0; j < *n; j++) {
			printf(" %i ",matrix[i][j]);
			}
		printf(")\n");
		}
	}
void product_matrix(int matrix_a[MAX][MAX], int matrix_b[MAX][MAX], int matrix_c[MAX][MAX], int *a, int *c, int *b){
		int i, j, k;	
		for ( i = 0;i<*a; i++){
			for ( j=0; j < *b; j++) {
					for ( k=0;k<*c;k++){
						matrix_c[i][j] += (matrix_a[i][k])*(matrix_b[k][j]);			
					}
				}			
			}
		}
/*	FUNZIONE DI DEBUG
	void check_value(int *a, int *c, int *b){
		printf ("%i, %i, %i", *a, *c, *b);
		}
*/
int main() {
	int matrix_a[MAX][MAX], matrix_b[MAX][MAX], matrix_c[MAX][MAX]={0};
	int a, c, b; 
	
	input_matrix_HUM_SH(&a , &c, matrix_a);
	printf("\nIMMISSIONE MATRICE COMPLETATA\né stata inserita una matrice (%i X %i), definita A:\n\n", a, c);
	print_matrix(&a, &c, matrix_a);	
	input_matrix_fixedrow_HUM_SH(&c , &b, matrix_b);
	printf("\nIMMISSIONE MATRICE COMPLETATA\né stata inserita una matrice (%i X %i), definita B:\n\n", c, b);
	print_matrix(&c, &b, matrix_b);
	product_matrix(matrix_a, matrix_b, matrix_c, &a , &c, &b);
	printf("\nLa matrice prodotto (%i X %i) C = A*B   risulta essere:\n\n", a, b);
	print_matrix(&a, &b, matrix_c);
	
	printf("\nCHIUSURA DEL PROGRAMMA\n\n");
	return 0;
	}
