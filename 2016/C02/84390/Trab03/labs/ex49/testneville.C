#include "NevilleInterpolator.h"
#include "TF1.h"
#include <cmath>

int main()
{
	double* x = new double [15];
	double* y = new double [15];

	for (int i = 0; i < 15; ++i)
	{
		x[i]= i;
		y[i]= i*i*i*i;
	}

	TF1 f("f0","x*x*x*x", 0, 15);
	
	NevilleInterpolator Inter(15,x,y);
	Inter.Draw();
	
	Inter.SetFunction(f);
	Inter.Draw();

	NevilleInterpolator Inter0(5,x,y,f);
	Inter0.Draw();

	for (int i = 0; i < 15; ++i)
	{
		x[i]= i;
		y[i]= sin(i+0.0001)/(i+0.0001);
	}

	TF1 g("g0","sin(x)/x", 0, 15);

	Inter0.SetDataPoints(15,x,y);
	Inter0.SetFunction(g);
	Inter0.Draw();
	Inter0.Print();

	return 0;
}