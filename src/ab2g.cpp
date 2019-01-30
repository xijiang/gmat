#include <iostream>
#include <vector>
#include <map>
#include <sstream>

/**
 * Convert allele genotypes to my format
 * e.g.,
 *    id1 a b a b   # ID with genotype ab and ab -> 11
 *    id2 a a b b   # ID with genotype aa and bb -> 02
 * also make a transform to store genotype majored
 */
using namespace std;

int main(int argc, char *argv[])
{
  if(argc!=3){
    cerr<<"Usage: "<<argv[0]<<" first-allele second-allele";
    return 1;
  }
  ios_base::sync_with_stdio(false);
  map<char, int> allele{{argv[1][0], 0}, {argv[2][0], 1}};
  vector<string>ID;
  string        gt, id;
  while(cin>>id){
    ID.push_back(id);
    string line;
    getline(cin, line);
    stringstream ss(line);
    char a, b;
    while(ss>>a>>b) gt.push_back(char(allele[a]+allele[b]+'0'));
  }

  size_t nid(ID.size()), i, j, frq;
  size_t nlc(gt.length()/nid);
  cout<<nid<<' '<<nlc<<'\n';
  for(j=0; j<nlc; ++j){
    frq = 0;
    for(i=0; i<nid; ++i) frq+=gt[nlc*i+j];
    frq-='0'*nid;
    cout<<frq<<'\n';
  }
  for(j=0; j<nlc; ++j){
    for(i=0; i<nid; ++i) cout<<gt[nlc*i+j];
    cout<<'\n';
  }
  return 0;
}
