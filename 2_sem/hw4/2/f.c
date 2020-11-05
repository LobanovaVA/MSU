#include<math.h>
#include"h.h"

static int count=0;

int get_count(void){ return count; }

double f(double x){
	count++;
	return sin(x)*x;
}

double d(double x){
    return cos(x)*x+sin(x);
}
