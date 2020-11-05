#include "all_func.h"

// Problem 1_1
int
problem_1_1 (const char* file_name, int k)
{
  FILE* fp;
  int num, single_byte = 0, num_byte = 0,  max_bit = 0;
  int count = 0, dist_count = 0, min_dist = -1, fl = 0;

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  while (fscanf (fp, "%d", &num) == 1)
    {
      max_bit = 1;
      for (num_byte = num; num_byte > 1; num_byte >>= 1)
        max_bit <<= 1;

      while (max_bit)
        {
          single_byte = num & max_bit;
          max_bit >>= 1;

          if (single_byte)
            {
              printf ("1");
              dist_count++;
              count++;
            }
          else
            {
              printf ("0");
              if (count >= k)
                {
                  if (fl)
                    {
                      dist_count -= (count + fl);
                      min_dist = (dist_count && (dist_count < min_dist || min_dist < 0))
                                  ? dist_count : min_dist;
                      dist_count = count;
                    }
                  fl = count;
                }
              dist_count++;
              count = 0;
            }

          if (!fl && count == 1)
            dist_count = 1;
        }
    }

  if (single_byte && fl && count >= k)
    {
      dist_count -= (count + fl);
      min_dist = (dist_count && (dist_count < min_dist || min_dist < 0))
                  ? dist_count : min_dist;
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }
  fclose (fp);
  if (min_dist < 0) min_dist = 0;
  return min_dist;
}




// Problem 1_2
int
problem_1_2 (const char* file_name_A, const char* file_name_B)
{
  FILE* fp_A, * fp_B;
  double a0, a1, a2, b0, b1;
  int k = 1;

  fp_A = fopen (file_name_A, "r");
  if (!fp_A)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;
  fp_B = fopen (file_name_B, "r");
  if (!fp_B)
    return ERROR_CANNOT_OPEN_INPUT_FILE_B;

  if (fscanf (fp_A, "%lf", &a0) != 1)
    {
      if (fscanf (fp_B, "%lf", &b0) != 1)
        {
          fclose (fp_A);
          fclose (fp_B);
          return ERROR_EMPTY_INPUT_FILE;
        }
      fclose (fp_A);
      fclose (fp_B);
      return ERROR_EMPTY_INPUT_FILE_A;
    }
  if (fscanf (fp_B, "%lf", &b0) != 1)
    {
      fclose (fp_A);
      fclose (fp_B);
      return ERROR_EMPTY_INPUT_FILE_B;
    }

  if (fscanf (fp_B, "%lf", &b1) != 1 || fscanf (fp_A, "%lf", &a1) != 1)
    {
      fclose (fp_A);
      fclose (fp_B);
      return 1;
    }
  b0 = b1;

  while (fscanf (fp_B, "%lf", &b1) == 1 )
    {
      if (fscanf (fp_A, "%lf", &a2) != 1)
        {
          fclose (fp_A);
          fclose (fp_B);
          return 0;
        }
      if (b0 * 2.0 > a0 + a2 || b0 * 2.0 < a0 + a2 )
        k = 0;
      b0 = b1;
      a0 = a1;
      a1 = a2;
    }

  if (!feof (fp_B))
    {
      fclose (fp_A);
      fclose (fp_B);
      return ERROR_CANNOT_READ_INPUT_FILE_B;
    }

  fclose (fp_A);
  fclose (fp_B);
  return k;
}




// Problem 1_3
int
problem_1_3 (const char* file_name, double* d)
{
  FILE* fp;
  int count = 0;
  double elem, sum = 0, sum_pow2 = 0;

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  while (fscanf (fp, "%lf", &elem) == 1)
    {
      count++;
      sum += elem;
      sum_pow2 += elem * elem;
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }
  if (count == 0)
    {
      fclose (fp);
      return ERROR_EMPTY_INPUT_FILE;
    }

  *d = (sum_pow2 * count - sum * sum) / (double) (count * count);
  fclose (fp);
  return count;
}



// Problem 1_4
int
problem_1_4 (const char* file_name)
{
  FILE* fp;
  int ans = 0;
  double x0, x1, x2;

  fp = fopen (file_name, "r");
  if (!fp) return ERROR_CANNOT_OPEN_INPUT_FILE;

  if (fscanf (fp, "%lf", &x0) != 1)
    {
      if (feof (fp))
        {
          fclose (fp);
          return ERROR_EMPTY_INPUT_FILE;
        }
      else
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
    }

  if (fscanf (fp, "%lf", &x1) != 1)
    {
      if (feof (fp))
        {
          fclose (fp);
          return 4;
        }
      else
        {
          fclose(fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
    }

  if (fscanf (fp, "%lf", &x2) != 1)
    {
      if (feof (fp))
        {
          if (!(x0 > x1 || x0 < x1))
            {
              fclose (fp);
              return 3;
            }
          else
            {
              fclose (fp);
              return 4;
            }
        }
      else
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }
    }

  if (!(x0 + x2 > 2 * x1 || x0 + x2 < 2 * x1 ))
    ans = 1;
  if (!(x0 * x2 > x1 * x1 || x0 * x2 < x1 * x1))
    ans = 2;
  if (!(x0 > x1 || x0 < x1) && !(x2 > x1 || x2 < x1))
    ans = 3;
  x0 = x1;
  x1 = x2;

  while (fscanf (fp, "%lf", &x2) == 1)
    {
      if (ans == 1 && (x0 + x2 > 2 * x1 || x0 + x2 < 2 * x1))
        ans = 0;
      if (ans == 2 && (x0 * x2 > x1 * x1 || x0 * x2 < x1 * x1))
        ans = 0;
      if (ans == 3 && (x2 >x1 || x2 < x1))
        ans = 0;
      if (ans == 0)
        {
          fclose (fp);
          return ans;
        }
      x0 = x1;
      x1 = x2;
    }

  if (!feof (fp))
    {
      fclose (fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }
  fclose (fp);
  return ans;
}



