#include "Func1D.h"
#include "Integrator.h"
#include "Derivator.h"
#include <cmath>
#include <iostream>

using namespace std;

// derivator global pois é preciso na função derivada userfunc
Derivator d;
double userfunc(double* var, double* par);

int main()
{
	TF1 f0("f0", "1/(x*x+ cos(x)*cos(x))", 0., M_PI);
	Func1D func(f0);
	func.Draw("","Prob2_func.pdf");

	d.SetFunction(f0);

	TF1 f1("f1", userfunc, 0., M_PI);
	Func1D func2d(f1);
	func2d.Draw("","Prob2_funcd2.pdf");

	double a = 0.;
	double b = M_PI;
	double max = 0.;
	double Error = 1E-4;

	for (double x = 0; x < b; x += (b-a)/1000)
	{
		if(fabs(f1.Eval(x)) > max)
			max = fabs(f1.Eval(x));
	}

	double h = sqrt(fabs(Error*12./((b-a)*max)));
	cout << "Optimal h = " << h << endl;

	Integrator fIntegrator(a,b,f0);

	double result;
	double error;

	// h = (b-a)/N
	fIntegrator.TrapezoidalRule((b-a)/h, result, error);

	cout << result << " +- " << error << "\trelative: " << error/result << endl;	

	return 0;
}

double userfunc(double* var, double* par)
{
	return d.CentralSecondAcu4(var[0]);
}