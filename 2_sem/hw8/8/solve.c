#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

void solve(double *a, double *x0, double *x, double *r, int m, int n){
	int i;
	double temp, ans, sc1=0, sc2=0, *p;
	for(i=0; i<m+1; i++) {
		AAx(a, x0, x, r, n);
		p=x0; x0=x; x=p;
	}
	for(i=0; i<n; i++){
		temp=x[i];
		sc1+=x0[i]*temp;
		sc2+=temp*temp;
	}
    if(sc2>=0 && sc2<=0) { printf("\nSC2=0\n"); break; }
    ans=sc1/sc2;
	if(m&1) x[0]=ans;
	else   x0[0]=ans;

}

void AAx(double *a, double *x0, double *x, double *r, int n){
	int i, j;
	double s, *pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j]*x0[j];
		r[i]=s;
		pa+=n;
	}
	pa=a;
	for(i=0; i<n; i++){
		s=0;
		for(j=0; j<n; j++)	s+=pa[j*n]*r[j];
		x[i]=s;
		pa++;
	}

}

