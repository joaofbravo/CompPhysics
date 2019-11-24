#include "ex15.h"
#include <iostream>
#include <cmath>

using namespace std;

int main(){

	double x, y, f1, f2, f3;

	cout << "f(x) = sqrt(sin(2x))" << endl;
	cout << "Insert a value for x: ";
	cin >> x;

	y = x * M_PI / 180;

	f1 = func(y);
	func(y, f2);
	func(y, &f3);

	cout << "f1(" << x <<") = " << f1 << endl;
	cout << "f1(" << x <<") = " << f2 << endl;
	cout << "f1(" << x <<") = " << f3 << endl;

	return 0;
}