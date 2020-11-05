#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

double  solve(double *a, int m, int n){
	int i;
	double max=fi(a, m, n, 0), f;
	for(i=1; i<m; i++) {
		f=fi(a, m, n, i);
		if(max<f) max=f;
	}
	return max;
}

double fi(double *a, int m, int n, int i){
	int j;
	double s=0, *p=a+i*n;
	(void) m;

	for(j=0; j<n; j++) s+=fabs(p[j]);
	return s;
}
