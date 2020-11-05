#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *r){
	int i, it, n=1;
	double h=fabs(b-a), s=h*f(a)/2.0 + h*f(b)/2.0, s2, sdop;

	for(it=0; it<MAX_IT; it++){
		sdop=0;
		for(i=0; i<n; i++)	sdop+=f(a+(2*i+1)*(h/2.0));
		s2=(0.5)*s+(h/2.0)*sdop;

    	if(fabs(s2-s)<e) break;
    	s=s2; h/=2.0; n*=2;
	}

	if(it>=MAX_IT) return -1;
	else return *r=s2, 2*n; 
}
