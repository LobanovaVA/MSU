#include <math.h>
#include "h.h"

int integral( double (*g)(double, double), double x, double a, double b, double e, double *r){
	int i, it, n=1;
	double h=fabs(b-a)/2, fa=g(x,a), fb=g(x,b), snew, s1new, s2new, s1=0, s2=h*g(x,a+h),  s=(h/3.0)*fa + (4.0/3.0)*s2 + (h/3.0)*fb;

	for(it=0; it<MAX_IT; it++){

		s1new=0.5*(s1+s2);
		s2new=0;
		for(i=0; i<2*n; i++)	s2new+=g(x,a+(2*i+1)*(h/2.0));
		s2new*=(h/2.0);
		snew=(h/6.0)*fa + (2.0/3.0)*s1new +(4.0/3.0)*s2new + (h/6.0)*fb;

    	if(fabs(snew-s)<e) break;
        s=snew; s1=s1new; s2=s2new; h/=2.0; n*=2;
	}

	if(it>=MAX_IT) return -1;
	else return *r=snew, 2*n; 
}
