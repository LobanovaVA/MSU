#ifndef ADDITION_H
#define ADDITION_H

#define ERROR_CANNOT_OPEN_INPUT_FILE -11
#define ERROR_CANNOT_READ_INPUT_FILE -12

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int func (const char *filename);
//static void process_function (const char *filename, int my_rank, int p);

#endif
