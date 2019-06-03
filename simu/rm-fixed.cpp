#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);
  // get the genotypes of the 1st ID, and get nlc info, initiate frq
  string line;
  vector<string> gt;
  getline(cin, line);
  gt.push_back(line);
  
  int nlc(static_cast<int>(line.length()));
  int frq[nlc];

  for(auto i{0}; i<nlc; ++i) frq[i] = line[i]-'0';

  // read the genotypes of the rest ID, store them and calculate frq
  while(getline(cin, line)){
    gt.push_back(line);
    for(auto i{0}; i<nlc; ++i) frq[i] += line[i] - '0';
  }

  int nid(static_cast<int>(gt.size()));

  for(auto&x:frq) if(x==nid*2) x=0;

  // output them if not fixed
  for(auto&ig:gt){
    for(auto i{0}; i<nlc; ++i) if(frq[i]) cout<<' '<<ig[i];
    cout<<'\n';
  }
  return 0;
}
