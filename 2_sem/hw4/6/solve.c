#include <math.h>
#include "h.h"

int solve( double (*f)(double), int m, double *M,  double a, double b, double e, double *x){
	int it=0, i, j, itmax;
	double d, fd, ymax;

	for(i=0; i<m+1; i++){
		M[i+m+1]=a+i*(b-a)/m;
		M[i]=f(M[i+m+1]);
		M[i+2*m+2]=M[i+m+1];
		if(fabs(M[i])<EPS) return *x=M[i+m+1], it;
	}

	for(it=1; it<MAX_IT; it++){
		
		for(i=1;i<m+1;i++)
			for(j=m;j>=i;j--)
				M[j+2*m+2]=( M[j+2*m+2]*(0-M[j-i])-M[j-1+2*m+2]*(0-M[j]) ) / (M[j]-M[j-i]);

		d=M[3*m-2];
		fd=f(d);
		if(fabs(fd)<e) break;

		ymax=-1;
		for(i=0;i<m+1;i++) if(fabs(M[i])>ymax) { itmax=i; ymax=fabs(M[i]); }
		if(fabs(fd)>ymax) return -1;
		else {
            M[itmax+m+1]=d; M[itmax]=fd;
            for(j=0; j<m+1; j++) M[j+2*m+2]=M[j+m+1];
        }

	}

	if(it>=MAX_IT) return -1;
	else return *x=d, it; 
}
