extern int ERR;
#include <math.h>
#include "h.h"

int solve( double (*f)(double, double), double a, double b, double e, double *x){
	int it=0;
	double c, fa=f(a,e), fb=f(b,e), fc, eps=1e-10;
	if(ERR) return -1;
	if(fa*fb>0) return -1;
	if(fabs(fa)<e) return *x=a, it;
	if(fabs(fb)<e) return *x=b, it;

	for(it=1; it<MAX_IT; it++){
		if((b-a)<10*eps) eps=e;
		//{	if(e>0.1*eps) eps=e; else eps*=0.1;	}

		c=(a+b)/2;
		if(!(a>c || a<c)) break;
		fc=f(c,eps);
		if(ERR) return -1;
		if(fabs(fc)<eps) break;

		if(fa*fc<0) { b=c; fb=fc; }
		else if(fb*fc<0) { a=c; fa=fc; }
		if((b-a)<eps) break;
	}

	if(it>=MAX_IT) return -1;
	else return *x=c, it; 
}
