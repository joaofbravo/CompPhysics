#include "point.h"
#include <cmath>
#include <iostream>

using namespace std;

point::point(float x, float y) {
	coo = new float[2];
	coo[0] = x;
	coo[1] = y;
}

point::point(const point& fP){
	coo = new float[2];
	coo[0] = fP.coo[0];
	coo[1] = fP.coo[1];
}

const point& point::operator= (const point& fP) {
	if (this != &fP) {
		coo[0] = fP.coo[0];
		coo[1] = fP.coo[1];
	}

	return *this;
}

point::~point(){
	delete[] coo;
}

point point::operator+(const point& fP)
{
	return point(coo[0] + fP.coo[0],coo[1] + fP.coo[1]);
}

point point::operator-(const point& fP)
{	
	return point (coo[0] - fP.coo[0],coo[1] - fP.coo[1]);
}

point point::operator*(const point& fP)
{	
	return point (coo[0] * fP.coo[0],coo[1] * fP.coo[1]);
}

float point::operator!(){
	return sqrt(coo[0] * coo[0] + coo[1] * coo[1]);
}

void point::Print(){
	cout << "X = " << coo[0] << endl;
	cout << "Y = " << coo[1] << endl;
	cout << "Norma: " << !(*this) << endl;
}
