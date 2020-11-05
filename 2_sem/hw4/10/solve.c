#include <math.h>
#include "h.h"

int solve( double (*f)(double), double a, double b, double e, double *x){
	int it=0, i, imax, imin;
	double c=(b+a)/2, d, fa=f(a), fb=f(b), fc=f(c), fd, ka, kb, m[6], max, min;
	//if(!(a>c || a<c))return *x=fc, it;
	m[0]=a; m[1]=b; m[2]=c; m[3]=fa; m[4]=fb; m[5]=fc;

	for(it=1; it<MAX_IT; it++){
		ka=( ((m[3]-m[4])/(m[0]-m[1])) - ((m[4]-m[5])/(m[1]-m[2])) )/(m[0]-m[2]);
		kb=  ((m[3]-m[4])/(m[0]-m[1])) - (m[0]+m[1])*( ( ((m[3]-m[4])/(m[0]-m[1]))-((m[4]-m[5])/(m[1]-m[2])) )/ (m[0]-m[2]) );

		//ka=( (fa-fb)/(a-b) - (fb-fc)/(b-c) )/(a-c);
		//kb=(fa-fb)/(a-b) - (a+b)*( ( (fa-fb)/(a-b)-(fb-fc)/(b-c) )/ (a-c) );

		if(ka>0) return -1;
		d=(-0.5)*kb/ka;
		fd=f(d);

		max=m[3]; min=m[3];
		for(i=3; i<6; i++){
			if(m[i]>max) { max=m[i]; imax=i-3;}
			if(m[i]<min) { min=m[i]; imin=i-3;}
		}
		m[imin]=d; m[imin+3]=fd;

		if(fabs(fd-m[imax+3])<e || fabs(d-m[imax])<e) break;
	}

	if(it>=MAX_IT) return -1;
	else return *x=fd, it; 
}
