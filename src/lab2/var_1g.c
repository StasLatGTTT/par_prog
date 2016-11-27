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

void send(int dst, int *len, double *data);

void recv(int src, int *len, double *data);

int main(int argc, char **argv)
{
	MPI_Init(&argc, &argv);
	double a[ISIZE][JSIZE];
	int i, j, rank = -1, size = -1, max = length_diag(0, 0);
	double start, end, E, S, T1, Tp;
	FILE *ff;

	MPI_Rank(&rank, MPI_COMM_WORLD);
	MPI_Size(&size, MPI_COMM_WORLD);

	ROOT
	{
		for (i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			a[i][j] = 10 * i +j;
		}
		}

		start = MPI_Wtime();
		for (i = 1; i < ISIZE; i++){
		for (j = 3; j < JSIZE - 1; j++){
			a[i][j] = sin(0.00001 * a[i - 1][j - 3]);
		}
		}
		end = MPI_Wtime();
		T1 = end - start;

		ff = fopen("result_1g_par.txt","w");
		for(i = 0; i < ISIZE; i++){
			for (j = 0; j < JSIZE; j++){
				fprintf(ff,"%f ",a[i][j]);
			}
			fprintf(ff,"\n");
		}
		fclose(ff);


		for (i = 0; i < ISIZE; i++){
		for (j = 0; j < JSIZE; j++){
			a[i][j] = 10 * i +j;
		}
		}

		start = MPI_Wtime();
		for (i = 1; i < ISIZE; i++){
		for (j = 3; j < JSIZE - 1; j++){
			a[i][j] = sin(0.00001 * a[i - 1][j - 3]);
		}
		}
		end = MPI_Wtime();
		Tp = end - start;

		ff = fopen("result_1g_cons.txt","w");
		for(i = 0; i < ISIZE; i++){
			for (j = 0; j < JSIZE; j++){
				fprintf(ff,"%f ",a[i][j]);
			}
			fprintf(ff,"\n");
		}
		fclose(ff);

		S = T1 / Tp;
		E = S / (size-1);
		printf("T1=%f\tTp=%f\tS=%f\tE=%f\n", T1, Tp, S, E);
	}
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

void send(int dst, int *len, double* data){
	MPI_Send(len, 1, MPI_INT, dst, 0x77, MPI_COMM_WORLD);
	MPI_Send(data, *len, MPI_DOUBLE, dst, 0x77, MPI_COMM_WORLD);
}

void recv(int dst, int *len, double* data){
	MPI_Status status;
	MPI_Recv(len, 1, MPI_INT, dst, 0x77, MPI_COMM_WORLD, &status);
	MPI_Recv(data, *len, MPI_DOUBLE, dst, 0x77, MPI_COMM_WORLD, &status);
}
