#include "Derivator.h"
#include "TF1.h"
#include "DataPoints.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	TF1 f("f","exp(x)", -5, 5);
	Derivator dfunc;
	dfunc.SetFunction(f);
	dfunc.Draw();
	
	cout << setprecision(7);
	cout << dfunc.ForwardDifference(0) << endl;
	cout << dfunc.BackwardDifference(0) << endl;
	cout << dfunc.CentralDifference(0) << endl;
	cout << dfunc.CentralFirstAcu4(0) << endl;
	cout << dfunc.CentralFirstAcu8(0) << endl;
	cout << dfunc.CentralSecondAcu2(0) << endl;
	cout << dfunc.CentralSecondAcu4(0) << endl;
	cout << dfunc.CentralForthAcu2(0) << endl;

	cout << dfunc.ForwardDifference(2) << endl;
	cout << dfunc.BackwardDifference(2) << endl;
	cout << dfunc.CentralDifference(2) << endl;
	cout << dfunc.CentralFirstAcu4(2) << endl;
	cout << dfunc.CentralFirstAcu8(2) << endl;
	cout << dfunc.CentralSecondAcu2(2) << endl;
	cout << dfunc.CentralSecondAcu4(2) << endl;
	cout << dfunc.CentralForthAcu2(2) << endl;

	double x[20];
	double y[20];
	int n = 8;

	for (int i = 0; i < n; ++i)
	{
		x[i] = i;
		y[i] = fabs((dfunc.CentralForthAcu2(i) - dfunc.Eval(i))/dfunc.Eval(i));
	}

	DataPoints data(n,x,y);
	data.Draw();

	return 0;
}