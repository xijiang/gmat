// VanRaden Journal of Dairy Science Vol. 91 No. 11, 2008
void vr1g(istream&in, ostream&oo){
  int    nid, nlc;		// PART I
  in>>nid>>nlc;			// dimensions

  double twop[nlc], erpq[nlc];	// PART II: 2p
  double inv(1./nid);		// =1/nid; and 'x' is faster than '/'
  for(auto i=0; i<nlc; ++i){
    double td;
    in >> td;
    td *= inv;			// = 2p
    twop[i] = td;
    erpq[i] = sqrt(1./(td*(1-td*.5)));
  }

  double gt[nid][nlc];		// ease for SIMP to put gt of one ID adjacently
  for(int ilc{0}; ilc<nlc; ++ilc){
    string line;
    in>>line;
    for(int i{0}; i<nid; ++i)
      gt[i][ilc]  = (line[i] - '0' - twop[ilc]) * erpq[ilc];
  }
  
  oo<<nid<<'\n';		// to matrix of my format
  for(auto iid{0}; iid<nid; ++iid)
    for(auto jid{0}; jid<=iid; ++jid){
      double td[nlc];		// for SIMD
      for(auto ilc{0}; ilc<nlc; ++ilc)
	td[ilc] = gt[iid][ilc]*gt[jid][ilc];
      double sum = accumulate(td, td+nlc, 0);
      oo.write((char*)&sum, sizeof(sum));
    }
}

void stupid(istream &in, ostream&oo){
  int nid, nlc;
  in >> nid >> nlc;

  double twop[nlc], erpq[nlc];
  for(auto i=0; i<nlc; ++i){
    double td;
    in >> td;
    td /= nid;
    twop[i] = td;
    erpq[i] = 
