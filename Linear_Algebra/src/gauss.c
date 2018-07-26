#include "./inc/lib_matrix.c"

int main(int argc, char const *argv[]) {
  // importa nome coeff
  size_t coeff_in = strlen(argv[1]);
  char * coeff_file = malloc(coeff_in+1);
  if(coeff_file == NULL) return EXIT_FAILURE;
  strcpy(coeff_file , argv[1]);

  // importa nome t.know
  size_t know_in = strlen(argv[2]);
  char * know_file = malloc(know_in+1);
  if(know_file == NULL) return EXIT_FAILURE;
  strcpy(know_file , argv[2]);

  int mode = atoi(argv[3]);             // stabilisce la modalità di risoluzione
  long double det = 1.0;
  matrix coeff = import_matrix(coeff_file);
  matrix know = import_matrix(know_file);
  matrix sol = new_matrix(coeff.N_row,1);

  if (mode == 0) {
    det = triangularize_matrix_0(coeff, know);
    print_matrix(coeff);     // esporta la matrice triangolare
  }

  if (mode == 1) {
    det = triangularize_matrix_0(coeff, know);
    backward_substitution_0(coeff, know, sol);
    print_matrix(sol);      // esporta la soluzione
    export_matrix(sol, "./dat/sol.dat");
  }

  if (mode == 2) {
    det = triangularize_matrix_0(coeff, know);
    printf("\nDet = %Le\n", det);
  }

  if (mode == 3) {
    triangularize_matrix_1(coeff, know);
    backward_substitution_0(coeff, know, sol);
    print_matrix(sol);      // esporta la soluzione
    export_matrix(sol, "./dat/sol.dat");
  }

  /*
  if (mode == 3) {
    matrix L = new_matrix(coeff.N_row, coeff.N_col);
    matrix U = new_matrix(coeff.N_row, coeff.N_col);

    LU_0(coeff, L, U);

    print_matrix(L);
    print_matrix(U);
  }
  */

  free_matrix(coeff);
  free_matrix(know);
  free_matrix(sol);


  return 0;
}
