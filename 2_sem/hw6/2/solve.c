#include <stdio.h>
#include<stdlib.h>
#include "h.h"

double solve(double *a, int n){
	int i;
	double s=0;
	for(i=0; i<n; i++) s+=*(a+i*n+i);
	return s;
}
