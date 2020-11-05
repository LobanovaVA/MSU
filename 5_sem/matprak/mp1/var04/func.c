#include "addition.h"

int
func (const char *filename)
{
  FILE* fp;
  int count = 1;
  double x, max;

  fp = fopen (filename, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  if (fscanf (fp, "%lf", &max) != 1)
    {
      if (!feof (fp))
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
      fclose (fp);
      return 0;
    }

  while (fscanf (fp, "%lf", &x) == 1)
    {
      if (x > max)
        {
          max = x;
          count = 1;
        }
      else if (!(x < max))
        count++;
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (fp);
  return count;
}
