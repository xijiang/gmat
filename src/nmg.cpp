#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  size_t nid, nlc;              { cin>>nid>>nlc; }

  double twop[nlc], topq[nlc];{	// read frequencies
    double mul(1./nid);
    size_t i;
    for(i = 0; i<nlc; ++i){
      cin>>twop[i];
      twop[i] *= mul;
      topq[i]  = 1. / (twop[i]*(1-twop[i]*.5));
    }
  }

  double gt[nid][nlc];{		// read genotypes
    string line;
    size_t i, k;
    for(k=0; k<nlc; ++k){
      cin>>line;
      for(i=0; i<nid; ++i) gt[i][k] = line[i] - '0' - twop[k];
    }
  }

  {				// calculate G
    size_t i, j, k;

    cout<<nid<<'\n';
    for(i=0; i<nid; ++i)
      for(j=0; j<=i; ++j){
	double sum{0}, td[nlc];
	for(k=0; k<nlc; ++k) td[k] = gt[i][k]*gt[j][k]*topq[k];
	for(auto&p:td) sum += p;
	sum/=nlc;
	cout.write((char*)&sum, sizeof(double));
      }
  }
  return 0;
}
