#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
  size_t nid, nlc;              { cin>>nid>>nlc; }

  double twop[nlc], s2pq{0};{	// read frequencies
    double mul(1./nid);
    for(auto&p:twop){
      cin  >> p;
      p    *= mul;
      s2pq += p*(1-p*.5);
    }
    s2pq = 1./s2pq;
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
	for(k=0; k<nlc; ++k) td[k] = gt[i][k]*gt[j][k];
	for(auto&p:td) sum += p;
	sum *= s2pq;
	cout.write((char*)&sum, sizeof(double));
      }
  }
  return 0;
}
