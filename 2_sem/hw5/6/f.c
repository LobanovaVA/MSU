#include<math.h>
#include"h.h"

double f(double x) { return x; }

double intf(double x1, double x2) { 
	double sgn1=1.0, sgn2=1.0;
	if(x1<0) sgn1=-1.0;
	if(x2<0) sgn2=-1.0;
	return (2.0/3.0)*1*( pow(fabs(x2), 1.5)-pow(fabs(x1), 1.5) )+2.0*0*( sgn2*pow(fabs(x2), 0.5)-sgn1*pow(fabs(x1), 0.5) );
}
