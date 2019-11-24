#ifndef __LagrangeInterpolator__
#define __LagrangeInterpolator__

#include "Interpolator.h"

class TF1;

class LagrangeInterpolator : public Interpolator {
public:
	LagrangeInterpolator(int =0, double* =nullptr, double* =nullptr, TF1* =nullptr);
	LagrangeInterpolator(int, double*, double*, TF1&);
	~LagrangeInterpolator();

	double Interpolate(double);

	void Print(string ="DATA.txt") const; // print results
};

#endif