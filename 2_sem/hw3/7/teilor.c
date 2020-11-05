#include<math.h>
#include"h.h"
double teilor(double x, double e){
	double s=1.0, fr=1.0, i=1.0;
	while (!(fr<e)){
		fr*=(x/i);
		s+=fr;
		i+=1.0;
	}
	return s;
}

