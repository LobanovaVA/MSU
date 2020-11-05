#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x){
	int it=0;
	double c, fa=f(a), fb=f(b), fc;
	if(fa*fb>0) return -1;
	if(fabs(fa)<EPS) return *x=a, it;
	if(fabs(fb)<EPS) return *x=b, it;

	for(it=1; it<MAX_IT; it++){
		c=(fb*a-fa*b)/(fb-fa);
        if(!(a>c || a<c) || !(b>c || b<c)) break;
		fc=f(c);
		//if(!(fc>0 || fc<0)) break;
		if(fabs(fc)<EPS) break;

		if(fa*fc<0) { b=c; fb=fc; }
		else if(fb*fc<0) { a=c; fa=fc; }
		if((b-a)<e) break;
	}

	if(it>=MAX_IT) return -1;
	else return *x=c, it; 
}
