#include <stdio.h>
#include <string.h>

int 
main (int argc, char **argv)
{
	for (int i = (int) strlen (argv[1]) - 1; i >= 0; i--)
		printf("%c", argv[1][i]);

	return 0;
}