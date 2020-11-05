#include <math.h>
#include "h.h"

int solve( double (*x)(double), double (*y)(double), double a, double b, double e, double *r){
	int i, it, n=1;
	double h=fabs(b-a), s2,x1,x2,y1,y2, xa=x(a), xb=x(b), ya=y(a), yb=y(b), s=sqrt(pow(xa-xb,2)+pow(ya-yb,2));

	for(it=0; it<MAX_IT; it++){
		s2=0;
		x1=xa; y1=ya;
		for(i=1; i<2*n; i++)	{
			x2=x(a+i*(h/2.0));
			y2=y(a+i*(h/2.0));
			s2+=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
			x1=x2; y1=y2;
		}
		s2+=sqrt(pow(x1-xb,2)+pow(y1-yb,2));
    	if(fabs(s2-s)<e) break;
    	s=s2; h/=2.0; n*=2;
	}

	if(it>=MAX_IT) return -1;
	else return *r=s2, 2*n; 
}
