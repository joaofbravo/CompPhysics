#ifndef __Integrator__
#define __Integrator__

#include "Func1D.h"

class Integrator: public Func1D {

public:
	Integrator(double fx0 =0, double fx1 =0, TF1* fp =nullptr);
	Integrator(double fx0, double fx1, TF1& fp);
	~Integrator();

	void SetLimits(double fx0, double fx1);

	void TrapezoidalRule(int n, double& Integral, double& Error) const;
	void SimpsonRule(int n, double& Integral, double& Error) const;
	
protected:
	double x0;
	double x1;
};

#endif