#include <stdio.h>

int
main (void)
{
  int month;
  scanf ("%d", &month);

  if (month < 3 || month == 12)
    return printf("winter\n"), 0;

  if (month > 2 && month < 6)
    return printf("spring\n"), 0;

  if (month > 5 && month < 9)
    return printf("summer\n"), 0;

  return printf("autumn\n"), 0;
}
