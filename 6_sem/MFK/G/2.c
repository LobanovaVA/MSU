#include <stdio.h>
#include <string.h>

#define LEN 100
int
main (void)
{
	int n, number = 2;
	char bukva = 'A';
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	fscanf (in, "%d", &n);

	for (int i = 0; i < n / 2; i++)
	{
		fprintf (out, "%c%d", bukva, number);
		bukva++;
		number = (number == 8) ? 2 : number + 2;

	}

	fclose (in);
	fclose (out);
	return 0;
}
