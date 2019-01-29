#include <iostream>
#include <fstream>
/**
 * When a G matrix is calculated in parallel, 
 * this program is to merge the resulting G from each thread into one.
 * Elements from each G is weighted by their number of loci.
 */
using namespace std;

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false); // avoid significant overhead
  int      nf(argc-1), tlc{0}, nid, nlc;
  ifstream fin[nf];
  double   weight[nf], td;

  for(auto i=0; i<nf; ++i){	// Read headers
    fin[i].open(argv[i+1]);
    fin[i] >> nid >> nlc;
    weight[i] = nlc;
    tlc += nlc;
    fin[i].ignore();
  }
  
  for(auto&p:weight) p/=tlc;	// determine weights

  cout<<nid<<' '<<tlc<<'\n';	// output new header

  for(auto i=0; i<nid; ++i)
    for(auto j=0; j<=i; ++j){	// and the body
      double sum{0};
      for(auto k=0; k<nf; ++k){
	fin[k].read((char*)&td, sizeof(double));
	sum+=td*weight[k];
      }
      cout.write((char*)&sum, sizeof(double));
    }
  return 0;
}
