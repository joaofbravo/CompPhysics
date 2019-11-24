#ifndef __ODEpoint__
#define __ODEpoint__ 

#include "Vec.h"

class ODEpoint: public Vec {
public:
	ODEpoint(int fndim =0, const double* x =nullptr);
	ODEpoint(const ODEpoint&);
	ODEpoint(const Vec&);
	ODEpoint(ODEpoint&&);
	ODEpoint(Vec&&);
	~ODEpoint();

	// assignments
	const ODEpoint& operator=(const ODEpoint&);
	const ODEpoint& operator=(const Vec&);
	ODEpoint& operator=(ODEpoint&&);
	ODEpoint& operator=(Vec&&);

	// get methods
	int Dim() const;
	double T() const;
	double X(int i) const;
	double* GetArray();
};

#endif
