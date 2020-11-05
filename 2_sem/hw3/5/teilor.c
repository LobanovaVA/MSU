#include<math.h>
#include"h.h"
double teilor(double x, double e){
	double s=x, fr=x, i=3.0;
	while (!(fabs(fr)<e)){
		fr=(-1.0)*fr*(x/i)*(x/(i-1.0));
		s+=fr;
		i+=2.0;
	}
	return s;
}

