/*	
	#	Analisi statistiche di sequenze random
	#	Mario Ambrosino - 17/04/2018
	#	1° argomento: NOME_FILE
	#	2° argomento: Numero totale di elementi seq. random chi2
	#	3° argomento: Numero di bin
	#	4° argomento: Numero di test
*/	

#include "./include/lib_analysis.c"

int main (int argc, char **argv) {

//DEFINIZIONI
	char * name_file = argv[1];
	data input;
	input = Import_list(input, name_file);
	long tot_number = atoi(argv[2]);
	long num_bin = atoi(argv[3]);
	long num_test = atoi(argv[4]);
	double average = 0, st_dev = 0;
	
	//MEDIA
	average = Average(input);
	printf("\nAverage of the Generator = %lf", average);
	
	//DEV.ST.
	st_dev = standard_deviation(input);
	printf("\nStandard Deviation of the Generator = %lf", st_dev);
	
	//CHI QUADRO
	printf("\n\nChi-Squared Analysis");

	chi_square(tot_number, num_bin, num_test);
	
	return EXIT_SUCCESS;
}
