#define MAX_IT 1000
#define EPS 1e-16

int solve( double (*f)(double), double x0, double e, double *x);

double f(double x);
double d(double x);
int get_count(void);
