#include<math.h>
#include"h.h"

double f(double x) { return x*x*x*x-1; }

double intf(double a, double b) { 
    return (pow(b,5)/5.0-b)-(pow(a,5)/5.0-a);
}
