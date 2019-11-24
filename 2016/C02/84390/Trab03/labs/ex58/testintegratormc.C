#include "IntegratorMC.h"
#include "TF2.h"
#include "TF3.h"
#include "TH1F.h"
#include "cFCgraphics.h"
#include <iostream>

using namespace std;

int main() {
	//para n dimensões, mais vale usar só o UniformRandom.

	TFormula f("f", "x");
	double min[] = {-1,-1,-1,-1};
	double max[] = {1,1,1,1};

	IntegratorMC fIntegrator(f,min,max);

	double result[4];
	double error[4];

	fIntegrator.UniformRandom(1000000, result[0], error[0]);
	cout << result[0] << " +- " << error[0] << "\trelative: " << error[0]/result[0] << endl;

	TFormula pdf("pdf","exp(x)/(exp(1)-exp(-1))");
	TFormula inv("inv","log(x + 1/(exp(2)-1))+log(exp(1)-exp(-1))");

	fIntegrator.ImportanceSampling(1000000, result[1], error[1], pdf, &inv);
	cout << result[1] << " +- " << error[1] << "\trelative: " << error[1]/result[1] << endl;

	TFormula square("square","x>0 ? 1 : -1");
	TFormula squareinv("squareinv","2*x-1");

	fIntegrator.AcceptanceRejection(1000000, result[2], error[2], square, &squareinv);
	cout << result[2] << " +- " << error[2] << "\trelative: " << error[2]/result[2] << endl;

	cout << "\nÁrea:  ";
	fIntegrator.UniformRandom(1000000, result[3], error[3], true);
	cout << result[3] << " +- " << error[3] << "\trelative: " << error[3]/result[3] << endl << endl << endl;


	TFormula f2("f2", "x*x");
	double min2[] = {0,0,0,0};
	double max2[] = {1,1,1,1};

	IntegratorMC f2Integrator(f2,min2,max2);

	double result2[4];
	double error2[4];

	f2Integrator.UniformRandom(1000000, result2[0], error2[0]);
	cout << result2[0] << " +- " << error2[0] << "\trelative: " << error2[0]/result2[0] << endl;

	TFormula pdf2("pdf2","exp(x)/(exp(1)-1)");
	TFormula inv2("inv2","log(x*(exp(1)-1)+1)");

	f2Integrator.ImportanceSampling(1000000, result2[1], error2[1], pdf2, &inv2);
	cout << result2[1] << " +- " << error2[1] << "\trelative: " << error2[1]/result2[1] << endl;

	TFormula square2("square2","1");
	TFormula squareinv2("squareinv2","x");

	f2Integrator.AcceptanceRejection(1000000, result2[2], error2[2], square2, &squareinv2);
	cout << result2[2] << " +- " << error2[2] << "\trelative: " << error2[2]/result2[2] << endl;

	cout << "\nÁrea:  ";
	f2Integrator.UniformRandom(1000000, result2[3], error2[3], true);
	cout << result2[3] << " +- " << error2[3] << "\trelative: " << error2[3]/result2[3] << endl;

	return 0;
}