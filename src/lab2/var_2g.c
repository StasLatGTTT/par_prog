/*
	Автор: Латушко Станислав
	Дата: 27.11.2016
	Программа: лабораторная работа номер 2, вариант 2г
	Аргументы: отсутствуют

	d = { '>', '<'}
	Di = -4;
	Dj = 5;
	Метод распараллеливания ещё не определён
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define ISIZE 1000
#define JSIZE 1000

#define Di -4
#define Dj 5

int main(int argc, char **argv)
{
	double *pa, *pb;
	double *a[ISIZE];
	double *b[ISIZE];
	int i, j, N = 1;
	FILE *ff;
	double start, end, T1, Tp, E, S;

	pa = (double*)malloc(sizeof(double) * ISIZE * JSIZE);
	pb = (double*)malloc(sizeof(double) * ISIZE * JSIZE);
	for(i = 0; i < ISIZE; i++){
		a[i] = pa + i * JSIZE;
		b[i] = pb + i * JSIZE;
	}
	printf("%d\t%d\t%d\t%d\n", pa, pa + ISIZE * JSIZE, 0 - Di, a[ISIZE-1]);

	//consistent computation
	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i + j;
	}
	}

	start = omp_get_wtime();
	for (i = 0; i < ISIZE + Di; i++){
	for (j = Dj; j < JSIZE; j++){
		a[i][j] = sin(0.00001 * a[i - Di][j - Dj]);
	}
	}
	end = omp_get_wtime();
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
		a[i][j] = 10 * i + j;
		b[i][j] = a[i][j];
	}
	}

	start = omp_get_wtime();
	#pragma omp parallel
	{
		N = omp_get_num_threads();
		#pragma omp for private(i, j)
		for (i = 0; i < ISIZE + Di; i++){
		for (j = Dj; j < JSIZE; j++){
			b[i][j] = sin(0.00001 * a[i - Di][j - Dj]);
		}
		}
	}
	end = omp_get_wtime();
	Tp = end - start;

	ff = fopen("result_par.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",b[i][j]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);

	S = T1 / Tp;
	E = S / N;
	printf("%f with 1 thread\n%f with %d threads\n", T1, Tp, N);
	printf("S = %f\t E = %f\n", S, E);

	free(pa);
	free(pb);
	return 0;
}
