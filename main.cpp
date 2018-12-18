#include "SparseMatrix.hpp"
#include "DenseMatrix.hpp"
#include "vecteur.hpp"
#include "Jacobi.hpp"

using namespace std;

int main()
{
  SparseMatrix N(5);
  int n = 2;
  DenseMatrix D(n);
  for(int i=0; i<n-1; i++)
  {
    D(i,i-1)=-1;
    D(i,i)=2;
    D(i,i+1)=-1;
  }

  D(0,0)=2;
  D(0,1)= -1;
  D(n-1, n-2)= -1;
  D(n-1,n-1)=2;
  cout<<D<<endl;

  Vecteur b(n);
  for(int i=0; i<n;i++){
    b(i)=1;

  }



  //cout << b << endl;
  Jacobi A(D, b, 0.001, 1000);
  A.Solve();
  A.parametres();

  Vecteur y(n);
  for(int i = 0; i<n;i++){
    y(i) = 1;
  }
  Vecteur x ;

  x = inv_triang_inf(D,y);
  cout << y << endl;
  cout << "INVERSE " << x << endl;


}
