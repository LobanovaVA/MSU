#include "all_func.h"

int
main (int argc, char *argv[])
{
    char *string1, *string2;
    int ans;

    if (argc != 3)
      {
        printf ("Usage: %s STRING1 STRING2\n", argv[0]);
        return 1;
      }

    string1 = argv[1];
    string2 = argv[2];

    ans = strcspn_ (string1, string2);
    printf ("Answer: %d\n", ans);
}

