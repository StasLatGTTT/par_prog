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

  //создание нескольких потоков с частной для каждого потока переменной num
  #pragma omp parallel private(num)
  {
    //каждый поток узнает свой номер
    num=omp_get_thread_num();
    //в цикле проверяем, не оказалось ли значение counter равно номеру потока
    while(1){
      //если оказалось равно, ты поток сообщает об этом, увеличивает counter на 1 и прекращает работу
      if(num==counter){
        printf("I'm %d\n", num);
        counter+=1;
        break;
      }
    }
  }
  return 0;
}
