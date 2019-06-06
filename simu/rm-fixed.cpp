#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc!=2){
    cerr<<"ERR: Specify if loci are fixed\n";
    return 1;
  }
  ios_base::sync_with_stdio(false);
  vector<bool> oo;
  ifstream foo(argv[1]);
  for(bool x; foo>>x; oo.push_back(x));
  
  // get the genotypes of the 1st ID, and get nlc info, initiate frq
  for(string line; cin>>line;){
    int i{0};
    for(auto&x:oo) if(x)cout<<line[i];
    cout<<'\n';
  }
  return 0;
}
