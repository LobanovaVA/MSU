#include "f.h"

double f(int n, double x0, double *x, double *y, double *d){
	double res=0;
	int i, j;
	for (j=n-1;j>0;j--) 
		y[j]=(y[j]-y[j-1])/(x[j]-x[j-1]);
	
	for(i=2;i<2*n;i++) {
		for(j=2*n-1;j>=i;j--) {
			if(j%2!=0) 	d[j/2]=(d[j/2]-y[j/2])/(x[j/2]-x[(j-i)/2]);
			else y[j/2]=(y[j/2]-d[j/2-1])/(x[j/2]-x[(j-i)/2]);
		}
	}

	res=d[n-1];
	for(i=2*n-2;i>=0;i--) {
		if(i%2==0) res=res*(x0-x[i/2])+y[i/2];
		else res=res*(x0-x[i/2])+d[i/2];
	}
	return res;
}

/*


double f(int n, double x0, double *x, double *y, double *d){

	int i, j; 
	double p=1, s=y[0];

	for(i=1;i<n;i++){
		for(j=n-1;j>=i;j--){
			if(x[j]<x[j-i] || x[j]>x[j-i]) 
				y[j]=(y[j]-y[j-1])/(x[j]-x[j-i]);
			else y[j]=d[j];
		}
		p*=(x0-x[i-1]);
		s+=p*y[i];
	}
	return s;
}


*/