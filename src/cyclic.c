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

  //проверяем аргументы
  if(argc==2)
  iterations_left=atoi(argv[1]);

  //создание нескольких потоков с частной для каждого переменной num
  #pragma omp parallel private(num)
  {
    //узнаём число и номер каждого потока
    size=omp_get_num_threads();
    num=omp_get_thread_num();
    //в цикле поток ждёт пока counter не станет равен номеру потока
    while(1){
      //когда оказывается равен, поток увеличивает counter на 1 по модулю size - число потоков
      if(num==counter){
        if(iterations_left!=0) printf("I'm %d\n", num);
        //если произошел counter overflow (counter сменился с size-1 на 0), это значит, что началась новая итерация
        //в этом случае число оставшихся итераций должно быть уменьшено на 1
        iterations_left-=(counter+1)/size;
        counter=(counter+1)%size;
        //если осталось 0 итераций, поток прекращает работу
        if(iterations_left==0) break;
      }
    }
  }
  return 0;
}
