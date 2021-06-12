#include <stdio.h>
#include <string.h>
#include <math.h>

#define LEN 1001

int f (char w[]);

int
f (char w[])
{
	int count = 0;	
	for (int i = 0; i < (int) strlen (w); i++)
		if (w[i] == '*')
			count++;
	return count;
}
int
main (void)
{
	int count = 0, n , space, tmp;
	char buf[LEN];
	FILE *in, *out;

	in = fopen ("input.txt", "r");
	out = fopen ("output.txt", "w");

	while (fgets (buf, LEN, in) != NULL)
    	count += f(buf);

    tmp = sqrt (8 * count + 1);
    if (count == 0 || 8 * count + 1 != tmp * tmp)
    	fprintf (out, "NO\n");
    else
    {
    	tmp = n = (tmp - 1) / 2;
    	space = n - 1;

    	for (int i = 0; i < n; i++)
    	{

    		for (int j = 0; j < space; j++)
    			fprintf (out, " ");

    		fprintf (out, "*");

    		for (int j = 0; j < i; j++)
    			fprintf (out, " *");

    		fprintf (out, "\n");
    		space--;
    	}
    }
    
	fclose (in);
	fclose (out);
	return 0;
}
