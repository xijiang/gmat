#!/usr/bin/env bash
g++   -O2 -Wall -std=c++17             -o split    split.cpp
icpc -mkl -Wall -std=c++11             -o zzprime  zzprime.cpp
g++   -O2 -Wall -std=c++17             -o mrgblk   mrgblk.cpp 
icpc -mkl -Wall -std=c++11 -DMKL_ILP64 -o inverseG inverseG.cpp 

# provide your genotype file name at the command line
cat $1 | ./split

nfile=`ls *.gt | wc -l`
thread=1
for ((i=1; i<=$nfile; ++i)); do
    ./zzprime $i.gt > $i-$i.G &
    let thread=thread+1
    for ((j=1; j<$i; ++j)); do
	./zzprime $i.gt $j.gt >$i-$j.G &
	let thread=thread+1
	if [ $thread -gt 9 ]; then
	    wait
	    thread=0
	fi
    done
done
wait

time ./mrgblk 63721 1000 |
    ./inverseG 100 >G.inv
