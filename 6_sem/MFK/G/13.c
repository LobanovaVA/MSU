#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];
	char *point, *slash;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fscanf (in, "%s", buf);

	point = strrchr (buf, '.');
	slash = strrchr (buf, '/');

	if (point == NULL || point - buf < slash - buf)
		fprintf (out, "%s.html", buf);
	else
	{
		*point = '\0';
		fprintf (out, "%s.html", buf);
	}

	fclose (in);
	fclose (out);
	return 0;
}
