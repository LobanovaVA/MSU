#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ERROR_OPEN_FILE -1
#define ERROR_READ_FILE -2
#define ERROR_WORD_MEMORY -3
#define MAX_PRINT 10
#define LEN 1234

int read_matrix(const char *, char **, int, int, char *);
void print_matrix(char **, int, int);
void solve(char **, int, int, int, int);

int main(int argc, char **argv){
	const char *name;
    char **a, *t;
    int m, n, s1, s2, ret, k;
	if( !( (argc==7) && (m=atoi(argv[3])) && (n=atoi(argv[4])) && (s1=atoi(argv[5])) && (s2=atoi(argv[6])) ) )
        return printf("Usage: %s fileA.txt STR m n i j\n", argv[0]), 1;
    if (m<1 || n<1 || s1<1 || s1>n || s2<1 || s2>n) return printf("Incorrect data\n"), 2;
    if(!(a=(char**)malloc((n*m)*sizeof(char*))) )return printf("Not enough memory\n"), 3;
	name=argv[1]; t=argv[2]; s1--; s2--;

	ret=read_matrix(name, a, m, n, t);
	if(ret<0){
		switch(ret){
            case ERROR_OPEN_FILE: printf("\nCannot open %s\n", name); break;
            case ERROR_READ_FILE: printf("\nCannot read %s\n", name); break;
            case ERROR_WORD_MEMORY: printf("\nNot enough memory for word from %s\n", name); break;
            default: printf("Unknown error %d in %s\n", ret, name);
		}
		free(a);
		return 4;
	}
    printf("\nOriginal matrix:\n");  print_matrix(a, m, n);
    solve(a, m, n, s1, s2);
    printf("\nChanged matrix: \n");  print_matrix(a, m, n);
    
    for(k=0; k<m*n; k++) free(a[k]);
    free(a);
	return 0;
}

int read_matrix(const char *name, char **a, int m, int n, char *t){
	FILE *fp;
	int i, j, k, fl, wcol, wlen, alf[256];
    char buf[LEN], *p;

    for(i=0; i<256; i++) alf[i]=0;
	for(i=0; t[i]; i++) alf[(unsigned int)t[i]]=1;
	bzero (a, m*n*sizeof(char *));


	if(!(fp=fopen(name, "r"))) return ERROR_OPEN_FILE;
    for(i=0;i<m;i++){
        if(!fgets(buf, LEN, fp)){
	       for(k=0; k<i*n; k++) free(a[k]);
	       return fclose(fp), ERROR_READ_FILE;
	   }
        
        //for(j=0; buf[j]; j++) if(buf[j]=='\n') {buf[j]=0; break;}
        if (buf[strlen(buf)-1]=='\n') buf[strlen(buf)-1]=0;

        wcol=0; wlen=0; fl=0; p=buf;	
        for(j=0; buf[j] && wcol<n; j++){
        	if(alf[(unsigned int)buf[j]]==1){
        		if(fl){
        			if(!(a[i*n+wcol]=(char *)malloc((wlen+1)*sizeof(char)))) {
        				for(k=0; k<i*n+wcol; k++) free(a[k]);
        				return fclose(fp), ERROR_WORD_MEMORY;
        			}
        			p[wlen]=0;
        			strcpy(a[i*n+wcol], p);
        			wcol++;
        			wlen=0;
        			fl=0;
        		}
        	}
        	else{
        		if(!fl) { p=buf+j; fl=1;}
        		wlen++;
        	}

        }

        if(fl){
        	if(!(a[i*n+wcol]=(char *)malloc((wlen+1)*sizeof(char)))) {
        				for(k=0; k<i*n+wcol; k++) free(a[k]);
        				return fclose(fp), ERROR_WORD_MEMORY;
        			}
        		p[wlen]=0;
        		strcpy(a[i*n+wcol], p);
        		wcol++;
        		wlen=0;
        }

    }
	fclose(fp);
	return 0;
}


void print_matrix(char **a, int m, int n){
	int i, j, str, col;
	str=(m>MAX_PRINT)?MAX_PRINT:m;
	col=(n>MAX_PRINT)?MAX_PRINT:n;
	for(i=0; i<str; i++){
		for(j=0; j<col; j++)
			printf("%s   ", a[i*n+j]);
		printf("\n");
	}
}


void solve(char **a, int m, int n, int s1, int s2){
	int i;
	char *temp, **p1=a+s1, **p2=a+s2;
	for(i=0; i<m*n; i+=n){ temp=p1[i]; p1[i]=p2[i]; p2[i]=temp;	}
}




