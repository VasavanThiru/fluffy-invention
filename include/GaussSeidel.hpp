#ifndef GAUSS_SEIDEL_HPP
#define GAUSS_SEIDEL_HPP
#include "DenseMatrix.hpp"
#include "vecteur.hpp"

class GaussSeidel{

private:
  DenseMatrix A;
  Vecteur b;
  double e;
  int n_max;

  Vecteur X;
  int niter;
  std::vector <double> resvec;

public:

  GaussSeidel();
  GaussSeidel(const GaussSeidel &J);
  GaussSeidel(const DenseMatrix &A0, const Vecteur & b0, const double & e0, const int & n_max0);
  void Solve(void);
  void parametres(void) const;

};
#endif
