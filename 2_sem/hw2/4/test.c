#include <stdio.h>
#include <string.h>
#include "test.h"

int test(const char *s, const char *buf){
	int i, j=0;

	for(i=0; buf[i]; i++){
		if(s[i+j]!='.'){
			if((unsigned int)s[i+j]==92) j++;
			if(s[i+j]!=buf[i]) return 0;
		}
	}
	return !s[i+j];
}

