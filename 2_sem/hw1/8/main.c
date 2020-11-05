#include <stdio.h>
#include "f.h"
#include "edit.h"

int main(int argc, char **argv){
	const char *a, *b, *s, *r;
	int ret;
	if(argc!=5){
		printf("Usage: %s a.txt b.txt strS strR\n", argv[0]);
		return 1;
	}
    a=argv[1]; b=argv[2]; s=argv[3]; r=argv[4];
	ret=f(a,b,s,r,&edit);
	if(ret<SUCCESS){
		switch(ret){
			case ERROR_OPEN_A:  printf("Cannot open %s\n", a); break;
			case ERROR_OPEN_B:  printf("Cannot open %s\n", b); break;
			case ERROR_READ_A:  printf("Cannot read %s\n", a); break;
			case ERROR_WRITE_B: printf("Cannot write %s\n",b); break;
            case ERROR_STR_S:   printf("Empty string s\n");    break;
			default: printf("Uknown error %d in either %s or %s\n", ret, a, b);
		}
		return 2;
	}
	printf("Result=%d\n", ret);
	return 0;
}
