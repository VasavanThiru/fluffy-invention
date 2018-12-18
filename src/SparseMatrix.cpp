#include "SparseMatrix.hpp"
#include "vecteur.hpp"

using namespace std;

SparseMatrix::SparseMatrix() : n(0), row(vector <int>(0)), col(std::vector<int>(0)), val(std::vector<double>(0)){}
SparseMatrix::SparseMatrix(int t): n(t),row(vector <int>(0)), col(std::vector<int>(0)), val(std::vector<double>(0)){}
SparseMatrix::SparseMatrix(int t, std::vector<int> & X, std::vector<int> &Y, std::vector<double> &Z): n(t), row(X),col(X),val(Z){}
SparseMatrix::SparseMatrix(const SparseMatrix &M): n(M.n), row(M.row), val(M.val){}

double SparseMatrix::operator()(int i, int j)const
{
  double x(0);
  for(int k=0; k<val.size(); k++)
  {
    if(i == row[k] && j == col[k])
    {
      x= val[k];
    }
  }
  return x;
}

std::ostream & operator <<(std::ostream & o, const SparseMatrix &M){
  for(int i=0; i<M.n; i++)
  {
    for(int j=0; i<M.n; j++)
    {
      o << M(i,j)<< " ";
    }
    o<< std::endl;
  }
  return o;
}

int SparseMatrix::taille() const{return n;}

Vecteur SparseMatrix::MVProd(const Vecteur &B) const{
  Vecteur C(B.taille());
  for(int i=0; i<val.size(); i++)
   {
     C(row[i]) += val[i]*B(col[i]);
   }
   return C;
}



void SparseMatrix::InsertS(const int & i,const int & j,const double & value)
{
    if ((*this)(i,j)==0)
    {
        row.push_back(i);
        col.push_back(j);
        val.push_back(value);
    }
    else
    {
        for (int k = 0; k < val.size(); k++)
        {
            if (i == row[k] && j == col[k])
            {
                val[k] += value;
            }
        }
    }
}
/*
int main()
{
  SparseMatrix V(3);
  //V(1,1)=3;
  cout << V(1,1) <<endl;

  std::vector<int> row = {0,0,0,1,1,2,2,3,4,4};
  std::vector<int> col = {0,3,4,2,3,1,2,2,2,3};
  std::vector<double> val = {3,2,1,5,8,1,2,9,10,4};

  SparseMatrix L(5, row, col, val);
  SparseMatrix O(L);
  cout << O << endl;

}
*/
