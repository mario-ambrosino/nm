#include "./inc/lib_matrix.c"

int main(int argc, char const *argv[]) {
  int m = atoi(argv[1]);
  int n = atoi(argv[2]);

  // importa nome output
  size_t name_in = strlen(argv[3]);
  char * name_file = malloc(name_in+1);
  if(name_file == NULL) return EXIT_FAILURE;
  strcpy(name_file , argv[3]);

  matrix A = random_matrix(m,n);
  export_matrix(A, name_file);
  free_matrix(A);
  return 0;
}
