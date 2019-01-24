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

int main(int argc, char *argv[])
{
  vector<double> twop, gt;
  double         s2pq;

  __read_gt(cin, twop, s2pq, gt);

  vr1g(twop, s2pq, gt, cout);
  //yang(twop, s2pq, gt, cout);
  
  return 0;
}
