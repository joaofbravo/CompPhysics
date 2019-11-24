#include "LagrangeInterpolator.h"
#include "TF1.h"
#include <cmath>

int main()
{
	double* x = new double [15];
	double* y = new double [15];

	for (int i = 0; i < 15; ++i)
	{
		x[i]= i;
		y[i]= 3.*i/((i+2.)*(i+2.));
	}

	TF1 f("f0","3*x/((x+2)*(x+2))", 0, 15);
	
	LagrangeInterpolator Inter(10,x,y,f);
	Inter.Draw();

	return 0;
}