#include "Func1D.h"
#include "TF1.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	TF1 f("f1","log(x)/x + pow(x,x)", 0, 10);
	Func1D func (&f);
	func.Draw();
	Func1D gunc (f);
	gunc.Draw();
	Func1D hunc (gunc);
	hunc.Draw();
	Func1D iunc (move(func));
	iunc.Draw();
	func.Draw();

	cout << hunc.Eval(2) << endl;
	cout << hunc.Eval(0) << endl;

	TF1 f2("f2","x^2+30", 0., 10);
	Func1D fexp (&f2);
	fexp.Draw();
	cout << "exp(-2) = " << fexp.Eval(-2) << endl;
	cout << "exp(0) = " << fexp.Eval(0) << endl;
	cout << "exp(1) = " << fexp.Eval(1) << endl;
	cout << "exp(2) = " << fexp.Eval(2) << endl;
	cout << "exp(5) = " << fexp.Eval(5) << endl;
	cout << setprecision(8) << "exp(10000) = " << fexp.Eval(10000) << endl;

	return 0;
}
