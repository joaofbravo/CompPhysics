#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>

using namespace std;

void random(double&, double=5, double=55);
void std_dev(double&, const double*, const double&, int);


int main(){

	double x[1000], avrg=0., dev=0., y;

	cout << "This program calculates the average and standard deviation of 1000 randomly generated values between 5 and 55. \nIt also calculates y=x/(x-10) for each one of them. \n" << endl;

	srand(time(NULL));

	for (int i = 0; i < 1000; ++i){
		random(x[i], 5, 55);

		avrg += x[i];

		y = x[i] / (x[i] - 10);

		cout << y << "   ";

		if((i+1) % 5 == 0)
			cout << endl;
	}

	avrg /= 1000;

	std_dev(dev, x, avrg, 1000);

	cout << "\nThe average is " << avrg << " and the standard deviation is " << dev << endl << endl;

	return 0;
}


void random(double &x, double min, double max){
	x = ((double)rand() / (double)RAND_MAX) *(max-min) + min;
}

void std_dev(double &dev, const double *x, const double &avrg, int N){
	for (int i = 0; i < N; ++i)
		dev += (x[i] - avrg) * (x[i] - avrg);
	
	dev = sqrt(dev / (N-1));
}