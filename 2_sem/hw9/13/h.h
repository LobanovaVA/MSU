#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define MAX_PRINT 10

int errors(int ret, const char *name);

int read_matrix(double *a, int m, int n, const char *name);
void  init_matrix(double *a, int m, int n, double(*f)(double, double));
void print_matrix(double *a, int m, int n);
double fa(double i, double j);

int solve(double *a, double *b, int n);
void change_columns(double *a, int m, int n, int i, int j);
void change_strings(double *a, int m, int n, int i, int j);

void mult_matrix(double *a, double *b, double *c, int n);
double norm1(double *a, int n);
double fi(double *a, int n, int i);
double norm2(double *a, int n);
double fj(double *a, int n, int j);
double norm3(double *a, int n);
