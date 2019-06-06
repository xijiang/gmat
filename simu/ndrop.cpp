#include <iostream>
#include <fstream>
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

void sample(int p, string&gt, int nlc, // sample genotypes from p and append to gt
	    poisson_distribution<int>&psd,
	    uniform_int_distribution<int>&rhp,
	    uniform_int_distribution<int>&pos,
	    mt19937 rng){
  size_t bg=static_cast<size_t>(p)*2*static_cast<size_t>(nlc);
  
  auto h1(gt.substr(bg    , nlc));
  auto h2(gt.substr(bg+nlc, nlc));
  
  auto h0(rhp(rng));
  auto nm(psd(rng));		// how many mutations
  if(!nm){
    h0?
      gt+=h2 :
      gt+=h1;
    return;
  }
  
  int  pp[nm];
  for(auto&x:pp) x=pos(rng);	// where are they
  sort(pp, pp+nm);		// put in order

  auto b{0};
  for(auto&x:pp){
    h0?
      gt+=h2.substr(b,x-b) :
      gt+=h1.substr(b,x-b);
    h0 = 1-h0;			// cross-over here
    b = x;
  }
  // the last segment
  h0?
    gt+=h2.substr(b,nlc-b) :
    gt+=h1.substr(b,nlc-b);
}


int main(int argc, char *argv[])
{
  if(argc!=3){
    cerr<<"Usage: cat ideal-chr | "<<argv[0]<<" extended.ped chr-len\n";
    return 1;
  }
  ios_base::sync_with_stdio(false); // avoid significant overhead
  ifstream fin(argv[1]);
  double   len(stof(argv[2]));
  mt19937  rng;
  bake_rng(rng);

  PED ped;			// read extended pedigree below
  for(int pa, ma; fin>>pa>>ma; ped.push_back({pa,ma}));

  int    ne, nlc;
  string gt;			// read ideal genotypes below

  cin>>ne>>nlc;
  for(auto i{0}; i<ne*2; ++i){ // ignore the frequency part
    string hap;			// to keep variables as few as possible
    cin>>hap;			// and I ignore the base pair positions here
    gt +=hap;
  }

  poisson_distribution<int>      psd(len);
  uniform_int_distribution<int>  rhp(0,1), pos(0, nlc-1);

  cout<<ped.size()-ne<<'\n'<<nlc<<'\n';
  for(auto i=ne; i<static_cast<int>(ped.size()); ++i){
    auto&[pa,ma] = ped[i];
    sample(pa-1, gt, nlc, psd, rhp, pos, rng);
    sample(ma-1, gt, nlc, psd, rhp, pos, rng);
    cout<<gt.substr(gt.length()-nlc*2, nlc)<<'\n';
    cout<<gt.substr(gt.length()-nlc,   nlc)<<'\n';
  }
  return 0;
}
