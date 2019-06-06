#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std;
using PED=vector<tuple<int, int>>;

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
    cerr<<argv[0]<<" ne nlc\n";
    return 1;
  }
  ios_base::sync_with_stdio(false); // avoid significant overhead
  mt19937  rng;
  bake_rng(rng);
  int    nid(stoi(argv[1])), nlc(stoi(argv[2]));
  double frq[nlc];
  uniform_real_distribution<double> ud(0, 1);
  for(auto&p:frq) p=ud(rng);

  cout<<nid<<'\n'<<nlc<<'\n';
  for(auto i{0}; i<nid; ++i){
    for(auto j{0}; j<nlc; ++j) (ud(rng)<frq[j])?(cout<<0):(cout<<1);
    cout<<'\n';
    for(auto j{0}; j<nlc; ++j) (ud(rng)<frq[j])?(cout<<0):(cout<<1);
    cout<<'\n';
  }    
  return 0;
}
