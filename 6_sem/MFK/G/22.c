#include <stdio.h>
#include <string.h>

#define LEN 21

int
main (void)
{
	FILE *in, *out;
	char buf[LEN], b;
	int curr, prev = -1, count = 1;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fscanf (in, "%s", buf);
	fprintf (out, "%c", buf[0]);


	for (int i = 1; count < 4 && i < (int) strlen (buf); i++)
	{
		b = buf[i];

		if (b != 'a' && b != 'e' && b != 'h' && b != 'i' &&
			b != 'o' && b != 'u' && b != 'w' && b != 'y')
		{
			if (b == 'b' || b == 'f' || b == 'p' || b == 'v')
				curr = 1;
			else 
				if (b == 'c' || b == 'g' || b == 'j' || b == 'k' ||
					b == 'q' || b == 's' || b == 'x' || b == 'z')
					curr = 2;
				else
					if (b == 'd' || b == 't')
						curr = 3;
					else
						if (b == 'l')
							curr = 4;
						else
							if (b == 'm' || b == 'n')
								curr = 5;
								else
									if (b == 'r')
										curr = 6;
		}
		else continue;

		if (prev == -1)
		{
			fprintf (out, "%d", curr);
			prev = curr;
			count++;
		}
		else
		{
			if (curr != prev)
			{
				fprintf (out, "%d", curr);
				prev = curr;
				count++;
			}

		}

	}

	if (count < 4)
		for (int i = 0; i < 4 - count; i++)
			fprintf (out, "0");

	fclose (in);
	fclose (out);
	return 0;
}
