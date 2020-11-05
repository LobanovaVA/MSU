#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x0){
	int it=0, i, j;
	double c=(b+a)/2, d, fa=f(a), fb=f(b), fc=f(c), fd;
	double x[3], y[3], m[3];
	if(!(a>c || a<c))return *x0=c, it;
	if(fabs(fa)<EPS) return *x0=a, it;
	if(fabs(fb)<EPS) return *x0=b, it;
	if(fabs(fc)<EPS) return *x0=c, it;
	//if(!(fc>0 || fc<0)) return *x0=c, it;

	for(it=1; it<MAX_IT; it++){
		x[0]=fa; x[1]=fb; x[2]=fc;
		y[0]=a; y[1]=b; y[2]=c;
        m[0]=a; m[1]=b; m[2]=c;

		for(i=1;i<3;i++)
			for(j=2;j>=i;j--)
				m[j]=( m[j]*(0-x[j-i])-m[j-1]*(0-x[j]) ) / (x[j]-x[j-i]);

		//d=y[0]+(0-x[0])*(y[0]-y[1])/(x[0]-x[1])+(0-x[0])*(0-x[1])*( (y[0]-y[1])/(x[0]-x[1]) - (y[1]-y[2])/(x[1]-x[2]) )/(x[0]-x[2])	;

		d=m[2];
		fd=f(d);

		if(fabs(fd)>fabs(fa) && fabs(fd)>fabs(fb) && fabs(fd)>fabs(fc) ) return -1;
		else {
			if(fabs(fc)>fabs(fa) && fabs(fc)>fabs(fb) && fabs(fc)>fabs(fd)  ) { c=d; fc=fd; }
			else {
				if(fabs(fb)>fabs(fa) && fabs(fb)>fabs(fc) && fabs(fb)>fabs(fd)  ) { b=d; fb=fd; }
				else {
					if(fabs(fa)>fabs(fb) && fabs(fa)>fabs(fc) && fabs(fa)>fabs(fd)  ) { a=d; fa=fd; }
					else return -1;
				}
			}
		}

		if(fabs(fd)<e) break;
	}

	if(it>=MAX_IT) return -1;
	else return *x0=d, it; 
}
