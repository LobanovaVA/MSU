#include <math.h>
#include "h.h"

//double f(double x, double e, double (*teilor)(double x, double e)){
double f(double x, double e){
    double xr=fmod(x, 1.0), ans=1.0;
    int i;
    //if(x<0) return 1/f((-1)*x, e, teilor);
    if(x<0) return 1/f((-1)*x, e);

    //for(i=1; i<=x; i++) ans*=E;
    ans=pow(M_E, x-xr);
    return ans*teilor(xr, e);
}
