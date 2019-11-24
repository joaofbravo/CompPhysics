#include "NevilleInterpolator.h"
#include <iostream>

NevilleInterpolator::NevilleInterpolator(int fN, double *fx, double *fy, TF1* f0) : Interpolator(fN,fx,fy,f0) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

NevilleInterpolator::NevilleInterpolator(int fN, double *fx, double *fy, TF1& f0) : Interpolator(fN,fx,fy,f0) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

NevilleInterpolator::~NevilleInterpolator()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double NevilleInterpolator::Interpolate(double xval)
{
	// Neville algorithm
	// 1) only one array (1-dim) y[] containing the 0th order polynomials
	// 2) loop on the order of the polynomials: (i=1, i<n+1, ++i)
	// 3) loop on every column to compute the different polynomials
	// y[] array will be rewritten with new values
	// 4) the interpolant calculated at the coordinate xval, corresponds to the last value

	double yp[N];
	
	for (int i = 0; i < N; i++) {
		yp[i] = y[i]; // auxiliar vector
	}

	// use extreme x-values and loop from end to beginning
	for (int k = 1; k < N; k++){
		for (int i = 0; i < N-k; i++)
			yp[i] = ((xval-x[i+k])*yp[i] - (xval-x[i])*yp[i+1]) / (x[i] - x[i+k]);
	}

	double A = yp[0];

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return A;
}

void NevilleInterpolator::Print(string FILE) const
{
	cout << "----------Neville Interpolator----------" << endl;

	Interpolator::Print(FILE);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}