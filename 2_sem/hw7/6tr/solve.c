#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

double solve(double *a, double *b, int m, int n){
	int k;
	double max=rk(a, b, m, n, 0), f;
	for(k=1; k<m;  k++) {
		f=fabs(rk(a, b, m, n, k));
		if(max<f) max=f;
	}
	return max;
}

double rk(double *a, double *b, int m, int n, int k){
	
	int i;
	double rk=0;
	(void) n;
	for(i=0; i<m; i++) rk+=fabs(rij(a,b,m,n,i,k));
	return rk;
}

double rij(double *a, double *b, int m, int n, int i, int j){
	int z, zm=0;
	double ret=0, *pa=a+i*n, *pb=b+j;
	//for(z=0; z<n; z++) ret+=pa[z]*pb[z*m];
	for(z=0; z<n; z++, zm+=m) ret+=pa[z]*pb[zm];
	if(i==j) ret--;
	return ret;
}



