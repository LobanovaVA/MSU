#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, int n){
	int i, j;
	//double temp;
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++){
		  a[j*n+i]=(-1.)*(a[i*n+j]=0.5*(a[i*n+j]-a[j*n+i]));
            //a[i*n+j]=0.5*(a[i*n+j]-a[j*n+i]);
            //a[j*n+i]=(-1.)*a[i*n+j];
		}
	for(i=0; i<n; i++) a[i*n+i]=0;
}
