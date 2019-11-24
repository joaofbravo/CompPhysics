#include "DataPoints.h"

using namespace std;

int main()
{
	double* x = new double [15];
	double* y = new double [15];

	for (int i = 0; i < 15; ++i)
	{
		x[i]= i;
		y[i]= i*i;
	}

	DataPoints DATA(15,x,y);
	DataPoints a(DATA);
	DataPoints b(move(a));

	DATA.Draw();
	DATA.Print();
	a.Print();
	b.Print();

	return 0;
}