#include <iostream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false); // avoid significant overhead
  int    i, j, nid, w{6}, p{2}, nlc;
  double td;

  if(argc==2){
    p = stoi(argv[1]);
    w = 4+p;
  }
  
  cin>>nid>>nlc;
  cin.ignore();

  clog<<"Dimension/nID:    "<<nid<<'\n';
  clog<<"No. of loci used: "<<nlc<<'\n';

  cout.precision(p);
  cout<<fixed;
  for(i=0; i<nid; ++i){
    for(j=0; j<=i; ++j){
      cin.read((char*)&td, sizeof(double));
      cout<<setw(w)<<td;
    }
    cout<<'\n';
  }
  
  return 0;
}
