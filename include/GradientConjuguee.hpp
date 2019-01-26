#ifndef GRADIENT_CONJUGUEE_HPP
#define GRADIENT_CONJUGUEE_HPP

#include "DenseMatrix.hpp"
#include "vecteur.hpp"

class GradientConjuguee
{
private:
  DenseMatrix A;
  Vecteur b;
  double e;
  int n_max;

  Vecteur X;
  int niter;
  std :: vector <double> resvec;

public:
  GradientConjuguee();
  GradientConjuguee(const GradientConjuguee & J);
  GradientConjuguee(const DenseMatrix & A0, const Vecteur & b0, const double & e0, const int & n_max0);
  void Solve(void);
  void parametres(void) const;


};
#endif
