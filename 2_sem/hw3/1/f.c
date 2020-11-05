#include "f.h"

double f(int n, double x0, double *x, double *y){
	int i, j; 
	double g, s=0;

	for(i=0; i<n; i++){
		g=1;
		for(j=0;j<n;j++){
			if(i!=j) g=g*(x0-x[j])/(x[i]-x[j]);
		}
		s+=g*y[i];
	}
	return s;
}