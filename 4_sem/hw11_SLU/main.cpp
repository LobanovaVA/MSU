#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"


double f1 (double x, double y, double a)
{
    double ans = 0;
    ans += sin (1. / (1. + x * x)) * sin (1. / (1. + x * x));
    ans += sin (1. / (1. + y * y)) * sin (1. / (1. + y * y));
    ans -= a;
    ans *= (-1) * (0.25);
    return ans;
}

double f2 (double x, double y, int n)
{
    double ans = 0;
    ans += atan (-1. /(2 * (1 + x * x + y * y)));
    ans += M_PI * n;
    return ans;
}

double norma (double a, double b)
{ return sqrt (a * a + b * b); }


int main (int argc, char *argv[])
{
    double a = 0, eps = 0; int n = 0;
    if (argc != 4 || (sscanf(argv[3], "%d", &n)!=1) || (sscanf(argv[2], "%lf", &eps)!=1)  || !(eps > 0)) 
        return printf ("Usage: %s  alpha  eps > 0  n \n", argv[0]), 1;
    sscanf(argv[1], "%lf", &a);

    double x1, x2 = 0, y1, y2 = 0, norm = 0;
    int i = 0, max_i = (int)(9 - 25 * log(eps));
    double time = clock();

    do
    {
        x1 = x2; y1 = y2;
        x2 = f1 (x1, y1, a);
        y2 = f2 (x1, y1, n);
        norm = norma (x1 - x2, y1 - y2);
        i++;
    } while (!(norm < eps) && i < max_i);

    if (i == max_i) printf("\n Iteration limit reached!\n");

    time = clock () - time;
    printf("\nAnswer:\nx = %.12e\ny = %.12e\n", x2, y2);

    printf("\nThe error between the last iterations: %.12e", norm);
    double f1_ = (-1.) * 4. * f1 (x1, y1, a) + 4 * x2;
    double f2_ = 1. / (1. + x2 * x2 + y2 * y2) + 2 * tan (y2);
    printf("\nThe error for the source system: %.12e", norma(f1_, f2_));

    printf("\nIterations: %d\n", i);
    printf("\nTime: %lf\n", time/CLOCKS_PER_SEC);

    return 0;
}
