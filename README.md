# G matrix constructor

This contains various G matrix constructors.

## Working format
### Genotype file
Suppose the genotypes are coded as 0, 1, 2 for genoteype 00, 01 and 11,
then the frequencies in the file are the counts of allele `1' for all the
individuals on each locus. 

  * nid nlc       # put in one line for clarity
  * frequencies   # number of loci lines
  * genotypes     # number of loci lines

Example:

    5 2
    4
    6
    01201
    12012

### G matrix format
    nid                    # a number with a (Unix) new line character
    binaries of the lower triangular of G  # $\frac{n(n+1)}{2}\times 8$ bytes

## Note:

In the driver, nid and nlc must be defined as size_t or long.
An int is of size 4 bytes or maximally 2,147,483,648.
current nid*nlc can easily be bigger than that.

## ToDo:
todo: vcf spliter
todo: parallel with bash code
