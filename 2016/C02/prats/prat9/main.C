#include "ZeroFunctor.h"
#include "TF1.h"
#include <iostream>

using namespace std;

int main() {
	TF1 *f = new TF1("fzero", "[0] + [1]*x");
	f->SetParameters(1.,10.);
	ZeroFunctor Z(f);
	double a = Z.Bisection(-10., 100., 1.E-3, 10000);

	cout << "root: " << a  << endl;

	return 0;
}