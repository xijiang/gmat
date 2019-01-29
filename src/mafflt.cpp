#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  int    nid, nlc;
  double maf(stoi(argv[1]));
  int    frq[nlc], min, max;

  if(maf<=0 || maf>.49){
    cerr<<"Wrong MAF, which should be in (0, .5)\n";
    return 1;
  }
  
  cin>>nid>>nlc;
  min = nid*2*maf;
  max = nid*2-min;
  return 0;
}
