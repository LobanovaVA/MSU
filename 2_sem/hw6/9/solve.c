#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, int m, int n, double *b, double *c){
	int i, j;
	double s, *pai;

	for(i=0; i<m; i++){
		s=0;
		pai=a+i*n;
		for(j=0; j<n; j++)	s+=pai[j]*b[j];
		c[i]=s;
	}
}