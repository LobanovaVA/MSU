#ifndef ADDITION_H
#define ADDITION_H

#define MAX_PRINT 10

#define SUCCESS 0
#define ERR_USAGE_ARGC 1
#define ERR_ALLOCATE_MEMORY 2
#define ERR_DATA_INIT 3
#define ERR_PTHREAD_BARRIER_INIT 4
#define ERR_PTHREAD_CREATE 5

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
  int size = 0;
  double *arr = nullptr;
  double *tmp_sum = nullptr;
  int *tmp_num = nullptr;
  int *border = nullptr;
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
double f (int n, int i);
int read_array (const char *filename, double *array, int size);
int check_read_errors (int ret, const char *filename);
void init_array (double *array, int size);
void print_array (double *array, int size);

/* === Solve === */
void * thread_func (void *args);
void replace_inner (double *arr, int l, int r, double &b_sum, int &b_num,
                    double &e_sum, int &e_num, int &border, int &result);
void gluing_previous (double *arr, int p, int k, int size, double *e_sum,
                      int *e_num, int *border, double &sum, int &count);
void gluing_following (double *arr, int p, int k, int size, double *b_sum,
                       int *b_num, int *border, double &sum, int &count);
#endif




