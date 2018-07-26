
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// STRUTTURA DATI

struct list_struct {
	double *x;
	int Dim;
}; typedef struct list_struct list;

list new_list(int New_Dimension, list Input);
list Import_list(list Input, char name_file[]);
void Export_list(list Input, char name_file[]);
int sort(list data, int mode);

int bubble_sort(list data);
int insertion_sort(list data);
int shell_sort(list data);
int quick_sort(list data, int first, int last);
int merge_sort(list data);
int merge(double a[], int start, int center, int end, int dim, int step);
void swap(list data, int in, int out);



list new_list(int New_Dimension, list Input) {
	Input.Dim = New_Dimension;
//	printf("\nlist[%i] defined. dim = %lu Bytes.", Input.ID, Input.Dim * sizeof(double) * 2);
	Input.x = (double *) calloc(Input.Dim, sizeof(double));
	if (Input.x == NULL) {
//		printf("\nFailure in dynamical memory allocation of the X array.");
		exit(EXIT_FAILURE);
		}
	return Input;
}


list Import_list(list Input, char name_file[]) {
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
	Input = new_list(Input.Dim, Input);
	for(i = 0 ; i < Input.Dim; i++) {
		fscanf(input_file, "%lf", &Input.x[i]);
		}
	fclose(input_file);
	return(Input);
}

void Export_list(list Input, char name_file[]) {
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

// ALGORITMI DI ORDINAMENTO

int sort(list data, int mode) {
	int step = 0;
       if (mode == 1) {
    step = bubble_sort(data);
  }
  else if (mode == 2) {
    step = insertion_sort(data);
  }
  else if (mode == 3) {
    step = shell_sort(data);
  }
  else if (mode == 4) {
    step = quick_sort(data, 0, data.Dim-1);
  }
  else if (mode == 5) {
    step = merge_sort(data);
  }
	return step;
}

 int bubble_sort(list data) {
	int i, j, step = 0;
	for (i = 0; i < data.Dim-1; i++) {
		for (j = data.Dim-1; j > i; j--) {
			if(data.x[j-1] > data.x[j]) {
        swap(data, j-1, j);
				step++;
      }
		}
	}
	return step;
}

int insertion_sort(list data) {
	int i, j, step = 0;
	double point;
	for (i = 1; i < data.Dim; i++) {
		point = data.x[i];
		j = i - 1;
		while ((j >= 0) && (data.x[j] > point)) {
			data.x[j+1] = data.x[j];
			j--;
			step++;
			}
		data.x[j+1] = point;
		}
		return step;
	}

 int shell_sort(list data) {
	 int i, j, step = 0;
	 double point;
	 for (int gap = data.Dim/2; gap > 0; gap /=2) {
		 for (i = gap; i < data.Dim; i++) {
	 		point = data.x[i];
	 		j = i;
	 		while ((j >= gap) && (data.x[j-gap] > point)) {
	 			data.x[j] = data.x[j-gap];
	 			j -= gap;
	 			step++;
	 			}
	 		data.x[j] = point;
	 		}
	 }
		 return step;
 }

int quick_sort(list data, int first, int last) {
	int i, j, step = 0;
	double pivot;

	if (first < last){										  			//controllo dim min subarray = 2
		pivot = data.x[last];								//fissa il valore di soglia dello splicing
		i = first;													//inizializza i puntatori del subarray
		j = last;
		while (i <= j) {                           // controllo
			while ((i <= last) && (data.x[i] <= pivot)) {
				i++;
			}
			while (data.x[j] > pivot) {
				j--;
			}
			if (i < j) {
	  		swap(data, i, j);
				step++;
				i++;
				j--;
			}
		}
		if (i <= last) {
			quick_sort(data, first, j);							// ricorsione su subarray sinistro
			quick_sort(data, i, last);						 // ricorsione su subarray destro
		} else {
			quick_sort(data, first, last - 1);			// eventuale
		}
	}
	return step;
}

int merge_sort(list data) {
	int dim = data.Dim;
	int dim_merge = dim-1;
	dim--;
	int i;
	int n = 2;
	int step = 0;

	while (n < dim_merge*2) {
		for (i = 0; (i + n - 1) <= dim_merge; i+=n) {
			step = merge(data.x, i , (i + i + n - 1) / 2, i + ( n - 1 ) , dim_merge ,step);
		}
		i--;
		if ( ( dim_merge + 1 )%n != 0) {
			if (dim > dim_merge)
				step = merge(data.x, dim_merge -((dim_merge)%n) , dim_merge ,dim ,dim, step);
			dim_merge=dim_merge-((dim_merge+1)%n);}
		n = n*2;
	}
	// passo iniziale
	if (dim > dim_merge)
		step = merge(data.x, 0, dim - (dim - dim_merge), dim , dim, step);
	return step;
}

int merge(double a[], int start, int center, int end, int dim, int step) {
	int i, j, k;
	double t_array[dim];

	i = start;
	j = center + 1;
	k = 0;

	while ((i <= center) && (j <= end)) {
		if (a[i] <= a[j]) {
			t_array[k++] = a[i++];
			step++;
		} else {
			t_array[k++] = a[j++];
			step++;
		}
	}

	while (i <= center) 		{
		t_array[k++] = a[i++];
		step++;
	}

	while (j <= end) 		{
		t_array[k++] = a[j++];
		step++;
	}

	for (k = start; k <= end; k++) {
		a[k] = t_array[k-start];
		step++;
	}
	return step;
}
//merge sort top-down

// funzioni ausiliarie

void swap(list data, int in, int out) {
	double temp;
	temp = data.x[in];
	data.x[in] = data.x[out];
	data.x[out] = temp;
	}
