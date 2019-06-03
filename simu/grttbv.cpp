#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

// note, index starts from 0

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false); // avoid significant overhead
  
  if(argc!=2){
    cerr<<"Usage: cat genotype-file | "<<argv[0]<<" qtl-effects\n";
    return 1;
  }

  vector<tuple<int, double>> qtl;{
    ifstream fin(argv[1]);
    int      pos;
    double   eff;
    while(fin>>pos>>eff) qtl.push_back({pos, eff});
  }

  int nid, nlc;
  cin>>nid>>nlc;
  for(string hap; cin>>hap;){
    double tbv{0};
    for(auto&[pos, eff]:qtl) tbv+=(hap[pos]-'0')*eff;
    cout<<tbv<<'\n';
  }
  
  return 0;
}
