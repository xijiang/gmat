#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  double maf(stof(argv[1]));
  if(maf<=0 || maf>.49){
    cerr<<"Wrong MAF, which should be in (0, .49]\n";
    return 1;
  }

  int    nid, nlc, olc;
  cin>>nid>>nlc;
  olc = nlc;

  int    frq[nlc], min, max;
  
  min = nid*2*maf;
  max = nid*2-min;
  
  for(auto&p:frq){
    cin>>p;
    if(p<=min || p>=max){
      p=0;
      --olc;
    }
  }
  
  cout<<nid<<' '<<olc<<'\n';
  for(auto&p:frq) if(p) cout<<p<<'\n';
  for(auto&p:frq){
    string line;
    cin>>line;
    if(p) cout<<line<<'\n';
  }
  return 0;
}
