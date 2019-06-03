#include <iostream>
#include <random>
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;
using VTII=vector<tuple<int, int>>;

void bake_rng(mt19937&rng){
  random_device rdv;
  int           seeds[624];

  for(auto&x:seeds) x=rdv();
  seed_seq seq(seeds, seeds+624);
  rng.seed(seq);
}


void samplePrt(VTII&ped, int start, int end, int nprt, int nsib, mt19937&rng){
  int nid(end-start+1);
  int prt[nid];

  if(nid<nprt) throw runtime_error("not enough ID to sample parents");
  nprt/=2;
  
  for(auto&p:prt) p=start++;
  shuffle(prt, prt+nid, rng);

  start=0; end=nid-1;
  for(auto i=0; i<nprt; ++i, ++start, --end)
    for(auto j=0; j<nsib; ++j) ped.push_back({prt[start], prt[end]});
}


int main(int argc, char *argv[])
{
  if(argc!=4){
    cerr<<"Usage: "<<argv[0]<<" N-parents N-sibs n-generations\n";
    return 1;
  }
  int nprt(atoi(argv[1])), nsib(atoi(argv[2])), ngrt(atoi(argv[3]));
  
  mt19937 rng;
  bake_rng(rng);

  VTII ped;
  nprt -= nprt%2;		// I only consider n-pa == n-ma
  for(auto i=0; i<nprt; ++i) ped.push_back({0, 0});
  int start{1}, end{nprt};
  samplePrt(ped, start, end, nprt, nsib, rng); // generation 0
  for(auto i=1; i<ngrt; ++i){
    start=end+1;
    end+=nprt*nsib/2;
    samplePrt(ped, start, end, nprt, nsib, rng);
  }
  sort(ped.begin(), ped.end());
  for(auto&[pa, ma]:ped) cout<<pa<<' '<<ma<<'\n';

  return 0;
}
