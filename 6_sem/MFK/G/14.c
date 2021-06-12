#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char ln[LEN], n[LEN];

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fscanf (in, "%s %s", ln, n);
	fprintf (out, "Hello, %s %s!", n, ln);

	fclose (in);
	fclose (out);
	return 0;
}
