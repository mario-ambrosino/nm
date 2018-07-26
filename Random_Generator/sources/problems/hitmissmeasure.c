#include "./include/lib_random.c"
/* 
	##	Misure con metodo Montecarlo 
	##	Mario Ambrosino v.1.0 19/04/2018
	##	
	## Use 1° argument as Max_Points 
	## Use 2° argument as radius

*/

int main (int argc, char **argv)  {
	
	int i=0;
	int Max_Points = atoi(argv[1]);
	double radius = atof(argv[2]);
	double x, y, z, k, A, V, Atrue, Vtrue;
	RANDOM seed = -time(0);
	
	k = 0;
	for (i = 1; i < Max_Points; i++) {
		x = radius * (2 * RAN2(&seed) - 1);
		y = radius * (2 * RAN2(&seed) - 1);
		z = radius * (2 * RAN2(&seed) - 1);
		if (x*x + y*y + z*z < radius*radius) k++;
	}
	V = 8 * radius * radius * radius * k / Max_Points;
	Vtrue = 4.0 * M_PI * radius * radius * radius / 3;
	printf("\nVolume for the sphere (radius = %lf) vs true volume = %lf vs %lf", radius, V, Vtrue);
	
	k = 0;
	for (i = 1; i < Max_Points; i++) {
		x = radius * (2 * RAN2(&seed) - 1);
		y = radius * (2 * RAN2(&seed) - 1);
		if (x*x + y*y < radius*radius) k++;
	}
	A = 4 * radius * radius * k / Max_Points;
	Atrue = M_PI * radius * radius;
	printf("\nArea for the circle (radius = %lf) vs true area = %lf vs %lf", radius, A, Atrue);
	return EXIT_SUCCESS;
}
