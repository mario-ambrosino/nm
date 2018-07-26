
#include "lib_random.c"
#include <string.h>

struct data_mat {
	long double ** elem;
	int N_row;
	int N_col;
}; typedef struct data_mat matrix;

void error(char msg[]){
  printf("%s", msg);
	exit(EXIT_FAILURE);
}

// void swap(long double *a, long double *b);
// void row_swap(matrix A, int n, int m);
matrix new_matrix(int n, int m);
matrix random_matrix(int n, int m);
matrix import_matrix(char name_file[]);
void print_matrix(matrix A);
void export_matrix(matrix A, char name_file[]);
void free_matrix(matrix A);
matrix product_matrix(matrix A, matrix B);
matrix extend_matrix(matrix A, matrix B);
double triangularize_matrix_0(matrix A, matrix B);
int triangularize_matrix_1(matrix A, matrix B);
int partial_pivoting_0(matrix A, matrix B, int i);
void backward_substitution_0(matrix A, matrix B, matrix X);
void LU_0(matrix M, matrix L, matrix U);

// operazioni unarie sulla matrice
/*
void swap(long double *a, long double *b) {
long double temp;
temp = *a;
*a = *b;
*b = temp;
}

void row_swap(matrix A, int m, int n) {
  long double * temp;
  if((m < A.N_row)&&(n < A.N_row)) {
    temp = A.elem[m];
    A.elem[m] = A.elem[n];
    A.elem[n] = temp;
  }
  else (error("Failure: row index bigger than N.\nClosing...\n"));
}

void row_swap2(matrix A, int m, int n) {
  long double temp;
  for(int i = 0; i < A.N_col; i++) {
    temp = A.elem[m][i];
    A.elem[m][i] = A.elem[n][i];
    A.elem[n][i] = temp;
  }
}
*/
// I/O delle matrici
matrix new_matrix(int m, int n) {
  matrix A;
  A.N_row = m;
  A.N_col = n;
  A.elem= (long double **) calloc(A.N_row + 1, sizeof(long double *));
  for(int i = 0; i < A.N_row; i++) {
    A.elem[i] = (long double *) calloc(A.N_col + 1, sizeof(long double ));
    }
  return A;
  }


matrix random_matrix(int m, int n) {
  int i, j;
  //seed per generazione matrice random
  struct timeval tv;
  gettimeofday(&tv, 0);
  RANDOM seed = -tv.tv_usec;
  matrix A;
  A.N_row = m;
  A.N_col = n;
  A.elem= (long double **) calloc(A.N_row, sizeof(long double *));
  for(i = 0; i < A.N_row; i++) {
    A.elem[i] = (long double *) calloc(A.N_col, sizeof(long double ));
    for(j = 0; j < A.N_col; j++) {
      A.elem[i][j] = RAN2(&seed);
    }
  }
  return A;
}

