#include "Integrator.h"
#include "Derivator.h"
#include "TRandom3.h"
#include "TF1.h"
#include <iostream>
#include <cmath>

using namespace std;

Integrator::Integrator(double fx0, double fx1, const TF1* fp) : x0(fx0), x1(fx1), Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1, const TF1& fp) : x0(fx0), x1(fx1), Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1, const Func1D& f) : x0(fx0), x1(fx1), Func1D((Func1D&)f)
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