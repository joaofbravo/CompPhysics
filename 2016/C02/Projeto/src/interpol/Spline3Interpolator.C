#include "Spline3Interpolator.h"
#include "FCmatrixBanded.h"
#include "EqSolver.h"
#include "TF1.h"
#include "TGraph.h"
#include <iostream>

#include "cFCgraphics.h"


Spline3Interpolator::Spline3Interpolator(int fN, double *fx, double *fy, TF1* f0) : Interpolator(fN,fx,fy,f0)
{
	if (N > 1) {
		SetCurvatureLines();

		string Dname("DerivativeFInterpolator");
		string Pname("PrimitiveFInterpolator");
		
		Dname += std::to_string(funccounter);
		Pname += std::to_string(funccounter);

		dFInterpolator = new TF1(Dname.c_str(), this, &Spline3Interpolator::dfInterpolator, fx[0], fx[fN-1], 0);
		pFInterpolator = new TF1(Pname.c_str(), this, &Spline3Interpolator::pfInterpolator, fx[0], fx[fN-1], 0);
	}
	else {  
		dFInterpolator = nullptr;
		pFInterpolator = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Spline3Interpolator::Spline3Interpolator(int fN, double *fx, double *fy, TF1& f0) : Interpolator(fN,fx,fy,f0)
{
	if (N > 1) {
		SetCurvatureLines();

		string Dname("DerivativeFInterpolator");
		string Pname("PrimitiveFInterpolator");
		
		Dname += std::to_string(funccounter);
		Pname += std::to_string(funccounter);

		dFInterpolator = new TF1(Dname.c_str(), this, &Spline3Interpolator::dfInterpolator, fx[0], fx[fN-1], 0);
		pFInterpolator = new TF1(Pname.c_str(), this, &Spline3Interpolator::pfInterpolator, fx[0], fx[fN-1], 0);
	}
	else {
		dFInterpolator = nullptr;
		pFInterpolator = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Spline3Interpolator::Spline3Interpolator(const Spline3Interpolator& original) : Interpolator((Spline3Interpolator&)original)
{
	if (N > 1) {
		SetCurvatureLines();

		string Dname("DerivativeFInterpolator");
		string Pname("PrimitiveFInterpolator");
		
		Dname += std::to_string(funccounter);
		Pname += std::to_string(funccounter);

		dFInterpolator = new TF1(Dname.c_str(), this, &Spline3Interpolator::dfInterpolator, x[0], x[N-1], 0);
		pFInterpolator = new TF1(Pname.c_str(), this, &Spline3Interpolator::pfInterpolator, x[0], x[N-1], 0);
	}
	else {
		dFInterpolator = nullptr;
		pFInterpolator = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Spline3Interpolator::~Spline3Interpolator() {
	if (dFInterpolator) delete dFInterpolator;
	if (pFInterpolator) delete pFInterpolator;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Spline3Interpolator::SetDataPoints(int fN, double* fx, double* fy)
{
	Interpolator::SetDataPoints(fN,fx,fy);
	
	if (N > 1) {
		if (dFInterpolator) delete dFInterpolator;
		if (pFInterpolator) delete pFInterpolator;

		SetCurvatureLines();

		string Dname("DerivativeFInterpolator");
		string Pname("PrimitiveFInterpolator");
		
		Dname += std::to_string(funccounter);
		Pname += std::to_string(funccounter);

		dFInterpolator = new TF1(Dname.c_str(), this, &Spline3Interpolator::dfInterpolator, fx[0], fx[fN-1], 0);
		pFInterpolator = new TF1(Pname.c_str(), this, &Spline3Interpolator::pfInterpolator, fx[0], fx[fN-1], 0);
	}
	else if (N == 1){
		if (dFInterpolator) delete dFInterpolator;
		if (pFInterpolator) delete pFInterpolator;

		dFInterpolator = nullptr;
		pFInterpolator = nullptr;
	}

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

const TF1& Spline3Interpolator::GetInterpolDerivative() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *dFInterpolator;
}

const TF1& Spline3Interpolator::GetInterpolPrimitive() const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return *pFInterpolator;
}

double Spline3Interpolator::Interpolate(double xval)
{
	if(!x || !y)
	{
		cout << __PRETTY_FUNCTION__ << ": ERROR! Did not set point vectors." << endl;
		exit (1);
	}

	int n;

	// detect which segment x is in
	for (n = 0; n < N; n++)
		if ((xval-x[n]) < 0.) break; // upper bound returned
	
	if (n == 0) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[0];
	}

	if (xval > x[N-1]) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[N-1];
	}

	n -= 1;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return K[n]/6 * ((xval-x[n+1])*(xval-x[n+1])*(xval-x[n+1])/(x[n]-x[n+1]) - (xval-x[n+1])*(x[n]-x[n+1])) - K[n+1]/6 * ((xval-x[n])*(xval-x[n])*(xval-x[n])/(x[n]-x[n+1]) - (xval-x[n])*(x[n]-x[n+1])) + (y[n]*(xval-x[n+1]) - y[n+1]*(xval-x[n]))/(x[n]-x[n+1]);
}

double Spline3Interpolator::InterpolateDerivative(double xval) const
{
	if(!x || !y)
	{
		cout << __PRETTY_FUNCTION__ << ": ERROR! Did not set point vectors." << endl;
		exit (1);
	}

	int n;

	for (n = 0; n < N; n++) 
		if ((xval-x[n]) < 0.) break; //upper bound returned
	
	if (n == 0) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[0];
	}

	if (xval > x[N-1]) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[N-1];
	}

	n -= 1;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return K[n]/2 * ((xval-x[n+1])*(xval-x[n+1])/(x[n]-x[n+1]) - (x[n]-x[n+1])/3) - K[n+1]/2 * ((xval-x[n])*(xval-x[n])/(x[n]-x[n+1]) - (x[n]-x[n+1])/3) + (y[n]-y[n+1])/(x[n]-x[n+1]);
}

double Spline3Interpolator::InterpolatePrimitive(double xval) const
{
	if(!x || !y)
	{
		cout << __PRETTY_FUNCTION__ << ": ERROR! Did not set point vectors." << endl;
		exit (1);
	}

	int n;

	// detect which segment x is in
	for (n = 0; n < N; n++)
		if ((xval-x[n]) < 0.) break; // upper bound returned
	
	if (n == 0) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[0];
	}

	if (xval > x[N-1]) // out of range
	{
		cout << __PRETTY_FUNCTION__ << ": Atention! Point out of range."<< endl;
		return y[N-1];
	}

	n -= 1;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return x[0] + K[n]/12.* ((xval-x[n+1])*(xval-x[n+1])*(xval-x[n+1])*(xval-x[n+1])/(2*(x[n]-x[n+1])) - (xval-x[n+1])*(xval-x[n+1])*(x[n]-x[n+1])) - K[n+1]/12. * ((xval-x[n])*(xval-x[n])*(xval-x[n])*(xval-x[n])/(2*(x[n]-x[n+1])) - (xval-x[n])*(xval-x[n])*(x[n]-x[n+1])) + (y[n]*(xval-x[n+1])*(xval-x[n+1]) - y[n+1]*(xval-x[n])*(xval-x[n]))/(2*(x[n]-x[n+1]));
}

void Spline3Interpolator::Print(string FILE) const {
	cout << "----------Spline3 Interpolator----------" << endl;
	
	Interpolator::Print(FILE);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Spline3Interpolator::SetCurvatureLines()
{
	// define tri-diagonal matrix and array of constants
	vector<Vec> triVec;
	Vec Din(N);
	Vec Dout(N-1);
	Vec b(N);

	// pontas: f''=0
	Din[0] = 1.;
	Din[N-1] = 1.;

	Dout[0] = 0.;
	Dout[N-2] = 0.;

	b[0] = 0.;
	b[N-1] = 0.;

	//preencher sistema
	int i;
	for (i = 1; i < N-2; ++i)
	{
		Din[i] = 2*(x[i-1] - x[i+1]);
		Dout[i] = (x[i] - x[i+1]);
		b[i] = 6*((y[i-1]-y[i]) / (x[i-1]-x[i]) - (y[i]-y[i+1]) / (x[i]-x[i+1]));
	}

	Din[i] = 2*(x[i-1] - x[i+1]);
	b[i] = 6*((y[i-1]-y[i]) / (x[i-1]-x[i]) - (y[i]-y[i+1]) / (x[i]-x[i+1]));

  	// Din.Print();
  	// Dout.Print();
  	// b.Print();

	triVec.push_back(Dout);
	triVec.push_back(Din);
	triVec.push_back(Dout);

	FCmatrixBanded triD(triVec);

	// solve system and get the 2nd derivative coefficients
	EqSolver sist(triD, b); 
	
	// store coeffs on internal array K
	K = sist.GaussEliminationSolver();

	#ifdef DEBUG
	cout << "Spline3 system to solve:" << endl;
	sist.Print(4, 6);

	cout << "Printing the second Derivatives vector:" << endl;
	K.Print(4, 6);

	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

double Spline3Interpolator::dfInterpolator(double* var, double* par) const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return InterpolateDerivative(var[0]);
}

double Spline3Interpolator::pfInterpolator(double* var, double* par) const
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif

	return InterpolatePrimitive(var[0]);
}