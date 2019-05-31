// icpc -std=c++11 -mkl -DMKL_ILP64 inverseG.cpp -o inverseG
#include <iostream>
#include <cmath>
#include <mkl.h>

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);
  double diag{10};
  if(argc==2) diag = stof(argv[1]);

  // Read G which is in binary storage
  cin.seekg(0, cin.end);
  MKL_INT sz  = cin.tellg();
  MKL_INT len = sz/sizeof(double);
  MKL_INT dim(sqrt(len)), info;
  cin.seekg(0, cin.beg);
  
  double G[len];
  cin.read(reinterpret_cast<char*>(G), sz);
  for(MKL_INT i=0; i<dim; ++i) G[i*dim+i]+=diag;
  
  info = LAPACKE_dpotrf (LAPACK_ROW_MAJOR, 'L', dim, G, dim);
  info = LAPACKE_dpotri (LAPACK_ROW_MAJOR, 'L', dim, G, dim);

  cout.write(reinterpret_cast<char*>(G), sz);
  return 0;
}
