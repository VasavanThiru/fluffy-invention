#ifndef VECTEUR_HP
#define VECTEUR_HP

#include <iostream>
#include <vector>

class Vecteur{


private:
  int n;
  std::vector<double> v;

public:

  Vecteur();
  Vecteur(int t);
  Vecteur(const std::vector <double> &);
  Vecteur(const Vecteur &M);

  int taille () const;

  double & operator() (int i);
  double operator() (int i) const;

  friend std:: ostream & operator <<(std:: ostream&,const Vecteur &);
  Vecteur operator *(const double &);
  Vecteur & operator = (const Vecteur &V);
  friend double Ps(const Vecteur &, const Vecteur &);
  std::vector<double> getv()const;
  Vecteur operator +(const Vecteur &);
  Vecteur operator -(const Vecteur &);
  double norme();
};
#endif
