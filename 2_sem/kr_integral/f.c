extern int ERR;

#include<math.h>
#include"h.h"

static int count=0;

int get_count(void){ return count; }

double f(double x, double e){
	double a=0.0, b=10.0, r;
	int ret;
	count++;
	ret=integral(&g, x, a, b, e, &r);
	if(ret<0) ERR=1;
	return r;
}

double g(double x, double y){	return (x*x*x*x*x/10.0)-(12e-4)*y*y*y*x*x*x+(x*x/10.0)+(2e-2)*y*x;	}
// 2*sin(2*x)-sqrt(x)*(y*y*y+y*y+x)*exp((-1)*y*y/x)