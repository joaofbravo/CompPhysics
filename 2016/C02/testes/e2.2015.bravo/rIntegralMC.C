#include "IntegratorMC.h"
#include "TFormula.h"
#include "TMath.h"
#include "Spline3Interpolator.h"
#include "Func1D.h"
#include "ZeroFinder.h"
#include <iostream>

using namespace std;

int main() {
	TFormula f("f", "1/(x*x + cos(x)*cos(x))");

	double min=0.;
	double max=TMath::Pi();
	double result;
	double error;

	IntegratorMC integ(f, &min, &max);
	integ.UniformRandom(1000, result, error);
	cout << result << " +- " << error << "\trelative error: " << error/result << endl;

	TFormula pdf("pdf","1/TMath::Pi()");
	TFormula inv("inv","x*TMath::Pi()");
	integ.ImportanceSampling(1000, result, error, pdf, &inv);
	cout << result << " +- " << error << "\trelative error: " << error/result << endl;

	TFormula pdf2("pdf2","([0] == 0)? 1/TMath::Pi(): [0]*exp(-[0]*x)/(1-exp(-[0]*TMath::Pi()))");
	TFormula inv2("inv2","([0] == 0)? x*TMath::Pi(): log(1 - [0] * x*(1-exp(-[0]*TMath::Pi()))/[0])/(-[0])");
	double ey[20];
	double ex[20];
	double a = 0.1;

	for (int i = 0; i < 20; ++i, a+=1./10.) {
		ex[i] = a;
		pdf2.SetParameter(0,a);
		inv2.SetParameter(0,a);

		integ.ImportanceSampling(1000, result, ey[i], pdf2, &inv2);
		cout << "Iter " << i << ":  " << ey[i] << endl;
	}
	cout << endl;

	Spline3Interpolator spline(20, ex, ey);
	// spline.Draw();

	ZeroFinder Z(spline.GetInterpolDerivative());
	// Z.Draw();

	double zero = Z.Secant(0.7, 0.9, 1.E-3);
	cout << "Optimal a: " << zero << endl << endl;

	return 0;
}