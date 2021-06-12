#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];
	int count = 0;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	while (fscanf (in, "%s", buf) != EOF) 
		if (buf[strlen(buf) - 1] == 'a')
			count++;

	fprintf (out, "%d", count);

	fclose (in);
	fclose (out);
	return 0;
}
