#ifndef __Interpolator__
#define __Interpolator__

#include "DataPoints.h"
#include "cFCgraphics.h"
#include <string>

class TF1;

class Interpolator : public DataPoints {
public:
	Interpolator(int =0, double* =nullptr, double* =nullptr, TF1* =nullptr);
	Interpolator(int, double*, double*, TF1&);
	Interpolator(const Interpolator&);
	
	virtual ~Interpolator();


	virtual void SetDataPoints(int, double*, double*);
	void SetFunction(TF1&); // underlying function
	const TF1& GetInterpolationFunction() const;

	virtual double Interpolate(double x) = 0;
	
	void Draw() const; //draw everything (points and interpolation function)
	virtual void Print(string ="execs/DATA.txt") const; // print results

	static int funccounter;

protected:
	double fInterpolator(double*, double*);

	TF1* FInterpolator; //interpolation function
	TF1* F0; // underlying function from where points were extracted
};

#endif