#define MAX_IT 1000000
#define EPS 1e-16

int solve( double (*f)(double), int m, double *M,  double a, double b, double e, double *x);

double f(double x);
int get_count(void);
