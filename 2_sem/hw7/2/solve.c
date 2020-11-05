#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

double  solve(double *a, int m, int n){
	int j;
	double max=fi(a, m, n, 0), f;
	for(j=1; j<n;  j++) {
		f=fi(a, m, n, j);
		if(max<f) max=f;
	}
	return max;
}

double fi(double *a, int m, int n, int j){
	
	int in;
	double s=0, *p=a+j;
	(void) m;
	for(in=0; in<n*m; in+=n) s+=fabs(p[in]);
	return s;
}
