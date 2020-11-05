#include "addition.h"

// for Problem 1, 2
char *
edit (char *str, int *fl, char param)
{
  int i = 0, d = 0;

  while (str[i])
    {
      if (str[i] == '\\')
        {
          if (str[i + 1] && (str[i + 1] == '\\' || str[i + 1] == param ) )
            {
              d++;
              i++;
              str[i - d] = str[i];
              i++;
            }
          else
            {
              *fl = 1;
              return str;
            }
        }
      else
        {
          str[i - d] = str[i];
          i++;
        }
    }

  str[strlen (str) - d] = 0;
  return str;
}



// for Problem 3
char *
clear_edit_3 (char *str, int *fl)
{
  int i = 0, d = 0;
  if (str[1] && str[0] == '\\' && str[1] == '<')
    {
      *fl = 1;
      d = 2;
      i = 2;
    }

  while (str[i])
    {
      if (str[i] == '\\' && str[i + 1])
        {
          if (str[i + 1] == '\\')
            {
              d++;
              i++;
              str[i - d] = str[i];
              i++;
              continue;
            }

          if (str[i + 1] == '<')
            {
              if (str[i - 1] == ' ' || str[i - 1] == '\t')
                {
                  d += 2;
                  i += 2;
                  continue;
                }
              else
                {
                  *fl = -1;
                  return 0;
                }
            }

          *fl = -1;
          return 0;
        }
      else
        {
          str[i - d] = str[i];
          i++;
        }
    }

  str[strlen (str) - d] = 0;
  return str;
}



// for Problem 4
char *
clear_edit_4 (char *str, int *fl)
{
  int i = 0, d = 0;

  while (str[i])
    {
      if (str[i] == '\\' && str[i + 1])
        {
          if (str[i + 1] == '\\')
            {
              d++;
              i++;
              str[i - d] = str[i];
              i++;
              continue;
            }

          if (str[i + 1] == '>')
            {
              if (!str[i + 2])
                {
                  *fl = 1;
                  d += 2;
                  break;
                }
              else
                {
                  if (str[i + 2] == ' ' || str[i + 2] == '\t')
                    {
                      d += 2;
                      i += 2;
                      continue;
                    }
                  else

                    {
                      *fl = -1;
                      return 0;
                    }
                }
            }
          *fl = -1;
          return 0;
        }
      else
        {
          str[i - d] = str[i];
          i++;
        }
    }

  str[strlen (str) - d] = 0;
  return str;
}



// for Problem 5, 6, 7, 8
int
check_incr (const char *str, char param)
{
  if (str[0] != '.' && str[0] == param)
    return 1;

  int i;
  for (i = 0; str[i]; i++)
    {
      if(str[i] == '\\')
        {
          i++;
          if (str[i] != param && str[i] != '\\')
            return 1;
        }
    }
  return 0;
}


// for Problem 5
int
check_with_dot (const char *buf, const char *str)
{
  int i, j = 0, k = 0;

  for (i = 0; buf[i] && str[k + j]; i++, k++)
    {
      if (str[k + j] != '.')
        {
          if (str[k + j] == '\\')
            j++;

          if (str[k + j] != buf[i])
            {
              k = -1;
              j = 0;
            }
        }
    }
  return !str[k + j];
}


// for Problem 6
int
check_with_query (const char *buf, const char *str)
{
  int i;
  for (i = 0; buf[i]; i++)
    {
      if (check_with_query_rec (buf + i, str, 0, 0))
        return 1;
    }
  return 0;
}

int
check_with_query_rec (const char *buf, const char *str, int i, int j)
{
  int ret1 = 0, ret2 = 0;
  if ( !(j < (int) strlen(str) && i < (int) strlen(buf)) )
    return 1;

  if (str[j] == '\\')
    j++;

  if (!str[j + 1])
    {
      if (str[j] == buf[i])
        return 1;
      else
        return 0;
    }

  if (str[j + 1] != '?')
    {
      if (str[j] == buf[i])
        return check_with_query_rec (buf, str, i + 1, j + 1);
      else
        return 0;
    }
  else
    {
      if (str[j] == buf[i])
        {
          ret1 = check_with_query_rec (buf, str, i + 1, j + 2);
          ret2 = check_with_query_rec (buf, str, i + 1, j);
          return ret1 || ret2;
        }
      else
        return check_with_query_rec (buf, str, i, j + 2);
    }
}


