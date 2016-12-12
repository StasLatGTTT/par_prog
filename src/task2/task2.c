#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define EPS 0.01

int main(int argc, char* argv[]){
	long int N = 1;
	double x_min = -10.0, x_max = 10.0, y_left, y_right;
	double err = 1, h = 1, temp, param = 100.0;
	double *a, *b, *c, *f, *x, *y, *y_next, *y_der;

	if(argc != 2){
		printf("Invalid argument number\n");
		return -1;
	}
	param = atof(argv[1]);
	temp = 1.0 / ((x_max - x_min) * sqrt(param));
	while(h > temp) {
		N *= 10;
		h = (x_max - x_min) / N;
	}
	N++;
	y_left = sqrt(2);
	y_right = y_left;
	printf("param = %lf\ttemp = %lf\th = %lf\tN = %d\n", param, temp, h, N);

	a = (double*) malloc(N * sizeof(double));
	b = (double*) malloc(N * sizeof(double));
	c = (double*) malloc(N * sizeof(double));
	f = (double*) malloc(N * sizeof(double));
	x = (double*) malloc(N * sizeof(double));
	y = (double*) malloc(N * sizeof(double));
	y_next = (double*) malloc(N * sizeof(double));
	y_der = (double*) malloc(N * sizeof(double));

	free(a);
	free(b);
	free(c);
	free(x);
	free(y);
	free(y_next);
	free(y_der);
	free(f);
	return 0;
}
