CXXFLAGS = -O2 -Wall -std=c++17
THREAD = ${CXXFLAGS} -pthread

target=drv

all:    ${target}

drv:	drv.cpp gmat.cpp
	g++ ${CXXFLAGS} -o drv drv.cpp

mv:
	mkdir -p ../bin
	mv ${target} ../bin
