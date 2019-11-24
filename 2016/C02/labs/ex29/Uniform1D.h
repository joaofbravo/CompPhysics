#ifndef __Uniform1D__
#define __Uniform1D__

#include "Motion1D.h"

class Uniform1D : public Motion1D {
public:
	Uniform1D(int=0, float=0., float=0., float=0., float=0.);
	~Uniform1D(){;}

	void Print();

private:
	float ti; // initial time
	float dt; // time duration
	float xi; // initial position
	float vel; // velocity (m/s)
};

#endif