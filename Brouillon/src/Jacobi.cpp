#include "Jacobi.hpp"
#include <iostream>

using namespace std;

Jacobi::Jacobi()
{
  DenseMatrix A0(0);
  A=A0;
  Vecteur V0(0);
  b=V0;
  e = 0;
  n_max=0;

  X=V0;
  niter = 0;
  resvec = std::vector<double>(0);
}

Jacobi::Jacobi(const Jacobi &J): A(J.A), b(J.b), e(J.e), n_max(J.n_max), X(J.X), niter(J.niter), resvec(J.resvec) {}
Jacobi::Jacobi(const DenseMatrix &A0, const Vecteur &b0, const double &e0,const int & n_max0): A(A0), b(b0),e(e0), n_max(n_max0){}
//Jacobi::Jacobi(const SparseMatrix &A0, const Vecteur &b0, const double &e0,const int & n_max0): A(A0), b(b0),e(e0), n_max(n_max0){}



void Jacobi::Solve(void)
{
  int n = 0;
  Vecteur x(A.size());
  Vecteur r(b);
  Vecteur y(A.size());
  while( r.norme()>e*b.norme() && n<n_max)
  {
    for(int i = 0; i< A.size(); i++)
    {
      if (A(i,i)!=0)
      {
        y(i)=(1/A(i,i))*r(i);
      }

    }
    x =x+y;
    r=b-A*x;
    n++;
    resvec.push_back(r.norme());
    niter = n;
    X=x;
  }
}


void Jacobi::  parametres(void) const
{
    cout << "ENTREES" << endl << endl;
    cout << "La matrice A" << endl;
    cout << A << endl;
    cout << "Le vecteur b" << endl;
    cout << b <<endl;
    cout << "Epsilon" << endl;
    cout << e << endl << endl;
    cout << "Le nombre d'iterations max " << endl;
    cout << n_max << endl;
    cout << " La réponse est "  << X << " niter " << niter << endl;
}
