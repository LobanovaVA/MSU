#include <math.h>
#include "h.h"

double solve( double (*f)(double), double x, double h)	{
	return (f(x+h)-f(x-h))/(2.0*h);
}
