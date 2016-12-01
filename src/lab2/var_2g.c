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
	double *pa;
	double *a[ISIZE];
	int i, j;
	FILE *ff;
	double start, end, T1, Tp, E, S;

	pa = (double*)malloc(sizeof(double) * ISIZE * JSIZE);
	for(i = 0; i < ISIZE; i++){
		a[i] = pa + i * JSIZE;
	}
	printf("%d\t%d\t%d\t%d\n", pa, pa + ISIZE * JSIZE, 0 - Di, a[ISIZE-1]);

	//consistent computation
	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i + j;
	}
	}

	for (i = 0; i < ISIZE + Di; i++){
	for (j = Dj; j < JSIZE; j++){
		a[i][j] = sin(0.00001 * a[i - Di][j - Dj]);
	}
	}

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
	}
	}

	for (i = 0; i < ISIZE + Di; i++){
	for (j = Dj; j < JSIZE; j++){
		a[i][j] = sin(0.00001 * a[i - Di][j - Dj]);
	}
	}

	ff = fopen("result_par.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",a[i][j]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);

	free(pa);
	return 0;
}
