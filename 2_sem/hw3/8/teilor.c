#include<math.h>
#include"h.h"
double teilor(double x, double e){
	double s, fr, i=2.0;
	x=x-1.0;
	s=x; fr=x;
	while (!(fabs(fr)<e)){
		fr=(-1.0)*fr*x*(i-1.0)/i;
		s+=fr;
		i+=1.0;
	}
	return s;
}

