#include <cstdlib>

double GetRandom(double xmin, double xmax)
{
	return ((double)rand()/(double)RAND_MAX) * (xmax-xmin) + xmin;
}