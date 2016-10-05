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

    //проверка количества аргументов
    if(argc==2){
	n=atoi(argv[1]);
    } else {
	n=1000;
    }

    //вычисление суммы одним потоком с замером времени
    time_start=omp_get_wtime();
    for(int i=1;i<=n;i++){
	     sum+=1.0/((double)i);
    }
    time_end=omp_get_wtime();

    //вывод информации об однопоточном вычислении
    time_sing=time_end-time_start;
    printf("Single thread worked %f s. Sum=%f\n", time_sing, sum);

    sum=0.0;

    //вычисление несколькими потоками
    time_start=omp_get_wtime();
    //создаются несколько потоков, переменная personal_sum обявляется частной для каждого потока
    #pragma omp parallel private(personal_sum)
    {
      //узнаём, сколько потоков создалось
      size=omp_get_num_threads();
      //цикл распределяется по созданным потокам
	    #pragma omp for
	    for(int i=1;i<=n;i++){
	       personal_sum+=1.0/((double)i);
	    }
      //критическая секция предотвращает ошибку из-за попытки одновременной записи переменной несколькими потоками
	    #pragma omp critical
	    {
	       sum+=personal_sum;
	    }
  }
  time_end=omp_get_wtime();

  //вывод информации о многопоточном вычислении
  time_mult=time_end-time_start;
  printf("%d threads worked %f s. Sum=%f\n", size, time_mult, sum);

  //вычисление и вывод ускорения и эффективности
  S=time_sing/time_mult;
  E=S/size;
  printf("Efficiency E=%f, acceleration S=%f\n", E,S);

  return 0;
}
