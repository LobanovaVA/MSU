#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define MAX_PRINT 10

int read_matrix(double *a, int m, int n, const char *name);

void  init_matrix(double *a, int m, int n, double(*f)(double, double));
void print_matrix(double *a, int m, int n);
double solve(double *a, double *b, int m, int n);
double rk(double *a, double *b, int m, int n, int k);
double rij(double *a, double *b, int m, int n, int i, int j);
double fa(double i, double j);
double fb(double i, double j);