#ifndef JACOBI_HPP
#define JACOBI_HPP
#include "DenseMatrix.hpp"
#include "vecteur.hpp"
#include "SparseMatrix.hpp"
#include <vector>

class Jacobi{

private:
  DenseMatrix A;
  Vecteur b;
  double e;
  int n_max;

  Vecteur X;
  int niter;
  std::vector<double> resvec;

public:
  Jacobi();
  Jacobi(const Jacobi &J);
  Jacobi(const DenseMatrix &A0, const Vecteur &b0, const double &e0, const int & n_max0);
  //Jacobi(const SparseMatrix &A0, const Vecteur &b0, const double &e0, const int & n_max0);

  void Solve(void);
  void parametres(void) const;

};

#endif
