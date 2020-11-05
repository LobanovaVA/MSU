#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "h.h"

int solve(double *a, double *b, int n){
	int i, j, k, i_max, ind[n], count=0;
	double *pa1, *pb1, *pa2, *pb2;
	double a_max, temp, EPS=1e-15;

		a_max=a[0];
		for(k=0; k<n*n; k++) {
			temp=fabs(a[k]);
			if(temp>a_max) a_max=temp;
		}
		if(a_max<1.0) EPS*=a_max;


	for(k=0; k<n; k++) ind[k]=k;
	for(k=0; k<n; k++){
		
		pa1=a+k*n; pb1=b+k*n;
		i_max=k; a_max=fabs(pa1[k]);
		for(j=k+1; j<n; j++) {
			temp=fabs(pa1[j]);
			if(temp>a_max) { a_max=temp; i_max=j;}
		}

		if(a_max<EPS) return 1;
		if(k!=i_max) {
			change_columns(a,n,n,k,i_max);
			i=ind[k];
			ind[k]=ind[i_max];
			ind[i_max]=i;
		}


		temp=pa1[k];
		for(j=k+1; j<n; j++) pa1[j]/=temp;
		for(j=0;   j<n; j++) pb1[j]/=temp;


		for(i=k+1; i<n; i++) {
		 	pa2=a+i*n; pb2=b+i*n;
		 	temp=pa2[k];
		 	for(j=k+1; j<n; j++) pa2[j]-=temp*pa1[j]; 
			for(j=0;   j<n; j++) pb2[j]-=temp*pb1[j]; 
		}
	}


	for(k=n-1; k>0; k--){
		pa1=a+k*n; pb1=b+k*n;
		for(i=k-1; i>=0; i--) {
		 	pa2=a+i*n; pb2=b+i*n;
		 	temp=pa2[k];
			for(j=0; j<n; j++) pb2[j]-=temp*pb1[j]; 
		}
	}


	for(k=0; k<n; k++){
		i=ind[k];
		while(i!=k){
			change_strings(b,n,n,k,i);
			ind[k]=ind[i];
			ind[i]=i;
			i=ind[k];
			count++;
			if(count>n) return 0;

		}

	}

	return 0;
}

void change_columns(double *a, int m, int n, int i, int j){
	int z;
	double temp, *pi=a+i, *pj=a+j;
	for(z=0; z<m*n; z+=n){
		temp=pi[z];
		pi[z]=pj[z];
		pj[z]=temp;
	}
}

void change_strings(double *a, int m, int n, int i, int j){
	int z;
	double temp, *pi=a+i*n, *pj=a+j*n;
	(void) m;
	for(z=0; z<n; z++){
		temp=*(pi+z);
		*(pi+z)=*(pj+z);
		*(pj+z)=temp;
	}
}
