#include <iostream>

using namespace std;

double sum(const double *const v, int n);


int main(){

	double result, v[10] = {1,2,3,4,5,6,7,8,9,10};

	result = sum(v, sizeof(v) / sizeof(*v));

	cout << "The sum of the array's elements is " << result << endl << endl;

	return 0;
}


double sum(const double *const v, int n){

	double result;

	for (int i = 0; i < n; ++i){
		result += v[i];
	}
	
	return result;
}