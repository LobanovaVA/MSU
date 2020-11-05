#ifndef ADDITION_H
#define ADDITION_H

#include "student.h"

#define MAX_PRINT 10
#define ERROR_CANNOT_OPEN_INPUT_FILE -1
#define ERROR_CANNOT_READ_INPUT_FILE -2
#define ERROR_CANNOT_READ_CLASS -3
#define ERROR_CANNOT_INITIALIZE_STUDENT_NAME 

int read_array (const char *name, student* a, int n);
void print_array (student* a, int n, FILE* out = stdout);
bool sort_control (student* a, int n);

#endif
