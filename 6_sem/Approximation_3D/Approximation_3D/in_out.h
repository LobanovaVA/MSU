#ifndef IN_OUT_H
#define IN_OUT_H

#include "struct.h"

int parse_command_line (char *argv[], input_info &in, polygon &pol);
int read_polygon (const char *filename, polygon &pol);

#endif // IN_OUT_H
