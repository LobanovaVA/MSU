#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, int m, int n, int i, int j){
	int z;
	double temp, *pi=a+i*n, *pj=a+j*n;
	(void) m;

	for(z=0; z<n; z++){
		temp=*(pi+z);
		*(pi+z)=*(pj+z);
		*(pj+z)=temp;

	}
	
}