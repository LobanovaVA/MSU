#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double a, r, e, ret;

    printf("Input a, e: ");
    if(scanf("%lf %lf", &a, &e)!=2) return printf("Usage: number a, e OR Invalid number format\n"), 1;

	ret=solve( &f, a, e, &r);
	if(ret<0) return printf("Integral is not found\n"), 2; 
    printf("Integral(f(x)dx)=%e\nerror=%e\nb=%lf\n", r, fabs(r-intf(a)), ret );
    return 0;
}
