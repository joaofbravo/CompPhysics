#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	float fpi  = 4 * atanf(1);
	double dpi = 4 * atan(1);
	double pf  = (M_PI-fpi) / M_PI;
	double pd  = (M_PI-dpi) / M_PI;

	cout << "Float precision: " << pf << endl;
	cout << "Double precision: " << pd << endl;

	return 0;
}

