#include <iostream>
#include <fstream>

/**
 * This will convert my G matrix into 3 columns
 * An ID file contains a column of ID names is needed for this conversion
 */
using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);
  int nid;                              cin>>nid;
  string ID[nid];
  {
    ifstream fin(argv[1]);
    for(auto i=0; i<nid; ++i) fin>>ID[i];
  }

  cin.ignore();
  double td;
  for(auto i=0; i<nid; ++i)
    for(auto j=0; j<=i; ++j){
      cin.read((char*)&td, sizeof(double));
      cout<<ID[i]<<'\t'<<ID[j]<<'\t'<<td<<'\n';
    }
  return 0;
}
