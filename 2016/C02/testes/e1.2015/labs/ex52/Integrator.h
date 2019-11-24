#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"

class Integrator: public Func1D {
public:
	Integrator(double min =0, double  max=0, const TF1* =nullptr);
	Integrator(double, double, const TF1&);
	Integrator(double, double, const Func1D&);
	Integrator(double, double, Func1D&&);
	~Integrator();

	void SetLimits(double, double);

	void TrapezoidalRule(int, double&, double&) const;
	void SimpsonRule(int, double&, double&) const;
	
protected:
	double x0;
	double x1;
};

#endif