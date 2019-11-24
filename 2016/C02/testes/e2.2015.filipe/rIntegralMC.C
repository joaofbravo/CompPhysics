#include "IntegratorMC.h"
#include "Derivator.h"
#include "cFCgraphics.h"
#include "Func1D.h"
#include "Spline3Interpolator.h"
#include <cmath>
#include <iostream>
#include "ZeroFinder.h"

using namespace std;




int main()
{
	TFormula f0("f0", "1/(x*x+ cos(x)*cos(x))");

	double a = 0;
	double b = M_PI;
	int N = 1000;


	double result;
	double error;

	IntegratorMC fIntegrator(f0,&a,&b);
	fIntegrator.UniformRandom(N,result, error);

	cout << "UniformRandom: " <<result << " +- " << error << "\trelative: " << error/result << endl;

	TFormula pdf("pdf","([0] == 0)? 1/TMath::Pi(): [0]*exp(-[0]*x)/(1-exp(-[0]*TMath::Pi()))");
	TFormula inv("inv","([0] == 0)? x*TMath::Pi(): log(1 - [0] * x*(1-exp(-[0]*TMath::Pi()))/[0])/(-[0])");

	pdf.SetParameter(0,1);
	inv.SetParameter(0,1);
	

	


	result = 0;
	error = 0;
	fIntegrator.ImportanceSampling(N,result, error,pdf,&inv);

	cout << "ImportanceSampling: " <<result << " +- " << error << "\trelative: " << error/result << endl;

	double Error_a[20];

	double aval = 0;
	double x[20];
	for(int i = 0; i < 20; i++, aval+= 2./20.)
	{
		x[i] = aval;
		pdf.SetParameter(0,aval);
		inv.SetParameter(0,aval);
		fIntegrator.ImportanceSampling(N,result, Error_a[i],pdf,&inv);
		// cout << i << endl;
	}

	Spline3Interpolator spline(20,x,Error_a);
	spline.Draw();
	ZeroFinder zero(spline.GetInterpolDerivative());
	cout <<"Optimal a: " << (aval = zero.Secant(0.5,0.9,0.1)) <<endl;



	return 0;
}

