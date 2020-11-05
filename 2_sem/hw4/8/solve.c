#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x){
	int it=0;
	double h=(b-a)/10.0, x0=a, x1, f0=f(x0), f1;

	for(it=1; it<MAX_IT; it++){
		if(fabs(h)<e) break;
		x1=x0+h;
		f1=f(x1);
		//if((x1<b)) { a=x0; b=x1; h/=(-10.0);}
		//if(!(x1>a)) { a=x1; b=x0; h/=(-10.0);}
        if(!(x1<b)) { x1=b; h/=(-10.0);}
        if(!(x1>a)) { x1=a; h/=(-10.0);}
        if(f0>f1) h/=(-10.0);
		x0=x1; f0=f1;
	}

	if(it>=MAX_IT) return -1;
	else return *x=f1, it; 
}
