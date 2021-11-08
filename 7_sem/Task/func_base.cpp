#include "func_base.h"
#include "structs.h"

#include <math.h>

double
rho (const double t, const double x)
{
  return exp (t) * (cos (3. * M_PI * x) + 1.5);
}

double
rho_t (const double t, const double x)
{
  return rho (t, x);
}

double
rho_x (const double t, const double x)
{
  return -3. * M_PI * exp (t) * sin (3. * M_PI * x);
}

/* ============================================================================ */

double
g (const double t, const double x)
{
  return log (rho (t, x));
}

double
g_t (const double /*t*/, const double /*x*/)
{
  return 1.;
}

double
g_x (const double t, const double x)
{
  return rho_x (t, x) / rho (t, x);
}

/* ============================================================================ */

double
u (const double t, const double x)
{
  return cos (2. * M_PI * t) * sin (4. * M_PI * x);
}

double
u_t (const double t, const double x)
{
  return -2. * M_PI * sin (2. * M_PI * t) * sin (4. * M_PI * x);
}

double
u_x (const double t, const double x)
{
  return 4. * M_PI * cos (2. * M_PI * t) * cos (4. * M_PI * x);
}

double
u_xx (const double t, const double x)
{
  return -16.* M_PI * M_PI * cos (2. * M_PI * t) * sin (4. * M_PI * x);
}

/* ============================================================================ */

double
f0 (const double t, const double x)
{
  return g_t (t, x) + u (t, x) * g_x (t, x) + u_x (t, x);
}

double
f (const double t, const double x, const data_t &data)
{
  return u_t (t, x) + u (t, x) * u_x (t, x)
      + tilde_p_rho (rho (t, x), data) * g_x (t, x)
      - data.mu * u_xx (t, x) / rho (t, x);
}

double
f0_const (const double /*t*/, const double /*x*/)
{
  return 0.;
}

double
f_const (const double /*t*/, const double /*x*/, const data_t &/*data*/)
{
  return 0.;
}

/* ============================================================================ */

double
rho_1 (const double /*t*/, const double x)
{
  return (x > 4.5 && x < 5.5) ? 2 : 1;
}

double
g_1 (const double t, const double x)
{
  return log (rho_1 (t, x));
}

double
u_1 (const double /*t*/, const double /*x*/)
{
  return 0.;
}

double
rho_2 (const double /*t*/, const double /*x*/)
{
  return 1.;
}

double
g_2 (const double t, const double x)
{
  return log (rho_2 (t, x));
}

double
u_2 (const double /*t*/, const double x)
{
  return (x > 4.5 && x < 5.5) ? 1 : 0;
}

/* ============================================================================ */

double
rho_3 (const double /*t*/, const double x, const size_t k)
{
  return 2. + sin (k * M_PI * x);
}

double
g_3 (const double t, const double x, const size_t k)
{
  return log (rho_3 (t, x, k));
}

double
u_3 (const double /*t*/, const double /*x*/, const size_t /*k*/)
{
  return 0;
}

double
rho_4 (const double /*t*/, const double /*x*/, const size_t /*k*/)
{
  return 1.;
}

double
g_4 (const double t, const double x, const size_t k)
{
  return log (rho_4 (t, x, k));
}

double
u_4 (const double /*t*/, const double x, const size_t k)
{
  return sin (k * M_PI * x);
}

/* ============================================================================ */

double
rho_0 (const double /*t*/, const double /*x*/)
{
  return 1.;
}

double
g_0 (const double t, const double x)
{
  return log (rho_0 (t, x));
}

double
u_0 (const double /*t*/, const double /*x*/)
{
  return 0.;;
}
