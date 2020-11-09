#include "addition.h"

int
count_sum_and_num (const char *filename, double *sum__, int *num__)
{
  FILE* fp;
  int num = 0;
  double curr = 0, prev = 0, next = 0, sum = 0;

  fp = fopen (filename, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  if (fscanf (fp, "%lf", &prev) != 1)
    {
      if (!feof (fp))
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
      fclose (fp);
      *sum__ = 0;
      *num__ = 0;
      return SUCCESS;
    }

  if (fscanf (fp, "%lf", &curr) != 1)
    {
      if (!feof (fp))
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
      fclose (fp);
      *sum__ = prev;
      *num__ = 1;
      return SUCCESS;
    }

  if (feof (fp))
    {
      if (prev < curr)
        {
          *sum__ = prev + curr;
          *num__ = 2;
        }
      else
        {
          *sum__ = 0;
          *num__ = 0;
        }
      fclose (fp);
      return SUCCESS;
    }

  if (prev < curr)
    {
      sum = prev;
      num = 1;
    }

  while (fscanf (fp, "%lf", &next) == 1)
    {
      if (prev < curr || curr < next)
        {
          sum += curr;
          num++;
        }
      prev = curr;
      curr = next;
    }

  if (prev < curr)
    {
      sum += curr;
      num++;
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
      if (curr > x)
        count ++;
    }

  fclose (fp);
  return count;
}
