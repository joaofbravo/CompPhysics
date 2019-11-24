#include "ZeroFinder.h"
#include "TF1.h"
#include <iostream>

using namespace std;

ZeroFinder::ZeroFinder(const TF1* fp) : Func1D(fp) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ZeroFinder::ZeroFinder(const TF1& fp) : Func1D(fp) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ZeroFinder::ZeroFinder(const Func1D& f) : Func1D((Func1D&)f) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ZeroFinder::ZeroFinder(Func1D&& f) : Func1D((Func1D&&)f) {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

ZeroFinder::~ZeroFinder() {
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double ZeroFinder::Bisection (double xl, double xr, double eps, int Ni) const {

	if (xl > xr) {
		double c = xl;
		xl = xr;
		xr = c;
	}

	double fxl = F->Eval(xl);
	double fxr = F->Eval(xr);

	if (fxl*fxr > 0.) {
		cout << "Bisection: There is not only one zero in this interval. Returning 0." << endl;
		return 0.;
	}

	double x0, fx0;
	int n = 0;

	while(fabs(xr-xl) > eps && n < Ni) {
		fxl = F->Eval(xl);
		fxr = F->Eval(xr);
		
		x0 = 0.5*(xl+xr);
		fx0 = F->Eval(x0);

		n++;
		// cout << "xl=" << xl << ",  x" << n << "= " << x0 << ",  xr=" << xr << ",\titeration " << n << endl;

		if (fxl*fx0 <0.)
			xr = x0;
		else if(fx0*fxr <0.)
			xl = x0;
		else
			break;
	}

	if (n == Ni) {
		cout << "Bisection: No zero found in " << n << " iterations. Returning 0." << endl;
		return 0.;
	}

	cout << "Bisection: Zero found in " << n << " iterations." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return x0;
}

double ZeroFinder::Newton (double xn, double eps, int Ni) const {

	double xn1;
	int i;

	for(i = 0; i < Ni; i++)
	{  
		xn1 = xn - F->Eval(xn)/F->Derivative(xn,0,eps*1.e-5);

		// cout << "xn-1=" << xn << "  xn=" << xn1 << "  iteration " << i+1 << endl;

		if (fabs(xn1-xn) < eps)
			break;

		xn = xn1;
	}

	if (i == Ni) {
		cout << "Newton: No zero found in " << i << " iterations. Returning 0." << endl;
		return 0.;
	}

	i++;
	cout << "Newton: Zero found in " << i << " iterations." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return xn1;
}

double ZeroFinder::Secant (double x0, double x1, double eps, int Ni) const 
{

	double xn=x0, xn1, xn2=x1;
	int i;

	// if (F->Eval(x0)*F->Eval(x1) > 0.) {
	// 	cout << "Secant: There is not only one zero in this interval. Returning 0." << endl;
	// 	return 0.;
	// }

	for(i = 0; i < Ni; i++)
	{  
		xn1 = xn2;
		xn2 = xn1 - (F->Eval(xn1)*(xn1-xn))/(F->Eval(xn1)-F->Eval(xn));

		// cout << "x" << i-1 << "=" << xn << " x" << i << "= " << xn1 << "  x" << i+1 << "=" << xn2 << ", \titeration " << i+1 << endl;

		if (fabs(xn2-xn1) < eps)
			break;

		xn = xn1;
	}

	if (i == Ni) {
		cout << "Secant: No zero found in " << i << " iterations. Returning 0." << endl;
		return 0.;
	}

	i++;
	cout << "Secant: Zero found in " << i << " iterations." << endl;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return xn1;
}