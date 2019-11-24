#include <cmath>
#include <iostream>

using namespace std;

int main() {

	short int i = 0;
	float a=1, b=0;
	double c=1, d=0;

	//float underflow
	while(a - b != 0){
		--i;
		a = pow(2,i-1);
		b = pow(2,i);
	}

	cout << "Float underflow limit:\t 2^" << i+1 << " = " << pow(2,i+1) << endl << endl;
	i = 0;

	//double underflow
	while(c - d != 0){
		--i;
		c = pow(2,i-1);
		d = pow(2,i);
	}
	cout << "Double underflow limit:\t 2^" << i+1 << " = " << pow(2,i+1) << endl << endl;
	i = 0;

	//float overflow
	while(a - b == 0){
		++i;
		a = b = pow(2,i);
	}
	cout << "Float overflow limit:\t 2^" << i-1 << " = " << pow(2,i-1) << endl << endl;
	i = 0;

	//double overflow
	while(c - d == 0){
		++i;
		c = d = pow(2,i);
	}
	cout << "Double overflow limit:\t 2^" << i-1 << " = " << pow(2,i-1) << endl << endl;

	return 0;
}