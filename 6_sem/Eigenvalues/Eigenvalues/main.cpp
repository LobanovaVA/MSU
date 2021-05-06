#include "addition.h"
#include "in_out.h"
#include "solve.h"
#include "residual.h"

int
main (int argc, char *argv[])
{
  char *file_name = 0;
  int matrix_size, print_size, mode, ret;
  double eps;

  ptr_matr ptr_A, ptr_L, ptr_V;
  matr A, V;


  /* ========== get args ========== */
  if (! ( (argc == 5 || argc == 6)
          && sscanf (argv[1], "%d", & matrix_size) == 1 && matrix_size > 0
          && sscanf (argv[2], "%d", & print_size) == 1 && print_size > 0
          && sscanf (argv[3], "%lf", &eps) == 1 && eps > 0
          && sscanf (argv[4], "%d", & mode) == 1 && mode >= 0 && mode < 5 ))
    {
      printf ("ERROR: Usage: %s matrix_SIZE print_SIZE EPS MODE (FILENAME)\n", argv[0]);
      return ERR_USAGE_ARGC;
    }

  if (mode == 0 && argc != 6)
    {
      printf ("ERROR: Incorrect parameter MODE = %d without FILENAME\n", mode);
      return ERR_USAGE_ARGC;
    }


  /* === memory allocation & initialization === */
  ptr_A = std::make_unique <double []> (((matrix_size + 1) * matrix_size) / 2);
  ptr_V = std::make_unique <double []> (2 * matrix_size + 1);
  A = ptr_A.get ();
  V = ptr_V.get ();

  if (mode == 0)
    {
      file_name = argv[5];
      int ret = read_matrix (file_name, matrix_size, A);
      if (ret < 0)
        {
          switch (ret)
            {
            case ERROR_CANNOT_OPEN_INPUT_FILE:
              printf ("ERROR: Cannot open %s\n", file_name);
              break;
            case ERROR_CANNOT_READ_INPUT_FILE:
              printf ("ERROR: Cannot read %s\n", file_name);
              break;
            case ERROR_INCORRECT_MATRIX_TYPE:
              printf ("ERROR: Incorrect matrix type in %s\n", file_name);
              break;
            default:
              printf ("ERROR: Unknown error %d in %s\n", ret, file_name);
            }
          return ERR_DATA_INIT;
        }
    }
  else
    init_matrix (mode, matrix_size, A);

  printf ("\nOriginal matrix A:\n");
  print_symmetric_matrix(A, matrix_size, print_size);

  double norm = norm_symm_matr (matrix_size, A);
  printf("\nMatrix norm = %.3e\n", norm);



  /* ========== transformation matrix ========== */
  double track_orig, lenght_orig;
  cacl_inv_symm_matr (matrix_size, A, track_orig, lenght_orig, norm);

#ifdef FULLPRINT
  printf ("\nOriginal invariants:\n  track  = %.3e\n  lenght = %.3e\n", track_orig, lenght_orig);
#endif

  double time_trans = clock ();
  ret = transform_symm_matrix (matrix_size, A, norm);
  time_trans = (clock () - time_trans) / CLOCKS_PER_SEC;

  printf ("\n===================================================================\n");
  printf ("\nTransformed matrix A:\n");
  print_symmetric_matrix(A, matrix_size, print_size);

  double track_trans, lenght_trans;
  cacl_inv_tridiag_matr (matrix_size, A, track_trans, lenght_trans, norm);

#ifdef FULLPRINT
  printf ("\nTransformed invariants:\n  track  = %.3e\n  lenght = %.3e\n", track_trans, lenght_trans);

  printf ("\nResidual invariants after transformation:\n  residual_track  = %.3e\n  residual_lenght = %.3e\n",
          fabs (track_orig - track_trans) / norm, fabs (lenght_orig - lenght_trans) / norm);
#endif



  /* ========== find eigenvalues ========== */
  double time_solve = clock ();
  ret = find_eigenvalues (matrix_size, A, V, eps, norm);
  time_solve = (clock () - time_solve) / CLOCKS_PER_SEC;

  printf ("\n===================================================================\n");
//  printf ("\n\n============================  RESULTS  ============================\n");

  if (ret < SUCCESS)
    {
      switch (ret)
        {
        case ERROR_SINGULAR_MATRIX:
          printf ("\nERROR: Singular matrix\n");
          break;
        case ERROR_NEGATIVE_MATRIX:
          printf ("\nERROR: Non-positive-definite matrix\n");
          break;
        default:
          printf ("\nERROR: Unknown error = %d in find_eigenvalues\n", ret);
        }
      return ERROR_EPS;
    }



  /* ========== finally ========== */
  printf ("\nEigenvalues:\n");
  print_matrix (V, 1, matrix_size, print_size);

  double track_res, lenght_res;
  cacl_inv_diag_matr (matrix_size, V, track_res, lenght_res, norm);

#ifdef FULLPRINT
  printf ("\nResult invariants:\n  track  = %.3e\n  lenght = %.3e\n", track_res, lenght_res);

  printf ("\nResidual invariants after solve:\n  residual_track  = %.3e\n  residual_lenght = %.3e\n",
          fabs (track_trans - track_res) / norm, fabs (lenght_trans - lenght_res) / norm);

  printf ("\nResidual invariants after\n transformation + solve:\n  residual_track  = %.3e\n  residual_lenght = %.3e\n",
          fabs (track_orig - track_res) / norm, fabs (lenght_orig - lenght_res) / norm);

  printf ("\nTransformation time = %.2f\nSolve time = %.2f\n",
          time_trans / CLOCKS_PER_SEC, time_solve / CLOCKS_PER_SEC);

  printf ("\nIterations = %d\n", ret);
#endif

  printf ("\n===================================================================\n\n");
  printf ("%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
          argv[0], fabs (track_orig - track_res), fabs (lenght_orig - lenght_res),
          ret, ret / matrix_size, time_trans, time_solve);

  return SUCCESS;
}
