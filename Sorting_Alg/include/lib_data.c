//LIBRERIA DI STRUTTURE DATI USATE PER IL CORSO DI METODI NUMERICI
#include <stdio.h>
#include <stdlib.h>

//STRUTTURA DATI
struct data_struct {
	double *x;
	double *y;
	double *z;
	int Dim;
	int ID;
};

//
typedef struct data_struct data;
int ID_counter = 1;

data new_1D_data(int New_Dimension, data Input) {
	Input.ID = ID_counter++;
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.x == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

data new_data(int New_Dimension, data Input) {
	Input.ID = ID_counter++;
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.x == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.y = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.y == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

data new_3D_data(int New_Dimension, data Input) {
	Input.ID = ID_counter++;
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] defined. Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.x == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.y = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.y == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	Input.z = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.y == NULL) {
//		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

data mod_size_data(int New_Dimension, data Input) {
	Input.Dim = New_Dimension;
//	printf("\ndata[%i] size modified. New Size = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = realloc(Input.x, Input.Dim * sizeof(double));
	if (Input.x == NULL) {
		printf("\nFailure in dynamical memory reallocation of the X array.");
		exit(EXIT_FAILURE);
		}
	Input.y = realloc(Input.y, Input.Dim * sizeof(double));
	if (Input.y == NULL) {
		printf("\nFailure in dynamical memory allocation of the Y array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}

double Min_X_data(data Input){
	int i;
	double min_X = Input.x[0];

	for (i = 0; i < Input.Dim; i++){
		if (Input.x[i] < min_X) min_X = Input.x[i];
	}
	return min_X;
}

double MMin_X_data(data Input){
	int i;
	double min_X = Input.x[0];

	for (i = 1; i < Input.Dim-1; i++){
		if (Input.x[i] < min_X) min_X = Input.x[i];
	}
	return min_X;
}


double Min_Y_data(data Input){
	int i;
	double Min_Y = Input.y[Input.Dim];

	for (i = 0; i < Input.Dim; i++){
		if (Input.y[i] < Min_Y) Min_Y = Input.y[i];
	}
	return Min_Y;
}

double Max_X_data(data Input){
	int i = 0;
	double Max_X = Input.x[0];

	for (i = 0; i < Input.Dim; i++){
		if (Input.x[i] > Max_X) Max_X = Input.x[i];
	}
	return Max_X;
}

double Max_Y_data(data Input){
	int i = 0;
	double Max_Y = Input.y[0];

	for (i = 0; i < Input.Dim; i++){
		if (Input.y[i] > Max_Y) Max_Y = Input.y[i];
	}
	return Max_Y;
}

void Export_1D_data(data Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
//		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf\n", Input.x[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}

void Export_y_data(data Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
//		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf; 0.;\n", Input.y[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}

void Export_data(data Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
//		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf %lf\n", Input.x[i], Input.y[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}

void Export_3D_data(data Input, char name_file[255]) {
	int i;
	FILE *input_file;
	if ((input_file = fopen(name_file,"w")) == NULL ) {
		printf("\nFailure in file opening. \nClosing...");
		exit(EXIT_FAILURE);
	}
	for(i = 0 ; i < Input.Dim; i++) {
		fprintf(input_file, "%lf %lf %lf\n", Input.x[i], Input.y[i], Input.z[i]);
		}
	fclose(input_file);
//	printf("\nExport Completed.\n");
}

data Old_Import_data(data Input, char name_file[255]) {
	int i;
	FILE *input_file;
	FILE *fp = popen("cat ./data/function.dat | wc -l", "r");
	fscanf(fp, "%d", &Input.Dim);
	Input = mod_size_data(Input.Dim, Input);
	pclose(fp);
	if ((input_file = fopen(name_file,"r")) == NULL ) {
		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
	for(i = 0 ; i < Input.Dim; i++) {
		fscanf(input_file, "%lf %lf", &Input.x[i], &Input.y[i]);
		}
	fclose(input_file);
//	printf("\nImport Completed. %i data pair(s) found.", Input.Dim);
	return(Input);
}

data Import_data(data Input, char name_file[255]) {
	int i = 0, N = 0;
	FILE *input_file = NULL;
	if ((input_file = fopen(name_file,"r")) == NULL ) {
//		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
	char c;
   while( (c = getc(input_file))!=EOF ) if(c=='\n') N++;
   rewind(input_file);
   Input.Dim = N;
	Input = mod_size_data(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		fscanf(input_file, "%lf %lf", &Input.x[i], &Input.y[i]);
		}
	fclose(input_file);
//	printf("\nImport Completed. %i data pair(s) found.", Input.Dim);
	return(Input);
}

data Import_list(data Input, char name_file[255]) {
	int i = 0, N = 0;
	FILE *input_file = NULL;
	if ((input_file = fopen(name_file,"r")) == NULL ) {
//		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
	char c;
   while( (c = getc(input_file))!=EOF ) if(c=='\n') N++;
   rewind(input_file);
   Input.Dim = N;
	Input = new_1D_data(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		fscanf(input_file, "%lf", &Input.x[i]);
		}
	fclose(input_file);
	return(Input);
}


data Import_New_data(data Input, char name_file[255]) {
	int i = 0, N = 0;
	FILE *input_file = NULL;
	if ((input_file = fopen(name_file,"r")) == NULL ) {
		printf("\nFailure in file opening.\nClosing...");
		exit(EXIT_FAILURE);
		}
	char c;
   while( (c = getc(input_file))!=EOF ) if(c=='\n') N++;
   rewind(input_file);
   Input.Dim = N;
	Input = new_data(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		fscanf(input_file, "%lf %lf", &Input.x[i], &Input.y[i]);
		}
	fclose(input_file);
//	printf("\nImport Completed. %i data pair(s) found.", Input.Dim);
	return(Input);
}

void Print_data(data Input){
	int i;
	printf("\nStruttura Dato[%i]:\n\n", Input.ID);
	for(i = 0; i < Input.Dim ; i++) {
		printf("\n( %lf %lf ) = Dato[%i]", Input.x[i], Input.y[i], i);
	}
}

void Print_data_range(data Input) {
	double a = Min_X_data(Input);
	double b = Max_X_data(Input);
	double c = Min_Y_data(Input);
	double d = Max_Y_data(Input);
	printf("\ndata pairs (x,y) ∊ ( %lf, %lf ) X ( %lf, %lf ).", a, b, c, d);
}

data Write_X_data(int Cardinality_Input, double *Input, data Output) {
	int i;
	Output = mod_size_data(Cardinality_Input, Output);
	Output.Dim = Cardinality_Input;
	for(i = 0; i < Cardinality_Input ; i++) {
		Output.x[i] = Input[i];
	}
	return(Output);
}

data Write_Y_data(int Cardinality_Input, double *Input, data Output) {
	int i;
	Output = mod_size_data(Cardinality_Input, Output);
	Output.Dim = Cardinality_Input;
	for(i = 0; i < Cardinality_Input ; i++) {
		Output.y[i] = Input[i];
	}
	return(Output);
}

data Copy_data(data Input, data Output)  {
	int i;
	Output = mod_size_data(Input.Dim, Output);
	Output.Dim = Input.Dim;
	for(i = 0; i < Input.Dim ; i++) {
		Output.x[i] = Input.x[i];
		Output.y[i] = Input.y[i];
	}
	return(Output);
}

void Free_data(data Input) {
//	printf("\nFreeing Data[%i]\n", Input.ID);
	free(Input.x);
	free(Input.y);
}

//funzione fattoriale
unsigned long long int fattoriale(int n) {
	//dichiarazione variabili interne
	int i;
	unsigned long long int p=1;
	//ciclo fattoriale
	for (i=1; i<=n; i++)
		{
		p *= i;
		if ( p == 0 ) {
			printf("Errore. Massimo input %d per la macchina", i-1);
			i=n;
			}
		}
	return p;
	}
