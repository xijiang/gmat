#!/usr/bin/env bash
if [ $# != 1 ]; then
    echo Usage: ./gmat.sh option
    echo options:
    echo -e "\t"prepare:   compile the source codes into binaries
    echo -e "\t"vr1g:      calculate G using VanRaden method I
    echo -e "\t"vrqg:      using frquency of 0.5
    echo -e "\t"nmg:       Method II?
    echo -e "\t"maf:       A test run with MAF 0.1
    echo -e "\t"parallel:  run in parallel, and them merge the results
else
    case "$1" in
	prepare)		# make the binaries
	    cd ../src/
	    make
	    make mv
	    cd -
	    ;;
	vr1g)			# calculate with VanRaden method I
	    cat sample.vcf |	# if vcf is compressed, use, e.g., zcat
		../bin/vcf2g |
		../bin/vr1g >vr1g.G
	    ../bin/viewg <vr1g.G |
		head
	    ;;
	vrqg)			# using allele frequency 0.5
	    cat sample.vcf |	# can also be
		../bin/vcf2g |
		../bin/vrqg >vrqg.G
	    ../bin/viewg <vrqg.G |
		head
	    ;;
	nmg)			# using VR method II
	    cat sample.vcf |
		../bin/vcf2g |
		../bin/nmg >nmg.G
	    ../bin/viewg <nmg.G |
		head
	    ;;
	maf)
	    cat sample.vcf |
		../bin/vcf2g  |
		../bin/mafflt .1 | # one can specify other maf in (0, .49]
		../bin/vr1g >maf.G
	    ../bin/viewg <maf.G |
		head
	    ;;
	parallel)
	    cat sample.vcf |	# test
		../bin/vcf2g |
		../bin/splitg 5 tmp
	    for i in {1..5}; do
		cat tmp.$i |
		    ../bin/vr1g > $i.G &
	    done
	    wait
	    ../bin/mrggmt {1..5}.G > parallel.G
	    ../bin/viewg <parallel.G |
		head
	    ;;
	*)
	    echo -e "\t" No such option
	    echo -e "\t" Try to run without an option to see available options
    esac
fi

