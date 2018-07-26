#include "./include/lib_random.c"
#define GCL RAN1
double Average(data Input);
double standard_deviation(data Input);
void chi_square(long TOT_NUMBER, long NUM_BIN, long NUM_TEST);

double Average(data Input) {
	int i = 0;
	double output = 0;
	for (i = 0; i < Input.Dim; i++) {
		output += Input.x[i];
	}
	return output / Input.Dim;
}

double standard_deviation(data Input) {
	int i = 0;
	double average = Average(Input), output = 0;
	for (i = 0; i < Input.Dim; i++) {
		output = pow(Input.x[i]-average,2);
	}
	output /= Input.Dim - 1;
	return output;
}

void chi_square(long TOT_NUMBER, long NUM_BIN, long NUM_TEST) {
	long i, j, bin, totNumber = TOT_NUMBER;
	long y[NUM_BIN];
	long numTest = NUM_TEST, numBin = NUM_BIN; 
	double phi, avePhi, errPhi;
	RANDOM seed = time(0), random = -seed;
	
	//CICLO TEST
	for(j = 0; j < numTest; j++)	{
		//Azzeramento vettore istogramma
		for(i = 0; i < numBin; i++)	{
			y[i] = 0;
		}
		for(i = 0; i < totNumber; i++)	{
		bin = (double)GCL(&random) * numBin;
		if(bin == numBin)	{
			bin--;
		} 
		else if(bin > numBin) {
			printf("Errore: bin troppo grande\n");
			exit(EXIT_FAILURE);
			}
			y[bin]++;
		}
		phi = (- (double) totNumber);
		for(i = 0; i < numBin; i++){
		phi += ( (double) y[i] * (double)y[i] * (double)numBin 
			 / (double) totNumber);  
		}
		//printf("\nTest %ld Phi %lg \n", j, phi);
		avePhi += phi;
		errPhi += (phi * phi);
	}
	avePhi /= (double) numTest;
	errPhi /= (double) numTest;
	errPhi -= (avePhi * avePhi);
	if(numTest > 1){
	 errPhi /= (double) (numTest-1);
	} else {
	 errPhi = 0.0;
	}
	if(errPhi > 0.0){
	 errPhi = sqrt(errPhi);
	} else {
	 errPhi = 0.0;
	}
	printf("\nReduced Chi Squared = %lg /  +/- %lg\n",avePhi / (numBin - 1), errPhi / (numBin - 1));
}


