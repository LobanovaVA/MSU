#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x){
	int it=0;
	double fa=f(a), fb=f(b), s=(sqrt(5)+1)*0.5;

	for(it=1; it<MAX_IT; it++){
		if(fabs(b-a)<e) break;
		if(fa<fb) { a=a+(b-a)/s; fa=f(a); }
		else { b=b-(b-a)/s; fb=f(b); } 
	}


	if(it>=MAX_IT) return -1;
	else return *x=fb, it; 
}
