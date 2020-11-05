#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, double *x0, double *x, double *b, double *r, double tau, int m, int n){
	int i, j, k, z;
	double s, *pa;
	for(i=0; i<m; i++) {
		b_Ax(a, x0, x, b, tau, n);   // tau*(B-A*X_k-1) записываем в R
		pa=a+(n-1)*n;
		for (j=n-1; j>=0; j--) {
			s=0;
            for (k=n-1; k>j; k--) s+=r[k]*pa[k];
            if(pa[j]>=0 && pa[j]<=0) { printf("element=0"); break;}
            r[j]=(x[j]-s)/pa[j];
            pa-=n;
        }
        for (k=0;k<n;k++) x0[k]+=r[k];
	}
	for(i=0; i<n; i++) x[i]=x0[i];
}

void b_Ax(double *a, double *x0, double *x, double *b, double tau, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		x[i]=tau*(b[i]-s);
		pa+=n;
	}
}

