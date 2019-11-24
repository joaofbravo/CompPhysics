#include <iostream>
#include <cmath>

using namespace std;

const double G = 6.67408e-11;
const double M_Earth = 5.97219e24;
const unsigned int R_Earth = 6371000;

int main(){
	
	double T, hgt;

	cout << "Insert the satellite's period in seconds: ";
	cin >> T;

	if(T < 0){
		cout << "Insert a non-negative number" << endl;
		return -1;
	}

	hgt = pow(G * M_Earth * T * T / (4 * M_PI * M_PI), 1.0/3.0) - R_Earth;

	if(hgt >=0){
		cout << "The satellite is " << hgt << " meters above the ground." << endl << endl;
	}
	else{
		cout << "Impossible! The satellite would be " << abs(hgt) << " meters below the ground." << endl << endl;
	}

	return 0;
}