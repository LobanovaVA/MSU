#include <math.h>
#include "h.h"

double solve( double (*f)(double), double a, double b, int n)	{
	double h=(b-a)/(2.0*n), s=0, x1=a, x2=a+h, x3=a+2.0*h, f1=f(x1), f2=f(x2), f3=f(x3);
	int i;
	for(i=0; i<n; i++)	{
		s+=integral(x1, x2, x3, f1, f2, f3);
		x1=x3; x2+=2.0*h; x3+=2.0*h; 
		f1=f3; f2=f(x2); f3=f(x3); 
	}
	return s;
}

double integral(double x1, double x2, double x3, double f1, double f2, double f3){
	double  a=( (f1-f2)/(x1-x2) - (f2-f3)/(x2-x3) )/(x1-x3), 
			b=(f1-f2)/(x1-x2) - (x1+x2)*( ( (f1-f2)/(x1-x2)-(f2-f3)/(x2-x3) )/ (x1-x3) ), 
			c=f1-x1*(f1-f2)/(x1-x2)+x1*x2*( ( (f1-f2)/(x1-x2)-(f2-f3)/(x2-x3) )/ (x1-x3) ),
			sgn1=1.0, sgn3=1.0;
	
	if(x1<0) sgn1=-1.0;	
	if(x3<0) sgn3=-1.0;
	return  (2.0/5.0)*a*( pow(fabs(x3), 2.5)-pow(fabs(x1), 2.5) )+
			(2.0/3.0)*b*( pow(fabs(x3), 1.5)-pow(fabs(x1), 1.5) )+
			 2.0*c*( sgn3*pow(fabs(x3), 0.5)-sgn1*pow(fabs(x1), 0.5) );
}