#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char *argv[])
{
  int ne(stoi(argv[1])), pa, ma, id{1};
  ofstream foo("id.lst");
  
  for(auto i=0; i<ne; ++i) cin>>pa>>ma;
  while(cin>>pa>>ma){
    pa<ne?(pa=0):(pa-=ne);
    ma<ne?(ma=0):(ma-=ne);
    cout<<pa<<' '<<ma<<'\n';
    foo<<id++<<'\n';
  }
  return 0;
}
