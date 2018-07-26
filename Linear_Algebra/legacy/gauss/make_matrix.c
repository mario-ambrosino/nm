#include "./inc/lib_matrix.c"

int main(int argc, char const *argv[]) {
  int n = atoi(argv[1]);
  int m = atoi(argv[2]);
  matrix A = random_matrix(n,m);
  print_matrix(A); 
  return 0;
}
