/*
Listato per confrontare vari algoritmi di ordinamento su lista 1-dim

[1] (char) input_name_file
[2] (int) mode
[3] (char) output_name_file

(possible mode)

[0] Make Uniform Random Data
[1] Bubble Sort
[2] Insertion Sort
[3] Shell sort
[4] Quick sort
[5] Merge sort

bubble_sort
*/
#include "./include/lib_sort.c"

int main(int argc, char *argv[]) {
  int mode = atoi(argv[2]);
  //Acquisizione indirizzo input
  size_t len_in = strlen(argv[1]);
  char * input_name_file = malloc(len_in+1);
  if(input_name_file == NULL) return EXIT_FAILURE;
  strcpy(input_name_file, argv[1]);

  //Acquisizione indirizzo output
  size_t len_out = strlen(argv[3]);
  char * output_name_file = malloc(len_out+1);
  if(output_name_file == NULL) return EXIT_FAILURE;
  strcpy(output_name_file, argv[3]);

  long unsigned start = 0;                                  // variabili per timing
  long unsigned stop = 0;                                   // variabili per timing
  list data = Import_list(data, input_name_file);     //Genera struttura dati

  start = clock();
  long unsigned step = 0;
  step = sort(data, mode);                                  //Ordina struttura dati
  stop = clock();

  Export_list(data, output_name_file);                 //Esporta struttura dati
  free(data.x);                                       //Libera la struttura dati
  printf("\nM:%i, %lu, %lu", mode, step, (stop - start));

  return 0;
}
