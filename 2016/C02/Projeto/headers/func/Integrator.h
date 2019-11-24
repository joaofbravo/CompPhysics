#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"

class Integrator: public Func1D {
public:
	Integrator(double =0, double =0, TF1* =nullptr);
	Integrator(double, double, TF1&);
	Integrator(double, double, Func1D&);
	Integrator(double, double, Func1D&&);
	~Integrator();

	void SetLimits(double x0, double x1);
	void SetMin(double x0);
	void SetMax(double x1);

	void TrapezoidalRule(int, double&, double&) const;
	void SimpsonRule(int, double&, double&) const;

	double SimpsonAdaptative(double epsilon, int maxRecursionDepth = 50) const;
	
protected:
	double x0;
	double x1;
};

#endif