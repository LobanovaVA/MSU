#include <math.h>
#include "h.h"

double solve( double (*f)(double), double a, double b, int n)	{
	double h=(b-a)/(2.0*n), s0=0, s1=f(a+h);
	int i;
	for(i=1; i<n; i++)	{
		s0+=f(a+2*i*h);
		s1+=f(a+(2*i+1)*h);
	}
	return h*f(a)/3.0 + 2.0*h*s0/3.0 + 4.0*h*s1/3.0 + h*f(b)/3.0;
}
