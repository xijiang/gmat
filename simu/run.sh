#!/usr/bin/env bash

make
. functions.sh

echo This script will simulate a pedigree of
echo -e "\t6 generations"
echo -e "\tNe of 120"
echo -e "\t10 chromosomes"
echo Output 3 files:
echo -e "\tsim.ped: ID pa ma snp-genotypes TBV"
echo -e "\tqtl.effects: QTL info"
echo -e "\tsim.ibv: inbreeding values of everybody"

# general parameters
nchr=5				# number of chromosomes
ne=120				# effective population size
ng=10000			# number of generations
chr=1				# chromosome length in Morgen
mr=1				# mutation rate /Morgan/meiosis

time simulate-an-ideal-population $ne $ng $chr $mr $nchr
echo Simulated an ideal population

nsib=10
ngrt=10
./simPed $ne $nsib $ngrt >sample.ped
cat sample.ped | ./obvped $ne >obsv.ped

time drop-ideal-to-sorted-pedigree $nchr $chr
echo  dropped the ideal genotypes into the sorted pedigree

nqtl=1000
time sample-qtl-n-generate-TBV $nqtl
echo sampled QTL and TBV

# prepare the files for future utilization
merge-n-clean
tar jcvf sim.tar.bz2 sim.ped qtl.effects sim.ibv
rm sim.ped qtl.effects sim.ibv
