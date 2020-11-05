#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, double *x0, double *x, double *b, double *r, int m, int n){
	int i, j;
	double tau, temp, sc1, sc2;
	for(i=0; i<m; i++) {
		b_Ax(a, x0, x, b, n);   // -R_k-1 = B-A*X_k-1 записываем в Х
		Ax(a, x, r, n);			// A*R_k-1 записываем в R
        sc1=0; sc2=0;
		for(j=0; j<n; j++){
			temp=x[i]; sc1+=temp*temp;
			temp=r[i]; sc2+=temp*temp;
		}
        if(sc2>=0 && sc2<=0) { printf("\nSC2=0\n"); break; }
		tau=sc1/sc2;
        if(tau>=0 && tau<=0) { printf("\nTAU=0\n"); break; }
		for(j=0; j<n; j++) x0[j]+=tau*x[j];
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

void Ax(double *a, double *x0, double *x, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		x[i]=s;
		pa+=n;
	}
}

