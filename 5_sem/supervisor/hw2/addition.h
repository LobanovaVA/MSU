#ifndef ALL_FUNC_H
#define ALL_FUNC_H

#define MAX_PRINT 20
#define M_MAX_PRINT 10
#define N_MAX_PRINT 5
#define N 1<<20
#define LEN 1234
#define SUCCESS 0

#define ERROR_CANNOT_OPEN_INPUT_FILE -10
#define ERROR_CANNOT_OPEN_INPUT_FILE_A -11
#define ERROR_CANNOT_OPEN_INPUT_FILE_B -12

#define ERROR_CANNOT_READ_INPUT_FILE -20
#define ERROR_CANNOT_WRITE_IN_FILE -30

#define ERROR_NOT_ENOUGH_MEMMORY -40

#define EMPTY_STR_S -50
#define ERROR_STR_S -51

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char * edit (char *str, int *fl, char param);
int problem_1 (const char *file_name_A, const char *file_name_B, const char *str_s);
int problem_2 (const char *file_name_A, const char *file_name_B, const char *str_s);

int problem_3 (const char *file_name_A, const char *file_name_B, const char *str_s);
char * clear_edit_3 (char *str, int *fl);

int problem_4 (const char *file_name_A, const char *file_name_B, const char *str_s);
char * clear_edit_4 (char *str, int *fl);


int check_incr (const char *str, char param);

int problem_5 (const char *file_name_A, const char *file_name_B, const char *str_s);
int check_with_dot (const char *buf, const char *str);

int problem_6 (const char *file_name_A, const char *file_name_B, const char *str_s);
int check_with_query (const char *buf, const char *str);
int check_with_query_rec (const char *buf, const char *str, int i, int j);

char * edit_like_with_plus (char *str, int *fl, char param);

int problem_7 (const char *file_name_A, const char *file_name_B, const char *str_s);
int check_with_plus (const char *buf, const char *str);

int problem_8 (const char *file_name_A, const char *file_name_B, const char *str_s);
int check_with_star (const char *buf, const char *str);

int problem_9 (const char *file_name_A, const char *file_name_B, const char *str_s);
int check_correct_bracket (const char *str);
int check_with_bracket (const char *buf, const char *str);
#endif

