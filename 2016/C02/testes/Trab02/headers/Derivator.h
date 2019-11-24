#ifndef __Derivator__
#define __Derivator__

#include "Func1D.h"

class Derivator: public Func1D {

public:
	Derivator(TF1* fp =nullptr);
	Derivator(TF1& fp);
	~Derivator();

	// pedidas pelo prof
	double ForwardDifference(double) const;
	double BackwardDifference(double) const;
	double CentralDifference(double) const;
	double CentralFirstAcu4(double) const;
	double CentralSecondAcu2(double) const;
	double CentralSecondAcu4(double) const;

	// extra
	double CentralFirstAcu8(double) const;
	double CentralForthAcu2(double) const;

	//falta implementar, coeficientes aqui: https://en.wikipedia.org/wiki/Finite_difference_coefficient#Forward_and_backward_finite_difference 
	// double CentralThirdAcu2(double) const;
	// double CentralFifthAcu2(double) const;
	// double CentralSixthAcu2(double) const;
	
private:
	double generalderivator(double xval, double h,double order, int N, double* coef, double* hcoef, bool roundupminimizer =false) const;
};

#endif