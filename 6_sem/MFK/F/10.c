#include <stdio.h>

#define N 1000
int
main (void)
{
    int count;
    char c, new;

    scanf ("%c", &c);
    new = c;


    while(c != '.')
    {
        count = 0;

        while (c == new)
        {
            count++;
            scanf ("%c", &new);
        }

        printf("%c%d", c, count);
        c = new;
    }
   
  return 0;
}
