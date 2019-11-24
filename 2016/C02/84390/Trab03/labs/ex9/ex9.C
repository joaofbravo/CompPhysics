#include <iostream>
#include <cmath>

using namespace std;

double Sum(int*, int*);

int main()
{
	int vi, vj;
	double r=0;

	cout << "Introduza os limites máximos na forma <vi>, <vj>: ";
	cin >> vi >> vj;

	if(vi < 0 || vj < 5){
		cout << "Introduza valores tal que vi>=0 e vj>=5" << endl;
		return -1;
	}

	r = Sum(&vi, &vj);

	cout << "A soma vale: " << r << endl;

	return 0;
}


double Sum(int* vi, int* vj) //vi, vj= limites de i e j
{
	double r=0.;

	for (int i = 0; i < *vi; ++i){
		for (int j = 0; i < *vj; ++j)
			r += cos(i*i + sqrt(j));
	}
	
	return r;
}