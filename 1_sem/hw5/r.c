#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int write_array(const char *, double *, int);
void print_array(double *, int);
int randAr(double*,int);
#define MAX_PRINT 100

int main(int argc, char * argv[]){
	int n, ret,result;
	double *a;
	char *name;
	if((argc != 3) || !(n = atoi(argv[1]))){
		printf("Usage : %s n name\n", argv[0]);
		return 1;
	}
	a = (double *)malloc(n * sizeof(double));
	if(!a){
		printf("Not enough memory\n");
		return 2;
	}
	result=randAr(a,n);
	if(result!=0){
		printf("Error\n");
		return 1;
	}
	name = argv[2];
	ret = write_array(name, a, n);
	if(ret < 0){
		switch(ret){
			case -1:
				printf("Can not open %s\n", name);
				break;
			case -2:
				printf("Can not read %s\n", name);
				break;	
			default:
				printf("Unknown error\n");
		}
		free(a);
		return 3;
	}
	printf("New array;\n");
	print_array(a,n);
	free(a);
	return 0;
}

int write_array(const char * name, double * a, int n){
	FILE * fp;
	int i;
	if(!(fp = fopen(name, "w"))) return -1;
	for(i = 0; i <n; i ++){
		fprintf(fp, "%0.2lf\n", a[i]);
	}
	fclose(fp);
	return 0;
}

void print_array(double * a, int n){
	int i;
	int m = ((n > MAX_PRINT)? MAX_PRINT : n);
	for(i = 0; i < m; i ++){
		printf("[%d] = %.2f\n", i, a[i]);
	}
}

int randAr(double*a,int n){
	int i=0;
	srand(time(NULL));
	for(;i<=n;i++){
		//srand(time(NULL));
		a[i] = rand();
	}
	return 0;
}
