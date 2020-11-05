#include "addition.h"

int read_array (const char *name, student* a, int n){
	FILE *fp;
	if(!(fp=fopen(name, "r"))) return ERROR_CANNOT_OPEN_INPUT_FILE;
	for(int i = 0; i < n; i++)
	{
		int ret=a[i].read(fp);
		if (ret  < 0) return fclose(fp), ret;
                if (ret  > 0) return fclose(fp), ERROR_CANNOT_READ_INPUT_FILE;
	}
	fclose(fp);
	return 0;
}

void print_array (student* a, int n, FILE* out)
{
	int m = ((n > MAX_PRINT) ? MAX_PRINT : n);
	for(int i = 0; i < m; i++)
		a[i].print (out);
	printf("\n");
}

bool sort_control (student* a, int n)
{
    for (int i=0; i<n-1; i++)
        if ((a[i]>a[i+1])) return false;
    return true;
}
