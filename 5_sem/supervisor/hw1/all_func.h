#ifndef ALL_FUNC_H
#define ALL_FUNC_H

#define MAX_PRINT 20
#define M_MAX_PRINT 10
#define N_MAX_PRINT 5
#define N 1<<20
#define LEN 1234

#define ERROR_CANNOT_OPEN_INPUT_FILE -10
#define ERROR_CANNOT_OPEN_INPUT_FILE_A -11
#define ERROR_CANNOT_OPEN_INPUT_FILE_B -12

#define ERROR_CANNOT_READ_INPUT_FILE -20
#define ERROR_CANNOT_READ_INPUT_FILE_A -21
#define ERROR_CANNOT_READ_INPUT_FILE_B -22

#define ERROR_EMPTY_INPUT_FILE -30
#define ERROR_EMPTY_INPUT_FILE_A -31
#define ERROR_EMPTY_INPUT_FILE_B -32

#define ERROR_NOT_ENOUGH_MEMMORY -40

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


//Series
int problem_1_1 (const char* file_name, int k);
int problem_1_2 (const char* file_name_A, const char* file_name_B);
int problem_1_3 (const char* file_name, double* d);
int problem_1_4 (const char* file_name);

//Arrays
int rand_array (double *arr, int size);
int read_array (const char *file_name, double *arr, int size);
void print_array (double *arr, int size);

int search_subserie (const char *file_name, double *arr, int size);
int remove_less_x (double* arr, int size, double x);
void right_move_to_k (double *arr, int size, int k);
int gcd (int a, int b);
//Sorts
void check_sort (double *arr, int size);
void swap (double *a, int i, int j);

int bin_search (const double *arr, int size, double x);
void merge (int size_1, int size_2, const double *arr_1, const double *arr_2, double *arr_ans);
int lin_redbuild (double *arr, int size, double x);
void bin_insert_sort (double *arr, int size);
void merge_sort (double *arr_1, double *arr_2, int size);
void quick_sort (double *arr, int size);
void heap_sort (double *a, int n);
void first_rebuild (double* arr, int size);
void max_tree (double *arr, int size, int j);

//Strings
int read_str_array (const char *file_name, char **arr, int size);
void print_str_array (char **arr, int size);

size_t strcspn_ (const char *string1, const char *string2);
int problem_4_2 (char **arr, int size, int k, char *str);
int problem_4_3 (char **arr, int size, int k, char *str);

int read_str_matrix (const char *file_name, char** matrix, int m_size, int n_size, char* space);
void print_str_matrix (char **matrix, int m_size, int n_size);
void sort_matrix (char **matrix, int m_size, int n_size);
void free_matrix (char **matrix, int m_size, int n_size);

void quick_sort_str (char **matrix, int m_size, int n_size);
int lin_redbuild_str (char **matrix, int m_size, int n_size, int i);
void swap_lines (char **matrix, int n_size, int i, int j);

int cmp_lines (char **matrix, int n_size, int i, int j);
int cmp_lines_elem (char **matrix, int n_size, int i, char *j);
int max_of_line (char **matrix, int n_size, int i);


#endif

