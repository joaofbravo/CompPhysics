#include "Integrator.h"
#include "Derivator.h"
#include "TRandom3.h"
#include "TF1.h"
#include <iostream>
#include <cmath>

using namespace std;
double SimpsonAdaptativeAux(TF1* F, double x0, double x1, double epsilon, double S, double fx0, double fx1, double fc, int bottom);

Integrator::Integrator(double fx0, double fx1,  TF1* fp) : x0(fx0), x1(fx1), Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1,  TF1& fp) : x0(fx0), x1(fx1), Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1,  Func1D& f) : x0(fx0), x1(fx1), Func1D((Func1D&)f)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1, Func1D&& f) : x0(fx0), x1(fx1), Func1D((Func1D&&)f)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::~Integrator()
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Integrator::SetLimits(double fx0, double fx1)
{
	x0 = fx0;
	x1 = fx1;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}
void Integrator::SetMin(double fx0)
{
	x0 = fx0;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}
void Integrator::SetMax(double fx1)
{
	x1 = fx1;

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif	
}

void Integrator::TrapezoidalRule(int n, double& Integral, double &Error) const 
{
	double a = x0;
	double b = x1;
	bool swaplim = false;
	
	if(b < a) {
		swap(a,b);
		swaplim = true;
	}

	double h = b-a;

	if(h < a*1e-16)
	{
		cout << "Limits chosen are too close to compute integral." << endl;
		
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		exit(1);
	}

	h /= (double)n;

	Integral = 0.;
	Integral += F->Eval(a);
	Integral += F->Eval(b);

	for (int i = 1; i < n; ++i)
		Integral += 2*F->Eval(a + i*h);

	if(swaplim)
		Integral *= -h/2.;
	else
		Integral *= h/2.;

	TRandom3 R(0);
	Derivator df(F);
	double avg = 0.;
	
	for (int i = 0; i < n; ++i)
		avg += df.CentralSecondAcu4(R.Rndm()*(b-a) + a);

	avg /= (double)n;
	// cout << n << "  avg: " << avg << endl;

	Error = fabs(h*h*(b-a)*avg/12.);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Integrator::SimpsonRule(int n, double& Integral, double& Error) const
{
	double a = x0;
	double b = x1;
	bool swaplim = false;

	if(b < a) {
		swap(a,b);
		swaplim = true;
	}

	double h = b-a;

	if(h < a*1e-16)
	{
		cout << "Limits chosen are too close to compute integral." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		exit(1);
	}

	h /= (double)n;

	Integral = 0.;

	if(n != 1){
		Integral += F->Eval(a);

		for (int i = 1; 2*i < n; ++i)
			Integral += 2*F->Eval(a+2*i*h);

		for (int i = 1; 2*i <= n; ++i)
			Integral += 4*F->Eval(a+(2*i-1)*h);
	}

	Derivator df(F);

	if(n%2 != 0)
	{
		if(n == 1)
		{
			Integral = (F->Eval(b) + F->Eval(a)) * (b-a)/2.;
			Error = fabs(h*h*(b-a)*df.CentralSecondAcu2((a+b)/24.));
			
			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif

			return;
		}

		Integral += 1./4.*(-F->Eval(b-2*h) + 12*F->Eval(b-h) + 5*F->Eval(b));
	}
	else
		Integral += F->Eval(b);
	
	if(swaplim)
		Integral *= -h/3.;
	else
		Integral *= h/3.;

	TRandom3 R(0);
	double avg = 0.;

	for (int i = 0; i < n; ++i)
		avg += df.CentralForthAcu2(R.Rndm()*(b-a) + a);		

	avg /= (double)n;
	// cout << n << "  avg: " << avg << endl;
	
	Error = fabs(h*h*h*h*(b-a)*avg/180.);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}


// ATTENTION! This method isn't original, only adapted to be used in this class,
// credits: https://en.wikipedia.org/wiki/Adaptive_Simpson's_method

double Integrator::SimpsonAdaptative(double epsilon, int maxRecursionDepth) const 
{           
	double c = (x0 + x1)/2, h = x1 - x0;
	double fx0 = F->Eval(x0), fx1 = F->Eval(x1), fc = F->Eval(c);
	double S = (h/6)*(fx0 + 4*fc + fx1);

	return SimpsonAdaptativeAux(F, x0, x1, epsilon, S, fx0, fx1, fc, maxRecursionDepth);                   
}

double SimpsonAdaptativeAux(TF1* F, double x0, double x1, double epsilon, double S, double fx0, double fx1, double fc, int bottom) {
	
	// cout << "xmin: " << x0;
	// cout << " xmax: " << x1;
	// cout << " bottom: "<< bottom << endl;

	double c = (x0 + x1)/2, h = x1 - x0;
	double d = (x0 + c)/2, e = (c + x1)/2;
	double fd = F->Eval(d), fe = F->Eval(e);
	double Sleft = (h/12)*(fx0 + 4*fd + fc);        
	double Sright = (h/12)*(fc + 4*fe + fx1);        
	double S2 = Sleft + Sright;

	if (bottom <= 0 || fabs(S2 - S) <= 15*epsilon) 
		return S2 + (S2 - S)/15;

	//15 comes from the Internet, but it is only Important in infinitesimal quantities

	return SimpsonAdaptativeAux(F, x0, c, epsilon/2, Sleft,  fx0, fc, fd, bottom-1) + SimpsonAdaptativeAux(F, c, x1, epsilon/2, Sright, fc, fx1, fe, bottom-1);                     
}