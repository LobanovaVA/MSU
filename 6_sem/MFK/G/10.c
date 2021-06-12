#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN], ans[LEN];
	int max = 0;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	while (fscanf (in, "%s", buf) != EOF) 
		if ((int) strlen(buf) > max)
		{
			max = strlen (buf);
			strcpy (ans, buf);
		}

	fprintf (out, "%s", ans);

	fclose (in);
	fclose (out);
	return 0;
}
