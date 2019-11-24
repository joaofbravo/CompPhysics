#include "Integrator.h"
#include "TF1.h"
#include "TMath.h"
#include <iostream>

using namespace std;

int main()
{
	TF1 f("f","exp(x)", 0, 1);
	Integrator intgr(2,0,f);
	double integral[2], error[2];
	intgr.TrapezoidalRule(1000, integral[0], error[0]);
	intgr.SimpsonRule(100, integral[1], error[1]);

	TF1 f2("f2", "cos(x)", 0., TMath::Pi());
	Integrator intgr2(2, TMath::Pi(), f2);
	double integral2[2], error2[2];
	intgr2.TrapezoidalRule(10, integral2[0], error2[0]);
	intgr2.SimpsonRule(100, integral2[1], error2[1]);
	
	cout << endl;
	cout << integral[0] << " +- " << error[0] << endl;
	cout << integral[1] << " +- " << error[1] << endl << endl;

	cout << integral2[0] << " +- " << error2[0] << endl;
	cout << integral2[1] << " +- " << error2[1] << endl;

	return 0;
}