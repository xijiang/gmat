/**
 * this small struct is to avoid the frame limitation problem.
 * when nlc x nid is large, 
 * a declarition like gt[nid][nlc] usually leads to a segmentation error
 */

#ifndef _gtp_struct
#define _gtp_struct

class GTP{
public:
  GTP(int _nid, int _nlc):nid(_nid), nlc(_nlc){
    g = new double*[nid];
    for(auto i=0; i<nid; ++i) g[i] = new double[nlc];
  }
  int nid, nlc;
  double**g;
  ~GTP(){
    for(auto i=0; i<nid; ++i) delete[] g[i];
    delete[] g;
  }
};
#endif
