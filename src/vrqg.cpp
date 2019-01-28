#include <iostream>
/**
 * using p=0.5
 */
using namespace std;

int main(int argc, char *argv[])
{
  size_t nid, nlc;              { cin>>nid>>nlc; }

  {				// ignore p-values here
    double dum;
    for(size_t i=0; i<nlc; ++i) cin>>dum;
  }
  
  double gt[nid][nlc];{		// read genotypes
    string line;
    size_t i, k;
    for(k=0; k<nlc; ++k){
      cin>>line;
      for(i=0; i<nid; ++i) gt[i][k] = line[i] - '1';
    }
  }

  {				// calculate G
    size_t i, j, k;
    double s2pq(2./nlc);

    cout<<nid<<'\n';
    for(i=0; i<nid; ++i)
      for(j=0; j<=i; ++j){
	double sum{0}, td[nlc];
	for(k=0; k<nlc; ++k) td[k] = gt[i][k]*gt[j][k];
	for(auto&p:td) sum += p;
	sum *= s2pq;
	cout.write((char*)&sum, sizeof(double));
      }
  }
  return 0;
}
