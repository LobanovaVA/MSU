#include<math.h>
#include"h.h"

double f(double x) { return x+2; }

double intf(double x1, double x3) { 
	double sgn1=1, sgn3=1;
	if(x1<0) sgn1=-1;	
	if(x3<0) sgn3=-1;
	return  (2.0/5.0)*0*( pow(fabs(x3), 2.5)-pow(fabs(x1), 2.5) )+
			(2.0/3.0)*1*( pow(fabs(x3), 1.5)-pow(fabs(x1), 1.5) )+
			 2.0*2*( sgn3*pow(fabs(x3), 0.5)-sgn1*pow(fabs(x1), 0.5) );
}
