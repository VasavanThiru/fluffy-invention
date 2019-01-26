#include "GradientConjuguee.hpp"
#include <iostream>

using namespace std;

GradientConjuguee :: GradientConjuguee ()
{
  DenseMatrix A0(0);
  A= A0;
  Vecteur V0(0);
  b= V0;
  e =0;
  n_max = 0;

  X=V0;
  niter = 0;
  resvec = vector <double>(0);

}

GradientConjuguee :: GradientConjuguee(const GradientConjuguee & J): A(J.A), b(J.b), e(J.e), n_max(J.n_max), X(J.X), niter(J.niter), resvec(J.resvec) {}
GradientConjuguee :: GradientConjuguee(const DenseMatrix & A0, const Vecteur & b0, const double & e0, const int & n_max0) : A(A0), b(b0), e(e0), n_max(n_max0) {}


void GradientConjuguee :: Solve(void){
  int k = 0;
  Vecteur x(A.size());
  Vecteur r(b);
  Vecteur p(r);
  Vecteur y(r.taille());
  double alpha_k;
  double beta_k;


  while(r.norme()>e*b.norme() && k<n_max)
  {

    alpha_k = Ps(r,r)/Ps(A*p,p);
    x = x +p*alpha_k;
    y = r;
    r = r -(A*p)*alpha_k;
    beta_k = Ps(r,r)/Ps(y,y);
    p = r+p*beta_k;
    k++;
    resvec.push_back(r.norme());
    niter = k;
    X = x;
  }
}


void GradientConjuguee :: parametres(void) const
{
    cout << "ENTREES" << endl << endl;
    cout << "La matrice A" << endl;
    cout << A << endl;
    cout << "Le vecteur b" << endl;
    cout << b << endl;
    cout << "Epsilon" << endl;
    cout << e << endl << endl;
    cout << "Le nombre d'iterations max" << endl;
    cout << n_max << endl;
    cout << "La réponse est " << X << "niter " << niter << endl;
    }
