#include <stdio.h>
#include <math.h>
#include "h.h"

int main(void){
    double h, x, ret;

    printf("Input x, h: ");
    if(scanf("%lf %lf", &x, &h)!=2) return printf("Usage: number x, h OR Invalid number format\n"), 1;

	ret=solve( &f, x, h);
    printf("ddf(x)=%e\nerror=%e\n", ret, fabs(ret-ddf(x)) );
    return 0;
}
