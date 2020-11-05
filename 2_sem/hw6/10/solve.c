#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, double *b, double *c,  int m, int n, int k){
	int i, j, z;
	double s, *pai, *pbj, *pci;

	for(i=0; i<m; i++)
		for(j=0; j<k; j++){
			s=0; 
			pai=a+i*n;
			pbj=b+z*k;
			pci=c+i*k;
			for(z=0; z<n, zz<m*n; z++) s+=pai[z]*b[z*k+j];
			pci[j]=s;
			
			
			//for(z=0; z<n; z++) s+=a[i*n+z]*b[z*k+j];
			//c[i*k+j]=s;
	}
}