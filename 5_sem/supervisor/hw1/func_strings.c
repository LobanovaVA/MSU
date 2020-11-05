#include "all_func.h"

int
read_str_array (const char *file_name, char **arr, int size)
{
  FILE *fp;
  int i, j;
  char buff[LEN];

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < size; i++)
    {
      if (!fgets (buff, LEN, fp))
        {
          fclose (fp);
          for (j = 0; j < i; j++)
            free (arr[j]);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
      arr[i] = (char *) malloc ((strlen (buff) + 1) * sizeof (char));
      if (buff[strlen (buff) - 1] == '\n')
        buff[strlen (buff) - 1] = 0;
      strcpy (arr[i], buff);
    }

  fclose (fp);
  return 0;
}


void
print_str_array (char **arr, int size)
{
  int i, print_size;
  print_size = ((size > MAX_PRINT) ? MAX_PRINT : size);
  for (i = 0; i < print_size; i++)
    printf ("[%d]: %s\n", i, arr[i]);
}




// Problem 4_1
size_t
strcspn_ (const char *string1, const char *string2)
{
  int i, del = 1, mod = (sizeof (unsigned int) << 3) - 1;
  unsigned int a[32 / sizeof (unsigned int)] = {0};
  unsigned int check;
  char s;

  for (i = mod; i > 1; i >>= 1) del++;
  for (i = 0; i * sizeof (unsigned int) < 32; i++) a[i] = 0;

  for (i = 0; string2[i]; i++)
    {
      s = (unsigned int) string2[i];
      a[s >> del] |= 1 << ((s & mod) + 1);
    }

  for (i = 0; string1[i]; i++)
    {
      s = (unsigned int) string1[i];
      check = 1 << ((s & mod) + 1);
      if ((a[s >> del] & check ) == check)
        return i;
    }
  return i;
}



// Problem 4_2
int
problem_4_2 (char **arr, int size, int k, char *str)
{
  int i, s = 0, count = 0;
  for (i = 0; i < size; i++)
    {
      if (strstr (arr[i], str))
        count++;
      else
        {
          if (count >= k)
            s += count;
          count = 0;
        }
      //if (s) strcpy (arr[i - s], arr[i]);
      if (s)
        {
          free (arr[i - s]);
          arr[i - s] = arr[i];
          arr[i] = 0;
        }
    }
  if (count >= k)
    s += count;
  return size - s;
}



// Problem 4_3
int
problem_4_3 (char **arr, int size, int k, char *str)
{
  int i, s = 0, count = 0;
  for (i = 0; i < size; i++)
    {
      if (!arr[i][strspn (arr[i], str)])
        count++;
      else
        {
          if (count >= k)
            s += count;
          count = 0;
        }

      if (s)
        {
          free (arr[i - s]);
          arr[i - s] = arr[i];
          arr[i] = 0;
        }
    }
  if (count >= k)
    s += count;
  return size - s;

}
