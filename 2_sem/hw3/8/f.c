#include <math.h>
#include "h.h"

//double f(double x, double e, double (*teilor)(double x, double e)){
double f(double x, double e){
    int k=0;
    while(!(x<2.0)){	x/=2.0; k++;    }
    return k*M_LN2+teilor(x,e);
}
