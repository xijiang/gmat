CXXFLAGS = -O2 -Wall -ffast-math -std=c++17

target=nmg viewg vr1g vrqg mafflt splitg pvr1g g2-3c vcf2g mrggmt

all:    ${target}

vr1g:	vr1g.cpp gtp.hpp
nmg:	nmg.cpp gtp.hpp
vrqg:	vrqg.cpp gtp.hpp
bigg:
	g++ $(CXXFLAGS) -pthread -o bigg bigg.cpp

mv:
	mkdir -p ../bin
	mv ${target} ../bin
