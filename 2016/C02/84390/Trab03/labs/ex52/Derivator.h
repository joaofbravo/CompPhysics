#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"

class Derivator: public Func1D {
public:
	Derivator(const TF1* =nullptr);
	Derivator(const TF1&);
	Derivator(const Func1D&);
	Derivator(Func1D&&);
	~Derivator();

	// derivatives
	double ForwardDifference(double) const;
	double BackwardDifference(double) const;
	double CentralDifference(double) const;
	double CentralFirstAcu4(double) const;
	double CentralFirstAcu8(double) const;

	double CentralSecondAcu2(double) const;
	double CentralSecondAcu4(double) const;

	double CentralForthAcu2(double) const;

	// coeffs: https://en.wikipedia.org/wiki/Finite_difference_coefficient#Forward_and_backward_finite_difference 
	
private:
	double generalderivator(double xval, double h, double order, int N, double* coef, double* hcoef, bool roundupminimizer =false) const;
};

#endif