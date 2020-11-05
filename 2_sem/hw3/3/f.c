#include "f.h"

double f(int n, double x0, double *x, double *y){
	int i, j; 
	for(i=1;i<n;i++)
		for(j=n-1;j>=i;j--)
			y[j]=( y[j]*(x0-x[j-i])-y[j-1]*(x0-x[j]) ) / (x[j]-x[j-i]);

	return y[n-1];
}