/*
	Автор: Латушко Станислав
	Дата: 14.12.2016
	Программа: задание 2, уравнение y'' = a * (y ^ 3 - y)
	Аргументы: параметр уравнения a
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <omp.h>

#define EPS 0.01
#define MY_TASK "a * (y ^ 3 - y)"

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
void sle_3d(double *y, double *a, double *b, double *c, double *w, int len);

void print_3d(double *a, double *b, double *c, int len);

int main(int argc, char* argv[]){
	int N = 1, i = 0;
	int i_temp;
	double x_min = -10.0, x_max = 10.0, y_left, y_right;
	double err = 1, h = 1, param = 100.0;
	double *a, *b, *c, *w, *x, *y, *y_next, *f, *f_der, *exch;
	double d_temp[4];
	FILE* out;

	printf("Starting computation\nEquation: y\'\' = %s\n", MY_TASK);

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
		param = 100.0;
	} else {
		param = atof(argv[1]);
	}
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

	printf("Task parameters\na = %lf\n", param);
	printf("Range: from %lf to %lf\n", x_min, x_max);
	printf("y(%lf) = %lf;   y(%lf) = %lf\n", x_min, y_left, x_max, y_right);
	printf("N = %d, h = %lf\n", N, h);

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
	y[0] = y_left;
	y[N - 1] = y_right;
	for (i = 1; i < N - 1; i++){
		y[i] = y[i - 1] + d_temp[0];
		y_next[i] = y[i] + d_temp[1];
		x[i] = x[i - 1] + h;
	}
	//initial err
	err = d_temp[1];

	double a1[] = {0.0, 3.0, 3.0, 3.0, 0.0};
	double b1[] = {1.0, -6.0, -6.0, -6.0, 1.0};
	double c1[] = {0.0, 3.0, 3.0, 3.0, 0.0};
	double w1[] = {1.0, 3.0, -9.0, 9.0, 5.0};
	double y1[] = {1.0, 2.0, 3.0, 4.0, 5.0};

	sle_3d(y1, a1, b1, c1, w1, 5);
	printf("%f\t%f\t%f\t%f\t%f\n", y1[0], y1[1], y1[2], y1[3], y1[4]);
	//main cycle
	printf("Starting computation cycle\n");
	while(err < EPS){
		//setting iteration vectors
		task_func(f, y, N, param);
		task_func_der(f_der, f, N, h, param);
		//err /= 2.0;
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

		//compute next iteration of approximation
		sle_3d(y_next, a, b, c, w, N);
		//sle_mx(y_next, mx, w, N);
		err = max_diff(y, y_next, N);
		exch = y;
		y = y_next;
		y_next = exch;
		printf("Cycle\terr=%f\n", err);
	}
	printf("Printing result\n");

	//save result in file
	out = fopen("task2_solution.txt", "w");
	fprintf(out, "%d\n", N);
	for(i = 0; i < N; i++){
		fprintf(out, "%f\n", x[i]);
	}
	for(i = 0; i < N; i++){
		fprintf(out, "%f\n", y[i]);
	}
	fclose(out);

	free(a);
	free(b);
	free(c);
	free(x);
	free(y);
	free(y_next);
	free(f_der);
	free(f);
	free(w);

	printf("Computation complete\n");
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

void sle_3d(double *y, double *a, double *b, double *c, double *w, int len)
{
	int i = 0, j = 0, d = 1;
	double *new_a, *new_b, *new_c, *new_w;

	new_a = (double*) malloc(len * sizeof(double));
	new_b = (double*) malloc(len * sizeof(double));
	new_c = (double*) malloc(len * sizeof(double));
	new_w = (double*) malloc(len * sizeof(double));

	while(d < 4){
		new_b[0] = b[0];
		new_b[len - 1] = b[len - 1];
		new_c[0] = c[0];
		new_c[len - 1] = c[len - 1];
		new_a[0] = a[0];
		new_a[len - 1] = a[len - 1];
		new_w[0] = w[0];
		new_w[len - 1] = w[len - 1];

		for(i = 1; i < len - 1; i++){
			new_a[i] = - a[i] * ((i-d>=0)?a[i-d]:0.0) / \
				((i-d>=0)?b[i-d]:1.0);

			new_c[i] = - c[i] * ((i+d<len)?c[i+d]:0.0) / \
				((i+d<len)?b[i+d]:1.0);

			new_b[i] = b[i] - a[i] * ((i-d>=0)?c[i-d]:0.0) / \
				((i-d>=0)?b[i-d]:1.0) - c[i] * \
				((i+d<len)?a[i+d]:0.0) / ((i+d<len)?b[i+d]:1.0);

			new_w[i] = w[i] - a[i] / ((i-d>=0)?b[i-d]:1.0) * \
			((i-d>=0)?w[i-d]:0.0) - c[i] / ((i+d<len)?b[i+d]:1.0) * \
				((i+d<len)?w[i+d]:0.0);

		}
		d *= 2;

		for(i = 0; i < len; i++){
			printf("%f\t", w[i]);
		}

		memcpy(a, new_a, len * sizeof(double));
		memcpy(b, new_b, len * sizeof(double));
		memcpy(c, new_c, len * sizeof(double));
		memcpy(w, new_w, len * sizeof(double));
		printf("\nRed cycle\n");
	}

	for(i = 0; i < len; i++){
		y[i] = w[i] / b[i];
	}

	print_3d(a, b, c, len);

	free(new_a);
	free(new_b);
	free(new_c);
	free(new_w);
}

void print_3d(double *a, double *b, double *c, int len){
	FILE *ff = fopen("matrix.txt", "w");
	fprintf(ff, "%f\t%f\n", b[0], c[0]);
	for (int i = 1; i < len; i++){
		int j = 0;
		for (; j < i - 1; j++){
			fprintf(ff,"0.000000\t");
		}
		fprintf(ff,"%f\t%f\t%f\n", a[i], b[i], c[i]);
	}
	fclose(ff);
}
