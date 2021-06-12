#include <stdio.h>
#include <string.h>

#define LEN 1001

int 
main (int argc, char **argv)
{
	FILE *in, *out;
	char str[LEN];
	int c_str = 0, c_w = 0, c_b = 0, len;

	if (argc != 3 || !(in = fopen (argv[1], "r")) || !(out = fopen (argv[2], "w")))
		return 1;


	fgets (str, LEN, in);

	while(!feof (in)) 
	{		
		len = strlen (str);
		c_str++;
		c_b += len;


		if (str[len - 1] == '\n')
			str[len - 1] = '\0';
		len = strlen (str);


		for (int i = 0; i < len;)
		{
			while (i < len && str[i] == ' ')
				i++;

			if (i < len) 
				c_w++;

			while (i < len && str[i] != ' ')
				i++;

		}

		fgets (str, LEN, in);
	}

	fprintf (out, "%d %d %d\n", c_str, c_w, c_b);

	fclose (in);
	fclose (out);
	return 0;
}
