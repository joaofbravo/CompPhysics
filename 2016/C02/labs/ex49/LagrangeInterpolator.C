#include "LagrangeInterpolator.h"
#include <iostream>

LagrangeInterpolator::LagrangeInterpolator(int fN, double *fx, double *fy, TF1* f0) : Interpolator(fN,fx,fy,f0) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

LagrangeInterpolator::LagrangeInterpolator(int fN, double *fx, double *fy, TF1& f0) : Interpolator(fN,fx,fy,f0) 
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

LagrangeInterpolator::~LagrangeInterpolator()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double LagrangeInterpolator::Interpolate(double xval)
{
	// Lagrange algorithm
	// n = polynomial degree
	// n+1 = nb of data points
	// x,y = abcissa and values
	// loop on data points (0...n)
	// second loop for the product
	
	// li(x) = Produtório(x − xj)/(xi − xj) (i=0,1,2,...,n), i!=j
	// P(x) = sum li(x)*yi

	double Px = 0.;

	for (int i = 0; i < N; i++) 
	{
		double li = 1.;

		for (int j = 0; j < i; j++)
			li *= (xval - x[j])/(x[i] - x[j]);

		// salto i!=j
		for (int j = i+1; j < N; j++)
			li *= (xval - x[j])/(x[i] - x[j]);

		Px += li * y[i];			
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
	
	return Px;
}

void LagrangeInterpolator::Print(string FILE) const
{
	cout << "----------Lagrange Interpolator----------" << endl;
	
	Interpolator::Print(FILE);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}