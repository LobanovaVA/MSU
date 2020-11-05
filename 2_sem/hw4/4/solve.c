#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x){
	int it=0;
	double c, fa=f(a), fb=f(b), fc;
	if(fabs(fa)<EPS) return *x=a, it;
	if(fabs(fb)<EPS) return *x=b, it;

	for(it=1; it<MAX_IT; it++){
		if(!(fa>fb || fa<fb)) return -1;
		c=(fb*a-fa*b)/(fb-fa);
		if(!(a>c || a<c) || !(b>c || b<c)) break;
		fc=f(c);
        
		if(fabs(fc)<EPS) break;

		if(fabs(fc)>fabs(fa) && fabs(fc)>fabs(fb)) return -1;
		else {
			if(fabs(fb)>=fabs(fa)) { b=c; fb=fc; }
			else {
				if(fabs(fa)>=fabs(fb)) { a=c; fa=fc; }
				else return -1;
			}
		}

		if(fabs(b-a)<e) break;
	}
	if(it>=MAX_IT) return -1;
	else return *x=c, it; 
}
