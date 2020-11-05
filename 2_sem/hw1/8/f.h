#define ERROR_OPEN_A -1
#define ERROR_OPEN_B -2
#define ERROR_READ_A -3
#define ERROR_WRITE_B -4
#define ERROR_STR_S -5
#define SUCCESS 0

int f(const char *a, const char *b, const char *s, const char *r, char * (*edit)(char *buf, int *alf, const char *r, int *c2));
