#ifndef DENSEMATRIX_HP
#define DENSEMATRIX_HP

#include <iostream>
#include <vector>
#include <string>
#include "vecteur.hpp"

class DenseMatrix{

private:
  int n;
  std::vector<double> v;

public:
  DenseMatrix();
  DenseMatrix(int t);
  DenseMatrix(const std::vector<double> &g);
  DenseMatrix(const DenseMatrix &M);
  int size() const;
  double & operator() (int i, int j);
  double operator()( int i, int j) const;
  friend std::ostream & operator <<(std::ostream &, const DenseMatrix &);
  void Load(char* const filename);
  friend double Frobenius(const DenseMatrix &D);
  Vecteur operator*(const  Vecteur& b);

  //DenseMatrix operator +(const DenseMatrix &A, const DenseMatrix& B);
};

Vecteur inv_triang_inf(const DenseMatrix &T, Vecteur &y);
#endif
