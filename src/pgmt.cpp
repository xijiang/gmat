#include <iostream>
#include <thread>
#include <tuple>
#include "gmat.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  int tth{int(thread::hardware_concurrency())};
  int nth{2};
  if(argc==2){			// determine how many threads to run
    nth = stoi(argv[1]);
    if(nth>tth) nth=tth;
  }

  const nrow{1024};
  
  if(argc==2)   nid = std::atoi(argv[1]);
  else          nid = nth/4;  //use 1/4 of computer resources by default
  if(nid < 1)   nid = 1;
  if(nid > nth) nid = nth;
  nth = nid;

  std::cin>>nid>>nlc;
  fastvr1g(nid, nlc, nth);
  return 0;
}
