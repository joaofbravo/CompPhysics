#include <iostream>

using namespace std;

int main(){

	double sum = 0;

	for (double x=0.1; x<5.45; x += 0.1) {
		sum += x;
	}

	cout << sum << endl;

	return 0;
}