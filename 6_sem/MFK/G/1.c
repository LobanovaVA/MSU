#include <stdio.h>
#include <string.h>

#define LEN 101
int
main (void)
{
	int len, ans;
	char buf[LEN];
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fgets (buf, LEN, in);
	len = ans = strlen(buf);

	if (buf[len - 1] == '\n')
	{
		buf[len - 1] = '\0';			
		len = ans = strlen(buf);
	}

	fprintf (out, "%s, %s, %s %d\n", buf, buf, buf, ans);

	fclose (in);
	fclose (out);

	return 0;
}