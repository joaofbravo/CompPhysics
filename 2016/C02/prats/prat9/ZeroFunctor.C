#include "ZeroFunctor.h"
#include "TF1.h"
#include <cmath> // fabs
#include <iostream>
using std::cout;
using std::endl;

ZeroFunctor::ZeroFunctor(TF1* p) : f(new TF1(*p)) {
  cout << __PRETTY_FUNCTION__ << endl;
}

ZeroFunctor::~ZeroFunctor() {
  if (f) delete f;
  cout << __PRETTY_FUNCTION__ << endl;
}

double ZeroFunctor::Bisection(double xl, double xr, double eps, int NI) {
  double x0;
  double fxl = f->Eval(xl);
  double fxr = f->Eval(xr);

  if (fxl*fxr > 0.) return 999.;

  int n = 0;

  while(fabs(xr-xl) > eps && n < NI) {
    fxl = f->Eval(xl);
    fxr = f->Eval(xr);
    x0 = 0.5*(xl+xr);
    double fx0 = f->Eval(x0);
    
    n++;
    printf("[xl=%f, x%d=%f, xr=%f\titeration %d \n", xl, n, x0, xr, n);
  
    if (fxl*fx0 <0.)
      xr = x0;
    else if(fx0*fxr <0.)
      xl = x0;
    else
      return x0;
  }

  if (n == NI) return 999.;

  cout << __PRETTY_FUNCTION__ << endl;

  return x0;
}