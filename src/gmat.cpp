#include "gmat.hpp"

// VanRaden Journal of Dairy Science Vol. 91 No. 11, 2008
void vr1g(std::vector<double>&twop,
	  double&s2pq,
	  std::vector<double>&gt,
	  std::ostream&oo){
  auto nlc(twop.size());
  auto nid(gt.size()/nlc);

  oo<<nid<<'\n';
  size_t i, j, k;
  for(i=0; i<nid; ++i){
    double*id = &gt[i*nlc];
    for(j=0; j<=i; ++j){
      double td[nlc];
      double*jd = &gt[j*nlc];
      for(k=0; k<nlc; ++k) td[k] = id[k]*jd[k];
      double sum{0};
      for(auto&p:td) sum+=p;
      sum/=s2pq;
      oo.write((char*)&sum, sizeof(double));
    }
  }
}


void seg_vr1g(){
}


void yang(std::vector<double>&twop,
	  double&s2pq,
	  std::vector<double>&gt,
	  std::ostream&oo){
  auto nlc(twop.size());
  auto nid(gt.size()/nlc);

  oo<<nid<<'\n';
  size_t i, j, k;
  double td[nlc], sum;
  for(i=0; i<nid; ++i){
    double*id = &gt[i*nlc];
    for(j=0; j<i; ++j){
      double*jd = &gt[j*nlc];
      for(k=0; k<nlc; ++k) td[k] = id[k]*jd[k];
      sum = 0;    for(auto&p:td) sum+=p;
      sum/=s2pq;
      oo.write((char*)&sum, sizeof(double));
    }
    sum = 0;
    for(k=0; k<nlc; ++k){
      double tp(twop[k]);
      double xr(id[k]+tp);
      sum += xr*xr - (1+tp)*xr + tp*tp*.5;
    }
    sum/=s2pq;
    ++sum;
    oo.write((char*)&sum, sizeof(double));
  }
}