// for Problem 7, 8
char *
edit_like_with_plus (char *str, int *fl, char param)
{
  int i = 0, j;
  char symbol;

  for (i = 0; str[i]; i++)
    {
      if (str[i] == param && str[i - 1] != '\\')
        {
          *fl = 1;
          symbol = str[i - 1];
          for (j = i + 1; str[j] && str[j] == symbol; j++)
            str[j - 1] = str[j];
          str[j - 1] = param;
        }
    }
  return str;
}


// for Problem 7
int
check_with_plus (const char *buf, const char *str)
{
  int i, j = 0, k = 0;
  char symbol;

  for (i = 0; buf[i] && str[k + j]; i++, k++)
    {
      if (str[k + j] != '+')
        {
          if (str[k + j] == '\\')
            j++;

          if (str[k + j] != buf[i])
            {
              k = -1;
              j = 0;
            }
        }
      else
        {
          symbol = str[k + j - 1];
          for (; buf[i] && buf[i] == symbol; i++);
          i--;
        }
    }

  while (str[k + j] && str[k + j] == '+')
    k++;

  return !str[k + j];
}


// for Problem 8
int
check_with_star (const char *buf, const char *str)
{
  int i, j = 0, k = 0;
  char symbol;

  for (i = 0; buf[i] && str[k + j]; i++, k++)
    {
      if (!str[k + j + 1])
        {
          if (str[k + j] != buf[i])
            {
              k = -1;
              j = 0;
            }
          else
            return 1;
        }
      else
        {
          if (str[k + j] == '\\')
            j++;

          if (str[k + j + 1] == '*')
            {
              if (str[k + j] == buf[i])
                {
                  symbol = str[k + j];
                  for (; buf[i] && buf[i] == symbol; i++);
                }
              i--;
              j++;
            }
          else
            {
              if (str[k + j] != buf[i])
                {
                  k = -1;
                  j = 0;
                }
            }
        }
    }

  if (str[k + j] == '\\') j++;
  if (str[k + j + 1] && str[k + j + 1] == '*' && !str[k + j + 2])
    return 1;

  while (str[k + j] && str[k + j] == '*')
    k++;

  return !str[k + j];
}


// for Problem 9
int
check_correct_bracket (const char *str)
{
  int i, fl_err = 0;
  for (i = 0; str[i]; i++)
    {
      if(str[i] == '\\')
        {
          i++;
          if (str[i] != '[' && str[i] != ']' && str[i] != '\\')
            return 1;
        }
      else
        {
          if (str[i] == '[')
            {
              fl_err = 1;
              i++;
              if (str[i] && str[i] != '[' && str[i] != ']')
                {
                  i++;
                  if (str[i] && str[i] == '-')
                    {
                      i++;
                      if (str[i] && str[i] != '[' && str[i] != ']')
                        {
                          i++;
                          if (str[i] && str[i] == ']')
                            fl_err = 0;
                        }
                    }
                }
            }
          if (fl_err)
            return 1;
        }
    }
  return 0;
}



int
check_with_bracket (const char *buf, const char *str)
{
  int i, j = 0, k = 0;
  char n, m;

  for (i = 0; buf[i] && str[k + j]; i++, k++)
    {
      if (str[k + j] == '[')
        {
          n = str[k + j + 1];
          m = str[k + j + 3];
          if (buf[i] < n || buf[i] > m)
            {
              k = -1;
              j = 0;
            }
          else
            j += 4;

        }
      else
        {
          if (str[k + j] == '\\')
            j++;

          if (buf[i] != str[k + j])
            {
              k = -1;
              j = 0;
            }
        }
    }

  return !str[k + j];
}
