#include "addition.h"
#include "student.h"
#include "list2.h"
#include "tree.h"

int list2::m = 0;
int list2::r = 0;

template <class T> void
solve (tree<T> *data, const char *filename, const char *prog, int r);

int
main (int argc, char *argv[])
{
  char *filename;
  int r, m;

  /* === get args === */
  if (! ( argc == 4 && sscanf (argv[1], "%d", &r) == 1
          && sscanf (argv[3], "%d", &m) == 1) )
    {
      printf ("ERROR: Usage: %s max_print_SIZE FILENAME list_SIZE\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  filename = argv[2];

  list2::set_m (m);
  list2::set_r (r);


  /* === tree <student> === */
  tree <student> *stud_tr = new tree <student>;
  solve (stud_tr, filename, argv[0], r);
  delete stud_tr;


  /* === tree <list2> === */
  tree <list2> *list_tr = new tree <list2>;
  solve (list_tr, filename, argv[0], r);
  delete list_tr;


  return SUCCESS;
}


template <class T> void
solve (tree<T> *data, const char *filename, const char *prog, int r)
{

  int i, ret;
  int ans[5] = {0};
  double time[5];

  ret = data -> read (filename);

  if (ret < SUCCESS)
    {
      switch (ret)
        {
        case ERROR_CANNOT_OPEN_INPUT_FILE:
          printf ("%s : ERROR: Cannot open input file %s\n", prog, filename);
          break;
        case ERROR_CANNOT_READ_INPUT_FILE:
          printf ("%s : ERROR: Cannot read input file %s\n", prog, filename);
          break;
        case ERROR_NOT_ENOUGH_MEMORY:
          printf ("%s : ERROR: Not enough memory to read from %s\n", prog, filename);
          break;
        default:
          printf ("%s : ERROR: Unknown error %d in %s\n", prog, ret, filename);
        }
      return;
    }

  data -> print (r);

  time[0] = clock();
  ans[0] = data -> problem_1 ();
  time[0] = (clock() - time[0]) / CLOCKS_PER_SEC;

  time[1] = clock();
  ans[1] = data -> problem_2 ();
  time[1] = (clock() - time[1]) / CLOCKS_PER_SEC;

  time[2] = clock();
  ans[2] = data -> problem_3 ();
  time[2] = (clock() - time[2]) / CLOCKS_PER_SEC;

  time[3] = clock();
  ans[3] = data -> problem_4 ();
  time[3] = (clock() - time[3]) / CLOCKS_PER_SEC;

  time[4] = clock();
  ans[4] = data -> problem_5 ();
  time[4] = (clock() - time[4]) / CLOCKS_PER_SEC;

  for (i = 0; i < 5; i++)
    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", prog, i + 1, ans[i], time[i]);

}


