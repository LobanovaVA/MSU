#include <stdio.h>
#include<stdlib.h>
#include "h.h"

int solve(double *a, int n){
	int i, j, fl=1;
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
			if( (*(a+i*n+j)>*(a+j*n+i)) || (*(a+i*n+j)<*(a+j*n+i)) ) return 0;
	return fl;
}
