#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define EPS 0.01

int main(int argc, char* argv){
	int param = 100, N = 1;
	double h = 0.1, x_min = -10.0, x_max = 10.0, err = 1;
	double *a, *b, *c, *f, *x, *y, *y_next, *y_der;


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
