#include <iostream>
#include <cstdlib>
#include <vector>
#include "DenseMatrix.hpp"
#include <cmath>
#include <fstream>
#include <string>
#include "vecteur.hpp"

using namespace std;

DenseMatrix::DenseMatrix(){
  n=0;
  v.resize(n);
}

DenseMatrix::DenseMatrix(int t): n(t), v(std::vector<double>(t*t,0)){}
DenseMatrix::DenseMatrix(const std::vector<double> &g): n(sqrt(g.size())), v(g){}
DenseMatrix::DenseMatrix(const DenseMatrix &M): n(M.n), v(M.v){}

int DenseMatrix::size() const{
  return n;
}

double & DenseMatrix::operator()(int i, int j) {
  return v[i+j*n];
}

double DenseMatrix::operator()( int i, int j)const{
  return v[i+j*n];
}

std::ostream & operator <<(std::ostream & o, const DenseMatrix &M){
  for(int i=0; i<M.n; i++)
  {
    for(int j=0; j<M.n; j++)
    {
      o << M(i,j) << " ";
    }
    o<< std::endl;
  }
  return o;
}

DenseMatrix operator +(const DenseMatrix& A, const DenseMatrix& B){
  int m = A.size();
  DenseMatrix C(m);
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      C(i,j)= A(i,j)+B(i,j);
    }
  }
  return C;
}

Vecteur DenseMatrix::operator*(const Vecteur& b){
  int m = size();
  Vecteur C(m);
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      C(i) +=  (*this)(i,j)*b(j);
    }
  cout<< C(i) <<endl;
  }
  return C;
}


Vecteur inv_triang_inf(const DenseMatrix &T, Vecteur &y){
  int m = T.size();
  Vecteur x(m);
  double S = 0;
  for(int j=0; j<m; j++){
    S=0;
    for(int k=0; k<= j-1; k++){
      S = S+ T(j,k)*x(k);}
    x(j) = 1/T(j,j)*(y(j)-S);
    }
  return x;
}

Vecteur inv_triang_sup(const DenseMatrix &A, Vecteur &b){
  int n = A.size();
  Vecteur x(n);
  double S = 0;
  for(int j=0; j<n; j++){
    S=0;
    for(int k=j+1; k<=n ; k++){
      S= S+ A(j,k)*x(k);}
    x(j) = 1/A(j,j)* (b(j) -S);
    }
  return x;
}




void DenseMatrix::Load(char* const filename){
  ifstream fichiermat(filename, ios::in);
  if (fichiermat){
    string chaine;
    fichiermat >> chaine >> n >> n >> chaine;
    int rc = n*n;
    v.resize(rc);
    for(int i=0; i<rc; i++){
      fichiermat >> v[i];
    }
  }
  else{
    cerr<<"Impossible d'ouvrir le fichier !" << endl;
  }
}


/*

int main()
{
  DenseMatrix M;
  DenseMatrix N(7);
  vector <double> v(4,2);
  v[0]=1;v[1]=2;v[2] =3; v[3]= 4;
  DenseMatrix L(v);
  DenseMatrix O(L);
  cout<< M << endl;
  cout<< N << endl;
  cout<< L << endl;
  cout<< O+L << endl;

  int n = 7;
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
}
*/
