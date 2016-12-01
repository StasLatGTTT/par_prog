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
	double a[ISIZE][JSIZE];
	int i, j;
	FILE *ff;
	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i + j;
	}
	}
	for (i = 0; i < ISIZE - 4; i++){
	for (j = 5; j < JSIZE; j++){
		a[i][j] = sin(0.00001*a[i+4][j-5]);
	}
	}
	ff = fopen("result.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",a[i][j]);
		}
		fprintf(ff,"\n");
	}
	fclose(ff);
}
