#include <math.h>
#include "h.h"

int solve( double (*f)(double), double x0, double e, double *x){
	int it=0;
	double c;
	
	//if(fabs(fx0)<e) return *x=x0, it;
	for(it=1; it<MAX_IT; it++){
		c=f(x0);
		if(fabs(c-x0)<e) break;
		x0=c;
	}

	if(it>=MAX_IT) return -1;
	else return *x=c, it; 
}
