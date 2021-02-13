#ifndef TIME_H
#define TIME_H

#include "addition.h"

#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>

double get_cpu_time ();
double get_full_time ();

#endif

