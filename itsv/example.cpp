#include <iostream>
#include <random>
#include <numeric>
#include <vector>

using namespace std;
using Vec=vector<double>;
using Mat=vector<Vec>;

void bake_rng(mt19937&);
void steepest_descent(Mat&, Vec&, Vec&);

int main(int argc, char *argv[])
{
  // The random numbers
  const int Dim{2000}, Dgv{200};
  mt19937 rng;
  bake_rng(rng);
  uniform_real_distribution<double> Vdd;

  // Define the problem, find x, such that Ax=b
  Mat A;
  Vec x, b, t;
  for(auto i{0}; i<Dim; ++i){	// column-majored, creats uppper-triangle
    Vec v;
    for(auto j{0}; j<i; ++j) v.push_back(Vdd(rng));
    v.push_back(Vdd(rng)+Dgv);
    A.push_back(v);
    t.push_back(Vdd(rng));
  }
  for(auto i=0; i<Dim; ++i)	// the full matrix
    for(auto j=i+1; j<Dim; ++j) A[i].push_back(A[j][i]);

  for(auto&p:A) b.push_back(inner_product(&p[0], &p[0]+Dim, &t[0], 0.));

  steepest_descent(A, b, x);

  cout<<fixed;
  cout.precision(4);
  for(auto&p:A){
    for(auto&q:p) cout<<' '<<q;
    cout<<'\n';
  }
  for(auto&p:x) cout<<' '<<p;
  cout<<'\n';
  for(auto&p:b) cout<<' '<<p;
  cout<<'\n';
  
  return 0;
}


void bake_rng(mt19937&rng){
  random_device rdv;
  int 	      	seeds[624];

  for(auto&x:seeds) x=rdv();
  seed_seq seq(seeds, seeds+624);
  rng.seed(seq);
}


void steepest_descent(Mat&A, Vec&b, Vec&x){
  int Dim(static_cast<int>(b.size()));
  const double epsilon(1e-7);
  double q[Dim], r[Dim];
  for(auto k{0}; k<Dim; ++k) r[k] = b[k];
  double delta(inner_product(r, r+Dim, r, 0.));
  
  for(auto i{0}; i<Dim && delta>epsilon; ++i){
    for(auto k{0}; k<Dim; ++k) q[k] = inner_product(&A[i][0], &A[i][0]+Dim, r, 0);
    double alpha = delta/inner_product(r, r+Dim, q, 0.);
    for(auto k{0}; k<Dim; ++k) x[k] += alpha*r[k];
    if((i+1)%50==0)
      for(auto k{0}; k<Dim; ++k)
	r[k] = b[k] - inner_product(&A[k][0], &A[k][0]+Dim, &x[0], 0);
    else
      for(auto k{0}; k<Dim; ++k) r[k] -= alpha*q[k];
    delta = inner_product(r, r+Dim, r, 0.);
    cout<<' '<<i<<' '<<delta;
  }
  cout<<endl;
}
