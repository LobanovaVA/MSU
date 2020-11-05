#include <math.h>
#include "h.h"

double solve( double (*f)(double), double a, double b, int n)	{
	double h=(b-a)/n, s=0;
	int i;
	for(i=1; i<n; i++)	s+=f(a+i*h);
	return h*f(a)/2.0+h*s+h*f(b)/2.0;
}
