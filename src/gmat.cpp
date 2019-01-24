// VanRaden Journal of Dairy Science Vol. 91 No. 11, 2008
void vr1g(istream&in, ostream&oo){
  // Read data
  // -- PART I
  int nid, nlc;
  in >> nid >> nlc;

  // -- PART II
  double twop[nlc], s2pq{0};
  {
    double mul(1./nid);
    for(auto&p:twop){
      in >> p;
      p *= mul;
      s2pq += p*(-.5*p + 1);	// if to use fma, trivial though
    }
  }

  // -- PART III
  double gt[nid][nlc];
  {
    string line;
    for(auto i{0}; i<nlc; ++i){
      in >> line;
      for(auto k{0}; k<nid; ++k) gt[k][i] = line[k] - '0' - twop[i];
    }
  }

  // Calculation
  oo<<nid<<'\n';
  for(auto i{0}; i<nid; ++i)
    for(auto j{0}; j<=i; ++j){
      double tvc[nlc];
      for(auto k{0}; k<nlc; ++k) tvc[k] = gt[i][k] * gt[j][k];
      double sum{0};
      for(auto&p:tvc) sum+=p;
      sum/=s2pq;
      oo.write((char*)&sum, sizeof(double));
    }
}


void vr2g(istream&in, ostream&oo){

}
