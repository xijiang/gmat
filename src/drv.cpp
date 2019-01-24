#include <iostream>
#include <cmath>

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

#include "gmat.cpp"

int main(int argc, char *argv[])
{
  vr1g(cin, cout);		// strictly follows the instructions
  
  return 0;
}
