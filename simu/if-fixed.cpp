/**
 * input : genotype of 0, 1, or 2, with no spaces
 * output: 0 if fixed, 1 otherwise
 */
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);

  // get the genotypes of the 1st ID, and get nlc info, initiate frq
  string line;
  int    i, nid{1};
  getline(cin, line);
  
  int nlc(static_cast<int>(line.length()));
  int frq[nlc];

  for(i=0; i<nlc; ++i) frq[i] = line[i]-'0';

  // read the genotypes of the rest ID, calculate frq
  while(getline(cin, line)){
    for(i=0; i<nlc; ++i) frq[i] += line[i] - '0';
    ++nid;
  }

  for(auto&x:frq)
    if(x==nid*2) x=0;
    else         x=1;

  for(auto&p:frq) cout<<p<<'\n';
  return 0;
}
