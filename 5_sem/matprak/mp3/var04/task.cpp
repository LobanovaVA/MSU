#include "addition.h"

int
count_sum_and_num (const char *filename, double *sum__, int *num__)
{
  FILE* fp;
  int num = 0;
  double elem = 0, sum = 0;

  fp = fopen (filename, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  while (fscanf (fp, "%lf", &elem) == 1)
    {
      if (elem < 0)
        {
          sum += elem;
          num++;
        }
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;;
    }

  fclose (fp);
  *sum__ = sum;
  *num__ = num;
  return SUCCESS;
}

// считается что файлы открываются читаются и все ок
int
count_greater_than (const char *filename, double x)
{
  FILE* fp;
  double curr;
  int count = 0;

  fp = fopen (filename, "r");
  while (fscanf (fp, "%lf", &curr) == 1)
    {
      if (curr < x)
        count ++;
    }

  fclose (fp);
  return count;
}
