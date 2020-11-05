#include "addition.h"

//Problem 1
int
problem_1 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], str_s_copy[LEN];
  int count = 0, fl = 0, flstr = 0, i;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  if (str_s[0] == '^')
    flstr = 1;

  strcpy (str_s_copy, str_s);
  edit (str_s_copy, &fl, 94);

  if (fl == 1)
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_STR_S;
    }

  if (!strlen (str_s_copy))
    {
      fclose (in_fp);
      fclose (out_fp);
      return EMPTY_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if ( (flstr && strstr (buf, str_s_copy + 1) == buf)
           || (!flstr && !!strstr (buf, str_s_copy)) )
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 2
int
problem_2 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], str_s_copy[LEN];
  int count = 0, fl = 0, flstr = 0, i, edit_str_len;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  edit_str_len = strlen (str_s) - 1;
  if (str_s[edit_str_len] == '$' && edit_str_len > 0 && str_s[edit_str_len - 1] != '\\')
    flstr = 1;

  strcpy (str_s_copy, str_s);
  edit (str_s_copy, &fl, 36);

  if (fl == 1)
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_STR_S;
    }

  edit_str_len = strlen (str_s_copy);
  if (!edit_str_len)
    {
      fclose (in_fp);
      fclose (out_fp);
      return EMPTY_STR_S;
    }

  if (flstr)
    {
      str_s_copy[edit_str_len - 1] = 0;
      edit_str_len--;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if ( (flstr && !!strstr (buf + (strlen (buf) - edit_str_len), str_s_copy) )
           || (!flstr && !!strstr(buf, str_s_copy)) )
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }
  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 3
int
problem_3 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], str_s_copy[LEN], *tmp;
  int count = 0, fl = 0, i;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  strcpy (str_s_copy, str_s);
  clear_edit_3 (str_s_copy, &fl);

  if (fl < 0)
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_STR_S;
    }

  if (!strlen (str_s_copy))
    {
      fclose (in_fp);
      fclose (out_fp);
      return EMPTY_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      tmp = strstr (buf, str_s_copy);
      if ( (fl && (!!tmp && (tmp == buf || *(tmp - 1) == ' ' || *(tmp - 1) == '\t' )))
           || (!fl && !!tmp) )
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 4
int
problem_4 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], *buf_copy, str_s_copy[LEN], *tmp;
  int count = 0, fl = 0, i, len_edited, check;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  strcpy (str_s_copy, str_s);
  clear_edit_4 (str_s_copy, &fl);

  if (fl < 0)
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_STR_S;
    }

  len_edited = strlen (str_s_copy);
  if (!len_edited)
    {
      fclose (in_fp);
      fclose (out_fp);
      return EMPTY_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }
      buf_copy = buf;

      while (buf_copy)
        {
          tmp = strstr (buf_copy, str_s_copy);
          if (!tmp)
            break;

          check = (fl && (!!tmp && (!tmp[len_edited] || *(tmp + len_edited) == ' '
                                    || *(tmp + len_edited) == '\t' ))) || (!fl && !!tmp);
          if (check)
            {
              fprintf (out_fp, "%s\n", buf);
              count++;
              if (ferror (out_fp))
                {
                  fclose (in_fp);
                  fclose (out_fp);
                  return ERROR_CANNOT_WRITE_IN_FILE;
                }
              break;
            }
          buf_copy += len_edited;
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 5
int
problem_5 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN];
  int i, ret, count = 0;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  ret = check_incr (str_s, '.');
  if (ret)
    {
      fclose(in_fp);
      fclose(out_fp);
      return ERROR_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if (check_with_dot (buf, str_s))
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 6
int
problem_6 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN];
  int i, ret, count = 0;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  ret = check_incr (str_s, '?');
  if (ret)
    {
      fclose(in_fp);
      fclose(out_fp);
      return ERROR_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if (check_with_query (buf, str_s))
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 7
int
problem_7 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], str_s_copy[LEN];
  int i, ret, count = 0, fl_default = 0;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  ret = check_incr (str_s, '+');
  if (ret)
    {
      fclose(in_fp);
      fclose(out_fp);
      return ERROR_STR_S;
    }

  strcpy (str_s_copy, str_s);
  edit_like_with_plus (str_s_copy, &fl_default, '+');

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if ( (fl_default &&  strstr (buf, str_s_copy))
           || check_with_plus (buf, str_s_copy))
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}



//Problem 8
int
problem_8 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN], str_s_copy[LEN];
  int i, ret, count = 0, fl_default = 0;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  ret = check_incr (str_s, '*');
  if (ret)
    {
      fclose(in_fp);
      fclose(out_fp);
      return ERROR_STR_S;
    }

  strcpy (str_s_copy, str_s);
  edit_like_with_plus (str_s_copy, &fl_default, '*');

  printf ("str = %s\n", str_s_copy);
  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if ( (fl_default &&  strstr (buf, str_s_copy))
           || check_with_star (buf, str_s_copy))
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}




//Problem 9
int
problem_9 (const char *file_name_A, const char *file_name_B, const char *str_s)
{
  FILE *in_fp, *out_fp;
  char buf[LEN];
  int i, ret, count = 0;

  in_fp = fopen (file_name_A, "r");
  if (!in_fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE_A;

  out_fp = fopen (file_name_B, "w");
  if (!out_fp)
    {
      fclose (in_fp);
      return ERROR_CANNOT_OPEN_INPUT_FILE_B;
    }

  ret = check_correct_bracket (str_s);
  if (ret)
    {
      fclose(in_fp);
      fclose(out_fp);
      return ERROR_STR_S;
    }

  while (fgets (buf, LEN, in_fp))
    {
      for (i = 0; buf[i]; i++)
        if (buf[i] == '\n')
          {
            buf[i] = 0;
            break;
          }

      if (check_with_bracket (buf, str_s))
        {
          fprintf (out_fp, "%s\n", buf);
          count++;
          if (ferror (out_fp))
            {
              fclose (in_fp);
              fclose (out_fp);
              return ERROR_CANNOT_WRITE_IN_FILE;
            }
        }
    }

  if (ferror (in_fp))
    {
      fclose (in_fp);
      fclose (out_fp);
      return ERROR_CANNOT_READ_INPUT_FILE;
    }

  fclose (in_fp);
  fclose (out_fp);
  return count;
}
