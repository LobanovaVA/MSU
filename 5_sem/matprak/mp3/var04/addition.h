#ifndef ADDITION_H
#define ADDITION_H

#define SUCCESS 0
#define ERROR_USAGE_ARGC 1
#define ERROR_ALLOCATE_MEMORY 2
#define ERROR_PTHREAD_BARRIER_INIT 3
#define ERROR_PTHREAD_CREATE 4

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12

#include <stdio.h>
#include <string.h>
#include <pthread.h>

class argument
{
public:
  int p = 0;
  int k = 0;
  const char **files = nullptr;  // массив имен файлов
  double *shared_sum = nullptr;  // сумма элементов участков строго возрастания
  int *shared_num = nullptr;     // кол-во элементов участков строго возрастания
  int *status = nullptr;         // массив статусов работы каждого из потоков
  int *result = nullptr;         // массив итогового ответа
  pthread_barrier_t *barrier = nullptr;

public:
  argument () = default;
  ~argument () = default;
};

void * thread_func (void *args);
int count_sum_and_num (const char *filename, double *sum__, int *num__);
int count_greater_than (const char *filename, double x);

#endif




