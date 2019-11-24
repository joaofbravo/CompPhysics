#include "Mmultiply.h"
#include <iostream>

using namespace std;

int main(){

	double **mx = new double* [2];
	mx[0] = new double [3];
	mx[1] = new double [3];

	mx[0][0] = 2.;
	mx[1][0] = 3.;
	mx[0][1] = 10.;
	mx[1][1] = 2.;
	mx[0][2] = 5.;
	mx[1][2] = 7.;

	double *vr = new double [3] {2, 5, 7};
	double *pt = new double [3];

	Mmultiply(mx, vr, 2, 3, pt);

	for (int i = 0; i < 2; ++i)
		cout << pt[i] << " ";
	cout << endl;

	delete[] pt;
	delete[] vr;
	deleteM(mx, 2);	

	return 0;
}
