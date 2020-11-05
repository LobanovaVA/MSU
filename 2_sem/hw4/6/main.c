#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

int main(void){
    double m, a, b, e, x;
    double *M;
    int ret;

    printf("Input m, a, b, e: ");
    if(scanf("%lf %lf %lf %lf", &m, &a, &b, &e)!=4) return printf("Usage: number m, a, b, x OR Invalid number format\n"), 1;
    if(!(M=(double*)malloc(3*(m+1)*sizeof(double))) )return printf("Not enough memory\n"), 3;
	ret=solve( &f, m, M, a, b, e, &x);

	if(ret<0){
        switch(ret){
            case -1: printf("Root is not found\n");  break;
            default: printf("Uknown error %d", ret);
        }
        free(M);
        return 2;
    }

    printf("X=%lf\nIt(solve)=%d\nIt(f)=%d\n", x, ret, get_count());
    printf("f(X)=%.e\n", f(x));
    free(M);
    return 0;
}
