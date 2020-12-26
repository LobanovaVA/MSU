#ifndef ADDITION_H
#define ADDITION_H

#define MAX_PRINT 10

#define SUCCESS 0
#define ERR_USAGE_ARGC 1
#define ERR_ALLOCATE_MEMORY 2
#define ERR_DATA_INIT 3
#define ERR_PTHREAD_BARRIER_INIT 4
#define ERR_PTHREAD_CREATE 5

#define E_EMPTY -271

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <memory>


class argument
{
public:
  int p = 0;
  int k = 0;

  int size_1 = 0;
  int size_2 = 0;

  double *matrix = nullptr;

  double *prev_str = nullptr;
  double *next_str = nullptr;
  double *buff_str = nullptr;

  double *shared_sum = nullptr;
  int *shared_num = nullptr;

  int *result = nullptr;
  double *time = nullptr;

  pthread_barrier_t *barrier = nullptr;

public:
  argument () = default;
  ~argument () = default;
};


/* === Time === */
double get_full_time ();
double get_cpu_time ();


/* === Initialization === */
double f (int i, int j);
int read_matrix (const char *filename, double *matrix, int size_1, int size_2);
int check_read_errors (int ret, const char *filename);
void init_matrix (double *matrix, int size_1, int size_2);
void print_matrix (double *matrix, int size_1, int size_2);
void get_line (int i, double *line, double *matrix, int size_1, int size_2);


/* === Solve === */
void * thread_func (void *args);
void count_sum_num (double *matrix, int size_1, int size_2, int l, int r,
                    double *prev_str, double *next_str, double &sum, int &num);
void replace_elem (double *matrix, int size_1, int size_2, int l, int r,
                   double *prev_str, double *next_str, double *buff_str, double value);
#endif




