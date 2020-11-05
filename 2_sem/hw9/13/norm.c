#include <math.h>
#include "h.h"
#define N 40

void mult_matrix(double *a, double *b, double *c, int n){
	int bm, bi, nbm, nbi;
	int l, nl;
	int i, j, m;
	double *pa, *pb, *pc, s;

	for(bm=0; bm<n; bm+=N){
		nbm=(bm+N<=n?bm+N:n);
		for(bi=0; bi<n; bi+=N){
			nbi=(bi+N<=n?bi+N:n);
			for(m=bm, pc=c+bm; m<nbm; m++, pc++)
			for(i=bi; i<nbi; i++)
			pc[i*n]=0.;
			for(l=0; l<n; l+=N){
				nl=(l+N<=n?l+N:n);
				for(m=bm, pc=c+bm; m<nbm; m++, pc++)
				for(i=bi, pb=b+m; i<nbi; i++){
					pa=a+l+i*n;
					for(s=0., j=l; j<nl; j++)
						s+= *(pa++)*pb[j*n];
					pc[i*n]+=s;
				}
			}
		}
	}
}




double norm1(double *a, int n){
	int i;
	double max=fi(a, n, 0), f;
	for(i=1; i<n; i++) {
		f=fi(a, n, i);
		if(max<f) max=f;
	}
	return max;
}
double fi(double *a, int n, int i){
	int j;
	double s=0, *p=a+i*n;
	for(j=0; j<n; j++) s+=fabs(p[j]);
	return s;
}


double norm2(double *a, int n){
	int j;
	double max=fj(a, n, 0), f;
	for(j=1; j<n;  j++) {
		f=fj(a, n, j);
		if(max<f) max=f;
	}
	return max;
}
double fj(double *a, int n, int j){
	int in;
	double s=0, *p=a+j;
	for(in=0; in<n*n; in+=n) s+=fabs(p[in]);
	return s;
}



double norm3(double *a, int n){
	double s=0., temp;
	int i;
	for(i=0; i<n*n; i++) {
		temp=a[i];
		s+=temp*temp;
	}
	return sqrt(s);
}
