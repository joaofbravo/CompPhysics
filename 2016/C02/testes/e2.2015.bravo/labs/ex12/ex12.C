#include <iostream>
#include <cmath>

using namespace std;

const double g = 9.81;

int main(){
	
	double hgt, t;

	cout << "Insert the height at which the mass will fall: ";
	cin >> hgt;

	if(hgt < 0){
		cout << "Insert a non-negative number" << endl;
		return -1;
	}

	t = sqrt(2 * hgt / g);

	cout << "It will take " << t << " seconds for the mass to reach the ground." << endl << endl;

	return 0;
}