#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define MAX_PRINT 10

int read_matrix(double *a, int m, int n, const char *name);

void  init_matrix(double *a, int m, int n, double(*f)(double, double, double *, int));
void print_matrix(double *a, int m, int n);
double solve(double *a, double *x, double *b, int m, int n);
double rk(double *a, double *x, double *b, int m, int n, int k);
double fa(double i, double j, double *a, int n);
double fb(double i, double j, double *a, int n);
double fx(double i, double j, double *a, int n);