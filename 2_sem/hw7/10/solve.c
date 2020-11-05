#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, int m, int n){
	int i, j;
	double *pa;
	
	for(i=m-2; i>0; i--) {
		pa=a+(i-1)*n;
		for(j=1; j<n-1; j++)
			pa[n+j]=0.2*(pa[j]+pa[n+j-1]+pa[2*n+j]+pa[n+j+1]);
	}

}


