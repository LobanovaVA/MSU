#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, int m, int n, int i, int j, double b){
	int z;
	double *pi=a+i*n, *pj=a+j*n;
	(void) m;

	for(z=0; z<n; z++) pj[z]+=pi[z]*b;
	
}