simulate-an-ideal-population(){
    ne=$1
    ng=$2
    len=$3
    mr=$4
    nchr=$5

    for ((ichr=1; ichr<=$nchr; ++ichr)); do
	./pgsnp $ne $ng $len $mr >$ichr.chr 2>/dev/null &
    done
    wait
}

drop-ideal-to-sorted-pedigree(){
    nchr=$1
    len=$2
    nged=$3
    
    files=""

    for ((ichr=1; ichr<=$nchr; ++ichr)); do
	files=$files" p$ichr.chr" # gether all the dropped chromosomes.
	cat $ichr.chr |
	    ./ndrop sample.ped $len >p$ichr.chr 
    done

    # below also clean fixed loci
    ./merge $files |
	./allele2g >raw.gt

    # presume the last $nged ID were genotyped, or can be observed
    tail -n $nged raw.gt |
	./if-fixed > fixed.txt

    cat raw.gt |
	./rm-fixed fixed.txt >sim.gt
}

sample-qtl-n-generate-TBV(){
    nqtl=$1
    
    ./splQTL $(head -2 sim.gt |tail -1) $nqtl >qtl.effects
    
    cat sim.gt |
	./grttbv qtl.effects >sim.tbv
}


merge-n-clean(){
    ./combine obsv.ped sim.gt sim.tbv >sim.ped
    cat obsv.ped |
	./amat f id.lst |
	gawk '{print $2}' >sim.ibv
    rm *.chr sample.ped obsv.ped sim.gt sim.tbv id.lst
    make clean
}
