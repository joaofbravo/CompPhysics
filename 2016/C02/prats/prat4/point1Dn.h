#ifndef __point1Dn__
#define __point1Dn__

#include <cstdio>

class point1Dn {
public:
	point1Dn(double fx=0.); //constructor
	point1Dn(double* fx=NULL); //constructor by pointer
	~point1Dn(); //destructor
	
	//other constructors and operators
	point1Dn(point1Dn&); //copy constructor
	point1Dn& operator=(point1Dn&); //copy assignment
	point1Dn operator+(point1Dn&); //binary +
	
	//other methods
	void print();
	void SetX(double);
	double X();
	

private:
	double *px; //pointer to coord
	
};

#endif