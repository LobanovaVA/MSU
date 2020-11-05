#define ERROR_OPEN_A -1
#define ERROR_OPEN_B -2
#define ERROR_READ_A -3
#define ERROR_WRITE_B -4
#define EMPTY_STR_S -5
#define ERROR_STR_S -6
#define SUCCESS 0

int f(const char *a, const char *b, const char *s, char * (*edit)(char *s, int *fl));
