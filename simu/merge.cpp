#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc<3){
    cerr<<"Please specify at least 2 chromosome files at command line\n";
    return 1;
  }

  int      nchr(argc-1);
  ifstream fin[nchr];
  int      nid, nlc{0};
  for(auto i{1}; i<argc; ++i){
    fin[i-1].open(argv[i]);
    int ilc;
    fin[i-1]>>nid>>ilc;
    nlc+=ilc;
  }
  cout<<nid<<'\n'<<nlc<<'\n';
  
  for(string hap; fin[0]>>hap;){
    cout<<hap;
    for(auto i{1}; i<nchr; ++i){
      fin[i]>>hap;
      cout<<hap;
    }
    cout<<'\n';
  }
  
  return 0;
}
