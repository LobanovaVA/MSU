#include <math.h>
#include "h.h"

int solve( double (*f)(double), double (*d)(double), double x0, double e, double *x){
	int it=0;
	double c, fx0=f(x0), dx0=d(x0);
	
	if(fabs(fx0)<e) return *x=x0, it;

	for(it=1; it<MAX_IT; it++){
		if(!(dx0>0 || dx0<0)) return -1;
		//if(fabs(dx0)<EPS) return -1;
		c=x0-fx0/dx0;
		if(!(x0>c || x0<c)) break;
		x0=c; fx0=f(c); dx0=d(c);

		if(fabs(fx0)<e) break;
		//if(!(fc>0 || fc<0)) break; //критерий выхода
	}

	if(it>=MAX_IT) return -1;
	else return *x=c, it; 
}
