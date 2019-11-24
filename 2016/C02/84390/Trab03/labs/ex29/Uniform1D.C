#include "Uniform1D.h"
#include <cstdio>

Uniform1D::Uniform1D(int fN, float Ti, float Xi, float Dt, float Vel) : 
Motion1D(fN), ti(Ti), dt(Dt), xi(Xi), vel(Vel) {
	
	// t and x arrays are created by Motion1D
	t[0]=ti;
	x[0]=xi;

	float tinc = dt / ((float)fN - 1);
	float xinc = vel * tinc;

	for (int i=1; i<N; i++) {
		t[i] = t[i-1] + tinc;
		x[i] = x[i-1] + xinc;
	}

	printf("%s\n", __PRETTY_FUNCTION__);
}

void Uniform1D::Print() {
	Motion1D::Print(); //call Print from base class
	
	printf("ti=%f, xi=%f, vel=%f \n", ti, xi, vel);
	printf("%s\n", __PRETTY_FUNCTION__);
}