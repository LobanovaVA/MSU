#ifndef ADDITION_H
#define ADDITION_H

enum err_type {
  NO_ERROR,
  USAGE_ARGC,
  PRECOND,
  EIGEN_SOLVER
};

#include <vector>
using vect = std::vector<double>;

#define G(i) (2 * (i))
#define V(i) (2 * (i) + 1)

#endif // ADDITION_H



