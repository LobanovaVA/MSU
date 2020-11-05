#include<math.h>
#include"h.h"
double teilor(double x, double e){
	double s=1.0, fr=1.0, i=2.0;
	while (!(fabs(fr)<e)){
		fr=(-1.0)*fr*(x/i)*(x/(i-1.0));
		s+=fr;
		i+=2.0;
	}
	return s;
}

