#ifndef SPARSEMATRIX_HP
#define SPARSEMATRIX_HP

#include <cmath>
#include <iostream>
#include <vector>
#include "vecteur.hpp"

class SparseMatrix{

private:
  int n;
  std::vector<int> row;
  std::vector<int> col;
  std::vector<double> val;

public:
  SparseMatrix();
  SparseMatrix(int t);
  SparseMatrix(int t, std::vector<int> & X, std::vector<int> &Y, std::vector<double> &Z);
  SparseMatrix(const SparseMatrix &M);
  double operator()(int i, int j) const;
  friend std::ostream & operator <<(std::ostream &, const SparseMatrix &);
  int taille() const;
  Vecteur MVProd(const Vecteur &B) const;
  void InsertS(const int& j, const int& k, const double& v);
};
#endif