matrix import_matrix(char name_file[]) {
  int i = 0, j = 0;
  matrix A;

  FILE *input_file = NULL;
	if ((input_file = fopen(name_file,"r")) == NULL ) {
//		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
    char c;
     while( (c = getc(input_file))!=EOF ) {
       if(c=='\n') i++;
       if(c==';') j++;
     }
     rewind(input_file);
     A.N_row = i;
     A.N_col = j / i;
     // printf("N = %u, M = %u", A.N_row, A.N_col );

  A.elem= (long double **) calloc(A.N_row, sizeof(long double *));
  for(i = 0; i < A.N_row; i++) {
    A.elem[i] = (long double *) calloc(A.N_col, sizeof(long double ));
    for(j = 0; j < A.N_col; j++) {
    	fscanf(input_file, "%Le; ", &A.elem[i][j]);
    }
  }
  return A;
}

void print_matrix(matrix A) {
  for (int i = 0; i < A.N_row; i++) {
    printf("\n");
    for (int j = 0; j < A.N_col; j++) {
      printf("%Le; ", A.elem[i][j]);
    }
  }
  printf("\n");
}

void export_matrix(matrix A, char name_file[]) {
FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
//		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
    for (int i = 0; i < A.N_row; i++) {
      for (int j = 0; j < A.N_col; j++) {
        fprintf(input_file, "%Le; ", A.elem[i][j]);
      }
      fprintf(input_file, "\n");
    }
	fclose(input_file);
}

void free_matrix(matrix A) {
  for(int i = 0; i < A.N_row; i++) {
    free(A.elem[i]);
  }
}

matrix product_matrix(matrix A, matrix B) {
  matrix C = new_matrix(A.N_row, B.N_col);
  if(A.N_col != B.N_row) {
    error("Failure: invalid choice of matrices\nClosing...\n");
  }
  for (int i = 0; i < A.N_row; i++){
	for (int j = 0; j < B.N_col; j++) {
			for (int k = 0; k < A.N_col ; k++){
  				C.elem[i][j] += (A.elem[i][k])*(B.elem[k][j]);
  			}
  		}
  	}
  return C;
  }

	matrix extend_matrix(matrix A, matrix B) {
	  matrix C = new_matrix(A.N_row, A.N_col + B.N_col);
	  for (int i = 0; i < A.N_row; i++){
		for (int j = 0; j < A.N_col; j++) {
	  				C.elem[i][j] = A.elem[i][j];
	  			}
	  		}
		for (int i = 0; i < B.N_row; i++){
		for (int j = 0; j < B.N_col; j++) {
	  				C.elem[i][j+A.N_col] = B.elem[i][j];
	  			}
	  		}
	  return C;
	  }

double triangularize_matrix_0(matrix A, matrix B) {
	int i, j, k;
	long double C;
	long double det = 1.0;
	int parity = +1;

	for(i = 0; i < A.N_col; i++) {
		parity *= partial_pivoting_0(A, B, i);
		C = A.elem[i][i];
		det *= parity*A.elem[i][i];

		//divide la riga i-ma per il pivot
		for(j = i; j < A.N_col; j++) {
			A.elem[i][j] /= C;
		}
		//divide 0'i-mo dell'insieme dei t.noto per pivot
		B.elem[i][0] /= C;
		//sottrae 0'equazione normalizzata dalle altre
		for(k = i+1; k < A.N_col; k++) {
			C = A.elem[k][i];
			for(j = i; j < A.N_col; j++) {
				A.elem[k][j] -= A.elem[i][j] * C;
			}
			B.elem[k][0] -= C*B.elem[i][0];
		}
	}
	return det;
}

int triangularize_matrix_1(matrix A, matrix B) {
	int i, j, k;
	int parity = +1;
	for(i = 0; i < A.N_col; i++) {
		parity *= partial_pivoting_0(A, B, i);
		for(k = i+1; k < A.N_col; k++) {
			for(j = i; j < A.N_col; j++) {
				A.elem[k][j] -= A.elem[i][j] * A.elem[k][i] / A.elem[i][i];
			}
			B.elem[k][0] -= B.elem[i][0] * A.elem[k][i] / A.elem[i][i];
		}
	}
	return parity;
}

int partial_pivoting_0(matrix A, matrix B, int i) {
	int ipiv = i;
	long double vmax = A.elem[i][i];
	int parity = +1;
	for (int j = i ; j < A.N_row; j++) {
		if(A.elem[j][i] > vmax) {
			vmax = A.elem[j][i];
			ipiv = j;
			long double temp;
			for(int s = 0; s < A.N_col; s++) {
				temp = A.elem[ipiv][s];
				A.elem[ipiv][s] = A.elem[i][s];
				A.elem[i][s] = temp;
				for(int s = 0; s < B.N_col; s++) {
					temp = B.elem[ipiv][s];
					B.elem[ipiv][s] = B.elem[i][s];
					B.elem[i][s] = temp;
				}
				parity *= -(parity);
			}
		}
	}
	return parity;
}

void backward_substitution_0(matrix A, matrix B, matrix X) {
	X.elem[X.N_row - 1][0] = B.elem[B.N_row - 1][0];
	for(int i = (B.N_row - 2) ; i > 0; i--){
		X.elem[i][0] = B.elem[i][0];
		for(int j = i+1; j < B.N_row; j++) {
			X.elem[i][0] -= A.elem[i][j]*X.elem[j][0];
		}
	}
	// ultimo ciclo a parte. Non ho compreso il perché.
	X.elem[0][0] = B.elem[0][0];
	for(int j = 1; j < B.N_row; j++) {
		X.elem[0][0] -= A.elem[0][j]*X.elem[j][0];
	}
}

void LU_0(matrix M, matrix L, matrix U) {
	int i, j, k;
	int N = M.N_row;
		//dato il grado di libertà di L assegna elem. diag. 1
	for (i = 0; i < N ; i++) {
		L.elem[i][i] = 1.;
	}
	/* calcola gli elementi fuori della diagonale */
	for (j = 0; j < N ; j++) {
		for (i = 0; i < j ; i++) {
			U.elem[i][j] = M.elem[i][j];
			for (k=0; k < i-1; k++) {
				U.elem[i][j] -= L.elem[i][k]* U.elem[k][j];
			}
		}
		for ( i = j + 1; i < N ; i++) {
			L.elem[i][j] = M.elem[i][j];
			for ( k = 0; k < j - 1; k++) {
				L.elem[i][j] -= L.elem[i][k] * U.elem[k][j];
			}
			L.elem[i][j] /= U.elem[j][j];
		}
	}
}
