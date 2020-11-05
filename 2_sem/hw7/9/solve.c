#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, int m, int n){
	int i, j;
	double *pa;
	
	for(i=1; i<m-1; i++) {
		pa=a+(i-1)*n;
		for(j=n-2; j>0; j--) 
			pa[n+j]=0.2*(pa[j]+pa[n+j-1]+pa[2*n+j]+pa[n+j+1]);
	}

}


