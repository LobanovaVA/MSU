#include <math.h>
#include "h.h"

//double f(double x, double e, double (*teilor)(double x, double e)){
double f(double x, double e){
    int flm=1;
    x=fmod(x, M_PI+M_PI);

    if( !(x<M_PI_2) && x<M_PI )  { flm=-1; x=M_PI-x; }
    if( !(x<M_PI) && x<M_PI+M_PI_2 ){ flm=-1; x-=M_PI;  }
    if( !(x<M_PI+M_PI_2) ) x=M_PI+M_PI-x;

    if(x<1) return flm*teilor(x,e);
    else return flm*(2*(teilor(x/2,e))*(teilor(x/2,e))-1);

}
