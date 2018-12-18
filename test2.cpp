#include <iostream>
#include "vecteur.hpp"
#include "DenseMatrix.hpp"

int main()
{
  Vecteur b(3), x, r(3);
  DenseMatrix M(3);
  M(0, 0) = 1.;
  M(0, 1) = 0.;
  M(0, 2) = 0.;
  M(1, 0) = 2.;
  M(1, 1) = 3.;
  M(1, 2) = 0.;
  M(2, 0) = 4.;
  M(2, 1) = 5.;
  M(2, 2) = 6.;
  b(0) = 1.;
  b(1) = 2.;
  b(2) = 3.;
  std::cout << M << std::endl;
  std::cout << b << std::endl;
  x = inv_triang_inf(M, b);
  std::cout << x << std::endl;
  r(0) = 1.;
  r(1) = 0.;
  r(2) = -1. / 6.;
  if((x - r).norme() != 0.) {
    std::cout << "Error" << std::endl;
  }
  return 0;
}

