#ifndef GAUSS_SEIDEL_HPP
#define GAUSS_SEIDEL_HPP
#include "DenseMatrix.hpp"
#include "vecteur.hpp"

class GaussSeidel{

private:
  DenseMatrix A;
  Vecteur b;
  int n_max;

  Vecteur X;
  int niter;
  std::vector <double> resvec;

public:

  GaussSeidel();



};
#endif
