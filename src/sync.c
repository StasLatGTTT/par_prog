/*
Автор: Латушко Станислав
Дата: 05.10.2016
Программа: синхронизированный вывод потоков
*/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char* argv[]){
  int counter=0;
  int num=0;
  #pragma omp parallel private(num)
  {
    num=omp_get_thread_num();
    while(1){
      if(num==counter){
        printf("I'm %d\n", num);
        counter+=1;
        break;
      }
    }
  }
  return 0;
}
