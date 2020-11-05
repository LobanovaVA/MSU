#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, double *x0, double *x, double *b, double *r, double *u, int m, int n){
	int i, j;
	double tau, temp, sc1, sc2, s, *pa;
	pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j*n]*b[j];	// A_t*B записываем в B
		x[i]=s;
		pa++;
	}
	for(i=0; i<n; i++) b[i]=x[i];

	for(i=0; i<m; i++) {
		b_AAx(a, x0, x, b, u, n);   // -R_k-1 = B-A*X_k-1 записываем в Х
		AAx(a, x, r, u, n);			// A*R_k-1 записываем в R
        sc1=0; sc2=0;
        for(j=0; j<n; j++){
            temp=r[i];
            sc1+=temp*x[i];
            sc2+=temp*temp;
        }
        if(sc2>=0 && sc2<=0) { printf("\nSC2=0\n"); break; }
        tau=sc1/sc2;
        if(tau>=0 && tau<=0) { printf("\nTAU=0\n"); break; }
		for(j=0; j<n; j++) x0[j]+=tau*x[j];
	}
	for(i=0; i<n; i++) x[i]=x0[i];
}

void b_AAx(double *a, double *x0, double *x, double *b, double *u, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		u[i]=s;
		pa+=n;
	}
	pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j*n]*u[j];
		x[i]=b[i]-s;
		pa++;
	}

}

void AAx(double *a, double *x0, double *x, double *u, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		u[i]=s;
		pa+=n;
	}
	pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j*n]*u[j];
		x[i]=s;
		pa++;
	}

}

