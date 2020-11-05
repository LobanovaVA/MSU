#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 1234

int readMatrix (const char * path, char ** A, int m, int n, const char * t);
void printMatrix (const char ** A, int m, int n);

void solve (const char ** A, int m, int n, int i, int j);

int main (int argc, char * argv []) {
    const char * path;
    const char * t;
    int m, n;
    int i, j;
    char ** A;
  
    if (argc != 7) {
        printf ("Use %s path t m n i j\n", argv[0]);
        return 1;
    }
  
    path = argv[1];
    t = argv[2];
    m = atoi (argv[3]);
    n = atoi (argv[4]);
    i = atoi (argv[5]);
    j = atoi (argv[6]);

    if (m < 1 || n < 1 ||
        i < 0 || i >= m ||
        j < 0 || j >= m) {
        return 1;
    }
  
    A = malloc (m * n * sizeof (char *));
    
    if (A == NULL) {
        printf ("bad alloc\n");
        return 1;
    }
    
    if (readMatrix (path, A, m, n, t) != 0) {
        free (A);
        return 1;
    }
  
    printMatrix ((const char **) A, m, n);
    
    solve ((const char **) A, m, n, i, j);
    
    printMatrix ((const char **) A, m, n);
    
    for (int k = 0; k < m * n; k++) {
        free (A[k]);
    }
    
    free (A);

    return 0;
  
}

void solve (const char ** A, int m, int n, int i, int j) {
    const char ** Ai = A + i * n;
    const char ** Aj = A + j * n;
    const char * temp;
    int k;
    
    (void) m;
    
    for (k = 0; k < n; k++) {
        temp = Ai[k];
        Ai[k] = Aj[k];
        Aj[k] = temp;
    }

}

int readMatrix (const char * path, char ** A, int m, int n, const char * t) {
    char buf [LEN];
    char * p, * e;
    FILE * f;
    int len;

    int i, j, k;
    
    bzero (A, m * n * sizeof (char *));
    
    f = fopen (path, "r");
    
    if (f == NULL) {
        return 1;
    }
  
    for (i = 0 ; i < m; i++) {
        
        if (fgets (buf, LEN, f) == NULL) {
            fclose (f);
            return 1;
        }
        
        len = strlen (buf);

        if (buf[len - 1] == '\n') {
            buf[len - 1] = '\0';
        }
        
        e = buf;
        
        for (j = 0; j < n; j++) {
            
            p = strtok_r (e, t, &e);
            
            if (p == NULL) {
                break;
            }
            
            len = strlen (p) + 1;
            
            A[i * n + j] = malloc (len);
            
            if (A[i * n + j] == NULL) {

                for (k = 0; k < i * n + j; k++) {
                    free (A[k]);
                }

                fclose (f);

                return 1;
                
            }
            
            strcpy (A[i * n + j], p);
        
        }
        
    }
    
    fclose (f);
    
    return 0;
  
}

#define min(a, b) ((a < b) ? a : b)

void printMatrix (const char ** A, int m, int n) {
    int M = min (m, 10);
    int N = min (n, 10);
    int i, j;
  
    for (i = 0; i < M; i++) {

        for (j = 0; j < N; j++) {
            printf ("%s ", A[i * n + j]); 
        }

        printf ("\n");

    }
  
    printf ("\n");
  
}