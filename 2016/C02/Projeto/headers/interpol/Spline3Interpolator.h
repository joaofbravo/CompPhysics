#ifndef __Spline3Interpolator__
#define __Spline3Interpolator__

#include "Interpolator.h"
#include "Vec.h"

class TF1;

class Spline3Interpolator : public Interpolator {
public:
	Spline3Interpolator(int =0, double* =nullptr, double* =nullptr, TF1* =nullptr);
	Spline3Interpolator(int, double*, double*, TF1&);
	Spline3Interpolator(const Spline3Interpolator&);

	~Spline3Interpolator();

	void SetDataPoints(int, double*, double*);
	const TF1& GetInterpolDerivative() const;
	const TF1& GetInterpolPrimitive() const;

	double Interpolate(double);
	double InterpolateDerivative(double) const;
	double InterpolatePrimitive(double) const; //===== Não funciona bem! Falta impor condições de fronteira.

	void Print(string FILE="DATA.txt") const; // print results

private:
	void SetCurvatureLines();
	Vec K; //2nd derivatives

	double dfInterpolator(double*, double*) const;
	TF1* dFInterpolator; //Derivative of interpolation function

	double pfInterpolator(double*, double*) const;
	TF1* pFInterpolator; //Primitive of interpolation function
};

#endif