#include <stdio.h>
#include <math.h>
#include "h.h"

void solve(double *a, int m, int n){
	int i, j, z, imax=0, jmax=0;
	double  max=a[0], fabs_aij, temp, *pi, *pj;
	
	for(i=0; i<m; i++) {
		pi=a+i*n;
		for(j=0; j<n; j++){
			fabs_aij=fabs(pi[j]);
			if(max<fabs_aij) {	max=fabs_aij; imax=i;	jmax=j;		}
		}
	}
	pi=a; pj=a+imax*n;
	for(z=0; z<n; z++){
		temp=pi[z];
		pi[z]=pj[z];
		pj[z]=temp;
	}
	pi=a; pj=a+jmax;
	for(z=0; z<m*n; z+=n){
		temp=pi[z];
		pi[z]=pj[z];
		pj[z]=temp;
	}

}


