#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc!=3){
    cerr<<"Usage: cat sample.g | "<<argv[0]<<" number-of-files stem\n\n";
    cerr<<"    splitted files will be named stem.1, stem.2 ... stem.nf\n";
    return 1;
  }
  
  int nf(stoi(argv[1])), ilc{0}, nid, nlc, stp{0};
  cin>>nid>>nlc;
  stp = nlc/nf;

  if(nf<2 || stp<10){		// minimum 2 files, minimum lines 10 per file
    cerr<<"Invalid number of files or too few lines in splitted files\n";
    return 2;
  }

  int frq[nlc];
  for(auto&p:frq) cin>>p;
  for(auto i=1; i<nf+1; ++i){
    ofstream foo(string(argv[2])+'.'+to_string(i));
    if(i!=nf){
      foo<<nid<<' '<<stp<<'\n';
      for(;ilc<stp*i; ++ilc) foo<<frq[ilc]<<'\n';
      for(auto j=0; j<stp; ++j){
	string line;
	cin>>line;
	foo<<line<<'\n';
      }
    }else{
      int rest(nlc-ilc);
      foo<<nid<<' '<<rest<<'\n';
      for(; ilc<nlc; ++ilc) foo<<frq[ilc]<<'\n';
      string line;
      while(cin>>line) foo<<line<<'\n';
    }
  }
      
  return 0;
}
