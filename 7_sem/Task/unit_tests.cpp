#include "unit_tests.h"

#include "unit_tests_base.h"
#include "func_base.h"

#include <cmath>

void Test_def_func ()
{
  Assert (is_equal (rho (0, 0), 2.5), "rho (0, 0)");
  Assert (is_equal (rho (0, 1. / 6.), 1.5), "rho (0, 1/6)");
  Assert (is_equal (rho (0, 1. / 3.), 0.5), "rho (0, 1/3)");

  Assert (is_equal (rho_x (0, 0), 0), "rho_x (0, 0)");
  Assert (is_equal (rho_x (0, 1. / 6.), -3. * M_PI), "rho_x (0, 1/6)");

  Assert (is_equal (g_x (0, 0), 0), "g_x (0, 0)");
  Assert (is_equal (g_x (0, 1. / 6.), -2. * M_PI), "g_x (0, 1/6)");

  Assert (is_equal (u (0, 0), 0), "u (0, 0)");
  Assert (is_equal (u (0, 1. / 8.), 1.), "u (0, 1/8)");
  Assert (is_equal (u (1. / 2.,  1. / 8.), -1.), "u (1/2, 1/8)");
  Assert (is_equal (u (1. / 8.,  1. / 8.), M_SQRT1_2), "u (1/8, 1/8)");
  Assert (is_equal (u (1. / 8.,  1. / 16.), 0.5), "u (1/8, 1/16)");

  Assert (is_equal (u_t (0, 0), 0), "u_t (0, 0)");
  Assert (is_equal (u_t (0, 1. / 8.), 0), "u_t (0, 1/8)");
  Assert (is_equal (u_t (1. / 2.,  1. / 8.), 0.), "u_t (1/2, 1/8)");
  Assert (is_equal (u_t (1. / 8.,  1. / 8.), -M_SQRT2 * M_PI), "u_t (1/8, 1/8)");
  Assert (is_equal (u_t (1. / 8.,  1. / 16.), -M_PI), "u_t (1/8, 1/16)");

  Assert (is_equal (u_x (0, 0), 4 * M_PI), "u_x (0, 0)");
  Assert (is_equal (u_x (1. / 4.,  1. / 8.), 0), "u_x (1/4, 1/8)");
  Assert (is_equal (u_x (1. / 2.,  1. / 4.), 4 * M_PI), "u_x (1/2, 1/4)");
  Assert (is_equal (u_x (1. / 8.,  1. / 4.), -2 * M_SQRT2 * M_PI), "u_x (1/8, 1/4)");
  Assert (is_equal (u_x (1. / 8.,  1. / 16.), 2 * M_PI), "u_x (1/8, 1/16)");

  Assert (is_equal (u_xx (0, 0), 0), "u_xx (0, 0)");
  Assert (is_equal (u_xx (0, 1. / 8.), -16.* M_PI * M_PI ), "u_xx (0, 1/8)");
  Assert (is_equal (u_xx (1. / 2.,  1. / 8.), 16.* M_PI * M_PI), "u_xx (1/2, 1/8)");
  Assert (is_equal (u_xx (1. / 8.,  1. / 16.), -8.* M_PI * M_PI), "u_xx (1/8, 1/16)");
}

void TestAll ()
{
#ifdef DEBUG
  TestRunner runner;
  runner.RunTest (Test_def_func, "Test_def_func");
#endif
}
