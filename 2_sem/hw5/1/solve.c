#include <math.h>
#include "h.h"

double solve( double (*f)(double), double h, double x)	{
	return (f(x+h)-f(x))/h;
}
