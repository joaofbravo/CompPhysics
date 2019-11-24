#include <cmath>
#include <iostream>

using namespace std;

int main() {

	float a = 0, b = 10;
	double c = 0, d = 10;

	//float precision
	while(a != 1){
		b /= 10;
		a = 1. + b;
	}
	cout << "Float precision:  " << " = " << b << endl << endl;

	//double precision
	while(c != 1){
		d /= 10;
		c = 1. + d;
	}
	cout << "Double precision: " << " = " << d << endl << endl;

	return 0;
}