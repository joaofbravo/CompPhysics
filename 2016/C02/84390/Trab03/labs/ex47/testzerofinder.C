#include "ZeroFinder.h"
#include <iostream>

using namespace std;

int main() {

	TF1* f = new TF1("fzero", "[0] + [1]*x + [2]*x*x");
	f->SetParameters(1.,5., -10.);
	ZeroFinder Z(f);

	delete f;

	// Z.Draw();

	double zero1 = Z.Bisection(-10., 0.1, 1.E-3);
	cout << "Bisection root: " << zero1 << endl << endl;

	double zero2 = Z.Newton(0.1, 1.E-3);
	cout << "Newton root: " << zero2 << endl << endl;

	double zero3 = Z.Secant(-10., 0.1, 1.E-3);
	cout << "Secant root: " << zero3 << endl << endl;

	return 0;
}