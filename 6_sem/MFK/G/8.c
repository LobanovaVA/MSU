#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 10001

int cmp (const void *a, const void *b);
int cmp (const void *a, const void *b) { return *(int*)a - *(int*)b; }


int
main (void)
{
	char buf[LEN];
	int num[LEN / 2] = {0}, n = -1;

	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';	

	for (int i = 0; i < (int) strlen (buf); i++)
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			n++;
			for (; buf[i] >= '0' && buf[i] <= '9' && i < (int) strlen (buf); i++)
			num[n] = num[n] * 10 + (buf[i] - '0');
		}
	}	

	n++;	
	qsort (num, n, sizeof(int), cmp);

	for (int i = 0; i < n; i++)
		fprintf (out, "%d ", num[i]);

	fclose (in);
	fclose (out);

	return 0;
}