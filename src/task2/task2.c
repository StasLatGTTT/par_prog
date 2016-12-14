#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define EPS 0.01

/*
	Calculates 1st norm of defference of two vectors
		arr1, arr2 - vectors to calculate their difference
		len - their common length
*/
double max_diff(double *arr1, double *arr2, int len);

/*
	Calculates vector of task function based on current y
		f - pointer where to place target vector
		y - current iteration of solution
		len - their common length
		param - task parameter
*/
void task_func(double *f, double *y, int len, double param);

/*
	Calculates vector of f derivatives
		f_der - pointer where to place target vector
		f - vector to calculate derivative of
		len - thir common length
		h - step of x
		param - task parameter
*/
void task_func_der(double *f_der, double *f, int len, double h, double param);

/*
	Solve system of linear equations
		y - solution vector
		a - lower-left diagonal
		b - main diagonal
		c - upper-right diagonal
		w - free vector
		len - their common length
*/
void solve_sle(double *y, double *a, double *b, double *c, double *w, int len);

int main(int argc, char* argv[]){
	int N = 1, i = 0;
	int i_temp;
	double x_min = -10.0, x_max = 10.0, y_left, y_right;
	double err = 1, h = 1, param = 100.0;
	double *a, *b, *c, *w, *x, *y, *y_next, *f, *f_der;
	double d_temp[4];

	/*
		Initiate task parameters
			param - coefficient in task function a
			h - step of x
			N - number of nodes
			y_left, y_right - left and right border conditions
			d_temp - array of optimisation doubles
			i_temp - optimisation integer

	*/
	if(argc != 2){
		printf("Invalid argument number\n");
		return -1;
	}
	param = atof(argv[1]);
	//cycle constant: upper limit of posiible h
	d_temp[0] = 1.0 / ((x_max - x_min) * sqrt(param));
	//cycle constant: x range
	d_temp[1] = x_max - x_min;
	while(h > d_temp[0]) {
		N *= 10;
		h = d_temp[1] / N;
	}
	N++;
	y_left = sqrt(2);
	y_right = y_left;

	/*
		Allocate memory for solution
			a - lower-left diagonal
			b - main diagonal
			c - upper-right diagonal
			w - free vector
			x - x-axis
			y - current stem approximation
			y_next - next step approximation
			f - task function vector
			f_der - task function derivative vector
	*/
	a = (double*) malloc(N * sizeof(double));
	b = (double*) malloc(N * sizeof(double));
	c = (double*) malloc(N * sizeof(double));
	w = (double*) malloc(N * sizeof(double));
	x = (double*) malloc(N * sizeof(double));
	y = (double*) malloc(N * sizeof(double));
	y_next = (double*) malloc(N * sizeof(double));
	f = (double*) malloc(N * sizeof(double));
	f_der = (double*) malloc(N * sizeof(double));

	//initial x and y setting
	//cycle constant: diff between neighbour y
	d_temp[0] = (y_right - y_left) / (x_max - x_min) * h;
	//cycle constant: diff between y and y_next
	d_temp[1] = EPS * 10;
	x[0] = x_min;
	x[N - 1] = x_max;
	for (i = 1; i < N - 1; i++){
		y[i] = y[i - 1] + d_temp[0];
		y_next[i] = y[i] + d_temp[1];
		x[i] = x[i - 1] + h;
	}
	//initial err
	err = d_temp[1];

	//main cycle
	while(err > EPS){
		//setting iteration vectors
		task_func(f, y, N, param);
		task_func_der(f_der, f, N, h, param);
		err /= 10.0;
		a[0] = c[0] = a[N -1] = c[N - 1] = 0.0;
		b[0] = b[N - 1] = 1;
		w[0] = y_left;
		w[N - 1] = y_right;
		//cycle constant: cycle range
		i_temp = N - 1;
		//cycle constant: frequently used expression
		d_temp[0] = 1 / (h * h);
		for(i = 1; i < i_temp; i++){
			a[i] = d_temp[0] - f_der[i - 1] / 12.0;
			c[i] = d_temp[0] - f_der[i + 1] / 12.0;
			b[i] = -2.0 * d_temp[0] - f_der[i] * 5.0 / 6.0;
			w[i] = (f[i - 1] + f[i + 1] + 10.0 * f[i] \
				- f_der[i - 1] * y[i - 1] \
				- f_der[i * 1] * y[i + 1] \
				- 10 * f_der[i] * y[i]) / 12.0;
		}
	}

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

void task_func(double *f, double *y, int len, double param)
{
	for (int i = 0; i < len; i++){
		f[i] = param * (y[i] * y[i] - 1) * y[i];
	}
}

void task_func_der(double *f_der, double *f, int len, double h, double param)
{
	f_der[0] = (f[1] - f[0]) / h;
	f_der[len - 1] = (f[len - 1] - f[len - 2]) / h;
	h *= 2;
	for (int i = 1; i < (len - 1); i++){
		f_der[i] = (f[i + 1] - f[i - 1]) / h;
	}
}
