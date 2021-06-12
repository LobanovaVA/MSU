#include <stdio.h>
#include <string.h>

#define LEN 1001

int
main (void)
{
	FILE *in, *out;
	char buf[LEN];
	int len;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");
	buf[0] = '\0';

	fgets (buf, LEN, in);
	len = strlen (buf);

	printf("%d\n", len);
	if (buf[len - 1] == '\n')
		buf[len - 1] = '\0';
	len = strlen (buf);

	for (int i = 0; i < len; i++)
	{
		if (buf[i] == 'L' && i + 3 < len && buf[i + 1] == 'i' 
			&& buf[i + 2] == 'n' && buf[i + 3] == 'g')
		{
			fprintf (out, "Cao");
			i+=3;
			
		}
		else
		fprintf (out, "%c", buf[i]);
	}

	fclose (in);
	fclose (out);
	return 0;
}
