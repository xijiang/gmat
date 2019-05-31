// icpc -std=c++11 -mkl -DMKL_ILP64 inverse.cpp -o inverse
#include <iostream>
#include <fstream>
#include <iomanip>
#include <mkl.h>

using namespace std;
void readdiag(double* G,	// the (big) G matrix, row-majored
	      int     b,	// which block to update
	      MKL_INT dim,	// the block size, usually of 1k, but the last
	      MKL_INT blk,	// the BLK size
	      MKL_INT nid){	// also the dim of G
  MKL_INT  len=dim*dim, start=b*blk;
  double   g[len];
  int      i, j;
  ifstream fin(to_string(b+1)+'-'+to_string(b+1)+".G");
    
  fin.read(g, len*sizeof(double));
  for(i=0; i<dim; ++i)		// store the G as the lower triangle
    for(j=0; j<=i; ++j) G[(start+i)*nid+start+j] = g[i*dim+j];
}

void readoffd(double* G;
	      

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);
  const MKL_INT NID=63721,   BLK=1000;
  const MKL_INT LEN=NID*NID, NB =NID/BLK, NR =NID%BLK; // number of blocks, number of residues
  const double  Diag=100;			       // the number to be added to the diagonal.
  double        G[LEN];

  // Read the G matrix
  // -- for those of dimension BLK x BLK
  for(int i=0; i<NB; ++i){
    readdiag(G, i, BLK, BLK, NID);
    for(int j=0; j<i; ++j) readoffd(G, i, j, BLK, BLK, NID);
  }
  // -- for those of dimension lesser, e.g., at the lower edge
  if(NR){
    for(int i=0; i<NB; ++i) readoffd(G, NB, i, NR, BLK, NID);
    readdiag(G, NB, NR, NID);
  }

  inverse(G, NID);
  output (G, NID);
  return 0;
}

/*
//void sample(double*p, int lda){
//  cout<<'\n';
//  for(auto i=0; i<10; ++i){
//    for(auto j=0; j<10; ++j) cout<<setw(10)<<p[i*lda+j];
//    cout<<'\n';
//  }
//}
  
  
  ifstream fin("1-1.G");
  fin.seekg(0, fin.end);
  MKL_INT len = fin.tellg();
  fin.seekg(0, fin.beg);
  MKL_INT ne=len/sizeof(double);
  lapack_int info;

  double G[ne], B[ne], I[ne];
  fin.read(reinterpret_cast<char*>(G), len);
  for(auto i=0; i<ne; ++i) B[i] = G[i];
  cout<<fixed;
  cout.precision(6);
  sample(G, 1000);
  
  info = LAPACKE_dpotrf (LAPACK_ROW_MAJOR, 'L', 1000, G, 1000);
  sample(G, 1000);
  info = LAPACKE_dpotri (LAPACK_ROW_MAJOR, 'L', 1000, G, 1000);
  for(auto i=0; i<1000; ++i)
  for(auto j=i+1; j<1000; ++j)
  G[i*1000+j] = G[j*1000+i];
  sample(G, 1000);
  cblas_dgemm (CblasRowMajor, CblasNoTrans, CblasNoTrans, 1000, 1000, 1000, 1., G, 1000, B, 1000, 0., I, 1000);
  sample(I, 1000);
  //dpotrf;
  //dpotri;
  //dgemm;
  //cout<<sizeof(lapack_int)<<' '<<sizeof(MKL_INT)<<endl;
  //lapack_int LAPACKE_dpotrf (int matrix_layout , char uplo , lapack_int n , double * a ,lapack_int lda );
  //lapack_int LAPACKE_dpotri (int matrix_layout , char uplo , lapack_int n , double * a ,lapack_int lda );
  //void cblas_dgemm (const CBLAS_LAYOUT Layout, const CBLAS_TRANSPOSE transa, constCBLAS_TRANSPOSE transb, const MKL_INT m, const MKL_INT n, const MKL_INT k, const doublealpha, const double *a, const MKL_INT lda, const double *b, const MKL_INT ldb, constdouble beta, double *c, const MKL_INT ldc);
  //matrix_layout: LAPACK_ROW_MAJOR / LAPACK_COL_MAJOR
  //uplo = 'U' / 'L' for upper or lower storage
  //I always make lda==n, the dimension of the square matrix
  //CBLAS_TRANSPOSE: CblasNoTrans / CblasTrans
  cout<<G[0]<<endl;
*/
