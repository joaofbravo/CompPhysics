#include <cmath>

using namespace std;

double func(double x){
	return sqrt(abs(sin(2 * x)));
}

void func(double x, double& f){
	f = sqrt(abs(sin(2 * x)));
}

void func(double x, double *const f){
	*f = sqrt(abs(sin(2 * x)));
}