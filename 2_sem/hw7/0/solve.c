#include <stdio.h>
#include<stdlib.h>
#include "h.h"

int solve(double *a, int m, int n){
	int i, j, fl=1;
	for(i=0; i<m; i++)
		for(j=1; j<n; j++)
			if( (*(a+i*n+j)>*(a+j*n+i)) || (*(a+i*n+j)<*(a+j*n+i)) ) return 0;
	return fl;
}