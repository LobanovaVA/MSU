#include "addition.h"

static int from_root[2];
static int to_root[2];

void
process_function (const char *filename, int my_rank, int p)
{
  (void) p;
  char byte;
  int ret;

  ret = func (filename);

  if (read (from_root[0], &byte, 1) != 1)
    {
      fprintf (stderr, "Error reading in process %d, pid = %d\n",
               my_rank, getpid ());
      return;
    }

  if (write (to_root[1], &ret, sizeof (int)) != sizeof (int))
    {
      fprintf (stderr, "Error writing in process %d, pid = %d\n",
               my_rank, getpid ());
      return;
    }
}



int
main (int argc, char * argv[])
{
  pid_t pid;
  int p, i, ret = 0, total = 0;
  char byte;

  if (argc < 2)
    {
      printf ("Usage: %s filename_1 ... filename_m\n", argv[0]);
      return 1;
    }

  p = argc - 1;

  if (pipe (from_root) == -1 || pipe (to_root) == -1)
    {
      fprintf (stderr, "Cannot pipe!\n");
      return 2;
    }

  for (i = 0; i < p ; i++)
    {
      pid = fork ();
      if (pid == -1)
        {
          fprintf (stderr, "Cannot fork!\n");
          return 3 + i;
        }
      else if (pid == 0)
        {
          close (from_root[1]);
          close (to_root[0]);

          process_function (argv[i + 1], i, p);

          close (from_root[0]);
          close (to_root[1]);

          return 0;
        }
    }

  close (from_root[0]);
  close (to_root[1]);

  for (i = 0; i < p ; i++)
    {
      byte = (char) i;

      if (write (from_root[1], &byte, 1) != 1)
        {
          fprintf (stderr, "Error writing in root process\n");
          return 100;
        }

      if (read (to_root[0], &ret, sizeof (int)) != sizeof (int))
        {
          fprintf (stderr, "Error reading in root process\n");
          return 101;
        }

      if (ret < 0)
        {
          total = -1;
          switch (ret)
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              fprintf (stderr, "Error cannot open input file %s\n", argv[i + 1]);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              fprintf (stderr, "Error cannot read input file %s\n", argv[i + 1]);
              break;
            default:
              fprintf (stderr, "Unknown error %d in %s\n", ret, argv[i + 1]);
            }
        }
      else if (total >= 0)
        total += ret;
    }

  close (from_root[1]);
  close (to_root[0]);

  if (total >= 0)
    printf ("Ans = %d\n", total);
  return 0;
}
