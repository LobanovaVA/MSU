#include <stdio.h>

int
main (void)
{
	int a; 
	char b;
	scanf ("%c%d", &b, &a);

	if (b == 'A' || b == 'C' || b == 'E' || b == 'G')
	{
		if (a % 2 == 0)
			printf ("WHITE\n");
		else
			printf ("BLACK\n");
	}
	else
	{
		if (a % 2 != 0)
			printf ("WHITE\n");
		else
			printf ("BLACK\n");

	}

  	return 0;
}

