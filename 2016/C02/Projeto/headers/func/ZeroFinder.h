#ifndef __ZeroFinder__
#define __ZeroFinder__

#include "Func1D.h"

class ZeroFinder : public Func1D {
public:
	ZeroFinder(TF1* =nullptr);
	ZeroFinder(TF1&);
	ZeroFinder(Func1D&);
	ZeroFinder(Func1D&&);
	~ZeroFinder();

	double Bisection (double xl, double xr, double eps, int Ni=1000) const;
	double Newton (double x0, double eps, int Ni=1000) const;
	double Secant (double x0, double x_1, double eps, int Ni=1000) const;
};

#endif