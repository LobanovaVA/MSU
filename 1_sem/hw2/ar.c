#include<stdio.h>
/*
FILE* fopen(const char* filename, const char* made);
int fclose(FILE*);
int feof(FILE*fp);
int fscanf (FILE* fp, const char* format, ...);
int fprintf(FILE* fp, const char* format, ...);
int f(const char*name, double *p);
*/
int f(const char* name, double *ans);
int f(const char* name, double *ans){
	FILE* fp;
	int n=0;
	double s=0, x;
	fp=fopen(name, "r");
	if(!fp) return -1;
	while(fscanf(fp, "%lf", &x)==1){
		s+=x;
		n++;
	}
	if(!feof(fp)){
		fclose(fp);
		return -2;
	}
	fclose(fp);
	if(n==0) return 0;
	*ans=s/n;
	return 1;
}
int main(void){
	const char* name="a.txt";
	double ans;
	int res;
	res=f(name, &ans);
	if(res<0){
		switch(res){
			case -1: 
				printf("Cannot open %s\n", name);
				break;
			case -2: 
				printf("Cannot read %s\n", name);
				break;
			default: printf("Unknown error %d in %s\n", res, name);
		}
		return 1;
	}
	if(res==0) printf("Empty file %s\n", name);
	else printf("Result=%f\n", ans);
	return 0;
}
			
			
		
		
