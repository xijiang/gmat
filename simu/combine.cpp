#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[])
{
  if(argc!=4) return 1;
  
  ifstream ped(argv[1]), fgt(argv[2]), fbv(argv[3]);
  int      nid, nlc, pa, ma;
  string   gt;
  double   bv;
  
  fgt>>nid>>nlc;
  while(ped>>pa>>ma){
    fgt>>gt;
    fbv>>bv;
    cout<<pa<<' '<<ma<<' '<<gt<<' '<<bv<<'\n';
  }
  
  return 0;
}
