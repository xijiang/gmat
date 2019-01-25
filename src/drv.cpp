#include <iostream>
#include "gmat.hpp"

/**
 * I am using my genotype format here, suppose SNP alleles are coded as 0 & 1
 * part   I: nid nlc                 # in one line
 * part  II: incidence of allele 1   # nlc lines 
 * part III: genotype of each locus  # nlc lines, each line is of nid characters
 *                                   #   of 0, 1, & 2, no space
 *
 * part III is independent for batch process, i.e., if there are to many loci
 * then G can bu accumulated (loci) block by block
 */

using namespace std;

void distribute(int&nth){
  nth=1;			// dummy, number of threads, do later
  size_t nid, nlc;		// sizeof(int) is only 4, size_t 8
  cin>>nid>>nlc;

  vector<double> twop(nlc), geno(nlc*nid);
  double         s2pq{0}, mul(1./nid);

  for(auto&p:twop){
    cin  >> p;
    p    *= mul;
    s2pq += p*(-.5*p + 1);
  }

  for(size_t i=0; i<nlc; ++i){
    string gt;
    cin >> gt;
    for(size_t j=0; j<nid; ++j) geno[nlc*j+i] = gt[j] - '0' - twop[i];
  }
  vr1g(twop, s2pq, geno, cout);
}

int main(int argc, char *argv[])
{
  ios_base::sync_with_stdio(false);
  
  int nth{2};

  distribute(nth);
  
  return 0;
}
