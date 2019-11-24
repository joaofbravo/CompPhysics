#include "NewtonInterpolator.h"
#include <iostream>

NewtonInterpolator::NewtonInterpolator(int fN, double *fx, double *fy, TF1* f0) : Interpolator(fN,fx,fy,f0), coeffs(false) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

NewtonInterpolator::NewtonInterpolator(int fN, double *fx, double *fy, TF1& f0) : Interpolator(fN,fx,fy,f0), coeffs(false)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

NewtonInterpolator::~NewtonInterpolator()
{
	if (a) delete a;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void NewtonInterpolator::SetDataPoints(int fN, double* fx, double* fy)
{
	Interpolator::SetDataPoints(fN,fx,fy);

	if(a) delete a;
	coeffs = false;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double NewtonInterpolator::Interpolate(double xval)
{
	// Newton algorithm

	if(!coeffs) {
		a = new double [N];

		for (int i = 0; i < N; ++i)
			a[i] = y[i]; // auxiliar coeffs vector

		// Coefficients:
		for (int k = 1; k < N; ++k){
			for (int i = k; i < N; ++i)
				a[i] = (a[i] - a[k-1]) / (x[i] - x[k-1]);
		}

		coeffs = true;
	}

	// Polynomial:
	// 1) init the last polynomial: P = a[n];
	// 2) loop on (k=1; k<n+1; k++)
	// P = a[n-k] + (x - X[n-k])*P

	double P = a[N-1];

	for (int k = 1; k < N; ++k)
		P = a[N-k-1] + (xval - x[N-k-1])*P;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return P;
}

void NewtonInterpolator::Print(string FILE) const
{
	cout << "----------Newton Interpolator----------" << endl;
	
	Interpolator::Print(FILE);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}