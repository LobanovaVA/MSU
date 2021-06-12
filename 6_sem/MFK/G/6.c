#include <stdio.h>
#include <string.h>

#define LEN 1001

int is_palindrom (char w[]);

int 
is_palindrom (char w[])
{
	int len = strlen (w);
	for (int i = 0; i < len / 2; i++)
		if (w[i] != w[len - i - 1])
			return 0;

	return 1;
}

int
main (void)
{
	char buf[LEN];
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	if (buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = '\0';			

	if (is_palindrom (buf))
		fprintf (out, "YES\n");
	else
		fprintf (out, "NO\n");

	fclose (in);
	fclose (out);

	return 0;
}