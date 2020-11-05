#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

double solve(double *a, double *x, double *b, int m, int n){
	int k;
	double s=0;
	for(k=0; k<m;  k++) s+=fabs(rk(a,x, b, m, n, k));
	return s;
}

double rk(double *a, double *x, double *b, int m, int n, int k){
	int z;
	double rk=0, *p=a+k*n;
	(void) m;
	for(z=0; z<n; z++) rk+=p[z]*x[z];
	rk-=b[k];
	return rk;
}
