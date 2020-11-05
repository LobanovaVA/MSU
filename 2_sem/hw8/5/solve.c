#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, double *x0, double *x, double *b, double tau, int m, int n){
	int i, j;
	double ans, sc1=0, sc2=0, *pa;
	for(i=0; i<m; i++) {
		b_Ax(a, x0, x, b, n);   // B-A*X_k-1 записываем в Х
		pa=a;
		for(j=0; j<n; j++){     // умножаем на tau D^-1 записываем в R
			x[i]*=tau/(*pa);
			pa+=n+1;
			x0[i]+=x[i];
		}
	}
	for(i=0; i<n; i++) x[i]=x0[i];
}

void b_Ax(double *a, double *x0, double *x, double *b, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		x[i]=b[i]-s;
		pa+=n;
	}
}



