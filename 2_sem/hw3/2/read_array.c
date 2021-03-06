#include <stdio.h>
#include "f.h"
int read_array(int n, const char *a, double *x, double *y){
	FILE *in;
	int i;
	if(!(in=fopen(a, "r"))) return ERROR_OPEN;
	for(i=0;i<n;i++) if(fscanf(in, "%lf %lf", (x+i), (y+i)) !=2) return fclose(in), ERROR_READ;
	if(ferror(in)) return fclose(in), ERROR_READ;
	fclose(in);
	return SUCCESS;
}