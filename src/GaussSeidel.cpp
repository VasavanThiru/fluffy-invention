#include "GaussSeidel.hpp"
#include <iostream>

using namespace std;

GaussSeidel::GaussSeidel()
{
  DenseMatrix A0(0);
  A = A0;
  Vecteur V0(0);
  b = V0;
  e=0;
  n_max=0;

  X=V0;
  niter = 0;
  resvec = std::vector<double>(0);

}

GaussSeidel::GaussSeidel(const GaussSeidel &J): A(J.A), b(J.b), e(J.e), n_max(J.n_max), X(J.X), niter(J.niter), resvec(J.resvec) {}
GaussSeidel::GaussSeidel(const DenseMatrix &A0, const Vecteur & b0, const double & e0, const int & n_max0):  A(A0), b(b0), e(e0), n_max(n_max0) {}

void GaussSeidel::Solve(void){

  int n = 0;
  Vecteur x(A.size());
  Vecteur r(b);
  Vecteur y(A.size());
  DenseMatrix M(A.size());
  int k = 0;
  for(int i=0; i<A.size(); i++)
  {
      for(int j=0; j<=k; j++){
        M(i,j)=A(i,j);
      }
      k++;
  }
  while(r.norme()>e*b.norme() && n<n_max)
  {
    y =  inv_triang_inf(M,r);
    x = x+y;
    r = b-A*x;
    n++;
    resvec.push_back(r.norme());
    niter = n;
    X = x;
  }
}

void GaussSeidel:: parametres(void) const
{
    cout << "ENTREES" << endl;
    cout << "La matrice A" << endl;
    cout << A << endl;
    cout << "Le vecteur b" << endl;
    cout << b << endl;
    cout << "Epsilon" << endl;
    cout << e << endl;
    cout << "Le nombre d'iterations max" << endl;
    cout << n_max << endl;
    cout << "La réponse est " << X << "niter " << niter << endl;
}
