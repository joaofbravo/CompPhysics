#ifndef __point__
#define __point__

#include <iostream>

using namespace std;

class point {
public:
	point(double fx=0., double fy=0.) : x(new double(fx)), y(new double(fy)){ cout << "const default" << endl;} //default constructor
	
	point(const point& p) : x(new double(*(p.x))), y(new double(*(p.y))){
	cout << "copy const" << endl;} //copy constructor
	
	point(point&& P) : x(P.x), y(P.y) {
	P.x = nullptr; P.y=nullptr; cout << "move const" << endl;} //move constructor

	~point() {delete x; delete y; cout << "del" << endl;} //destructor

	const point& operator= (const point& p); //copy assignment
	point& operator= (point&& P); //move assignment

	point operator+(const point& P); //add two points
	const point& operator+=(const point& p); //add point to current point
	const point& operator-(); //symmetric point
	bool operator==(const point& A); //compare two points

	double* X() const {return x;}
	double* Y() const {return y;}

private:
	double *x; //X coordinate ptr
	double *y; //Y coordinate ptr
};

#endif