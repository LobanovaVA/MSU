#include <stdio.h>
#include<stdlib.h>
#include "h.h"

void solve(double *a, int m, int n, int i, int j){
	int z;
	double temp, *pi=a+i, *pj=a+j;
	for(z=0; z<m*n; z+=n){
		temp=*(pi+z);
		*(pi+z)=*(pj+z);
		*(pj+z)=temp;
		
		/*
		temp=a[z*n+i];
		a[z*n+i]=a[z*n+j];
		a[z*n+j]=temp;
		*/
	}
	
}