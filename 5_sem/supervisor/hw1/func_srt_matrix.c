#include "all_func.h"

int
read_str_matrix (const char *file_name, char** matrix, int m_size,
                 int n_size, char* space)
{
  int i, j, word_len;
  char buff[LEN];
  char *ptr, *word;

  FILE *fp = fopen (file_name, "r");
  if (!fp)
    return ERROR_CANNOT_OPEN_INPUT_FILE;

  for (i = 0; i < m_size; i++)
    {
      if (!fgets (buff, LEN, fp))
        {
          fclose (fp);
          return ERROR_CANNOT_READ_INPUT_FILE;
        }

      word = strtok_r (buff, space, &ptr);
      for (j = 0; j < n_size; j++)
        {
          if (word)
            {
              word_len = strlen (word);
              matrix[i * n_size + j] = (char *) malloc ((word_len + 1) * sizeof (char));
              if (!matrix[i * n_size + j])
                {
                  fclose (fp);
                  return ERROR_NOT_ENOUGH_MEMMORY;
                }
              if (word[word_len - 1] == '\n')
                word[word_len - 1] = 0;
              else
                word[word_len] = 0;

              strcpy (matrix[i * n_size + j], word);
            }
          else
            {
              matrix[i * n_size + j] = (char *) malloc (sizeof (char));
              if (!matrix[i * n_size + j])
                {
                  fclose (fp);
                  return ERROR_NOT_ENOUGH_MEMMORY;
                }
              matrix[i * n_size + j][0] = 0;
            }
          word = strtok_r (NULL, space, &ptr);
        }
    }

  fclose (fp);
  return 0;
}

void
print_str_matrix (char **matrix, int m_size, int n_size)
{
  int i, j;
  int m_print_size = ((m_size > M_MAX_PRINT) ? M_MAX_PRINT : m_size);
  int n_print_size = ((n_size > N_MAX_PRINT) ? N_MAX_PRINT : n_size);
  for (i = 0; i < m_print_size; i++)
    {
      for (j = 0; j < n_print_size; j++)
        {
          printf ("%20s", matrix[i * n_size + j]);
        }
      printf ("\n");
    }
}

void free_matrix (char **matrix, int m_size, int n_size)
{
  int i;
  for (i = 0; i < m_size * n_size; i++)
    {
      if (matrix[i])
        free (matrix[i]);
    }
  if (matrix)
    free (matrix);
}

void
quick_sort_str (char **matrix, int m_size, int n_size)
{
  int pos;
  int elem;

  if (m_size < 2)
    return ;

  while (m_size > 2)
    {
      elem = m_size / 2;
      pos = lin_redbuild_str (matrix, m_size, n_size, elem);
      if (pos < m_size - pos)
        {
          quick_sort_str (matrix, pos, n_size);
          matrix += pos * n_size;
          m_size -= pos;
        }
      else
        {
          quick_sort_str (matrix + pos * n_size, m_size - pos, n_size);
          m_size = pos;
        }
    }

  if (m_size == 2 && (cmp_lines (matrix, n_size, m_size - 2, m_size - 1) < 0))
    swap_lines (matrix, n_size, m_size - 2, m_size - 1);
  return ;
}


int
lin_redbuild_str (char **matrix, int m_size, int n_size, int i)
{
  int left = 0, right = m_size - 1;
  char *i_max = matrix[i * n_size + max_of_line(matrix, n_size, i)];
  while (left <= right)
    {
      while ( cmp_lines_elem (matrix, n_size, left, i_max) > 0)
        left++;
      while ( cmp_lines_elem (matrix, n_size, right, i_max) < 0)
        right--;
      if (left <= right)
        {
          swap_lines (matrix, n_size, left, right);
          right--;
          left++;
        }
    }
  return left;
}

void swap_lines (char **matrix, int n_size, int i_pos, int j_pos)
{
  char *tmp;
  int i = i_pos * n_size, j = j_pos * n_size, k;
  for (k = 0; k < n_size; k++)
    {
      tmp = matrix[i + k];
      matrix[i + k] = matrix[j + k];
      matrix[j + k] = tmp;
    }
}

int
max_of_line (char **matrix, int n_size, int pos)
{
  int max_pos = 0, i = pos * n_size, j;
  for (j = 0; j < n_size; j++)
    {
      if (strcmp (matrix[i + j], matrix[i + max_pos]) > 0)
        max_pos = j;
    }
  return max_pos;
}

int
cmp_lines (char **matrix, int n_size, int i_pos, int j_pos)
{
  char *i_max = matrix[i_pos * n_size], *j_max = matrix[j_pos * n_size];
  int i = i_pos * n_size, j = j_pos * n_size, k;

  for (k = 0; k < n_size; k++)
    {
      if (strcmp(matrix[i + k], i_max) > 0)
        i_max = matrix[i + k];
      if (strcmp(matrix[j + k], j_max) > 0)
        j_max = matrix[j + k];
    }
  return strcmp (i_max, j_max);
}

int
cmp_lines_elem (char **matrix, int n_size, int pos, char *elem)
{
  char* i_max = matrix[pos * n_size];
  int i = pos * n_size, k;
  for (k = 0; k < n_size; k++)
    {
      if (strcmp (matrix[i + k], i_max) > 0)
        i_max = matrix[i + k];
    }
  return strcmp (i_max, elem);
}


