#ifndef __NevilleInterpolator__
#define __NevilleInterpolator__

#include "Interpolator.h"

class TF1;

class NevilleInterpolator : public Interpolator {
public:
	NevilleInterpolator(int =0, double* =nullptr, double* =nullptr, TF1* =nullptr);
	NevilleInterpolator(int, double*, double*, TF1&);
	~NevilleInterpolator();

	double Interpolate(double);

	void Print(string ="DATA.txt") const; // print results
};

#endif