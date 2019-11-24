#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

// returns accumulated distribution on x intervals
// NCALLS = number of times generation function is called
// vector<double> x = x boundaries on the N intervals (N+1 boundaries)
// double (*f) (double, double)) = pointer to generating function

vector<double>& Fobs(int NCALLS, vector<double>& x, double (*f) (double, double)) {

	/*
	vector<double>::iterator Vit;

	for (Vit = x.begin() + 1; Vit != x.end() ; Vit++)
	{
		if(*Vit < *(Vit-1))
		{
			cout << "Please provide an ordered vec" << endl;
			exit(-1);
		}
	}
	*/
	vector<double>::iterator Vit;
	static vector<double> res(x.size()-1, 0);

	for (int i = 0; i < NCALLS; ++i)
	{
		double r = f(x[0], x[(int)x.size()-1]);
		int j = 0;
		for (Vit = x.end()-1, j =(int) x.size()-2; r < *Vit; j--, Vit--)
			res[j]+= r;
	}

	for(unsigned int i= 0; i < res.size(); i++)
		res[i] /= *(res.end()-1);

	return res;
}