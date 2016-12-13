#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define EPS 0.01

double max_diff(double *arr1, double *arr2, int len);

int main(int argc, char* argv[]){
	long int N = 1;
	double x_min = -10.0, x_max = 10.0, y_left, y_right;
	double err = 1, h = 1, temp, param = 100.0;
	double *a, *b, *c, *w, *x, *y, *y_next, *f, *f_der;

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

	a = (double*) malloc(N * sizeof(double));
	b = (double*) malloc(N * sizeof(double));
	c = (double*) malloc(N * sizeof(double));
	w = (double*) malloc(N * sizeof(double));
	x = (double*) malloc(N * sizeof(double));
	y = (double*) malloc(N * sizeof(double));
	y_next = (double*) malloc(N * sizeof(double));
	f = (double*) malloc(N * sizeof(double));
	f_der = (double*) malloc(N * sizeof(double));

	free(a);
	free(b);
	free(c);
	free(x);
	free(y);
	free(y_next);
	free(f_der);
	free(f);
	free(w);
	return 0;
}

double max_diff(double *arr1, double* arr2, int len)
{
	double max = fabs(arr1[0] - arr2[0]), curr;
	for (int i = 1; i < len; i++){
		curr = fabs(arr1[i] - arr2[i]);
		max = (curr > max) ? curr : max;
	}
	return max;
}
