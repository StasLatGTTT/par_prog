#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define ISIZE 1000
#define JSIZE 1000

int main(int argc, char **argv)
{
	double a[ISIZE][JSIZE];
	int i, j, N = 1;
	FILE *ff;
	double start, end, T1, Tp, E, S;

	//consistent computation
	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i +j;
	}
	}

	start = clock();
	for (i = 1; i < ISIZE; i++){
	for (j = 3; j < JSIZE - 1; j++){
		a[i][j] = sin(0.00001 * a[i - 1][j - 3]);
	}
	}
	end = clock();
	T1 = end - start;

	ff = fopen("result_cons.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",a[i][j]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);

	//parallel computation
	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i +j;
	}
	}

	start = clock();
	for (i = 1; i < ISIZE; i++){
	for (j = 3; j < JSIZE - 1; j++){
		a[i][j] = sin(0.00001 * a[i - 1][j - 3]);
	}
	}
	end = clock();
	Tp = end - start;

	ff = fopen("result_par.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",a[i][j]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);

	S = T1 / Tp;
	E = S / N;
	printf("%f with 1 thread\n%f with %d threads\n", T1, Tp, N);
	printf("S = %f\t E = %f\n", S, E);
}
