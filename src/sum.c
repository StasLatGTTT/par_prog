/*
Автор: Латушко Станислав
Дата: 05.10.2016
Программа: параллельное суммирование ряда 1/n
Аргументы: число элементов массива (по умолчанию 1000)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
    int n, size=0;
    double sum=0.0;
    double personal_sum=0.0;
    double time_start=0.0, time_end=0.0, time_sing=0.0, time_mult=0.0;
    double E=0.0, S=0.0;

    if(argc==2){
	n=atoi(argv[1]);
    } else {
	n=1000;
    }

    time_start=omp_get_wtime();
    for(int i=1;i<=n;i++){
	sum+=1.0/((double)i);
    }
    time_end=omp_get_wtime();

    time_sing=time_end-time_start;
    printf("Single thread worked %f s. Sum=%f\n", time_sing, sum);

    sum=0.0;

    time_start=omp_get_wtime();
    #pragma omp parallel private(personal_sum)
    {
	size=omp_get_num_threads();
	#pragma omp for
	for(int i=1;i<=n;i++){
	    personal_sum+=1.0/((double)i);
	}
	#pragma omp critical
	{
	    sum+=personal_sum;
	}
    }
    time_end=omp_get_wtime();

    time_mult=time_end-time_start;
    printf("%d threads worked %f s. Sum=%f\n", size, time_mult, sum);
    S=time_sing/time_mult;
    E=S/size;
    printf("Efficiency E=%f, acceleration S=%f\n", E,S);

    return 0;
}
