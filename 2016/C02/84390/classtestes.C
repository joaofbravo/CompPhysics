#include "classtestes.h"
#include <cmath>

using namespace std;

const float epsilon = 0.000001;

//copy assignment
const point& point::operator= (const point& p) {
	//check if address of the current object (this) is the same of the argument
	if (this != &p) {
		x = p.x;
		y = p.y;
	}

	cout << "copy assign" << endl;
	return *this;
}

//move assignment
point& point::operator= (point&& p) {
	delete x;
	delete y;
	
	x = p.x;
	y = p.y;
	
	p.x = nullptr;
	p.y = nullptr;
	
	cout << "move assign" << endl;
	return *this;
}

//add two points
point point::operator+(const point& p) {
	cout << "operator +" << endl;
	return point(*x+*(p.x), *y+*(p.y));
}

//add point to current point
const point& point::operator+=(const point& p) {
	*x += *p.x;
	*y += *p.y;

	cout << "operator +=" << endl;
	return *this;
}

//symmetric point
const point& point::operator-() {
	*x = -(*x);
	*y = -(*y);

	cout << "operator -" << endl;
	return *this;
}

//compare two points
bool point::operator==(const point& p) {
	cout << "operator ==" << endl;

	if (fabs(*x - *(p.x)) <= ( (fabs(*x) > fabs(*(p.x)) ? fabs(*(p.x)) : fabs(*x)) * epsilon ) && 
		fabs(*y - *(p.y)) <= ( (fabs(*y) > fabs(*(p.y)) ? fabs(*(p.y)) : fabs(*y)) * epsilon ))
		return true;
	
	return false;
}