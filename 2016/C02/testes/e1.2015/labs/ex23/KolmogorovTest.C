#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

double KolmogorovTest(vector<double> Fx, vector<double> Fref)
{
	if(Fref.end() - Fref.begin() != Fx.end() - Fx.begin())
		cout << "Please provide two functions with the same number of partitions." << endl;

	vector<double>::iterator VitRef, VitF;

	double max = 0;
	double dif = 0;

	for(VitRef = Fref.begin(), VitF = Fx.begin(); VitRef != Fref.end(); VitF++, VitRef++) {
		if((dif = abs(*VitRef - *VitF)) > max)
			max = dif;
	}

	return max;
}