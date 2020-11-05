#include <math.h>
#include "h.h"

double solve( double (*f)(double), double a, double b, int n)	{
	double h=(b-a)/n, s=0, x1=a, x2=a+h, f1=f(x1), f2=f(x2);
	int i;
	for(i=0; i<n; i++)	{
		s+=integral(x1, x2, f1, f2);
		f1=f2; 
		x1=x2;
		x2+=h;
		f2=f(x2);
	}
	return s;
}

double integral(double x1, double x2, double f1, double f2){
	double a=(f1-f2)/(x1-x2), b=(x1*f2-x2*f1)/(x1-x2), sgn1=1.0, sgn2=1.0;
	if(x1<0) sgn1=-1.0;
	if(x2<0) sgn2=-1.0;
	return (2.0/3.0)*a*( pow(fabs(x2), 1.5)-pow(fabs(x1), 1.5) )+2.0*b*( sgn2*pow(fabs(x2), 0.5)-sgn1*pow(fabs(x1), 0.5) );
}
