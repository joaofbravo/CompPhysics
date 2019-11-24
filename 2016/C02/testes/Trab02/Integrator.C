#include "Integrator.h"
#include "Derivator.h"
#include "TRandom3.h"
#include "TF1.h"
#include <iostream>
#include <cmath>

using namespace std;

Integrator::Integrator(double fx0, double fx1, TF1 *fp):x0(fx0), x1(fx1), Func1D(fp)
{
	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

Integrator::Integrator(double fx0, double fx1, TF1 &fp):x0(fx0), x1(fx1), Func1D(fp)
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
	bool swap = false;
	
	if(b < a)
	{
		std::swap(a,b);
		swap = true;
	}

	if((b-a) < a*1e-16)
	{
		cout << "Limits chosen are too close to compute integral." << endl;
		
		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return;
	}

	double h = (b-a)/(double)n;

	Integral = 0.;

	Integral += p->Eval(a);
	Integral += p->Eval(b);

	for (int i = 1; i < n; ++i)
		Integral += 2*p->Eval(a + i*h);

	Integral *= h/2;

	if(swap)
		Integral = -Integral;

	TRandom3 R(0);
	
	Derivator df(p);

	double avg = 0.;
	
	for (int i = 0; i < n; ++i)
	{
		avg += df.CentralSecondAcu4(R.Rndm()*(b-a) + a);		
		// cout << endl;
	}

	avg /= (double)n;

	//neste ciclo for dá problema, descomentar o endl resolve... MAS PORQUÊ??????
	// cout << n << "\tavg: " << avg << endl;

	Error = fabs(h*h/12.*(b-a)*avg);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}

void Integrator::SimpsonRule(int n, double& Integral, double& Error) const
{
	double a = x0;
	double b = x1;
	bool swap = false;

	if(b < a)
	{
		std::swap(a,b);
		swap = true;
	}

	if((b-a) < a*1e-16)
	{
		cout << "Limits chosen are too close to compute integral." << endl;

		#ifdef DEBUG
		cout << __PRETTY_FUNCTION__ << endl;
		#endif

		return;
	}

	double h = (b-a)/(double)n;

	Integral = 0.;

	Integral += p->Eval(a);
	// cout << Integral << endl;
	
	

	Derivator df(p);

	for (int i = 1; i < n/2; ++i)
	{
		Integral += 2*p->Eval(a+2*i*h);
		// cout << Integral << endl;
	}

	for (int i = 1; i <= n/2; ++i)
	{
		Integral += 4*p->Eval(a+(2*i-1)*h);
		// cout << Integral << endl;
	}

	if((n/2)*2 != n)
	{
		if(n == 1)
		{
			Integral = (p->Eval(b) + p->Eval(a)) * (b-a)/2.;
			Error = fabs(h*h/12.*(b-a)*df.CentralSecondAcu2((a+b)/2.));
			
			#ifdef DEBUG
			cout << __PRETTY_FUNCTION__ << endl;
			#endif

			return;
		}

		Integral += 1./4.*(-p->Eval(b-2*h) + 12*p->Eval(b-h) + 5*p->Eval(b));
	}else
		Integral += p->Eval(b);

	Integral *= h/3.;
	
	if(swap)
		Integral = -Integral;

	TRandom3 R(0);
	
	double avg = 0.;
	
	for (int i = 0; i < n; ++i){
		avg += df.CentralForthAcu2(R.Rndm()*(b-a) + a);		
		// cout << endl;
	}

	avg /= (double)n;

	//neste ciclo for dá problema, descomentar o endl resolve... MAS PORQUÊ??????
	// cout << n << "\tavg: " << avg << endl;

	Error = fabs((b-a)*h*h*h*h/180.*avg);

	#ifdef DEBUG
	cout << __PRETTY_FUNCTION__ << endl;
	#endif
}