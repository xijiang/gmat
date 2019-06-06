#!/usr/bin/env bash
make

ne=120
nlc=5000

./ngsnp $ne $nlc >base.gt

nsib=10
ngrt=10
nged=2400			# number of genotyped ID
./simPed $ne $nsib $ngrt >sample.ped
cat sample.ped |
    ./obvped $ne >obsv.ped

cat base.gt |
    ./ndrop sample.ped 3 |
    ./allele2g >raw.gt

tail -n $nged raw.gt |
    ./if-fixed >fixed.txt

cat raw.gt |
    ./rm-fixed fixed.txt >sim.gt

nqtl=1000
./splQTL $(head -2 sim.gt |tail -1) $nqtl >qtl.effects

cat sim.gt |
    ./grttbv qtl.effects >sim.tbv

./combine obsv.ped sim.gt sim.tbv >sim.ped

cat obsv.ped |
    ./amat f id.lst |
    gawk '{print $2}' >sim.ibv

make clean
tar jcvf sim.tar.bz2 sim.ped qtl.effects sim.ibv
rm sample.ped obsv.ped raw.gt fixed.txt sim.gt qtl.effects sim.tbv id.lst sim.ibv base.gt sim.ped
