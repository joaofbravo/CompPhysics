#ifndef __pointSorter__
#define __pointSorter__

#include <vector>
#include <map>
#include "point.h"

class pointSorter {
public:
	pointSorter(const std::vector<point*>& = {});
	~pointSorter();

	point* operator[] (int);
	std::vector<point*> sort(int = 0);
	int size();

private:
	std::vector<point*> V;
	std::map<double, point*> M;
};

#endif
