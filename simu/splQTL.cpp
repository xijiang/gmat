#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

void bake_rng(mt19937&rng){
  random_device rdv;
  int           seeds[624];

  for(auto&x:seeds) x=rdv();
  seed_seq seq(seeds, seeds+624);
  rng.seed(seq);
}


int main(int argc, char *argv[])
{
  if(argc!=3){
    cerr<<"Usage: "<<argv[0]<<" nlc nqtl\n";
    return 1;
  }

  mt19937 rng;
  bake_rng(rng);

  int nlc(stoi(argv[1]));
  int nqt(stoi(argv[2]));
  int qtl[nlc];
  
  for(auto i=0; i<nlc; ++i) qtl[i] = i;
  shuffle(qtl, qtl+nlc, rng);
  sort(qtl, qtl+nqt);
  
  normal_distribution<double> gauss(0, 1);
  for(auto i=0; i<nqt; ++i) cout<<qtl[i]<<'\t'<<gauss(rng)-gauss(rng)<<'\n';
  
  return 0;
}
