#ifndef __NewtonInterpolator__
#define __NewtonInterpolator__

#include "Interpolator.h"

class TF1;

class NewtonInterpolator : public Interpolator {
public:
	NewtonInterpolator(int =0, double* =nullptr, double* =nullptr, TF1* =nullptr);
	NewtonInterpolator(int, double*, double*, TF1&);
	~NewtonInterpolator();

	void SetDataPoints(int, double*, double*);

	double Interpolate(double);

	void Print(string ="DATA.txt") const; // print results

private:
	bool coeffs;
	double* a; // coeffs array
};

#endif