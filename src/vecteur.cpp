#include <iostream>
#include <vector>
#include "vecteur.hpp"
#include <cmath>

using namespace std;

Vecteur::Vecteur(){
  n=0;
  v = std::vector<double> (0);
}

Vecteur::Vecteur(int t){
  n=t;
  v.resize(n,0);
}

Vecteur::Vecteur(const vector <double> &v0){
  n = v0.size();
  v = v0;
}



Vecteur::Vecteur(const Vecteur &M){
  n = M.n;
  v = M.v;
}

double Vecteur::operator()(int i) const{
  return v[i];
}

double & Vecteur::operator()(int i){
  return v[i];
}

int Vecteur::taille( ) const{
  return n;
}


std::ostream & operator <<(std::ostream & o, const Vecteur &M){

  for(int i= 0; i < M.n; i++)
  {
    o<< M(i) << " ";
  }
  o<<std::endl;
  return o;
}

Vecteur Vecteur::operator *(const double &a){
  Vecteur C(*this);
  for (int i = 0; i<C.taille(); i++)
  {
    C(i) = C(i)*a;

  }
  return C;
}

Vecteur & Vecteur::operator = (const Vecteur & V)
{
  n = V.n;
  v = V.v;
  return (*this);
}

double Ps(const Vecteur &V, const Vecteur &U){

  double A(0);
  for(int i = 0; i<V.taille(); i++){
    A += V(i)*U(i);
  }
  return A;
}

std::vector<double> Vecteur::getv() const{
  return v;
}

Vecteur Vecteur::operator +(const Vecteur &B){
  int m = B.taille();
  Vecteur C(m);
  for(int i=0; i<m; i++)
  {
    C(i)= v[i]+B(i);
  }
  return C;
}

Vecteur Vecteur::operator -(const Vecteur &B){
  int m = B.taille();
  Vecteur C(m);
  for(int i=0; i<m; i++)
  {
    C(i)= v[i]-B(i);
  }
  return C;
}

double Vecteur::norme(){
  double A(0);
  for(int i=0; i<n; i++)
  {
    A +=v[i]*v[i];
  }
  return sqrt(A);
}

/*

// TEST
int main()
{
  Vecteur V(3);
  std::vector<double> v(4,3);
  v[1]=1;
  //v[0]=1;
  v[2]=2;
  Vecteur B(v);
  cout<<B<<endl;
}
*/
