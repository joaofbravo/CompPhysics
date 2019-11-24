#include <iostream>
#include <math.h>

using namespace std;

double sin0(double, double);
double sin1(double, double);

int main()
{
	double x = 3;
	double delta = 1e-11;

	cout << "x = " << x << " delta = " << delta << endl << endl;
	
	cout << "Metod 1: sin(x)-sin0(x) = " << sin(x) - sin0(x,delta) << endl;
	cout << "Relative error = " << (sin(x) - sin0(x,delta))/(sin(x)) << endl << endl;

	cout << "Metod 2: sin(x)-sin1(x) = " << sin(x) - sin1(x,delta) << endl;
	cout << "Relative error = " << (sin(x) - sin1(x,delta))/(sin(x)) << endl << endl;

	return 0;
}

double sin0(double x, double step)
{
	return (cos(x) - cos(x + step))/step;
}

double sin1(double x, double step)
{
	return (2/step)*sin(x+step/2)*sin(step/2);
}