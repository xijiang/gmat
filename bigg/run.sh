#!/usr/bin/env bash
g++ -O2 -Wall -std=c++17 -o split split.cpp
icpc -mkl -std=c++11 -o zzprime zzprime.cpp

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
	if [ $thread > 9 ]; then
	    wait
	    thread=0
	fi
    done
done
wait
