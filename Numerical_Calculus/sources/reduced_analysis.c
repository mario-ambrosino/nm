/*
	#	Analisi statistiche di sequenze random
	#	Mario Ambrosino - 20/04/2018
	#	1° argomento: NOME_FILE
*/

#include "./include/lib_analysis.c"

int main (int argc, char **argv) {

//DEFINIZIONI
	char * name_file = argv[1];
	data input;
	input = Import_list(input, name_file);
	double average = 0, st_dev = 0;

	//MEDIA
	average = Average(input);
	st_dev = standard_deviation(input);
	printf("%e %e\n", average, st_dev);

	return EXIT_SUCCESS;
}
