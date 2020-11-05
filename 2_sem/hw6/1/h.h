#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define MAX_PRINT 10

int read_matrix(double *a, int n, const char *name);

void  init_matrix(double *a, int n);
void print_matrix(double *a, int n);
int solve(double *a, int n);
double f(double i, double j);
