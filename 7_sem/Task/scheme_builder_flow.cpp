#include "scheme.h"
#include "addition.h"
#include "unit_tests_base.h"

scheme_builder_flow::scheme_builder_flow (
    const size_t M_, const coefficient_flow &coef_,
    eigen_matrix_t &matrix_, eigen_vector_t &rhs_)
  : M (M_), coef (coef_), matrix (matrix_), rhs (rhs_) {}

void
scheme_builder_flow::fill_system (const double g_t0, const double u_t0)
{
  equation_G_0 (g_t0);
  equation_V_0 (u_t0);

  for (size_t m = 1; m < M; m++)
    {
      equation_G_m (m);
      equation_V_m (m);
    }

  equation_G_M ();
  equation_V_M ();

  matrix.setFromTriplets (triplets.begin (), triplets.end ());
}

void
scheme_builder_flow::equation_G_0 (const double g_t0)
{
  triplets.emplace_back (G(0), G(0), 1.);
  rhs[G(0)] = g_t0;
}

void
scheme_builder_flow::equation_V_0 (const double u_t0)
{
  triplets.emplace_back (V(0), V(0), 1.);
  rhs[V(0)] = u_t0;
}

void
scheme_builder_flow::equation_G_m (const size_t m)
{
  triplets.emplace_back (G(m), G(m-1), coef.G_G_m_minus (m));
  triplets.emplace_back (G(m), V(m-1), coef.G_V_m_minus (m));
  triplets.emplace_back (G(m), G(m),   coef.G_G_m (m));
  triplets.emplace_back (G(m), G(m+1), coef.G_G_m_plus (m));
  triplets.emplace_back (G(m), V(m+1), coef.G_V_m_plus (m));

  rhs[G(m)] = coef.rhs_G_m (m);
}
void
scheme_builder_flow::equation_V_m (const size_t m)
{
  triplets.emplace_back (V(m), G(m-1), coef.V_G_m_minus (m));
  triplets.emplace_back (V(m), V(m-1), coef.V_V_m_minus (m));
  triplets.emplace_back (V(m), V(m),   coef.V_V_m (m));
  triplets.emplace_back (V(m), G(m+1), coef.V_G_m_plus (m));
  triplets.emplace_back (V(m), V(m+1), coef.V_V_m_plus (m));

  rhs[V(m)] = coef.rhs_V_m (m);
}

void
scheme_builder_flow::equation_G_M ()
{
  triplets.emplace_back (G(M), G(M-1), coef.G_M_1 ());
  triplets.emplace_back (G(M), G(M),   coef.G_M ());

  rhs[G(M)] = coef.rhs_G_M ();
}

void
scheme_builder_flow::equation_V_M ()
{
  triplets.emplace_back (V(M), V(M-1), -1.);
  triplets.emplace_back (V(M), V(M), 1.);

  rhs[V(M)] = coef.rhs_V_M ();
}
