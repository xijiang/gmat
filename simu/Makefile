CXX = g++
CXXFLAGS = -O2 -Wall -std=c++17
THREAD = ${CXXFLAGS} -pthread

target=ngsnp ndrop merge grttbv splQTL allele2g amat combine obvped simPed if-fixed rm-fixed

all:    ${target}

.phony: clean

clean:
	rm -f ${target}
