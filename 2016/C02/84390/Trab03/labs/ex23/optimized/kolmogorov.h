#include <vector>

using namespace std;

double GetRandom(double xmin, double xmax);

vector<double>& Fobs(int NCALLS, vector<double>& x, double (*f) (double, double));

double KolmogorovTest(vector<double> &Fx, vector<double> &Fref);