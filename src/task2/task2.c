#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

int main(int argc, char* argv){
	int param = 100, N = 1;
	double h = 0.1, x_min = -10.0, x_max = 10.0;
	double *a, *b, *c, *f, *x, *y, *y_next, *y_der;

	a = (double*) malloc((N + 1) * sizeof(double));
	b = (double*) malloc((N + 1) * sizeof(double));
	c = (double*) malloc((N + 1) * sizeof(double));
	f = (double*) malloc((N + 1) * sizeof(double));
	x = (double*) malloc((N + 1) * sizeof(double));
	y = (double*) malloc((N + 1) * sizeof(double));
	y_next = (double*) malloc((N + 1) * sizeof(double));
	y_der = (double*) malloc((N + 1) * sizeof(double));

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
