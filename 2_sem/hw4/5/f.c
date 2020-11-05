#include<math.h>
#include"h.h"

static int count=0;

int get_count(void){ return count; }

double f(double x){
	count++;
	return x*x*x-2*x;
}
