#ifndef __DataPoints__
#define __DataPoints__

#include "cFCgraphics.h"

class DataPoints {
public:
	DataPoints(int =0, double* =nullptr, double* =nullptr);
	DataPoints(const DataPoints&);
	DataPoints(DataPoints&&);
	virtual ~DataPoints();

	virtual void SetDataPoints(int, double*, double*);

	virtual void Draw() const;
	virtual void Print(string ="execs/DATA.txt") const;
	
protected:
	int N; // number of data points
	double *x, *y; // arrays
};

#endif