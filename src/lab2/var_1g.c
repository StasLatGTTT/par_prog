/*
	Автор: Латушко Станислав
	Дата: 27.11.2016
	Программа: параллельное суммирование ряда 1/n
	Аргументы: отсутствуют

	d = { '<', '<'}
	Di = 1;
	Dj = 3;
	Распараллеливание диагональным методом
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#define ISIZE 1000
#define JSIZE 1000

#define ROOT if(rank == 0)
#define WORKER if(rank != 0)

int get_diag(int x, int y, double* arr, double *diag);

int insert_diag(int x, int y, double* arr, double *diag);

int length_diag(int x, int y);

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	double a[ISIZE][JSIZE];
	int i, j;
	FILE *ff;

	for (i = 0; i < ISIZE; i++){
	for (j = 0; j < JSIZE; j++){
		a[i][j] = 10 * i +j;
	}
	}

	for (i = 1; i < ISIZE; i++){
	for (j = 3; j < JSIZE - 1; j++){
		a[i][j] = sin(0.00001 * a[i - 1][j - 3]);
	}
	}

	ff = fopen("result_1g.txt","w");
	for(i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			fprintf(ff,"%f ",a[i][j]);
		}
		fprintf(ff,"\n");
	}

	fclose(ff);
	MPI_Finalize();
	return 0;
}

int length_diag(int x, int y)
{
	int len=0;
	while((x < JSIZE) && (y < ISIZE)){
		x += 3;
		y += 1;
		len++;
	}
	return len;
}

int get_diag(int x, int y, double* a, double* diag)
{
	int i = 0;
	while(x < JSIZE && y < ISIZE){
		diag[i] = a[y * JSIZE + x];
		x += 3;
		y += 1;
		i++;
	}
	return 0;
}

int insert_diag(int x, int y, double* a, double* diag)
{
	int i = 0;
	while(x < JSIZE && y < ISIZE){
		a[y * JSIZE + x] = diag[i];
		x += 3;
		y += 1;
		i++;
	}
	return 0;
}
