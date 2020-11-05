#include <string.h>
#include "test.h"
int test(char *buf, int i, const char *s, int j){
	if(!buf[i] && !s[j]) return 1;
	else return 0;
	if(buf[i+1] && buf[i+1]!='?'){
		if(buf[i]==s[j]) return test(buf, i+1, s, j+1);
		else return 0; 
	}
	else return (test(buf, i+2, s, j) || test(buf, i+2, s, j+1));
}
