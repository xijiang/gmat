# G matrix constructors

This contains various G matrix constructors.

## Usage:
```bash
git clone https://github.com/xijiang/gmat
cd gmat/fnc
./gmat.sh prepare                    # for first time usage
./gmat.sh vr1g                       # VanRaden method 1
./gmat.sh                            # to show all available options
```

## Working format
### Genotype file
Suppose the genotypes are coded as 0, 1, 2 for genoteype 00, 01 and 11,
then the frequencies in the file are the counts of allele '1' for all the
individuals on each locus. 

  * nid nlc       # put in one line for clarity
  * frequencies   # number of loci lines
  * genotypes     # number of loci lines

For example:

    5 2
    4
    6
    01201
    12012

### G matrix format
    nid nlc    # nID and nLoci used for this G, follows a (Unix) new line char
    binaries of the lower triangular of G  # n(n+1)/2 doubles, each of 8 bytes

A function, _g2-3c_, is added to convert this into a 3-column format,
provides ID names in a separate file.

### VCF format
My program don't deal with missing alleles.
The missings can be imputed with Beagle 5, which results in VCF files.
A function, _vcf2g_, is included to convert it to the working format.

## Realization of parallel calculation
This is realized in two stages:
  1. G calculator stores the genotypes locus-majored for SIMD
  2. Using bash to parallelization, which is
     * Cheaper
     * Easier to understand

A function, *splitg*, is added to split jobs.
Also see the bash scripts to see how to use them.

## Note:

In the driver, *nid* and *nlc* must be defined as size_t or long.
An int is of size 4 bytes or maximally 2,147,483,648.
current *nid* x *nlc* can easily be bigger than that.

All the programs were written in the "stupid" way for easier later modification.

## ToDo:
  * todo: to address the frame limit issue
