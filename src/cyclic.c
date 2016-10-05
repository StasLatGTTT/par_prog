/*
Автор: Латушко Станислав
Дата: 05.10.2016
Программа: синхронизированный циклический вывод потоков
Аргументы: количество циклов вывода сообщений (по умолчанию равен 5)
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
  int counter=0, iterations_left=5;
  int num=0, size=0;

  if(argc==2)
  iterations_left=atoi(argv[1]);

  #pragma omp parallel private(num)
  {
    size=omp_get_num_threads();
    num=omp_get_thread_num();
    while(1){
      if(num==counter){
        if(iterations_left!=0) printf("I'm %d\n", num);
        iterations_left-=(counter+1)/size;
        counter=(counter+1)%size;
        if(iterations_left==0) break;
      }
    }
  }
  return 0;
}
