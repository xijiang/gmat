#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false); // avoid significant overhead
  int    nid, nlc, tlc{0};
  cin>>nid>>nlc;
  
  string a, b, t(nlc, 'x');
  vector<string> g;
  int    q[nlc]{0};
  
  for(auto i{0}; i<nid; ++i){
    cin>>a>>b;
    for(auto j{0}; j<nlc; ++j){
      t[j] = a[j]-'0'+b[j];
      q[j]+= t[j]-'0';
    }
    g.push_back(t);
  }

  for(auto&x:q){
    if(x==2*nid) x=0;
    if(x) ++tlc;
  }

  cout<<nid<<'\n'<<tlc<<'\n';
  
  for(auto&x:g){
    for(auto i{0}; i<nlc; ++i) if(q[i]) cout<<x[i];
    cout<<'\n';
  }
  return 0;
}
